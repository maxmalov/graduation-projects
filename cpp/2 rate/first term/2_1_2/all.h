#ifndef _ALL_H
#define _ALL_H
#include<iostream>
#include<conio.h>
int** GetMem(size_t size);
void Print(int** pArr, size_t size);
void GoSpiral(int** pArr, size_t size);
void DelMem(int** pArr, size_t size);
char menu();
int** ReadF(char *Fname, size_t &size);
void CreateF(char *fname);
bool ReadSize_t(size_t &value);
bool ReadInt(int &value);
int** HandleFilling(size_t &size);
#endif