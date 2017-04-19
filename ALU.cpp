#include "regfile.h"
void ALU(void)
{
	EX = ID;
	EX->ALU();
}
void Instruction::ALU(void)
{
	int tmp, tmp1;
	long long int lli;
	unsigned long long int ulli;
	switch(opcode){
		case 0x00:
			switch(funct){
				case 0x20:
						ALUOut = A + B;
					break;
				case 0x21:
						ALUOut = A + B;
					break;
				case 0x22:
						ALUOut = A - B;
					break;
				case 0x24:
						ALUOut = A & B;
					break;
				case 0x25:
						ALUOut = A | B;
					break;
				case 0x26:
						ALUOut = A ^ B;
					break;
				case 0x27:
						ALUOut = ~(A | B);
					break;
				case 0x28:
						ALUOut = ~(A & B);
					break;
				case 0x2a:
						ALUOut = A < B;
					break;
				case 0x00:
						ALUOut = B << C;
					break;
				case 0x02:
						ALUOut = (unsigned int)B >> C;
					break;
				case 0x03:
						ALUOut = B >> C;
					break;
				case 0x08:
						reg_value[PC] = A;
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
					break;
				case 0x12:
						ALUOut = reg_value[LO];
					break;
			}
			break;
		case 0x08:
				ALUOut = A + C;
			break;
		case 0x09:
				ALUOut = A + C;
			break;
		case 0x23:
				ALUOut = A + C;
			break;
		case 0x21:
				ALUOut = A + C;
			break;
		case 0x25:
				ALUOut = A + C;
			break;
		case 0x20:
				ALUOut = A + C;
			break;
		case 0x24:
				ALUOut = A + C;
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
			break;
		case 0x0c:
				ALUOut = A & C;
			break;
		case 0x0d:
				ALUOut = A | C;
			break;
		case 0x0e:
				ALUOut = ~(A | C);
			break;
		case 0x0a:
				ALUOut = A < C;
			break;
		case 0x04:
				if(A==B){
					ALUOut = reg_value[PC] + 4*C;
					reg_value[PC] = ALUOut;
				}
			break;
		case 0x05:
				if(A!=B){
					ALUOut = reg_value[PC] + 4*C;
					reg_value[PC] = ALUOut;
				}
			break;
		case 0x07:
				if(A>0){
					ALUOut = reg_value[PC] + 4*C;
					reg_value[PC] = ALUOut;
				}
			break;
		case 0x02:
				reg_value[PC] = (reg_value[PC] & 0xf0000000) | (4*C);
			break;
		case 0x03:
				ALUOut = reg_value[PC];
				reg_value[PC] = (reg_value[PC] & 0xf0000000) | (4*C);
			break;
	}
}
