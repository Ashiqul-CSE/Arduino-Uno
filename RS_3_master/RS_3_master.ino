START_BYTE = 0x96; // 10010110
STOP_BYTE  = 0xA9; // 10101001


PACKAGE:
-------- 
START_BYTE 0x96
ADDRESS
DATALEN
[DATA1]            // if exists
[DATA2]            // if exists
[DATA3]            // if exists
CRC
STOP_BYTE  0xA9


DATALEN bits
------------
bit7 = 1  MASTER SENDS
       0  SLAVE  SENDS
bit6 = 1  ADDRESS WAS XORed with 1, IT WAS EQUAL TO START_BYTE or STOP_BYTE
       0  ADDRESS UNCHANGED
bit5 = 0  FIXED
bit4 = 1  DATA3 (if exists) WAS XORed with 1, IT WAS EQUAL TO START_BYTE or STOP_BYTE
       0  DATA3 (if exists) UNCHANGED
bit3 = 1  DATA2 (if exists) WAS XORed with 1, IT WAS EQUAL TO START_BYTE or STOP_BYTE
       0  DATA2 (if exists) UNCHANGED
bit2 = 1  DATA1 (if exists) WAS XORed with 1, IT WAS EQUAL TO START_BYTE or STOP_BYTE
       0  DATA1 (if exists) UNCHANGED
bit1bit0 = 0 to 3 NUMBER OF DATA BYTES SEND


CRC generation :
----------------
crc_send  = datalen ^ address;
crc_send ^= data[0];    // if exists
crc_send ^= data[1];    // if exists
crc_send ^= data[2];    // if exists
crc_send = ~crc_send;
if ((crc_send == START_BYTE) || (crc_send == STOP_BYTE))
   crc_send++;
  
