#include"all.h"
using namespace std;
void Print(int** pArr, size_t size)
//������� ������� �� ����� ������ � ���������� pArr � �������� size
{
	system("cls");
	cout<<"Your current matrix: "<<endl;
	for(size_t i=0;i<size;++i)
	{
		for(size_t j=0;j<size;++j) 
		{
			cout<<pArr[i][j]<<"\t";
		}
		cout<<'\n';
	}
}
void GoSpiral(int** pArr, size_t size)
/*
  �������, ������� � ������� ������ �������� ��������� �������, ������� ������� �� ������� � ������������� 
  �������� � ������� ������. 
  ������� ���������: ** pArr - ��������� �� �������� ������,
                     size - ������ �������.
*/   
{
	int d=1;
	int y=-1;
	int x=0;
	
	Print(pArr,size);
	cout<<"Result: ";
	for(size_t j=size*size;j>=1;) //���� ���� �������� �� ����������
	{
		for(size_t i=0;i<size;++i) //���� ������� �� �����������
		{
			y+=d;
			cout<<pArr[x][y]<<" "; --j;
		}
		for(size_t i=0;i<size-1;++i) //���� ������� �� ���������
		{
			x+=d;
			cout<<pArr[x][y]<<" "; --j;		
		}
		d*=-1;
		--size;
	}
}
char menu()
//��������� ������ �� ����� ����. ���������� ��������� ����� ����.
{
	char ans;
	
	system("cls");
	cout<<"   Main menu"<<endl;
	//cout<<"1. Create the config file."<<endl;
	cout<<"1. Infill a table."<<endl; 
	cout<<"2. Print the table. "<<endl;
	cout<<"3. Work with table. "<<endl;
	cout<<"4. Exit. "<<endl;
	cout<<'\n';
	ans=_getch();
	
	return ans;
}
