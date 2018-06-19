#include"employer.h"

int emenu()
{
	system("cls");
	int ans;
	do
	{
		cout<<"1. Infill class"<<endl;
		cout<<"2. Set first name"<<endl;
		cout<<"3. Set second name"<<endl;
		cout<<"4. Set patro name"<<endl;
		cout<<"5. Set birth date"<<endl;
		cout<<"6. Set license"<<endl;
		cout<<"7. Set registration"<<endl;
		cout<<"8. Set TIN"<<endl;
		cout<<"9. Set taxes"<<endl;
		cout<<"10. Set tax"<<endl;
		cout<<"11. See first name"<<endl;
		cout<<"12. See second name"<<endl;
		cout<<"13. See patro name"<<endl;
		cout<<"14. See birth date"<<endl;
		cout<<"15. See license"<<endl;
		cout<<"16. See registration"<<endl;
		cout<<"17. See TIN"<<endl;
		cout<<"18. See taxes"<<endl;
		cout<<"19. See tax"<<endl;
		cout<<"20. See all info"<<endl;
		cout<<"0. Back"<<endl;
		ans=ReadN(cin);
	}while(ans<0 || ans>19);
	return ans;
}
void ework(employer& e)
{
	char* tmp; tmp=new char[char_size];
	int lic,bd;
	_tax tax;
	d_s ds;
	int ans;
	do
	{
		system("cls");
		ans=emenu();
		switch(ans)
		{
			case 1:cin>>e; break;
			case 2:
				cout<<"Set first name: "; cin.getline(tmp,char_size);
				e.set_fname(tmp); *tmp=0; break;
			case 3:
				cout<<"Set second name: "; cin.getline(tmp,char_size);
				e.set_sname(tmp); *tmp=0; break;
			case 4:
				cout<<"Set patro name: "; cin.getline(tmp,char_size);
				e.set_pname(tmp); *tmp=0; break;
			case 5:
				do cout<<"Set birth date : "; while( (bd=ReadN(cin))==-1 );
				e.set_bdate(bd); break;
			case 6:
				do cout<<"Set license: "; while( (lic=ReadN(cin))==-1 );
				e.set_bdate(lic); break;
			case 7:
				cout<<"Set registration: "; cin.getline(tmp,char_size);
				e.set_reg(tmp); *tmp=0; break;
			case 8:
				cout<<"Set TIN: "; cin.getline(tmp,char_size);
				e.set_TIN(tmp); *tmp=0; break;
			case 9:
				cout<<"Set taxes: "; cin>>tax; e.set_tax(tax); break;
			case 10:
				do cout<<"Set date: "; while((ds.date=ReadN(cin))==-1);
				do cout<<"Set sum: "; while((ds.sum=ReadN(cin))==-1);
				do cout<<"Set index: "; while((bd=ReadN(cin))==-1);
				e.set_taxi(ds,bd); break;
			case 11:cout<<"First name: "<<e.get_fname()<<endl; _getch(); break;
			case 12:cout<<"Second name: "<<e.get_sname()<<endl; _getch(); break;
			case 13:cout<<"Patro name: "<<e.get_pname()<<endl; _getch(); break;
			case 14:cout<<"Birth date: "<<e.get_bdate()<<endl; _getch(); break;
			case 15:cout<<"License: "<<e.get_lic()<<endl; _getch();  break;
			case 16:cout<<"Registration: "<<e.get_reg()<<endl; _getch(); break;
			case 17:cout<<"TIN: "<<e.get_TIN()<<endl; _getch(); break;
			case 18:cout<<"Taxes: "<<e.get_tax()<<endl; _getch(); break;
			case 19:
				do cout<<"Index: "; while((bd=ReadN(cin))==-1);
				cout<<"Date: "<<e[bd].date<<" Sum: "<<e[bd].sum<<endl; _getch(); break;
			case 20:cout<<e; _getch(); break;
		}
	}while(ans!=0);
	delete[] tmp; tmp=0;
	return;
}
//------------------------------------------------------------------------------------------------------

