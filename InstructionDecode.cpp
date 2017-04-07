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
	ID.str("");
	unsigned int in = stol(IF.str(),nullptr,0);
	cout << hex << in << endl;
	unsigned int opcode = in >> 26;
	unsigned int rs = (in << 6) >> 27;
	unsigned int rt = (in << 11) >> 27;
	unsigned int rd = (in << 16) >> 27;
	unsigned int funct = (in << 26) >> 26;
	int C=(in << 16)>>16;
	long long int lli=0;
	unsigned long long int ulli=0;
	int tmp, tmp1;
	switch(opcode){
		//R-type Instructions
		case 0x00:
//			snap << "R-type Instructions" << endl;
			C = (in << 21) >> 27;
			switch(funct){
				case 0x20:
//					snap << "add $" << rd << " $" << rs << " $" << rt << endl;
					ID << "ADD";
					break;
				case 0x21:
//					snap << "addu $" << rd << " $" << rs << " $" << rt << endl;
					ID << "ADDU";
					break;
				case 0x22:
//					snap << "sub $" << rd << " $" << rs << " $" << rt << endl;
					ID << "SUB";
					break;
				case 0x24:
//					snap << "and $" << rd << " $" << rs << " $" << rt << endl;
					ID << "AND";
					break;
				case 0x25:
//					snap << "or $" << rd << " $" << rs << " $" << rt << endl;
					ID << "OR";
					break;
				case 0x26:
//					snap << "xor $" << rd << " $" << rs << " $" << rt << endl;
					ID << "XOR";
					break;
				case 0x27:
//					snap << "nor $" << rd << " $" << rs << " $" << rt << endl;
					ID << "NOR";
					break;
				case 0x28:
//					snap << "nand $" << rd << " $" << rs << " $" << rt << endl;
					ID << "NAND";
					break;
				case 0x2a:
//					snap << "slt $" << rd << " $" << rs << " $" << rt << endl;
					ID << "SLT";
					break;
				case 0x00:
//					snap << "sll $" << rd << " $" << rt << " " << setfill('0') << setw(4) << hex << C << endl;
					if(rt==0 && rd==0 && C==0){
						ID << "NOP";
					}else{
						ID << "SLL";
					}
					break;
				case 0x02:
//					snap << "srl $" << rd << " $" << rt << " " << setfill('0') << setw(4) << hex << C << endl;
					ID << "SRL";
					break;
				case 0x03:
//					snap << "sra $" << rd << " $" << rs << " " << setfill('0') << setw(4) << hex<< C << endl;
					ID << "SRA";
					break;
				case 0x08:
//					snap << "jr $" << rs << endl;
					ID << "JR";
					break;
				case 0x19:
//					snap << "multu $" << rs << " $" << rt << endl;
					ID << "MULTU";
					break;
				case 0x10:
//					snap << "mfhi $" << rd << endl;
					ID << "MFHI";
					break;
				case 0x12:
//					snap << "mflo $" << rd << endl;
					ID << "MFLO";
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
			ID << "ADDI";
			C = (C << 16) >> 16;
			break;
		case 0x09:
//			snap << "addiu $" << rt << " $" << rs << " " << setfill('0') << setw(4) << hex << C << endl;
			ID << "ADDIU";
			C = (C << 16) >> 16;
			break;
		case 0x23:
//			snap << "lw $" << rt << " " << setfill('0') << setw(4) << hex << C << "($" << rs << ")" << endl;
			ID << "LW";
			C = (C << 16) >> 16;
			break;
		case 0x21:
//			snap << "lh $" << rt << " " << setfill('0') << setw(4) << hex << C << "($" << rs << ")" << endl;
			ID << "LH";
			C = (C << 16) >> 16;
			break;
		case 0x25:
//	  		snap << "lhu $" << rt << " " << setfill('0') << setw(4) << hex << C << "($" << rs << ")" << endl;
			ID << "LHU";
			C = (C << 16) >> 16;
			break;
		case 0x20:
//	  		snap << "lb $" << rt << " " << setfill('0') << setw(4) << hex << C << "($" << rs << ")" << endl;
			ID << "LB";
			C = (C << 16) >> 16;
			break;
		case 0x24:
//			snap << "lbu $" << rt << " " << setfill('0') << setw(4) << hex << C << "($" << rs << ")" << endl;
			ID << "LBU";
			C = (C << 16) >> 16;
			break;
		case 0x2b:
//			snap << "sw $" << rt << " " << setfill('0') << setw(4) << hex << C << "($" << rs << ")" << endl;
			ID << "SW";
			C = (C << 16) >> 16;
			break;
		case 0x29:
//			snap << "sh $" << rt << " " << setfill('0') << setw(4) << hex << C << "($" << rs << ")" << endl;
			ID << "SH";
			C = (C << 16) >> 16;
			break;
		case 0x28:
//			snap << "sb $" << rt << " " << setfill('0') << setw(4) << hex << C << "($" << rs << ")" << endl;
			ID << "SB";
			C = (C << 16) >> 16;
			break;
		case 0x0f:
//			snap << "lui $" << rt << " " << setfill('0') << setw(4) << hex << C << endl;
			ID << "LUI";
			break;
		case 0x0c:
//			snap << "andi $" << rt << " $" << rs << " " << setfill('0') << setw(4) << hex << C << endl;
			ID << "ANDI";
			break;
		case 0x0d:
//			snap << "ori $" << rt << " $" << rs << " " << setfill('0') << setw(4) << hex << C << endl;
			ID << "ORI";
			break;
		case 0x0e:
//			snap << "nori $" << rt << " $" << rs << " " << setfill('0') << setw(4) << hex << C << endl;
			ID << "NORI";
			break;
		case 0x0a:
//			snap << "slti $" << rt << " $" << rs << " " << setfill('0') << setw(4) << hex << C << endl;
			ID << "SLTI";
			C = (C << 16) >> 16;
			break;
		case 0x04:
//			snap << "beq $" << rs << " $" << rt << " " << setfill('0') << setw(4) << hex << C << endl;
			ID << "BEQ";
			C = (C << 16) >> 16;
			break;
		case 0x05:
//			snap << "bne $" << rs << " $" << rt << " " << setfill('0') << setw(4) << hex << C << endl;
			ID << "BNE";
			C = (C << 16) >> 16;
			break;
		case 0x07:
//			snap << "bgtz $" << rs << " " << setfill('0') << setw(4) << hex << C << endl;
			ID << "BGTZ";
			C = (C << 16) >> 16;
			break;
		//J-type Instructions
		case 0x02:
//			snap << "j " << setfill('0') << setw(4) << hex << C << endl;
			ID << "J";
			C = (in << 6) >> 6;
			break;
		case 0x03:
//			snap << "jal " << setfill('0') << setw(4) << hex << C << endl;
			ID << "JAL";
			C = (in << 6) >> 6;
			break;
		//Specialized Instruction
		case 0x3f:
//			snap << "halt" << endl;
			ID << "HALT";
			exit(0);
			break;
		//illegal Instructions
		default:
//			snap << "illegal" << endl;
			cout << "illegal instruction found at 0x" << setfill('0') << setw(8) << hex << uppercase << reg_value[PC]-4 << endl;
			exit(0);
			break;
	}
}
