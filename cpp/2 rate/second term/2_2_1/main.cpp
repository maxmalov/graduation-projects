#include "class_text.h"
#include <stdlib.h>
#include <string.h>
#include <iostream>
//#define _STRING_TEST_												//тестирование класса строки
//#define _TEXT_TEST_												//тестирование класса текст
#define _TEXT_DEMO_											//демонстрация возможностей

/*
Вариант 5.
	Реализовать класс "Защищенный массив символов"
		Поля: границы индексирования
		Методы: получить границы, прочитать/изменить элемент, вывести массив в поток ввода/вывода
	Реализовать класс "Текст"
		Текст хранится в виде массива защищенных массивов символов
		Поля: максимальный размер
		Методы: добавить строку в конец, прочитать изменить строку с заданным индексом, удалить
				строку с заданным номером, потоковый ввод-вывод текста
	Автор: Малов Максим МП-703
*/
#ifdef _STRING_TEST_
void main()
{
	_string s1("abcd"), s2("1234");
	cout<<s1<<endl;  
	cout<<s2<<endl;
	
	char* buf=0; buf=new char[10]; strcpy(buf,"abcdef");
	s2=buf;
	delete []buf; buf=0;
	cout<<s2<<endl;


	s1=s2;
	s2.~_string();
	cout<<s1<<endl;

	_string s3(s1);
	s1.~_string();
	cout<<s3<<endl;

	s1.~_string();
	s2.~_string();
	s3.~_string();
}
#endif

#ifdef _TEXT_TEST_
void main()
{
	_text t1(10), t2(7);
	t1.adds("abc"); t1.adds("aaa");
	t2.adds("123"); t2.adds("111");
	cout<<t1<<endl;  cout<<t2<<endl;

	t1=t2;
	t2.~_text();
	cout<<t1<<endl;

	_text t3(t2);
	cout<<t3<<endl;

	t2.~_text();
	
	t1.adds("1234");
	t3=t2=t1;
	cout<<t1<<endl;
	cout<<t2<<endl;

	t1.~_text();
	t2.~_text();
	t3.~_text();
}
#endif

#ifdef _TEXT_DEMO_
char MainMenu()
{
	char ans;
	do
	{
		system("cls");
		cout<<"Main menu"<<endl;
		cout << "1.Create text"<< endl;
		cout << "2.Work with text" << endl;
		cout << "0.Exit" << endl;
		ans=_getch();
	}while((ans!='1')&&(ans!='2')&&(ans!='0'));
	return ans;
}
char TextMenu(_text& T)
{
	char ans;
	do
	{
		system("cls");
		cout<<"Text interface (Current size:"<<T.GetCS()<<", Maximal size: "<<T.GetMS()-1<<"):"<<endl;
		cout<<"1.Show text"<<endl;
		cout<<"2.Show string"<<endl;
		cout<<"3.Add string to the end"<<endl;
		cout<<"4.Change string"<<endl;
		cout<<"5.Delete string"<<endl;
		cout<<"0.Exit"<<endl;
		cout<<"_______________________________________________________\n";
		ans=_getch();
	}while((ans!='1')&&(ans!='2')&&(ans!='3')&&(ans!='4')&&(ans!='5')&&(ans!='0'));
	return ans;
}

void main()
{
	int ans1, ans2, elem, ind;
	_text T;
	char *str=0;
	do
	{
		ans1=MainMenu();
		switch(ans1)
		{
			case '1': 
				if(T.GetTxt()) T.~_text();
				cin>>T; break;
			case '2':
				do
				{
					if(T.GetTxt())
					{
						ans2=TextMenu(T);
						try
						{
							switch(ans2)
							{
								case '1': cout<<"Info:\n"<<T; _getch(); break;
								case '2':
									do{ cout<<"Enter index: "; elem=ReadN(); }while(elem==-1);
									cout<<T[elem]<<endl;
									cout<<"(left index-"<<T[elem].GetLI()<<", right index-"<<T[elem].GetRI()<<")\n"<<endl;
									_getch();
									break;
								case '3': 
									str=new char [char_size];
									cout<<"Enter new string: ";
									cin.getline(str,char_size);
									T.adds(str);
									delete []str; str=0;
									break;
								case '4': 
									str=new char [char_size];
									cout<<"Enter new string: ";
									cin.getline(str,char_size);
									do{ cout<<"Enter index: "; elem=ReadN(); }while(elem==-1);
									do{ cout<<"Enter left index range: "; ind=ReadN(); }while(ind==-1);
									T.chgs(elem,ind,str);
									delete []str; str=0;
									break;
								case '5': 
									do{ cout<<"Enter index: "; elem=ReadN(); }while(elem==-1);
									T.dels(elem);
									break;
							}
						}
						catch(Error obj)
						{
							int err=obj.GetErr();
							obj.PrtMsg(); _getch();
						}
					}
					else { cerr<<"Text doesn't exist!"; _getch(); ans2='0'; }
				}while(ans2!='0');
				break;
		}
	}while(ans1!='0');
	if(T.GetTxt()) T.~_text();
}
#endif