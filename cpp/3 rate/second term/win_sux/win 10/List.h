#ifndef _LIST_H_
#define _LIST_H_


#include "Figure.h"


class List
{
//Реализация на базе односвязного закольцованного списка с начальным буферным элементом.
	private:
		struct ListElem
		{
			Figure *elem;
			ListElem *next;
		};
		ListElem *buf;
		ListElem *current;
	public:
		List();						//конструктор списка
		List(const List &);			//конструктор копирования
		List & operator= (const List &);
		~List();					//деструктор  списка

		void Reset();				//установить указатель в начало
		void Step();				//передвинуть указатель вперед
		
		bool IsEmpty()const;		//проверка на пустоту
		bool IsEnd()const;			//проверка : указатель в конце?
		
		void MakeEmpty();			//сделать пустым
		
		void Insert(Figure *);		//вставить элемент за указатель
		Figure *Get();				//извлечь элемент за указателем
		
		void Delete();				//удалить элемент за указателем
		
		void Draw(HDC hdc)const;

		struct exEndOfList{};
};

void FillList(List &lFigures, int xW, int yW);
#endif