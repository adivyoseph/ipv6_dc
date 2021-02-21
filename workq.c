#include "workq.h"


/**
 * 
 * 
 * @author martin (2/21/21) 
 *  
 * @brief called one to initialize work_q FIFO's 
 *  
 * @param p_workq pointer work_q pair 
 * @param name work_q name used for debug 
 * 
 * @return int 0 always, does not have to be checked
 */
int workq_init(work_q_t *p_workq, char *name){

    p_workq->up_q.head = 0;
    p_workq->up_q.tail = 0;
    p_workq->down_q.head = 0;
    p_workq->down_q.tail = 0;
    strcpy(p_workq->name, name);

    return 0;
}


static int q_available_entries(q_t *p_q){
    if (p_q->tail < p_q->head)
		return p_q->head - p_q->tail - 1;
	else
		return p_q->head + (Q_PERQ_MEGS_MAX - p_q->tail);
}

/**
 * 
 * 
 * @author martin (2/21/21) 
 * @brief try to send a message on a work_q 
 * 
 * @param direction 
 * @param p_workq 
 * @param p_mesg 
 * 
 * @return int 1 busy, 0 sent
 */
int workq_send(int direction, work_q_t *p_workq, q_mesg_t *p_mesg){
    q_t *p_q = NULL;
    int rtc = 1;        //fail

    if(directuion == Q_DIRECTION_DOWN){
        p_q = &p_workq->down_q;
    }
    else {
        p_q = &p_workq->up_q;
    }

    if (q_available_entries(p_q) == 0) { //then FIFO is full
        printf("Queue is full\n");
    }
    else {
        p_q->msgs[p_q->tail].size = p_mesg->size;
        memcpy(p_q->msgs[p_q->tail].data, p_mesg->data, p_mesg->size);
        (p_q->tail)++;
        (p_q->tail) %= Q_PERQ_MEGS_MAX;
        p_q->send_cnt++;
        rtc = 0;
    }
    return rtc;
}

/**
 * 
 * 
 * @author martin (2/21/21)
 * 
 * @param direction 
 * @param p_workq 
 * @param p_mesg 
 * 
 * @return int read count, 0 if empty, else 1
 */
int workq_read(int direction, work_q_t *p_workq, q_mesg_t *p_mesg){
    q_t *p_q = NULL;
    q_mesg_t *p_mesg_found = NULL;
    int rtc = 0;        //read count

    if(directuion == Q_DIRECTION_DOWN){
        p_q = &p_workq->down_q;
    }
    else {
        p_q = &p_workq->up_q;
    }

    if (p_q->head != p_q->tail){
        p_mesg_found = p_q->msgs[p_q->head];
        p_mesg->size = p_mesg_found->size;
        memcpy(p_mesg->data, p_mesg_found->data, p_mesg_found->size );
        (p_q->head)++;
        (p_q->head) %= FIFO_DEPTH_MAX;
        p_q->read_cnt++;
        rtc = 1;
    }
    return rtc;
}

