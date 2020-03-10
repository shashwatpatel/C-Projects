/**
 * Implementation of various scheduling algorithms.
 *
 * SJF scheduling
 **/

#include <stdlib.h>
#include <stdio.h>
#include "task.h"
#include "list.h"
#include "cpu.h"

// reference to the head of the list
struct node *head = NULL;
// sequence counter of next available thread identifier
int nextTid = 0;

Task *pickShortest();
// add a new task to the list of tasks
void add(char *name, int priority, int burst) {
    // first create the new task
    Task *newTask = (Task *) malloc(sizeof(Task));

    newTask->name = name;
    newTask->tid = nextTid++;
    newTask->priority = priority;
    newTask->burst = burst;

    // insert the new task into the list of tasks
    insert(&head, newTask);
}

/**
 * Run the SJF scheduler
 **/

void schedule()
{
    Task *current;
    reverse(&head);
	//Sanity check
    traverse(head);
    while (head != NULL) {
        current = pickShortest();
        //Run the shortest job first
        run(current, current-> burst);
        delete(&head, current);
    }
}

/**
 * Returns the next task selected to run.
 **/
Task *pickShortest()
{
  struct node *t = head; //A temp pointer to which memory is allocated
  Task *shortest = head -> task;
  //Check to see if list is not empty and then compare priority
  while (t != NULL) {
	  //Compare processes based on burst priority
    if(t -> task -> burst < shortest -> burst)
    //Update priority
    shortest = t -> task;
     t = t -> next; 
  }
  return shortest; 
 }
