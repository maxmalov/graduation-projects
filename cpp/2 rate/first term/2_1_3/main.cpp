#include "L1_work.h"
/*
  41. Дан список слов среди которых есть пустые. Написать функции:
      1. Поменять первое и последнее непустые слова местами.
	  2. Напечатать текст из первых букв непустых слов.
	  3. Удалить из непустых слов первые буквы.
	  4. Определить количество слов в непустом списке, отличных от последнего.
  Автор: Малов Максим МП-703
*/
void main(int argc, char* argv[])
{
	GetList1* GL1=0;
	char ans1, ans2, ans3, ans4;
	char* word=0;
	List1* tmp=0;
	do
	{
		ans1=MainMenu();
		switch(ans1)
		{
		    case 1:
			{	
				do
				{
					ans2=ListOptionMenu();
					switch(ans2)
					{
						case 1:
							if(GL1) 
							{
								Destroy(GL1); 
								try {GL1=Create();}
								catch(std::bad_alloc) {PrintMessage(2);}
							}
							else
							{
								try{GL1=Create();}
								catch(std::bad_alloc) {PrintMessage(2);}
							}
							break;
						case 2:
							if(GL1)
							{
								try{GL1=ReadF(argv[1],GL1);}
								catch(std::bad_alloc){PrintMessage(2);}
								catch(exBadFile){PrintMessage(7);}
							}
		                    else PrintMessage(5);
							break;
						case 3: 
							if(GL1)
							{
								try
								{ 
									word=new char[char_size];
									std::cout<<"Enter word: ";
									std::cin.getline(word,char_size); 
									AddToBegin(GL1,word);
									delete word;
								}
								catch(std::bad_alloc){PrintMessage(2);}
								//catch(exBadList){PrintMessage(3);}
							}
		                    else PrintMessage(5);
							break;
						case 4: 
							if((GL1)&&(!IsEmpty(GL1)))
							{
								try
								{ 
									word=new char[char_size];
									std::cout<<"Enter word: ";
									std::cin.getline(word,char_size); 
									AddAfterCurrent(GL1,word);
									delete word;
								}
								catch(std::bad_alloc){PrintMessage(2);}
								//catch(exBadList){PrintMessage(3);}
							}
							else 
							{
								if(!GL1) PrintMessage(5);
								else 
									if(IsEmpty(GL1)) PrintMessage(3);
							}
							break;
						case 5:
							if((GL1)&&(!IsEmpty(GL1)))
							{
								try
								{ 
									word=new char[char_size];
									std::cout<<"Enter word: ";
									std::cin.getline(word,char_size); 
									AddToEnd(GL1,word);
									delete word;
								}
								catch(std::bad_alloc){PrintMessage(2);}
								//catch(exBadList){PrintMessage(3);}
							}
							else 
							{
								if(!GL1)PrintMessage(5);
								else
									if(IsEmpty(GL1)) PrintMessage(3);
							}
							break;
						case 6:
							if(GL1)
							{
								try{DelBegin(GL1);}
								catch(exBadList){PrintMessage(3);}
							}
							else PrintMessage(5);
							break;
						case 7:
							if(GL1)
							{
								try{DelAfterCurrent(GL1);}
								catch(exBadList){PrintMessage(3);}
							}
							else PrintMessage(5);
							break;
						case 8:
							if((GL1)&&(!IsEmpty(GL1)))
							{
								try{DelEnd(GL1);}
								catch(exBadList){PrintMessage(3);}
							}
							else PrintMessage(5);
							break;
						case 9:
							if(GL1)
							{
								try{ToBegin(GL1);}
								catch(exBadList){PrintMessage(3);}
							}
							else PrintMessage(5);
							break;
						case 10:
							if(GL1)
							{
								try{ToNext(GL1);}
								catch(exBadList){PrintMessage(3);}
							}
							else PrintMessage(5);
							break;
						case 11:
							if(GL1)
							{
								try{ToEnd(GL1);}
								catch(exBadList){PrintMessage(3);}
							}
							else PrintMessage(5);
							break;
						case 12:
							if(GL1)
							{
								try{std::cout<<"Current word: "<<See(GL1); _getch();}
								catch(exBadList){PrintMessage(3);}
							}
							else PrintMessage(5);
    						break;
						case 13:
							if(GL1)
							{							
								do
								{
									std::cout<<"Removing list..."<<std::endl;
									if(!IsEmpty(GL1))
									{
										std::cout<<"1. Clear list"<<std::endl;
										std::cout<<"2. Delete list"<<std::endl;
										ans3=_getch();
										switch(ans3)
										{
											case '1': MakeEmpty(GL1); break;
											case '2': Destroy(GL1); break;
										}
									}
									else { Destroy(GL1); ans3='1';}
								}while((ans3!='1')&&(ans3!='2'));
							}
							else PrintMessage(5);
							break;
						case 14:
							if((GL1)&&(!IsEmpty(GL1))) 
							{ 
								if(IsEnd(GL1)) { std::cout<<"End of list"<<std::endl; _getch(); } 
								else { std::cout<<"Not end of list"<<std::endl; _getch(); }
							}
							else 
							{
								if(!GL1)PrintMessage(5);
								else
									if(IsEmpty(GL1)) PrintMessage(3);
							}
							break;
						case 15:
							if(GL1) 
							{ 
								if(IsEmpty(GL1)) { std::cout<<"List is empty"<<std::endl; _getch(); } 
								else { std::cout<<"List isn`t empty"<<std::endl; _getch(); }
							}
							else PrintMessage(5);
							break;
						case 16:
							if(GL1)
							{
								try{ PrintList(GL1); }
								catch(exBadList){PrintMessage(3);}
							}
							else PrintMessage(5);
							break;
					}
				}while(ans2!=0);
				break;
			}
            case 2:
			{
				if(GL1)
				{
					do
					{
						ans4=ListWorkMenu();
						switch(ans4)
						{
                			case 1:
								try{PrintList(GL1); TopToEnd_EndToTop(GL1); PrintList(GL1);}
								catch(exBadList){PrintMessage(6);}
								catch(std::bad_alloc){PrintMessage(2);}
								break;
							case 2:
								try{PrintFirstLetters(GL1);}
								catch(exBadList){PrintMessage(3);}
								break;
							case 3:
								try{DelFirstLetters(GL1);}
								catch(exBadList){PrintMessage(3);}
								break;
							case 4:
								try
								{
									PrintList(GL1);
									std::cout<<"Result: "<<CountWordsDifferFromLast(GL1)<<std::endl;
									_getch();
								}
								catch(exBadList){PrintMessage(3);}
								break;
						}
					}while(ans4!=0);
					break;
				}
				else PrintMessage(5);
				break;
			}
		}
	}while(ans1!=0);
	if(GL1) Destroy(GL1);
}