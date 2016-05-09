#include<iostream.h>
#include<stdio.h>
#include<conio.h>
#include<process.h>
#include<string.h>
#include<fstream.h>

//CLASS TO STORE TRAIN DETAILS
class train {
				  public:
				  int trainno,d,s;
				  char tname[20],zone[10];
				  float dist_station[10];
				  char departure[10],arrival[10];
				  char station[10][10];
				  char days[7][10];
				  void get_data();
				  void put_data();
				  void getday();
				  void putday();
				  void putstation();
				  void getstation();
				  void modify();
				};

//CLASS TO KEEP THE TRACK OF TICKETS AND SEATS OF A TRAIN
class seats{
				 public:
				 int trainno;
				 int tot_seats_ac_tier;
				 int bkd_seats_ac_tier;
				 int ac_seats[48];
				 int sleeper_seats[72];
				 int tot_seats_sleeper_class;
				 int bkd_seats_sleeper_class;
				 int pnr[120];
				 seats()
				 {
					 bkd_seats_sleeper_class=0;
					 bkd_seats_ac_tier=0;
					 tot_seats_sleeper_class=72;
					 tot_seats_ac_tier=48;
				 }
			  }seat_ob[50];

			  int sctr=0;       //ARRAY SEAT COUNTER
			  int pactr=0;      //PNR AC COUNTER
			  int psctr=49;      //PNR SLEEPER CLASS COUNTER

//FUNCTION TO GET TRAIN DETAILS
void train::get_data()
{
	cout<<"\n\n         *TRAIN NAME ";
	gets(tname);
	getstation();
	cout<<"\n\n         *ZONE";
	gets(zone);
	cout<<"\n\n         *SCHEDULED DAYS OF DEPARTURE "<<endl;
	getday();
	cout<<"\n\n         *ARRIVAL TIME(HH:MM:SS)";
	gets(arrival);
}

//FUNCTION TO GET THE SCHEDULED DAYS FOR DEPARTURE
void train::getday()
{
  char ans;
  int n=0;
  do{
		 cout<<"\n "<<(n+1)<<">";
		 gets(days[n]);
		 n++;
		 cout<<"\n        IF MORE (ENTER y FOR YES )" ;
		 cin>>ans;
	  }while(ans=='y'||ans=='Y');
  d=n;
}


//FUNCTION TO DISPLAY THE SCHEDULED DAYS OF DEPARTURE OF A TRAIN

void train::putday()
{
	  for(int i=0;i<d;i++)
		{
			cout<<"\n\n      \t\t"<<(i+1)<<">";
			puts(days[i]);
		}
}

//FUNCTION TO GET THE STATIONS PLYING IN THE ROUTE OF A TRAIN

void train::getstation()
{
  char ans;
  int n=0;
  cout<<"\n\n          ";
  cout<<"\n\n        *STATIONS PLYING IN BETWEEN";
  do
  {   cout<<endl<<"            "<<(n)<<">";
		gets(station[n]);
		cout<<"\n      *DISTANCE FROM ORIGIN(IN K.m.s)";
		cin>>dist_station[n];
		n++;
		cout<<"\n            IF MORE STATIONS PRESS y TO CONTINUE ";
		cin>>ans;
  }while(ans=='y'||ans=='Y');
  cout<<"\n\n  *DESTINATION ";
  gets(station[n]);
  cout<<"\n\n    *DISTANCE FROM ORIGIN(IN K.m.s)";
  cin>>dist_station[n];
  s=n;
  }

//FUNCTION TO DISPLAY THE STATIONS PLYING IN THE ROUTE OF A TRAIN

void train :: putstation()
 {
	int n=0;
	cout<<"\n\n\t\t*ORIGINATING PLACE ::";
	puts(station[n]);
	cout<<"\n\n\t\t*DESTINATION::";
	puts(station[s]);
	cout<<"\n\t\t->DISTANCE FROM ORIGIN ::"<<dist_station[s];
	cout<<"\n\n\n\t\t*STATIONS PLYING IN BETWEEN ::";
	for(int i=1;i<s;i++)
	 {
		 cout<<endl<<"\n\t\t "<<i<<">";
		 puts(station[i]);
		 cout<<"\n\t\t->DISTANCE FROM ORIGIN ::"<<dist_station[s];
	 }
  }

