/*
 * DIO.h
 *
 * Created: 9/13/2019 10:49:22 AM
 *  Author: Peter
 */ 


#ifndef DIO_H_
#define DIO_H_

#include "REG_Lib.h"

#include "DIO_cnfg.h"

typedef enum{NOK,OK}Std_Func_t;

#define MAX_NUM_OF_PINS		(uint8)32



Std_Func_t DIO_init (void);

Std_Func_t DIO_write (uint8 port,uint8 pin,uint8 val);

Std_Func_t DIO_read (uint8 port,uint8 pin,uint8 * Pval);

#endif /* DIO_H_ */
