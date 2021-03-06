#ifndef ___PROCESS_H___
#define ___PROCESS_H___
#define P_OUTPUT_Q_MAX 8

typedef struct process_s {
    char *cp_name;
    work_q_t  *p_inputQ;
    int  outputQCnt;
    work_q_t  *p_outputQs[P_OUTPUT_Q_MAX];
    pthread_t thread_id; 
    void (*p_func)(void *vp_data);



} process_t;



#endif
