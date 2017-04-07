#include <set>
#include <iostream>
#include <sstream>
#define HI 32
#define LO 33
#define PC 34

extern int reg_value[35];
extern std::set<int> show_set;
extern std::stringstream IF, ID, EX, DM, WB;

void show_reg(void);
