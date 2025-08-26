#include "os_prv.h"
#include "os_int.h"
#include "../MCAL/SYSTICK/SYSTICK_int.h"
#include "../MCAL/SYSTICK/SYSTICK_PRV.h"


static Task_t S_aTaskList[MAX_TASKS] = {{0}};
static u32 S_aTaskRemainingTicks[MAX_TASKS] = {0};

void OS_u8TaskScheduler(void);

void OS_vinit(void){
    MSYSTICK_vChooseClockSource(SYSTICK_CLK_SOURCE_AHB_DIV_8);

}
void OS_vStart(void){
    MSYSTICK_vSetIntervalMulti( TICK_TIME , OS_u8TaskScheduler );
}
u8 OS_u8SuspendTask(u8 TaskPriority){
    if(TaskPriority < MAX_TASKS){
        if(S_aTaskList[TaskPriority].State == TASK_RUNNING){
            S_aTaskList[TaskPriority].State = TASK_SUSPENDED;
            return TASK_SUCCESSFULLY_SUSPENDED;
        }
        else {
            return TASK_NOT_RUNNING;
        }
    }
    else {
        return TASK_EXCEEDED_MAX_NUMBER;
    }
}
u8 OS_u8ResumeTask(u8 TaskID){
    if(TaskID < MAX_TASKS){
        if(S_aTaskList[TaskID].State == TASK_SUSPENDED){
            S_aTaskList[TaskID].State = TASK_RUNNING;
            return TASK_SUCCESSFULLY_RESUMED;
        }
        else {
            return TASK_NOT_SUSPENDED;
        }
    }
    else {
        return TASK_EXCEEDED_MAX_NUMBER;
    }
}
u8 OS_u8DeleteTask(u8 TaskID){
    if(TaskID < MAX_TASKS){
        if(S_aTaskList[TaskID].State != TASK_DORMET){
            S_aTaskList[TaskID].State = TASK_DORMET;
            return TASK_SUCCESSFULLY_DELETED;
        }
        else {
            return TASK_NOT_RUNNING;
        }
    }
    else {
        return TASK_EXCEEDED_MAX_NUMBER;
    }
}

// did not add yet the logic for the repeated IDs 
u8 OS_u8CreateTask(u8 TaskID, void(*TaskFunction)(void), u32 Periodicity, u8 Priority){
    if(Priority < MAX_TASKS ){
        if (S_aTaskList[Priority].State == TASK_DORMET){
            S_aTaskList[Priority].TaskID = TaskID ;
            S_aTaskList[Priority].TaskFunction = TaskFunction;
            S_aTaskList[Priority].Periodicity = Periodicity;
            S_aTaskList[Priority].Priority = Priority;
            S_aTaskList[Priority].State = TASK_RUNNING;
            return TASK_SUCCESSFULLY_CREATED ; // Success
        }
        else {
            return TASK_PRIORITY_REPEATED ;
        }
    }
    else {
        return TASK_EXCEEDED_MAX_NUMBER ;
    }
} 

void OS_u8TaskScheduler(void){
    for (u8 taskPriority = 0 ; taskPriority < MAX_TASKS ; taskPriority++ ){
        if (S_aTaskList[taskPriority].State == TASK_RUNNING)
            if (S_aTaskRemainingTicks[taskPriority] == 0 || S_aTaskRemainingTicks[taskPriority] > S_aTaskList[taskPriority].Periodicity ){
                S_aTaskList[taskPriority].TaskFunction() ;   
                S_aTaskRemainingTicks[taskPriority] = S_aTaskList[taskPriority].Periodicity ;   
            }

            else {
                S_aTaskRemainingTicks[taskPriority]-- ;
            }
        else {
            // do nothing 
        }
    }
}