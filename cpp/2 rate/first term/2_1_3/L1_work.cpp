#include "L1_work.h"
#include<string.h>
using namespace std;
GetList1* ReadF(char* FName, GetList1* GL1)
//функция считывания слов из файла
//слова в файле должны разделяться запятой и пробелом после нее
{
	int i=0;
	char* tmp=0;
	if(!IsEmpty(GL1)) MakeEmpty(GL1); 
	ifstream inF(FName);
	if(inF.fail()) 
	{
		throw exBadFile();
		return 0;
	}
	do
	{
		tmp=new char[char_size];
		inF>>tmp;
		if(tmp[0]!='\0')
		{
			if(tmp[0]==',') tmp[0]='\0';
			else 
			{
				for(i=0;tmp[i];++i);
				if(tmp[i-1]==',')tmp[i-1]='\0';
			}
			AddToEnd(GL1,tmp); 
			delete []tmp;
		}
	}while(!inF.eof());
	//DelEnd(GL1); 
	return GL1;
}
void TopToEnd_EndToTop(GetList1* &GL1)
//Процедура меняет в списке первое и последнее слова местами
{
	if((!IsEmpty(GL1))&&(GL1->begin->next!=GL1->begin))
	{
		List1* tmp_ToBegin=0,* tmp_ToEnd=0;
		char* buf1=0,* buf2=0;
		try
		{
			tmp_ToEnd=First(GL1); tmp_ToBegin=Last(GL1);
			buf1=new char[strlen(tmp_ToEnd->word)+1]; strcpy(buf1,tmp_ToEnd->word);
			buf2=new char[strlen(tmp_ToBegin->word)+1]; strcpy(buf2,tmp_ToBegin->word);
			delete []tmp_ToEnd->word; delete []tmp_ToBegin->word; 
			tmp_ToEnd->word=buf2;	
			tmp_ToBegin->word=buf1; 
		}
		catch(std::bad_alloc)
		{
			if(buf1) delete []buf1;	
			throw;
		}
		catch(exBadList){throw;}
	}
	else throw exBadList();
}
void PrintFirstLetters(GetList1* GL1)
//Процедура выписывает первые символы непустых слов в списке.
{
	if(!IsEmpty(GL1))
	{
		PrintList(GL1);
		std::cout<<"First letters: ";
		ToBegin(GL1);
        if(GL1->current->word[0]) std::cout<<*GL1->current->word<<", ";
		ToNext(GL1);
		for(GL1->current;GL1->current!=GL1->begin;ToNext(GL1))
			if(GL1->current->word[0]) 
			{
				if(!IsEnd(GL1))std::cout<<*GL1->current->word<<", ";
				else std::cout<<*GL1->current->word;
			}
		_getch();
	}
	else throw exBadList();
}
void DelFirstLetters(GetList1* &GL1)
//Процедура удаляет первые символы непустых слов в списке.
{
	if(!IsEmpty(GL1))
	{
		std::cout<<"Old variant:"<<std::endl; PrintList(GL1);
		ToBegin(GL1);
		for(ToBegin(GL1);!IsEnd(GL1);ToNext(GL1))
			if(GL1->current->word[0]) 
				for(size_t i=1;GL1->current->word[i-1];++i) 
					GL1->current->word[i-1]=GL1->current->word[i];
        if(GL1->current->word[0]) 
				for(size_t i=1;GL1->current->word[i-1];++i) 
					GL1->current->word[i-1]=GL1->current->word[i];
		std::cout<<"New variant:"<<std::endl; PrintList(GL1);
	}
	else throw exBadList();
}
size_t CountWordsDifferFromLast(GetList1* GL1)
//Процедура ищет в списке количество слов отличных от последнего
{
	if(!IsEmpty(GL1))
	{
		size_t count=0;
		char* need=0;
		ToEnd(GL1); 
		List1* ctmp=GL1->current;
		need=new char[strlen(GL1->current->word)+1];
		strcpy(need,GL1->current->word);
        for(ToBegin(GL1);!IsEnd(GL1);ToNext(GL1))
			if(strcmp(GL1->current->word,need)!=0) ++count;
		delete []need;
		return count;			
	}
	else throw exBadList();
}