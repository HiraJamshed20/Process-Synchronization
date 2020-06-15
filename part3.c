#include <stdio.h>
#include <semaphore.h>
#include "part3.h"
#include "main.h"
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
/*
	- DO NOT USE SLEEP FUNCTION
	- Define every helper function in .h file
	- Use Semaphores for synchronization purposes
 */



typedef sem_t Semaphore;

Semaphore* NorthRight;
Semaphore* NorthLeft;
int i = 40;

Semaphore* SouthRight;
Semaphore* SouthLeft;

Semaphore* WestRight;
Semaphore* WestLeft;

Semaphore* EastRight;
Semaphore* EastLeft;

int NorthRightCount;
Semaphore* LockNorthRight;

int NorthLeftCount;
Semaphore* LockNorthLeft;

int SouthRightCount;
Semaphore* LockSouthRight;

int SouthLeftCount;
Semaphore* LockSouthLeft;

int EastRightCount;
Semaphore* LockEastRight;

int EastLeftCount;
Semaphore* LockEastLeft;

int WestRightCount;
Semaphore* LockWestRight;

int WestLeftCount;
Semaphore* LockWestLeft;

int* TrackerWestLeft;
int WestLeftIndexHead;

int* TrackerEastLeft;
int EastLeftIndexHead;

int* TrackerNorthLeft;
int NorthLeftIndexHead;

int* TrackerSouthLeft;
int SouthLeftIndexHead;

struct argumentP3* northleft;
int northleftfill;

struct argumentP3* northright;
int northrightfill;

struct argumentP3* southleft;
int southleftfill;

struct argumentP3* southright;
int southrightfill;

struct argumentP3* eastleft;
int eastleftfill;

struct argumentP3* eastright;
int eastrightfill;

struct argumentP3* westleft;
int westleftfill;

struct argumentP3* westright;
int westrightfill;

Semaphore* nl;
Semaphore* nr;
Semaphore* sl;
Semaphore* sr;
Semaphore* el;
Semaphore* er;
Semaphore* wl;
Semaphore* wr;

void initializeP3() {

	NorthRight = (Semaphore *) malloc(1*sizeof(Semaphore));
	NorthLeft = (Semaphore *) malloc(1*sizeof(Semaphore));
	sem_init(NorthRight, 0, 0);
	sem_init(NorthLeft, 0, 0);
	NorthLeftCount = 0;
	NorthRightCount = 0;
	LockNorthLeft = (Semaphore *) malloc(1*sizeof(Semaphore));
	LockNorthRight = (Semaphore *) malloc(1*sizeof(Semaphore));
	sem_init(LockNorthRight, 0, 1);
	sem_init(LockNorthLeft, 0, 1);
	TrackerNorthLeft = (int *) malloc(150*sizeof(int));
	NorthLeftIndexHead = 0;

	SouthRight = (Semaphore *) malloc(1*sizeof(Semaphore));
	SouthLeft = (Semaphore *) malloc(1*sizeof(Semaphore));
	sem_init(SouthRight, 0, 0);
	sem_init(SouthLeft, 0, 0);
	SouthLeftCount = 0;
	SouthRightCount = 0;
	LockSouthLeft = (Semaphore *) malloc(1*sizeof(Semaphore));
	LockSouthRight = (Semaphore *) malloc(1*sizeof(Semaphore));
	sem_init(LockSouthRight, 0, 1);
	sem_init(LockSouthLeft, 0, 1);
	TrackerSouthLeft = (int *) malloc(150*sizeof(int));
	SouthLeftIndexHead = 0;

	WestLeft = (Semaphore *) malloc(1*sizeof(Semaphore));
	WestRight = (Semaphore *) malloc(1*sizeof(Semaphore));
	sem_init(WestRight, 0, 0);
	sem_init(WestLeft, 0, 0);
	WestRightCount = 0;
	WestLeftCount = 0;
	LockWestLeft = (Semaphore *) malloc(1*sizeof(Semaphore));
	LockWestRight = (Semaphore *) malloc(1*sizeof(Semaphore));
	sem_init(LockWestRight, 0, 1);
	sem_init(LockWestLeft, 0, 1);
	TrackerWestLeft = (int *) malloc(150*sizeof(int));
	WestLeftIndexHead = 0;

	EastLeft = (Semaphore *) malloc(1*sizeof(Semaphore));
	EastRight = (Semaphore *) malloc(1*sizeof(Semaphore));
	sem_init(EastRight, 0, 0);
	sem_init(EastLeft, 0, 0);
	EastLeftCount = 0;
	EastRightCount = 0;
	LockEastLeft = (Semaphore *) malloc(1*sizeof(Semaphore));
	LockEastRight = (Semaphore *) malloc(1*sizeof(Semaphore));
	sem_init(LockEastRight, 0, 1);
	sem_init(LockEastLeft, 0, 1);
	TrackerEastLeft = (int *) malloc(150*sizeof(int));
	EastLeftIndexHead = 0;

	northleft = (struct argumentP3 *) malloc(150*sizeof(struct argumentP3));
	northleftfill = 0;

	northright = (struct argumentP3 *) malloc(150*sizeof(struct argumentP3));
	northrightfill = 0;

	southleft = (struct argumentP3 *) malloc(150*sizeof(struct argumentP3));
	southleftfill = 0;

	southright = (struct argumentP3 *) malloc(150*sizeof(struct argumentP3));
	southrightfill = 0;

	eastleft = (struct argumentP3 *) malloc(150*sizeof(struct argumentP3));
	eastleftfill = 0;

	eastright = (struct argumentP3 *) malloc(150*sizeof(struct argumentP3));
	eastrightfill = 0;

	westleft = (struct argumentP3 *) malloc(150*sizeof(struct argumentP3));
	westleftfill = 0;

	westright = (struct argumentP3 *) malloc(150*sizeof(struct argumentP3));
	westrightfill = 0;

	nl = (Semaphore *) malloc(1*sizeof(Semaphore));
	nr = (Semaphore *) malloc(1*sizeof(Semaphore));
	sl = (Semaphore *) malloc(1*sizeof(Semaphore));
	sr = (Semaphore *) malloc(1*sizeof(Semaphore));
	el = (Semaphore *) malloc(1*sizeof(Semaphore));
	er = (Semaphore *) malloc(1*sizeof(Semaphore));
	wl = (Semaphore *) malloc(1*sizeof(Semaphore));
	wr = (Semaphore *) malloc(1*sizeof(Semaphore));

	sem_init(nl, 0, 1);
	sem_init(nr, 0, 1);
	sem_init(sl, 0, 1);
	sem_init(sr, 0, 1);
	sem_init(el, 0, 1);
	sem_init(er, 0, 1);
	sem_init(wl, 0, 1);
	sem_init(wr, 0, 1);

}