//FUNCTION TO DISPLAY DATA

void train::put_data()
{
	clrscr();
	cout<<"\t\t***********TRAIN RECORD*******************";
	cout<<"\n\n\t\t*TRAIN NO ::"<<trainno;
	cout<<"\n\n\n\t\t*TRAIN NAME ::";
	puts(tname);
	cout<<"\n\n\t\t *ZONE ::";
	puts(zone);
	cout<<"\n\n\t\t*DEPARTURE TIME(HH:MM:SS) :: "<<arrival;
	getch();
	clrscr();
	cout<<"\n\n\t\t*SCHEDULED DAYS OF DEPARTURE ::";
	putday();
	putstation();
}

 //FUNCTION TO MODIFY THE DETAILS OF A TRAIN

 void train::modify()
 {
	  char ans;
	  int ch;
	  do
	  {
		 clrscr();
		 gotoxy(24,6);
		 cout<<"MENU TO MODIFY :";
		 gotoxy(2,10);
		 cout<<" 1.TRAIN NAME ";
		 gotoxy(2,13);
		 cout<<" 2.ROUTE ";
		 gotoxy(2,16);
		 cout<<"  3.SCHEDULED DAYS OF DEPARTURE ";
		 gotoxy(6,19);
		 cout<<"ENTER YOUR CHOICE :";
		 cin>>ch;
		 switch(ch)
		 {
			 case 1: {
							 clrscr();
							 cout<<"\n ENTER THE NEW NAME :";
							 gets(tname);
							 break;
						 }
			 case 2:{
							 clrscr();
							 cout<<"\nENTER THE NEW ROUTE :";
							 getstation();
							 break;
						}
			 case 3:{
							 clrscr();
							 cout<<"\nENTER THE SCHEDULED DAYS FOR DEPARTURE";
							 getday();
							 break;
					  }
			 default:{ cout<<endl<<"WRONG OPTION";
						  break;
						}
		  }
		 cout<<"\n\n DO YOU WANT TO MODIFY FURTHER :";
		 cin>>ans;
	 }while(ans=='Y'||ans=='y');
	 getch();
  }

//FUNCTION TO WRITE THE DETAILS OF A TRAIN INTO FILE

void add_new()
{
	clrscr();
	fstream f1("train.txt",ios::app|ios::binary);
	train t;
	if(!f1)
	 {
		 cout<<"File cannot be opened ";
		 exit(0);
	 }
	cout<<"\n\n         *TRAIN CODE ";
	cin>>t.trainno;
	seat_ob[sctr].trainno=t.trainno;
	sctr++;
	t.get_data();
	f1.write((char*)&t,sizeof(t));
	f1.close();
	getch();
	//f1.close();
 }//FUNCTION ENDS

//FUNCTION TO MODIFY THE DETAILS OF A TRAIN INTO FILE

void modify(int tno)
 {
	char ans;
	int flag=2;
	fstream f1,f2;
	f1.open("Re.txt",ios::in|ios::binary);
	if(!f1)
	{
	  cout<<" file cannot open ";
	  getch();
	  exit(0);
	}
	f2.open("temp.txt",ios::app|ios::binary);
	train t;
	f1.seekg(0);
	f1.read((char*)&t,sizeof(t));
	while(!f1.eof())
	{
		if(t.trainno!=tno)
		 {
			flag=0;
			f2.write((char*)&t,sizeof(t));
		 }
		 else if(t.trainno==tno)
		  {
			 flag=1;
			 t.put_data();
			 cout<<"\n\n        DO YOU WANT TO TO MODIFY?Y\N ";
			 cin>>ans;
				if(ans=='y'||ans=='Y')
				 {
					 t.modify();
					 f2.write((char*)&t,sizeof(t));
					 clrscr();
					 cout<<"  TO VIEW THE MODIFIED RECORD PRESS ANY KEY TO CONTINUE";
					 getch();
					 clrscr();
					 t.put_data();
					 getch();
				 }
			  else
				f2.write((char*)&t,sizeof(t));
		  }
		  if(flag==0)
			{
				clrscr();
				cout<<"\n\n    RECORD NOT FOUND ";
				getch();
			 }
			f1.close();
			f2.close();
			remove("Re.txt");
			rename("temp.txt","Re.txt");
	}
 }	//FUNCTION ENDS

