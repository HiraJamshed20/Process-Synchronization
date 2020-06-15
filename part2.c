#include <stdio.h>
#include <semaphore.h>
#include "part2.h"
#include "main.h"
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
/*
	- DO NOT USE SLEEP FUNCTION
	- Define every helper function in .h file
	- Use Semaphores for synchronization purposes
 */

const int INTER_ARRIVAL_TIME = 5;
const int NUM_TRAINS = 5;
int maxCapacity;
int numOfStations;
typedef sem_t Semaphore;

struct passenger{
	int from;
	int to;
	Semaphore* outgoing;
	Semaphore* incoming;
	
};

struct passenger*** station;
int* stationCounter;
int* headIndex;
Semaphore* stationLock;

struct passenger** trainFinalOutput;
int* countFinalOutput;
int* currentCapacity;

struct passenger**** outgoing;
int** outgoingCounter;

/**
 * Do any initial setup work in this function.
 * numStations: Total number of stations. Will be >= 5. Assume that initially
 * the first train is at station 1, the second at 2 and so on.
 * maxNumPeople: The maximum number of people in a train
 */
void initializeP2(int numStations, int maxNumPeople) 
{
	int i = 0;
	maxCapacity = maxNumPeople;
	numOfStations = numStations;

	station = (struct passenger***) malloc(numStations*sizeof(struct passenger **));
	stationCounter = (int *) malloc(numStations*sizeof(int));
	headIndex =  (int *) malloc(numStations*sizeof(int));
	stationLock = (Semaphore *) malloc(numStations*sizeof(Semaphore));
	trainFinalOutput = (struct passenger **) malloc(NUM_TRAINS*sizeof(struct passenger));
	countFinalOutput = (int *) malloc(NUM_TRAINS*sizeof(int));
	currentCapacity = (int *) malloc(NUM_TRAINS*sizeof(int));
	outgoing = (struct passenger****) malloc(NUM_TRAINS*sizeof(struct passenger ***));
	outgoingCounter = (int **) malloc(NUM_TRAINS*sizeof(int*));

	for(i = 0; i < NUM_TRAINS; i++)
	{
		trainFinalOutput[i] = (struct passenger *) malloc(150*sizeof(struct passenger));
		countFinalOutput[i] = 0;
		currentCapacity[i] = 0;
		outgoingCounter[i] = (int *) malloc(numStations*sizeof(int));
		outgoing[i] = (struct passenger***) malloc(numOfStations*sizeof(struct passenger**));
		for(int j = 0; j < numOfStations; j++)
		{
			outgoing[i][j] = (struct passenger **) malloc(150*sizeof(struct passenger *));
		}
		for(int j = 0; j < numOfStations; j++)
		{
			outgoingCounter[i][j] = 0;
		}
	}

	for(i = 0; i < numStations; i++)
	{
		station[i] = (struct passenger**) malloc(150*sizeof(struct passenger*));
		stationCounter[i] = 0;
		headIndex[i] = 0;
		sem_init(&stationLock[i], 0, 1);
		
	}

	
}



void User2(void* arg)
{
	struct passenger* user = arg;
	Semaphore * in = (Semaphore *) malloc(1*sizeof(Semaphore));
	sem_init(in, 0, 0);
	Semaphore * out = (Semaphore *) malloc(1*sizeof(Semaphore));
	sem_init(out, 0, 0);
	user->incoming = in;
	user->outgoing = out;
	sem_wait(&stationLock[user->from]);
	station[user->from][stationCounter[user->from]] = user;
	stationCounter[user->from]++;
	sem_post(&stationLock[user->from]);
	sem_wait(user->incoming);
	sem_wait(user->outgoing);
}

/**
 * Print in the following format:
 * If a user borads on train 0, from station 0 to station 1, and another boards
 * train 2 from station 2 to station 4, then the output will be
 * 0 0 1
 * 2 2 4
 */
void * goingFromToP2(void * user_data) 
{
	User2(user_data);
	return user_data;
}


