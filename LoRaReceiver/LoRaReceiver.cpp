#include <string.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"

//Inlude Library
#include "LoRa-RP2040.h"

//declare speaker pin
const uint SPKR = 0;

//function to beep the speaker
void beep(int x)
{
   	gpio_put(SPKR, 1);
        sleep_ms(x);
        gpio_put(SPKR, 0);
	sleep_ms(x);
}

void arm_bomb(int TimePeriod)
{
	int reduction_value = 16;
	while(TimePeriod >= 16){
		if(TimePeriod > 500){
		reduction_value = 64;
		}
		else if(TimePeriod <= 500 && TimePeriod >=300){
		reduction_value = 32;
		} 
		else{
		reduction_value = 16;
		}
			printf("reduction value is %d  and  ",reduction_value);
			printf("Time Period is %d \n",TimePeriod);
			if(TimePeriod <=328 && TimePeriod > 200){
			printf("currently in double beep mode\n");
			beep(TimePeriod);
			beep(TimePeriod);
			TimePeriod -= reduction_value;
			}
			else if(TimePeriod <=200 && TimePeriod >100)
			{
				printf("Currently in triple beep mode! \n");
				beep(TimePeriod);
				beep(TimePeriod);
				beep(TimePeriod);
				TimePeriod -= reduction_value;
			}
			else if(TimePeriod <=100){
			printf("Currently in pentuple beep mode! \n");
				beep(TimePeriod);
				beep(TimePeriod);
				beep(TimePeriod);
				beep(TimePeriod);
				beep(TimePeriod);
				TimePeriod -= reduction_value;
			}
			else{
			printf("Currently in Single Beep Mode \n");
			beep(TimePeriod);
			TimePeriod -= reduction_value;
			}
			//beep(TimePeriod);
	}
}

int main() {

   stdio_init_all();
   //wait for minicom to open
   //printf("waiting 1 second\n");
   
   beep(250);

   if (!LoRa.begin(500E6)) {
      printf("Starting LoRa failed!\n");
      while (1);
   }

   printf("LoRa Started\n");
   
   //int counter = 0;

   gpio_init(SPKR);
   gpio_set_dir(SPKR, GPIO_OUT);
  
   
   while (1) {
      int packetSize = LoRa.parsePacket();
      if (packetSize) {
         // received a packet
         printf("Received packet \n'");
	 //beep(250);
	 arm_bomb(1000);
	 packetSize = 0;

         // read packet
         /*while (LoRa.available()) {
            printf((char*)LoRa.read());
         }

         // print RSSI of packet
         printf("' with RSSI \n");
         printf((char*)LoRa.packetRssi(),"\n");*/
      }
      //printf("the while loop is looping\n");
      //sleep_ms(128);
  }

  return 1;
}