//FUNCTION TO DELETE THE DETAILS OF A TRAIN FROM A FILE

void deletion(int tno)
{
  fstream f1,f2;
  train t;
  int flag=1;
  for(int i=0;i<sctr;i++)
  {
	 if(tno==seat_ob[i].trainno)
		{
		  seat_ob[i].trainno=0;  //initialize it to an arbitary value
		}
	}
	f1.open("train.txt",ios::in|ios::binary);
	f2.open("temp.txt",ios::out|ios::binary);
	f1.read((char*)&t,sizeof(t));
	while(!f1.eof())
	{
	  if(t.trainno!=tno)
		{
		flag=0;
		f2.write((char*)&t,sizeof(t));
		}
		else if(t.trainno==tno)
		 flag=2;
		f1.read((char*)&t,sizeof(t));
	}
	f1.close();
	f2.close();
	remove("Re.txt");
	rename("temp.txt","Re.txt");
	if(flag==2)
	{
	  clrscr();
	  cout<<"\n THE RECORD HAS BEEN DELETED ";
	  getch();
	}
	else if(flag==0)
	{
	 clrscr();
	 cout<<"\n RECORD NOT FOUND";
	 getch();
	}
}//FUNCTION ENDS

 /*FUNCTION TO SEARCH TRAIN DETAILS DEPENDING ON TRAIN ON TRAIN NAME AND
	TRAIN CODE*/

void search()
 {
  clrscr();
  void search_byname();
  void search_byno();
  int ch;
  clrscr();
  gotoxy(27,4);
  cout<<"***TRAIN SEARCH***";
  gotoxy(7,10);
  cout<<"1.TRAIN NAME";
  gotoxy(7,13);
  cout<<"2.TRAIN CODE";
  gotoxy(7,16);
  cout<<"3.RETURN BACK";
  gotoxy(27,19);
  cout<<"ENTER YOUR CHOICE= ";
  cin>>ch;
  switch(ch)
  {
	 case 1:
	 {
		search_byname();
		break;
	 }
	 case 2:
	 {
		search_byno();
		break;
	 }
	 case 3:
	  break;
	 default:
	  {
		 cout<<"\n YOU HAVE ENTERED THE WRONG CHOICE";
		 break;
		}
	}
 }//FUNCTION ENDS

//FUNCTION TO SEARCH TRAIN DETAILS DEPENDING ON TRAIN NAME
void search_byname()
{
  int flag=0;
  char name[10];
  fstream f;
  f.open("Re.txt",ios::in|ios::binary);
  train t;
  cout<<"\n ENTER THE TRAIN NAME YOU WANT TO SEARCH :";
  gets(name);
  f.read((char*)&t,sizeof(t));
  while(!f.eof())
	{
	  if(strcmp(t.tname,name)==0)
		{
		  clrscr();
		  t.put_data();
		  flag=1;
		}
	 f.read((char*)&t,sizeof(t));
	}//WHILE ENDS

	if(flag==0)
	  cout<<"\n RECORD NOT FOUND ";
	  getch();
}//FUNCTION ENDS

//FUNCTION TO SEARCH TRAIN DETAILS DEPENDING ON TRAIN CODE

void search_byno()
{
	int flag=0;
	int tno;
	fstream f;
	f.open("Re.txt",ios::in|ios::binary);
	train t;
	cout<<"\n ENTER THE TRAIN NAME YOU WANT TO SEARCH :";
	cin>>tno;
	f.read((char*)&t,sizeof(t));
	while(!f.eof())
	 {
		if(t.trainno==tno)
		{
		  clrscr();
		  t.put_data();
		  flag=1;
		 }
	  f.read((char*)&t,sizeof(t));
	 }//WHILE ENDS

	if(flag==0)
	 {
	  cout<<"\n RECORD NOT FOUND ";
	  }
	  getch();
}//FUNCTION ENDS

