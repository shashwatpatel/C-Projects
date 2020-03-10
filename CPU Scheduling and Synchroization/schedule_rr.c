/**
 * Implementation of various scheduling algorithms.
 *
 * RR scheduling
 **/
#include <stdlib.h>
#include <stdio.h>
#include "task.h"
#include "list.h"
#include "cpu.h"
#include "schedulers.h"

// reference to the head of the list
struct node *head = NULL;
// sequence counter of next available thread identifier
int nextTid = 0;

//Task *RoundRobin();
// add a new task to the list of tasks
void add(char *name, int priority, int burst) {
    // first create the new task
    Task *newTask = (Task *) malloc(sizeof(Task));
    newTask->name = name;
    newTask->tid = nextTid++;
    newTask->priority = priority;
    newTask->burst = burst;
    insert(&head, newTask); //Insert task in the list      
}

/**
 * Run the RR scheduler
 **/
 /**
 * Courtesy of: https://www.tutorialspoint.com/c-program-for-round-robin-scheduling
 **/
void schedule()
{
	reverse(&head);
	//Sanity check
    traverse(head);
   struct node *t = head;
   //If given tasks are more than 0 
   //Loop through each process
   while(1) {
	   Task *numTasks = t -> task;
	   //If burst time is greater than quantum time decrease burst time by quantum
	   if (numTasks -> burst > QUANTUM) {
		   run(numTasks, QUANTUM);
		   numTasks -> burst -= QUANTUM;
		   t = t -> next;
		   //If the temp pointer is not 0 then update numTasks or if its 0 then update head
		   if (t != NULL) { numTasks = t -> task; }
		   else { t = head; }
		   if (t != NULL) { numTasks = t -> task; }
		   else { return; }   
	   }
	   else {
		   //If burst time is smaller then calculate the process time 
		   int time = numTasks -> burst;
			run(numTasks, time);
			numTasks -> burst -= time;
			t = t -> next;
			delete(&head, numTasks);
			//If the temp pointer is not 0 then update numTasks or if its 0 then update head
			if (t != NULL) { numTasks = t->task; }
			else { t = head; }
			if (t != NULL) { numTasks = t -> task; }
			else { return; }
		}
	}
}
