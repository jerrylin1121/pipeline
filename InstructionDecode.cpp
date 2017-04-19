#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <string>
#include "InstructionDecode.h"
#include "memory.h"
#include "regfile.h"
#include "error.h"
using namespace std;
extern fstream snap;
void InstructionDecode(void)
{
	if(!ID->stall)
		ID = IF;
	ID->stall = false;
	ID->InstructionDecode();
	if(ID->stall){
		ID->out << " to_be_stalled";
		IF->stall = true;
	}
}
void Instruction::InstructionDecode(void)
{
	out.str("");
	bool needA = false, needB = false;
	switch(opcode){
		//R-type Instructions
		case 0x00:
			C = (instruction & 0x000007c0) >> 6;
//			snap << "R-type Instructions" << endl;
			switch(funct){
				case 0x20:
//					snap << "add $" << rd << " $" << rs << " $" << rt << endl;
					out << "ADD";
					if(reg_use[rd]==0) reg_use[rd] = 1;
					needA = true;
					needB = true;
					break;
				case 0x21:
//					snap << "addu $" << rd << " $" << rs << " $" << rt << endl;
					out << "ADDU";
					if(reg_use[rd]==0) reg_use[rd] = 1;
					needA = true;
					needB = true;
					break;
				case 0x22:
//					snap << "sub $" << rd << " $" << rs << " $" << rt << endl;
					out << "SUB";
					if(reg_use[rd]==0) reg_use[rd] = 1;
					needA = true;
					needB = true;
					break;
				case 0x24:
//					snap << "and $" << rd << " $" << rs << " $" << rt << endl;
					out << "AND";
					if(reg_use[rd]==0) reg_use[rd] = 1;
					needA = true;
					needB = true;
					break;
				case 0x25:
//					snap << "or $" << rd << " $" << rs << " $" << rt << endl;
					out << "OR";
					if(reg_use[rd]==0) reg_use[rd] = 1;
					needA = true;
					needB = true;
					break;
				case 0x26:
//					snap << "xor $" << rd << " $" << rs << " $" << rt << endl;
					out << "XOR";
					if(reg_use[rd]==0) reg_use[rd] = 1;
					needA = true;
					needB = true;
					break;
				case 0x27:
//					snap << "nor $" << rd << " $" << rs << " $" << rt << endl;
					out << "NOR";
					if(reg_use[rd]==0) reg_use[rd] = 1;
					needA = true;
					needB = true;
					break;
				case 0x28:
//					snap << "nand $" << rd << " $" << rs << " $" << rt << endl;
					out << "NAND";
					if(reg_use[rd]==0) reg_use[rd] = 1;
					needA = true;
					needB = true;
					break;
				case 0x2a:
//					snap << "slt $" << rd << " $" << rs << " $" << rt << endl;
					out << "SLT";
					if(reg_use[rd]==0) reg_use[rd] = 1;
					needA = true;
					needB = true;
					break;
				case 0x00:
//					snap << "sll $" << rd << " $" << rt << " " << setfill('0') << setw(4) << hex << C << endl;
					if(!rd & !rt & !C){
						out << "NOP";
					}else{
						out << "SLL";
						if(reg_use[rd]==0) reg_use[rd] = 1;
						needB = true;
					}
					break;
				case 0x02:
//					snap << "srl $" << rd << " $" << rt << " " << setfill('0') << setw(4) << hex << C << endl;
					out << "SRL";
					if(reg_use[rd]==0) reg_use[rd] = 1;
					needB = true;
					break;
				case 0x03:
//					snap << "sra $" << rd << " $" << rs << " " << setfill('0') << setw(4) << hex<< C << endl;
					out << "SRA";
					if(reg_use[rd]==0) reg_use[rd] = 1;
					needB = true;
					break;
				case 0x08:
//					snap << "jr $" << rs << endl;
					out << "JR";
					needA = true;
					break;
				case 0x18:
//					snap << "mult $" << rs << " $" << rt << endl;
					out << "MULT";
					needA = true;
					needB = true;
					break;
				case 0x19:
//					snap << "multu $" << rs << " $" << rt << endl;
					out << "MULTU";
					needA = true;
					needB = true;
					break;
				case 0x10:
//					snap << "mfhi $" << rd << endl;
					out << "MFHI";
					if(reg_use[rd]==0) reg_use[rd] = 1;
					break;
				case 0x12:
//					snap << "mflo $" << rd << endl;
					out << "MFLO";
					if(reg_use[rd]==0) reg_use[rd] = 1;
					break;
				default:
//					snap << "illegal" << endl;
					cout << "illegal instruction found at 0x" << setfill('0') << setw(8) << hex << uppercase << reg_value[PC]-4 << endl;;
					exit(0);
					break;
			}
			break;
		//I-type Instructions
		case 0x08:
//			snap << "addi $" << rt << " $" << rs << " " << setfill('0') << setw(4) << hex << C << endl;
			out << "ADDI";
			C = (C<<16)>>16;
			if(reg_use[rt]==0) reg_use[rt] = 1;
			needA = true;
			break;
		case 0x09:
//			snap << "addiu $" << rt << " $" << rs << " " << setfill('0') << setw(4) << hex << C << endl;
			out << "ADDIU";
			C = (C<<16)>>16;
			if(reg_use[rt]==0) reg_use[rt] = 1;
			needA = true;
			break;
		case 0x23:
//			snap << "lw $" << rt << " " << setfill('0') << setw(4) << hex << C << "($" << rs << ")" << endl;
			out << "LW";
			C = (C<<16)>>16;
			if(reg_use[rt]==0) reg_use[rt] = 1;
			needA = true;
			break;
		case 0x21:
//			snap << "lh $" << rt << " " << setfill('0') << setw(4) << hex << C << "($" << rs << ")" << endl;
			out << "LH";
			C = (C<<16)>>16;
			if(reg_use[rt]==0) reg_use[rt] = 1;
			needA = true;
			break;
		case 0x25:
//	  		snap << "lhu $" << rt << " " << setfill('0') << setw(4) << hex << C << "($" << rs << ")" << endl;
			out << "LHU";
			C = (C<<16)>>16;
			if(reg_use[rt]==0) reg_use[rt] = 1;
			needA = true;
			break;
		case 0x20:
//	  		snap << "lb $" << rt << " " << setfill('0') << setw(4) << hex << C << "($" << rs << ")" << endl;
			out << "LB";
			C = (C<<16)>>16;
			if(reg_use[rt]==0) reg_use[rt] = 1;
			needA = true;
			break;
		case 0x24:
//			snap << "lbu $" << rt << " " << setfill('0') << setw(4) << hex << C << "($" << rs << ")" << endl;
			out << "LBU";
			C = (C<<16)>>16;
			if(reg_use[rt]==0) reg_use[rt] = 1;
			needA = true;
			break;
		case 0x2b:
//			snap << "sw $" << rt << " " << setfill('0') << setw(4) << hex << C << "($" << rs << ")" << endl;
			out << "SW";
			C = (C<<16)>>16;
			needA = true;
			break;
		case 0x29:
//			snap << "sh $" << rt << " " << setfill('0') << setw(4) << hex << C << "($" << rs << ")" << endl;
			out << "SH";
			C = (C<<16)>>16;
			needA = true;
			break;
		case 0x28:
//			snap << "sb $" << rt << " " << setfill('0') << setw(4) << hex << C << "($" << rs << ")" << endl;
			out << "SB";
			C = (C<<16)>>16;
			needA = true;
			break;
		case 0x0f:
//			snap << "lui $" << rt << " " << setfill('0') << setw(4) << hex << C << endl;
			out << "LUI";
			if(reg_use[rt]==0) reg_use[rt] = 1;
			break;
		case 0x0c:
//			snap << "andi $" << rt << " $" << rs << " " << setfill('0') << setw(4) << hex << C << endl;
			out << "ANDI";
			if(reg_use[rt]==0) reg_use[rt] = 1;
			needA = true;
			break;
		case 0x0d:
//			snap << "ori $" << rt << " $" << rs << " " << setfill('0') << setw(4) << hex << C << endl;
			out << "ORI";
			if(reg_use[rt]==0) reg_use[rt] = 1;
			needA = true;
			break;
		case 0x0e:
//			snap << "nori $" << rt << " $" << rs << " " << setfill('0') << setw(4) << hex << C << endl;
			out << "NORI";
			if(reg_use[rt]==0) reg_use[rt] = 1;
			needA = true;
			break;
		case 0x0a:
//			snap << "slti $" << rt << " $" << rs << " " << setfill('0') << setw(4) << hex << C << endl;
			out << "SLTI";
			C = (C<<16)>>16;
			if(reg_use[rt]==0) reg_use[rt] = 1;
			needA = true;
			break;
		case 0x04:
//			snap << "beq $" << rs << " $" << rt << " " << setfill('0') << setw(4) << hex << C << endl;
			out << "BEQ";
			C = (C<<16)>>16;
			needA = true;
			needB = true;
			break;
		case 0x05:
//			snap << "bne $" << rs << " $" << rt << " " << setfill('0') << setw(4) << hex << C << endl;
			out << "BNE";
			C = (C<<16)>>16;
			needA = true;
			needB = true;
			break;
		case 0x07:
//			snap << "bgtz $" << rs << " " << setfill('0') << setw(4) << hex << C << endl;
			out << "BGTZ";
			C = (C<<16)>>16;
			needA = true;
			break;
		//J-type Instructions
		case 0x02:
//			snap << "j " << setfill('0') << setw(4) << hex << C << endl;
			out << "J";
			C = (C<<6)>>6;
			break;
		case 0x03:
//			snap << "jal " << setfill('0') << setw(4) << hex << C << endl;
			out << "JAL";
			C = (C<<6)>>6;
			break;
		//Specialized Instruction
		case 0x3f:
//			snap << "halt" << endl;
			out << "HALT";
			break;
		//illegal Instructions
		default:
//			snap << "illegal" << endl;
			cout << "illegal instruction found at 0x" << setfill('0') << setw(8) << hex << uppercase << reg_value[PC]-4 << endl;
			exit(0);
			break;
	}
	if(needA){
		switch(opcode){
			case 0x00:
				if(funct==0x08){
					if(reg_use[rs]==0 || reg_use[rs]==3){
						A = reg_value[rs];
					}else if(reg_use[rs]==2){
						if(DM->ALUReady){
							A = DM->ALUOut;
							out << " fwd_EX-DM_rs_$" << rs;
						}else{
							stall = true;
							return;
						}
					}else{
						stall = true;
						return;
					}
				}
				break;
			case 0x04: case 0x05: case 0x07:
				if(reg_use[rs]==0 || reg_use[rs]==3){
					A = reg_value[rs];
				}else if(reg_use[rs]==2){
					if(DM->ALUReady){
						A = DM->ALUOut;
						out << " fwd_EX-DM_rs_$" << rs;
					}else{
						stall = true;
						return;
					}
				}else{
					stall = true;
					return;
				}
				break;
			default:
				if(reg_use[rs]==2){
					if(!EX->ALUReady)
						stall = true;
						return;
				}
				break;
		}
	}
	if(needB){
		switch(opcode){
			case 0x00:
				if(funct==0x08){
					if(reg_use[rt]==0 || reg_use[rt]==3){
						B = reg_value[rt];
					}else if(reg_use[rt]==2){
						if(DM->ALUReady){
							B = DM->ALUOut;
							out << " fwd_EX-DM_rt_$" << rt;
						}else{
							stall = true;
							return;
						}
					}else{
						stall = true;
						return;
					}
				}
				break;
			case 0x04: case 0x05: case 0x07:
				if(reg_use[rt]==0){
					B = reg_value[rt];
				}else if(reg_use[rt]==2){
					if(DM->ALUReady){
						B = ALUOut;
						out << " fwd_EX-DM_rt_$" << rt;
					}else{
						stall = true;
						return;
					}
				}else{
					stall = true;
					return;
				}
				break;
			default:
				if(reg_use[rt]==2){
					if(!EX->ALUReady)
						stall = true;
						return;
				}
				break;
		}
	}
	switch(opcode){
		case 0x00:
			if(funct==0x08){
				reg_value[PC] = A;
			}
			break;
		case 0x08:
			if(A==B){
				reg_value[PC] = reg_value[PC] + 4*C;
			}
			break;
		case 0x09:
			if(A!=B){
				reg_value[PC] = reg_value[PC] + 4*C;
			}
			break;
		case 0x07:
			if(A>0){
				reg_value[PC] = reg_value[PC] + 4*C;
			}
			break;
		case 0x02:
			reg_value[PC] = (PC&0xf0000000) | 4*C;
			break;
		case 0x03:
			reg_value[PC] = (PC&0xf0000000) | 4*C;
	}
}
