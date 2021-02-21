#ifndef ___WORK_Q_H___
#define ___WORK_Q_H___

#define Q_MESG_DATA_MAX     256
#define Q_PERQ_MEGS_MAX     4
#define Q_DIRECTION_DOWN    0
#define Q_DIRECTION_UP      1


/**
 * message is content agnostic 
 * payload is copied into message to avoid mallocs 
 * message content is service and work_q dependent 
 */
typedef struct q_mesg_s {
    int size;
    char data[Q_MESG_DATA_MAX];
} q_mesg_t;


/**
 * workQ's contain a queue pair
 */
typedef struct q_s {
    int in;
    int out;
    q_mesg_t msgs[Q_PERQ_MEGS_MAX];
}q_t;

/**
 * 
 */
typedef struct work_q_s {
    q_t up_q;
    q_t down_q;
} work_q_t;


int workq_send_down(work_q_t *p_workq, q_mesg_t *p_mesg) {
    return workq_send(Q_DIRECTION_DOWN, p_workq, p_mesg);
}
int workq_send_up(work_q_t *p_workq, q_mesg_t *p_mesg) {
    return workq_send(Q_DIRECTION_UP, p_workq, p_mesg);
}
int workq_send(int direction, work_q_t *p_workq, q_mesg_t *p_mesg);


int workq_read_down(work_q_t *p_workq, q_mesg_t *p_mesg) {
    return workq_read(Q_DIRECTION_DOWN, p_workq, p_mesg);
}
int workq_read_up(work_q_t *p_workq, q_mesg_t *p_mesg) {
    return workq_read(Q_DIRECTION_UP, p_workq, p_mesg);
}
int workq_read(int direction, work_q_t *p_workq, q_mesg_t *p_mesg);


#endif
