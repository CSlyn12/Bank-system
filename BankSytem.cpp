#include<iostream>
#include<fstream>
#include<cstring>

using namespace std;

struct bankAccount
{
	int accNumber;
	char name[20];
	double balance;
	
};
//-------------------------------------------------------------------------------------------
//prototypes

void intro();
void createNew();
void  showAccounts();
void display(const bankAccount& acc);
void dep_Withdraw(int n);



//-------------------------------------------------------------------------------------------
int main()
{
	intro();
	char ch;
	bankAccount account;
	do
	{	
		//Option Menu loop until choice is not equal to number 4 ("EXIT")

		system("cls");
		cout<<"\n\n\n\t-------------------MAIN MENU-------------------";
		cout<<"\n\n\t1 		 NEW ACCOUNT					";
		cout<<"\n\n\t2 		EXISTING ACCOUNT				";
		cout<<"\n\n\t3 		DISPLAY RECORDS					";
		cout<<"\n\n\t4 			EXIT					";
		cout<<"\n\n\n\t-----------------------------------------------";
		cout<<"\n\n\tSelect Option (1-4):\t ";
		cin>>ch;
		system("cls");
		
		
		switch(ch)
		{
			case '1':
				createNew();
				break;
			case '2':
				int num;
				cout<<"\n\n\tEnter The account No. : "; 
				cin>>num;
				dep_Withdraw(num);
				break;			
			case '3':
				showAccounts();		
				break;
	
		 case '4':
			cout<<"\n\n\tThanks for using bank managemnt system";
			break;

		 default :cout<<"Wrong code";
		}
		cin.ignore();
		cin.get();
		
		
	}while(ch!=4);
	system ("pause");
	return 0;
}

void intro()
{
	cout <<"\n\n\t\t\tW E L C O M E 	T O	  C A R L O N B A N K";	
	cout<<"\n\n\t\t\t\t\tM A N A G E M E N T";
	cout<<"\n\n\t\t\t\t\t S Y S T E M"<<endl<<endl;	
	system("pause");	
}
//-----------------------------------------------------------------------------------------------------------
void createNew()
{
  //creates a appends a new entry 

	bankAccount account;

	ofstream outFile;
	outFile.open("bankfile.dat",ios::binary|ios::app);
	
	do
	{		
		cout << "\t\tENTER 2-DIGIT ACOUNT NUMBER : ";		
		cin >> account.accNumber;
		
		if(account.accNumber <10 || account.accNumber>100)
		{							
		  cout <<"\n\n\t\t\tSORRY, YOU'VE ENTERED A WRONG ACCOUNT NUMBER!!' "<<endl<<endl;							
		}
		else
			break;	 
	  
	}while(account.accNumber <10 || account.accNumber>100);
	
	cout<<"\t\tENTER NAME: ";
	cin.ignore();
  	cin.getline(account.name, 30);
	  
	do
	{
		cout<<"\nEnter The Initial deposit (Minimum initial deposit is PHP 1,000 ) : ";
		cin>>account.balance;
		
		if (account.balance<1000)		
			cout <<"\n\n\n\t\t\tI N S U F F I C I E N T		A M O U N T!!!"<<endl<<endl;		
		
		else
		{
			cout<<"\n\n\n\n\t\t\tCONGRATULATIONS!!!	YOU'VE SUCCESSFULLY OPENED A NEW ACCOUNT."<<endl<<endl;
			break;
		}
			
	}while(account.balance<1000);
	
	long recordSize = sizeof(account);
	outFile.seekp((account.accNumber -1)* recordSize, ios::beg);
	
	outFile.write(reinterpret_cast<char *> (&account), sizeof(bankAccount));
	cout <<"----------------------------------------------------------------------------------------------------------------------";
	outFile.close();
	
}
//---------------------------------------------------------------------------------------------------------
void  showAccounts()
{
	bankAccount acc;
	ifstream inFile;
	inFile.open("bankFile.dat", ios::binary);
	while(inFile)
	{
		inFile.read(reinterpret_cast <char*> (&acc), sizeof(acc));	
		display(acc);
	}
	
	inFile.close();
}
//----------------------------------------------------------------------------------------------------------------------

void display(const bankAccount& acc)
{
	cout<<"Account number:\t"<<acc.accNumber<<endl<<"Name:\t"<<acc.name<<endl<<"Balance:\t"<<acc.balance<<endl<<endl;
}
//----------------------------------------------------------------------------------------------------------------------
void dep_Withdraw(int n)
{
	double amt;
	double bal;
	int pos;
	bool found = false;	
	bankAccount account;
	fstream inFile;
	inFile.open("bankfile.dat", ios::binary|ios::in|ios::out);
	
	if(!inFile)
		{
			cout<<"File could not be open !! Press any Key...";
			
		}			
	
		while(!inFile.eof() && found == false)
		{
			inFile.read(reinterpret_cast<char *> (&account), sizeof(account));
			if(n== account.accNumber) 		
			{
				cout<<"Account number:\t"<<account.accNumber<<endl;
				cout<<"Name:\t"<<account.name<<endl;				
				char choice;
				do
				{
					cout<<"\n\n";
					cout<<"\n\n\n\t--------TRANSACTION TYPE---------\n";
					cout<<"\n\n\t[B]	 BALANCE INQUIRY								";
					cout<<"\n\n\t[D] 		 DEPOSIT									";
					cout<<"\n\n\t[W] 		WITHDRAW			";
					cout<<"\n\n\t[E] 		END TRANSACTION				";
					cout<<"\n\n\n\t----------------------------------\n";
					cout<<"Choose transaction type:\t";
					cin.ignore();
					cin>>choice;
					choice = toupper(choice);
					system("cls");
					
					switch(choice)
					{
						
					
						case 'D':
						
							cout<<"\n\n\tTO DEPOSIT AMOUNT ";
							cout<<"\n\nEnter The amount to be deposited:\t";
							cin>>amt;
							account.balance+=amt;
							cout<<"New balance is:\t"<<account.balance<<endl;
							break;
							
						case 'W':					
							cout<<"\n\n\tTO WITHDRAW AMOUNT ";
							cout<<"\n\nEnter The amount to be withdraw:\t";
							cin>>amt;
							bal=account.balance-amt;
									
							if((bal<500 ))
								cout<<"Insufficience balance!";
							else
							{
								account.balance-=amt;
								cout<<"New balance is:\t"<<account.balance<<endl;
								break;
								
							}
								
								
						case'B':				
							cout<<"\nBalance is:\t"<<account.balance<<endl<<endl;
							break;
					
						case'E':
							cout<<"\n\n\t\t\tThank you for banking with us!"<<endl;
							break;
						default :cout<<"Wrong code";
					}
			
				}while(choice!='E');
				int pos = (-1* sizeof(account));
				inFile.seekp(pos, ios::cur);
				inFile.write(reinterpret_cast<char *> (&account), sizeof(account));
				found=true;	
			
				
			}						
    	}
 		    inFile.close();
			if(found==false)
			cout<<"\n\n Record Not Found ";				
}
//---------------------------------------------------------------------------------------------------------------


