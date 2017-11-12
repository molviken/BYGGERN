#include <rtm.h>
#include <stm32f4xx.h>
#include <finsh.h>

#include "libarduino.h"

struct pin_index
{
	int index;
	uint32_t rcc;
	GPIO_TypeDef *gpio;
	uint32_t pin;
};

#define ITEM_NUM(items)	sizeof(items)/sizeof(items[0])

struct pin_index pins[] =
{
	{ 0, RCC_AHB1Periph_GPIOC, GPIOC, GPIO_Pin_7},
	{ 1, RCC_AHB1Periph_GPIOC, GPIOC, GPIO_Pin_6},
	{ 2, RCC_AHB1Periph_GPIOC, GPIOC, GPIO_Pin_8},
	{ 3, RCC_AHB1Periph_GPIOB, GPIOB, GPIO_Pin_11},
	{ 4, RCC_AHB1Periph_GPIOE, GPIOE, GPIO_Pin_14},
	{ 5, RCC_AHB1Periph_GPIOE, GPIOE, GPIO_Pin_13},
	{ 6, RCC_AHB1Periph_GPIOE, GPIOE, GPIO_Pin_11},
	{ 7, RCC_AHB1Periph_GPIOE, GPIOE, GPIO_Pin_9},

	{ 8, RCC_AHB1Periph_GPIOD, GPIOD, GPIO_Pin_12},
	{ 9, RCC_AHB1Periph_GPIOD, GPIOD, GPIO_Pin_13},
	{10, RCC_AHB1Periph_GPIOD, GPIOD, GPIO_Pin_14},
	{11, RCC_AHB1Periph_GPIOD, GPIOD, GPIO_Pin_15},
	{12, RCC_AHB1Periph_GPIOE, GPIOE, GPIO_Pin_6},
	{13, RCC_AHB1Periph_GPIOE, GPIOE, GPIO_Pin_5},

	{14, RCC_AHB1Periph_GPIOD, GPIOD, GPIO_Pin_8},
	{15, RCC_AHB1Periph_GPIOD, GPIOD, GPIO_Pin_9},
	{16, RCC_AHB1Periph_GPIOD, GPIOD, GPIO_Pin_5},
	{17, RCC_AHB1Periph_GPIOD, GPIOD, GPIO_Pin_6},
	{18, RCC_AHB1Periph_GPIOB, GPIOB, GPIO_Pin_6},
	{19, RCC_AHB1Periph_GPIOB, GPIOB, GPIO_Pin_7},
	{20, RCC_AHB1Periph_GPIOC, GPIOC, GPIO_Pin_9},
	{21, RCC_AHB1Periph_GPIOA, GPIOA, GPIO_Pin_8},

