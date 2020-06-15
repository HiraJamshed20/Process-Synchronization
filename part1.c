#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h> 
#include "part1.h"
#include "main.h"
#include <unistd.h>
#include <string.h>
#include <fcntl.h> 
#include <assert.h>


struct Person{
	int id;
	int to;
	int from;
};

int MAX_NUM_FLOORS = 20;
int MAX_NUM_PEOPLE = 20;
typedef sem_t Semaphore;
Semaphore* InComing1;
Semaphore* OutGoing1;
Semaphore* InComing2;
Semaphore* OutGoing2;
Semaphore* print;
Semaphore* check2;
Semaphore* check1Incoming;
Semaphore* check2Incoming;
Semaphore* check1Outgoing;
Semaphore* check2Outgoing;
struct Person* person1;
struct Person* person2;
int countPerson1;
int countPerson2;
int* elevator1Incoming;
int* elevator1OutGoing;
int* elevator2Incoming;
int* elevator2OutGoing;
int E1;
int E2;
int count; 
Semaphore* print1;
Semaphore* print2;


void User(void* arg){

	int toFloor = ((struct argument *) arg)->to;
	int fromFloor = ((struct argument *) arg)->from;
	struct argument* k;
	if(toFloor - fromFloor > 0)
	{
		sem_wait(check1Incoming);
		elevator1Incoming[fromFloor]++;
		sem_post(check1Incoming);

		sem_wait(&InComing1[fromFloor]);

		sem_wait(check1Outgoing);
		elevator1OutGoing[toFloor]++;
		sem_post(check1Outgoing);

		sem_wait(&OutGoing1[toFloor]);


		sem_wait(print1);
		k = arg;
		person1[countPerson1].id = k->id;
		person1[countPerson1].from = k->from;
		person1[countPerson1].to = k->to;
		countPerson1++;
		sem_post(print1);

	}
	else
	{
		sem_wait(check2Incoming);
		elevator2Incoming[fromFloor]++;
		sem_post(check2Incoming);
		sem_wait(&InComing2[fromFloor]);
		

		sem_wait(check2Outgoing);
		elevator2OutGoing[toFloor]++;
		sem_post(check2Outgoing);


		sem_wait(&OutGoing2[toFloor]);
		sem_wait(print2);
		k = arg;
		person2[countPerson2].id = k->id;
		person2[countPerson2].from = k->from;
		person2[countPerson2].to = k->to;
		countPerson2++;
		sem_post(print2);

		
	}
}


void* Elevator1(){

	int i = 0;
	int value;
	int* value2;
	int temp;
	int count2 = 0;
	int Continue;
	int count1 = 0;
	int* k;
	while(1)
	{
		for(i = 0; i < MAX_NUM_FLOORS; i++)
		{
			sem_wait(check1Outgoing);
			value = elevator1OutGoing[i];
			sem_post(check1Outgoing);

			while(value > 0)
			{
				E1--;
				sem_post(&OutGoing1[i]);
				value--;			
			}
			sem_wait(check1Outgoing);
			elevator1OutGoing[i] = value;
			sem_post(check1Outgoing);

			sem_wait(check1Incoming);
			value = elevator1Incoming[i];
			sem_post(check1Incoming);

			if(value <= MAX_NUM_PEOPLE - E1)
			{
				while(value > 0)
				{
					sem_post(&InComing1[i]);
					value--;
					E1++;	
				}	
			}
			else
			{
				while(MAX_NUM_PEOPLE - E1 > 0)
				{
					sem_post(&InComing1[i]);
					value--;
					E1++;
				}
			}
			sem_wait(check1Incoming);
			elevator1Incoming[i] = value;
			sem_post(check1Incoming);
		}

		for(i = MAX_NUM_FLOORS - 1; i >= 0; i--)
		{
			sem_wait(check1Outgoing);
			value = elevator1OutGoing[i];
			sem_post(check1Outgoing);
			while(value > 0)
			{
				sem_post(&OutGoing1[i]);
				value--;
				E1--;
			}

			sem_wait(check1Outgoing);
			elevator1OutGoing[i] = value;
			sem_post(check1Outgoing);

			sem_wait(check1Incoming);
			value = elevator1Incoming[i];
			sem_post(check1Incoming);

			if(value <= MAX_NUM_PEOPLE - E1)
			{
				while(value > 0)
				{
					sem_post(&InComing1[i]);
					value--;
					E1++;
				}
			}
			else
			{
				while(MAX_NUM_PEOPLE - E1 > 0)
				{
					sem_post(&InComing1[i]);
					value--;
					E1++;
				}
			}
			sem_wait(check1Incoming);
			elevator1Incoming[i] = value;
			sem_post(check1Incoming);

		}
		
		Continue = 0;
		for(i = 0; i < MAX_NUM_FLOORS; i++)
		{
			sem_wait(check1Incoming);
			value = elevator1Incoming[i];
			sem_post(check1Incoming);

			if(value > 0)
			{
				Continue = 1;
				break;
			}

			sem_wait(check1Outgoing);
			value = elevator1OutGoing[i];
			sem_post(check1Outgoing);
			if(value > 0)
			{
				Continue = 1;
				break;
			}
		}

		if(Continue == 0)
			count1++;
		else
			count1 = 0;
		if (count1 == 10000)
			break;
	}

}

