//#define _TEST_
#include "Truth_table.h"
#include<iostream>
#include<conio.h>
using namespace std;
/*
	Вариант 57. Построение КНФ формулы логики высказываний
		Реализовать древовидную структуры хранения формулы FormTree
		Написать следующие функции
		- перекодирование дерева в строку
		- вычисление КНФ формулы
		- генератор случайной формулы
*/
void ErrMsg(int number)
{
	switch(number)
	{
	    //для модулей FormTree
	    case 1: std::cout<<"FormTree_realization.cpp: Out of memory!";break; 
		//для модулей IPR 
		case 2: std::cout<<"InvPolRec.cpp: Out of memory!";break;
		case 3: std::cout<<"InvPolRec.cpp: Incorrect formula!";break;
		case 4: std::cout<<"InvPolRec.cpp: Incorrect file!";break;
		//для модулей Truth Table
 		case 5: std::cout<<"Truth_table.cpp: Out of memory!";break;
		//для main
		case 6: std::cout<<"main.cpp: Out of memory!";break;
		case 7: std::cout<<"main.cpp: Input string doesn`t exist!";break;
		case 8: std::cout<<"main.cpp: You should import string previously!";break;
	}
	_getch();
}
char MainMenu(bool exStr)
{
	char ans;
	system("cls");
	std::cout<<"Main menu."<<std::endl;
	std::cout<<"1) Input string with formula."<<std::endl;
	std::cout<<"2) Generate file with formulas."<<std::endl;
	if(exStr) std::cout<<"3) Work with formula."<<std::endl;
	std::cout<<"0) Exit."<<std::endl;
	ans=_getch();
	return ans;
}
char Menu(bool impStr)
{
	char ans;
	do
	{
		system("cls");
		std::cout<<"CNF menu."<<std::endl;
		std::cout<<"1) Import string."<<std::endl;
		if(impStr)
		{
			std::cout<<"2) Watch formula CNF."<<std::endl;
			std::cout<<"3) Watch CNF tree."<<std::endl;
			std::cout<<"4) Watch truth table."<<std::endl;
			std::cout<<"0) Back to main menu."<<std::endl;
		}
		ans=_getch();
	}while((ans!='1')&&(ans!='2')&&(ans!='3')&&(ans!='4')&&(ans!='0'));
	return ans;
}
char InputMenu()
{
	char ans;
	do
	{	
		system("cls");
		std::cout<<"Input menu."<<std::endl;
		std::cout<<"1) Handle."<<std::endl;
		std::cout<<"2) From file."<<std::endl;
		ans=_getch();
	}while((ans!='1')&&(ans!='2')&&(ans!='0'));
	return ans;
}
void main(int argc, char* argv[])
{
	const int char_size=256;                    FormTree* root=0,* root_CNF=0; 
	char ans1, ans2, ans3;                      bool** TT=0;
	char* input=0,* fname=0;                    char* varstr=0,* CNF=0; 
	bool exStr=false, impStr=false;             int quan=0;
	
	int lenf=0, quanv=0, quanf=0, num=0;
	
#ifdef _TEST_
/*********************************************************************************************/
	root=Create();
	input=ReadF("in.txt");
	quan=CountVar(input,varstr);
	root=IPR(input);
	ImpToCon(root); NotToVal(root,false);
	PrintTr(root,0); _getch();
	TreeToCNF(root); CNF=TreeToStr(root,-1);
	PrintTr(root,0); std::cout<<"\nCNF: "<<CNF; _getch();
	Delete(root); 
	delete[]input; delete[]varstr;
/*****************************************************************************************/
#endif
#ifndef _TEST_	
	do
	{
		ans1=MainMenu(exStr);
		switch(ans1)
		{
			case '1':
				if(input) {delete []input; input=0; exStr=false;}
				if(root) {Delete(root), root=0; impStr=false;}
				if(root_CNF) {Delete(root_CNF), root_CNF=0;}
				if(varstr) {delete []varstr; varstr=0;}
				if(TT) {DeleteTable(TT,quan,Power(quan)); TT=0;}
				ans2=InputMenu();
				switch(ans2)
				{
					case '1':
						try
						{
							input=new char[char_size];
							std::cout<<"Enter formula: "; 
							while(std::cin.peek()=='\n') std::cin.ignore();
							std::cin.getline(input,char_size); 
							quan=CountVar(input,varstr); 
							root=IPR(input);
							exStr=true;
						}
						catch(std::bad_alloc)
						{
							if(!varstr) 
							{
								ErrMsg(6);
								delete []input; input=0;
							}
							if(!root)
							{
								ErrMsg(2);
								delete []input; input=0;
								delete []varstr; varstr=0;
							}
						}
						catch(exBadStr)
						{
							ErrMsg(3);
							delete []input; input=0;
							delete []varstr; varstr=0;
						}
						break;
					case '2':
						if(argc>1)
						{
							fname=new char[char_size];
							strcpy(fname,argv[1]);
						}
						else
						{
							fname=new char[char_size];
							std::cout<<"Enter file name: "; std::cin.getline(fname,char_size);
						}
						try
						{
							std::cout<<"Enter formula number: "; std::cin>>num;
							input=ReadF(fname,num);
							quan=CountVar(input,varstr);
							root=IPR(input);
							exStr=true;
							delete []fname;
						}
						catch(std::bad_alloc)
						{
							if(!input) ErrMsg(2);
							if(!varstr) 
							{
								ErrMsg(1);
								delete []input; input=0;
							}
							if(!root)
							{
								ErrMsg(2);
								delete []input; input=0;
								delete []varstr; varstr=0;
							}
						}
						catch(exBadFile){ ErrMsg(4); }
						break;
				}
				if(input){ std::cout<<"Formula :"<<input; _getch(); }
				break;
			case '2':
				std::cout<<"Enter lenght: "; std::cin>>lenf;
				std::cout<<"Enter quantity of values: "; std::cin>>quanv;
				std::cout<<"Enter quantity of formulas: "; std::cin>>quanf;
				FormGen(lenf,quanv,quanf);
				std::cout<<"File with formulas 'output.txt' was created successfully "; _getch();
				break;
			case '3':
				if(exStr)
				{
					do
					{
						ans3=Menu(impStr);
						switch(ans3)
						{
							case '1':
								try
								{
									TT=TruthTable(quan);
									root_CNF=MakeCNF(root,varstr,quan,TT); 
									impStr=true;
								}
								catch(std::bad_alloc)
								{
									if(!TT)
									{
										ErrMsg(5);
										delete []input; input=0;
										delete []varstr; varstr=0;
										exStr=false; impStr=false;
										ans3='0';
									}
									if(!root_CNF)
									{
										ErrMsg(5);
										DeleteTable(TT,quan,Power(quan)); TT=0;
										delete []input; input=0;
										delete []varstr; varstr=0;
										exStr=false; impStr=false;	
										ans3='0';
									}
								}
								catch(exBadStr)
								{
									ErrMsg(3);
									Delete(root); root=0;
									delete []input; input=0;
									delete []varstr; varstr=0;
									exStr=false; impStr=false;	
									ans3='0';
								}
								break;
							case '2':
								if(impStr)
								{
									try
									{
										CNF=TreeToStr(root_CNF,-1); 
										std::cout<<"Result: "<<CNF; _getch();
									}
									catch(std::bad_alloc) { ErrMsg(1); }
								}
								else ErrMsg(8);
								break;
							case '3':
								if(impStr){ PrintTr(root_CNF,0); _getch(); }
								else ErrMsg(8);
								break;
							case '4':
								if(impStr)
								{
									if(quan>0)for(int i=0;i<quan;++i) std::cout<<varstr[i]<<'\t';
									std::cout<<"Function"<<std::endl;
									if(quan<0)PrintTable(TT, Power(0),0);
									else PrintTable(TT, Power(quan),quan);
								}
								else ErrMsg(8);
								break;
						}
					}while(ans3!='0');
				}
				else ErrMsg(7);
				break;
		}
	}while(ans1!='0');
#endif
}