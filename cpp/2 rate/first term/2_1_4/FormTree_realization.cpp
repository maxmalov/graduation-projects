#include "FormTree_realization.h"
FormTree* Create()
{
	FormTree* root=0; root=new FormTree;
	root->left=root->right=0; root->info=0;
	return root;
}
void MakeEmpty(FormTree* &root)
{
	if(!root) return;
	Delete(root->left); Delete(root->right);
	root=0;
}
void Delete(FormTree* &root)
{
	if(!root) return;
	Delete(root->left); Delete(root->right);
    delete root;
}
void PrintTr(FormTree* root, int high)
{
	if(!root) return;
	PrintTr(root->right,high+1);
	for(int i=0;i<high;++i) std::cout<<"            ";
	std::cout<<root->info<<std::endl;
	PrintTr(root->left,high+1);
}
FormTree* Copy(FormTree* root)
{
	FormTree* new_root=0;
	if(!root) return new_root;
	try
	{
		new_root=new FormTree; new_root->info=root->info;
		new_root->left=Copy(root->left);
		new_root->right=Copy(root->right);
		return new_root;
	}
	catch(std::bad_alloc){ Delete(new_root); throw; }
}
/**************************************************************/
int Valuate(char str)
{
	if ((str=='v')||(str=='>')||(str=='^')) return 0;
	if (str=='&') return 1;
//	if (str=='^') return 2;
	return 3;
}
char* StrCat(char *str1, char *str2)
{	
	char *res=0;
	if (str1==0) 
	{
		if (str2==0) return 0;
		else 
		{
			res=new char[strlen(str2)+1]; strcpy(res,str2);
			return res;
		}
	}
	if (str2==0)
	{
		res=new char[strlen(str1)+1]; strcpy(res,str1);
		return res;
	}
	int len1=strlen(str1), len2=strlen(str2);
	res=new char[len1+len2+1];
	int k=0;
	for (int i=0; i<len1; ++i)
	{
		res[k]=str1[i];
		++k;
	}
	for (int i=0; i<len2; ++i)
	{
		res[k]=str2[i];
		++k;
	}
	res[k]='\0';
//	delete []str1; delete []str2;
	return res;
}
int valuate(char str)
{
	if((str=='v')||(str=='&')||(str=='>')) return 1;
	if(str=='^') return 2;
	if(str=='\0') return 3;
	return 0;
}
char* TreeToStr(FormTree* root, int prior) //при запуске полагать prior=-1
{
	if(!root) return 0;
	char* str=0; str=new char[2];
	switch(valuate(root->info))
	{
		case 1:
			str[0]=root->info; str[1]=0;
			str=StrCat(TreeToStr(root->left,Valuate(root->info)),str);
			str=StrCat(str,TreeToStr(root->right,Valuate(root->info)));
			if(prior>Valuate(root->info))
			{
				str=StrCat("(",str);
				str=StrCat(str,")");
			}
			break;
		case 2:
			str[0]='^'; str[1]=0;
			str=StrCat(str,TreeToStr(root->left,Valuate(root->info)));
			break;
		default:
			str[0]=root->info; str[1]=0;
			break;
	}
	return str;
}
/*********************************************************************************/
bool step(char *str, int &i, FormTree *&root2)
{
	if (i==-1) return 1;
	FormTree *root=0; try{ root=new FormTree; }
	catch (std::bad_alloc)
	{
		Delete(root2);
		root2=0; return 0;
	}
	root2=root;	root->info=str[i];
	root->left=0; root->right=0;
	int val=valuate(str[i]);
	if (val==0) --i;
	if (val==1)
	{
		--i;
		if (!step(str,i,root->left))
		{
			Delete(root);
			root=0; return 0;
		}
		if (!step(str,i,root->right))
		{
			Delete(root);
			root=0;
			return 0;
		}
		if((!root->left)||(!root->right)) return 0;
	}
	if (val==2)
	{
		--i;
		if (!step(str,i,root->left))
		{
			Delete(root);
			root=0;	return 0;
		}
		root->right=0;
		if(!root->left) return 0;
	}
	return 1;
}
void IPRToTree(char *str, FormTree *&top2)
{
	if (str==0) return;
	int len=strlen(str)-1;
	if (!step(str,len,top2))throw exBadStr();
}
/*******************************************************************************************************/
int CountVar(char* str, char* &VarStr)
{
	if (str==0) return 0;
	int i=0,count=0, count_c=0;
	char *tmp=0; tmp=new char[strlen(str)+1];
	strcpy(tmp,str);
	for(i=0;tmp[i];++i)	if((tmp[i]=='(')||(tmp[i]==')')) tmp[i]='>'; //удаление сторонних символов
	for(i=0;tmp[i];++i) if((tmp[i]=='1')||(tmp[i]=='0')) {count_c++; tmp[i]='>';}
	for(i=0;tmp[i];++i)
	{
		if (Valuate(tmp[i])==3)
		{
			++count;
			for (int j=i+1;tmp[j];++j) 	
				if(tmp[i]==tmp[j]) tmp[j]='>'; //удаление повтор€ющихс€ переменных
		}
	}
	try{VarStr=new char[count+1];}
	catch (std::bad_alloc)
	{
		delete []tmp;
		throw;
	}
	int j=0;
	for(i=0;tmp[i];++i) 
		if (Valuate(tmp[i])==3){ VarStr[j]=tmp[i]; ++j; }
	VarStr[j]='\0';
	delete []tmp;
	if(count) return count;
	if((!count)&&(count_c)) return -count_c;
	if((!count)&&(!count_c)) return 0;
}