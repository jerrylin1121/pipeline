#include <iostream>
#include <fstream>
#include <cstdlib>
#include <set>
#include "memory.h"
#include "error.h"
#include "regfile.h"
fstream error("error_dump.rpt", ios::out);
extern int cycle;
extern bool halt;
bool write_reg0(int index)
{
	if(!index){
		error << "In cycle " << dec << cycle+1 << ": Write $0 Error" << endl;
		return true;
	}
	return false;
}
void detect_number_overflow(bool in1, bool in2, bool out)
{
	if(in1==in2 && in1!=out){
		error << "In cycle " << dec << cycle+1 << ": Number Overflow" << endl;
	}
}
void overwrite_HI_LO(bool in)
{
	static bool write_HI_LO = false;
	if(in && write_HI_LO){
		error << "In cycle " << dec << cycle+1 << ": Overwrite HI-LO registers" << endl;
	}else if(in){
		write_HI_LO = true;
	}else{
		write_HI_LO = false;
	}
}
void mem_address_overflow(void)
{
	error << "In cycle " << dec << cycle+1 << ": Address Overflow" << endl;
	halt = true;
}
void data_misaligned(void)
{
	error << "In cycle " << dec << cycle+1 << ": Misalignment Error" << endl;
	halt = true;
}
