#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "bitree.h"
#include "generic_type.h"


static void *terminator;

void get_terminator(int size)
{
	void (*get_elem)(void *) = TYPE_FUNC(get_stdin_elem);

	if(!(terminator = malloc(size)))
		exit(ENOMEM);

	printf("Please insert the terminator of the tree:\n");
	get_elem(terminator);
}

status bitree_get_data(void *ptr)
{
	TYPE_FUNC(get_stdin_elem)(ptr);
	
	return !TYPE_FUNC(equal)(ptr, terminator);
}

int main(int argc, char *argv[])
{
	int elem_size = TYPE_SIZE;
	void (*show_elem)(void *) = TYPE_FUNC(show_elem);

	bitree root, backup;

	printf("[bitree - Test 15] Bitree Copy:\n") ;

	get_terminator(elem_size);

	bitree_init(&root);
	bitree_levelorder_create(&root, elem_size, bitree_get_data);

	printf("The binary tree is:\n");
	bitree_to_glist(root, show_elem);
	printf("\n");

	bitree_copy(&backup, &root, elem_size);

	printf("The backup is:\n");
	bitree_to_glist(backup, show_elem);
	printf("\n");

	bitree_destroy(&root);
	bitree_destroy(&backup);

	return EXIT_SUCCESS;
}
