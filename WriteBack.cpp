#include "regfile.h"
void WriteBack(void)
{
	WB = DM;
	WB->WriteBack();
}
void Instruction::WriteBack(void)
{
	switch(opcode){
		case 0x00:
			switch(funct){
				case 0x18: case 0x19: case 0x08:
					break;
				default:
					reg_value[rd] = ALUOut;
					break;
			}
			break;
		case 0x08: case 0x09: case 0x0f: case 0x0c: case 0x0d: case 0x0e: case 0x0a:
			reg_value[rt] = ALUOut;
			break;
		case 0x23: case 0x21: case 0x25: case 0x20: case 0x24:
			reg_value[rt] = MDR;
			break;
	}
}
