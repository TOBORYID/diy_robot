#include "communication.h"
#include "servo.h"
#include "uart.h"

static uint8_t checkmsg = 0;

void Com_Update(void)
{
	static communication_t msg;
	uint16_t nbytes = Get_Length();
	for(uint16_t i = 0; i < nbytes; i++)
	{
		uint8_t c = Get_Byte();
		if(ComDecode(c, &msg) == 1)
		{
			handle_msg(&msg);
		}
	}
}

void handle_msg(communication_t * msg)
{
	if(msg->TargetId == MyID)
	{
		switch(msg->MsgId)
		{
			case ReadParameter:
				Read_Parameter();
				break;
			case SetParameter:
				Write_Parameter(msg->payload);
				break;
			case ReadPosition:
				Read_Position();
				break;
			case SetPosition:
				Write_Position(msg->payload);
				break;
			default:
				break;
		}
	}

	if(msg->TargetId == AllID)
	{
		switch(msg->MsgId)
		{
			case ReadParameter:
				Read_Parameter();
				break;
			case SetParameter:
				Write_Parameter(msg->payload);
				break;
			case ReadPosition:
				Read_Position();
				break;
			case SetPosition:
				Write_Position(msg->payload);
				break;
			default:
				break;
		}
	}
}

void SendData(char *data)
{
	ComCode(MyID, MainID, DebugData, (uint8_t *)data, strlen(data));
}

void ComCode(uint8_t senderid, uint8_t targetid, uint8_t msgid, uint8_t * packet, uint8_t length)
{
	uint8_t data[8 + length];
	uint16_t crc16 = 0xffff;

	data[0] = 0xfd;
	data[1] = 0xfe;
	data[2] = length;
	crc_accumulate(data[2], &crc16);
	data[3] = senderid;
	crc_accumulate(data[3], &crc16);
	data[4] = targetid;
	crc_accumulate(data[4], &crc16);
	data[5] = msgid;
	crc_accumulate(data[5], &crc16);
	for(uint8_t i = 0; i < length; i++)
	{
		data[6 + i] = packet[i];
		crc_accumulate(data[6 + i], &crc16);
	}
	crc_accumulate(0, &crc16);
	data[6 + length] = crc16 & 0xFF;
	data[7 + length] = crc16 >> 8;
	Put_Str(data, 8 + length);
}

uint8_t ComDecode(uint8_t c, communication_t * msg)
{
	checkmsg = 0;
	switch(msg->parse_state)
	{
		case 0:
			if(c == 0xfd)
			{
				msg->parse_state = 1;
			}
			break;
		case 1:
			if(c == 0xfe)
			{
				msg->packet_idx = 0;
				msg->parse_state = 2;
				crc_init(&msg->checksum);
			}
			else
			{
				msg->parse_state = 0;
			}
			break;
		case 2:
			if(c < 50)
			{
				msg->len = c;
				crc_accumulate(c, &msg->checksum);
				msg->parse_state = 3;
			}
			else
			{
				msg->parse_state = 0;
			}
			break;
		case 3:
			msg->SenderId = c;
			crc_accumulate(c, &msg->checksum);
			msg->parse_state = 4;
			break;
		case 4:
			msg->TargetId = c;
			crc_accumulate(c, &msg->checksum);
			msg->parse_state = 5;
			break;
		case 5:
			msg->MsgId = c;
			crc_accumulate(c, &msg->checksum);
			msg->parse_state = 6;
			break;
		case 6:
			crc_accumulate(c, &msg->checksum);
			msg->payload[msg->packet_idx++] = c;
			if(msg->packet_idx == msg->len)
			{
				msg->parse_state = 7;
			}
			break;
		case 7:
			crc_accumulate(0, &msg->checksum);
			if(c == (msg->checksum & 0xFF))
			{
				msg->parse_state = 8;
			}
			else
			{
				msg->parse_state = 0;
			}
			break;
		case 8:
			if(c == (msg->checksum >> 8))
			{
				checkmsg = 1;
			}
			msg->parse_state = 0;
			break;
	}
	return checkmsg;
}

void crc_init(uint16_t * crcAccum)
{
	*crcAccum = 0XFFFF;
}

void crc_accumulate(uint8_t data, uint16_t * crcAccum)
{
	uint8_t tmp;
	tmp = data ^ (uint8_t)(*crcAccum & 0xff);
	tmp ^= (tmp << 4);
	*crcAccum = (*crcAccum >> 8) ^ (tmp << 8) ^ (tmp << 3) ^ (tmp >> 4);
}