void* Elevator2(){

	int i;
	int Continue;
	int value;
	int count2 = 0;
	int count3;
	int* value2;
	while(1)
	{
		for(i = MAX_NUM_FLOORS - 1; i >= 0; i--)
		{
			sem_wait(check2Outgoing);
			value = elevator2OutGoing[i];
			sem_post(check2Outgoing);

			while(value > 0)
			{
				E2--;
				sem_post(&OutGoing2[i]);
				value--;
			}

			sem_wait(check2Outgoing);
			elevator2OutGoing[i] = value;
			sem_post(check2Outgoing);

			sem_wait(check2Incoming);
			value = elevator2Incoming[i];
			sem_post(check2Incoming);

			if(value <= MAX_NUM_PEOPLE - E2)
			{
				while(value > 0)
				{
					sem_post(&InComing2[i]);
					value--;
					E2++;
				}
			}
			else
			{
				while(MAX_NUM_PEOPLE - E2 > 0)
				{
					sem_post(&InComing2[i]);
					value--;
					E2++;
				}
			}

			sem_wait(check2Incoming);
			elevator2Incoming[i] = value;
			sem_post(check2Incoming);
		}

		for(i = 0; i < MAX_NUM_FLOORS; i++)
		{
			sem_wait(check2Outgoing);
			value = elevator2OutGoing[i];
			sem_post(check2Outgoing);

			while(value > 0)
			{
				sem_post(&OutGoing2[i]);
				value--;
				E2--;
			}

			sem_wait(check2Outgoing);
			elevator2OutGoing[i] = value;
			sem_post(check2Outgoing);

			sem_wait(check2Incoming);
			value = elevator2Incoming[i];
			sem_post(check2Incoming);
			if(value <= MAX_NUM_PEOPLE - E2)
			{
				while(value > 0)
				{
					sem_post(&InComing2[i]);
					value--;
					E2++;
				}
			}
			else
			{
				while(MAX_NUM_PEOPLE - E2 > 0)
				{
					sem_post(&InComing2[i]);
					value--;
					E2++;
				}
			}
			sem_wait(check2Incoming);
			elevator2Incoming[i] = value;
			sem_post(check2Incoming);
		}

		// count++;
		// if(count == 500)
		// 	break;
		Continue = 0;
		for(i = 0; i < MAX_NUM_FLOORS; i++)
		{
			sem_wait(check2Incoming);
			value = elevator2Incoming[i];
			sem_post(check2Incoming);
			if(value > 0)
			{
				Continue = 1;
				break;
			}

			sem_wait(check2Outgoing);
			value = elevator2OutGoing[i];
			sem_post(check2Outgoing);
			if(value > 0)
			{
				Continue = 1;
				break;
			}
		}

		if(Continue == 0)
			count2++;
		else
			count2 = 0;
		if (count2 == 10000)
			break;
	}
}

/**
 * Do any initial setup work in this function.
 * numFloors: Total number of floors elevator can go to | will be smaller or equal to MAX_NUM_FLOORS
 * maxNumPeople: The maximum capacity of the elevator
 * 
 * Two elevators should start, one from the ground floor (elevator 1) and
 * the other one from the top floor (elevator 2).
 *
 * Note that: Elevator 1 starts from ground floor and goes up
 * Elevator 2 starts from Top floor and goes down.
 */