	{22, RCC_AHB1Periph_GPIOC, GPIOC, GPIO_Pin_12},
	{23, RCC_AHB1Periph_GPIOD, GPIOD, GPIO_Pin_2},
	{24, RCC_AHB1Periph_GPIOD, GPIOD, GPIO_Pin_1},
	{25, RCC_AHB1Periph_GPIOD, GPIOD, GPIO_Pin_0},
	{26, RCC_AHB1Periph_GPIOA, GPIOA, GPIO_Pin_9},
	{27, RCC_AHB1Periph_GPIOC, GPIOC, GPIO_Pin_13},
	{28, RCC_AHB1Periph_GPIOE, GPIOE, GPIO_Pin_15},
	{29, RCC_AHB1Periph_GPIOE, GPIOE, GPIO_Pin_12},
	{30, RCC_AHB1Periph_GPIOE, GPIOE, GPIO_Pin_10},
	{31, RCC_AHB1Periph_GPIOE, GPIOE, GPIO_Pin_8},
	{32, RCC_AHB1Periph_GPIOE, GPIOE, GPIO_Pin_7},
	{33, RCC_AHB1Periph_GPIOE, GPIOE, GPIO_Pin_4},
	{34, RCC_AHB1Periph_GPIOE, GPIOE, GPIO_Pin_3},
	{35, RCC_AHB1Periph_GPIOE, GPIOE, GPIO_Pin_2},
	{36, RCC_AHB1Periph_GPIOE, GPIOE, GPIO_Pin_1},
	{37, RCC_AHB1Periph_GPIOE, GPIOE, GPIO_Pin_0},
	{38, RCC_AHB1Periph_GPIOD, GPIOD, GPIO_Pin_11},
	{39, RCC_AHB1Periph_GPIOD, GPIOD, GPIO_Pin_10},
	{40, RCC_AHB1Periph_GPIOD, GPIOD, GPIO_Pin_7},
	{41, RCC_AHB1Periph_GPIOD, GPIOD, GPIO_Pin_3},
	{42, RCC_AHB1Periph_GPIOD, GPIOD, GPIO_Pin_4},
	{43, RCC_AHB1Periph_GPIOB, GPIOB, GPIO_Pin_8},
	{44, RCC_AHB1Periph_GPIOC, GPIOC, GPIO_Pin_15},
	{45, RCC_AHB1Periph_GPIOC, GPIOC, GPIO_Pin_14},
	{46, RCC_AHB1Periph_GPIOC, GPIOC, GPIO_Pin_11},
	{47, RCC_AHB1Periph_GPIOB, GPIOB, GPIO_Pin_5},
	{48, RCC_AHB1Periph_GPIOC, GPIOC, GPIO_Pin_10},
	{49, RCC_AHB1Periph_GPIOA, GPIOA, GPIO_Pin_15},
	{50, RCC_AHB1Periph_GPIOB, GPIOB, GPIO_Pin_4},
	{51, RCC_AHB1Periph_GPIOA, GPIOA, GPIO_Pin_7},
	{52, RCC_AHB1Periph_GPIOB, GPIOB, GPIO_Pin_3},
	{53, RCC_AHB1Periph_GPIOA, GPIOA, GPIO_Pin_4},
};

