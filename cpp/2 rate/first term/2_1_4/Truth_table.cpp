#include "Truth_table.h"
int Power(int number)
{
     int two=2;
	 if(number>=1)
	 {     
	      for(int i=0;i<number-1;i++) two*=2;
		  return two;
     }
	 if(number==0) return 1;
	 return 0;     
}
bool** TruthTable(int quan)
{
     int row=0; 
	 if(quan>0) row=Power(quan);
	 else {row=Power(0); quan=0;}
	 bool** pArr=0;
	 pArr=new bool*[row];
	 for(int i=0;i<row;++i)
	 {
	    try{pArr[i]=new bool[quan+1];}
		catch(std::bad_alloc)
		{
		    for(int j=0;j<i;++j) delete pArr[j];
			delete pArr;
		    throw; return 0;
		}
	}
	for (int i=0; i<quan; ++i)// перебор стобцов матрицы для заполнения
	{
		int pow1=Power(i), pow2=Power(quan-i-1), q=0;
		for (int j=0; j<pow1; ++j)// столько будет блоков вида 0...01...1
		{
			for (int k=0; k<pow2; ++k) {pArr[q][i]=0; ++q;}//заполнение нулями
		    for (int k=0; k<pow2; ++k) {pArr[q][i]=1; ++q;}//заполнение единицами
		}
	}
	for(int i=0;i<row;++i) pArr[i][quan]=0;
	return pArr;
}
void DeleteTable(bool** pArr, int quan, int row)
{
   for(int i=0;i<row;++i) delete []pArr[i];
   delete pArr; pArr=0;
}
void DeleteTable(int** pArr, int quan, int row)
{
   for(int i=0;i<row;++i) delete []pArr[i];
   delete pArr; pArr=0;
}
void PrintTable(bool** pArr, int row, int quan)
{
	for(int i=0;i<row;++i)
	{
		for(int j=0;j<quan+1;++j)
			std::cout<<pArr[i][j]<<"\t";
		std::cout<<std::endl;
	}
	_getch();
}
bool max(bool first, bool last)
{
	if(first>last) return first;
	else return last;
}
bool min(bool first, bool last)
{
	if(first<last) return first;
	else return last;
}
bool Count(FormTree* root, char* varstr, bool **TT, int level)
{
	switch(root->info)
	{
		case '1': return 1;
		case '0': return 0;
		case '&': return min( Count(root->left,varstr,TT,level), Count(root->right,varstr,TT,level) ); 
		case 'v': return max( Count(root->left,varstr,TT,level), Count(root->right,varstr,TT,level) );
		case '>': return max( Count(root->left,varstr,TT,level), !Count(root->right,varstr,TT,level)); 
		case '^': return !Count(root->left,varstr,TT,level);
		default: for (int i=0;varstr[i];++i) if (varstr[i]==root->info) return TT[level][i];
	}
}
void CountTT(FormTree* root, char* varstr, int quan, bool **TT)
{
	if ((TT==0)||(varstr==0)||(root==0)) return;
	if(quan<0) TT[0][0]=Count(root,varstr,TT,0);
	else
	{
		int tmp=Power(quan);
		for (int i=0;i<tmp;++i) TT[i][quan]=Count(root,varstr,TT,i);
	}
}
FormTree* MakeCNF(FormTree* root_original, char* varstr, int quan, bool** &TT)
{
	if ((TT==0)||(varstr==0)||(!root_original)) return 0;
	int row=0; 
	if(quan>0) row=Power(quan);
	else row=Power(0);
	CountTT(root_original,varstr,quan,TT);
/******************************************************************************/	
	FormTree* root=0; root=Create();
	char* CNF=0;
	int quan_0=0;
	for(int i=0;i<row;i++) if(TT[i][quan]==0) ++quan_0;
	if(quan_0==0)
	{
		try
		{
			CNF=new char[2];
			CNF[0]='1'; CNF[1]=0; 
			root=IPR(CNF);
			delete []CNF; return root;
		}
		catch(std::bad_alloc)
		{
			Delete(root);
			for(int i=0;i<row;++i) TT[i][quan]=0;
			throw;	
		}
	}
	if(quan_0==row)
	{
		try
		{
			CNF=new char[2];
			CNF[0]='0'; CNF[1]=0;
			root=IPR(CNF);
			delete []CNF; return root;
		}
		catch(std::bad_alloc){ Delete(root); throw; }
	}
/******************************************************************************/	
	bool** pArr=0;
	pArr=new bool* [quan_0];
	for(int i=0;i<quan_0;++i)
	{
		try{pArr[i]=new bool [quan+1];}
		catch(std::bad_alloc)
		{
			for(int j=0;j<i;++j) delete pArr[j];
			delete pArr;
			throw;
		}
	}

	int k=0;
	for(int i=0;i<row;++i)
	{
		if(TT[i][quan]==0)
		{
			for(int j=0;j<quan+1;++j) pArr[k][j]=TT[i][j];
			++k;
		}
	}
/******************************************************************************/	
	char* row_CNF=0;
	char* tmp=0; tmp=new char[2]; tmp[1]='\0';
	for(int i=0;i<quan_0;++i)
	{
		try{ row_CNF=StrCat(row_CNF,"("); }
		catch(std::bad_alloc)
		{
			DeleteTable(pArr,quan,quan_0);
			delete []row_CNF;
			delete []tmp;
			throw;
		}
		for(int j=0;j<quan+1;++j)
		{
			if(pArr[i][j]==1)
			{ 
				try { row_CNF=StrCat(row_CNF,"^");}
				catch(std::bad_alloc)
				{
					DeleteTable(pArr,quan,quan_0);
					delete []row_CNF;
					delete []tmp;
					throw;
				}
			}
			tmp[0]=varstr[j];
			try{ row_CNF=StrCat(row_CNF,tmp);}
			catch(std::bad_alloc)
			{	
				DeleteTable(pArr,quan,quan_0);
				delete []row_CNF;
				delete []tmp;
				throw;
			}
			if(j<quan-1)
			{
				try{ row_CNF=StrCat(row_CNF,"v");}
				catch(std::bad_alloc)
				{
					DeleteTable(pArr,quan,quan_0);
					delete []row_CNF;
					delete []tmp;
					throw;
				}
			}
		}
		try{ row_CNF=StrCat(row_CNF,")");}
		catch(std::bad_alloc)
		{
			DeleteTable(pArr,quan,quan_0);
			delete []row_CNF;
			delete []tmp;
			throw;
		}
		try{ CNF=StrCat(CNF,row_CNF);}
		catch(std::bad_alloc)
		{
			DeleteTable(pArr,quan,quan_0);
			delete []row_CNF;
			delete []tmp;
			if(CNF) delete []CNF;
			throw;
		}
		if(i!=quan_0-1)
		{
			try{CNF=StrCat(CNF,"&");} 
			catch(std::bad_alloc)
			{
				DeleteTable(pArr,quan,quan_0);
				delete []row_CNF;
				delete []tmp;
				if(CNF) delete []CNF;
				throw;
			}
		}
		delete []row_CNF; row_CNF=0;
	}
	try
	{
		root=IPR(CNF); delete []CNF; 
		return root;
	}
	catch(std::bad_alloc)
	{
		delete []CNF; 
		throw;
	}
	catch(exBadStr)
	{
		delete []CNF; 
		throw exBadStr();
	}
}