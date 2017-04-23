#include "library.h"

void DataMemoryAccess(void)
{
	DM = EX;
	DM->DataMemoryAccess();
	string str;
	DM->out >> str;
	DM->out.str("");
	DM->out.clear();
	DM->out << str;
}
void Instruction::DataMemoryAccess(void)
{
	switch(opcode){
		case 0x00:
			switch(funct){
				case 0x00:
					if(!(rs==0 && rt==0 && C==0)){
						reg_use[rd] = 2;
					}
				case 0x08: case 0x18: case 0x19:
					break;
				default:
					reg_use[rd] = 2;
					break;
			}
	}
	switch(opcode){
		case 0x08: case 0x09: case 0x0f: case 0x0c: case 0x0d: case 0x0e: case 0x0a:
			reg_use[rt] = 2;
			break;
		case 0x23:
			MDR = load_data(ALUOut, 4);
			MDRReady = true;
			reg_use[rt] = 2;
			break;
		case 0x21:
			MDR = load_data(ALUOut, 2);
			MDR = (MDR << 16 ) >> 16;
			MDRReady = true;
			reg_use[rt] = 2;
			break;
		case 0x25:
			MDR = load_data(ALUOut, 2);
			MDRReady = true;
			reg_use[rt] = 2;
			break;
		case 0x20:
			MDR = load_data(ALUOut, 1);
			MDR = (MDR << 24) >> 24;
			MDRReady = true;
			reg_use[rt] = 2;
			break;
		case 0x24:
			MDR = load_data(ALUOut, 1);
			MDRReady = true;
			reg_use[rt] = 2;
			break;
		case 0x2b:
			save_data(ALUOut, 4, reg_value[rt]);
			break;
		case 0x29:
			save_data(ALUOut, 2, reg_value[rt]);
			break;
		case 0x28:
			save_data(ALUOut, 1, reg_value[rt]);
			break;
		case 0x03:
			reg_use[31] = 2;
			break;
	}
}