struct apin_index apins[] =
{
	{ 0, RCC_AHB1Periph_GPIOC, GPIOC, GPIO_Pin_0},
	{ 1, RCC_AHB1Periph_GPIOC, GPIOC, GPIO_Pin_1},
	{ 2, RCC_AHB1Periph_GPIOA, GPIOA, GPIO_Pin_0,
	{ 3, RCC_AHB1Periph_GPIOA, GPIOA, GPIO_Pin_1},
	{ 4, RCC_AHB1Periph_GPIOA, GPIOA, GPIO_Pin_2},
	{ 5, RCC_AHB1Periph_GPIOA, GPIOA, GPIO_Pin_3},
	{ 6, RCC_AHB1Periph_GPIOA, GPIOA, GPIO_Pin_5},
	{ 7, RCC_AHB1Periph_GPIOA, GPIOA, GPIO_Pin_6},

	{ 8, RCC_AHB1Periph_GPIOC, GPIOC, GPIO_Pin_4},
	{ 9, RCC_AHB1Periph_GPIOC, GPIOC, GPIO_Pin_5},
	{10, RCC_AHB1Periph_GPIOB, GPIOB, GPIO_Pin_0},
	{11, RCC_AHB1Periph_GPIOB, GPIOB, GPIO_Pin_1},
	{12, RCC_AHB1Periph_GPIOC, GPIOC, GPIO_Pin_3},
	{13, RCC_AHB1Periph_GPIOC, GPIOC, GPIO_Pin_2},
	{14, RCC_AHB1Periph_GPIOB, GPIOB, GPIO_Pin_9},
	{15, RCC_AHB1Periph_GPIOB, GPIOB, GPIO_Pin_10},
}

typedef struct
{
	TIM_TypeDef *tim;
	uint32_t tim_rcc;
	uint16_t tim_channel;
	uint8_t pin_source;
	uint8_t gpio_af;
} pin_to_timer_index_t;

#define NOT_A_TIM RT_NULL
pin_to_timer_index_t pin_to_timer_index[] = {
	{NOT_A_TIM},
	{NOT_A_TIM},
	{TIM3, RCC_APB1Periph_TIM3, TIM_Channel_3, GPIO_PinSource8, GPIO_AF_TIM3},
	{TIM2, RCC_APB1Periph_TIM2, TIM_Channel_4, GPIO_PinSource11, GPIO_AF_TIM2},
	{TIM1, RCC_APB2Periph_TIM1, TIM_Channel_4, GPIO_PinSource14, GPIO_AF_TIM1},

	{TIM1, RCC_APB2Periph_TIM1, TIM_Channel_3, GPIO_PinSource13, GPIO_AF_TIM1},
	{TIM1, RCC_APB2Periph_TIM1, TIM_Channel_2, GPIO_PinSource11, GPIO_AF_TIM1},
	{TIM1, RCC_APB2Periph_TIM1, TIM_Channel_1, GPIO_PinSource9, GPIO_AF_TIM1},
	{TIM4, RCC_APB1Periph_TIM4, TIM_Channel_1, GPIO_PinSource12, GPIO_AF_TIM4},
	{TIM4, RCC_APB1Periph_TIM4, TIM_Channel_2, GPIO_PinSource13, GPIO_AF_TIM4},

	{TIM4, RCC_APB1Periph_TIM4, TIM_Channel_3, GPIO_PinSource14, GPIO_AF_TIM4},
	{TIM4, RCC_APB1Periph_TIM4, TIM_Channel_4, GPIO_PinSource15, GPIO_AF_TIM4},
	{TIM9, RCC_APB2Periph_TIM8, TIM_Channel_2, GPIO_PinSource6, GPIO_AF_TIM9},
	{TIM9, RCC_APB2Periph_TIM9, TIM_Channel_1, GPIO_PinSource5, GPIO_AF_TIM9},
};

inline pin_to_timer_index_t *pin_to_timer(uint8_t pin)
{
	if (pin >= ITEM_NUM(pin_to_timer_index))
		return RT_NULL;
	else
		return pin_to_timer_index + pin;
}

typedef struct
{
	//TIM_TypeDef *adc;	
	//uint32_t adc_rcc;	
	uint16_t adc_channel;	
	uint8_t pin_source;	
	//uint8_t gpio;
} pin_to_adc_index_t;

pin_to_adc_index_t pin_to_adc_index[] = {	
	{/*TIM3, RCC_APB2Periph_ADC1,*/  ADC_Channel_10, GPIO_PinSource8},	
	{/*TIM2, RCC_APB2Periph_ADC2, */ ADC_Channel_11, GPIO_PinSource11},	
	{/*TIM1, RCC_APB2Periph_ADC1, */ ADC_Channel_0, GPIO_PinSource14},	
//	{0},	
	{/*TIM1, RCC_APB2Periph_ADC1, */ADC_Channel_1, GPIO_PinSource13},	
	{/*TIM1, RCC_APB2Periph_ADC1, */ADC_Channel_2, GPIO_PinSource11},	
	{/*TIM1, RCC_APB2Periph_ADC1, */ADC_Channel_3, GPIO_PinSource9},	
	{/*TIM4, RCC_APB2Periph_ADC4, */ADC_Channel_5, GPIO_PinSource12},	
	{/*TIM4, RCC_APB2Periph_ADC4, */ADC_Channel_6, GPIO_PinSource13},	
//	{0},	
	{/*TIM4, RCC_APB2Periph_ADC4, */ADC_Channel_14, GPIO_PinSource14},	
	{/*TIM4, RCC_APB2Periph_ADC4, */ADC_Channel_15, GPIO_PinSource15},	
	{/*TIM9, RCC_APB2Periph_ADC8, */ADC_Channel_8, GPIO_PinSource6},	
	{/*TIM9, RCC_APB2Periph_ADC9, */ADC_Channel_9, GPIO_PinSource5},
	{/*TIM9, RCC_APB2Periph_ADC9, */ADC_Channel_13, GPIO_PinSource5},
	{/*TIM9, RCC_APB2Periph_ADC9, */ADC_Channel_12, GPIO_PinSource5},
};

inline apin_to_adc_index_t *pin_to_adc(uint8_t pin)
{	
	if (pin >= ITEM_NUM(apin_to_adc_index))
			return RT_NULL;	
		else
			return pin_to_adc_index + pin;
}

void pinMode(uint8_t pin, uint8_t mode)
{
	const struct pin_index* index;
	if (pin < ITEM_NUM(pins))
	{
	    GPIO_InitTypeDef  GPIO_InitStructure;
		index = &pins[pin];

	    /* GPIO Periph clock enable */
	    RCC_AHB1PeriphClockCmd(index->rcc, ENABLE);

	    /* Configure PE5 */
	    GPIO_InitStructure.GPIO_Pin = index->pin;
	    if (mode == OUTPUT)
	    {
	    	/* output setting */
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	    }
	    else
	    {
	    	/* input setting */
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	    }
	    GPIO_Init(index->gpio, &GPIO_InitStructure);
	}
}
FINSH_FUNCTION_EXPORT(pinMode, set pin mode);

void digitalWrite(uint8_t pin, uint8_t value)
{
	const struct pin_index* index;
	if (pin < ITEM_NUM(pins))
	{
		index = &pins[pin];
		if (value == HIGH)
			GPIO_SetBits(index->gpio, index->pin);
		else
			GPIO_ResetBits(index->gpio, index->pin);
	}
}
FINSH_FUNCTION_EXPORT(digitalWrite, write value to digital pin);

int digitalRead(uint8_t pin)
{
	int value;
	const struct pin_index *index;

	value = LOW;
	if (pin < ITEM_NUM(pins))
	{
		index = &pins[pin];
		if (GPIO_ReadInputDataBit(index->gpio, index->pin) == Bit_RESET)
			value = LOW;
		else
			value = HIGH;
	}

	return value;
}
FINSH_FUNCTION_EXPORT(digitalRead, read value from digital pin);

void adcConfig(struct *index )
{
	ADC_InitTypedef ADC_InitStructure;
	ADC_CommonInitTypedef ADC_CommonInitStructure;
	GPIO_InitTypedef GPIO_InitStructure;
	pin_to_adc_index_t *adc_index;
	struct apin_index *apin_index_p;

	apin_index_p = apins + pin;

	adc_index = pin_to_adc(pin);

	RCC_AHB1PeriphClockCmd(apin_index_p->rcc,ENABLE);
	RCC_AHB2PeriphClockCMD(RCC_AHB2Periph_ADC1,ENABLE);
	GPIO_InitStructure.GPIO_Pin = apin_index_p->pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_Pupd = GPIO_Pupd_NOPNULL;
	GPIO_Init(apin_index_p->rcc,&GPIO_InitStructure);
	
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = 		              		ADC_TwoSamplingDelay_5cyles;
	ADC_CommonInit(&ADC_CommonInitStructure);
	
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
  	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  	ADC_InitStructure.ADC_ExternalTrigConvEdge = 	ADC_ExternalTrigConvEdge_None;
       ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  	ADC_InitStructure.ADC_NbrOfConversion = 1;
  	ADC_Init(ADC1, &ADC_InitStructure);

  	ADC_RegularChannelConfig(ADC1, adc_index->adc_channel, 1, ADC_SampleTime_3Cycles);

  	ADC_Cmd(ADC1, ENABLE);
}

uint16_t analogRead(uint8 pin) {
    const struct pin_index* index
    index = &pins[pin];
    
    adcConfig(*index);
    
    }

