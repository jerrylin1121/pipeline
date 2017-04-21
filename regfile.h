#include <set>
#include <sstream>
#define HI 32
#define LO 33
#define PC 34
using namespace std;
class Instruction{
private:
	unsigned int instruction, funct;
	unsigned int rs, rt, rd;
	int A, B, C;
public:
	unsigned int opcode;
	bool ALUReady, MDRReady, stall;
	int ALUOut, MDR;
	stringstream out;
	Instruction(void){
		instruction = 0;
		opcode = 0;
		rs = 0;
		rt = 0;
		rd = 0;
		funct = 0;
		A = 0;
		B = 0;
		C = 0;
		ALUReady = false;
		MDRReady = false;
		stall = false;
		ALUOut = 0;
		MDR = 0;
		out.str("NOP");	
	}
	Instruction(unsigned int in){
		instruction = in;
		opcode = in >> 26;
		rs = (in&0x03e00000)>>21;
		rt = (in&0x001f0000)>>16;
		rd = (in&0x0000f800)>>11;
		funct = in&0x0000003f;
		A = 0;
		B = 0;
		C = in&0x0000ffff;
		ALUReady = false;
		MDRReady = false;
		stall = false;
		ALUOut = 0;
		MDR = 0;
		out.str("");
	}
	void InstructionDecode(void);
	void ALU(void);
	void DataMemoryAccess(void);
	void WriteBack(void);
	void End(void);
	friend ostream& operator<<(ostream& , const Instruction *);
};
extern ostream& operator<<(ostream& os, const Instruction * in);
extern int reg_value[35];
extern int reg_use[35];
extern set<int> show_set;
extern Instruction *IF, *ID, *EX, *DM, *WB;

void show_reg(void);
void show_stage(void);
