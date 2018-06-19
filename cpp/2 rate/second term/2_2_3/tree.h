#ifndef _TREE_
#define _TREE_

#include"elements.h"
template <typename T> struct tree_elem
{
	T info;
	tree_elem* left,* right;

	/*tree_elem& operator = (const tree_elem& tre)
	{
		info=tre.info;
		left=tre.left;
		right=tre.right;
	}*/
};

template <typename T> void rdestroy(tree_elem<T>* &tre)							//рекурсивное удаление
{
	if(!tre) return;
	rdestroy(tre->left);
	rdestroy(tre->right);
	delete tre; 
}

template <typename T> void change(tree_elem<T>*& p,tree_elem<T>*& q)						
//функция в дереве с корнем q находит наибольший элемент и переставляет его на место удаляемого узла, 
//указатель р переставляется на удаляемый элемент
{
	if(q->right) change(p,q->right);
	else
	{
		p->info=q->info;
		p=q;
		q=q->left;
	}
}
template <typename T> const tree_elem<T>* rfind(const tree_elem<T>* tre, const T& t)
{
	if(!tre) return 0;
	if(t<tre->info) return rfind(tre->left,t);
	if(t>tre->info) return rfind(tre->right,t);
	return tre;
}
template <typename T> bool radd(tree_elem<T>*& tre,const T& t) 						//рекурсивное добавление элемента
{
	if(!tre)
	{
		tre=new tree_elem<T>;
		tre->info=t;
		tre->left=tre->right=0;
		return true;
	}
	if(t<tre->info) return radd(tre->left,t);
	if(t>tre->info) return radd(tre->right,t);
	return false;
}
template <typename T> bool rdel(tree_elem<T>* &tre,const T& t)							//рекурсивное удаление элемента
{
	if(!tre) return false;
	if(t<tre->info) return rdel(tre->left,t);
	if(t>tre->info) return rdel(tre->right,t);

	tree_elem<T>* pdel=tre; 

	if(!tre->right) tre=tre->left;
	else
	{
		if(!tre->left) tre=tre->right;
		else change(pdel,pdel->left);
	}
	delete pdel; tre=0;
	return true;
}
template <typename T> void prttr(ostream& out,const tree_elem<T>* tre,int high)		//печать дерева по уровням
{
	if(tre)
	{ 
		prttr(out,tre->right,high+1);
		for(int i=0;i<high;++i) out<<"\t";
		out<<tre->info<<endl;
		prttr(out,tre->left,high+1);
	}
	else return;
}

template <typename T> int isequal(const tree_elem<T>* tr1,const tree_elem<T>* tr2)	//проверка на равенство
{
	if( (!tr1&&tr2) || (!tr2&&tr1) ) return 1;
	else
	{
		if( (!tr1&&!tr2) || (tr1->info==tr2->info && !isequal(tr1->left,tr2->left) && !isequal(tr1->right, tr2->right)) )return 0;
		else if(!(tr1->info==tr2->info)) return 1;
	}
}

template <typename T> int findsub(const tree_elem<T>* src,const tree_elem<T>* dst)	//поиск изоморфного поддерева в данном дереве 
{
	const tree_elem<T>* root=rfind(src,dst->info);
	if( isequal(root->left,dst->left)==0 && isequal(root->right,dst->right)==0 && root) return 0;
	return 1;
}

template <typename T> tree_elem<T>* rcopy(const tree_elem<T>* tre)
{
	tree_elem<T>* new_root=0;
	try
	{
		if(!tre) return;
		
		new_root=new tree_elem;
		new_root->info=tre->info;
		new_root->left=0;//tre->left;
		new_root->right=0;//tre->right;

		new_root->left=rcopy(tre->left);
		new_root->right=rcopy(tre->right);
		return new_root;
	}
	catch(bad_alloc){ rdestroy(new_root); throw exTree(1); }
	catch(exTree obj){ rdestroy(new_root); throw exTree(obj.get_err()); }
}
//-----------------------------------------------------------------------------------------------------------------------

template <typename T> class tree
{
	tree_elem<T>* root;
public:
	tree(){root=0;}
	~tree(){ rdestroy(root); root=0;}
	tree(const tree<T>& tr)
	{
		root=rcopy(tr.root);
	}
	tree& operator = (const tree<T>& tr)
	{
		if(this==&tr) return this;
		if(root) rdestroy(root);
		try{ root=rcopy(tr.root); }
		catch(exTree obj){ throw exTree(2); }
	}
	
	bool operator == (const tree<T>& tr) const
	{
		return (isequal(root,tr.root)==0)?true:false;
	}
	
	bool operator <= (const tree<T>& tr) const
	{
		return (findsub(tr.root,root)==0)?true:false;
	}

	void add(const T& t){ radd(root,t); }
	void del(const T& t)
	{
		if(root) rdel(root,t); 
		else throw exTree(3);
	}

	bool isempty()const { return (root==0); }

	friend ostream& operator << (ostream& out, const tree<T>& tr)
	{
		if(tr.root)	prttr<T>(out,tr.root,0); return out;
		throw exTree(3);
	}
	friend istream& operator >> (istream& in, tree<T>& tr)
	{
		T elem;
		in>>elem; tr.add(elem);
		return in;
	}

	void menu_tree()
	{
		char ans;
		T elem;
		int num;
		tree<T> tgt;
		do
		{
			try
			{
				ans=trmenu();
				switch(ans)
				{
					case '1': cout<<"Set element: "; cin>>elem; add(elem); break;
					case '2': cout<<"Set element: "; cin>>elem; del(elem); break;
					case '3': 
						system("cls");
						cout<<"Set target tree: "<<endl; 
						do cout<<"Set quantity of elements: "; while(!read(cin,num));
						for(int i=0;i<num;++i) cin>>tgt;
						cout<<"Source tree: "<<endl<<(*this)<<endl; cout<<"target tree: "<<endl<<tgt<<endl;
						if(!(tgt<=(*this))) cout<<"Not found..."<<endl;
						else cout<<"Found..."<<endl; 
						_getch(); rdestroy<T>(tgt.root); tgt.root=0; break;
					case '4': cout<<(*this); _getch(); break;
				}
			}
			catch(exTree obj){ obj.prmsg(); }
		}while(ans!='0');
	}
};
#endif

