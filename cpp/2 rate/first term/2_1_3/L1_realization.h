#ifndef _L1_LIST_REALIZATION_H_
#define _L1_LIST_REALIZATION_H_
const size_t char_size=255;
struct List1 //структура односвязного списка
{
	char* word;
	List1* next;
};
struct GetList1 //структура, посредством которой передается список
{
	//int count;
	List1* begin;
	List1* current;
};
struct exBadList{};
GetList1* Create();
void Destroy(GetList1* &GL1);
void AddAfterCurrent(GetList1* GL1, char *s);
void AddToBegin(GetList1* &GL1, char* s);
void AddToEnd(GetList1* GL1, char* s);
void DelAfterCurrent(GetList1* GL1);
void DelBegin(GetList1* &GL1);
void DelEnd(GetList1* GL1);
char* See(GetList1* GL1);
void ToNext(GetList1* GL1);
void ToBegin(GetList1* GL1);
void ToEnd(GetList1* GL1);
void MakeEmpty(GetList1* &GL1);
bool IsEnd(GetList1* GL1);
bool IsEmpty(GetList1* GL1);
List1* First(GetList1* GL1);
List1* Last(GetList1* GL1);
void PrintMessage(size_t number);
#endif