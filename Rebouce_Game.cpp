/*******************************************************************
		       REBOUNCE GAME
                    	SOURCE CODE
*******************************************************************/
#include<fstream>
#include<conio.h>
#include<stdio.h>
#include<dos.h>
#include<windows.h>
#include<ctype.h>
#include<iostream>
#include<process.h>
#include<string.h>

using namespace std;

void border1();               		//for making still screen border
void border();                		//for making screen border
void loading();               		//for creating loading effect
void dgameover(int,int,int);       	//the last page for dual mode
void gameover(int,int,int,int);    	//the last page for single mode
int compares(int,int);             	//score comparision
int comparel(int,int);             	//level comaparision
void start();                 		//udf for 3,2,1,go effect
void instruct();              		//instructions page
void gotoxy(short,short);		//for cursor placement
void ShowConsoleCursor(bool); 		// to hide console cursor
void SetConsoleSize();			//to set the size of console window
void DisableMaxConsole();		//to disable maximising console window

class gamer
{
	public:
	char uname[50];                 //user name
	int uage;                       //user age
	char upass[50];                 //user ID's password
	int uhscore;                    //user's score
	int uhlvl;                      //user's level
	gamer()                         //for initialising
	{
		uhscore=0;
		uhlvl=0;
		uage=0;
		strcpy(uname,"gamer");
		strcpy(upass,"123");
	}
	void getdata()
	{
		gotoxy(24,12);
		printf("Enter your user name:");
		fflush(stdin);
		gets(uname);

		gotoxy(24,13);
		printf("Enter your age:");
		cin>>uage;

		gotoxy(24,14);
		printf("Enter your password:");
		fflush(stdin);
		gets(upass);
	}
	~gamer()
	{
	}
}s1;

