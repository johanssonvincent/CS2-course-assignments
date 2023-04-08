/**
  * Compiles with:
  * gcc -Wall -std=c99 -o test_pqueue list.c pqueue.c test_pqueue.c
  *
  * Just a show of usage of datatype pqueue.
  *
  *
  * @author: Jonny Pettersson
  * @since:  2020-01-21
  */

#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "pqueue.h"

typedef struct {
	int prio;
	char val;
} queue_elem;


/* Function for comparing two prio-elements
 *
 * @param elem1 - the first value
 * @param elem2 - the second value
 *
 * @return > 0   if elem1 > elem2
 *         < 0   if elem1 < elem2
 *          0    if elem1 = elem2
*/
int lessthan(void *elem1, void *elem2)
{
	return ((queue_elem *)elem1)->prio - ((queue_elem *)elem2)->prio;
}

pqueue *create_pq(int choice)
{
	queue_elem *q_elem;
	int numbers[7] = {5,3,9,7,1,0,5};
	char chars[7] = {'a','a','a','a','a','a','b'};
	pqueue *pq;

	pq = pqueue_empty(lessthan);

	for (int i = 0; i < 7; i++){
		q_elem = malloc(sizeof q_elem);
		q_elem->prio = numbers[i];
		q_elem->val = chars[i];
		pqueue_insert(pq, q_elem);
	}

	return pq;
}

/*
 * Prints and empties a priorityqueue (but does not remove the queue)
 */
 void print_and_empty(pqueue *pq)
 {
    queue_elem *q_elem;

	 printf("\nThe elements in the queue:\n");

    while (!pqueue_is_empty(pq)){
        q_elem = (queue_elem *)pqueue_inspect_first(pq);
        pqueue_delete_first(pq);
        printf("(%d, %c) ",q_elem->prio, q_elem->val);
        free(q_elem);
    }
    printf("\n");
}


/*
 * The test creates a priority queue and insert the tuples (5,a)
 * (3,a) (9,a) (7,a) (1,a) (0,a) (5,b) into it, then it empties the
 * queue and writes the tuples to the screeen.
 */
int main()
{
	pqueue *pq;

	printf("\nCreates a priority queue with the elements (5,a) (3,a) ");
	printf("(9,a) (7,a) (1,a) (0,a) (5,b) added.\n");
	printf("\nThe result of printing the queue using ");
	printf("< as priority should be:\n");
	printf("(0, a) (1, a) (3, a) (5, a) (5, b) (7, a) (9, a)\n");

	pq = create_pq(1);

	print_and_empty(pq);
	printf("\n");
	pqueue_kill(pq);

	return 0;
 }
