#ifndef __COMMUNICATION_H__
#define __COMMUNICATION_H__

#include "stdint.h"
#include "eeprom.h"
#include "uart.h"

#define MyID    Servo.Id
#define AllID   0x00
#define MainID   0x01

typedef enum
{
	DebugData = 0,
	ReadParameter = 1,
	SetParameter = 2,
	ReadPosition = 3,
	SetPosition = 4,
} MSGID;

typedef struct __communication
{
	uint16_t checksum;
	uint8_t parse_state;
	uint8_t len;
	uint8_t packet_idx;
	uint8_t SenderId;
	uint8_t TargetId;
	uint8_t MsgId;
	uint8_t payload[50];
} communication_t;

void handle_msg(communication_t *msg);
void SendData(char *data);
void ComCode(uint8_t senderid, uint8_t targetid, uint8_t msgid, uint8_t *packet, uint8_t length);
void ComDecode(uint8_t c, communication_t *msg);
void crc_init(uint16_t *crcAccum);
void crc_accumulate(uint8_t data, uint16_t *crcAccum);

#endif

