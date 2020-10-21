#include <ESP8266WiFi.h>
#include <Ticker.h>

Ticker timer;

volatile int interrupts;

void setup()
{
  Serial.begin(115200);
  //Initialize Ticker every 0.5s
  timer1_attachInterrupt(onTime); // Add ISR Function
  timer1_enable(TIM_DIV16, TIM_EDGE, TIM_SINGLE);
  /* Dividers:
    TIM_DIV1 = 0,   //80MHz (80 ticks/us - 104857.588 us max)
    TIM_DIV16 = 1,  //5MHz (5 ticks/us - 1677721.4 us max)
    TIM_DIV256 = 3  //312.5Khz (1 tick = 3.2us - 26843542.4 us max)
  Reloads:
    TIM_SINGLE  0 //on interrupt routine you need to write a new value to start the timer again
    TIM_LOOP  1 //on interrupt the counter will start with the same value again
  */
  
  // Arm the Timer for our 0.5s Interval
  timer1_write(2500000); // 2500000 / 5 ticks per us from TIM_DIV16 == 500,000 us interval 
}

// ISR to Fire when Timer is triggerededed
ICACHE_RAM_ATTR void onTime() {
  interrupts++;
  Serial.print("Total Ticks:");
  Serial.println(interrupts);
  // Re-Arm the timer as using TIM_SINGLE
  timer1_write(2500000);//12us
}

void loop()
{
}
