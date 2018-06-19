#include "L1_interface.h"
void PrintList(GetList1* GL1)
//Печать списка
{
	int i=0;
	if(!IsEmpty(GL1))
	{	
		List1* ctmp=GL1->current;
		std::cout<<"List:"<<std::endl;
		for(ToBegin(GL1);!IsEnd(GL1);ToNext(GL1))
		{
			if(GL1->current==ctmp) std::cout<<"|"<<See(GL1)<<"|"<<" -> ";
			else std::cout<<See(GL1)<<" -> ";
		}
		std::cout<<See(GL1)<<" ->/O"<<std::endl;
		GL1->current=ctmp;
		_getch();
	}
	else throw exBadList();
}
int ListOptionMenu()
//Меню операций со списком
{
	int ans;
	bool flag;
	do
	{
		system("cls");
		std::cout<<"List option menu:"<<std::endl;
		std::cout<<"1) Create list."<<std::endl;
		std::cout<<"2) Read list from file."<<std::endl;
		std::cout<<"Add element."<<std::endl;
		std::cout<<"- 3) Add element to begin."<<std::endl;
		std::cout<<"- 4) Add element after current."<<std::endl;
		std::cout<<"- 5) Add element to end."<<std::endl;
		std::cout<<"Del element from begin."<<std::endl;
		std::cout<<"- 6) Del element from begin."<<std::endl;
		std::cout<<"- 7) Del element after current."<<std::endl;
		std::cout<<"- 8) Del element from end."<<std::endl;
		std::cout<<"Go to."<<std::endl;
		std::cout<<"- 9) Go to begin."<<std::endl;
		std::cout<<"- 10) Go to next."<<std::endl;
		std::cout<<"- 11) Go to end."<<std::endl;
		std::cout<<"12) See current element."<<std::endl;
		std::cout<<"13) Remove list."<<std::endl;
		std::cout<<"14) Check list for ending."<<std::endl;
		std::cout<<"15) Check list fo emptyness."<<std::endl;
		std::cout<<"16) Print list."<<std::endl;
		std::cout<<"0) Back to main menu."<<std::endl;
		std::cin>>ans;
		if(std::cin.fail())
		{
			flag=false;
			std::cin.clear();
			while(std::cin.peek()!='\n') std::cin.ignore();
			std::cin.ignore();
		}
		else flag=true;
	}while(!flag);
	while(std::cin.peek()!='\n') std::cin.ignore();
	std::cin.ignore();
	return ans;
}
int ListWorkMenu()
//Меню задач для списка
{
	int ans;
	bool flag;
	do
	{
		system("cls");
		std::cout<<"List work menu:"<<std::endl;
		std::cout<<"1) Change first word to last and on the contrary ."<<std::endl;
		std::cout<<"2) Print first word letters."<<std::endl;
		std::cout<<"3) Delete first word letters."<<std::endl;
		std::cout<<"4) Count words differ from the last."<<std::endl;
		std::cout<<"0) Back to main menu.\n"<<std::endl;
		std::cin>>ans;
		if(std::cin.fail())
		{
			flag=false;
			std::cin.clear();
			while(std::cin.peek()!='\n') std::cin.ignore();
			std::cin.ignore();
		}
		else flag=true;
    }while(!flag);
	while(std::cin.peek()!='\n') std::cin.ignore();
	std::cin.ignore();
	return ans;
}
int MainMenu()
//Главное меню
{
	int ans;
	bool flag;
	do
	{
	    system("cls");
		std::cout<<"Main menu:"<<std::endl;
		std::cout<<"1) List option menu."<<std::endl;
		std::cout<<"2) List work menu."<<std::endl;
		std::cout<<"0) Exit.\n"<<std::endl;
		std::cin>>ans;
		if(std::cin.fail())
		{
			flag=false;
			std::cin.clear();
			while(std::cin.peek()!='\n') std::cin.ignore();
			std::cin.ignore();
		}
		else flag=true;
	}while(!flag);
	while(std::cin.peek()!='\n') std::cin.ignore();
	std::cin.ignore();
	return ans;
}