/**
 * If there is a argumentP3 going from SOUTH to NORTH, from lane LEFT,
 * print 
 * SOUTH NORTH LEFT
 * Also, if two argumentP3s can simulateneously travel in the two lanes,
 * first print all the argumentP3s in the LEFT lane, followed by all the
 * argumentP3s in the right lane
 */

void User3(void* argu)
{
	struct argumentP3* arg = (struct argumentP3*) argu;
	int from = arg->from;
	int to = arg->to;
	int lane = arg->lane;
	int current;
	if(from == 0)
	{
		// North
		if(lane == 0)
		{
			// left
			if(to == 1)
			{
				sem_wait(LockNorthLeft);
				NorthLeftCount++;
				TrackerNorthLeft[NorthLeftCount-1] = 1;
				sem_post(LockNorthLeft);
				sem_wait(NorthLeft);
			}
			else
			{
				sem_wait(LockNorthLeft);
				current = NorthLeftCount;

				if(current == 0)
				{
					// done
					sem_post(LockNorthLeft);
				}
				else
				{
					NorthLeftCount++;
					TrackerNorthLeft[NorthLeftCount-1] = 0;
					sem_post(LockNorthLeft);
					sem_wait(NorthLeft);
					
				}

				
			}
			sem_wait(nl);
			northleft[northleftfill].from = arg->from;
			northleft[northleftfill].to = arg->to;
			northleft[northleftfill].lane = arg->lane;
			northleftfill++;
			sem_post(nl);
		}
		else if(lane  == 1)
		{
			// Right
			sem_wait(LockNorthRight);
			NorthRightCount++;
			sem_post(LockNorthRight);
			sem_wait(NorthRight);	
			sem_wait(nr);
			northright[northrightfill].from = arg->from;
			northright[northrightfill].to = arg->to;
			northright[northrightfill].lane = arg->lane;
			northrightfill++;
			sem_post(nr);
		}

		
	}
	else if(from == 1)
	{
		// South
		if(lane == 0)
		{
			// left
			if(to == 0)
			{
				sem_wait(LockSouthLeft);
				SouthLeftCount++;
				TrackerSouthLeft[SouthLeftCount-1] = 1;
				sem_post(LockSouthLeft);
				sem_wait(SouthLeft);
			}
			else
			{
				sem_wait(LockSouthLeft);
				current = SouthLeftCount;
		
				if(current == 0)
				{
					// done
					sem_post(LockSouthLeft);
				}
				else
				{
					SouthLeftCount++;
					TrackerSouthLeft[SouthLeftCount-1] = 0;
					sem_post(LockSouthLeft);
					sem_wait(SouthLeft);
				}
				
			}
			sem_wait(sl);
			southleft[southleftfill].from = arg->from;
			southleft[southleftfill].to = arg->to;
			southleft[southleftfill].lane = arg->lane;
			southleftfill++;
			sem_post(sl);
		}
		else if(lane  == 1)
		{
			// Right
			sem_wait(LockSouthRight);
			SouthRightCount++;
			sem_post(LockSouthRight);
			sem_wait(SouthRight);
			sem_wait(sr);
			southright[southrightfill].from = arg->from;
			southright[southrightfill].to = arg->to;
			southright[southrightfill].lane = arg->lane;
			southrightfill++;
			sem_post(sr);
			
		}
	}
	else if(from == 2)
	{
		// East
		if(lane == 0)
		{
			// left
			if(to == 3)
			{
				sem_wait(LockEastLeft);
				EastLeftCount++;
				TrackerEastLeft[EastLeftCount-1] = 1;
				sem_post(LockEastLeft);
				sem_wait(EastLeft);
			}
			else
			{
				sem_wait(LockEastLeft);
				current = EastLeftCount;

				if(current == 0)
				{
					// done
					sem_post(LockEastLeft);
				}
				else
				{
					EastLeftCount++;
					TrackerEastLeft[EastLeftCount-1] = 0;
					sem_post(LockEastLeft);
					sem_wait(EastLeft);
				}
				
			}
			sem_wait(el);
			eastleft[eastleftfill].from = arg->from;
			eastleft[eastleftfill].to = arg->to;
			eastleft[eastleftfill].lane = arg->lane;
			eastleftfill++;
			sem_post(el);
		}
		else if(lane  == 1)
		{
			// Right
			sem_wait(LockEastRight);
			EastRightCount++;
			sem_post(LockEastRight);
			sem_wait(EastRight);

			sem_wait(er);
			eastright[eastrightfill].from = arg->from;
			eastright[eastrightfill].to = arg->to;
			eastright[eastrightfill].lane = arg->lane;
			eastrightfill++;
			sem_post(er);
		}
	}
	else if(from == 3)
	{
		// West
		if(lane == 0)
		{
			// left
			if(to == 2)
			{
				sem_wait(LockWestLeft);
				WestLeftCount++;
				TrackerWestLeft[WestLeftCount-1] = 1;
				sem_post(LockWestLeft);
				sem_wait(WestLeft);
			}
			else
			{
				sem_wait(LockWestLeft);
				current = WestLeftCount;

				if(current == 0)
				{
					// done
					sem_post(LockWestLeft);
				}
				else
				{
					WestLeftCount++;
					TrackerWestLeft[WestLeftCount-1] = 0;
					sem_post(LockWestLeft);
					sem_wait(WestLeft);

				}
				
			}
			sem_wait(wl);
			westleft[westleftfill].from = arg->from;
			westleft[westleftfill].to = arg->to;
			westleft[westleftfill].lane = arg->lane;
			westleftfill++;
			sem_post(wl);
		}
		else if(lane  == 1)
		{
			// Right
			sem_wait(LockWestRight);
			WestRightCount++;
			sem_post(LockWestRight);
			sem_wait(WestRight);

			sem_wait(wr);
			westright[westrightfill].from = arg->from;
			westright[westrightfill].to = arg->to;
			westright[westrightfill].lane = arg->lane;
			westrightfill++;
			sem_post(wr);
		}
	}

}

