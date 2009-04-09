/** 
* @file cqueue.c
* @brief Generic circular queue implementation.
* @author Christian Nastasi
* @date 2009-03-18
*/

#include <string.h>
#include "cqueue.h"

int8_t cqueue_first(cqueue_t *q, uint8_t *p) 
{
	uint32_t idx;

	if (q->count == 0)
		return -CQUEUE_EMPTY;
	idx = q->front * ((uint32_t) q->data_size);
	memcpy(p, q->data + idx, q->data_size);
	return 1;
}

int8_t cqueue_last(cqueue_t *q, uint8_t *p) 
{
	uint32_t idx;

	if (q->count == 0)
		return -CQUEUE_EMPTY;
	idx = ((q->front + q->count) % q->length) * ((uint32_t) q->data_size);
	memcpy(p, q->data + idx, q->data_size);
	return 1;
}

int8_t cqueue_push(cqueue_t *q, uint8_t *p)
{
	uint32_t idx;

	if (q->count == q->length)
		return -CQUEUE_FULL;
	idx = ((q->front + q->count) % q->length) * ((uint32_t) q->data_size);
	memcpy(q->data + idx, p, q->data_size);
	q->count += 1;
	return 1;
}

int8_t cqueue_pop(cqueue_t *q, uint8_t *p)
{
	uint32_t idx;

	if (q->count == 0)
		return -CQUEUE_EMPTY;
	idx = q->front * ((uint32_t) q->data_size);
	memcpy(p, q->data + idx, q->data_size);
	q->front = (q->front + 1) % q->length;
	q->count -= 1;
	return 1;
}

