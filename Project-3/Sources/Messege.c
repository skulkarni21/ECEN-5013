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
	}
}

void Read_CI_Msg(CI_Msg*msg){
	uint8_t i;

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
}