void * goingFromToP3(void *argu){
	User3(argu);
	return argu;
}

void* trafficController()
{
	int value;
	int counter = 0;
	int current;
	int remaining = 0;
	int Continue;
	while (1) {

		//NORTH LEFT
		remaining = 0;
		sem_wait(LockNorthLeft);

		if( NorthLeftCount <= 5)
		{
			// total less than or = to 5
			remaining = 5 - NorthLeftCount;
			while(NorthLeftCount > 0)
			{
				sem_post(NorthLeft);
				NorthLeftCount--;
			}
		}
		else
		{
			// greater than 5
			value = 5;
			NorthLeftCount = NorthLeftCount - 5;
			while(value > 0)
			{
				sem_post(NorthLeft);
				value--;
			}

			NorthLeftIndexHead = NorthLeftIndexHead + 5;
	
			while(1)
			{
				if(TrackerNorthLeft[NorthLeftIndexHead] == 0)
				{
					sem_post(NorthLeft);
				}
				else
				{
					break;
				}

				NorthLeftIndexHead++;
			}

		}

		sem_post(LockNorthLeft);

		
		// NORTH RIGHT

		if(remaining > 0)
		{
			sem_wait(LockNorthRight);

			while(remaining > 0)
			{
				sem_post(NorthRight);
				remaining--;
				NorthRightCount--;
			}

			sem_post(LockNorthRight);
		}

		sleep(1);
		// EAST LEFT
		remaining = 0;
		sem_wait(LockEastLeft);

		if( EastLeftCount <= 5)
		{
			// total less than or = to 5
			remaining = 5 - EastLeftCount;
			while(EastLeftCount > 0)
			{
				sem_post(EastLeft);
				EastLeftCount--;
			}
		}
		else
		{
			// greater than 5
			value = 5;
			EastLeftCount = EastLeftCount - 5;
			while(value > 0)
			{
				sem_post(EastLeft);
				value--;
			}

			EastLeftIndexHead = EastLeftIndexHead + 5;
	
			while(1)
			{
				if(TrackerEastLeft[EastLeftIndexHead] == 0)
				{
					sem_post(EastLeft);
				}
				else
				{
					break;
				}

				EastLeftIndexHead++;
			}

		}

		sem_post(LockEastLeft);


		// EAST RIGHT

		if(remaining > 0)
		{
			sem_wait(LockEastRight);

			while(remaining > 0)
			{
				sem_post(EastRight);
				remaining--;
				EastRightCount--;
			}

			sem_post(LockEastRight);
		}

		sleep(1);
		//SOUTH LEFT
		remaining = 0;
		sem_wait(LockSouthLeft);

		if( SouthLeftCount <= 5)
		{
			// total less than or = to 5
			remaining = 5 - SouthLeftCount;
			while(SouthLeftCount > 0)
			{
				sem_post(SouthLeft);
				SouthLeftCount--;
			}
		}
		else
		{
			// greater than 5
			value = 5;
			SouthLeftCount = SouthLeftCount - 5;
			while(value > 0)
			{
				sem_post(SouthLeft);
				value--;
			}

			SouthLeftIndexHead = SouthLeftIndexHead + 5;
	
			while(1)
			{
				if(TrackerSouthLeft[SouthLeftIndexHead] == 0)
				{
					sem_post(SouthLeft);
				}
				else
				{
					break;
				}

				SouthLeftIndexHead++;
			}

		}

		sem_post(LockSouthLeft);

		
		// SOUTH RIGHT

		if(remaining > 0)
		{
			sem_wait(LockSouthRight);

			while(remaining > 0)
			{
				sem_post(SouthRight);
				remaining--;
				SouthRightCount--;
			}

			sem_post(LockSouthRight);
		}

		sleep(1);
		// WEST LEFT
		remaining = 0;
		sem_wait(LockWestLeft);

		if( WestLeftCount <= 5)
		{
			// total less than or = to 5
			remaining = 5 - WestLeftCount;
			while(WestLeftCount > 0)
			{
				sem_post(WestLeft);
				WestLeftCount--;
			}
		}
		else
		{
			// greater than 5
			value = 5;
			WestLeftCount = WestLeftCount - 5;
			while(value > 0)
			{
				sem_post(WestLeft);
				value--;
			}

			WestLeftIndexHead = WestLeftIndexHead + 5;
	
			while(1)
			{
				if(TrackerWestLeft[WestLeftIndexHead] == 0)
				{
					sem_post(WestLeft);
				}
				else
				{
					break;
				}

				WestLeftIndexHead++;
			}

		}

		sem_post(LockWestLeft);

		
		// WEST RIGHT

		if(remaining > 0)
		{
			sem_wait(LockWestRight);

			while(remaining > 0)
			{
				sem_post(WestRight);
				remaining--;
				WestRightCount--;
			}

			sem_post(LockWestRight);
		}

		sleep(1);

		Continue = 0;
		for(int i = 0; i < 5000; i++)
		{
			sem_wait(LockNorthLeft);
			if(NorthLeftCount > 0)
			{
				Continue = 1;
				sem_post(LockNorthLeft);
				break;
			}
			
			sem_post(LockNorthLeft);

			sem_wait(LockNorthRight);
			if(NorthRightCount > 0)
			{
				Continue = 1;
				sem_post(LockNorthRight);
				break;
			}

			sem_post(LockNorthRight);

			sem_wait(LockSouthLeft);

			if(SouthLeftCount > 0)
			{
				Continue = 1;
				sem_post(LockSouthLeft);
				break;
			}

			sem_post(LockSouthLeft);

			sem_wait(LockSouthRight);

			if(SouthRightCount > 0)
			{
				Continue = 1;
				sem_post(LockSouthRight);
				break;
			}

			sem_post(LockSouthRight);

			sem_wait(LockEastLeft);

			if(EastLeftCount > 0)
			{
				Continue = 1;
				sem_post(LockEastLeft);
				break;
			}

			sem_post(LockEastLeft);

			sem_wait(LockEastRight);

			if(EastRightCount > 0)
			{
				Continue = 1;
				sem_post(LockEastRight);
				break;
			}

			sem_post(LockEastRight);

			sem_wait(LockWestLeft);

			if(WestLeftCount > 0)
			{
				Continue = 1;
				sem_post(LockWestLeft);
				break;
			}

			sem_post(LockWestLeft);

			sem_wait(LockWestRight);

			if(WestRightCount > 0)
			{
				Continue = 1;
				sem_post(LockWestRight);
				break;
			}

			sem_post(LockWestRight);

		}
		
		if(Continue == 0)
			break;
		
	}

}

