//*******************************// include _h files
#include "judge.h"
//*******************************// define structure unity
//*******************************// define parameters
//*******************************// parameters
// i : case		|-- (0)normal (1)R1 short (2)R1 open (3)R2 short (4)R2 open (5)R3 short (6)R3 open (7)R4 short (8)R4 open 
//								(9)C1 open (10)C1 double (11)C2 open (12)C2 double (13)C3 open (14)C3 double 
//								--| // Freq:1000Hz  Amplitude: 30mV
// j : port		|-- (0)CH3 - (1)CH4 - (2)CH7 -- |
#if 1
double Amplitude_cmp_ref_01[CASE_TYPE][CASE_CHANNEL][2]= {
	// 0			1					2					3				4		5			6
	{{998.0, 567.0}, {1627.0, 1650.0}, {1021.0, 990.0}, {804.0, 770.0}, {3302.0}, {2110.0}, {174430.0}},		// (0)normal

	// 0			1					2				3				4		5		6
	{{127.0, 0.0}, {1700.0, 1711.0}, {654.0, 590.0}, {518.0, 480.0}, {1252.0}, {0.0}, {0.0}},			// (1)R1 short			@2 a*
	{{161.0, 0.0}, {1656.0, 1670.0}, {1470.0, 1470.0}, {1108.0, 1170.0}, {12361.0}, {0.0}, {0.0}},		// (2)R1 open		@4 a*
	{{149.0, 0.0}, {1696.0, 1715.0}, {830.0, 852.0}, {637.0, 669.0}, {1918.0}, {0.0}, {0.0}},			// (3)R2 short			@2 b*
	{{47.0, 0.0}, {1642.0, 1700.0}, {567.0, 514.0}, {460.0, 414.0}, {1102.0}, {0.0}, {0.0}},		// (4)R2 open		@2 a*
	{{151.0, 0.0}, {1647.0, 1668.0}, {970.0, 960.0}, {772.0, 745.0}, {19035.0}, {0.0}, {0.0}},		// (5)R3 short		@4 c*
	{{0.0, 0.0}, {1645.0, 1672.0}, {500.0, 500.0}, {417.0, 416.0}, {938.0}, {0.0}, {0.0}},				// (6)R3 open			@2 a*
	{{0.0, 0.0}, {1633.0, 1660.0}, {547.0, 547.0}, {436.0, 436.0}, {1008.0}, {0.0}, {0.0}},				// (7)R4 short			@2 a*
	{{159.0, 0.0}, {1645.0, 1670.0}, {1394.0, 1410.0}, {1083.0, 1100.0}, {9837.0}, {0.0}, {0.0}},		// (8)R4 open		@4 a*

	// 0			1					2				3				4		5		6
	{{77.0, 0.0}, {1680.0, 1720.0}, {1630.0, 1649.0}, {1260.0, 1250.0}, {83065.0}, {0.0}, {1000.0}},		// (9)C1 open		@0 a 4 a*
	{{540.0, 498.0}, {1607.0, 1618.0}, {1517.0, 1037.0}, {1172.0, 789.0}, {33897.0}, {165.0}, {1000.0}},	// (10)C1 double			@3 a
	{{76.0, 3.5}, {1660.0, 1700.0}, {1400.0, 1386.0}, {1080.0, 1074.0}, {9751.0}, {0.0}, {1000.0}},		// (11)C2 open		@0 a 4 b
	{{1100.0, 625.0}, {1700.0, 1749.0}, {1051.0, 1039.0}, {812.0, 798.0}, {3242.0}, {1570.0}, {1000.0}},	// (12)C2 doublE		@2 a 4
	{{1186.0, 650.0}, {1673.0, 1695.0}, {950.0, 950.0}, {750.0, 740.0}, {3542.0}, {1548.0}, {1000.0}},		// (13)C3 open			@2 a 4
	{{1098.0, 545.0}, {1681.0, 1719.0}, {1628.0, 1053.0}, {799.0, 808.0}, {3144.0}, {2018.0}, {1000.0}} 	// (14)C3 double		@2 b
};
#endif

