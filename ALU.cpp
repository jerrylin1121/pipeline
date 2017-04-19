#include "regfile.h"
void ALU(void)
{
	if(ID->stall){
		EX = new Instruction();
	}else{
		EX = ID;
		EX->ALU();
		string str;
		EX->out >> str;
		EX->out.str(str);
	}
}
void Instruction::ALU(void)
{
	int tmp, tmp1;
	long long int lli;
	unsigned long long int ulli;
	bool needA = false, needB = false;
	switch(opcode){
		case 0x00:
			switch(funct){
				case 0x10: case 0x12:
					break;
				case 0x00: case 0x02: case 0x03:
					needB = true;
					break;
				default:
					needA = true;
					needB = true;
					break;
			}
			break;
		case 0x08: case 0x09: case 0x23: case 0x21: case 0x25: case 0x20: case 0x24: case 0x2b: case 0x29: case 0x28: case 0x0c: case 0x0d: case 0x0e: case 0x0a:
			needA = true;
			break;
	}
	if(needA){
		if(reg_use[rs]==0 || reg_use[rs]==1){
			A = reg_value[rs];
		}else if(reg_use[rs]==2){
			if(DM->ALUReady){
				A = DM->ALUOut;
				out << " fwd_EX-DM_rs_$" << rs;
			}
		}else if(reg_use[rs]==3){
			if(WB->ALUReady){
				A = WB->ALUOut;
				out << " fwd_DM-WB_rs_$" << rs;
			}else if(WB->MDRReady){
				A = WB->MDR;
				out << " fwd_DM-WB_rs_$" << rs;
			}
		}
	}
	if(needB){
		if(reg_use[rt]==0 || reg_use[rt]==1){
			B = reg_value[rt];
		}else if(reg_use[rt]==2){
			if(DM->ALUReady){
				B = DM->ALUOut;
				out << " fwd_EX-DM_rt_$" << rt;
			}
		}else if(reg_use[rt]==3){
			if(WB->ALUReady){
				B = WB->ALUOut;
				out << " fwd_DM-WB_rt_$" << rt;
			}else if(WB->MDRReady){
				B = WB->MDR;
				out << " fwd_DM-WB_rt_$" << rt;
			}
		}
	}
	switch(opcode){
		case 0x00:
			switch(funct){
				case 0x20:
						ALUOut = A + B;
						ALUReady = true;
						reg_use[rd] = 1;
					break;
				case 0x21:
						ALUOut = A + B;
						ALUReady = true;
						reg_use[rd] = 1;
					break;
				case 0x22:
						ALUOut = A - B;
						ALUReady = true;
						reg_use[rd] = 1;
					break;
				case 0x24:
						ALUOut = A & B;
						ALUReady = true;
						reg_use[rd] = 1;
					break;
				case 0x25:
						ALUOut = A | B;
						ALUReady = true;
						reg_use[rd] = 1;
					break;
				case 0x26:
						ALUOut = A ^ B;
						ALUReady = true;
						reg_use[rd] = 1;
					break;
				case 0x27:
						ALUOut = ~(A | B);
						ALUReady = true;
						reg_use[rd] = 1;
					break;
				case 0x28:
						ALUOut = ~(A & B);
						ALUReady = true;
						reg_use[rd] = 1;
					break;
				case 0x2a:
						ALUOut = A < B;
						ALUReady = true;
						reg_use[rd] = 1;
					break;
				case 0x00:
						ALUOut = B << C;
						if(out.str()!="NOP"){
							ALUReady = true;
							reg_use[rd] = 1;
						}
					break;
				case 0x02:
						ALUOut = (unsigned int)B >> C;
						ALUReady = true;
						reg_use[rd] = 1;
					break;
				case 0x03:
						ALUOut = B >> C;
						ALUReady = true;
						reg_use[rd] = 1;
					break;
				case 0x18:
						tmp = reg_value[HI];
						tmp1 = reg_value[LO];
						lli  = (long long int)A * (long long int)B;
						reg_value[HI] = lli >> 32;
						reg_value[LO] = lli;
						if(tmp!=reg_value[HI]) show_set.insert(HI);
						if(tmp1!=reg_value[LO]) show_set.insert(LO);
					break;
				case 0x19:
						tmp = reg_value[HI];
						tmp1 = reg_value[LO];
						ulli  = (unsigned long long int)(unsigned int)A * (unsigned long long int)(unsigned int)B;
						reg_value[HI] = lli >> 32;
						reg_value[LO] = lli;
						if(tmp!=reg_value[HI]) show_set.insert(HI);
						if(tmp1!=reg_value[LO]) show_set.insert(LO);
					break;
				case 0x10:
						ALUOut = reg_value[HI];
						ALUReady = true;
						reg_use[rd] = 1;
					break;
				case 0x12:
						ALUOut = reg_value[LO];
						ALUReady = true;
						reg_use[rd] = 1;
					break;
			}
			break;
		case 0x08:
				ALUOut = A + C;
				ALUReady = true;
				reg_use[rt] = 1;
			break;
		case 0x09:
				ALUOut = A + C;
				ALUReady = true;
				reg_use[rt] = 1;
			break;
		case 0x23:
				ALUOut = A + C;
				reg_use[rt] = 1;
			break;
		case 0x21:
				ALUOut = A + C;
				reg_use[rt] = 1;
			break;
		case 0x25:
				ALUOut = A + C;
				reg_use[rt] = 1;
			break;
		case 0x20:
				ALUOut = A + C;
				reg_use[rt] = 1;
			break;
		case 0x24:
				ALUOut = A + C;
				reg_use[rt] = 1;
			break;
		case 0x2b:
				ALUOut = A + C;
			break;
		case 0x29:
				ALUOut = A + C;
			break;
		case 0x28:
				ALUOut = A + C;
			break;
		case 0x0f:
				ALUOut = A << C;
				ALUReady = true;
				reg_use[rt] = 1;
			break;
		case 0x0c:
				ALUOut = A & C;
				ALUReady = true;
				reg_use[rt] = 1;
			break;
		case 0x0d:
				ALUOut = A | C;
				ALUReady = true;
				reg_use[rt] = 1;
			break;
		case 0x0e:
				ALUOut = ~(A | C);
				ALUReady = true;
				reg_use[rt] = 1;
			break;
		case 0x0a:
				ALUOut = A < C;
				ALUReady = true;
				reg_use[rt] = 1;
			break;
	}
}
