#include"human.h"

int ReadN(istream& in)
{
	int num=0;
	in>>num;
	if((!in)||(num<0))
	{
		in.clear();
		while(in.peek()!='\n') in.ignore();
		in.ignore();
		return -1;
	}
	while(in.peek()!='\n') in.ignore();
	in.ignore();
	return num;
}
bool ReadI(int num)
{
	num=0;
	cin>>num;
	if(!cin)
	{
		cin.clear();
		while(cin.peek()!='\n') cin.ignore();
		cin.ignore();
		num=0; return false;
	}
	while(cin.peek()!='\n') cin.ignore();
	cin.ignore();
	return true;
}

char hmenu()
{
	system("cls");
	char ans;
	do
	{
		cout<<"1. Infill class"<<endl;
		cout<<"2. Set first name"<<endl;
		cout<<"3. Set second name"<<endl;
		cout<<"4. Set patro name"<<endl;
		cout<<"5. Set birth date"<<endl;
		cout<<"6. See first name"<<endl;
		cout<<"7. See second name"<<endl;
		cout<<"8. See patro name"<<endl;
		cout<<"9. See birth date"<<endl;
		cout<<"0. See all info"<<endl;
		cout<<"q. Back"<<endl;
		ans=_getch();
	}while( ans!='1' && ans!='2' && ans!='3' && ans!='4' && ans!='5' && ans!='6' && ans!='7' && ans!='8' && ans!='9' && ans!='0' && ans!='q');
	return ans;
}
void hwork(human& h)
{
	char* tmp; tmp=new char[char_size];
	char ans;
	int bd;
	do
	{
		system("cls");
		ans=hmenu();
		switch(ans)
		{
			case '1':cin>>h; break;
			case '2':
				cout<<"Set first name: "; cin.getline(tmp,char_size);
				h.set_fname(tmp); *tmp=0; break;
			case '3':
				cout<<"Set second name: "; cin.getline(tmp,char_size);
				h.set_sname(tmp); *tmp=0; break;
			case '4':
				cout<<"Set patro name: "; cin.getline(tmp,char_size);
				h.set_pname(tmp); *tmp=0; break;
			case '5':
				do cout<<"Set birth date : "; while( (bd=ReadN(cin))==-1 );
				h.set_bdate(bd); break;
			case '6':cout<<"First name: "<<h.get_fname()<<endl; _getch();break;
			case '7':cout<<"Second name: "<<h.get_sname()<<endl; _getch();break;
			case '8':cout<<"Patro name: "<<h.get_pname()<<endl; _getch();break;
			case '9':cout<<"Birth date: "<<h.get_bdate()<<endl; _getch();break;
			case '0':cout<<h; _getch();break;

		}
	}while(ans!='q');
	delete[] tmp; tmp=0;
	return;
}
//---------------------------------------------------------------------------------------------------------

void exHuman::prmsg()
{
	switch(err)
	{
		case 1:	cerr<<"Human.h: Initialization failure! (out of memory)"<<endl; break;
		case 2: cerr<<"Human.h: Copy failure! (out of memory)"<<endl; break;
		case 3:	cerr<<"Human.h: Assignment failure! (out of memory)"<<endl; break;
		
		case 4:	cerr<<"Human.h: Can't set first name!"<<endl; break;
		case 5: cerr<<"Human.h: Can't set second name!"<<endl; break;
		case 6: cerr<<"Human.h: Can't set patroname!"<<endl; break;
		case 7: cerr<<"Human.h: Can't set birth date!"<<endl; break;
		
		case 8:	cerr<<"Human.h: Can't get first name!"<<endl; break;
		case 9: cerr<<"Human.h: Can't get second name!"<<endl; break;
		case 10: cerr<<"Human.h: Can't get patroname!"<<endl; break;
	}
	_getch();
}
//----------------------------------------------------------------------------------------------------------

human::human(const char* fn,const char* sn,const char* pn,int bd)							
{
	try{ set_fname(fn); set_sname(sn); set_pname(pn); set_bdate(bd); }
	catch(exHuman obj)
	{
		if(name.fname){ delete[] name.fname; name.fname=0;}
		if(name.sname){ delete[] name.sname; name.sname=0;}
		throw exHuman(obj.get_err());
	}
}

