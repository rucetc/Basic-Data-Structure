#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "linkqueue.h"

status linkqueue_init(linkqueue *queue)
{
	if(!(queue->front = malloc(sizeof(qnode))))
		return OVERFLOW;

	queue->front->next = NULL;
	queue->rear = queue->front;
	
	return OK;
}

status linkqueue_destory(linkqueue *queue)
{
	if(!linkqueue_clear(queue))
		return ERROR;
	
	free(queue->front);
	queue->front = queue->rear = NULL;

	return OK;
}

status linkqueue_clear(linkqueue *queue)
{
	queue_ptr p, del;

	if(!queue || !queue->front)
		return ERROR;

	for(p = queue->front->next; p; p = p->next, free(del))
		del = p;

	queue->rear = queue->front;

	return OK;
}

status linkqueue_empty(linkqueue queue)
{
	return queue.front == queue.rear;
}

int linkqueue_length(linkqueue queue)
{
	int len;
	queue_ptr p;

	if(!queue.front)
		return -1;

	for(len = 0, p = queue.front; p; ++len, p = p->next)
		;
	
	return len;
}

status linkqueue_get_head(linkqueue queue, void **e)
{
	if(!queue.front || linkqueue_empty(queue))
		return ERROR;

	*e = queue.front->next->data;

	return OK;
}

status linkqueue_enqueue(linkqueue *queue, void *e)
{
	queue_ptr new_node;

	if(!queue->front)
		return ERROR;

	if(!(new_node = malloc(sizeof(qnode))))
		return OVERFLOW;

	new_node->data = e;
	new_node->next = NULL;

	queue->rear->next = new_node;
	queue->rear = new_node;

	return OK;
}

status linkqueue_dequeue(linkqueue *queue, void **e)
{
	queue_ptr del;

	if(!queue->front || linkqueue_empty(*queue))
		return ERROR;

	*e = queue->front->next->data;
	
	del = queue->front->next;
	queue->front->next = del->next;
	free(del);

	return OK;
}

status linkqueue_traverse(linkqueue queue ,void (*visit)(void *))
{
	queue_ptr p;

	if(!queue.front)
		return ERROR;

	for(p = queue.front->next; p; p = p->next)
		visit(p->data);

	printf("\n");

	return OK;
}
