#include "Message.h"

uint8_t unused;

void Decode_CI_Msg(CI_Msg* msg){
	switch(msg->command){
		case LED_RED:{
			log0("1");
			LED_select(RED,(msg->data[0]*100));
			break;
		}
		case LED_BLUE:{
			log0("2");
			LED_select(BLUE,(msg->data[0]*100));
			break;
		}
		case LED_GREEN:{
			log0("3");
			LED_select(GREEN,(msg->data[0]*100));
			break;
		}
		case LED_YELLOW:{
			log0("3");
			LED_select(YELLOW,(msg->data[0]*100));
			break;
		}
		case LED_CYAN:{
			log0("3");
			LED_select(CYAN,(msg->data[0]*100));
			break;
		}
		case LED_MAGENTA:{
			log0("3");
			LED_select(MAGENTA,(msg->data[0]*100));
			break;
		}
		case LED_WHITE:{
			log0("3");
			LED_select(WHITE,(msg->data[0]*100));
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
		if(checksum == msg->checksum)
			log0("\n checksum ok");
		else
			log0("Checksum fail");

}
