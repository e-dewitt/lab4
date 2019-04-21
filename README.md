#Authors
Ellen DeWitt
Aisha Iftikhar

#Course Information
CSE 2431
Spring 2019
Instructor:
Grader:

#Assignment Information
Lab 4

#Files Included
README.md (this file)
main.c

#main.c
	Methods:
		We wrote our code in C to allow access to the pthread library in C to implement our 5 philosophers and 5 threads in a thread array.

		To control access to the shared resource (forks) we chose to implement mutex locks on each of the forks when a philosopher is eating.

		To prevent deadlock each philosopher follows the same protocol, which is to always pick up the fork on their left first. This is the lower number fork so philosopher 0 would pick up fork 0 first and philosopher 1 would pick up fork 1 first and so on. This way even if philosopher's 0, 1, 2, and 3 have forks philosopher 4 will not be able to pick up fork 4 as it is waiting for fork 0 and will not cause deadlock.

		In order to prevent starvation each philosopher will eat and think for a random number of seconds between 1-10. This way no philosopher is thinking indefinitely and all philosophers have to stop eating and return their forks to go think. This allows the waiting philosophers to pick up forks.

	Output:
		Each time that a philosopher thread performs a new action (think, eat, get forks, put forks, wait for forks) a message will be output to the console with the thread number and the actions. For example when philosopher thread 3 enters the eats method the following will be output to the console:
			Philosopher 3 is eating for <number of seconds> seconds
	

#Compilation Instructions
	1) gcc -o main main.c -lpthread
	2) ./main
	Note: This program will continue forever so use the CTR C command or equivalent to exit the program.