void* train(void* id)
{
	int* value1 = (int *) id;
	int value2 = *value1;int value3 = value2;
	int currentCount;
	int counter = 0; 
	int i;
	int currentC;
	int value = 0;
	int currentHeadIndex;
	struct passenger* p;
	while(1)
	{
		for(i = value3; i < numOfStations; i++ )
		{		
			sem_wait(&stationLock[i]);
			int current = outgoingCounter[value2][i];
			

			int j = 0;
			while(current > 0)
			{
				sem_post(outgoing[value2][i][j]->outgoing);
				trainFinalOutput[value2][countFinalOutput[value2]] = *outgoing[value2][i][j];
				countFinalOutput[value2]++;
				j++;
				current--;
			}

			currentCount = stationCounter[i];
			currentHeadIndex = headIndex[i];
			outgoingCounter[value2][i] =0;

			currentC = currentCapacity[i];
			int newOutgoingCounter = outgoingCounter[value2][i];
			if(currentC < 50)
			{

				value = 50 - currentC;
				
				if(value >= currentCount)
				{
					currentCapacity[i] = currentC + currentCount;
					while(currentCount > 0)
					{
						p = station[i][currentHeadIndex];
						sem_post(p->incoming);
						outgoing[value2][i][newOutgoingCounter] = p;
						newOutgoingCounter++;
						currentHeadIndex++;
						currentCount--;
					}
					outgoingCounter[value2][i] = newOutgoingCounter;
				}
				else
				{
					while(value > 0)
					{
						p = station[i][currentHeadIndex];
						sem_post(p->incoming);
						outgoing[value2][i][newOutgoingCounter] = p;
						newOutgoingCounter++;
						currentHeadIndex++;
						currentCount--;
						value--;
					}
					currentCapacity[i] = 50;
					outgoingCounter[value2][i] = newOutgoingCounter;
				}
			}
			stationCounter[i] = currentCount;
			headIndex[i] = currentHeadIndex;
			
			sem_post(&stationLock[i]);
			sleep(1);
		}


		
		int Continue = 0;
		
		for(int u = 0; u <5000; u++)
		{
			for(i = 0; i < numOfStations; i++)
			{
				sem_wait(&stationLock[i]);
				if(stationCounter[i] > 0)
				{
					Continue = 1;
					break;
				}
				sem_post(&stationLock[i]);
				if(outgoingCounter[value2][i] > 0)
				{
					Continue = 1;
					break;
				}
			}
		}
		
		if(Continue == 0)
			break;
		
		value3 = 0;
	}
	

}

void * startP2()
{
	sleep(1.5);
	pthread_t thread_id1;
	int i = 0;
	pthread_create(&thread_id1, NULL, train, &i);	
	pthread_t thread_id2;
	int j = 1;
	pthread_create(&thread_id2, NULL, train, &j);
	pthread_t thread_id3;
	int x = 2;
	pthread_create(&thread_id3, NULL, train, &x);
	pthread_t thread_id4;
	int y = 3;
	pthread_create(&thread_id4, NULL, train, &y);
	pthread_t thread_id5;
	int z = 4;
	pthread_create(&thread_id5, NULL, train, &z);

	pthread_join(thread_id1, NULL);
	pthread_join(thread_id2, NULL);
	pthread_join(thread_id3, NULL);
	pthread_join(thread_id4, NULL);
	pthread_join(thread_id5, NULL);


	for(int d = 0; d < countFinalOutput[0]; d++)
	{
		printf("0 %d %d\n", trainFinalOutput[0][d].from, trainFinalOutput[0][d].to);
	}
	for(int d = 0; d < countFinalOutput[1]; d++)
	{
		printf("1 %d %d\n", trainFinalOutput[1][d].from, trainFinalOutput[1][d].to);
	}
	for(int d = 0; d < countFinalOutput[2]; d++)
	{
		printf("2 %d %d\n", trainFinalOutput[2][d].from, trainFinalOutput[2][d].to);
	}
	for(int d = 0; d < countFinalOutput[3]; d++)
	{
		printf("3 %d %d\n", trainFinalOutput[3][d].from, trainFinalOutput[3][d].to);
	}
	for(int d = 0; d < countFinalOutput[4]; d++)
	{
		printf("4 %d %d\n", trainFinalOutput[4][d].from, trainFinalOutput[4][d].to);
	}

	free(stationCounter);
	free(headIndex);
	free(stationLock);
	free(countFinalOutput);
	free(currentCapacity);

	for(int f = 0; f < numOfStations; f++)
	{
		if(station[i] != NULL)
			for(int j = 0; j < 150; j++)
			{
				free(station[f][j]);
			}
		free(station[f]);
	}

	free(station);

	for(int f = 0; f < NUM_TRAINS; f++)
	{
		if(trainFinalOutput[f] != NULL)
			free(trainFinalOutput[f]);
	}

	free(trainFinalOutput);
		
	for(int m = 0; m < NUM_TRAINS; m++)
	{
		for(int l = 0; l < numOfStations; l++)
		{
			free(outgoing[m][l]);
		}
		free(outgoing[m]);
	}
	
	free(outgoing);

	for(int k = 0; k < NUM_TRAINS; k++)
	{
		free(outgoingCounter[k]);
	}
	free(outgoingCounter);
	return NULL;
}