#ifndef OS_PRV_H
#define OS_PRV_H

#include "os_int.h"
#include "../lib/std_types.h"

typedef enum {
    TASK_DORMET     = 0,
    TASK_READY      = 1,
    TASK_RUNNING    = 2,
    TASK_SUSPENDED  = 3
} TaskState_t;

typedef enum {
    TASK_SUCCESSFULLY_CREATED   = 0 ,
    TASK_EXCEEDED_MAX_NUMBER    = 1 ,
    TASK_ID_REPEATED            = 2 , 
    TASK_PRIORITY_REPEATED      = 3 ,
}CreateTask_error_t;

typedef enum {
    TASK_SUCCESSFULLY_SUSPENDED = 0 ,
    TASK_NOT_RUNNING            = 1 ,
}SuspendTask_error_t;

typedef enum {
    TASK_SUCCESSFULLY_RESUMED = 0 ,
    TASK_NOT_SUSPENDED        = 1 ,
}ResumeTask_error_t;

typedef enum {
    TASK_SUCCESSFULLY_DELETED = 0 ,
}DeleteTask_error_t;

typedef struct {
    u8 TaskID;
    u32 Periodicity;
    u8 Priority;
    u8 State;
    void(*TaskFunction)(void);
    u32 FirstDelay;
} Task_t ;

#define MAX_TASKS 10
#define TICK_TIME 1

#endif
