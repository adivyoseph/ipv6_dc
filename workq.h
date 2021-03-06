#ifndef ___WORK_Q_H___
#define ___WORK_Q_H___

#include <stdint.h>
#include <pthread.h>

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
    pthread_mutex_t *mutex;
    int head;
    int tail;
    q_mesg_t msgs[Q_PERQ_MEGS_MAX];
    int send_cnt;
    int read_cnt;
}q_t;

/**
 * work_q links services 
 * services have one input work_q and one or many output 
 * work_q's 
 */
typedef struct work_q_s {
    q_t up_q;
    q_t down_q;
    char *cp_name;
} work_q_t;

extern int workq_init(work_q_t *p_workq);

extern int workq_send_down(work_q_t *p_workq, q_mesg_t *p_mesg) ;
extern int workq_send_up(work_q_t *p_workq, q_mesg_t *p_mesg);


extern int workq_read_down(work_q_t *p_workq, q_mesg_t *p_mesg);
extern int workq_read_up(work_q_t *p_workq, q_mesg_t *p_mesg);


#endif
