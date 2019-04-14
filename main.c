
#include<pthread.h> 
#include<semaphore.h> 
#include<stdio.h> 

#define NUM_THREADS 5

//Global variables
//possible states: thinking, waiting to eat (hungry), eating
int state[3]; 
int philosophers[5] = {0, 1, 2, 3, 4};
int forks[5] = {0, 1, 2, 3, 4};


sem_t mutex;
sem_t semaphore;
  
//Function Prototypes
void philosopher();
void think();
void get_forks();
void put_forks();
void eat();

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
    sem_init(&semaphore[i], 0, 0);
  }

  //create pthreads
  for(i = 0; i < NUM_THREADS; i++) {
    pthread_create(&thread_id[i], NULL, philosopher, &philosophers[i])
  }
  
return 0;
}

//set state of philosopher 
void philosopher(){
 while (true) {
    think();
    get_forks();
    eat();
    put_forks();
  }
}
void think(int this_philosipher){
  printf("\nPhilosopher %d is thinking", this_philosipher);
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
  printf("\nPhilosopher %d is eating!", this_philosipher);
  return;
}
