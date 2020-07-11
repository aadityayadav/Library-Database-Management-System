
#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<iomanip.h>

class book
{
    char bno[6];
    char bname[50];
    char aname[20];
  public:
    void create_book()
    {
    cout<<"\nNEW BOOK ENTRY...\n";
    cout<<"\nEnter The book no.";
    cin>>bno;
    cout<<"\n\nEnter The Name of The Book ";
    gets(bname);
    cout<<"\n\nEnter The Author's Name ";
    gets(aname);
    cout<<"\n\n\nBook Created..";
    }

    void show_book()
    {
    cout<<"\nBook no. : "<<bno;
    cout<<"\nBook Name : ";
    puts(bname);
    cout<<"Author Name : ";
    puts(aname);
    }

    void modify_book()
    {
    cout<<"\nBook no. : "<<bno;
    cout<<"\nModify Book Name : ";
    gets(bname);
    cout<<"\nModify Author's Name of Book : ";
    gets(aname);
    }

    char* retbno()
    {
    return bno;
    }

    void report()
    {

        cout<<bno<<setw(30)<<bname<<setw(30)<<aname<<endl;
    }


};




class student
{
    char admno[6];
    char name[20];
    char stbno[6];
    int token;
public:
    void create_student()
    {
    clrscr();
     cout<<"\nNEW STUDENT ENTRY...\n";
    cout<<"\nEnter The admission no. ";
    cin>>admno;
    cout<<"\n\nEnter The Name of The Student ";
    gets(name);
    token=0;
    stbno[0]='/0';
    cout<<"\n\nStudent Record Created..";
    }



    char* retadmno()
    {
    return admno;
    }

    char* retstbno()
    {
    return stbno;
    }

    int rettoken()
    {
    return token;
    }

    void addtoken()
    {
        token=1;
    }

    void resettoken()
    {
        token=0;
    }

    void getstbno(char t[])
    {
    strcpy(stbno,t);
    }

    void report()
    {
    cout<<"\t"<<admno<<setw(20)<<name<<setw(10)<<token<<endl;
    }

};

void write_book()
{
    char ch;
    fstream fp;

    book bk;
    fp.open("books.dat",ios::app|ios::binary);

    do
    {
    clrscr();
    bk.create_book();
    fp.write((char*)&bk,sizeof(book));
    cout<<"\n\nDo you want to add more record..(y/n?)";
    cin>>ch;
    }
    while(ch=='y'||ch=='Y');

    fp.close();
}

void write_student()
{

    char ch;
    fstream fp;
    student st;
    fp.open("students.dat",ios::app|ios::binary);
    do
    {
    st.create_student();
    fp.write((char*)&st,sizeof(student));
    cout<<"\n\ndo you want to add more record..(y/n?)";
    cin>>ch;
    }
    while(ch=='y'||ch=='Y');

    fp.close();
}


//***************************************************************
//        function to read specific record from file
//****************************************************************


void display_spb(char n[])
{
    fstream fp;
    book bk;
    cout<<"\nBOOK DETAILS\n";
    int flag=0;
    fp.open("books.dat",ios::in|ios::binary);
    while(fp.read((char*)&bk,sizeof(book)))
    {
    if(strcmpi(bk.retbno(),n)==0)
    {
        bk.show_book();
         flag=1;
    }
    }

    fp.close();
    if(flag==0)
    cout<<"\n\nBook does not exist";
    getch();
}




//***************************************************************
//        function to modify record of file
//****************************************************************


void modify_book()
{
    fstream fp;
    book bk;
    char n[6];
    int found=0;
    clrscr();

    cout<<"\n\n\tMODIFY BOOK REOCORD.... ";
    cout<<"\n\n\tEnter The book no. of The book";
    cin>>n;

    fp.open("books.dat",ios::in|ios::out|ios::binary);

    while(fp.read((char*)&bk,sizeof(book)) && found==0)
    {

        if(strcmpi(bk.retbno(),n)==0)
    {
        bk.show_book();
        cout<<"\nEnter The New Details of book"<<endl;
        bk.modify_book();
        int pos=-1*sizeof(bk);
        fp.seekp(pos,ios::cur);
        fp.write((char*)&bk,sizeof(book));
        cout<<"\n\n\t Record Updated";
        found=1;
    }
    }

    fp.close();
    if(found==0)
        cout<<"\n\n Record Not Found ";
    getch();
}


//***************************************************************
//        function to delete record of file
//****************************************************************


void delete_book()
{
    fstream fp;
    book bk;
    char n[6];
    clrscr();
    cout<<"\n\n\n\tDELETE BOOK ...";
    cout<<"\n\nEnter The Book no. of the Book You Want To Delete : ";
    cin>>n;
    fp.open("books.dat",ios::in|ios::out|ios::binary);
    fstream fp2;
    fp2.open("Temp.dat",ios::out);
    fp.seekg(0,ios::beg);
    while(fp.read((char*)&bk,sizeof(book)))
    {
    if(strcmpi(bk.retbno(),n)!=0)
    {
        fp2.write((char*)&bk,sizeof(book));
    }
    }


    fp2.close();
    fp.close();
    remove("books.dat");
    rename("Temp.dat","books.dat");
    cout<<"\n\n\tRecord Deleted ..";
    getch();
}



//***************************************************************
//        function to display Books list
//****************************************************************

void display_allb()
{
    fstream fp;
    book bk;
    clrscr();
    fp.open("books.dat",ios::in|ios::binary);
    if(!fp)
    {
    cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
           getch();
           return;
     }


    cout<<"\n\n\t\tBook LIST\n\n";
    cout<<"=========================================================================\n";
    cout<<"Book Number"<<setw(20)<<"Book Name"<<setw(25)<<"Author\n";
    cout<<"=========================================================================\n";

    while(fp.read((char*)&bk,sizeof(book)))
    {
    bk.report();
    }
     fp.close();
     getch();
}



