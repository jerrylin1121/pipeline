#include "library.h"

extern bool flushed;
extern int next_PC;
void InstructionFetch()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	if(flushed){
		IF = new Instruction(ins_mem[(reg_value[PC])/4]);
		IF->out << "0x" << setfill('0') << setw(8) << hex << uppercase << ins_mem[(reg_value[PC]/4)] << " to_be_flushed";
		reg_value[PC] = next_PC;
		IF->stall = false;
	}else if(ID->stall){
		if(ID==IF){
			IF = new Instruction(ins_mem[(reg_value[PC])/4]);
			IF->out << "0x" << setfill('0') << setw(8) << hex << uppercase << ins_mem[(reg_value[PC]/4)] << " to_be_stalled";
			IF->stall = true;
		}
	}else if(IF->stall){
		reg_value[PC] = next_PC;
		string str;
		IF->out >> str;
		IF->out.str("");
		IF->out.clear();
		IF->out << str;
		IF->stall = false;
	}else{
		IF = new Instruction(ins_mem[(reg_value[PC])/4]);
		IF->out << "0x" << setfill('0') << setw(8) << hex << uppercase << ins_mem[(reg_value[PC]/4)];	
		reg_value[PC] = next_PC;
	}
}
