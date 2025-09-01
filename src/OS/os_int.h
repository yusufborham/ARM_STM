#ifndef OS_INT_H
#define OS_INT_H

#include "os_prv.h"

#include "../lib/std_types.h"

/*
 * Initializes the OS.
 */
void OS_vinit(void);

/*
 * Starts the OS scheduler.
 */
void OS_vStart(void);

u8 OS_u8SuspendTask(u8 TaskID);
u8 OS_u8ResumeTask(u8 TaskID);
u8 OS_u8DeleteTask(u8 TaskID);
u8 OS_u8CreateTask(u8 TaskID, void(*TaskFunction)(void), u32 Periodicity, u8 Priority);

#endif