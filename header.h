/*header.h*/
#ifndef __HEADER_H_
#define __HEADER_H_


typedef unsigned int u32;
typedef 	signed int s32;
typedef unsigned char u8;
typedef 	signed char s8;
typedef unsigned short int u16;
typedef   signed short int s16;


#define SETBIT(x,y) x|=(1<<y)
#define CLRBIT(x,y) x&=~(1<<y)
#define READBIT(x,y) ((x>>y)&1)

#endif

#include <LPC21xx.H>
#include "delay.h"
#include "can_tx_basic.h"