    return adc_read(dev, PIN_MAP[pin].adc_channel);
}

void pwmConfig(uint8_t pin, uint8_t duty_cycle, unsigned int frequency, unsigned int clock)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	uint16_t PrescalerValue;
	GPIO_InitTypeDef GPIO_InitStructure;
	pin_to_timer_index_t *timer_index;
	struct pin_index *pin_index_p;
	uint32_t period = clock / frequency - 1;
	RT_ASSERT(period <= UINT16_MAX);

 	if(pin >= ITEM_NUM(pins))
		return;
	pin_index_p = pins + pin;

	timer_index = pin_to_timer(pin);
	if(!timer_index || !timer_index->tim)
		return;

	/* TIM clock enable */
	RCC_APB2PeriphClockCmd(timer_index->tim_rcc, ENABLE);

	/* GPIO clock enable */
	RCC_AHB1PeriphClockCmd(pin_index_p->rcc, ENABLE);

	/* GPIO configuration */
	GPIO_InitStructure.GPIO_Pin = pin_index_p->pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	/* Connect TIM3 pins to AF */
	GPIO_PinAFConfig(pin_index_p->gpio, timer_index->pin_source, timer_index->gpio_af);

	/* Compute the prescaler value */
	RT_ASSERT(SystemCoreClock / 2 / clock - 1 <= UINT16_MAX);
	PrescalerValue = (uint16_t) (SystemCoreClock / 2 / clock - 1);
	
	/* Time base configuration */
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Period = period;
	TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(timer_index->tim, &TIM_TimeBaseStructure);

	/* PWM1 Mode configuration: Channel1 */
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = period * duty_cycle / UINT8_MAX;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	switch (timer_index->tim_channel)
	{
		case TIM_Channel_1:
			TIM_OC1Init(timer_index->tim, &TIM_OCInitStructure);
			TIM_OC1PreloadConfig(timer_index->tim, TIM_OCPreload_Enable);
			break;
		case TIM_Channel_2:
			TIM_OC1Init(timer_index->tim, &TIM_OCInitStructure);
			TIM_OC1PreloadConfig(timer_index->tim, TIM_OCPreload_Enable);
			break;
		case TIM_Channel_3:
			TIM_OC1Init(timer_index->tim, &TIM_OCInitStructure);
			TIM_OC1PreloadConfig(timer_index->tim, TIM_OCPreload_Enable);
			break;
		case TIM_Channel_4:
			TIM_OC1Init(timer_index->tim, &TIM_OCInitStructure);
			TIM_OC1PreloadConfig(timer_index->tim, TIM_OCPreload_Enable);
			break;
		default:
			RT_ASSERT(0);
			return;
	}

	TIM_ARRPreloadConfig(timer_index->tim, ENABLE);
	TIM_Cmd(timer_index->tim, ENABLE);
}

