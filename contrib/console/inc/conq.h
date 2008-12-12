#ifndef _CONQ_H_
#define _CONQ_H_

#ifndef CONQ_DIMENSION
#define CONQ_DIMENSION		16
#endif

typedef struct {
	char			storage[CONQ_DIMENSION+1];	// Queue Itself
	int				nFirstElement;				// The position of the first element
	int				nLastElement;				// The position of the last element
	unsigned int	nElementNumber;				// Number of the elements inside the queue
} conq_t;

void	conq_init		(conq_t *q);			// Queue Initialization
void	conq_flush		(conq_t *q);			// Clean Queue Initialization
char	conq_insert		(conq_t *q, char x);	// Allow enqueuing op
char	conq_extract	(conq_t *q);			// Allow dequeuing op
int		conq_isempty	(conq_t *q);			// Retur TRUE if the Queue is empty, FALSE otherwise
//void	conq_print		(conq_t *q);			// Print the entire Queue Content

#endif

