
#include<pthread.h> 
#include<semaphore.h> 
#include<stdio.h> 
#include<unistd.h>
#include<stdlib.h> 

#define NUM_THREADS 5

//Global variables
//possible states: thinking, waiting to eat (hungry), eating
int state[3]; 
int philosophers[5] = {0, 1, 2, 3, 4};
int forks[5] = {1, 1, 1, 1, 1};

int max_time = 10;
int min_time = 1;

//mutex forx variables
pthread_mutex_t fork_id[NUM_THREADS];

sem_t mutex;
sem_t semaphore[5];

  
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

	  
	  //initialize semaphore
	  //sem_init() returns 0 on success; on error, -1 is returned, and errno is set to indicate the error
	  sem_init(&mutex, 0, 1);

	  //initialize a semaphore for each philosipher
	  for(i = 0; i < NUM_THREADS; i++) {
	    int j = sem_init(&semaphore[i], 0, 0);
	  	if (j != 0) {
	  		printf("\nError initializing semaphores");
	  		return 0;
	  	}
	  }

	  //create pthreads
	  for(i = 0; i < NUM_THREADS; i++) {
	    pthread_create(&thread_id[i], NULL, philosopher, &philosophers[i]);
	  }

	  for(i = 0; i < NUM_THREADS; i++) {
	    pthread_join(thread_id[i], NULL);
	   }
  	
  	//destroy the semaphores
	//sem_destroy(&mutex);
	//sem_destroy(&semaphores);

	return 0;
}

//set state of philosopher 
void *philosopher(void *philosopher_thread) {
 int k = 1;
 int id = *(int *)(philosopher_thread);
 while (k) {
    think(id);
    get_forks(id);
    eat(id);
    put_forks(id);
  }
}
void think(int this_philosipher){
  int time = rand() % (max_time - min_time + 1) + min_time;
  printf("\nPhilosopher %d is thinking for %d seconds", this_philosipher, time);
  sleep(time);
  return;
}
//pick up chopsticks/fork
void get_forks(int this_philosipher){
  while(pthread_mutex_lock(&fork_id[this_philosipher]) != 0) {
  	printf("\nPhilosopher %d is waiting for forks", this_philosipher);
  	sleep(1);
  }	
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
  

  printf("\nPhilosopher %d has its forks", this_philosipher);
  
  return;
}
//put down chopsticks/fork 
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
//set state to eating 
void eat(int this_philosipher){
  int time = rand() % (max_time - min_time + 1) + min_time;
  printf("\nPhilosopher %d is eating for %d seconds!", this_philosipher, time);
  sleep(time);
  return;
}