double err_case[CASE_TYPE];
double err_min_save;
double check_temp;
uint8_t case_evaluate;
//*******************************// define function
void check_normal(){
	uint8_t i;
	check_temp = 0.0;
	for (i = 0;i < 4;i ++){
		check_temp += fabs(ad_val_ready[i][0] - Amplitude_cmp_ref_01[0][i][0]);
		check_temp += fabs(ad_val_ready[i][1] - Amplitude_cmp_ref_01[0][i][1]);
	}
	Serial_TJC_SendTxt_2(25, "check temp:%4.2f", check_temp);
	if (check_temp > 600.0) judge_circuit_case(); 
	else   {
		case_evaluate = 0;
		if (1 || case_err_cal(0) < case_err_cal(13))
			Serial_TJC_SendTxt_2(TJC_JUDGE_SHOW_POS, "Normal");
		else{
			Serial_TJC_SendTxt_2(TJC_JUDGE_SHOW_POS, "C3 open 开路");
			case_evaluate = 13;
		}
	}
}
//
double case_err_cal(uint8_t check_case){
	check_temp = 0.0;
	for (uint8_t i = 0;i < 4;i ++){
		check_temp += fabs(ad_val_ready[i][0] - Amplitude_cmp_ref_01[check_case][i][0]);
		check_temp += fabs(ad_val_ready[i][1] - Amplitude_cmp_ref_01[check_case][i][1]);
	}
	return check_temp;
}
//
void judge_circuit_case(){
	if (ad_val_ready[0][0] < 200.0 && ad_val_ready[0][1] < 50.0) {	// R出问题
		if (700.0 < ad_val_ready[2][0] && ad_val_ready[2][0] < 900.0 && 700.0 < ad_val_ready[2][1] && ad_val_ready[2][1] < 900.0)	//@2 b
			case_evaluate = 3; 
		else if (250.0 < ad_val_ready[2][0] && ad_val_ready[2][0] < 400.0 && 250.0 < ad_val_ready[2][1] && ad_val_ready[2][1] < 400.0)  //@2 c
			case_evaluate = 7;
		else {
			case_evaluate = (ad_val_ready[4][0] > 1060.0)
								 ? 4 : 6;
			err_case[4] = case_err_cal(4);
			err_case[6] = case_err_cal(6);
			err_case[5] = case_err_cal(5);
			err_case[8] = case_err_cal(8);
			err_case[11] = case_err_cal(11);
			if (err_case[5] < err_case[case_evaluate]) case_evaluate = 5;
			if (err_case[8] < err_case[case_evaluate]) case_evaluate = 8;
			if (err_case[11] < err_case[case_evaluate]) case_evaluate = 11;

			if (err_case[case_evaluate] < 300.0) {
				case_evaluate = case_evaluate;
				
			}
			else {
				if (case_err_cal(9) < 300.0) case_evaluate = 9;
				else case_evaluate = 0;
			}
			
		}		//@4 a //@4 b //@4 c
	} 
	else {
		if (ad_val_ready[0][1] < 200.0 && ad_val_ready[0][1] < 200.0){	//@0 a
			case_evaluate = (case_err_cal(9) < case_err_cal(11)) ? 9 : 11;
		}
		else if (950.0 < ad_val_ready[2][0] && ad_val_ready[2][0] < 1200.0 && 950.0 < ad_val_ready[2][1] && ad_val_ready[2][1] < 1200.0){ //@2 a
			case_evaluate = (case_err_cal(12) < case_err_cal(13)) ? 12 : 13;
		}
		else if (1500.0 < ad_val_ready[2][0] && ad_val_ready[2][0] < 1700.0 && 950.0 < ad_val_ready[2][1] && ad_val_ready[2][1] < 1200.0
				&& 700.0 < ad_val_ready[3][0] && ad_val_ready[3][0] < 900.0 && 700.0 < ad_val_ready[3][1] && ad_val_ready[3][1] < 900.0) //@2 b
			case_evaluate = 14;
		else if (1100.0 < ad_val_ready[3][0] && ad_val_ready[3][0] < 1300.0 && 700.0 < ad_val_ready[3][1] && ad_val_ready[3][1] < 900.0) //@3 a
			case_evaluate = 10;
		else case_evaluate = 0;
	}

	err_min_save = case_err_cal(case_evaluate);

	switch(case_evaluate){
		case 0: { Serial_TJC_SendTxt_2(TJC_JUDGE_SHOW_POS, "未知"); 			break;}
		case 1: { Serial_TJC_SendTxt_2(TJC_JUDGE_SHOW_POS, "R1 Short 短路"); 		break;}
		case 2: { Serial_TJC_SendTxt_2(TJC_JUDGE_SHOW_POS, "R1 open 开路"); 		break;}
		case 3: { Serial_TJC_SendTxt_2(TJC_JUDGE_SHOW_POS, "R2 Short 短路"); 		break;}
		case 4: { Serial_TJC_SendTxt_2(TJC_JUDGE_SHOW_POS, "R2 open 开路"); 		break;}
		case 5: { Serial_TJC_SendTxt_2(TJC_JUDGE_SHOW_POS, "R3 Short 短路"); 		break;}
		case 6: { Serial_TJC_SendTxt_2(TJC_JUDGE_SHOW_POS, "R3 open 开路"); 		break;}
		case 7: { Serial_TJC_SendTxt_2(TJC_JUDGE_SHOW_POS, "R4 Short 短路"); 		break;}
		case 8: { Serial_TJC_SendTxt_2(TJC_JUDGE_SHOW_POS, "R4 open 开路"); 		break;}
		case 9: { Serial_TJC_SendTxt_2(TJC_JUDGE_SHOW_POS, "C1 open 开路"); 		break;}
		case 10:{ Serial_TJC_SendTxt_2(TJC_JUDGE_SHOW_POS, "C1 double 电容翻倍"); break;}
		case 11:{ Serial_TJC_SendTxt_2(TJC_JUDGE_SHOW_POS, "C2 open开路"); 		break;}
		case 12:{ Serial_TJC_SendTxt_2(TJC_JUDGE_SHOW_POS, "C2 double 电容翻倍"); break;}
		case 13:{ Serial_TJC_SendTxt_2(TJC_JUDGE_SHOW_POS, "C3 open 开路"); 		break;}
		case 14:{ Serial_TJC_SendTxt_2(TJC_JUDGE_SHOW_POS, "C3 double 电容翻倍"); break;}
		default:{ Serial_TJC_SendTxt_2(TJC_JUDGE_SHOW_POS, "Exception 异常"); 	break;}
	}

	if (0){	
		Serial_TJC_SendTxt_2(26, "Reference: 0 / 1");
		Serial_TJC_SendTxt_2(17, "%4.1f/%4.1f/%4.1f/%4.1f", Amplitude_cmp_ref_01[case_evaluate][0][0], Amplitude_cmp_ref_01[case_evaluate][0][1],
												Amplitude_cmp_ref_01[case_evaluate][1][0], Amplitude_cmp_ref_01[case_evaluate][1][1]);
		Serial_TJC_SendTxt_2(18, "%4.1f/%4.1f/%4.1f/%4.1f", Amplitude_cmp_ref_01[case_evaluate][2][0], Amplitude_cmp_ref_01[case_evaluate][2][1],
												Amplitude_cmp_ref_01[case_evaluate][3][0], Amplitude_cmp_ref_01[case_evaluate][3][1]);
	}

	Serial_TJC_SendTxt_2(24, "err_min:%6.4f", err_min_save);
}
//
//*******************************// end_c
