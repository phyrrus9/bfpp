#ifndef __BFPP_H__
#define __BFPP_H__

#define OP_NUL  0x00
#define OP_INC  0x01
#define OP_DEC  0x02
#define OP_IDP  0x03
#define OP_DDP  0x04
#define OP_RIN  0x05
#define OP_OUT  0x06
#define OP_JIZ  0x07
#define OP_JMP  0x08
#define OP_CLL  0x09
#define OP_GLB  0x0A
#define OP_LCL  0x0B
#define OP_PUS  0x0C
#define OP_POP  0x0D

#define BFPP_INS_DATASIZE 1
#define BFPP_PRO_CODESIZE 0xFF
#define BFPP_PRO_DATASIZE 0xFFFF

typedef struct __bfpp_instruction
{
	unsigned char operator;
	unsigned int  operand;
	char          data[BFPP_INS_DATASIZE];
} bfpp_instruction;

typedef struct __bfpp_program
{
	bfpp_instruction code[BFPP_PRO_CODESIZE];
	unsigned short   data[BFPP_PRO_DATASIZE];
	unsigned int     dp;
	unsigned short   pc;
} bfpp_program;

#endif
