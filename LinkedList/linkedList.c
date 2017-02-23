#include <stdlib.h>
#include "linkedList.h"

t_listnode *list_createnode(t_value value)
{
	t_listnode *p;
	p = malloc(sizeof(*p));
	if (p != NULL) {
		p->value = value;
		p->next = NULL;
	}
	return p;
}

t_listnode *list_addfront(t_listnode *list, t_value value)
{
	t_listnode *newnode = list_createnode(value);
	if (newnode != NULL) {
		newnode->next = list;
		return newnode;
	}
	return list;
}

t_listnode *list_lookup(t_listnode *list, t_value value)
{
	for (; list != NULL; list = list->next) {
		if (list->value == value) {
			return list;
		}
	}
	return NULL;
}

int list_size(t_listnode *list)
{
	int size = 0;
	for (; list != NULL; list = list->next)
		size++;
	return size;
}

t_listnode *list_delete(t_listnode *list, t_value value)
{
	t_listnode *p, *prev = NULL;
	for (p = list; p != NULL; p = p->next) {
		if (p->value == value) {
			if (prev == NULL) {
				list = p->next;
			} else {
				prev->next = p->next;
			}
			free(p);
			return list;
		}
		prev = p;
	}
	return NULL;
}
