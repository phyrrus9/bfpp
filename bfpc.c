#include <stdio.h>
#include "bfpp.h"

#define ERR_ARGS 1
#define ERR_FILE 2

#define PUSH(a) stack[sp++] = a
#define POP()   stack[--sp]

int main(int argc, char * * argv) //infile=argv[1] outfile=argv[2]
{
	FILE *infile;
	FILE *outfile;
	bfpp_program program;
	int i, x;
	char tmp;
	int string_ptr = 0;
	unsigned short stack[0xFF];
	unsigned int sp = 0;

	if (argc < 3)
	{
		printf("Usage: %s [infile] [outfile]\n", argv[0]);
		return ERR_ARGS;
	}
	if ((infile = fopen(argv[1], "r")) == NULL || (outfile = fopen(argv[2], "w")) == NULL)
	{
		printf("Error, cannot open one of the files\n");
		return ERR_FILE;
	}

	//zero the code block
	for (i = 0; i < BFPP_PRO_CODESIZE; i++)
	{
		program.code[i].operator = OP_NUL;
		program.code[i].operand  = 0;
		for (x = 0; x < BFPP_INS_DATASIZE; x++)
		{
			program.code[i].data[x] = 0;
		}
	}

	//zero the data block
	for (i = 0; i < BFPP_PRO_DATASIZE; i++)
	{
		program.data[i] = 0;
	}

	//zero the rest of the program
	program.dp = 0;
	program.pc = 0;

	//bagin compiling
	while (fscanf(infile, "%c", &tmp) != EOF)
	{
		switch (tmp)
		{
			case '+':
				program.code[program.pc++].operator = OP_INC;
				break;
			case '-':
				program.code[program.pc++].operator = OP_DEC;
				break;
			case '<':
				program.code[program.pc++].operator = OP_DDP;
				break;
			case '>':
				program.code[program.pc++].operator = OP_IDP;
				break;
			case '.':
				program.code[program.pc++].operator = OP_OUT;
				break;
			case ',':
				program.code[program.pc++].operator = OP_RIN;
				break;
			case '[':
				program.code[program.pc].operator = OP_JIZ;
				PUSH(program.pc);
				program.pc++;
				break;
			case ']':
				program.code[program.pc].operator = OP_JMP;
				program.code[program.pc].operand  = POP();
				program.code[program.code[program.pc].operand].operand = program.pc;
				break;
			case 'S':
				program.code[program.pc++].operator = OP_GLB;
				break;
			case 's':
				program.code[program.pc++].operator = OP_LCL;
				break;
			case 'P':
				program.code[program.pc++].operator = OP_PUS;
				break;
			case 'p':
				program.code[program.pc++].operator = OP_POP;
				break;
			case 'C':
				program.code[program.pc].operator = OP_CLL;
				string_ptr = 0;
				while (fscanf(infile, "%c", &tmp) != EOF)
				{
					if (tmp == 'C')
						break;
					program.code[program.pc].data[string_ptr++] = tmp;
				}
				program.code[program.pc].data[string_ptr] = 0;
				program.pc++;
				break;
			case ';':
				while (fscanf(infile, "%c", &tmp) != EOF)
				{
					if (tmp == ';')
						break;
				}
				break;
			default: break;
		}
	}
	fwrite(&program, sizeof(bfpp_program), 1, outfile);
	fclose(infile);
	fflush(outfile);
	fclose(outfile);
}