#define PWM_COUNTER_CLOCK 	1000000	// choose a value which will result in proper prescalar value
#define PWM_FREQUENCY		64000	// choose a value which will result in proper period
void analogWrite(uint8_t pin, uint8_t value)
{
	// We need to make sure the PWM output is enabled for those pins
	// that support it, as we turn it off when digitally reading or
	// writing with them.  Also, make sure the pin is in output mode
	// for consistenty with Wiring, which doesn't require a pinMode
	// call for the analog output pins.

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	if (value == 0)
	{
		pinMode(pin, OUTPUT);
		digitalWrite(pin, LOW);
	}
	else if (value == 255)
	{
		pinMode(pin, OUTPUT);
		digitalWrite(pin, HIGH);
	}
	else
	{
		pwmConfig(pin, value, PWM_FREQUENCY, PWM_COUNTER_CLOCK);
	}
}
FINSH_FUNCTION_EXPORT(analogWrite, write analog value to digital pin using pwm);

volatile static voidFuncPtr intFunc[EXTERNAL_NUM_INTERRUPTS];

static void defaultIsrHandler(void)
{
	rt_kprintf("Unknow ISR\n");
}

void initInterrupt(void)
{
	rt_uint32_t index;

	for (index = 0; index < EXTERNAL_NUM_INTERRUPTS; index ++)
	{
		intFunc[index] = defaultIsrHandler;
	}
}

void attachInterrupt(uint8_t interruptNum, void (*userFunc)(void), int mode) {
	if (interruptNum < EXTERNAL_NUM_INTERRUPTS)
	{
		intFunc[interruptNum] = userFunc;
	}
}

void detachInterrupt(uint8_t interruptNum) {
	if (interruptNum < EXTERNAL_NUM_INTERRUPTS)
	{
		intFunc[interruptNum] = defaultIsrHandler;
	}
}

RTM_EXPORT(pinMode);
RTM_EXPORT(digitalWrite);
RTM_EXPORT(digitalRead);
RTM_EXPORT(analogWrite);
RTM_EXPORT(analogRead);

RTM_EXPORT(attachInterrupt);
RTM_EXPORT(detachInterrupt);
