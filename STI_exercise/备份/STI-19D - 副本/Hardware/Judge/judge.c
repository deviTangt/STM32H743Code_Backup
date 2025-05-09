//*******************************// include _h files
#include "judge.h"
//*******************************// define structure unity
//*******************************// define parameters
//*******************************// parameters
// i : case		|-- (0)normal (1)R1 short (2)R1 open (3)R2 short (4)R2 open (5)R3 short (6)R3 open (7)R4 short (8)R4 open 
//								(9)C1 open (10)C1 double (11)C2 open (12)C2 double (13)C3 open (14)C3 double 
//								--| // Freq:1000Hz  Amplitude: 30mV
// j : port		|-- (0)CH3 - (1)CH4 - (2)CH7 -- |
double Amplitude_cmp_ref[CASE_TYPE][CASE_CHANNEL]= {
		{},				// 
		{},				//
		{},				//
		{}				//
};

double err_case[CASE_TYPE];
double err_min;
uint8_t case_err_min;
//*******************************// define function
void judge_circuit_case(float ad_val1, float ad_val2, float ad_val3){
	for (uint8_t i = 0;i < CASE_TYPE;i ++){
		err_case[i] = fabs(ad_val1 - Amplitude_cmp_ref[i][0]) + fabs(ad_val2 - Amplitude_cmp_ref[i][1]) + fabs(ad_val3 - Amplitude_cmp_ref[i][2]);
	}
	err_min = 1000.0;
	case_err_min = 0;
	for (uint8_t i = 0;i < CASE_TYPE;i ++){
		if (err_case[i] < err_min){
			err_min = err_case[i];
			case_err_min = i;
		}
	}
	switch(case_err_min){
		case 0:{ Serial_TJC_SendTxt(9, "Normal"); break;}
		case 1:{ Serial_TJC_SendTxt(9, "R1 Short 短路"); break;}
		case 2:{ Serial_TJC_SendTxt(9, "R1 open 开路"); break;}
		case 3:{ Serial_TJC_SendTxt(9, "R2 Short 短路"); break;}
		case 4:{ Serial_TJC_SendTxt(9, "R2 open 开路"); break;}
		case 5:{ Serial_TJC_SendTxt(9, "R3 Short 短路"); break;}
		case 6:{ Serial_TJC_SendTxt(9, "R3 open 开路"); break;}
		case 7:{ Serial_TJC_SendTxt(9, "R4 Short 短路"); break;}
		case 8:{ Serial_TJC_SendTxt(9, "R4 open 开路"); break;}
		case 9:{ Serial_TJC_SendTxt(9, "C1 open 开路"); break;}
		case 10:{ Serial_TJC_SendTxt(9, "C1 double 电容翻倍"); break;}
		case 11:{ Serial_TJC_SendTxt(9, "C1 open开路"); break;}
		case 12:{ Serial_TJC_SendTxt(9, "C2 double 电容翻倍"); break;}
		case 13:{ Serial_TJC_SendTxt(9, "C2 open 开路"); break;}
		case 14:{ Serial_TJC_SendTxt(9, "C3 double 电容翻倍"); break;}
		case 15:{ Serial_TJC_SendTxt(9, "C3 open 开路"); break;}
		default:{ Serial_TJC_SendTxt(9, "Exception 异常"); break;}
	}
}

//*******************************// end_c
