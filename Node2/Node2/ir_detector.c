/*
 * ir_detector.c
 *
 * Created: 06.11.2017 15:30:52
 *  Author: oystmol
 */ 
#include "ir_detector.h"
#include "adc_node2.h"
uint16_t ir_threshold(uint16_t filterTrigger){
	uint16_t mean = 0;
	for (int i = 0; i<filterTrigger; i++){
		mean += ADC_node2_read();
		//printf("målinger: %x \n", ADC_node2_read());
		_delay_ms(10);
	}
	mean = mean/(filterTrigger*0x2);
	printf("treshold %x \n", mean);
	return mean;
}

int ir_detection(uint16_t filterTrigger, uint16_t threshold){
	uint16_t mean = 0;
	
	for (int i = 0; i<filterTrigger; i++){
		mean += ADC_node2_read();
	}
	mean = mean/filterTrigger;
	//printf("mean %x \n", mean);
	if (mean < threshold){
		
		return 1;
	}
	else{
		return 0;
	}
}

struct Score ir_score_update(uint16_t threshold, struct Score poeng){
	
	if(ir_detection(0xa, threshold) && poeng.flag == 1){
		poeng.flag = 0;
		poeng.score +=1;
		_delay_ms(5000);

	}
	else if (!ir_detection(0xa, threshold) && poeng.flag == 0){
		poeng.flag = 1;
	}
	return poeng;
}