#include<fstream>
#include"all.h"
using namespace std;
bool ReadSize_t(size_t &value)
//������� ���������� ������������ ����� 
{
	value=0; 
	char* tmp=new char[10];
	cin.getline(tmp,10);
	for(int i=0;tmp[i];++i)
	{
		if((tmp[i]=='0')||(tmp[i]=='1')||(tmp[i]=='2')||(tmp[i]=='3')||(tmp[i]=='4')||(tmp[i]=='5')
			||(tmp[i]=='6')||(tmp[i]=='7')||(tmp[i]=='8')||(tmp[i]=='9')) continue;
		else return false;
	}
	value=atoi(tmp); 
	return true;
}
bool ReadInt(int &value)
//������� ���������� ������ ����� 
{
	value=0; 
	char* tmp=new char[10];
	cin.getline(tmp,10);
	for(int i=0;tmp[i];++i)
	{
		if((tmp[i]=='0')||(tmp[i]=='1')||(tmp[i]=='2')||(tmp[i]=='3')||(tmp[i]=='4')||(tmp[i]=='5')
			||(tmp[i]=='6')||(tmp[i]=='7')||(tmp[i]=='8')||(tmp[i]=='9')||(tmp[i]=='-')) continue;
		else return false;
	}
	value=atoi(tmp); 
	return true;
}
int** ReadF(char *Fname, size_t &size)
/*
   ������� ������ ������� �� �����.
   �������� ��������: *Fname - ��������� �� ������ � ������ �������� �����
                      size - ������ ������� (���������� �� ������), ���������� ����� 0
   ������� ���������� ��������� �� ��������� ������� ��� ���������� ������ ����������, � ��������� ������ ���������� NULL
*/
{
	int** pArr;
	size_t i=0, j=0;
	
	ifstream inF(Fname); //�������� �������� ��������� ������
	if(inF.fail()) 
	{
		cerr<<"File method: File not found!"<<endl; _getch();
		return NULL;
	}
	
	inF>>size;//���������� �������
	if(inF.fail())
	{
		cerr<<"File method: Read file error(file is empty or incorrect size of matrix)!"<<endl; _getch();
		return NULL;
	}
	
	pArr=GetMem(size); //��������� ������
	
	if(pArr==NULL) return NULL;

	for(i=0;(i<size)&&(!inF.eof());++i)
	{
		for(j=0;(j<size)&&(!inF.eof());++j)
		{
			inF>>pArr[i][j];
	        if(inF.fail()) 
	        {  
				cerr<<"File method: Read file error (incorrect symbols)!"<<endl; _getch();
				DelMem(pArr,size);
				return NULL;	    	
			}
		}
	}
	if( (i*j)==(size*size) ) //�������� ���������� ��������� �������� 
	{
		cout<<"File method: Matrix was filled successfully!"<<endl; _getch();
		return pArr;
	}
	else
	{ 
	    	cerr<<"File method: Read file error(not enough symbols)!"<<endl; _getch();
	    	DelMem(pArr,size);
			return NULL;
	}
}
/*void CreateF(char* fname)
// ��������� �������� �������� �����.
// ������� ��������: *fname - ��������� �� ������ � ������ �����.
{
	size_t size, tmp;
	ofstream outF(fname);//�������� ��������� ��������� ������

	do
	{
		cout<<"Enter size of future matrix: "; cin>>size;
	}while(size<=0);
	cout<<endl;
	outF<<size; outF<<'\n';	
	for(size_t i=0;i<size;++i)
	{
		for(size_t j=0;j<size;++j)
		{
			cout<<"Enter ["<<i<<"]["<<j<<"] element of matrix: "; cin>>tmp;
			outF<<tmp; outF<<" "; 
		}
		outF<<'\n';
	}
	cout<<"File was writed successfully! Press Enter to continue..."; _getch();
}*/
int** HandleFilling(size_t &size)
//������� ������� ���������� �������. �������� �������� ��������� �� 2������ ������.
{
	bool flag; 
	int** pArr=NULL;
	do
	{
		cout<<"Enter matrix size: "; 
		flag=ReadSize_t(size);
	}while(!flag);
	
	pArr=GetMem(size);
	if(!pArr) return NULL;
	
	for(size_t i=0;i<size;++i)
        for(size_t j=0;j<size;++j)
		do
		{
			cout<<"Enter ["<<i<<"]["<<j<<"] element of matrix: ";
		    flag=ReadInt(pArr[i][j]);
		}while(!flag);		
	return pArr;
}