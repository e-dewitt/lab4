//Authors: Ellen DeWitt and Aisha Iftikhar
//Class: CSE 2431 Spring 2019
//Instructor:
//Grader:

//libraries needed for this lab
#include<pthread.h> 
#include<semaphore.h> 
#include<stdio.h> 
#include<unistd.h>
#include<stdlib.h> 

//define the number of threads (philosophers) as a constant
#define NUM_THREADS 5

//Global variables 
int philosophers[5] = {0, 1, 2, 3, 4};
int forks[5] = {1, 1, 1, 1, 1};

//max and min number of seconds that the think and eat methods will execute for
int max_time = 10;
int min_time = 1;

//mutex forx variables
pthread_mutex_t fork_id[NUM_THREADS];

//Function Prototypes
void *philosopher(void *philosopher_thread);
void think(int this_philosipher);
void get_forks(int this_philosipher);
void put_forks(int this_philosipher);
void eat(int this_philosipher);

int main() {
  //create pthreads
	pthread_t thread_id[NUM_THREADS];

  //create count variable i
  int i;

  //initialize mutex threads
  for(i = 0; i < NUM_THREADS; i++) {
	 pthread_mutex_init(&fork_id[i], NULL);
	}

	//create pthreads
 for(i = 0; i < NUM_THREADS; i++) {
    pthread_create(&thread_id[i], NULL, philosopher, &philosophers[i]);
  }

 for(i = 0; i < NUM_THREADS; i++) {
  pthread_join(thread_id[i], NULL);
 }
  	
  //return 0 convention but not needed here since the program runs in an infinite loop
	return 0;
}

//philosopher method each thread is passed to
void *philosopher(void *philosopher_thread) {
 //variable to allow infinite loop for while loop
 int k = 1;

 //get the philosopher's number (id)
 int id = *(int *)(philosopher_thread);
 while (k) {
    think(id);
    get_forks(id);
    eat(id);
    put_forks(id);
  }
}

/*
This method gets a random number of seconds between 1 and 10 for the philosopher to
think before returning to the while loop and moving to the get_forks method
*/
void think(int this_philosipher){
  //time variable holds the result of the rand() function
  int time = rand() % (max_time - min_time + 1) + min_time;
  
  //output how long the philosopher is thinking for to the console
  printf("\nPhilosopher %d is thinking for %d seconds", this_philosipher, time);
  
  sleep(time);

  return;
}


/*
This method works by waiting for the mutex on the left fork (the fork with the lower id number)
to be unlocked. Once it can get this fork it then waits to pick up the fork on the right side (the fork with the higher id number
except for philosopher 4 who picks up fork 0)

Each time the philosopher picks up a fork they put a mutex lock on the fork to prevent another
philosopher from picking it up

The method then prints out a success method to the console and returns to the while
loop where the eats method is then called
*/
void get_forks(int this_philosipher){
  //wait for the left fork to become available
  //if unavailable print message to the console, sleep for 1 second and try again
  while(pthread_mutex_lock(&fork_id[this_philosipher]) != 0) {
  	printf("\nPhilosopher %d is waiting for forks", this_philosipher);
  	sleep(1);
  }	

  //wait for the right fork to become available
  //if unavailable print message to the console, sleep for 1 second and try again
  if(this_philosipher != 4){
	while(pthread_mutex_lock(&fork_id[this_philosipher + 1]) != 0) {
	  	printf("\nPhilosopher %d is waiting for forks", this_philosipher);
	  	sleep(1);
	}	
  } else {
  	while(pthread_mutex_lock(&fork_id[0]) != 0) {
  		printf("\nPhilosopher %d is waiting for forks", this_philosipher);
  		sleep(1);
  	}	
  }
  
  //print success message to the console and return to philosopher method
  printf("\nPhilosopher %d has its forks", this_philosipher);
  
  return;
}


/*
This method releases the mutex lock on the forks to its left and right and then returns to the main
philosopher method to think
*/
void put_forks(int this_philosipher){
  printf("\nPhilosopher %d is returning forks", this_philosipher);
  pthread_mutex_unlock(&fork_id[this_philosipher]);
  if(this_philosipher != 4){
  	pthread_mutex_unlock(&fork_id[this_philosipher+1]);
  } else {
  	pthread_mutex_unlock(&fork_id[0]);
  }
  return;
}

/*
This method gets a random number of seconds between 1 and 10 for the philosopher to
eat before returning to the while loop and moving to the put_forks method
*/
void eat(int this_philosipher){
  //time variable holds the result of the rand() function
  int time = rand() % (max_time - min_time + 1) + min_time;

  //output how long the philosopher is thinking for to the console
  printf("\nPhilosopher %d is eating for %d seconds!", this_philosipher, time);
 
  sleep(time);

  return;
}
