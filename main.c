
#include<pthread.h> 
#include<semaphore.h> 
#include<stdio.h> 

//Global variables
//possible states: thinking, waiting to eat (hungry), eating
int state[3]; 
int philosophers[5] = {0, 1, 2, 3, 4};

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
  pthread_t pid;
  
  //initialize semaphore
  //sem_init() returns 0 on success; on error, -1 is returned, and errno is set to indicate the error
  sem_init(&mutex, 0, 1);
  
return 0;
}

//set state of philosopher 
void philosopher(){
  return;
}
void think(){
  return;
}
//pick up chopsticks/fork
void get_forks(){
  return;
}
//put down chopsticks/fork 
void put_forks(){
  return;
}
//set state to eating 
void eat(){
  return;
}
