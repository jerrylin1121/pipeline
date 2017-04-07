#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "regfile.h"

using namespace std;

int reg_value[35];
set<int> show_set;
stringstream IF, ID, EX, ME, WB;
extern fstream snap;

void clear_set(void)
{
	IF.str("");
	ID.str("");
	EX.str("");
	ME.str("");
	WB.str("");
	show_set.clear();
}

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
	snap << "IF: 0x" << IF.str() << endl;
	clear_set();
}
