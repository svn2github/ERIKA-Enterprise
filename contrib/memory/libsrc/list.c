/** 
* @file list.c
* @brief Generic linked list implementation.
* @author Christian Nastasi
* @date 2009-03-18
*/

#include <list.h>


/******************************************************************************/
/*                        PRIVATE internal FUNCTIONS                          */
/******************************************************************************/
/* TODO: do something better than this! O(n) */
COMPILER_INLINE uint16_t get_free_index(list_t *l)
{
	uint16_t i; 
	/* TODO: won't work when LEN >= 0xFFFE, return 0 with no space! */
	
	for (i = 0; i < l->length; i++) 
		if (l->next[i] == L_FREE)
			break;
	return i;
}


/******************************************************************************/
/*                           COMMON BASIC FUNCTIONS                           */
/******************************************************************************/
void *list_last(list_t *l) 
{
	uint16_t i;

	if (l->head == L_EOL)
		return 0;
	for (i = l->head; l->next[i] != L_EOL; i = l->next[i]) ;
	return (void *) (l->data + (i * l->data_size));
}

void *list_push_front(list_t *l)
{
	uint16_t i;

	if (l->count == l->length) 
		return 0;
	if (l->head == L_EOL) {
		l->head = 0;
		l->next[0] = L_EOL;
		l->count++;
		return (void *) l->data;
	}
	i = get_free_index(l);
	l->next[i] = l->head;
	l->head = i;
	l->count++;
	return (void *) (l->data + (i * l->data_size));
}

void *list_push_back(list_t *l)
{
	uint16_t i;
	
	if (l->count == l->length) 
		return 0;
	if (l->head == L_EOL) {
		l->head = 0;
		l->next[0] = L_EOL;
		l->count++;
		return (void *) l->data;
	}
	for (i = l->head; l->next[i] != L_EOL; i = l->next[i]) ;
	l->next[i] = get_free_index(l);
	i = l->next[i];
	l->next[i] = L_EOL;
	l->count++;
	return (void *) (l->data + (i * l->data_size));
}

void *list_insert(list_t *l, uint16_t p)
{
	uint16_t i;

	if (p == 0)
		return list_push_front(l);
	if (p == l->count)
		return list_push_back(l);
	if (l->count == l->length || p > l->count) 
		return 0;
	for (i = l->head; p-- > 1; i = l->next[i]) ;
	p = get_free_index(l); 	/* p = new, prev(p) = i, next(p) = next(i) */
	l->next[p] = l->next[i];/* p->next(i) */
	l->next[i] = p;		/* i->p */
	l->count++;
	return (void *) (l->data + (p * l->data_size));
}

void *list_at(list_t *l, uint16_t p)
{
	uint16_t i;

	if (l->head == L_EOL || p >= l->count) 
		return 0;
	for (i = l->head; p-- != 0; i = l->next[i]) ;
	return (void *) (l->data + (i * l->data_size));
}

void *list_pop_front(list_t *l)
{
	uint16_t old_head = l->head;

	if (l->count == 0) 
		return 0;
	l->head = l->next[old_head];
	l->next[old_head] = L_FREE;
	return (void *) (l->data + (old_head * l->data_size));
}

void *list_pop_back(list_t *l)
{
	uint16_t i, prev_i;

	if (l->count == 0) 
		return 0;
	prev_i = l->head;
	for (i = l->head; l->next[i] != L_EOL; i = l->next[i]) 
		prev_i = i;
	l->next[i] = L_FREE;
	l->next[prev_i] = L_EOL;
	return (void *) (l->data + (i * l->data_size));
}

void *list_extract(list_t *l, uint16_t p)
{
	/* TODO */
	//l->count--;
	return 0;
}

/******************************************************************************/
/*                             ITERATOR FUNCTIONS                             */
/******************************************************************************/
void *list_iter_at(list_t *l, uint16_t p)
{
	uint16_t i;

	if (l->head == L_EOL || p > l->count) 
		return 0;
	for (i = l->head; p-- != 0; i = l->next[i]) ;
	l->iterator = i;
	return (void *) (l->data + (i * l->data_size));
}

void *list_iter_front(list_t *l)
{
	if (l->head == L_EOL) 
		return 0;
	l->iterator = l->head;
	return (void *) (l->data + (l->iterator * l->data_size));
}

void *list_iter_next(list_t *l)
{
	l->iterator = l->next[l->iterator];
	if (l->iterator == L_EOL)
		return 0;
	return (void *) (l->data + (l->iterator * l->data_size));
}

void *list_iter_current(list_t *l)
{
	if (l->iterator == L_EOL)
		return 0;
	return (void *) (l->data + (l->iterator * l->data_size));
}

void *list_iter_extract(list_t *l)
{
	/* TODO */
	//l->count--;
	return 0;
}



