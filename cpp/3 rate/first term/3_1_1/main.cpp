//B-14
//	Реализовать объект "Очередь в магазине"
//  Каждый человек имеет имя, фамилию, возможно льготы или детей 
//Автор: Малов Максим МП-703


#include<iostream>
using namespace std;
#include"queue.h"
#include"vld.h"

void main()
{
	_queue Q;
	_queue* q=new _queue;
	man* human;
	room* r;
	
	r=new room(15);
	q->push(r);
	delete r;

	human=new man_adv("1","2");
	q->push(human);
	delete human;

	human=new man_chn("3","4");
	q->push(human);
	delete human;
	
	Q.push(&Q);
	*q = Q;
	Q.clear();
	delete q;

	r=new room(34);
	Q.push(r);
	delete r;

	human=new man("5","6");
	Q.push(human);
	delete human;

	cout<<Q<<endl;
}