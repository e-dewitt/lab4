
#include<pthread.h> 
#include<semaphore.h> 
#include<stdio.h> 
#include<time.h>
#include<stdlib.h> 

#define NUM_THREADS 5

//Global variables
//possible states: thinking, waiting to eat (hungry), eating
int state[3]; 
int philosophers[5] = {0, 1, 2, 3, 4};
int forks[5] = {0, 1, 2, 3, 4};

int max_time = 10;
int min_time = 1;

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
	  
	  //initialize semaphore
	  //sem_init() returns 0 on success; on error, -1 is returned, and errno is set to indicate the error
	  sem_init(&mutex, 0, 1);

	  //initialize a semaphore for each philosipher
	  for(i = 0; i < NUM_THREADS; i++) {
	    int j = 0;//sem_init(&semaphore[i], 0, 0);
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
  return;
}
//pick up chopsticks/fork
void get_forks(int this_philosipher){
  printf("\nPhilosopher %d is getting forks", this_philosipher);
  
  return;
}
//put down chopsticks/fork 
void put_forks(int this_philosipher){
  printf("\nPhilosopher %d is returning forks", this_philosipher);
  return;
}
//set state to eating 
void eat(int this_philosipher){
  int time = rand() % (max_time - min_time + 1) + min_time;
  printf("\nPhilosopher %d is eating for %d seconds!", this_philosipher, time);
  return;
}
