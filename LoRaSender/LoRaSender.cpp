#include <string.h>
#include <pico/stdlib.h>
#include "LoRa-RP2040.h"

int main() {

	stdio_init_all();
	printf("Initialising...");
	sleep_ms(5000);
	printf("Starting LoRa!\n");
	
	if (!LoRa.begin(500E6)) {
		printf("Starting LoRa failed!\n");
		while (1);
	}
	printf("Lora Status: Succesfully initialised\n");
	
	//set gp1 high
	gpio_init(1);
	gpio_set_dir(1, GPIO_OUT);
	gpio_put(1,1);
	//initialize LED
	const uint LED = 28;
	gpio_init(LED);
	gpio_set_dir(LED, GPIO_OUT);
	gpio_put(LED,0);
	//initialize button
	const uint btn = 2;
	gpio_init(btn);
	gpio_set_dir(btn, GPIO_IN);
	uint counter = 0;
	while (1)
	{
		switch (gpio_get(btn))
		{
		case 1:
			gpio_put(LED,1);
			printf("Sending packet: %d\n",counter);
			// send packet
			LoRa.beginPacket();
			LoRa.print("hello ");
			LoRa.endPacket();
			sleep_ms(100);
			gpio_put(LED,0);
			sleep_ms(100);
			printf("Packet Sent ^-^\n");
			counter++;
		case 0:
			sleep_ms(1);
		}
  }
  return 0;
}
