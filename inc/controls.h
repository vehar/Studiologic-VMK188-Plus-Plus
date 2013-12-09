#include "stm32f4xx.h"
#include "timer.h"
#include "stm32f4xx_gpio.h"


#define SLIDERS_TICKS_FACTOR 2000/TIMER_TIMPERIOD
#define SLIDERS_DELTA 0x10
#define SLIDERS_MUX_DELAY 200/TIMER_TIMPERIOD
#define SLIDERS_MEASURE_NUM 100

#define SLIDER_S1 14
#define SLIDER_S2 4
#define SLIDER_S3 10
#define SLIDER_S4 22
#define SLIDER_S5 16
#define SLIDER_S6 7
#define SLIDER_S7 13
#define SLIDER_S8 1
#define SLIDER_S9 19

#define SLIDER_R1 9
#define SLIDER_R2 0
#define SLIDER_R3 3
#define SLIDER_R4 6
#define SLIDER_R5 15
#define SLIDER_R6 21
#define SLIDER_R7 18
#define SLIDER_R8 12

#define SLIDER_AT 17
#define SLIDER_PITCH 23
#define SLIDER_MOD 20
#define SLIDER_P1 5
#define SLIDER_P2 2
#define SLIDER_P3 11
#define SLIDER_EMPTY 8

#define SLIDER_S_MIN_IN 0
#define SLIDER_S_MAX_IN 3200
#define SLIDER_S_MIN_OUT 0
#define SLIDER_S_MAX_OUT 127

#define SLIDER_R_MIN_IN 850
#define SLIDER_R_MAX_IN 3420
#define SLIDER_R_MIN_OUT 0
#define SLIDER_R_MAX_OUT 127

#define SLIDER_P_MIN_IN 300
#define SLIDER_P_MAX_IN 2000
#define SLIDER_P_MIN_OUT 0
#define SLIDER_P_MAX_OUT 127

#define SLIDER_PITCH_MIN_IN 500
#define SLIDER_PITCH_MAX_IN 2000
#define SLIDER_PITCH_MIN_OUT 0
#define SLIDER_PITCH_MAX_OUT 127

#define SLIDER_MOD_MIN_IN 500
#define SLIDER_MOD_MAX_IN 2000
#define SLIDER_MOD_MIN_OUT 0
#define SLIDER_MOD_MAX_OUT 127

#define SLIDER_AT_MIN_IN 0
#define SLIDER_AT_MAX_IN 3200
#define SLIDER_AT_MIN_OUT 0
#define SLIDER_AT_MAX_OUT 127

#define ENCODER1_PORT            GPIOC
#define ENCODER1_PIN        GPIO_Pin_13

#define ENCODER2_PORT            GPIOC
#define ENCODER2_PIN        GPIO_Pin_11


#define LED_EN_PORT              GPIOE
#define LED_EN_PIN         GPIO_Pin_3

#define BUTTON0_PORT              GPIOE
#define BUTTON0_PIN         GPIO_Pin_0

#define BUTTON1_PORT              GPIOE
#define BUTTON1_PIN         GPIO_Pin_1

#define BUTTON2_PORT              GPIOE
#define BUTTON2_PIN         GPIO_Pin_2


typedef struct {
	uint8_t active;
	uint8_t reverse;
	uint8_t channel;
	uint8_t event;
	uint8_t value;
	uint16_t min_in_value;
	uint16_t max_in_value;
	uint8_t min_out_value;
	uint8_t max_out_value;
	double a; // a & b are the parameters in slider formula y=a*x+b;
	double b;
} Slider_type;


typedef struct {
	GPIO_TypeDef * port;
	uint16_t pin;
} button_port_type;

typedef struct {
	uint8_t active;
	uint8_t channel;
	uint8_t event;
} Button_type;


void ADC_init_all(void);
void read_controls(void);
void sliders_init(void);
