#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include "memory.h"
#include "regfile.h"
#include "InstructionFetch.h"
#include "InstructionDecode.h"
#include "ALU.h"
#include "DataMemoryAccess.h"
#include "WriteBack.h"

using namespace std;
fstream snap("snapshot.rpt", fstream::out);
int cycle = 0;
bool halt = false;

bool detect_end(void);

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
	while(!detect_end() && !halt){
		snap << "cycle " << dec << cycle << endl;
		show_reg();
		WriteBack();
		DataMemoryAccess();
		ALU();
		InstructionDecode();
		InstructionFetch();
		show_stage();
		++cycle;
	}
    return 0;
}
bool detect_end(void)
{
	if(IF->opcode==0x3f && ID->opcode==0x3f && EX->opcode==0x3f && DM->opcode==0x3f && WB->opcode ==0x3f)
		return true;
	else
		return false;
}