void initializeP1(int numFloors, int maxNumPeople) {

	int random;
	MAX_NUM_FLOORS = numFloors;
	MAX_NUM_PEOPLE = maxNumPeople;
	InComing1 = (Semaphore *) malloc(numFloors*sizeof(Semaphore));
	OutGoing1 = (Semaphore *) malloc(numFloors*sizeof(Semaphore));
	InComing2 = (Semaphore *) malloc(numFloors*sizeof(Semaphore));
	OutGoing2 = (Semaphore *) malloc(numFloors*sizeof(Semaphore));
	print = (Semaphore *) malloc(maxNumPeople*5*sizeof(Semaphore));
	elevator1Incoming = (int *) malloc(MAX_NUM_FLOORS*sizeof(int));
	elevator2Incoming = (int *) malloc(MAX_NUM_FLOORS*sizeof(int));
	elevator2OutGoing = (int *) malloc(MAX_NUM_FLOORS*sizeof(int));
	elevator1OutGoing = (int *) malloc(MAX_NUM_FLOORS*sizeof(int));
	
	for(random = 0; random < numFloors; random++)
	{
		sem_init(&InComing1[random], 0, 0);
		sem_init(&OutGoing1[random], 0, 0);
		sem_init(&OutGoing2[random], 0, 0);
		sem_init(&InComing2[random], 0, 0);
	}

	for(random = 0; random < numFloors; random++)
	{
		elevator2Incoming[random] = 0;
		elevator1Incoming[random] = 0;
		elevator1OutGoing[random] = 0;
		elevator2OutGoing[random] = 0;
	}


	for(random = 0; random < maxNumPeople*5; random++)
	{
		sem_init(&print[random], 0, 0);
	}

	E1 = 0;
	E2 = 0;
	count = 0;
	check2 = (Semaphore*) malloc(1*sizeof(Semaphore));
	sem_init(check2, 0, 1);
	check2Outgoing = (Semaphore*) malloc(1*sizeof(Semaphore));
	check1Outgoing = (Semaphore*) malloc(1*sizeof(Semaphore));
	check2Incoming = (Semaphore*) malloc(1*sizeof(Semaphore));
	check1Incoming = (Semaphore*) malloc(1*sizeof(Semaphore));
	sem_init(check1Outgoing, 0, 1);
	sem_init(check2Outgoing, 0, 1);
	sem_init(check2Incoming, 0, 1);
	sem_init(check1Incoming, 0, 1);

	person1 = (struct Person *) malloc(maxNumPeople*5*sizeof(struct Person));
	person2 = (struct Person *) malloc(maxNumPeople*5*sizeof(struct Person));
	print1 = (Semaphore *) malloc(1*sizeof(Semaphore));
	sem_init(print1, 0, 1);
	print2 = (Semaphore *) malloc(1*sizeof(Semaphore));
	sem_init(print2, 0, 1);
	countPerson1 = 0;
	countPerson2 = 0;
}

/**
 * Every passenger will call this function when 
 * he/she wants to take the elevator. (Already
 * called in main.c)
 * 
 * This function should print info "id from to" without quotes,
 * where:
 * 	id = id of the user
 * 	from = source floor (from where the passenger is taking the elevator)
 * 	to = destination floor (floor where the passenger is going)
 * 
 * info of a user x getting off the elevator before the user xx
 * should be printed before.
 * 
 * Suppose a user 1 from floor 1 wants to go to floor 4 and
 * a user 2 from floor 2 wants to go to floor 3 then the final print statements
 * will be 
 * 2 2 3
 * 1 1 4
 * 
 * Also, all print statements (info) of passengers in elevator 1 should be printed before
 * the print statements (info) of passengers in elevator 2.
 */

void* goingFromToP1(void *arg) {
	User(arg);
	return arg;

}

/*If you see the main file, you will get to 
know that this function is called after setting every
passenger.
So use this function for starting your elevators. In 
this way, you will be sure that all passengers are already
waiting for elevators.
*/

void startP1(){
	int i;
	pthread_t thread_id1; 
	pthread_t thread_id2; 

	sleep(MAX_NUM_PEOPLE/3);
	
    pthread_create(&thread_id1, NULL, Elevator1, NULL); 
    pthread_create(&thread_id2, NULL, Elevator2, NULL); 
    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);
   	
   	for(i = 0; i < countPerson1; i++)
   	{
   		printf("%d %d %d\n", person1[i].id, person1[i].from, person1[i].to);
   	}

   	for(i = 0; i < countPerson2; i++)
   	{
   		printf("%d %d %d\n", person2[i].id, person2[i].from, person2[i].to);
   	}

   	free(InComing1);
   	free(InComing2);
   	free(OutGoing2);
   	free(OutGoing1);
   	free(check2);
   	free(person2);
   	free(person1);
   	free(print1);
   	free(print2);
	return;
}