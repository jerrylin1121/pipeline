#include "regfile.h"
#include "error.h"
void WriteBack(void)
{
	WB->End();
	delete WB;
	WB = DM;
	WB->WriteBack();
}
void Instruction::WriteBack(void)
{
	switch(opcode){
		case 0x00:
			switch(funct){
				case 0x00:
					if(!( rd==0 && rt==0 & C==0)){
						if(!write_reg0(rd)){
							if(reg_value[rd]!=ALUOut) show_set.insert(rd);
							reg_value[rd] = ALUOut;
						}
					reg_use[rd] = 3;
					}
				case 0x18: case 0x19: case 0x08:
					break;
				default:
					if(!write_reg0(rd)){
						if(reg_value[rd]!=ALUOut) show_set.insert(rd);
						reg_value[rd] = ALUOut;
					}
					reg_use[rd] = 3;
					break;
			}
			break;
		case 0x08: case 0x09: case 0x0f: case 0x0c: case 0x0d: case 0x0e: case 0x0a:
			if(!write_reg0(rt)){
				if(reg_value[rt]!=ALUOut) show_set.insert(rt);
				reg_value[rt] = ALUOut;
			}
			reg_use[rt] = 3;
			break;
		case 0x23: case 0x21: case 0x25: case 0x20: case 0x24:
			if(!write_reg0(rt)){
				if(reg_value[rt]!=MDR) show_set.insert(rt);
				reg_value[rt] = MDR;
			}
			reg_use[rt] = 3;
			break;
	}
}
void Instruction::End(void)
{
	switch(opcode){
		case 0x00:
			switch(funct){
				case 0x18: case 0x19: case 0x08:
					break;
				default:
					reg_use[rd] = 0;
					break;
			}
			break;
		case 0x08: case 0x09: case 0x0f: case 0x0c: case 0x0d: case 0x0e: case 0x0a:
			reg_use[rt] = 0;
			break;
		case 0x23: case 0x21: case 0x25: case 0x20: case 0x24:
			reg_use[rt] = 0;
			break;
	}
}
