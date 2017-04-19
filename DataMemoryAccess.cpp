#include "memory.h"
#include "regfile.h"
void DataMemoryAccess(void)
{
	DM = EX;
	DM->DataMemoryAccess();
}
void Instruction::DataMemoryAccess(void)
{
	switch(opcode){
		case 0x23:
			MDR = load_data(ALUOut, 4);
			break;
		case 0x21:
			MDR = load_data(ALUOut, 2);
			MDR = (MDR << 16 ) >> 16;
			break;
		case 0x25:
			MDR = load_data(ALUOut, 2);
			break;
		case 0x20:
			MDR = load_data(ALUOut, 1);
			MDR = (MDR << 24) >> 24;
			break;
		case 0x24:
			MDR = load_data(ALUOut, 1);
			break;
		case 0x2b:
			save_data(ALUOut, 4, B);
			break;
		case 0x29:
			save_data(ALUOut, 2, B);
			break;
		case 0x28:
			save_data(ALUOut, 1, B);
			break;
	}
}
