/*
*********************************************************************************************************************
​ *
​ ​*​ ​@author​ :​Vishwanath Bhavikatti
​ ​*​ ​@date​ :April 28, 2023
 * @file name : llfifo.h
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

#ifndef _LLFIFO_H_
#define _LLFIFO_H_
#include <stdint.h>


typedef struct llfifo_s llfifo_t;
typedef struct node
{
    uint8_t data;
    struct node *next;
} node;
struct llfifo_s
{
    node *head;
    node *tail;
    node *write;
    int capacity;
    int length;
};
/*
 * The llfifo's main data structure.
 *
 * Defined here as an incomplete type, in order to hide the
 * implementation from the user. need to define this struct
 * in .c file.
 */
typedef struct llfifo_s llfifo_t;


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
llfifo_t *llfifo_create(int capacity);


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
int llfifo_enqueue(llfifo_t *fifo, uint8_t element);


/*
 * Removes ("dequeues") an element from the FIFO, and returns it
 *
 * Parameters:
 *   fifo  The fifo in question
 *
 * Returns:
 *   The dequeued element, or NULL if the FIFO was empty
 */
uint8_t llfifo_dequeue(llfifo_t *fifo);


/*
 * Returns the number of elements currently on the FIFO.
 *
 * Parameters:
 *   fifo  The fifo
 *
 * Returns:
 *   The number of elements currently on the FIFO
 */
int llfifo_length(llfifo_t *fifo);


/*
 * Returns the FIFO's current capacity
 *
 * Parameters:
 *   fifo  The fifo
 * Returns:
 *   The current capacity, in number of elements, for the FIFO
 */
int llfifo_capacity(llfifo_t *fifo);


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
void llfifo_destroy(llfifo_t *fifo);

#endif // _LLFIFO_H_
