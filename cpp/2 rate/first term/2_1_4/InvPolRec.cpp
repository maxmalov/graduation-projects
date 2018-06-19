#include "InvPolRec.h"
char* random(char s, int &scope)
{
	char* str=0;
	struct _timeb timebuffer;
	_ftime(&timebuffer);
	if(timebuffer.millitm%3==0)
	{
		str=new char[3];
		if(s!='>')
		{
			str[0]=s; str[1]='^'; str[2]='\0';
		}
		else 
		{
			str[0]=s; str[1]='\0';
		}
		return str;
	}
	else
	{
		str=new char[2]; 
		str[0]=s; str[1]='\0';
		return str;
	}
}
int division(int a, int b)
{
	if(a/b) return a/b;
	return 1;
}
void FormGen(int len, int vars, int quan)
{
	const int OPERATORS=3;
	char operators[OPERATORS]={'&', '>', 'v'};
	std::ofstream of("output.txt");
	while(quan>0)
	{
		char prev_s, prev_o='&';
		char* str=new char[char_size];
		char* tmp=new char[4];
		int scope=0;
		int parensFreq=division(len,5);
		int i=0;
		for(i=0;i<len;)
		{
			int t;
			
			if(!(t=rand()%parensFreq)||(str[i-1]=='>'))
			{
				str[i]='(';
				++scope;
				prev_s='(';
				++i;
			}
			
			str[i]=(char)(rand()%vars+'A'); ++i; prev_s='v';
			
			if(!(rand()%parensFreq)&&(scope>0)&&(prev_s!='v'))
			{
				str[i]=')';
				--scope;
				prev_s=')';
				++i;
			}
			tmp=random(operators[rand()%OPERATORS],scope);
			str[i]=tmp[0]; i++; prev_o=tmp[0];
			if(tmp[1]){ str[i]=tmp[1]; prev_o=tmp[1]; ++i;}
			prev_s='o';
		}
		str[i]=(char)(rand()%vars+'A');  prev_s='v'; ++i; 
		for(;scope;--scope) { str[i]=')'; prev_s=')'; ++i; }
		str[i]='\0';
		for(int j=0;str[j];++j) of<<str[j]; of<<'\n';
		delete []str; quan--;
	}
	of.close();
}
char* ReadF(char* Fname, int num)
{
	std::ifstream inF(Fname);
	if(inF.fail()) throw exBadFile();
	char* tmp=0; tmp=new char[char_size];
	while(num>0)
	{
		while(inF.peek()!='\n') inF.ignore();
		num--; inF.ignore();
	}
	
	inF.getline(tmp,char_size);
	if(inF.fail())
	{
		delete []tmp;
		throw exBadFile();
	}
	return tmp;
}
/*************************************************************************************************/
Stack* CreateS() 
{
	Stack* top=0;
	top=new Stack;
	top->next=0; top->info=0;
	return top;
}
bool Put(Stack* &top, char str)
{
	Stack* tmp=0; tmp=new Stack;
	tmp->info=str;
	tmp->next=top; top=tmp;
	return true;
}
void DelTop(Stack* &top)
{
	if(IsEmpty(top)) return;
	Stack* tmp=top->next;
	delete top;
	top=tmp;
}
bool IsEmpty(Stack* top){return top==0;}
void MakeEmpty(Stack* &top)
{
	while(!IsEmpty(top)) DelTop(top);
	delete top;
}
/*************************************************************************************************/
FormTree* IPR(char* str)
{
	int count=0;
	char prev='o';
	char* result=0;
	int count_b=0;
	Stack* top=0;
	for(int i=0;str[i];++i)
	{ if((str[i]!='(')&&(str[i]!=')')) ++count; }
	
	for(int i=0;str[i];++i) 
	{
		if(str[i]=='(') ++count_b;
		else if(str[i]==')') --count_b;
	}
	if(count_b!=0) throw exBadStr();
	result=new char[count+2];
	top=CreateS();
	int k=0;
	for(int i=0;str[i];++i)
	{
		if(str[i]=='(')
		{
			if(prev=='o')
			{
				if(!Put(top,str[i]))
				{
					MakeEmpty(top);
					delete []result;
					throw;
				}
			}
			else
			{
				MakeEmpty(top);
				delete []result;
				throw exBadStr();
			}
		}
		if(str[i]==')')
		{
			if(prev=='v')
			{
				while((!IsEmpty(top))&&(top->info!='('))
				{
					result[k]=top->info; ++k;
					DelTop(top);
				}
				if (!IsEmpty(top))
					if (top->info=='(') DelTop(top);
			}
			else
			{
				MakeEmpty(top);
				delete []result;
				throw exBadStr();
			}
		}
		if(Significance(str[i])==-1)
		{
			if(prev=='o')
			{
				result[k]=str[i]; ++k;
				prev='v';
			}
			else
			{
				MakeEmpty(top);
				delete []result;
				throw exBadStr();
			}
		}
		if(Significance(str[i])>=2)
		{
			if( ((prev=='v')&&(str[i]!='^')) || ((str[i]=='^')&&(prev=='o')))
			{
				while(top&&(Significance(top->info)>Significance(str[i])))
				{
					result[k]=top->info; ++k;
					DelTop(top);
				}
				if (!Put(top,str[i]))
				{
					MakeEmpty(top);
					delete []result;
					throw;
				}
				prev='o';
			}
			else
			{
				MakeEmpty(top);
				delete []result;
				throw exBadStr();
			}
		}
	}
	while(top)
	{
		result[k]=top->info; ++k;
		DelTop(top);
	}
	result[k]='\0';
	try
	{
		FormTree* root=0; root=Create();
		IPRToTree(result,root);
		delete []result;
		return root;
	}
	catch(std::bad_alloc)
	{
		if(result) delete []result;
		throw;
	}
	catch(exBadStr)
	{
		if(result) delete []result;
		throw exBadStr();
	}
}
/*************************************************************************************************/
int Significance(char str)
{
	if (str=='(') return 0;
	if (str==')') return 1;
	if ((str=='v')||(str=='>')) return 2;
	if (str=='&')	return 3;
	if (str=='^')	return 4;
	return -1;
}
/*************************************************************************************************/