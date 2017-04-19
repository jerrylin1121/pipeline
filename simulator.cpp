#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include "memory.h"
#include "regfile.h"
#include "InstructionFetch.h"
#include "InstructionDecode.h"

using namespace std;
fstream snap("snapshot.rpt", fstream::out);
int cycle = 0;
bool halt = false;

int main()
{
    ifstream iin("./iimage.bin", ios::in | ios::binary);
    ifstream din("./dimage.bin", ios::in | ios::binary);
	load_instruction(&iin);
	load_data(&din);
	IF = new Instruction();
	ID = new Instruction();
	EX = new Instruction();
	DM = new Instruction();
	WB = new Instruction();
	for(int i=0; i<34; ++i){
		show_set.insert(i);
	}
	for(int i=0; i<9; ++i){
		snap << "cycle " << dec << cycle << endl;
		InstructionDecode();
		InstructionFetch();
		show_reg();
		++cycle;
	}
    return 0;
}