human::human(const human& h)																
{
	try
	{ 
		set_fname(h.name.fname); 
		set_sname(h.name.sname); 
		set_pname(h.name.pname); 
		set_bdate(h.bdate); 
	}
	catch(exHuman obj)
	{
		if(name.fname){ delete[] name.fname; name.fname=0;}
		if(name.sname){ delete[] name.sname; name.sname=0;}
		if(obj.get_err()!=1) throw exHuman(obj.get_err());
		throw exHuman(2);
	}
}
human::~human()																			
{
	if(name.fname!=0){ delete[] name.fname; name.fname=0; }
	if(name.sname!=0){ delete[] name.sname; name.sname=0; }
	if(name.pname!=0){ delete[] name.pname; name.pname=0; }
	bdate=0;
}

human& human::operator = (const human& h)													
{
	if(this==&h) return *this;
	
	if(name.fname){ delete[] name.fname; name.fname=0;}
	if(name.sname){ delete[] name.sname; name.sname=0;}
	if(name.pname){ delete[] name.pname; name.sname=0;}
	bdate=0;

	try{ set_fname(h.name.fname); set_sname(h.name.sname); set_pname(h.name.pname); set_bdate(h.bdate); }
	catch(exHuman obj)
	{
		if(name.fname){ delete[] name.fname; name.fname=0;}
		if(name.sname){ delete[] name.sname; name.sname=0;}
		if(obj.get_err()!=1) throw exHuman(obj.get_err());
		throw exHuman(2);
	}
	return *this;
}
ostream& operator << (ostream& out, const human& h) 
{
	out<<"** Human data **"<<endl;
	out<<"Name: "<<h.get_fname()<<" "<<h.get_sname()<<" "<<h.get_pname()<<endl;
	out<<"Birth date: "<<h.get_bdate()<<endl;
	return out;
}
istream& operator >> (istream& in, human& h)
{
	int bd;
	char* buf=0;
	try
	{
		buf=new char[char_size];
		cout<<"** Human data **"<<endl;
		cout<<"Set first name: "; in.getline(buf,char_size); h.set_fname(buf); *buf=0;
		cout<<"Set second name: "; in.getline(buf,char_size); h.set_sname(buf); *buf=0; 
		cout<<"Set patroname: "; in.getline(buf,char_size); h.set_pname(buf); *buf=0;
		do cout<<"Set birth date: "; while( (bd=ReadN(in))==-1 ); h.set_bdate(bd); 
		delete[] buf; buf=0;
		return in;
	}
	catch(exHuman obj)
	{
		delete[] buf; buf=0;
		if(h.name.fname){ delete[] h.name.fname; h.name.fname=0;}
		if(h.name.sname){ delete[] h.name.sname; h.name.sname=0;}
		if(h.name.pname){ delete[] h.name.pname; h.name.pname=0;}
		throw exHuman(obj.get_err());
	}
}
inline void human::set_fname(const char* fn)
{
	if(fn)
	{
		try
		{
			name.fname=new char[strlen(fn)+1];
			strcpy(name.fname,fn);
		}
		catch(bad_alloc){throw exHuman(1); }
	}
	else throw exHuman(4);
}
inline void human::set_sname(const char* sn)
{
	if(sn)
	{
		try
		{
			name.sname=new char[strlen(sn)+1];
			strcpy(name.sname,sn);
		}
		catch(bad_alloc){ throw exHuman(1); }
	}
	else throw exHuman(5);
}
inline void human::set_pname(const char* pn)
{
	if(pn)
	{
		try
		{
			name.pname=new char[strlen(pn)+1];
			strcpy(name.pname,pn);
		}
		catch(bad_alloc){ throw exHuman(1); }
	}
	else throw exHuman(6);
}
inline void human::set_bdate(int bd)
{
	if(bd>=0) bdate=bd;
	else throw exHuman(7);

}