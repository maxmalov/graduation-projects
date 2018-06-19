//#include"human.h"
//#include"employer.h"
//#include"adress.h"
#include"trader.h"
/*
	Задача II. Вариант 14. 
	Реализовать класс "Человек", включающий в себя имя, фамилию, отчество,
	год рождения и методы, позволяющие изменять / получать значения этих полей.
	Реализовать производные классы:
		1) "Предприниматель" -- содержит номер лицензии, адрес регистрации, ИНН,
		данные о налоговых платежах (массив пар вида <дата, сумма>).
		2) "Турист" -- содержит данные паспорта (строка), данные о пересечении
		границы в виде массива пар <дата, страна>.
		3) "Челнок" (производный от 2 и 3) -- добавляется массив строк - список
		адресов, по которым покупается товар.
		Классы должны содержать методы доступа и изменения всех полей. Предельные
		размеры динамических массивов задаются при инициализации и не увеличиваются
		в дальнейшем.
*/

#define _MAIN_
//#define _HUMAN_TEST_
//#define _EMPLOYER_TEST_
//#define _TOURIST_TEST_
//#define _TRADER_TEST_
#ifdef _MAIN_
char main_menu()
{
	system("cls");
	char ans;
	do
	{
		cout<<"1. Create/edit human"<<endl;
		cout<<"2. Create/edit employer"<<endl;
		cout<<"3. Create/edit tourist"<<endl;
		cout<<"4. Create/edit trader"<<endl;
		cout<<"0. Exit"<<endl;
		ans=_getch();
	}while( ans!='1' && ans!='2' && ans!='3' && ans!='4' && ans!='0' );
	return ans;
}
void main()
{
	human h;
	employer emp;
	tourist t;
	trader tr;
	char ans;
	
	do
	{
		ans=main_menu();
		try
		{
			switch(ans)
			{
				case '1':hwork(h);break;
				case '2':ework(emp);break;
				case '3':twork(t);break;
				case '4':trwork(tr);break;
			}
		}
		catch(exHuman obj)
		{ 
			int err=obj.get_err();
			obj.prmsg(); 
			if(err!=8 && err!=9 && err!=10){ h.destroy(); ans=0; }
		}
		catch(exEmployer obj)
		{
			int err=obj.get_err();
			obj.prmsg(); 
			if(err!=9 && err!=10 && err!=11 && err!=12){ h.destroy(); ans=0; }
		}
		catch(exTourist obj)
		{
			int err=obj.get_err();
			obj.prmsg(); 
			if(err!=7 && err!=8 && err!=9){ h.destroy(); ans=0; }
		}
		catch(exTrader obj)
		{
			int err=obj.get_err();
			obj.prmsg(); 
			if(err!=3){ h.destroy(); ans=0; }
		}
	}while(ans!='0');
}
#endif
#ifdef _HUMAN_TEST_
void main()
{
	human h1("Eduardo","Fisco","Johnovich",1973), h2("Vitorio","Elan","Hzhovich",1993);
	cout<<h1<<endl; cout<<h2<<endl;
	human h3(h2); h2.~human(); cout<<h3<<endl;
	h1=h3; h3.~human(); cout<<h1<<endl;
	human h4; cin>>h4; cout<<h4<<endl;
	h1.~human();
	
	system("cls");
	cout<<h4.get_bdate()<<" "<<h4.get_fname()<<" "<<h4.get_pname()<<" "<<h4.get_sname();
}
#endif 

#ifdef _EMPLOYER_TEST_
void main()
{
	_tax tx1(10); 
	cin>>tx1;
	employer e1("Eduardo","Fisco","da Silva",1923,43643,"Omsk","5564435ER45354",tx1);

	employer e2(e1); e1.~employer();
	cout<<e2; e2.~employer(); _getch();
	
	system("cls");
	employer e3; cin>>e3;
	system("cls"); 
	employer e4=e3;
	e3.~employer(); cout<<e4;
}
#endif

#ifdef _TOURIST_TEST_
void main()
{
	_travel tr1(10); 
	cin>>tr1;
	tourist t1("Eduardo","Fisco","da Silva",1923,"5564435ER4",tr1);
	
	tourist t2(t1); t1.~tourist();
	cout<<t2; t2.~tourist(); _getch();
	
	system("cls");
	tourist t3; cin>>t3;
	system("cls"); cout<<t3;
	t3.~tourist();
}
#endif

#ifdef  _TRADER_TEST_
void main()
{
	trader tr; cin>>tr; 
//	system("cls"); 
//	cout<<tr; _getch();
	
	system("cls"); 
	trader tr1(tr); 
	tr.~trader(); cout<<tr1; _getch();
	
	trader tr2=tr1; tr.~trader();
	cout<<tr2;
}
#endif
