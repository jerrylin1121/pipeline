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
	ID = IF;
	ID->InstructionDecode();
}
void Instruction::InstructionDecode(void)
{
	out.str("");
	switch(opcode){
		//R-type Instructions
		case 0x00:
//			snap << "R-type Instructions" << endl;
			switch(funct){
				case 0x20:
//					snap << "add $" << rd << " $" << rs << " $" << rt << endl;
					out << "ADD";
					break;
				case 0x21:
//					snap << "addu $" << rd << " $" << rs << " $" << rt << endl;
					out << "ADDU";
					break;
				case 0x22:
//					snap << "sub $" << rd << " $" << rs << " $" << rt << endl;
					out << "SUB";
					break;
				case 0x24:
//					snap << "and $" << rd << " $" << rs << " $" << rt << endl;
					out << "AND";
					break;
				case 0x25:
//					snap << "or $" << rd << " $" << rs << " $" << rt << endl;
					out << "OR";
					break;
				case 0x26:
//					snap << "xor $" << rd << " $" << rs << " $" << rt << endl;
					out << "XOR";
					break;
				case 0x27:
//					snap << "nor $" << rd << " $" << rs << " $" << rt << endl;
					out << "NOR";
					break;
				case 0x28:
//					snap << "nand $" << rd << " $" << rs << " $" << rt << endl;
					out << "NAND";
					break;
				case 0x2a:
//					snap << "slt $" << rd << " $" << rs << " $" << rt << endl;
					out << "SLT";
					break;
				case 0x00:
//					snap << "sll $" << rd << " $" << rt << " " << setfill('0') << setw(4) << hex << C << endl;
					if(!rd & !rt & !C){
						out << "NOP";
					}else{
						out << "SLL";
					}
					break;
				case 0x02:
//					snap << "srl $" << rd << " $" << rt << " " << setfill('0') << setw(4) << hex << C << endl;
					out << "SRL";
					break;
				case 0x03:
//					snap << "sra $" << rd << " $" << rs << " " << setfill('0') << setw(4) << hex<< C << endl;
					out << "SRA";
					break;
				case 0x08:
//					snap << "jr $" << rs << endl;
					out << "JR";
					break;
				case 0x19:
//					snap << "multu $" << rs << " $" << rt << endl;
					out << "MULTU";
					break;
				case 0x10:
//					snap << "mfhi $" << rd << endl;
					out << "MFHI";
					break;
				case 0x12:
//					snap << "mflo $" << rd << endl;
					out << "MFLO";
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
			break;
		case 0x09:
//			snap << "addiu $" << rt << " $" << rs << " " << setfill('0') << setw(4) << hex << C << endl;
			out << "ADDIU";
			break;
		case 0x23:
//			snap << "lw $" << rt << " " << setfill('0') << setw(4) << hex << C << "($" << rs << ")" << endl;
			out << "LW";
			break;
		case 0x21:
//			snap << "lh $" << rt << " " << setfill('0') << setw(4) << hex << C << "($" << rs << ")" << endl;
			out << "LH";
			break;
		case 0x25:
//	  		snap << "lhu $" << rt << " " << setfill('0') << setw(4) << hex << C << "($" << rs << ")" << endl;
			out << "LHU";
			break;
		case 0x20:
//	  		snap << "lb $" << rt << " " << setfill('0') << setw(4) << hex << C << "($" << rs << ")" << endl;
			out << "LB";
			break;
		case 0x24:
//			snap << "lbu $" << rt << " " << setfill('0') << setw(4) << hex << C << "($" << rs << ")" << endl;
			out << "LBU";
			break;
		case 0x2b:
//			snap << "sw $" << rt << " " << setfill('0') << setw(4) << hex << C << "($" << rs << ")" << endl;
			out << "SW";
			break;
		case 0x29:
//			snap << "sh $" << rt << " " << setfill('0') << setw(4) << hex << C << "($" << rs << ")" << endl;
			out << "SH";
			break;
		case 0x28:
//			snap << "sb $" << rt << " " << setfill('0') << setw(4) << hex << C << "($" << rs << ")" << endl;
			out << "SB";
			break;
		case 0x0f:
//			snap << "lui $" << rt << " " << setfill('0') << setw(4) << hex << C << endl;
			out << "LUI";
			break;
		case 0x0c:
//			snap << "andi $" << rt << " $" << rs << " " << setfill('0') << setw(4) << hex << C << endl;
			out << "ANDI";
			break;
		case 0x0d:
//			snap << "ori $" << rt << " $" << rs << " " << setfill('0') << setw(4) << hex << C << endl;
			out << "ORI";
			break;
		case 0x0e:
//			snap << "nori $" << rt << " $" << rs << " " << setfill('0') << setw(4) << hex << C << endl;
			out << "NORI";
			break;
		case 0x0a:
//			snap << "slti $" << rt << " $" << rs << " " << setfill('0') << setw(4) << hex << C << endl;
			out << "SLTI";
			break;
		case 0x04:
//			snap << "beq $" << rs << " $" << rt << " " << setfill('0') << setw(4) << hex << C << endl;
			out << "BEQ";
			break;
		case 0x05:
//			snap << "bne $" << rs << " $" << rt << " " << setfill('0') << setw(4) << hex << C << endl;
			out << "BNE";
			break;
		case 0x07:
//			snap << "bgtz $" << rs << " " << setfill('0') << setw(4) << hex << C << endl;
			out << "BGTZ";
			break;
		//J-type Instructions
		case 0x02:
//			snap << "j " << setfill('0') << setw(4) << hex << C << endl;
			out << "J";
			break;
		case 0x03:
//			snap << "jal " << setfill('0') << setw(4) << hex << C << endl;
			out << "JAL";
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
}
