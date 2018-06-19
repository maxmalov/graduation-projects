#include "FormTree_realization.h"
#include<conio.h>
#include<fstream>
#include<iostream>
#include <sys/timeb.h>
#include <time.h>
const int char_size=256;
char* random(char* s);
void FormGen(int len, int vars, int quan);
char* ReadF(char* Fname, int num);
struct Stack
{
	char info;
	Stack* next;
};
struct exBadFormula {};
struct exBadFile {};
Stack* CreateS();
bool Put(Stack* &top, char str);
void DelTop(Stack* &top);
bool IsEmpty(Stack* top);
void MakeEmpty(Stack* &top);
FormTree* IPR(char* str);
int Significance(char str);

