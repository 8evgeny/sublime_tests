// SPDX-License-Identifier: (GPL-2.0+ OR MIT)
/*
 * Copyright (c) 2022 Wesion Technology Co., Ltd.
 *
 * Author: Yan <yan-wyb@foxmail.com> 
 *
 */

#include <stdio.h>
#include <wiringPi.h>

const int gpio_pin = 1;

int main()
{
	if(-1 == wiringPiSetup()){
		printf("set up error");
		exit(1);
	}

	pinMode(gpio_pin,OUTPUT);

	while(1){
		digitalWrite(gpio_pin,HIGH);
		printf("wPi Pin %d now is GIGH\n",gpio_pin);
		delay(5000);
		digitalWrite(gpio_pin,LOW);
		printf("wPi Pin %d now is LOW\n",gpio_pin);
		delay(5000);
	}

	exit(0);
}
