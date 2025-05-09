#ifndef _JUDGE_H
#define _JUDGE_H
//*******************************// include _h files
#include "main.h"
#include <math.h>
#include "TJC_Usart.h"
//*******************************// define statement
#define 	CASE_TYPE		15
#define 	CASE_CHANNEL	3
//*******************************// define structure unity
//*******************************// define parameters
// i : case		|-- (0)normal (1)R1 short (2)R1 open (3)R2 short (4)R2 open (5)R3 short (6)R3 open (7)R4 short (8)R4 open 
//								(9)C1 open (10)C1 double (11)C2 open (12)C2 double (13)C3 open (14)C3 double 
//								--| // Freq:1000Hz  Amplitude: 30mV
// j : port		|-- (0)CH3 - (1)CH4 - (2)CH7 -- |
extern double Amplitude_cmp_ref[CASE_TYPE][CASE_CHANNEL];
//*******************************// extern parameters
//*******************************// extern function


//*******************************// end_h
#endif

