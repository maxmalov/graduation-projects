#include"tourist.h"
int tmenu()
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
		cout<<"6. Set passport"<<endl;
		cout<<"7. Set travels"<<endl;
		cout<<"8. Set travel"<<endl;
		cout<<"9. See first name"<<endl;
		cout<<"10. See second name"<<endl;
		cout<<"11. See patro name"<<endl;
		cout<<"12. See birth date"<<endl;
		cout<<"13. See passport"<<endl;
		cout<<"14. See travels"<<endl;
		cout<<"15. See travel"<<endl;
		cout<<"16. See all info"<<endl;
		cout<<"0. Back"<<endl;
		ans=ReadN(cin);
	}while(ans<0 || ans>15);
	return ans;
}
void twork(tourist& t)
{
	char* tmp; tmp=new char[char_size];
	_travel trv;
	int bd;
	d_c dc;
	int ans;
	do
	{
		system("cls");
		ans=tmenu();
		switch(ans)
		{
			case 1:cin>>t; break;
			case 2:
				cout<<"Set first name: "; cin.getline(tmp,char_size);
				t.set_fname(tmp); *tmp=0; break;
			case 3:
				cout<<"Set second name: "; cin.getline(tmp,char_size);
				t.set_sname(tmp); *tmp=0; break;
			case 4:
				cout<<"Set patro name: "; cin.getline(tmp,char_size);
				t.set_pname(tmp); *tmp=0; break;
			case 5:
				do cout<<"Set birth date : "; while( (bd=ReadN(cin))==-1 );
				t.set_bdate(bd); break;
			case 6:
				cout<<"Set passport: "; cin.getline(tmp,char_size);
				t.set_passport(tmp); *tmp=0; break;
			case 7:
				cout<<"Set travels: "; cin>>trv;
				t.set_travel(trv);break;
			case 8:
				do cout<<"Set date: "; while((dc.date=ReadN(cin))==-1);
				cout<<"Set country: "; cin.getline(tmp,char_size);
				dc.country=new char[strlen(tmp)+1]; strcpy(dc.country,tmp); *tmp=0; break;
				do cout<<"Set index: "; while((bd=ReadN(cin))==-1);
				t.set_traveli(dc,bd); break;
			case 9:cout<<"First name: "<<t.get_fname()<<endl; _getch(); break;
			case 10:cout<<"Second name: "<<t.get_sname()<<endl; _getch(); break;
			case 11:cout<<"Patro name: "<<t.get_pname()<<endl; _getch(); break;
			case 12:cout<<"Birth date: "<<t.get_bdate()<<endl; _getch(); break;
			case 13:cout<<"Passport: "<<t.get_passport()<<endl; _getch(); break;
			case 14:cout<<"Travels: "<<t.get_travel()<<endl; _getch(); break;
			case 15:
				do cout<<"Index: "; while((bd=ReadN(cin))==-1);
				cout<<"Date: "<<t[bd].date<<" Country: "<<t[bd].country<<endl;
				_getch(); break;
			case 16:cout<<t; _getch(); break;
		}
	}while(ans!=0);
	delete[] tmp; tmp=0;
	return;
}
//------------------------------------------------------------------------------------------------------

void exTourist::prmsg()
{
	switch(err)
	{
		case 1:	cerr<<"tourist.h: Initialization failure! (out of memory)"<<endl; break;
		case 2: cerr<<"tourist.h: Copy failure! (out of memory)"<<endl; break;
		case 3:	cerr<<"tourist.h: Assignment failure! (out of memory)"<<endl; break;
		
		case 4: cerr<<"tourist.h: Can't set travel pays!"<<endl; break;
		case 5: cerr<<"tourist.h: Can't set travel pay!"<<endl; break;
		case 6: cerr<<"tourist.h: Can't set passport data!"<<endl; break;

		case 7: cerr<<"tourist.h: Can't get passport data!"<<endl; break;
		case 8: cerr<<"tourist.h: Can't get travel data!"<<endl; break;
		case 9: cerr<<"tourist.h: Bad index!"<<endl; break;
	}
	_getch();
}
//------------------------------------------------------------------------------------------------------

tourist::tourist(const char* fn,const char* sn,const char* pn,int bd,const char* pass,const _travel& tr):human(fn,sn,pn,bd)
{
	try
	{ 
		passport=0;
		set_passport(pass); set_travel(tr);
	}
	catch(exTourist obj)
	{
		if(passport){delete[] passport; passport=0;}
		throw exTourist(obj.get_err());
	}
}
tourist::tourist(const tourist& t):human(t)
{
	try
	{
		passport=0;
		set_passport(t.passport); set_travel(t.travel); 
	}
	catch(exTourist obj)
	{
		if(passport){delete[] passport; passport=0;}
		if(obj.get_err()!=1) throw exTourist(obj.get_err());
		throw exTourist(2);
	}
}
tourist::~tourist()
{ 
	travel.~_travel();
	if(passport){ delete[] passport; passport=0;} 
	human::~human();
}

tourist& tourist::operator = (const tourist& t)
{
	if(this==&t) return *this;
	(human&)(*this)=(human&)t;

	if(passport){delete[] passport; passport=0;}
	if(travel.data){delete[] travel.data; travel.data=0; travel.csize=travel.size=0;}
	
	try{ set_passport(t.passport); travel=t.travel; }
	catch(exTourist obj)
	{
		if(passport){delete[] passport; passport=0;}
		if(obj.get_err()!=1) throw exTourist(obj.get_err());
		throw exTourist(3);
	}
	catch(exTrv){throw exTourist(3);}
	return *this;
}

ostream& operator << (ostream& out,const tourist& t)
{
	out<<(human&)t<<endl;
	out<<"** Tourist data **"<<endl;
	out<<"passport: "<<t.get_passport()<<endl;
	out<<t.get_travel()<<endl;
	return out;
}
istream& operator >> (istream& in,tourist& t)
{
	in>>(human&)t;
	int elem=0;
	char* buf=0; buf=new char[char_size];
	cout<<"\n** Tourist data **"<<endl;
	cout<<"Set passport: "; in.getline(buf,pass_size); t.set_passport(buf); *buf=0;
	in>>t.travel;
	delete[] buf; buf=0;
	return in;	
}
