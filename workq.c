#include "workq.h"


/**
 * 
 * 
 * @author martin (2/21/21) 
 *  
 * @brief called one to initialize work_q FIFO's 
 * 
 * @param p_workq pointer work_q pair
 * 
 * @return int 0 always, does not have to be checked
 */
int workq_init(work_q_t *p_workq){

    p_workq->up_q.head = 0;
    p_workq->up_q.tail = 0;
    p_workq->down_q.head = 0;
    p_workq->down_q.tail = 0;


    return 0;
}









int workq_write(t_fifo *p_q, void* item){
    if (fifo_available(p_q) == 0) // when queue is full
    {
        printf("Queue is full\n");
        return 1;
    }
    else
    {
        //printf("write item %p  \n", item);
        p_q->data[p_q->tail]=item;
        //printf("write item %p  \n",p_q->data[p_q->tail]);
        (p_q->tail)++;
        (p_q->tail) %= FIFO_DEPTH_MAX;
    }
    return 0;

}

void * fifo_read(t_fifo *p_q){
    void* item;
    if (p_q->head == p_q->tail){
        return 0;
    }
    else
    {
        item = p_q->data[p_q->head];
        //printf("read item %p  \n", item);
        (p_q->head)++;
        (p_q->head) %= FIFO_DEPTH_MAX;
    }
    return item;

}