//FUNCTION TO PERFORM OPERATIONS ON TRAIN DETAILS
void train_details()
{
  int ch1;
  clrscr();

  do
	{
	  clrscr();
	  gotoxy(27,4);
	  cout<<"*****TRAIN MENU*****";
	  gotoxy(7,8);
	  cout<<"1.ADD NEW RECORDS";
	  gotoxy(7,10);
	  cout<<"2.MODIFY RECORDS";
	  gotoxy(7,12);
	  cout<<"3.DELETE RECORDS";
	  gotoxy(7,14);
	  cout<<"4.SEARCH RECORDS";
	  gotoxy(7,16);
	  cout<<"5.RETURN TO MAIN MENU ";
	  gotoxy(27,18);
	  cout<<"ENTER YOUR CHOICE=";
	  cin>>ch1;
	  switch(ch1)
	  {
		 case 1:{
					 add_new();
					 break;
				  }
		 case 2:{
					 int tno;
					 cout<<"\n ENTER THE TRAIN NO YOU WANT TO MODIFY:";
					 cin>>tno;
					 modify(tno);
					 break;
					}
		 case 3:{
					 int tno;
					 cout<<"\n ENTER THE TRAIN NO YOU WANT TO DELETE:";
					 cin>>tno;
					 deletion(tno);
					 break;
					}
		  case 4:{
						search();
						break;
					}
		  case 5:{
					  break;
					}
		  default:{
						 cout<<"\n\n WRONG OPTION";
						 getch();
						 break;
						}
	  }//SWITCH ENDS
  }while(ch1>=1&&ch1<5);
}//FUNCTION ENDS

void book_tickets();
void cancel_tickets();


//FUNCTION ON PASSENGER MENU

void passenger_details()
{
			int ch;
			clrscr();
			gotoxy(24,5);
			cout<<"*********PASSENGER MENU****************";
			gotoxy(10,10);
			cout<<"1.BOOK A TICKET ";
			gotoxy(10,13);
			cout<<"2. CANCEL A TICKET";
			gotoxy(10,16);
			cout<<"3. RETURN TO THE MAIN MENU ";
			gotoxy(27,22);
			cout<<" ENTER YOUR CHOICE: ";
			cin>>ch;
			switch(ch)
			 {
				 case 1:{
									book_tickets();
									clrscr();
									break;
						  }
				 case 2:{

									cancel_tickets();
									clrscr();
									break;
							}
				 case 3:{
								  break;
						  }
				default:{
									 cout<<"\n\n  WRONG OPTION ";
									 break;
						  }
			  }
			  getch();
 }//FUNCTION ENDS

//FUNCTION TO BOOK TICKETS IN AC TIER

void book_ac(int i,int no)//i>=the train record identified & no>=no of heads
 {
	 int ctr=0;
	 char ans;
	 int j,k;
	 if(seat_ob[i].tot_seats_ac_tier==seat_ob[i].bkd_seats_ac_tier)
	  {
		 cout<<endl<<"\n\n     *NO SEATS VACANT ";
	  }
  else
	{

			for(j=0;j<no;j++)
			 {
				 if(seat_ob[i].tot_seats_ac_tier!=seat_ob[i].bkd_seats_ac_tier)
					ctr++;
			 }//FOR ENDS

		cout<<"\n\n     *SEATS AVAILABLE ::"<<ctr;
		cout<<"\n\n     *DO YOU WANT TO BOOK THE TICKETS ?";
		cin>>ans;
		if(ans=='y'||ans=='Y')
		 {
			  clrscr();
			  for(k=0;k<no;k++)
				{
					seat_ob[i].bkd_seats_ac_tier++;
					seat_ob[i].pnr[pactr]=(pactr+1);
					seat_ob[i].ac_seats[pactr]=(pactr+1);
					cout<<"\n\n         *TICKET "<<(k+1);
					cout<<"\n\n         ->PNR "<<seat_ob[i].pnr[pactr];
					cout<<"\n\n         ->SEAT NO"<<seat_ob[i].ac_seats[pactr];
					cout<<"\n\n         ->RESERVATION CHARGES=Rs.250";
					cout<<"\n\n         ->FARE=Rs.600";
					cout<<"\n\n         ->TOTAL AMOUNT=Rs.850 ";
					pactr++;
					getch();
					clrscr();
				 }//FOR ENDS
		  }//INNER IF ENDS
		}//OUTER ELSE ENDS
	 }//FUNCTION ENDS

 //FUNCTION TO BOOK TICKETS IN SLEEPER CLASS