void exEmployer::prmsg()
{
	switch(err)
	{
		case 1:	cerr<<"Employer.h: Initialization failure! (out of memory)"<<endl; break;
		case 2: cerr<<"Employer.h: Copy failure! (out of memory)"<<endl; break;
		case 3:	cerr<<"Employer.h: Assignment failure! (out of memory)"<<endl; break;
		
		case 4:	cerr<<"Employer.h: Can't set license number!"<<endl; break;
		case 5: cerr<<"Employer.h: Can't set registration adress!"<<endl; break;
		case 6: cerr<<"Employer.h: Can't set TIN number!"<<endl; break;
		case 7: cerr<<"Employer.h: Can't set tax pays!"<<endl; break;
		case 8: cerr<<"Employer.h: Can't set tax pay!"<<endl; break;

		case 9: cerr<<"Employer.h: Can't get registration adress!"<<endl; break;
		case 10: cerr<<"Employer.h: Can't get TIN number!"<<endl; break;
		case 11: cerr<<"Employer.h: Can't get tax pays!"<<endl; break;
		case 12: cerr<<"Employer.h: Bad index!"<<endl; break;
	}
	_getch();
}
//------------------------------------------------------------------------------------------------------
employer::employer(const char* fn,const char* sn,const char* pn,int bd,int lic,const char* reg,const char* tin, const _tax& tx):human(fn,sn,pn,bd)
{
	try
	{
		license=0; registration=TIN=0;
		set_lic(lic); 
		set_reg(reg); 
		set_TIN(tin); 
		set_tax(tx); 
	}
	catch(exEmployer obj)
	{
		if(!registration) license=0;
		if(registration){delete[] registration; registration=0;}
		if(TIN){delete[] TIN; TIN=0;}
		throw exEmployer(obj.get_err());
	}
}
employer::employer(const employer& e): human(e)
{
	try
	{ 
		license=0; registration=TIN=0;
		set_lic(e.license); set_reg(e.registration); set_TIN(e.TIN); set_tax(e.tax); 
	}
	catch(exEmployer obj)
	{
		if(!registration) license=0;
		if(registration){delete[] registration; registration=0;}
		if(TIN){delete[] TIN; TIN=0;}
		if(obj.get_err()!=1) throw exEmployer(obj.get_err());
		throw exEmployer(2);
	}
}
employer::~employer()
{
	tax.~_tax();
	if(registration){ delete[] registration; registration=0;}
	if(TIN){ delete[] TIN; TIN=0;}
	human::~human();
}

employer& employer::operator = (const employer& e)
{
	if(this==&e) return *this;
	set_lic(e.license); set_reg(e.registration);
	set_TIN(e.TIN); set_tax(e.tax);
	return *this;
}
ostream& operator << (ostream& out,const employer& e)
{
	out<<(human&)e<<endl;
	out<<"** Employer data **"<<endl;
	out<<"License: "<<e.get_lic()<<endl;
	out<<"Registration: "<<e.get_reg()<<endl;
	out<<"TIN: "<<e.get_TIN()<<endl;
	out<<e.get_tax()<<endl;
	return out;
}
istream& operator >> (istream& in,employer& e)
{
	int elem=0;
	char* buf=0; buf=new char[char_size];
	in>>(human&)e;
	cout<<"\n** Employer data **"<<endl;
	do cout<<"Set license: "; while((elem=ReadN(in))==-1); e.set_lic(elem); 
	cout<<"Set registration: "; in.getline(buf,char_size); e.set_reg(buf); *buf=0;
	cout<<"Set TIN: "; in.getline(buf,TIN_size); e.set_TIN(buf); *buf=0;
	in>>e.tax;
	delete[] buf; buf=0;
	return in;	
}