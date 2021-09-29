/**
 * This is a priority queue implementation
 *
 * This queue uses dynamic memory allocation so it never gets full
 *
 * @author Scott C Johnson (scj@cs.rit.edu)
 *
 **/
#include <stdlib.h>
#include <stdbool.h>

typedef struct queue_struct {
    void **data;
    int capacity; //how many it can hold
    int size; // how many it is currently holding
    int (*cmp)(const void *a, const void *b);
} * QueueADT;


#define _QUEUE_IMPL_
#include "queueADT.h"

#define INCREASE_CAP 5

// will alsways return that b is greater than a
// used in fifo insertion
//
// this was made so I did not have to have special cases in
// the insert for when no cmp was provided.

int fifo_cmp( const void *a, const void *b ) {
	(void)a; //needed to avoid the unused variable warning
	(void)b;
	return 1;
}

QueueADT que_create( int (*cmp)(const void * a, const void * b) ) {
	QueueADT queue = (QueueADT)malloc(sizeof(struct queue_struct));
	queue->data = calloc(INCREASE_CAP, sizeof(void *));
	queue->capacity = INCREASE_CAP;
	queue->size = 0;
	
	if(cmp != 0)
		queue->cmp = cmp;
	else //fifo
		queue->cmp = fifo_cmp;
	
	return queue;
}

void que_destroy( QueueADT queue ) {
	free(queue->data);
	free(queue);
}

void que_clear( QueueADT queue ) {
	while(!que_empty(queue)){
		que_remove(queue);
	}
}

void que_insert( QueueADT queue, void * data ) {
	
	if(queue->size == queue->capacity){ //make the queue bigger if needed
		queue->data = realloc(queue->data, (queue->capacity+INCREASE_CAP) * sizeof(void *));
		queue->capacity += INCREASE_CAP;
	}
	queue->data[queue->size] = data; //insert at the end
	
	//move the item inserted to its proper place
	//start at the end and move it up
	for(int i = queue->size; i > 0; i--){
		//if the new item belongs before the current item
		if(queue->cmp(queue->data[i], queue->data[i-1]) < 0){
			//swap the two items
			void * tmp = queue->data[i];
			queue->data[i] = queue->data[i-1];
			queue->data[i-1] = tmp;
		}
		else //we can stop early
			break;
	}
	queue->size++;
}

void * que_remove( QueueADT queue ) {
	//get the first item
	void * item = queue->data[0];
	
	//move everything else up one spot
	for(int i = 0; i < queue->size-1; i++){
		queue->data[i] = queue->data[i+1];
	}
	queue->size--;
	return item;
}

bool que_empty( QueueADT queue ) {
	if(queue->size == 0)
		return true;
	return false;
}




