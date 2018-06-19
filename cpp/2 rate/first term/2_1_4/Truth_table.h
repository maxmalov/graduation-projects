#include<conio.h>
#include "FormTree_realization.h"
#include "InvPolRec.h"
int Power(int number);
bool** TruthTable(int quan);
void DeleteTable(bool** pArr, int quan, int row);
void DeleteTable(int** pArr, int quan, int row);
void PrintTable(bool** pArr, int row, int quan);
bool Count(FormTree* root, char* varstr, bool **TT, int level);
void CountTT(FormTree* root, char* varstr, int quan, bool **TT);
FormTree* MakeCNF(FormTree* root_original, char* varstr, int quan, bool** &TT);