#include <iomanip>
#include <fstream>
#include "regfile.h"

int reg_value[35];
set<int> show_set;
Instruction *IF, *ID, *EX, *DM, *WB;
extern fstream snap;

void show_reg(void)
{
	for(set<int>::iterator it = show_set.begin(); it!=show_set.end(); ++it){
		if(*it <= 31)
			snap << "$" << setfill('0') << setw(2) << dec << *it << ": 0x" << setfill('0') << setw(8) << hex << uppercase << reg_value[*it] << endl;
		if(*it==HI)
			snap << "$HI: 0x" << setfill('0') << setw(8) << hex << uppercase << reg_value[HI] << endl;
		if(*it==LO)
			snap << "$LO: 0x" << setfill('0') << setw(8) << hex << uppercase << reg_value[LO] << endl;
	}
	snap << "PC: 0x" << setfill('0') << setw(8) << hex << uppercase << reg_value[PC] << endl;
	snap << "IF: " << IF << endl;
	snap << "ID: " << ID << endl;
	snap << endl << endl;
	show_set.clear();
}

ostream& operator<<(ostream& os, const Instruction *in)
{
	os << in->out.str();
	return os;
}
