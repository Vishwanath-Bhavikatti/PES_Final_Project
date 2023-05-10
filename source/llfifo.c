/*
*********************************************************************************************************************
​ *
​ ​*​ ​@author​ :​Vishwanath Bhavikatti
​ ​*​ ​@date​ :April 28, 2023
 * @file name : llfifo.c
 * @file_description: I am using this linked list implementation as a buffer for my UART implementation.
 *                    The fuction implements queue operation using linked lists. Enqueue operation enqueues
 *                    data to a predefined list with given capacity. Dequeue function dequeues element
 *                    from the list and the capacity will not change even after dequeue operation.
 *
 * ---------------------------Functions Included in this file---------------------------------------------------------
 * llfifo_t *llfifo_create(int capacity) : Function to create a list
 * int llfifo_enqueue(llfifo_t *list, uint8_t element) : To enqueue an element into the list
 * uint8_t llfifo_dequeue(llfifo_t *list) : To dequeue elements from the list
 * int llfifo_length(lllifo_t *lifo) : Length of the list at any point of operation
 * int llfifo_capacity(lllifo_t *lifo) : Capacity of the list at any point of operation
 * void llfifo_destroy(lllifo_t *lifo) : Destroy the list (Not required for this assignment)
 * @credits: I took this code from my own previous assignment 2.

*************************************************************************************************************************
*/

#include <MKL25Z4.H>
#include "core_cm0plus.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "llfifo.h"

/*
 * Creates and initializes the FIFO
 *
 * Parameters:
 *   capacity  the initial size of the fifo, in number of elements.
 *             Valid values are in the range of 0 to the limits of memory
 *
 * Returns: A pointer to a newly-created llfifo_t instance, or NULL in
 *   case of an error.
 */
llfifo_t *llfifo_create(int capacity)
{
	//check if capacity is zero
    if (capacity == 0)
    {
        return NULL;
    }
    // creating temporary nodes
    node *temp;
    node *newnode;
    // creating a list using malloc operation
    llfifo_t *list = (llfifo_t *)malloc(sizeof(llfifo_t));
    list->head = NULL;
    list->tail = NULL;
    list->capacity = capacity;
    list->length = 0;

    list->head = (node *)malloc(sizeof(node));
    (list->head)->data = 0;
    (list->head)->next = NULL;
    temp = list->head;
    //At the beginning head and write pointer are pointing to the same node
    list->write = list->head;

    // creating nodes till the given capacity
    for (int i = 0; i < capacity - 1; i++)
    {
        newnode = (node *)malloc(sizeof(node));
        if (newnode == NULL)
        {
            printf("Unable to allocate memory!..");
            break;
        }
        newnode->data = 0;
        newnode->next = NULL;

        temp->next = newnode;
        temp = temp->next;

    }

    list->tail = temp;
    //returning the list with nodes created
    return list;
}

/*
 * Enqueues an element onto the FIFO, growing the FIFO by adding
 * additional elements, if necessary
 *
 * Parameters:
 *   fifo    The fifo
 *   element The element to enqueue, which cannot be NULL
 *
 * Returns:
 *   The new length of the FIFO on success, -1 on failure. It is an error to attempt
 * to enqueue the NULL pointer.
 */
int llfifo_enqueue(llfifo_t *list, uint8_t element)
{
// check id capacity is zero
    if (list->capacity == 0)
    {
        printf("List capacity is zero!\n");
        return -1;
    }
    list->length++;
    //if capacity is greater than length silently create a node and increase capacity of list
    if (list->length > list->capacity)
    {

    	list->capacity += 1;
        node *temp = (node *)malloc(sizeof(node));

        temp->data = element;
        temp->next = NULL;

        list->tail->next = temp;
        list->tail = temp;
        list->write = NULL;

    }
// using write pointer enqueue to the node
    else
    {
        (list->write)->data = element;
        list->write = list->write->next;
    }
// return enqueued length
    return list->length;
}

/*
 * Removes ("dequeues") an element from the FIFO, and returns it
 *
 * Parameters:
 *   fifo  The fifo in question
 *
 * Returns:
 *   The dequeued element, or NULL if the FIFO was empty
 */
uint8_t llfifo_dequeue(llfifo_t *list)
{
// variable to store dequeued value
    uint8_t ptr;
    // getting rid of unhappy case
    if (list == NULL)
    {
        return 0;
    }

    if (list->length == 0)
    {
        return 0;
    }

// store the dequeing value
    ptr = list->head->data;
    list->length--;

    // rearranging the nodes
    if (list->capacity > 1)
    {
        list->tail->next = list->head;
        list->tail = list->head;
        list->head = list->head->next;
        list->tail->next = NULL;
    }
    __disable_irq();
    if (list->write == NULL)
    {
        list->write = list->tail;
    }
    __enable_irq();
    //return data
    return ptr;
}

/*
 * Returns the number of elements currently on the FIFO.
 *
 * Parameters:
 *   fifo  The fifo
 *
 * Returns:
 *   The number of elements currently on the FIFO
 */
int llfifo_length(llfifo_t *fifo)
{
    if (fifo == NULL)
    {
        return -1;
    }
    else
    {
    	//returns current length
        return fifo->length;
    }
}

/*
 * Returns the FIFO's current capacity
 *
 * Parameters:
 *   fifo  The fifo
 * Returns:
 *   The current capacity, in number of elements, for the FIFO
 */
int llfifo_capacity(llfifo_t *fifo)
{
    if (fifo == NULL)
    {
        return -1;
    }
    else
    {
    	//returns capacity of the list
        return fifo->capacity;
    }
}
/*
 * Teardown function: Frees all dynamically allocated
 * memory. After calling this function, the fifo should not be used
 * again!
 *
 * Parameters:
 *   fifo  The fifo in question
 *
 * Returns: none
 */
void llfifo_destroy(llfifo_t *fifo)
{
    node *temp;
    node *ptr;
    temp = fifo->head;
    ptr = fifo->head;
    while (ptr != NULL)
    {
        ptr = ptr->next;
        free(temp);
        temp = ptr;
    }
    fifo->capacity = -1;
    fifo->length = -1;
    fifo = NULL;
    return;

}

