#include <iostream>
#include <iomanip>
#include "memory.h"
#include "regfile.h"

using namespace std;
void InstructionFetch()
{
	IF << setfill('0') << setw(8) << hex << uppercase << ins_mem[(reg_value[PC]/4)];
	reg_value[PC] += 4;
}
