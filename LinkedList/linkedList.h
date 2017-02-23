#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>
#include <stddef.h>

typedef int t_value;

typedef struct s_listnode {
	t_value value; // Data
	struct s_listnode *next;
} t_listnode;

t_listnode *list_createnode(t_value value);

t_listnode *list_addfront(t_listnode *list, t_value value);

t_listnode *list_lookup(t_listnode *list, t_value value);

int list_size(t_listnode *list);

t_listnode *list_delete(t_listnode *list, t_value value);

#endif /* !LINKED_LIST_H */