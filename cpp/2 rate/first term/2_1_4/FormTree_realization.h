#ifndef _FORMTREE_REALIZATION_H_
#define _FORMTREE_REALIZATION_H_
#include<string.h>
#include<iostream>
char* StrCat(char* strFirst, char* strLast);
struct FormTree
{
	char info;
	FormTree* left,* right;
};
struct exBadStr{};
FormTree* Create();
void MakeEmpty(FormTree* &root);
void Delete(FormTree* &root);
char* TreeToStr(FormTree* root, int prior);
void IPRToTree(char *str, FormTree *&top2);
int CountVar(char* str, char* &VarStr);
void PrintTr(FormTree* root, int high);
FormTree* Copy(FormTree* root);
#endif