//***************************************************************
//        function to issue book
//****************************************************************

void book_issue()
{
    fstream fp,fp1;
    book bk;
    student st;
    char sn[6],bn[6];
    int found=0,flag=0;
    clrscr();
    cout<<"\n\nBOOK ISSUE ...";
    cout<<"\n\n\tEnter The student's admission no.";
    cin>>sn;

    fp.open("students.dat",ios::in|ios::out|ios::binary);
    fp1.open("books.dat",ios::in|ios::out|ios::binary);
    while(fp.read((char*)&st,sizeof(student)) && found==0)
       {
    if(strcmpi(st.retadmno(),sn)==0)
    {

            found=1;
        if(st.rettoken()==0)
        {

                cout<<"\n\n\tEnter the book no. ";
        cin>>bn;
        while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
        {
               if(strcmpi(bk.retbno(),bn)==0)
            {
            bk.show_book();
            flag=1;
            st.addtoken();
            st.getstbno(bk.retbno());
                   int pos=-1*sizeof(st);
            fp.seekp(pos,ios::cur);
            fp.write((char*)&st,sizeof(student));
            cout<<"\n\n\t Book issued successfully";
            }
            }
          if(flag==0)
            cout<<"Book no does not exist";
        }
        else
          cout<<"You have not returned the last book ";

    }
    }
      if(found==0)
    cout<<"Student record not exist...";
    getch();
      fp.close();
      fp1.close();
}


//***************************************************************
//        function to deposit book
//****************************************************************


void book_deposit()
{
    fstream fp,fp1;
    book bk;
    student st;
    char sn[6],bn[6];
    int found=0,flag=0;
    clrscr();
    cout<<"\n\nBOOK DEPOSIT ...";
    cout<<"\n\n\tEnter The student admission no.";
    cin>>sn;
    fp.open("students.dat",ios::in|ios::out|ios::binary);
    fp1.open("books.dat",ios::in|ios::out|ios::binary);
    while(fp.read((char*)&st,sizeof(student)) && found==0)
       {
    if(strcmpi(st.retadmno(),sn)==0)
    {
        found=1;
        if(st.rettoken()==1)
        {
        while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
        {
           if(strcmpi(bk.retbno(),st.retstbno())==0)
        {
        bk.show_book();
        flag=1;


            st.resettoken();
            int pos=-1*sizeof(st);
            fp.seekp(pos,ios::cur);
            fp.write((char*)&st,sizeof(student));
            cout<<"\n\n\t Book deposited successfully";
        }
        }
      if(flag==0)
        cout<<"Book no. does not exist";
          }
     else
        cout<<"No book is issued..please check!!";
    }
       }
      if(found==0)
    cout<<"Student record not exist...";
    getch();
  fp.close();
  fp1.close();
  }




//***************************************************************
//        INTRODUCTION FUNCTION
//****************************************************************

void intro()
{
    clrscr();
    gotoxy(35,11);
    cout<<"WELCOME TO ";
    gotoxy(35,14);
    cout<<"LIBRARY MANAGEMENT";
    cout<<" SYSTEM";
    getch();
}



//***************************************************************
//        ADMINISTRATOR MENU FUNCTION
//****************************************************************

void admin_menu()
{
    clrscr();
    int ch2;
    cout<<"\n\n\n\tADMINISTRATOR MENU";
    cout<<"\n\n\t1.CREATE STUDENT RECORD";
    cout<<"\n\n\t2.CREATE BOOK ";
    cout<<"\n\n\t3.DISPLAY ALL BOOKS ";
    cout<<"\n\n\t4.DISPLAY SPECIFIC BOOK ";
    cout<<"\n\n\t5.MODIFY BOOK ";
    cout<<"\n\n\t6.DELETE BOOK ";
    cout<<"\n\n\t7.BACK TO MAIN MENU";
    cout<<"\n\n\tPlease Enter Your Choice (1-7) ";
    cin>>ch2;
    switch(ch2)
    {
        case 1:
            clrscr();
            write_student();
            break;
        case 2:
        clrscr();
        write_book();
        break;
        case 3:
        display_allb();
        break;
        case 4: {
           char num[6];
           clrscr();
           cout<<"\n\n\tPlease Enter The book No. ";
           cin>>num;
           display_spb(num);
           break;
        }
          case 5:
                  modify_book();break;
          case 6:
                  delete_book();break;
         case 7:
                 return;
         default:
                 cout<<"\a";
       }
       admin_menu();
}


//***************************************************************
//        THE MAIN FUNCTION OF PROGRAM
//****************************************************************


void main()
{
    char ch;
    intro();
    do
    {
    clrscr();
    cout<<"\n\n\n\tMAIN MENU";
    cout<<"\n\n\t1. BOOK ISSUE";
    cout<<"\n\n\t2. BOOK RETURN";
      cout<<"\n\n\t3. ADMINISTRATOR MENU";
      cout<<"\n\n\t4. EXIT";
      cout<<"\n\n\tPlease Select Your Option (1-4) ";
      cin>>ch;
      switch(ch)
      {
        case '1':
                    clrscr();
                    book_issue();
                    break;
          case '2':
                    book_deposit();
            break;
          case '3':
                    admin_menu();
                    break;
          case '4':
                    break;
          default :
                    cout<<"\a";
    }
    }while(ch!='4');
}
//                END OF PROJECT

