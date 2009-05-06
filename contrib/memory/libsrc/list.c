/** 
* @file list.c
* @brief Generic linked list implementation.
* @author Christian Nastasi
* @date 2009-03-18
*/

#include <list.h>


/* TODO: do something better than this! O(n) */
COMPILER_INLINE uint16_t get_free_index(list_t *l)
{
	uint16_t i; 
	/* TODO: won't work when LEN >= 0xFFFE, return 0 with no space! */
	
	for (i = 0; i < l->length; i++) 
		if (l->next[i] == L_FREE)
			break;
	return i + L_IDX_SKIP;
}


void *list_last(list_t *l) 
{
	uint16_t i;

	if (l->head == L_EOL)
		return 0;
	for (i = L_IDX(l->head); l->next[i] != L_EOL; i = L_IDX(l->next[i])) ;
	return (void *) (l->data + (i * l->data_size));
}

void *list_add(list_t *l)
{
	uint16_t i;

	if (l->count == l->length) 
		return 0;
	if (l->head == L_EOL) {
		l->head = L_IDX_SKIP;
		l->next[0] = L_EOL;
		l->count++;
		return (void *) l->data;
	}
	i = get_free_index(l);
	l->next[L_IDX(i)] = l->head;
	l->head = i;
	l->count++;
	return (void *) (l->data + (i * l->data_size));
}

void *list_append(list_t *l)
{
	uint16_t i;
	
	if (l->count == l->length) 
		return 0;
	if (l->head == L_EOL) {
		l->head = L_IDX_SKIP;
		l->next[0] = L_EOL;
		l->count++;
		return (void *) l->data;
	}
	for (i = L_IDX(l->head); l->next[i] != L_EOL; i = L_IDX(l->next[i])) ;
	l->next[i] = get_free_index(l);
	i = L_IDX(l->next[i]);
	l->next[i] = L_EOL;
	l->count++;
	return (void *) (l->data + (i * l->data_size));
}

void *list_insert(list_t *l, uint16_t p)
{
	uint16_t i;

	if (p == 0)
		return list_add(l);
	if (p == l->count)
		return list_append(l);
	if (l->count == l->length || p > l->count) 
		return 0;
	for (i = L_IDX(l->head); p-- > 1; i = L_IDX(l->next[i])) ;
	p = get_free_index(l); /* p = new,   prev(p) = i,   next(p) = next(i) */
	l->next[L_IDX(p)] = l->next[L_IDX(i)];			/* p->next(i) */
	l->next[L_IDX(i)] = p;					/* i->p */
	l->count++;
	return (void *) (l->data + (L_IDX(p) * l->data_size));
}

void *list_at(list_t *l, uint16_t p)
{
	uint16_t i;

	if (l->head == L_EOL || p >= l->count) 
		return 0;
	for (i = L_IDX(l->head); p-- != 0; i = L_IDX(l->next[i])) ;
	return (void *) (l->data + (i * l->data_size));
}

void *list_remove(list_t *l, uint16_t p)
{
	//l->count--;
	return 0;
}

void *list_iterator_at(list_t *l, uint16_t p)
{
	uint16_t i;

	if (l->head == L_EOL || p > l->count) 
		return 0;
	for (i = L_IDX(l->head); p-- != 0; i = L_IDX(l->next[i])) ;
	l->iterator = i;
	return (void *) (l->data + (i * l->data_size));
}

void *list_iterator_head(list_t *l)
{
	if (l->head == L_EOL) 
		return 0;
	l->iterator = l->head;
	return (void *) (l->data + (L_IDX(l->iterator) * l->data_size));
}

void *list_iterate(list_t *l)
{
	l->iterator = l->next[L_IDX(l->iterator)];
	if (l->iterator == L_EOL)
		return 0;
	return (void *) (l->data + (L_IDX(l->iterator) * l->data_size));
}

void *list_iterator_get_current(list_t *l)
{
	if (l->iterator == L_EOL)
		return 0;
	return (void *) (l->data + (L_IDX(l->iterator) * l->data_size));
}

void *list_iterator_remove_current(list_t *l)
{
	//l->count--;
	return 0;
}