void startP3(){
	int i = 0;
	pthread_t trafficController1;
 	pthread_create(&trafficController1, NULL, trafficController, NULL); 
 	pthread_join(trafficController1, NULL);

 	for(i = 0; i < northleftfill; i++)
 	{
 		printf("NORTH ");
 		if(northleft[i].to == 1)
 		{
 			printf("SOUTH ");
 		}
 		else
 		{
 			printf("EAST ");
 		}

 		printf("LEFT\n");
 		
 		
 	}

 	for(i = 0; i < northrightfill; i++)
 	{
 		printf("NORTH WEST RIGHT\n");
 	}

 	for(i = 0; i < eastleftfill; i++)
 	{
 		printf("EAST ");
 		if(eastleft[i].to == 3)
 		{
 			printf("WEST ");
 		}
 		else
 		{
 			printf("NORTH ");
 		}

 		printf("LEFT\n");
 		
 	}

 	for(i = 0; i < eastrightfill; i++)
 	{
 		printf("EAST NORTH RIGHT\n");
 	}

 	for(i = 0; i < southleftfill; i++)
 	{
 		printf("SOUTH ");
 		if(southleft[i].to == 0)
 		{
 			printf("NORTH ");
 		}
 		else
 		{
 			printf("WEST ");
 		}

 		printf("LEFT\n");
 		
 	}

 	for(i = 0; i < southrightfill; i++)
 	{
 		printf("SOUTH EAST RIGHT\n");
 	}


 	for(i = 0; i < westleftfill; i++)
 	{
 		printf("WEST ");
 		if(westleft[i].to == 2)
 		{
 			printf("EAST ");
 		}
 		else
 		{
 			printf("NORTH ");
 		}

 		printf("LEFT\n");
 		
 	}

 	for(i = 0; i < westrightfill; i++)
 	{
 		printf("WEST SOUTH RIGHT\n");
 	}

 	free(NorthRight);
 	free(NorthLeft);
 	free(SouthRight);
 	free(SouthLeft);
 	free(EastLeft);
 	free(EastRight);
 	free(WestRight);
 	free(WestLeft);

 	free(nl);
 	free(nr);
 	free(er);
 	free(el);
 	free(sr);
 	free(sl);
 	free(wr);
 	free(wl);

 	free(northleft);
 	free(northright);
 	free(eastleft);
 	free(eastright);
 	free(southleft);
 	free(southright);
 	free(westleft);
 	free(westright);

 	free(TrackerNorthLeft);
 	free(TrackerWestLeft);
 	free(TrackerEastLeft);
 	free(TrackerSouthLeft);

 	free(LockSouthRight);
 	free(LockSouthLeft);
 	free(LockWestLeft);
 	free(LockWestRight);
 	free(LockNorthRight);
 	free(LockNorthLeft);
 	free(LockEastLeft);
 	free(LockEastRight);
}