void book_sleeper(int i,int no)
 {
	 int ctr=0;
	 char ans;
	 if(seat_ob[i].tot_seats_sleeper_class==seat_ob[i].bkd_seats_sleeper_class)
	  {
		  cout<<endl<<"\n\n   *NO SEATS VACANT ";
		}
	 else
	  {
	 for(int j=0;j<no;j++)
	  {
		if(seat_ob[i].tot_seats_sleeper_class!=seat_ob[i].bkd_seats_sleeper_class)
				 ctr++;
		}//FOR ENDS
  cout<<"\n\n           *SEATS AVAILABLE:: "<<ctr;
  cout<<"\n\n           *DO YOU WANT TO BOOK THE TICKETS ?";
  cin>>ans;
  if(ans=='y'||ans=='Y')
	 {
		 clrscr();
		 for(int k=0;k<no;k++)
		  {
				seat_ob[i].bkd_seats_sleeper_class++;
				seat_ob[i].pnr[psctr]=(psctr+1);
				seat_ob[i].sleeper_seats[psctr]=(psctr+1);
				cout<<"\n\n        *TICKETS "<<(k+1);
				cout<<"\n\n        ->PNR"<<seat_ob[i].pnr[psctr];
				cout<<"\n\n        ->SEAT NO ";
				cout<<seat_ob[i].sleeper_seats[psctr];
				cout<<"\n\n       ->RESERVATION CHARGES=Rs.250 ";
				cout<<"\n\n       ->FARE=Rs.300 ";
				cout<<"\n\n       ->TOTAL AMOUNT=Rs.550 ";
				psctr++;
				psctr++;
				getch();
			 }//FOR ENDS
		 }//INNER IF ENDS
	  }//OUTER IF ENDS
	}//FUNCTION ENDS

//FUNCTION TO BOOK TICKETS
void book_tickets()
{
	clrscr();
	int trainno,no,cls,flag=0;
	cout<<"\n\n     *ENTER THE TRAIN NO ";
	cin>>trainno;
	for(int i=0;i<sctr;i++)
	 {
		 if(seat_ob[i].trainno==trainno)
		  {
				if(seat_ob[i].trainno==trainno)
				  {
					  flag=1;
					  cout<<"\n\n    ENTER THE NO OF HEADS ";
					  cin>>no;
					  cout<<"\n\n    ENTER THE CLASS ";
					  cout<<"\n\n    1>AC CLASS ";
					  cout<<"\n\n    2>GENERAL SLEEPER CLASS ";
					  cin>>cls;
					  if(cls==1)
							book_ac(i,no);
					  else if(cls==2)
							book_sleeper(i,no);
					  else
							cout<<endl<<" WRONG OPTION ";
					}
			 }
			if(flag==0)
			{
				clrscr();
				cout<<"\n\n   *RECORD NOT  FOUND ";
				getch();
			}
	  }
	  }//FUNCTION ENDS

  //FUNCTION TO CANCEL THE TICKETS BELONGING TO AC TIER

  void cancel_ac(int i,int pnr)
	{
	  int flag=0;
	  if(pactr==0)
		{
		  cout<<"\n\n NO TICKETS HAVE BEEN BOOKED ";
		  getch();
		}
	  else
	  {
		 for(int x=0;x<pactr;x++)
		  {
			  if(pnr==seat_ob[i].pnr[x])
				{
					flag=1;
					cout<<"\n\n     *TICKET CANCELLED ";
					cout<<"\n\n      MONEY REFUNDED Rs.600 ";
					seat_ob[i].pnr[x]=0;
					seat_ob[i].ac_seats[x]=0;
					seat_ob[i].bkd_seats_ac_tier--;
				 }
			}//FOR ENDS
		}//ELSE ENDS
	if(flag==0)
	 {
		cout<<" THE PNR DOESNOT EXIT \n";
		getch();
	 }
	}//FUNCTION ENDS

