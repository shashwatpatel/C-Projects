/**
 * Implementation of various scheduling algorithms.
 *
 * Priority scheduling
 */
#include <stdlib.h>
#include <stdio.h>
#include "task.h"
#include "list.h"
#include "cpu.h"
#include "schedulers.h"

// reference to the head and tail of the list
struct node *head;

// sequence counter of next available thread identifier
int nextTid = 0;

Task *SortPriority()
{
  struct node *t = head; //A temp pointer to which memory is allocated
  Task *priority = head -> task;
  //Check to see if list is not empty and then compare priority
  while (t != NULL) {
	//Sorting based on priority 10 being the greatest 1 being the least
    if(t -> task -> priority > priority -> priority)
    //Update priority and move on to next
    priority = t -> task;
     t = t -> next; 
  }
  return priority; 
 }

void add(char *name, int priority, int burst) {
	//Code used from FCFS to add a task to the list
    Task *newTask = (Task *) malloc(sizeof(Task));
    newTask->name = name;
    newTask->tid = nextTid++;
    newTask->priority = priority;
    newTask->burst = burst;
    insert(&head, newTask);
}
/**
 * Run the Priority scheduler
 **/
void schedule()
{
	//Code used from FCFS
    Task *current;
    reverse(&head);
	//Sanity check
    traverse(head);
    while (head != NULL) {
        current = SortPriority();
        //Run highest priority first
        run(current, current-> burst);
        delete(&head, current);
    }
}

