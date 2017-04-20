#include <iostream>
#include <iomanip>
#include "memory.h"
#include "regfile.h"

using namespace std;
void InstructionFetch()
{
	if(ID->stall){
		if(ID==IF){
			reg_value[PC] += 4;
			IF = new Instruction(ins_mem[(reg_value[PC])/4]);
			IF->out << "0x" << setfill('0') << setw(8) << hex << uppercase << ins_mem[(reg_value[PC]/4)] << " to_be_stalled";
			IF->stall = true;
		}
	}else if(IF->stall){
		string str;
		IF->out >> str;
		IF->out.str("");
		IF->out.clear();
		IF->out << str;
		IF->stall = false;
	}else{
		reg_value[PC] += 4;
		IF = new Instruction(ins_mem[(reg_value[PC])/4]);
		IF->out << "0x" << setfill('0') << setw(8) << hex << uppercase << ins_mem[(reg_value[PC]/4)];	
	}
}
