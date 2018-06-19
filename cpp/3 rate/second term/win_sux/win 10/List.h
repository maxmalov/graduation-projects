#ifndef _LIST_H_
#define _LIST_H_


#include "Figure.h"


class List
{
//���������� �� ���� ������������ ��������������� ������ � ��������� �������� ���������.
	private:
		struct ListElem
		{
			Figure *elem;
			ListElem *next;
		};
		ListElem *buf;
		ListElem *current;
	public:
		List();						//����������� ������
		List(const List &);			//����������� �����������
		List & operator= (const List &);
		~List();					//����������  ������

		void Reset();				//���������� ��������� � ������
		void Step();				//����������� ��������� ������
		
		bool IsEmpty()const;		//�������� �� �������
		bool IsEnd()const;			//�������� : ��������� � �����?
		
		void MakeEmpty();			//������� ������
		
		void Insert(Figure *);		//�������� ������� �� ���������
		Figure *Get();				//������� ������� �� ����������
		
		void Delete();				//������� ������� �� ����������
		
		void Draw(HDC hdc)const;

		struct exEndOfList{};
};

void FillList(List &lFigures, int xW, int yW);
#endif