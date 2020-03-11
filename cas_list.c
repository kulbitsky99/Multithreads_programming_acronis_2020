#ifndef __LIST_H
#define __LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdatomic.h>
#include <pthread.h>

struct list_head {
	struct list_head *next;
};

#define LIST_HEAD_INIT(name) { &(name) }

#define LIST_HEAD(name) \
	struct list_head name = LIST_HEAD_INIT(name)

#define INIT_LIST_HEAD(ptr) do { \
	(ptr)->next = (ptr); \
} while (0)

/*
 * Insert a new entry between two known consecutive entries. 
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */

static inline void list_add(	struct list_head *new,
			      				struct list_head *prev,
			      				struct list_head *next)
{
	do
	{
		printf("Printf in do-while\n");
		new->next = next;
	} while (!atomic_compare_exchange_weak(&(prev->next), &next, new));
	printf("Addresses in list_add: %p %p %p\n", next, prev->next, new);
	printf("Addresses in list_add_2: %p %p\n", next->next, (prev->next)->next);
}

/**
 * list_add - add a new entry
 * @new: new entry to be added
 * @head: list head to add it after
 *
 * Insert a new entry after the specified head.
 * This is good for implementing stacks.
 */
static inline void list_add_forward(struct list_head *new, struct list_head *head)
{
	//printf("Addresses in list_add_forward: %p %p %p\n", new, head, head->next);
	list_add(new, head, head->next);
}

/**
 * list_empty - tests whether a list is empty
 * @head: the list to test.
 */
static inline int list_empty(struct list_head *head)
{
	return head->next == head;
}

/**
 * list_entry - get the struct for this entry
 * @ptr:	the &struct list_head pointer.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_struct within the struct.
 */
#define list_entry(ptr, type, member) \
	((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))

/**
 * list_for_each	-	iterate over a list
 * @pos:	the &struct list_head to use as a loop counter.
 * @head:	the head for your list.
 */
#define list_for_each(pos, head) \
	for (pos = (head)->next; pos != (head); \
        	pos = pos->next)
        	
/**
 * list_for_each_entry	-	iterate over list of given type
 * @pos:	the type * to use as a loop counter.
 * @head:	the head for your list.
 * @member:	the name of the list_struct within the struct.
 */
#define list_for_each_entry(pos, head, member)				\
	for (pos = list_entry((head)->next, typeof(*pos), member);	\
	     &pos->member != (head); 					\
	     pos = list_entry(pos->member.next, typeof(*pos), member))

void atomic_ckeck(){
	int obj = 1;
	//int expected = 1;
	int desired = 3;
	int *obj_p = &obj;
	int *expected_p = &obj;
	int *desired_p = &desired;
	printf("obj = %p, expected = %p, desired = %p\n", obj_p, expected_p, desired_p);
	//printf("obj = %d, expected = %d, desired = %d\n", obj, expected, desired);
	_Bool ret_val = atomic_compare_exchange_weak(&obj_p, &expected_p, desired_p);
	if(ret_val)
		printf("OK\n");
	printf("obj = %p, expected = %p, desired = %p\n", obj_p, expected_p, desired_p);	
	//printf("obj = %d, expected = %d, desired = %d\n", obj, expected, desired);
}

typedef struct{
	struct list_head * new;
	struct list_head * prev;
	struct list_head * next;

} Data;

void * pthread_list_add_forward(void* ptr){
	Data *args = (Data*)ptr;
	list_add_forward(args->new, args->prev);
	return NULL;
}

void * pthread_list_add(void* ptr){
	Data *args = (Data*)ptr;
	list_add(args->new, args->prev, args->next);
	return NULL;
}

int main()
{
	struct list_head pos1;
	struct list_head pos2;
	printf("Pos1, pos2: %p %p\n", &pos1, &pos2);
	LIST_HEAD(my_list);
	printf("My_list, my_list.next: %p %p\n", &my_list, my_list.next);
	
	// list_add_forward(&pos1, &my_list);
	// printf("Result list: %p %p %p\n", &my_list, my_list.next, (my_list.next)->next);
	// list_add(&pos2, &my_list, my_list.next);
	// printf("RESULT_LIST: %p %p %p %p\n", &my_list, my_list.next, (my_list.next)->next, ((my_list.next)->next->next));
	/*
	struct list_head * iter = NULL;

	list_for_each(iter, &pos1)
		printf("%p\n", iter);
	*/

	// preparing arguments to be passed
	Data args1 = {
		.new   = &pos1,
		.prev  = &my_list,
		.next  = NULL
	};

	pthread_t thread1, thread2;
	int ret_val = pthread_create(&thread1, NULL, pthread_list_add_forward, (void*)&args1);
	if(ret_val != 0)
	{
		fprintf(stderr,"Error - pthread_create() return code: %d\n", ret_val);
        exit(EXIT_FAILURE);
	}

	// printf("Result list: %p %p %p\n", &my_list, my_list.next, (my_list.next)->next);

	// ?
	/*
	args.new  = &pos2;
	args.prev = &my_list;
	args.next = my_list.next;
	*/

	Data args2 = {
		.new   = &pos2,
		.prev  = &my_list,
		.next  = my_list.next
	};

	ret_val = pthread_create(&thread2, NULL, pthread_list_add, (void*)&args2);
	if(ret_val != 0)
	{
		fprintf(stderr,"Error - pthread_create() return code: %d\n", ret_val);
        exit(EXIT_FAILURE);
	}

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	printf("RESULT_LIST: %p %p %p %p\n", &my_list, my_list.next, (my_list.next)->next, ((my_list.next)->next->next));
	// atomic_ckeck();
	return 0;
}		

#endif