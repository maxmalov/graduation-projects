#include<iostream>
#include<string>
#include<conio.h>
#include<shlwapi.h>
using namespace std;
/* Программа распечатывает множество слов, встречающихся в каждом из 2х заданных предложений.
   Автор: Максим Малов МП-703
   Версия: beta 1.003
*/
size_t Fill_w(size_t start, char w[], char s[])
/*
  Функция заполнения буферной строки w, из главной строки s. Запись производится с символа с индексом старт
  и до первого разделителя. После процесса заполнения функция возвращает индекс встретившегося разделителя или
  индекс конца строки.
*/
{
	size_t i=start;

	while((s[i]==' ')||(s[i]=='\t')||(s[i]=='\n')) i++; //пропуск всех разделителей
	start=i; 
	for(i=start; s[i]&&(s[i]!=' ')&&(s[i]!='\t')&&(s[i]!='\n'); ++i) w[i-start]=s[i];
	w[i-start]='\0';
	if(s[i]!=NULL) ++i;
	return i;
}
void DelRepeats(char s[])
//Процедура удаляет повторяющиеся слова в данной строке s.
{	
	size_t i=0, j, ok, lnt, tmp1, tmp2;
	char w1[256], w2[256];
	lnt=strlen(s);
    do
	{
		tmp1=Fill_w(i,w1,s);
		i=tmp1;
		do
		{
			tmp2=Fill_w(i,w2,s); 
			ok=strcmp(w1,w2);
			if(ok==0) 
			{
				for(j=i; j<i+strlen(w1);++j) s[j]=' '; 
				i=j;
			}
			else i=tmp2;
		}while(tmp2<lnt);
		i=tmp1;
	}while(tmp1<lnt);
}                      

void main()
{
  	char s1[256], s2[256];
	char w1[256], w2[256];
	int ok=1;
	size_t count=0, i=0, j=0, tmp1, tmp2;
	
	cout<<"Enter the first sentence and press Enter button:"<<endl;	cin.getline(s1,1000); 
	  
	cout<<"Enter the second sentence and press Enter button:"<<endl; cin.getline(s2,1000); 
	
	if((s1[0]==NULL)||(s2[0]==NULL)) count=0;
	else 
	{
		DelRepeats(s1);
		DelRepeats(s2);
		do
	    {
			tmp1=Fill_w(i,w1,s1); //cout<<"W1: "<<w1<<" (Tmp1: "<<tmp1<<");  "; _getch();
			do
			{
				tmp2=Fill_w(j,w2,s2); //cout<<"W2: "<<w2<<"  (Tmp2: "<<tmp2<<")  ";
				ok=strcmp(w1,w2); //cout<<"Ok: "<<ok<<endl; _getch();
				if(ok==0)
				{
					count++;
					cout<<"Match #"<<count<<" : "<<w1<<endl;
					i=tmp1; 
					j=0;
					tmp2=strlen(s2);
				}
				else j=tmp2;
			}while(tmp2<strlen(s2));
			i=tmp1; 
			j=0;
		}while(tmp1<strlen(s1));
	}
	if(count==0) cout<<"Coincidences aren`t founded"<<endl;
	_getch();
}
