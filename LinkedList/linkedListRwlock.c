#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

//#define __USE_XOPEN2K //for rwlock

pthread_rwlock_t llist_rwlock = PTHREAD_RWLOCK_INITIALIZER;

void *writer_thread(void *arg)
{
	int i;
	t_listnode *head = (t_listnode *)arg;
	for (i = 0; i < 10; ++i) {
		pthread_rwlock_wrlock(&llist_rwlock);
		head = list_addfront(head, i);
		pthread_rwlock_unlock(&llist_rwlock);
	}
	return NULL;
}

void *reader_thread(void *arg)
{
	int i;
	t_listnode *head = (t_listnode *)arg;
	for (i = 0; i < 10; ++i) {
		pthread_rwlock_rdlock(&llist_rwlock);
		int size = list_size(head);
		printf("size = %d\n", size);
		pthread_rwlock_unlock(&llist_rwlock);
	}
	return NULL;
}

int main()
{
	t_listnode *head = NULL; // Внимание: head – объект в стеке, указатель на него передан в потоки
	int nwriters = 2, i;
	pthread_t *writers = malloc(sizeof(*writers) * nwriters);
	for (i = 0; i < nwriters; ++i) {
		if (pthread_create(&writers[i], NULL, writer_thread, &head) != 0) {
			fprintf(stderr, "Can't create thread\n");
			exit(EXIT_FAILURE);
		}
	}
	int nreaders = 4;
	pthread_t *readers = malloc(sizeof(*readers) * nreaders);
	for (i = 0; i < nreaders; ++i) {
		if (pthread_create(&readers[i], NULL, reader_thread, &head) != 0) {
		fprintf(stderr, "Can't create thread\n");
		exit(EXIT_FAILURE);
		}
	}
	for (i = 0; i < nwriters; ++i) 
		pthread_join(writers[i], NULL);
	for (i = 0; i < nreaders; ++i) 
		pthread_join(readers[i], NULL);
	free(readers); 
	free(writers);
	return 0;
}