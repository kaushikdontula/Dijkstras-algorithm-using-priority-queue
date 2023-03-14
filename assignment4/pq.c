/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name: Kaushik Dontula
 * Email: dontulak@oregonstate.edu
 */

#include <stdlib.h>

#include "pq.h" 
#include "dynarray.h"

/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 */

struct pq_data{
	int priority;
	void* data;
	
};

struct pq{
	struct dynarray* heap_array;
	int size;
};


/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create() {
	
	//creating priority queue on heap
	struct pq* temp = malloc(sizeof(struct pq));
	temp->size = 0;

	//creating dynarray within our struct pq
	temp->heap_array = dynarray_create();
	return temp;
}


/*
 * This function should free the memory allocated to a given priority queue.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the priority queue.  That is the responsibility of the caller.
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 */
void pq_free(struct pq* pq) {

	dynarray_free(pq->heap_array);
	free(pq);

	return;
}


/*
 * This function should return 1 if the specified priority queue is empty and
 * 0 otherwise.
 *
 * Params:
 *   pq - the priority queue whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if pq is empty and 0 otherwise.
 */
int pq_isempty(struct pq* pq) {
	
	//if the size returns 0 return the queue is empty
	if(dynarray_size(pq->heap_array) == 0){
		return 1;
	}
	else{
		return 0;
	}
}


/*
 * This function should insert a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, LOWER priority
 * values are assigned to elements with HIGHER priority.  In other words, the
 * element in the priority queue with the LOWEST priority value should be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   value - the value to be inserted into pq.
 *   priority - the priority value to be assigned to the newly-inserted
 *     element.  Note that in this implementation, LOWER priority values
 *     should correspond to elements with HIGHER priority.  In other words,
 *     the element in the priority queue with the LOWEST priority value should
 *     be the FIRST one returned.
 */

 //percolates up
void pq_insert(struct pq* pq, void* value, int priority) {

	//create and initialize new priority queue data element
	struct pq_data* temp = malloc(sizeof(struct pq_data));
	temp->data = value;
	temp->priority = priority;


	//insert the value of that element into the array and increase size of pq
	dynarray_insert(pq->heap_array, temp);
	pq->size++;

	//initialize current index to array size and parent index to 0
 	int curr_index = dynarray_size(pq->heap_array) - 1;
    int parent_index = 0;

	//create temp data struct
	struct pq_data* temp_1 = NULL;

	//while true
	while(1){

		//calculate the inserted elements parent index using the formula
		parent_index = (curr_index - 1) / 2;
		temp_1 = (struct pq_data*) dynarray_get(pq->heap_array, parent_index);
		
		//compare the priority of the inserted element to the priority of its parent. If priority of parent is greater than the priority of inserted element then swap 
		if(temp_1->priority > temp->priority){
			dynarray_set(pq->heap_array, parent_index, temp);
			dynarray_set(pq->heap_array, curr_index, temp_1);
			curr_index = parent_index;
		}
		//element has reached beginning of array OR parent priority is less than inserted element priority
		else{
			break;
		}
	}

	return;
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_first(struct pq* pq) {
	struct pq_data* temp = dynarray_get(pq->heap_array, 0);

	if(temp != NULL){
		return temp->data;
	}
	else{
		return NULL;
	}

}


/*
 * This function should return the priority value of the first item in a
 * priority queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   Should return the priority value of the first item in pq, i.e. the item
 *   with LOWEST priority value.
 */
int pq_first_priority(struct pq* pq) {
	struct pq_data* temp = dynarray_get(pq->heap_array, 0);

	if(temp != NULL){
		return temp->priority;
	}
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value, and then remove that item
 * from the queue.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */

 //percolates down
void* pq_remove_first(struct pq* pq) {

	//if the priority queue is empty 
	if (pq_isempty(pq)) {
    	return NULL;
  	}
	
	// Get the root element AKA the element with lowest priority
	struct pq_data* root = dynarray_get(pq->heap_array, 0);
	void* root_data = root->data;

	// replace the first element in the array with the last element and remove last element
	struct pq_data* last_element = dynarray_get(pq->heap_array,dynarray_size(pq->heap_array) - 1);
	dynarray_set(pq->heap_array, 0, last_element);
	dynarray_remove(pq->heap_array,dynarray_size(pq->heap_array) - 1);
	last_element = NULL;
	pq->size--;

	free(root);
	//free(last_element);

	//this is the root index
	int curr_index = 0;

	//calculate the left and right child using binary tree node formula
	int left_child_index = curr_index * 2 + 1;
	int right_child_index = curr_index * 2 + 2;

	//while the left node is within the size of our heap array
	while (left_child_index < dynarray_size(pq->heap_array)) {
		// Find the child with the lowest priority
		int lowest_child_index = curr_index;

		//get the current child and the left of the root
		struct pq_data* curr = (struct pq_data*) dynarray_get(pq->heap_array, curr_index);
		struct pq_data* left_child = (struct pq_data*) dynarray_get(pq->heap_array, left_child_index);

		//checks which child has the lowest priority
		if (left_child->priority < curr->priority) {
			lowest_child_index = left_child_index;
		}
		//check if the right child is in the heap array bounds
		if (right_child_index < dynarray_size(pq->heap_array)) {
			//get the right child
			struct pq_data* right_child = (struct pq_data*) dynarray_get(pq->heap_array, right_child_index);

			//if priority of right child is less than lowest priority node then update the index of lowest priorirty to be right child index
			if (right_child->priority < ((struct pq_data*)dynarray_get(pq->heap_array, lowest_child_index))->priority) {
				lowest_child_index = right_child_index;
			}
		}
		

		// If the current node has lower priority than its lowest-priority child, swap them
		if (curr->priority > ((struct pq_data*)dynarray_get(pq->heap_array, lowest_child_index))->priority) {
			dynarray_set(pq->heap_array, curr_index, dynarray_get(pq->heap_array, lowest_child_index));
			dynarray_set(pq->heap_array, lowest_child_index, curr);
			curr_index = lowest_child_index;
			left_child_index = curr_index * 2 + 1;
			right_child_index = curr_index * 2 + 2;
		} else {
			break;
		}
	}

	return root_data;
}