int main()                   //start of main function
{
	SetConsoleSize();
    	DisableMaxConsole();
	ShowConsoleCursor(false);
    
	while(1)
	{
		system("cls");

		fstream f1,f2;

		border();

		gotoxy(28,10);
		printf("WELCOME TO REBOUNCE!!!");

		loading();

		gotoxy(25,18);
		printf("PRESS ANY KEY TO CONTINUE...");

		getch();

		char chh=' ';

		system("cls");

		border();

		gamemod:

		system("cls");

		border1();

		gotoxy(26,10);
		printf("CHOOSE THE GAME MODE:");

		gotoxy(25,13);
		printf("S-->SINGLE PLAYER MODE");

		gotoxy(25,14);
		printf("D-->DUAL PLAYER MODE");

		gotoxy(25,15);
		printf("H-->HOW TO PLAY");

		gotoxy(25,16);
		printf("Q-->QUIT");

		gotoxy(25,17);
		printf("ENTER YOUR CHOICE:");
		cin>>chh;

		if(chh=='q'||chh=='Q')
		{
			exit(0);
		}

		if(chh=='s'||chh=='S')
		{
			int pastry=3;                                   //counter variable fo no of password tries

			int ch10=1,hiscore=0,hilvl=1;

			long fpos=0;

			char reply1='y',gamer[50]=" ";

			gameacc:

			system("cls");

			border1();

			gotoxy(22,12);
			printf("PRESS 1 FOR NEW GAMER ACCOUNT");

			gotoxy(22,14);
			printf("PRESS 2 IF EXISTING GAMER");

			gotoxy(22,16);
			printf("ENTER YOUR CHOICE:");
			cin>>ch10;

			if(ch10==1)
			{
				f1.open("GAMERS.dat",ios::binary|ios::app);

				while(reply1=='y')
				{
					system("cls");

					border1();

					s1.getdata();

					f1.write((char*)&s1,sizeof(s1));

					rep:

					gotoxy(20,16);
					printf("Do you want to add another account(y/n):");
					cin>>reply1;

					reply1=tolower(reply1);

					if(reply1!='n'&&reply1!='y')                           //comdition if the user enters any wrong input
					{
						gotoxy(20,18);

						printf("INVALID INPUT!PLEASE TRY AGAIN...");
						Sleep(700);

						gotoxy(20,18);
						printf("                                 ");          //for deleting invalid input line

						goto rep;                                    //to return to dirch1,to enter the choice again
					}
				}

				f1.close();

				goto un;
			}
			if(ch10==2)
			{
				un:

				char uname1[50];

				f2.open("GAMER.dat",ios::binary|ios::out);

				pm:

				f1.open("GAMERS.dat",ios::binary|ios::in);

				system("cls");

				border1();

				gotoxy(27,14);
				printf("Press P1 for previous menu");

				gotoxy(31,23);
				printf("Press Q for quit");

				gotoxy(27,10);
				printf("Enter the user name:");
				fflush(stdin);
				gets(uname1);

				if(strcmpi(uname1,"P1")==0)
				{
					goto gameacc;
				}
				if(strcmpi(uname1,"q")==0)
				{
					exit(0);
				}

				while(f1.read((char*)&s1,sizeof(s1)))
				{
					if(strcmp(uname1,s1.uname)==0)
					{
						f2.write((char*)&s1,sizeof(s1));
						goto close;
					}
				}

				if(strcmp(uname1,s1.uname)!=0)
				{
					gotoxy(23,18);
					printf("Sorry!The account does not exist!!");
					Sleep(700);
					f1.close();
					goto pm;
				}

				close:

				f1.close();

				f2.close();

				char pass1[40]=" ";

				f2.open("GAMER.dat",ios::binary|ios::in);

				int ctri=0;

				gotoxy(27,14);
				printf("                              ");

				gotoxy(31,23);
				printf("                        ");

				pass:

				gotoxy(27,12);
				printf("Enter the password:");

				gotoxy(27,13);
				printf("                      ");

				gotoxy(27,13);

				f2.seekg(0,ios::beg);

				while(f2.read((char*)&s1,sizeof(s1)))
				{
					for(ctri=0;ctri<strlen(s1.upass);ctri++)
					{
						pass1[ctri]=getch();
						printf("*");
					}

					if(strcmp(pass1,s1.upass)==0)
					{
						goto prof;
					}
					else
					{
						pastry--;			//to decrease the no. to tries left for entering the password

						if(pastry>0)                     //condition to display if the users has chances left for entering the password
						{

							gotoxy(24,16);
							printf("Wrong password!Please try again.");

							gotoxy(27,18);
							printf("You have %d chances left!",pastry);        //to display no of chances left for entering the password

							Sleep(1000);

							gotoxy(24,16);
							printf("                                     ");

							gotoxy(27,18);
							printf(" 	     			        ");

							goto pass;
						}
						else if(pastry==0)                         //to end the program incase the user fails to enter the password thrice
						{
							system("cls");

							border1();

							gotoxy(29,12);
							printf("You have NO chances left");

							gotoxy(23,14);
							printf("YOU ARE NOT ELIGIBLE TO PLAY THE GAME...");

							getch();

							exit(0);
						}
					}

				}
				prof:

				f2.close();

				system("cls");

				border();

				f2.open("GAMER.dat",ios::in|ios::binary);

				while(f2.read((char*)&s1,sizeof(s1)))
				{
					gotoxy(31,9);
					printf("WELCOME GAMER");

					gotoxy(31,11);
					printf("Gamer Profile");

					gotoxy(25,14);
					printf("-->User name: %s",s1.uname);

					strcpy(gamer,s1.uname);

					gotoxy(25,15);
					printf("-->Age: %d",s1.uage);

					gotoxy(25,16);
					printf("-->Highest score: %d",s1.uhscore);

					hiscore=s1.uhscore;

					gotoxy(25,17);
					printf("-->Highest level: %d",s1.uhlvl);

					hilvl=s1.uhlvl;

				}

				f2.close();

				gotoxy(25,19);

				printf("PRESS ANY KEY TO CONTINUE...");
				getch();
				system("cls");

				int speed=65,level=1,stik=0,dirn=0,x=0,y=0,turns=0,score=0;  /*level-display game level
								      dirn-for direction of the ball
								      score-to count no. of times ball hits the stick
								      turns-to diplay the no. of chances left
								      stik-to locate the position of stick
								      x,y-to locate the position of ball
								      */
				 int ctr=10;                                  //a counter variable

				 int bests=0,bestl=0;

				 char choice=' ';               //variable to input a character choice from user
				 border();
				 turns=5;                  //initial no of chances to play the game

				 start();

				  play:

				  x=40;                     //default positions of the ball and the stick at start of game
				  y=22;
				  stik=36;

				  gotoxy(57,25);                        //to display score of the user as he plays
				  printf("SCORE:");

				  gotoxy(36,25);
				  printf("REBOUNCE");

				  gotoxy(72,25);
				  printf("Q=quit");

				  gotoxy(64,25);
				  printf("%d",score);

				  gotoxy(3,25);                          //to display the no of chances left for the user to play the game again
				  printf("CHANCES: ");
				  printf("%d",turns);

				  gotoxy(18,25);
				  printf("LEVEL: %d",level);

				  gotoxy(x,y);                                  //denotes movement of the ball
				  printf("o");

				  gotoxy(stik,23);                              //denotes movement of the stick
				  printf("|_______|");

				  dirch1:

				  choice=' ';                   // to initialise variable choice

				  gotoxy(19,14);
				  printf("PRESS 'A' TO MOVE LEFT OR 'D' TO MOVE RIGHT...");    //to input the user's choice of direction

				  choice=getch();
				  choice=tolower(choice);

				  if(choice=='d')                                     //to set the direction of ball as per user's choice
					dirn=1;

				  else if(choice=='a')
					dirn=2;


				  else if(choice=='q')
				  {
					bests=compares(score,hiscore);
					bestl=comparel(level,hilvl);
					f1.open("GAMERS.dat",ios::binary|ios::in|ios::out);
					while(!f1.eof())
					{
						fpos=f1.tellg();
						f1.read((char*)&s1,sizeof(s1));
						if(strcmp(s1.uname,gamer)==0)
						{
							s1.uhscore=bests;
							s1.uhlvl=bestl;
							f1.seekg(fpos);
							f1.write((char*)&s1,sizeof(s1));
							break;
						}
					}
					f1.close();
					gameover(score,level,bests,bestl);
				  }

				  else if(choice!='a'||'d')                           //comdition if the user enters any wrong input
				  {
					gotoxy(23,16);

					printf("INVALID INPUT!PLEASE TRY AGAIN...");
					Sleep(700);

					gotoxy(23,16);
					printf("                                 ");          //for deleting invalid input line

					goto dirch1;                                    //to return to dirch1,to enter the choice again
				  }

				  gotoxy(19,14);
				  printf("                                              ");

				  while(choice!='q')                                            //valid till the user does not opt to exit
				  {
					while((x<=79)&&(x>=2)&&(y<=22)&&(y>=2))           //so that the ball does not cross the border line
					{
						gotoxy(x,y);
						printf("o");

						gotoxy(stik,23);
						printf("|_______|");
						Sleep(speed);                                //to control the speed of the game

						gotoxy(x,y);                              //to erase the ball if the stick does not strike the ball
						printf(" ");

						gotoxy(stik,23);                           //to erase the bat if the stick does not strike the ball
						printf("         ");


						if(dirn==1)                                //to make the ball move in top-right direction
						{
							x++;
							y--;
						}

						if(dirn==2)                                 //to make the ball move in top-left direction
						{
							x--;
							y--;
						}

						if(dirn==3)                                  //to make the ball move in bottom-left direction
						{
							x--;
							y++;
						}

						if(dirn==4)                                  //to make the ball move in bottom-right direction
						{
							x++;
							y++;
						}

						if(kbhit())                         //to input the choice from the user to move the stick
						{
							char last_ch;

							last_ch=choice;
							choice=getch();
							choice=tolower(choice);

							if(choice=='q')
							{
								bests=compares(score,hiscore);
								bestl=comparel(level,hilvl);
								f1.open("GAMERS.dat",ios::binary|ios::in|ios::out);
								while(!f1.eof())
								{
									fpos=f1.tellg();
									f1.read((char*)&s1,sizeof(s1));
									if(strcmp(s1.uname,gamer)==0)
									{
										s1.uhscore=bests;
										s1.uhlvl=bestl;
										f1.seekg(fpos);
										f1.write((char*)&s1,sizeof(s1));
										break;
									}
								}
								f1.close();
								gameover(score,level,bests,bestl);
							}
							if(choice!='a'&&choice!='d')        //to set the last input as the default input in case the user enters any inappropriate entry
							{
								choice=last_ch;
							}

						}

						if(choice=='a')                         //to make the stick move left if the use presses 'a' or 'A'
						{
							if(stik>2)
							stik-=2;
						}

						if(choice=='d')                         //to make the stick move right if the use presses 'd' or 'D'
						{
							if(stik<70)
							stik+=2;
						}
					}

					if(x==1)                                     //to change direction of ball if it strikes left border wall
					{
						x=2;

						if(dirn==2)
						dirn=1;

						if(dirn==3)
						dirn=4;
					}

					if(x==80)                                    //to change direction of ball if it strikes right border wall
					{
						x=79;

						if(dirn==4)
						dirn=3;

						if(dirn==1)
						dirn=2;
					}

					if(y==1)                                      //to change direction of ball if it strikes top border wall
					{
						y=2;

						if(dirn==1)
						dirn=4;

						if(dirn==2)
						dirn=3;

					}
					if((y==23)&&(x>=stik)&&(x<=stik+9))             //to change the direction of ball if it strikes with the stick
					{
						score++;                                //to increment the no of hits between ball and stick i.e. score

						if(score==ctr)
						{
							level++;
							ctr=ctr+10;

							gotoxy(25,25);
							printf("%d",level);

							speed=speed-5;
						}

						gotoxy(64,25);                          //to display the new score
						printf("%d",score);

						y=22;

						if(dirn==3)
							dirn=2;

						if(dirn==4)
							dirn=1;

					}

					if((y==23)&&((x<stik)||(x>stik+9)))               //condition if the ball does not strike with the stick
					{
						turns--;                                 //to decrement the no. of chanes left to play the game

						if(turns==0)                              //if chances left are 0,then display gameover page
						{
							bests=compares(score,hiscore);
							bestl=comparel(level,hilvl);
							f1.open("GAMERS.dat",ios::binary|ios::in|ios::out);
							while(!f1.eof())
							{
								fpos=f1.tellg();
								f1.read((char*)&s1,sizeof(s1));
								if(strcmp(s1.uname,gamer)==0)
								{
									s1.uhscore=bests;
									s1.uhlvl=bestl;
									f1.seekg(fpos);
									f1.write((char*)&s1,sizeof(s1));
									break;
								}
							}
							f1.close();
							gameover(score,level,bests,bestl);
						}

						gotoxy(12,25);
						printf("%d",turns);

						playagain:

						choice=' ';              //to initialise choice variable

						gotoxy(16,14);
						printf("FOR ANOTHER CHANCE PRESS 'P' OR TO QUIT PRESS 'Q'");    /*to input choice from the user whether he wishes to play again or not*/

						choice=getch();

						choice=tolower(choice);

						if(choice=='q')                    //condition to display gameover page if the user wishes to exit the program
						{
							bests=compares(score,hiscore);
							bestl=comparel(level,hilvl);
							f1.open("GAMERS.dat",ios::binary|ios::in|ios::out);
							while(!f1.eof())
							{
								fpos=f1.tellg();
								f1.read((char*)&s1,sizeof(s1));
								if(strcmp(s1.uname,gamer)==0)
								{
									s1.uhscore=bests;
									s1.uhlvl=bestl;
									f1.seekg(fpos);
									f1.write((char*)&s1,sizeof(s1));
									break;
								}
							}
							f1.close();
							gameover(score,level,bests,bestl);
						}

						if(choice=='p')                        //condition to restart the game if the user wishes to play again
						{

						     gotoxy(16,14);
						     printf("                                                 ");
						     goto play;
						}

						else
						{
							gotoxy(23,16);
							printf("INVALID INPUT!PLEASE TRY AGAIN...");           //condition if the user incprintf some wrong entry

							Sleep(700);

							gotoxy(23,16);
							printf("                                  ");

							goto playagain;
						}
					}
				}
			}
			else
			{
				gotoxy(23,16);
				printf("INVALID INPUT!PLEASE TRY AGAIN...");           //condition if the user incprintf some wrong entry

				Sleep(700);

				gotoxy(23,16);
				printf("                                  ");

				goto gameacc;
			}
		}
		if(chh=='d'||chh=='D')
		{
			duser:

			system("cls");

			border();

			int dspeed=65,dlevel=1,dstik1=0,dstik2=0,ddirn=0,dx=0,dy=0,dturns=0,dscore1=0,dscore2=0;  /*level-display game level
								      dirn-for direction of the ball
								      score-to count no. of times ball hits the stick
								      turns-to diplay the no. of chances left
								      stik-to locate the position of stick
								      x,y-to locate the position of ball
								      */

			int dctr=10;                                  //a counter variable

			char dchoice=' ';               //variable to input a character choice from user

			dturns=5;                  //initial no of chances to play the game

			start();

			dplay:

			dx=40;                     //default positions of the ball and the stick at start of game
			dy=22;
			dstik1=36;

			dstik2=36;

			gotoxy(55,25);                        //to display score of the user as he plays
			printf("P1 SCORE: %d",dscore1);

			gotoxy(37,25);
			printf("LEVEL: %d",dlevel);

			gotoxy(72,25);
			printf("Q=quit");

			gotoxy(3,25);                          //to display the no of chances left for the user to play the game again
			printf("TURNS: %d",dturns);

			gotoxy(18,25);
			printf("P2 SCORE: %d",dscore2);

			gotoxy(dx,dy);                                  //denotes movement of the ball
			printf("o");

			gotoxy(dstik1,23);                              //denotes movement of the stick
			printf("|-------|");

			gotoxy(dstik2,2);                              //denotes movement of the stick
			printf("|-------|");

			ddirch1:

			dchoice=' ';                   // to initialise variable choice

			gotoxy(14,14);
			printf("PLAYER 1 PRESS 'A' TO MOVE LEFT OR 'D' TO MOVE RIGHT");    //to input the user's choice of direction

			dchoice=getch();
			dchoice=tolower(dchoice);

			if(dchoice=='d')                                     //to set the direction of ball as per user's choice
				ddirn=1;

			else if(dchoice=='a')
				ddirn=2;

			else if(dchoice=='q')
				dgameover(dscore1,dscore2,dlevel);


			else if(dchoice!='a'||'d')                           //comdition if the user enters any wrong input
			{
				gotoxy(23,16);

				printf("INVALID INPUT!PLEASE TRY AGAIN...");
				Sleep(700);

				gotoxy(23,16);
				printf("                                 ");          //for deleting invalid input line

				goto ddirch1;                                    //to return to dirch1,to enter the choice again
			}

			gotoxy(14,14);
			printf("                                                    ");

			while(dchoice!='q')                                            //valid till the user does not opt to exit
			{
				while((dx<=79)&&(dx>=2)&&(dy<=22)&&(dy>=3))           //so that the ball does not cross the border line
				{
					gotoxy(dx,dy);
					printf("o");

					gotoxy(dstik1,23);
					printf("|-------|");

					gotoxy(dstik2,2);
					printf("|-------|");
					Sleep(dspeed);                                //to control the speed of the game

					gotoxy(dx,dy);                              //to erase the ball if the stick does not strike the ball
					printf(" ");

					gotoxy(dstik1,23);                           //to erase the bat if the stick does not strike the ball
					printf("         ");

					gotoxy(dstik2,2);
					printf("         ");

					if(ddirn==1)                                //to make the ball move in top-right direction
					{
						dx++;
						dy--;
					}

					if(ddirn==2)                                 //to make the ball move in top-left direction
					{
						dx--;
						dy--;
					}

					if(ddirn==3)                                  //to make the ball move in bottom-left direction
					{
						dx--;
						dy++;
					}

					if(ddirn==4)                                  //to make the ball move in bottom-right direction
					{
						dx++;
						dy++;
					}

					if(kbhit())                         //to input the choice from the user to move the stick
					{
						char dlast_ch;

						dlast_ch=dchoice;
						dchoice=getch();
						dchoice=tolower(dchoice);

						if(dchoice=='q')
							dgameover(dscore1,dscore2,dlevel);

						if(dchoice!='a'&&dchoice!='d'&&dchoice!='j'&&dchoice!='l')        //to set the last input as the default input in case the user enters any inappropriate entry
						{
							dchoice=dlast_ch;
						}
					}

					if(dchoice=='a')                         //to make the stick move left if the use presses 'a' or 'A'
					{
						if(dstik1>2)
						dstik1-=2;
					}

					if(dchoice=='d')                         //to make the stick move right if the use presses 'd' or 'D'
					{
						if(dstik1<70)
						dstik1+=2;
					}

					if(dchoice=='j')                         //to make the stick move left if the use presses 'a' or 'A'
					{
						if(dstik2>2)
						dstik2-=2;
					}

					if(dchoice=='l')                         //to make the stick move right if the use presses 'd' or 'D'
					{
						if(dstik2<70)
						dstik2+=2;
					}
				}

				if(dx==1)                                     //to change direction of ball if it strikes left border wall
				{
					dx=2;

					if(ddirn==2)
					ddirn=1;

					if(ddirn==3)
					ddirn=4;
				}

				if(dx==80)                                    //to change direction of ball if it strikes right border wall
				{
					dx=79;

					if(ddirn==4)
					ddirn=3;

					if(ddirn==1)
					ddirn=2;
				}

				if((dy==23)&&(dx>=dstik1)&&(dx<=dstik1+9))             //to change the direction of ball if it strikes with the stick
				{
					dscore1++;                                //to increment the no of hits between ball and stick i.e. score

					if(dscore1==dctr)
					{
						dlevel++;

						dctr=dctr+10;

						gotoxy(44,25);
						printf("%d",dlevel);

						dspeed=dspeed-5;
					}

					gotoxy(65,25);                          //to display the new score
					printf("%d",dscore1);

					dy=22;

					if(ddirn==3)
					ddirn=2;

					if(ddirn==4)
					ddirn=1;

				}

				if((dy==2)&&(dx>=dstik2)&&(dx<=dstik2+9))             //to change the direction of ball if it strikes with the stick
				{
					dscore2++;                                //to increment the no of hits between ball and stick i.e. score

					gotoxy(28,25);                          //to display the new score
					printf("%d",dscore2);

					dy=3;

					if(ddirn==2)
					ddirn=3;

					if(ddirn==1)
					ddirn=4;

				}

				if((dy==2)&&((dx<dstik2)||(dx>dstik2+9)))               //condition if the ball does not strike with the stick
				{
					dturns--;                                 //to decrement the no. of chanes left to play the game

					if(dturns==0)                              //if chances left are 0,then display gameover page
					{
						dgameover(dscore1,dscore2,dlevel);
					}

					gotoxy(10,25);
					printf("%d",dturns);

					dplayagain:

					dchoice=' ';              //to initialise choice variable

					gotoxy(16,14);
					printf("FOR ANOTHER CHANCE PRESS 'P' OR TO QUIT PRESS 'Q'");    /*to input choice from the user whether he wishes to play again or not*/

					dchoice=getch();

					dchoice=tolower(dchoice);

					if(dchoice=='q')                    //condition to display gameover page if the user wishes to exit the program
					{
						dgameover(dscore1,dscore2,dlevel);
					}

					if(dchoice=='p')                        //condition to restart the game if the user wishes to play again
					{

					       gotoxy(16,14);
					       printf("                                                 ");
					       goto dplay;
					}

					else
					{
						gotoxy(23,16);
						printf("INVALID INPUT!PLEASE TRY AGAIN...");           //condition if the user incprintf some wrong entry

						Sleep(700);

						gotoxy(23,16);
						printf("                                  ");

						goto dplayagain;
					}
				}

				if((dy==23)&&((dx<dstik1)||(dx>dstik1+9)))               //condition if the ball does not strike with the stick
				{
					dturns--;                                 //to decrement the no. of chanes left to play the game

					if(dturns==0)                              //if chances left are 0,then display gameover page
					{
						dgameover(dscore1,dscore2,dlevel);
					}

					gotoxy(10,25);
					printf("%d",dturns);

					dplayagain1:

					dchoice=' ';              //to initialise choice variable

					gotoxy(16,14);
					printf("FOR ANOTHER CHANCE PRESS 'P' OR TO QUIT PRESS 'Q'");    /*to input choice from the user whether he wishes to play again or not*/

					dchoice=getch();

					dchoice=tolower(dchoice);

					if(dchoice=='q')                    //condition to display gameover page if the user wishes to exit the program
					{
						dgameover(dscore1,dscore2,dlevel);
					}

					if(dchoice=='p')                        //condition to restart the game if the user wishes to play again
					{

					       gotoxy(16,14);
					       printf("                                                 ");
					       goto dplay;
					}

					else
					{
						gotoxy(23,16);
						printf("INVALID INPUT!PLEASE TRY AGAIN...");           //condition if the user incprintf some wrong entry

						Sleep(700);

						gotoxy(23,16);
						printf("                                  ");

						goto dplayagain1;
					}
				}
			}
		}
		if(chh=='H'||chh=='h')
		{
			instruct();
			goto gamemod;
		}
		else
		{
			gotoxy(23,18);
			printf("INVALID INPUT!PLEASE TRY AGAIN...");           //condition if the user incprintf some wrong entry

			Sleep(700);

			gotoxy(23,18);
			printf("                                  ");

			goto gamemod;
		}
	}
}
void gotoxy(short x, short y)           //definition of gotoxy function                                             
{
 	COORD pos ={x,y};
 	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void border()                            //udf for border
{
	float row=0,col=0;

	for(row=1;row<=24;row++)
	{
		gotoxy(80,row);
		printf("*");
		Sleep(10);
	}

	for(col=80;col>0;col--)
	{
		gotoxy(col,24);
		printf("*");
		Sleep(10);
	}

	for(row=24;row>0;row--)
	{
		gotoxy(1,row);
		printf("*");
		Sleep(10);
	}
	for(col=1;col<=80;col++)
	{
		gotoxy(col,1);
		printf("*");
		Sleep(10);
	}
}
void border1()                            //udf for border
{
	int row=0,col=0;

	for(row=1;row<=24;row++)
	{
		gotoxy(80,row);
		printf("*");
	}

	for(col=80;col>0;col--)
	{
		gotoxy(col,24);
		printf("*");
	}

	for(row=24;row>0;row--)
	{
		gotoxy(1,row);
		printf("*");
	}
	for(col=1;col<=80;col++)
	{
		gotoxy(col,1);
		printf("*");
	}
}
void loading()                          //udf for loading effect
{

	gotoxy(35,16);
	printf("LOADING...");

	gotoxy(25,12);
	printf("---------------------------");

	gotoxy(25,13);
	printf("|");

	gotoxy(51,13);
	printf("|");

	gotoxy(25,14);
	printf("---------------------------");

	for(int ctr=26;ctr<=50;ctr++)
	{
		gotoxy(ctr,13);
		printf("*");
		Sleep(100);
	}

	Sleep(1000);
}
int comparel(int level0,int hlvl0)
{
	if(level0!=1)
	{
		if(level0>hlvl0)
		{
			hlvl0=level0;
		}
	}
	return hlvl0;
}
void instruct()
{
	system("cls");

	border();

	gotoxy(31,2);
	printf("HOW TO PLAY");

	gotoxy(28,4);
	printf("SINGLE PLAYER MODE");

	gotoxy(3,6);
	printf("--> You will be provided with only 5 turns!");

	gotoxy(3,7);
	printf("--> You can move the paddle by using key 'A' for left and 'D' for right.");

	gotoxy(3,8);
	printf("--> Your aim is to move the paddle so as to rebounce the ball back.");

	gotoxy(3,9);
	printf("--> Your score will increase as you hit the ball by the paddle.");

	gotoxy(3,10);
	printf("--> The level and speed of the game increases as the game progresses.");

	gotoxy(3,11);
	printf("--> You will lose a turn each time the ball falls off the screen.");

	gotoxy(29,13);
	printf("DUAL PLAYER MODE");

	gotoxy(3,15);
	printf("--> Both the players will be provided with only 5 turns together.");

	gotoxy(3,16);
	printf("--> Player 1(P1) gets bottom paddle and Player 2(P2) gets upper paddle.");

	gotoxy(3,17);
	printf("--> Player 1 can move the paddle by using key 'A' for left and 'D' for right.");

	gotoxy(3,18);
	printf("--> Player 2 can move the paddle by using key 'J' for left and 'L' for right.");

	gotoxy(3,19);
	printf("--> Both the players need to rebounce the ball using their paddles.");

	gotoxy(3,20);
	printf("--> The score of both the players increases individually as they hit the ball.");

	gotoxy(3,21);
	printf("-->The level and speed of the game increases as the game progresses.");

	gotoxy(25,23);
	printf("PRESS ANY KEY TO RETURN...");

	getch();
}
int compares(int score0,int hscore0)
{
	if(score0!=0)
	{
		if(score0>hscore0)
		{
			hscore0=score0;
		}
	}
	return hscore0;
}
void gameover(int score1,int level1,int hscore1,int hlvl1)                          //udf to display the end page of the game
{
	system("cls");

	border();

	gotoxy(33,10);
	printf("                                ");

	gotoxy(33,8);
	printf("GAME OVER!");

	gotoxy(28,10);
	printf("YOUR TOTAL SCORE: %d",score1);

	gotoxy(28,12);
	printf("YOUR FINAL LEVEL: %d",level1);           //to display the final level reached

	gotoxy(30,14);
	printf("HIGHEST SCORE: %d",hscore1);

	gotoxy(30,16);
	printf("HIGHEST LEVEL: %d",hlvl1);

	gotoxy(25,18);
	printf("HOPE YOU ENJOYED THE GAME!!");

	getch();

	exit(0);
}
void dgameover(int dscore10,int dscore20,int dlevel1)                          //udf to display the end page of the game
{
	system("cls");

	border();

	gotoxy(35,10);
	printf("GAME OVER!");

	gotoxy(28,12);
	printf("PLAYER 1'S TOTAL SCORE: %d",dscore10);

	gotoxy(28,14);
	printf("PLAYER 2'S TOTAL SCORE: %d",dscore20);

	gotoxy(28,16);
	printf("FINAL LEVEL REACHED: %d",dlevel1);           //to display the final level reached

	if(dscore10>dscore20)
	{
		gotoxy(32,18);
		printf("PLAYER 1 WINS!!!");
	}
	else if(dscore10<dscore20)
	{
		gotoxy(32,18);
		printf("PLAYER 2 WINS!!!");
	}
	else if(dscore10==dscore20)
	{
		gotoxy(35,18);
		printf("TIE GAME!!!");
	}

	gotoxy(28,20);
	printf("HOPE YOU ENJOYED THE GAME!!");

	getch();

	exit(0);
}                                                         //udf to display the 3,2,1.. efeect at the start of the game
void start()
{
	for(int ctr=3;ctr>=1;ctr--)
	{
		gotoxy(38,13);
		printf("%d",ctr);
		Sleep(400);
	}

	gotoxy(38,13);
	printf("GO!!");

	Sleep(500);

	gotoxy(38,13);
	printf("     ");
}
void ShowConsoleCursor(bool showFlag) // to hide console cursor
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.dwSize   = 10;
    cursorInfo.bVisible = showFlag; // to set cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}
void SetConsoleSize()		//to set the size of console window
{
	HWND console = GetConsoleWindow();
    RECT ConsoleRect;
    GetWindowRect(console, &ConsoleRect); 
    MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 690, 425, TRUE);
}
void DisableMaxConsole()		//to disable console window maximizing
{
	HWND hwnd = GetConsoleWindow();
	DWORD style = GetWindowLong(hwnd, GWL_STYLE);
	style &= ~WS_MAXIMIZEBOX;
	SetWindowLong(hwnd, GWL_STYLE, style);
	SetWindowPos(hwnd, NULL, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE|SWP_FRAMECHANGED);
}
