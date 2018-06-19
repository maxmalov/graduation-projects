/*
	36. МНОЖЕСТВО С ХЭШ-ТАБЛИЦЕЙ

	Реализовать класс-шаблон, объектами которого являются множества элементов с
	элементами типа T (int, float, myObject, и т.д.) Для внутреннего
	представления множества использовать динамическую хэш-таблицу.
	Предполагается, что элемента типа Т можно сравнивать на равенство, кроме того
	для элементов типа Т определен оператор int() преобразования в целое число.

	Операции над множеством:

	   * узнать мощность множества
	   * добавить/удалить элемент
	   * проверить есть ли элемент в множестве
	   * сделать множество пустым
	   * ввод/вывод множество в поток

	Отношения между двумя множествами:

	   * равны ли два множества
	   * содержит ли одно множество другое
	   * пересечение двух множеств
	   * объединение двух множеств
	   * разность двух множеств
	   * симметрическая разность двух множеств

	Реализовать класс "Итератор множества", который позволяет перебирать
	элементы заданного множества. Порядок перебора элементов не фиксирован.
	Набор методов итератора:

	   * установить итератор в начальное состояние,
	   * проверить: итератор перебрал все элементы множества,
	   * выдать текущий элемент,
	   * перейти к следующему элементу.

	Пример:
	myObject e(..);
	SetOf S;
	S.adjoinElement( e ); // добавить элемент e в S.

	SetIterator Iter( S );
	for( Iter.reset(); !Iter.done(); Iter.next() ) {
	myObject tmp = I.value();
	...
	}

	Рекомендуется сначала сделать обычные классы с типом элемента myObject, не
	используя шаблоны. После того, как эти классы будут отлажены, можно
	модифицировать их для использования шаблонов.
	
	Автор: Малов Максим МП-703

*/
#include"hash_table.h"
//#define _TEST_
//#define _TEST_SET_
#define _TEST_SETS_
//#define _TEST_HASH_


#ifdef _TEST_
void main()
{
	set_of<char> so1, so2, so3;
	so1.add('a'); so2.add('a'); so3.add('n');  
	so1.add('b'); so2.add('n'); so3.add('o');  
	so1.add('c'); so2.add('i'); so3.add('q');  
	so1.add('f'); so2.add('l'); so3.add('t');  
	so1.add('h');				so3.add('c'); 
	so1.add('n');   
	iter_set<char> is(so1); is.end(); is--;
	for(is; !is.start(); is--) cout<<*is;
	_getch(); cout<<endl;
	hash_table<set_of<char>> HT;
	HT.add(so1); HT.add(so2); HT.add(so3);
	iter_hash<set_of<char>> ih(HT); 
	ih.end(); ih--;
	for(ih; !ih.start(); ih--) cout<<*ih<<endl;
}
#endif

#ifdef _TEST_SET_
char sh_mmenu()
{
	char ans;
	do
	{
		system("cls");
		cout<<"1. Add element."<<endl;
		cout<<"2. Delete element."<<endl;
		cout<<"3. Check element."<<endl;
		cout<<"4. Get cardinal."<<endl;
		cout<<"5. Delete set."<<endl;
		cout<<"6. Print set."<<endl;
		cout<<"0. Exit."<<endl;
		ans=_getch();
	}while(ans!='1' && ans!='2' && ans!='3' && ans!='4' && ans!='5' && ans!='6' && ans!='0');
	return ans;
}
void main()
{
	char ans;
	set_of<char> so;
	char elem;
	do
	{
		ans=sh_mmenu();
		try
		{
			switch(ans)
			{
				case '1':
					cout<<"Set element:"<<endl; cin>>elem; 
					so.add(elem);
					break;
				case '2':
					cout<<"Set element:"<<endl; cin>>elem; 
					so.del(elem);
					break;
				case '3':
					cout<<"Set element:"<<endl; cin>>elem; 
					if(so>elem) cout<<"found"<<endl;
					else cout<<"not found"<<endl; 
					_getch();
					break;
				case '4':
					cout<<"Cardinal: "<<so.card()<<endl; _getch();
					break;
				case '5':
					so.clear();
					break;
				case '6':
					cout<<so; _getch();
					break;
			}
		}
		catch(exSet obj){obj.prtmsg(); _getch();}
	}while(ans!='0');
}
#endif


#ifdef _TEST_SETS_
char sh_mmenu()
{
	char ans;
	do
	{
		system("cls");
		cout<<"1. Union of sets."<<endl;
		cout<<"2. Intersectoin of sets."<<endl;
		cout<<"3. Sets difference set."<<endl;
		cout<<"4. Sets symmetric difference set."<<endl;
		cout<<"0. Exit."<<endl;
		ans=_getch();
	}while(ans!='1' && ans!='2' && ans!='3' && ans!='4' && ans!='0');
	return ans;
}
void main()
{
	char ans;
	set_of<char> so1, so2;
	do
	{
		ans=sh_mmenu();
		try
		{
			switch(ans)
			{
				case '1':
					so1.clear();
					so2.clear();
					cout<<"Fill first set(use 'n' for add new, 'e' for exit):"<<endl; cin>>so1; 
					cout<<"\nFill second set(use 'n' for add new, 'e' for exit):"<<endl; cin>>so2;
					cout<<"\n"<<(so1|so2)<<endl; _getch();
					break;
				case '2':
					so1.clear();
					so2.clear();
					cout<<"Fill first set(use 'n' for add new, 'e' for exit):"<<endl; cin>>so1; 
					cout<<"\nFill second set(use 'n' for add new, 'e' for exit):"<<endl; cin>>so2;
					cout<<"\n"<<(so1&so2)<<endl; _getch();
					break;
				case '3':
					so1.clear();
					so2.clear();
					cout<<"Fill first set(use 'n' for add new, 'e' for exit):"<<endl; cin>>so1; 
					cout<<"\nFill second set(use 'n' for add new, 'e' for exit):"<<endl; cin>>so2;
					cout<<"\n"<<(so1-so2)<<endl; _getch();
					break;
				case '4':
					so1.clear();
					so2.clear();
					cout<<"Fill first set(use 'n' for add new, 'e' for exit):"<<endl; cin>>so1; 
					cout<<"\nFill second set(use 'n' for add new, 'e' for exit):"<<endl; cin>>so2;
					cout<<"\n"<<(so1^so2)<<endl; _getch();
					break;
			}
		}
		catch(exSet obj){obj.prtmsg(); _getch();}
	}while(ans!='0');
}
#endif

#ifdef _TEST_HASH_
char sh_mmenu()
{
	char ans;
	do
	{
		cout<<"1. Add set"<<endl;
		cout<<"2. Delete set"<<endl; 
		cout<<"3. Print"<<endl;
		cout<<"0. Exit"<<endl;
	}while(ans!='1' && ans!='2' && ans!='3' && ans!='0');
	return ans;
}
void main()
{
	char ans;
	hash_table<set_of<char>> HT;
	do
	{
		ans=sh_mmenu();
		try
		{
			switch(ans)
			{
				case '1':
					so.clear();
					cout<<"Fill set(use 'n' for add new, 'e' for exit):"<<endl; cin>>so; 
					HT.add(so);
					break;
				case '2':
					so.clear();
					cout<<"Fill set(use 'n' for add new, 'e' for exit):"<<endl; cin>>so; 
					HT.del(so);
					break;
				case '3':
					iter_hash<set_of<char>> ih(HT); 
					for(ih.start(); !ih.end(); ih++) cout<<*ih<<endl;
					break;
			}
		}
		catch(exHT obj){obj.prtmsg(); _getch();}
	}while(ans!='0');
}
#endif