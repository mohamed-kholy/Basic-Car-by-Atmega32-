/*
 * APP.c
 *
 * Created: 9/10/2021 12:29:17 AM
 *  Author: Node-Geeks
 */ 
#include "APP/APP.h"


int main(void)
{
	APP_init();
	
    while (1) 
    {
		APP_voidStateUpdate();
	}
}

