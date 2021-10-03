/* 
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/

queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    if(q != NULL) {
        q->head = NULL;
        q->tail = NULL;
        q->size = 0;
    }
    return q;
}

/* Free all storage used by queue */

void q_free(queue_t *q)
{
    if(q == NULL) return;

    list_ele_t *cur_head = q->head;
    
    while(cur_head != NULL) {
        list_ele_t *temp = cur_head;
        cur_head = cur_head->next;
        free(temp);
    }

    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
bool q_insert_head(queue_t *q, int v)
{
    if(q == NULL) return false;

    list_ele_t *insert_space = malloc(sizeof(list_ele_t));
    
    if(insert_space == NULL) return false;

    insert_space->value = v;
    insert_space->next = q->head;
    q->head = insert_space;
    q->size += 1;
    if(q->size == 1) {
        q->tail = q->head;
    }
    return true;
}

/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
bool q_insert_tail(queue_t *q, int v)
{
    if(q == NULL) return false;

    list_ele_t *insert_space = malloc(sizeof(list_ele_t));

    if(insert_space == NULL) return false;

    insert_space->value = v;
    insert_space->next = NULL;

    if(q->tail != NULL) {
        q->tail->next = insert_space;
        q->tail = insert_space;
        q->size += 1;
    }

    else {
        q->head = insert_space;
        q->tail = insert_space;
        q->size += 1;
    }

    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If vp non-NULL and element removed, store removed value at *vp.
  Any unused storage should be freed
*/

bool q_remove_head(queue_t *q, int *vp)
{
    if(q == NULL || q->head == NULL) return false;
    
    if(vp != NULL) {
        *vp = q->head->value; 
    }
    
    list_ele_t *temp = q->head;
    q->head = q->head->next;
    free(temp);
    q->size -= 1;
    if(q->size == 0) {
        q->tail = NULL;
    }

    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */

int q_size(queue_t *q)
{
    if(q == NULL || q->head == NULL) return 0;

    return q->size;
}

/*
  Reverse elements in queue.
  Your implementation must not allocate or free any elements (e.g., by
  calling q_insert_head or q_remove_head).  Instead, it should modify
  the pointers in the existing data structure.
 */
void q_reverse(queue_t *q)
{
    if(q == NULL || q->size < 2) return;

    list_ele_t *prev_node = NULL;
    list_ele_t *cur_node = q->head;
    list_ele_t *next_node = cur_node->next;

    while(next_node != NULL) {
        cur_node->next = prev_node;
        prev_node = cur_node;
        cur_node = next_node;
        next_node = next_node->next;
    }
    cur_node->next = prev_node;
    
    q->tail = q->head;
    q->head = cur_node;
}