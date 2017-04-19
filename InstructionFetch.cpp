#include <iostream>
#include <iomanip>
#include "memory.h"
#include "regfile.h"

using namespace std;
void InstructionFetch()
{
	reg_value[PC] += 4;
	IF = new Instruction(ins_mem[(reg_value[PC])/4]);
	IF->out << "0x" << setfill('0') << setw(8) << hex << uppercase << ins_mem[(reg_value[PC]/4)];
}
