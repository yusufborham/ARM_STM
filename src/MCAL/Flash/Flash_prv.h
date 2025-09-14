/*
 * FMI_prv.h
 *
 *  Created on : Sep 10, 2025
 *      Author : Nada Mamdouh
 *      Version: 0.0
 */

#ifndef SRC_MCAL_FMI_FMI_PRV_H_
#define SRC_MCAL_FMI_FMI_PRV_H_

#include "Flash_int.h"

#define FMI_BASE_ADDR	0x40023C00U

typedef struct
{
	u32 ACR;
	u32 KEYR;
	u32 OPTKEYR;
	u32 SR;
	u32 CR;
	u32 OPTCR;
}FMI_MemMap_t;

#define FMI		((volatile FMI_MemMap_t*)(FMI_BASE_ADDR))

#define KEY1	0x45670123
#define KEY2	0xCDEF89AB

/* REGISTERS */
#define BSY		16
#define LOCK	31
#define MER		2
#define STRT	16
#define SNB		3
#define SER		1
#define PSIZE	8
#define PG		0


#endif /* SRC_MCAL_FMI_FMI_PRV_H_ */