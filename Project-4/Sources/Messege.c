#include "Message.h"

uint8_t unused,i;
float lux;
uint16_t humidity;

void Decode_CI_Msg(CI_Msg* msg){
	switch(msg->command){
		case LED_RED:{
			LED_select(RED,(msg->data[0]*100));
			break;
		}
		case LED_BLUE:{
			LED_select(BLUE,(msg->data[0]*100));
			break;
		}
		case LED_GREEN:{
			LED_select(GREEN,(msg->data[0]*100));
			break;
		}
		case LED_YELLOW:{
			LED_select(YELLOW,(msg->data[0]*100));
			break;
		}
		case LED_CYAN:{
			LED_select(CYAN,(msg->data[0]*100));
			break;
		}
		case LED_MAGENTA:{
			LED_select(MAGENTA,(msg->data[0]*100));
			break;
		}
		case LED_WHITE:{
			LED_select(WHITE,(msg->data[0]*100));
			break;
		}
		case LIGHT:{
			lux = tsl_getLux();
			log3("The lux value is: ",lux);
			break;
		}
		case HUMIDITY:{
			humidity = readHumidity();
			log3("The humidity is: ",humidity);
			break;
		}
	}
}

void Read_CI_Msg(CI_Msg*msg){
	uint8_t i, checksum;

		remove_item(&rx_buff,&(msg->command));
		remove_item(&rx_buff,&(msg->length));

		if(msg->length != 0){
			for(i=0;i<(msg->length);i++)
				remove_item(&rx_buff,&(msg->data[i]));
			for(i=(msg->length);i<2;i++)
				remove_item(&rx_buff,&unused);
		}
		else{
			for(i=0;i<2;i++)
				remove_item(&rx_buff,&unused);
		}

		remove_item(&rx_buff, &(msg->checksum));
		checksum = msg->command + msg->length + msg->data[0] + msg->data[1];
//		if(checksum == msg->checksum)
//			log0("\n checksum ok");
//		else
//			log0("Checksum fail");

}
