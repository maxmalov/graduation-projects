#include"trader.h"
int trmenu()
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
		cout<<"11. Set passport"<<endl;
		cout<<"12. Set travels"<<endl;
		cout<<"13. Set travel"<<endl;
		cout<<"14. Set adresses"<<endl;
		cout<<"15. Set adress"<<endl;
		cout<<"16. See first name"<<endl;
		cout<<"17. See second name"<<endl;
		cout<<"18. See patro name"<<endl;
		cout<<"19. See birth date"<<endl;
		cout<<"20. See license"<<endl;
		cout<<"21. See registration"<<endl;
		cout<<"22. See TIN"<<endl;
		cout<<"23. See taxes"<<endl;
		cout<<"24. See tax"<<endl;
		cout<<"25. See passport"<<endl;
		cout<<"26. See travels"<<endl;
		cout<<"27. See travel"<<endl;
		cout<<"28. See adresses"<<endl;
		cout<<"29. See adress"<<endl;
		cout<<"30. See all info"<<endl;
		cout<<"0. Back"<<endl;
		ans=ReadN(cin);
	}while(ans<0 || ans>29);
	return ans;
}
void trwork(trader& tr)
{
	char* tmp; tmp=new char[char_size];
	int lic,bd;
	_travel trv;
	_adress adr;
	_tax tax;
	d_c dc;
	d_s ds;
	int ans;
	do
	{
		system("cls");
		ans=trmenu();
		switch(ans)
		{
			case 1:cin>>tr; break;
			case 2:
				cout<<"Set first name: "; cin.getline(tmp,char_size);
				tr.set_fname(tmp); *tmp=0; break;
			case 3:
				cout<<"Set second name: "; cin.getline(tmp,char_size);
				tr.set_sname(tmp); *tmp=0; break;
			case 4:
				cout<<"Set patro name: "; cin.getline(tmp,char_size);
				tr.set_pname(tmp); *tmp=0; break;
			case 5:
				do cout<<"Set birth date : "; while( (bd=ReadN(cin))==-1 );
				tr.set_bdate(bd); break;
			case 6:
				do cout<<"Set license: "; while( (lic=ReadN(cin))==-1 );
				tr.set_bdate(lic); break;
			case 7:
				cout<<"Set registration: "; cin.getline(tmp,char_size);
				tr.set_reg(tmp); *tmp=0; break;
			case 8:
				cout<<"Set TIN: "; cin.getline(tmp,char_size);
				tr.set_TIN(tmp); *tmp=0; break;
			case 9:
				cout<<"Set taxes: "; cin>>tax; tr.set_tax(tax); break;
			case 10:
				do cout<<"Set date: "; while((ds.date=ReadN(cin))==-1);
				do cout<<"Set sum: "; while((ds.sum=ReadN(cin))==-1);
				do cout<<"Set index: "; while((bd=ReadN(cin))==-1);
				tr.set_taxi(ds,bd); break;
			case 11:
				cout<<"Set passport: "; cin.getline(tmp,char_size);
				tr.set_passport(tmp); *tmp=0; break;
			case 12:
				cout<<"Set travels: "; cin>>trv;
				tr.set_travel(trv); trv.~_travel(); break;
			case 13:
				do cout<<"Set date: "; while((dc.date=ReadN(cin))==-1);
				cout<<"Set country: "; cin.getline(tmp,char_size);
				dc.country=new char[strlen(tmp)+1]; strcpy(dc.country,tmp); *tmp=0; break;
				do cout<<"Set index: "; while((bd=ReadN(cin))==-1);
				tr.set_traveli(dc,bd); break;
			case 14:
				cout<<"Set adresses: "; cin>>adr; tr.set_adr(adr); 
				adr.~_adress(); break;
			case 15:
				do cout<<"Index: "; while((bd=ReadN(cin))==-1);
				cout<<"Set adress: "; cin.getline(tmp,char_size);
				tr.set_adri(tmp,bd); *tmp=0; break;		
			case 16:cout<<"First name: "<<tr.get_fname()<<endl; _getch(); break;
			case 17:cout<<"Second name: "<<tr.get_sname()<<endl; _getch(); break;
			case 18:cout<<"Patro name: "<<tr.get_pname()<<endl; _getch(); break;
			case 19:cout<<"Birth date: "<<tr.get_bdate()<<endl; _getch(); break;
			case 20:cout<<"License: "<<tr.get_lic()<<endl; _getch(); break;
			case 21:cout<<"Registration: "<<tr.get_reg()<<endl; _getch(); break;
			case 22:cout<<"TIN: "<<tr.get_TIN()<<endl; _getch(); break;
			case 23:cout<<"Taxes: "<<tr.get_tax()<<endl; _getch(); break;
			case 24:
				do cout<<"Index: "; while((bd=ReadN(cin))==-1);
				cout<<"Date: "<<((employer&)tr)[bd].date<<" Sum: "<<((employer&)tr)[bd].sum<<endl; 
				_getch(); break;
			case 25:cout<<"Passport: "<<tr.get_passport()<<endl; _getch(); break;
			case 26:cout<<"Travels: "<<tr.get_travel()<<endl; _getch(); break;
			case 27:
				do cout<<"Index: "; while((bd=ReadN(cin))==-1);
				cout<<"Date: "<<((tourist&)tr)[bd].date<<" Country: "<<((tourist&)tr)[bd].country<<endl; 
				_getch(); break;
			case 28:cout<<"Adresses: "<<tr.get_adr()<<endl; _getch(); break;
			case 29:
				do cout<<"Index: "; while((bd=ReadN(cin))==-1);
				cout<<"Adress: "<<tr[bd]; _getch(); break;
			case 30:cout<<tr; _getch(); break;
		}
	}while(ans!=0);
	delete[] tmp; tmp=0;
	return;
}
//-----------------------------------------------------------------------------------------------//
void exTrader::prmsg()
{
	switch(err)
	{
		case 1: cerr<<"trader.h: Copy failure! (out of memory)"<<endl; break;
		case 2:	cerr<<"trader.h: Assignment failure! (out of memory)"<<endl; break;
		case 3:	cerr<<"trader.h: Bad index!"<<endl; break;
	}
	_getch();
}
//--------------------------------------------------------------------------------------------------//
trader::trader(const trader& trad):human(trad),employer(trad),tourist(trad)
{
	int i;
	try
	{
		adress.csize=trad.adress.csize;
		adress.size=trad.adress.size;
		adress.data=new char*[trad.adress.size];
		for(i=0;i<adress.csize;++i)
		{
			adress.data[i]=new char[strlen(trad[i])+1];
			strcpy(adress.data[i],trad[i]);
		}
		for(int i=adress.csize;i<adress.size;++i) adress.data[i]=0;
	}
	catch(bad_alloc)
	{
		if(adress.data)
		{
			for(int j=0;j<i;++j){ delete[] adress.data[i]; adress.data[i]=0; }
			delete[] adress.data; adress.data=0;
		}
		throw exTrader(1);
	}
}
trader::~trader()
{
	adress.~_adress();
	tourist::~tourist();
	employer::~employer();
}
trader& trader::operator =(const trader& trad)
{
	if(this==&trad) return *this;
	(employer&)(*this)=(employer&)trad;
	(tourist&)(*this)=(tourist&)trad;

	if(adress.data)
	{		
		for(int i=0;i<adress.csize;++i){ delete[] adress.data[i]; adress.data[i]=0; }
		delete[] adress.data; adress.data=0;
	}

	int i;
	try
	{
		adress.csize=trad.adress.csize;
		adress.size=trad.adress.size;
		adress.data=new char*[trad.adress.size];
		for(i=0;i<adress.csize;++i)
		{
			adress.data[i]=new char[strlen(trad[i])+1];
			strcpy(adress.data[i],trad[i]);
		}
		for(int i=adress.csize;i<adress.size;++i) adress.data[i]=0;
	}
	catch(bad_alloc)
	{
		if(adress.data)
		{
			for(int j=0;j<i;++j){ delete[] adress.data[i]; adress.data[i]=0; }
			delete[] adress.data; adress.data=0;
		}
		throw exTrader(2);
	}
	return *this;
}
ostream& operator <<(ostream& out,const trader& trad)
{
	out<<(employer&)trad<<endl;
	out<<"** Tourist data **"<<endl;
	out<<"passport: "<<trad.get_passport()<<endl;
	out<<trad.get_travel()<<endl;
	out<<"** Trader data **"<<endl;
	out<<trad.get_adr()<<endl;
	return out;
}
istream& operator >>(istream& in,trader& trad)
{
	in>>(employer&)trad;
	int elem=0;
	char* buf=0; buf=new char[char_size];
	cout<<"\n** Tourist data **"<<endl;
	cout<<"Set passport: "; in.getline(buf,pass_size); trad.set_passport(buf); *buf=0;
	in>>trad.travel;
	delete[] buf; buf=0;
	cout<<"\n** Trader data **"<<endl;
	in>>trad.adress;
	return in;
}