//FUNCTION TO CANCEL THE TICKETS BELONGING TO SLEEPER CLASS

void cancel_sleeper(int i,int pnr)
	{
	  int flag=0;
	  if(pactr==49)
		{
		  cout<<"\n\n NO TICKETS HAVE BEEN BOOKED ";
		  getch();
		}
	  else
	  {
		 for(int x=49;x<psctr;x++)
		  {
			  if(pnr==seat_ob[i].pnr[x])
				{
					flag=1;
					cout<<"\n\n     *TICKET CANCELLED* ";
					cout<<"\n\n      MONEY REFUNDED Rs.400 ";
					seat_ob[i].pnr[x]=0;
					seat_ob[i].sleeper_seats[x]=0;
					seat_ob[i].bkd_seats_sleeper_class--;
				 }
			}//FOR ENDS
		}//ELSE ENDS
	 if(flag==0)
	  { cout<<"  THE PNR DOESNOT EXIST   \n";
		 getch();
	  }
	}//FUNCTION ENDS

//FUNCTION TO CANCEL THE TICKETS

void cancel_tickets()
{
  clrscr();
  int cls,trainno,pnr,flag=0;
  cout<<"\n\n         *ENTER THE TRAIN NO ";
  cin>>trainno;
  for(int i=0;i<sctr;i++)
	{
		if(seat_ob[i].trainno==trainno)
		  {
			 flag=1;
			 cout<<"\n\n *ENTER THE PNR ";
			 cin>>pnr;
			 cout<<"\n\n   *ENTER THE CLASS ";
			 cout<<"\n\n    1>AC CLASS ";
			 cout<<"\n\n    2>GENERAL SLEEPER CLASS ";
			 cin>>cls;
			 if(cls==1)
			  cancel_ac(i,pnr);
			 else if(cls==2)
			  cancel_sleeper(i,pnr);
			 else
				 cout<<endl<<"WRONG OPTION ";
			}
		 if(flag==0)
		 {
			 clrscr();
			 cout<<"\n\n     *RECORD NOT FOUND ";
			 getch();
		  }
	}
}//FUNCTION ENDS


void main()
{
  clrscr();
  int ch;
  gotoxy(18,9);
  cout<<"*****RAILWAY RESERVATION PROJECT*******";
  gotoxy(22,10);
  cout<<"_____________________________";
  gotoxy(40,18);
  cout<<"BY - MAYA AGARWAL ";
  getch();
  clrscr();
  do{
		clrscr();
		gotoxy(28,6);
		cout<<"***********MAIN MENU***********";
		gotoxy(10,10);
		cout<<"1. TRAIN MENU";
		gotoxy(10,13);
		cout<<"2. PASSENGER MENU ";
		gotoxy(10,16);
		cout<<"3. EXIT";
		gotoxy(27,22);
		cout<<"ENTER YOUR CHOICE ";
		cin>>ch;
		switch(ch)
		{
		 case 1:{
			train_details();
			break;
				  }
		 case 2:{
			 passenger_details();
			 break;
				}
		 case 3:{
		  clrscr();
		  gotoxy(28,10);
		  cout<<"THANK YOU !";
		  break;
		  }
		default: {
		  clrscr();
		  gotoxy(6,10);
		  cout<<"YOU HAVE ENTERED THE WRONG CHOICE";
		  gotoxy(18,10);
		  cout<<"THANK YOU "; }
	  }
	}while(ch>=1&&ch<4);

}//PROGRAM ENDS








