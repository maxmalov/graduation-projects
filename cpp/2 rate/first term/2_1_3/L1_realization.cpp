#include"L1_realization.h"
#include<iostream>
#include<string.h>
#include<conio.h>
GetList1* Create()
{
	GetList1* GL1=0;
	GL1=new GetList1;
	GL1->begin=GL1->current=0; //GL1->count=0;
	return GL1;
}
void Destroy(GetList1* &GL1)
{
	if(!IsEmpty(GL1)) MakeEmpty(GL1);
	delete GL1; GL1=0;
}
void AddAfterCurrent(GetList1* GL1, char *s)
{
	if(!IsEmpty(GL1))
	{
		List1* tmp=0; tmp=new List1;
		try
		{
			tmp->word=new char[strlen(s)+1];
			strcpy(tmp->word,s);
			tmp->next=GL1->current->next;
			GL1->current->next=tmp;
			//GL1->count++;
		}
		catch(std::bad_alloc){delete tmp; throw;}
	}
	else throw exBadList();
}
void AddToBegin(GetList1* &GL1, char* s)
{
	List1* tmp=0; tmp=new List1;
	List1* ctmp=0;
	try
	{
		tmp->word=new char[strlen(s)+1];
		strcpy(tmp->word,s);
		if(IsEmpty(GL1))
		{ 
			GL1->begin=tmp; GL1->current=tmp;
			GL1->current->next=GL1->current;
		}
		else 
		{
			ctmp=GL1->current;//запоминаем текущее положение
			tmp->next=GL1->begin;
			ToEnd(GL1); GL1->current->next=tmp;
		    GL1->begin=tmp;
            GL1->current=ctmp;//возвращаем изначальное текущее положение
		}
		//GL1->count++;
	}
	catch(std::bad_alloc){delete tmp; throw;}
}
void AddToEnd(GetList1* GL1, char* s)
{ 
	if(IsEmpty(GL1))AddToBegin(GL1,s);
	else
	{
		List1* ctmp=GL1->current;//запоминаем текущее значение
		ToEnd(GL1); AddAfterCurrent(GL1,s);
		GL1->current=ctmp;//возвращаем текущее значение
	}
}
void DelAfterCurrent(GetList1* GL1)
{
	if(!IsEmpty(GL1)) 
	{
		if(GL1->begin->next!=GL1->begin)
		{
			List1* tmp=GL1->current->next;
		    if(tmp==GL1->begin) GL1->begin=GL1->begin->next;
		    GL1->current->next=tmp->next;
		    delete []tmp->word; delete tmp;
		}
		else DelBegin(GL1);
		//GL1->count--;
	}
	else throw exBadList();
}
void DelBegin(GetList1* &GL1)
{
	if(!IsEmpty(GL1)) 
	{
		if(GL1->begin->next==GL1->begin)
		{
			delete GL1->begin->word; delete GL1->begin;
			GL1->begin=GL1->current=0;
			//GL1->count=0;
		}
		else
		{
			List1* ctmp=0;
			if(GL1->current==GL1->begin) ctmp=GL1->current->next;//запоминаем текущее значение
			else ctmp=GL1->current;
			ToEnd(GL1); GL1->begin=GL1->begin->next;
			DelAfterCurrent(GL1);
			GL1->current=ctmp;//возвращаем текущее значение
		}
	}
	else throw exBadList();
}
void DelEnd(GetList1* GL1)
{
	if(!IsEmpty(GL1))
	{
		List1* ctmp=0;
		if(GL1->begin==GL1->begin->next) DelBegin(GL1);
		else
		{
			if(IsEnd(GL1)) ctmp=GL1->begin; //запоминаем текущее значение
			else ctmp=GL1->current;
			while(GL1->current->next->next!=GL1->begin) ToNext(GL1);
			DelAfterCurrent(GL1);
			GL1->current=ctmp; //возвращаем текущее значение
		}
	}
	else throw exBadList();
}
char* See(GetList1* GL1)
{
	if(!IsEmpty(GL1)) return (GL1->current->word);
	else throw exBadList();
}
void ToNext(GetList1* GL1)
{
	if(!IsEmpty(GL1)) GL1->current=GL1->current->next;
	else throw exBadList();
}
void ToBegin(GetList1* GL1)
{
	if(!IsEmpty(GL1)) GL1->current=GL1->begin;
	else throw exBadList();
}
void ToEnd(GetList1* GL1)
{
	if(!IsEmpty(GL1)) 
		while(GL1->current->next!=GL1->begin) ToNext(GL1);	
	else throw exBadList();
}
void MakeEmpty(GetList1* &GL1) 
{ 
	if(!IsEmpty(GL1)) 
	{
		ToBegin(GL1);
		while(GL1->begin) DelBegin(GL1); 
	}
	//GL1->count=0;
}
bool IsEnd(GetList1* GL1){return(GL1->current->next==GL1->begin);}
bool IsEmpty(GetList1* GL1){ return(GL1->begin==0); }
List1* First(GetList1* GL1)
//Поиск первого непустого слова
{
	if(!IsEmpty(GL1))
	{
		for(ToBegin(GL1);(!IsEnd(GL1))&&(!GL1->current->word[0]);ToNext(GL1));
		if(!IsEnd(GL1)) return GL1->current;
		else throw exBadList();
	}
	else throw exBadList();
}
List1* Last(GetList1* GL1)
//поиск последнего непустого слова
{
	List1* tmp=0;
	if(!IsEmpty(GL1))
	{
		for(ToBegin(GL1);!IsEnd(GL1);ToNext(GL1))
		{
			if(GL1->current->word[0]) tmp=GL1->current;
			else continue;
		}
		if(GL1->current->word[0]) tmp=GL1->current;
		if((tmp!=First(GL1))&&tmp) return tmp;
		else throw exBadList();
	}
	else throw exBadList();
}
void PrintMessage(size_t number)
{
	switch(number)
	{
		case 1: std::cout<<"L1_realization.cpp: Done!"<<std::endl; break;
		case 2: std::cerr<<"L1_realization.cpp: Out of memory!"<<std::endl; break;
		case 3: std::cerr<<"L1_realization.cpp: List is empty!"<<std::endl; break;
		case 4: std::cerr<<"L1_realization.cpp: End of list!"<<std::endl; break;
		case 5: std::cerr<<"You should create list previously!"<<std::endl;break;
		case 6: std::cerr<<"There are no 2 not empty words in current list!"<<std::endl;break;
		case 7: std::cerr<<"L1_word.cpp: Bad input file!"<<std::endl;break;
	}
	_getch();
}