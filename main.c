#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>


#include "workq.h"
#include "process.h"

extern void th_netController(void *vp_data);
extern void th_switchPort(void *vp_data);

work_q_t workQs[8] =
    {
        { //0
            .cp_name = "switch2Controller",
        },
    };

process_t procs[8] = {
    {
        .cp_name = "network controller",
        .p_inputQ = &workQs[0],
        .outputQCnt = 1,
        .p_outputQs[0] = &workQs[0],
        .p_func = th_netController,
    },
    {
        .cp_name = "switch_port_0_up",
        .p_inputQ = &workQs[0],
        .outputQCnt = 1,
        .p_outputQs[0] = NULL,
        .p_func = th_switchPort,
    },
    {
        .cp_name = "switch_port_0_down",
        .p_inputQ = NULL,
        .outputQCnt = 1,
        .p_outputQs[0] = &workQs[0],
        .p_func = th_switchPort,
    },

    };


int main(void){

    int i;

    for (i = 0; i < 8; i++) {
        workq_init(&workQs[i]);
    }


    return 0;
}
