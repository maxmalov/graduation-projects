#include "List.h"
#include "stdafx.h"
List::List()
{
	buf = new ListElem;
	current = buf;
	buf->next = current;
}

List::List(const List &L)
{
	buf = new ListElem;
	current = buf;
	buf->next = current;

	ListElem *p = L.buf->next;
	ListElem *q = 0;

	while (p != L.buf)
	{
		q = new ListElem;
		q->elem = p->elem->Copy();

		q->next = current->next;
		current->next = q;
		current = q;
		p = p->next;
	}
	current = buf;
}
List & List::operator= (const List &L)
{
	if (this == &L)	
		return *this;

	MakeEmpty();

	ListElem *p = L.buf->next;
	ListElem *q = 0;

	while (p != L.buf)
	{
		q = new ListElem;
		q->elem = p->elem->Copy();
		q->next = current->next;
		current->next = q;
		current = q;
		p = p->next;
	}
	current = buf;
	return *this;
}
List::~List()
{
	MakeEmpty();
	delete buf;
}

void List::Reset()
{
	current = buf;
}
void List::Step()
{
	if (IsEnd())
		throw	exEndOfList();

	current = current->next;
}
bool List::IsEmpty()const
{
	return (buf->next == buf);
}
bool List::IsEnd()const
{
	return (current->next == buf);
}
void List::MakeEmpty()
{
	ListElem *p = buf->next;
	while (p != buf)
	{
		current = p->next;
		delete p->elem;
		delete p;		//Удаляем элемент списка
		p = current;
	}
	current = buf;
	buf->next = current;
}
void List::Insert(Figure *S)
{
	ListElem *p = new ListElem;

	p->elem = S->Copy();

	p->next = current->next;
	current->next = p;
}

Figure *List::Get()
{
	if (IsEnd())
		throw exEndOfList();
	
	ListElem *p = current->next;
	Figure *result = p->elem;
	current->next = p->next;
	delete p;
	return result;
}

void List::Delete()
{
	if (IsEnd())
		throw exEndOfList();

	ListElem *p = current->next;
	current->next = p->next;
	delete p->elem;
	delete p;
}

void List::Draw(HDC hdc)const
{

	for(ListElem *le = buf->next;le != buf; le = le->next)
		le->elem->Draw(hdc);
}

void FillList(List &lFigures, int xW, int yW)
{
	int cxFigures = 8;
	int cyFigures = 4;
	int xFsize = xW/cxFigures;
	int yFsize = yW/cyFigures;
	Figure *f = NULL;
	int iRand = 0;
	srand( (unsigned)time( NULL ) );

	for(int iy = 0; iy < cyFigures; iy++)
	{
		for(int ix = 0; ix < cxFigures; ix++)
		{
			iRand = rand()%3;
			switch(iRand)
			{
				case 0:
					{
						int xCenter = rand()%xFsize;
						int yCenter = rand()%yFsize;
						int iR = rand()%(min(min(min(xCenter, yCenter), xFsize-xCenter), yFsize-yCenter)+1);
						f = new Circle(xCenter + ix*xFsize, yCenter + iy*yFsize, iR, 
							RGB(rand()%256, rand()%256, rand()%256), RGB(rand()%256, rand()%256, rand()%256));
						lFigures.Insert(f);
						delete f;
						break;
					}
				case 1:
					{
						POINT pt1, pt2, pt3;
						pt1.x = (rand()%xFsize + ix*xFsize); pt1.y = (rand()%yFsize + iy*yFsize);
						pt2.x = (rand()%xFsize + ix*xFsize); pt2.y = (rand()%yFsize + iy*yFsize);
						pt3.x = (rand()%xFsize + ix*xFsize); pt3.y = (rand()%yFsize + iy*yFsize);
						f = new Triangle(pt1, pt2, pt3, RGB(rand()%256, rand()%256, rand()%256), RGB(rand()%256, rand()%256, rand()%256));
						lFigures.Insert(f);
						delete f;
						break;
					}
				case 2:
					{
						int xLeft = rand()%xFsize;
						int yTop  = rand()%yFsize;
						int xRight = xLeft + rand()%(xFsize - xLeft);
						int yBottom = yTop + rand()%(yFsize - yTop);
						f = new Rectangl(xLeft + ix*xFsize, yTop + iy*yFsize, xRight + ix*xFsize, yBottom + iy*yFsize, 
							RGB(rand()%256, rand()%256, rand()%256), RGB(rand()%256, rand()%256, rand()%256));
						lFigures.Insert(f);
						delete f;
						break;
					}
			}
			lFigures.Step();
		}
	}


}