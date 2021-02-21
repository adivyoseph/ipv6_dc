#include "workq.h"



int workq_init(work_q_t *p_workq){

    p_workq->up_q.head = 0;
    p_workq->up_q.tail = 0;
    p_workq->down_q.head = 0;
    p_workq->down_q.tail = 0;


    return 0;
}
