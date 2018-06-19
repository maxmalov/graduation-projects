#ifndef _L1_WORK_H_
#define _L1_WORK_H
#include "L1_realization.h"
#include "L1_interface.h"
#include<iostream>
#include<fstream>
#include<conio.h>
struct exBadFile{};
GetList1* ReadF(char* FName, GetList1* GL1);
void TopToEnd_EndToTop(GetList1* &GL1);
void PrintFirstLetters(GetList1* GL1);
void DelFirstLetters(GetList1* &GL1);
size_t CountWordsDifferFromLast(GetList1* GL1); 
#endif