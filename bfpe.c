#include <stdio.h>
#include "bfpp.h"

int main(int argc, char * * argv)
{
	FILE *f;
	int i;
	bfpp_program program;

	if (argc < 2)
	{
		printf("Usage: %s [program]\n", argv[0]);
		return 1;
	}

	if ((f = fopen(argv[1], "r")) == NULL)
	{
		printf("File open error\n");
		return 2;
	}

	size_t read_in = fread(&program, sizeof(bfpp_program), 1, f);
	fclose(f);


	unsigned int *dp = &program.dp;
	unsigned short *data = program.data;
	unsigned int global_dp;
	unsigned short global_data[BFPP_PRO_DATASIZE];
	for (i = 0; i < 0xFF; i++)
	{
		switch (program.code[i].operator)
		{
			case OP_INC:
				data[*dp]++;
				break;
			case OP_DEC:
				data[*dp]--;
				break;
			case OP_IDP:
				*dp = *dp + 1;
				break;
			case OP_DDP:
				*dp = *dp - 1;
				break;
			case OP_RIN:
				data[*dp] = getchar();
				break;
			case OP_OUT:
				printf("%c", data[*dp]);
				fflush(stdout);
				break;
			case OP_JIZ:
				if (data[*dp] == 0)
				{
					program.pc = program.code[i].operand;
					break;
				}
				break;
			case OP_JMP:
				if (data[*dp])
				{
					program.pc = program.code[i].operand;
					break;
				}
				break;
			case OP_CLL: break; //IMPLEMENT LATER
			case OP_GLB:
				dp = &global_dp;
				data = global_data;
				break;
			case OP_LCL:
				dp = &program.dp;
				data = program.data;
			default: break;
		}
	}
}
