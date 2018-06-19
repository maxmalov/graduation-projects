#include"tree.h"
/*
	������� 24. 
	������� ������������� �������� � �������������� ���������
	��������� ������ ��������, ����������� ����� � ������������ ��������
	����� �����.
	����������� ����� �������������� � ���� z=a+bi,
	���������, ��� z>z1, ���� Re z > Re z1 ��� (Re z = Re z1 � Im z > Im z1).
	������������ ������� ����� ����� ����� ���������� ������������
	������������������� �������.
	������������ ����� �������, ����������� �������� � ������ ���������.
	��� �������� ������������� ������: 
		������� � �������� �������� � ������, 
		����� ������ � ����� �� ������� (�� ������� � �����), 
		���� ��	������, 
		�������� <=, ������������, �������� �� ������ T1 ���������� ������ T.
	�����: ������ ����� ��-703
*/
//#define _COM_TEST_
//#define _ARR_TEST_
#define _MAIN_

#ifdef _COM_TEST_
void main()
{
	_complex c1; cin>>c1;
	_complex c2(2,3);
	c1=c2;
	_complex c3(c1);
	cout<<c3;
}
#endif

#ifdef _ARR_TEST_
void main()
{
	_array a1; cin>>a1;
	_array a2; cin>>a2;

	if(a1==a2) cout<<a1<<"="<<a2;
	(a1>a2)?cout<<a1<<">"<<a2 : cout<<a1<<"<"<<a2;
}
#endif
#ifdef _MAIN_
void main()
{
	char ans;
	tree<char> ch_tree;
	tree<_complex> comp_tree;
	tree<_array> arr_tree;
	do
	{
		ans=mmenu();
		switch(ans)
		{
			case '1':ch_tree.menu_tree(); break;
			case '2':comp_tree.menu_tree(); break;
			case '3':arr_tree.menu_tree(); break;
		}

	}while(ans!='0');
}
#endif