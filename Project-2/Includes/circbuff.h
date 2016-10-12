#ifndef CIRC
#define CIRC

/*This structure contains the variables for the buffer*/
typedef struct {
	uint8_t* buffer;		//pointer to the circular buffer
	uint8_t* head;			//pointer to the head of the buffer
	uint8_t* tail;			//pointer to the tail of the buffer
	uint32_t length;		//Total length of the buffer
	uint32_t num_items;		//number of items present in the buffer
}CircBuff_t;


/*Enumeration for the state of the buffer*/
typedef enum {
	FULL,
	EMPTY,
	SUCCESS,
	FAIL
}state;


/*Prototypes of the functions*/
uint8_t IfFull(CircBuff_t *cb);
uint8_t IfEmpty(CircBuff_t *cb);
state add_item(CircBuff_t *cb, uint8_t item);
state remove_item(CircBuff_t *cb, volatile uint8_t *dest);
void init_buff(CircBuff_t *buff, uint32_t length);
void empty_buff(CircBuff_t *buff);
void fill_buff(CircBuff_t *buff);

#endif
