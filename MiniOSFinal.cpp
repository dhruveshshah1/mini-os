//
//  main.cpp
//  MiniOS
//


#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<ctime>
#include<fstream>
#include<string.h>
#include<queue>
//#include<windows.h>
using namespace std;
string secondarymemory[1024],mainmemory[256],cachememory[4],cachepointer[4], numberofprograms,superuserpass="",currentuser;
int nofprograms=0,multipleprograms=0;
struct FAT
{
    string name;
    int start=0,size=0;
}fat[100];
void displaytemplate()
{
    time_t now=time(0);
    char *dt=ctime(&now);
    cout<<"          "<<dt;
    //cout<<"        "<<ctime(&now);
    cout<<"-----------------------------------------------\n";
    cout<<"             Welcome to AgniOS                 \n";
    cout<<"-----------------------------------------------\n";
    cout<<"Created by CS-E Studs. Copyright © 2018.\nAll rights reserved.\n";
    cout<<"-----------------------------------------------\n";

}
void showq(queue <string> gq)
{
    queue <string> g = gq;
    while (!g.empty())
    {
        cout << '\t' << g.front();
        g.pop();
    }
    cout << '\n';
}
int strcmp(string a,string b),numberofusers=0,superuser=0;
void clrscr()
{
    system("clear");
}
void strtoint(string t)
{
    int i=0;
    while(t[i]!='\0')
    {

        numberofusers=numberofusers+t[i]-'0';
        numberofusers*=10;
        i++;
    }
    numberofusers/=10;
}
void login()
{
    void loginpage();
    ifstream read;
    read.open("login.csv");
    string username,password,un,pw,su,super="1";
    cout<<"Enter username:";
    cin>>username;
    while(read.good()==1)
    {
        // cout<<read.good();
        getline(read, un,',');
        getline(read, pw,',');
        getline(read,su,'\n');
        // cout<<su;
        if(un==username)
            break;
    }
    if(read.good()==0)
    {
        cout<<"Username doesn't Exist!\n";
        loginpage();
    }
    else{
        cout<<"Enter password:";
        cin>>password;
        if(un==username && pw == password)
        {
            //cout<<un<<pw<<su[0];
            //  int c=su[0]-'0';
            if(su[0]=='1')
            {
                cout<<"SuperUser Logged In!\n";
                //superuserpass=password;
            }
            else
            {
                string temp;
                cout<<"logged in!\n";
                ifstream read;
                read.open("superuser.txt");
                getline(read,superuserpass);
                read.close();
                // cout<<"SU:"<<superuserpass;
            }
        }
        else{
            cout<<"Login failed!\n";
            loginpage();
        }

    }
}
void newuser()
{
    void loginpage();
    string username,password,tempass;
    cout<<"Enter a user name:";
    cin>>username;
    currentuser=username;
    ifstream read;
    read.open("login.csv");
    while(read.good()==1)
    {
        // string s;
        string un,p;
        getline(read,un,',');
        getline(read,p,'\n');
        //getline(read,s,'\n');
        if(un==username)
        {
            cout<<"Username Already Exists!\n";
            newuser();
        }
    }
    read.close();
    username+=',';
    cout<<"Enter the password:";
    cin>>password;
    tempass=password;
    password+=',';
    ofstream file;
    file.open("login.csv",ios::app);
    if(numberofusers==0)
        file<<"Username,"<<"Password,"<<"SuperUser\n";
    file<<username;
    file<<password;
    if(numberofusers==0)
    {
        file<<"1"<<endl;
        // password=password-',';
        ofstream write;
        write.open("superuser.txt");
        write<<tempass;
        write.close();
    }
    else
        file<<"0"<<endl;
    file.close();
    numberofusers++;
    file.open("nofusers.txt");
    file<<numberofusers;
    file.close();
    loginpage();
}
void loginpage()
{
    string temp;
    char choice;
    ifstream read;
    read.open("nofusers.txt");
    getline(read,temp,'n');
    read.close();
    //cout<<"DB"<<temp<<endl;
    //strtoint(temp);
    numberofusers=temp[0]-'0';
    //cout<<"VAR:"<<numberofusers<<endl;
    if(numberofusers==0)
    {
        cout<<"No User Registered!\n";
        newuser();
    }
    else{
        cout<<"1.Login\n2.New User\n";
        cout<<"Enter your choice:";
        cin>>choice;
        if(choice=='1')
        {
            login();
        }
        else if(choice=='2')
        {
            if(numberofusers==5)
            {
                cout<<"Maximum Five Users are allowed!\n";
                loginpage();
            }
            else
                newuser();
        }
        else{
            cout<<"Wrong Input!"<<endl;
            loginpage();
        }
    }
}
void firsttime()
{
    void dbtoarray();
    void arraytodb();
    void newprogram(string, int);
    string f="Free";
    ofstream write;
    write.open("SecondaryMemory.csv");
    write<<"Address"<<","<<"Allocation"<<endl;
    for(int i=0;i<1024;i++)
    {
        write<<i<<",";
        write<<f<<endl;
    }
    write.close();
    write.open("MainMemory.csv");
    write<<"Address"<<","<<"Allocation"<<endl;
    for(int i=0;i<256;i++)
    {
        write<<i<<",";
        write<<f<<endl;
    }
    write.close();
    write.open("CacheMemory.csv");
    write<<"Address"<<","<<"Allocation,"<<"Points To"<<endl;
    for(int i=0;i<4;i++)
    {
        write<<i<<",";
        write<<f<<","<<"Null"<<endl;
    }
    write.close();
    write.open("FAT.csv");
    write<<"File Name,"<<"Starting Address,"<<"Size"<<endl;
    write.close();
    write.open("nofprograms.txt",ios::app);
    write<<0;
    write.close();
    //ofstream write;
    write.open("nofusers.txt");
    write<<"0";
    write.close();
    dbtoarray();
    for(int i=0;i<1024;i++)
    {
        if(i>100 && i<=200)
            secondarymemory[i]="Kernel";
        if(i>300 && i<=400)
            secondarymemory[i]="Shell";
        if(i>50 && i<=100)
            mainmemory[i]="Kernel";
        if(i>150 && i<=200)
            mainmemory[i]="Shell";
    }
    /*  newprogram("DefaultApp1", 35);
     newprogram("DefaultApp2", 45);
     newprogram("DefaultApp3", 25);
     newprogram("DefaultApp4", 30);*/

    arraytodb();
}
void dbtoarray()
{
    string temp;
    ifstream read;
    read.open("SecondaryMemory.csv");
    getline(read,temp,',');
    getline(read,temp,',');
    // getline(read,temp,'\n');
    for(int i=0;i<1024;i++)
    {
        getline(read,temp,',');
        getline(read,secondarymemory[i],'\n');
        // getline(read,temp,'\n');
    }
    read.close();
    read.open("MainMemory.csv");
    getline(read,temp,',');
    getline(read,temp,',');
    //getline(read,temp,'\n');
    for(int i=0;i<256;i++)
    {
        getline(read,temp,',');
        getline(read,mainmemory[i],'\n');
        // getline(read,temp,'\n');
    }
    read.close();
    read.open("CacheMemory.csv");
    getline(read,temp,',');
    getline(read,temp,',');
    getline(read,temp,'\n');
    for(int i=0;i<4;i++)
    {
        getline(read,temp,',');
        getline(read,cachememory[i],',');
        getline(read,cachepointer[i],'\n');
    }
    read.close();
    read.open("nofprograms.txt");
    getline(read,numberofprograms);
    read.close();
    read.open("nofprograms.txt");
    getline(read,numberofprograms);
    read.close();
    nofprograms=numberofprograms[0]-'0';
    //FAT fat[nofprograms];
    read.open("FAT.csv");
    getline(read,temp,',');
    getline(read,temp,',');
    getline(read,temp,'\n');
    for(int i=0;i<nofprograms;i++)
    {
        getline(read,fat[i].name,',');
        getline(read,temp,',');
        for(int k=0;temp[k]!='\0';k++)
        {
            fat[i].start*=10;
            fat[i].start+=temp[k]-'0';
        }
        getline(read,temp,'\n');
        for(int k=0;temp[k]!='\0';k++)
        {
            fat[i].size*=10;
            fat[i].size+=temp[k]-'0';
        }
    }
}
void arraytodb()
{
    ofstream write;
    write.open("SecondaryMemory.csv");
    write<<"Address"<<","<<"Allocation"<<endl;
    for(int i=0;i<1024;i++)
    {
        write<<i<<",";
        write<<secondarymemory[i]<<endl;
    }
    write.close();
    write.open("MainMemory.csv");
    write<<"Address"<<","<<"Allocation"<<endl;
    for(int i=0;i<256;i++)
    {
        write<<i<<",";
        write<<mainmemory[i]<<endl;
    }
    write.close();
    write.open("CacheMemory.csv");
    write<<"Address"<<","<<"Allocation,"<<"Points To"<<endl;
    for(int i=0;i<4;i++)
    {
        write<<i<<",";
        write<<cachememory[i]<<","<<cachepointer[i]<<endl;
    }
    write.close();
    write.open("nofprograms.txt");
    write<<nofprograms;
    write.close();
    write.open("FAT.csv");
    write<<"File Name,"<<"Starting Address,"<<"Size"<<endl;
    for(int i=0;i<nofprograms;i++)
        write<<fat[i].name<<","<<fat[i].start<<","<<fat[i].size<<endl;
    write.close();
}
void deleteprogram(string name)
{
    int c=0;
    for(int i=0;i<1023;i++)
    {
        if(secondarymemory[i]==name)
            c++;
    }
    if(c>0)
    {
        for(int i=0;i<1023;i++)
        {
            if(secondarymemory[i]==name)
                secondarymemory[i]="Free";
            if(i<256)
                if(mainmemory[i]==name)
                    mainmemory[i]="Free";
        }
        for(int i=0;i<nofprograms;i++)
        {
            if(fat[i].name==name)
            {
                for(int j=i;j<nofprograms-1;j++)
                {
                    fat[j].name=fat[j+1].name;
                    fat[j].start=fat[j+1].start;
                    fat[j].size=fat[j+1].size;
                }
                break;
            }
        }
        nofprograms--;
        cout<<"Deleted!\n";
        arraytodb();
    }
    else{
        cout<<name<<" doesn't exists!";
    }
}
void log(string wr)
{
    string temp=currentuser+".txt";
    ofstream write;
    write.open(temp,ios::app);
    write<<wr<<endl;
}
void newprogram(string name, int size)
{

    int i=0;
    //sleep(size%10);
    cout<<"Installing...";

        sleep(size/10);
        //cout<<".";

    cout<<endl;
    while(secondarymemory[i]!="Free")
        i++;
    int flag=0,temp=size;
    // cout<<i;
    for(int k=i;k<1023;k++)
    {
        if(secondarymemory[k]=="Free")
            temp--;
        if(temp==0)
        {
            flag++;
            break;
        }
    }
    //cout<<flag;
    if(flag==1){
        for(int j=i;j<=(i+size);j++)
        {
            for(int k=j;k<1024;k++)
            {
                if(secondarymemory[k]=="Free"){
                    secondarymemory[k]=name;
                    //  cout<<"Saved at"<<k<<secondarymemory[k]<<endl;
                    break;
                }
            }
        }

        fat[nofprograms].name=name;
        // cout<<fat[nofprograms].size<<fat[nofprograms].start;
        fat[nofprograms].start=i;
        fat[nofprograms].size=size;
        nofprograms++;
        arraytodb();
    }
    else
        cout<<"Not enough Storage!\n";
}

void memorystatus()
{
    int sfr=0,mfr=0;
    cout<<"Calculating..";
    for(int i=0;i<5;i++)
    {
        sleep(1);
        cout<<".";
    }
    for(int i=0;i<1024;i++)
    {
        if(secondarymemory[i]=="Free")
            sfr++;
        if(i<256)
            if(mainmemory[i]=="Free")
                mfr++;
    }
    cout<<"\nSecondary Storage:\nTotal Memory:1023 Bytes\nUsed Memory:"<<1023-sfr<<"\nAvailable Memory:"<<sfr<<" Bytes"<<endl;
    cout<<"\nMain Memory:\nTotal Memory:256 Bytes\nUsed Memory:"<<256-mfr<<" Bytes\nAvailable Memory:"<<mfr<<" Bytes"<<endl;
    /*string t;
     cout<<"Press Enter to continue!\n";
     //cin>>t;
     getline (cin,t);
     cout<<t;*/

}
void cachefifo(string process)
{
    int i;
    string temp,s;
    ifstream read;
    read.open("SecondaryMemory.csv");
    getline(read,s,',');
    getline(read,s,',');
    //getline(read,s,'\n');
    for(i=0;i<1024;i++)
    {
        getline(read,s,',');
        //cout<<s<<endl;
        getline(read,temp,'\n');
        if(temp==process)
            break;
        // getline(read,temp,'\n');

    }
    read.close();
    // cout<<"Start"<<s;
    for(i=0;i<4;i++)
    {
        if(cachememory[i]=="Free")
        {
            cachememory[i]=process;
            cachepointer[i]=s;
            cout<<"Loaded into Cache Memory!\n";
            //  arraytodb();
            break;
        }
    }
    if(i==4)
    {
        for(i=0;i<3;i++)
        {

            cachememory[i]=cachememory[i+1];
            cachepointer[i]=cachepointer[i+1];
        }
        cachememory[3]=process;
        cachepointer[3]=s;
        // cout<<cachepointer[0];

        cout<<"FIFO used to replace!\n";
    }
    arraytodb();
}
void checkcache(string process)
{
    int c=0;
    for(int i=0;i<4;i++)
    {
        if(cachememory[i]==process)
        {   cout<<"Found in Cache\n";
            c++;
            break;
        }
    }
    if(c==0)
    {
        for(int i=0;i<nofprograms;i++)
        {
            if(fat[i].name==process)
            {
                cachefifo(fat[i].name);
            }
        }
    }
}
void runsingle(string process,int n=0)
{
    checkcache(process);
    int j;
    for(j=0;j<nofprograms;j++){
        if(fat[j].name==process)
        {
            //cachefifo(fat[i].name,fat[i].start);
            break;
        }
    }
    int sze=fat[j].size;
    int mfr=0;
    for(int i=0;i<256;i++)
    {
        if(mainmemory[i]=="Free")
            mfr++;
    }
    if(mfr<sze)
    {
        cout<<"Not Enough Space in RAM!\n";
    }
    else{
        int j=0;
        for(int i=0;i<256;i++)
        {
            if(mainmemory[i]=="Free")
            {
                mainmemory[i]=process;
                j++;
            }
            if(j==sze)
                break;
        }
    }
    arraytodb();
    if(n==0){
    cout<<process<<" is Executing!\n";
    for(int i=0;i<sze/10;i++)
    {sleep(1);}
    for(int l=0;l<256;l++)
    {
        if(mainmemory[l]==process)
        {
            mainmemory[l]="Free";
        }
    }
    arraytodb();}
    //cout<<"Finished!";
}
void checklogs()
{
    string t,cu=currentuser+".txt";
    ifstream read;
    read.open(cu);
    cout<<"LOGS for User:"<<currentuser<<endl;
    while(read.good()==1)
    {
        getline(read,t,'\n');
        cout<<t<<endl;
    }
}
void settings()
{
    displaytemplate();
    char choice='0';
    while(choice!='5')
    {
        string loginfo;
        clrscr();
        displaytemplate();
        cout<<"\n1.Check Time\n2.Check Memory Status\n3.Check File Allocation Table\n4.Check Logs\n5.Exit\nEnter your choice:";
        cin>>choice;
        switch (choice)
        {
            case '1':
            {
                string temp="0";
                clrscr();
                time_t now=time(0);
                char *dt=ctime(&now);
                cout<<"Current System Time:"<<dt;
                cout<<"Enter '1' to go back!"<<endl;
                while(temp!="1"){
                cin>>temp;
                if(temp!="1")
                    cout<<"Wrong Input! Enter Again:";
                }

                break;
            }
            case '2':
            {
                string temp="0";
                clrscr();
                memorystatus();
                while(temp!="1"){
                cin>>temp;
                if(temp!="1")
                    cout<<"Wrong Input! Enter Again:";
                }
                break;
            }

            case '3':
            {
                string temp="0";
                clrscr();
                //cout<<"Name\t\t\tStart\t\t\tSize\n";
                cout<<endl;
                for(int i=0;i<nofprograms;i++)
                {
                    cout<<"Name:"<<fat[i].name<<"Start:"<<fat[i].start<<"Size:"<<fat[i].size<<endl;
                }
                 while(temp!="1"){
                cin>>temp;
                if(temp!="1")
                    cout<<"Wrong Input! Enter Again:";
                }
                loginfo="Checked FAT Table";
                log(loginfo);
                break;
            }
            case '4':
            {
                string temp="0";
                clrscr();
                checklogs();
                 while(temp!="1"){
                cin>>temp;
                if(temp!="1")
                    cout<<"Wrong Input! Enter Again:";
                }
                break;
            }
            default:
            {
                cout<<"Wrong Input!";
                break;
            }
        }
    }
}
void displayprogs(queue <string> wait,queue <string> run,queue <string> fin)
{
    cout<<"Round Robin Algorithm with Quantum Time 1s.";
    cout<<"\nWaiting:";
    showq(wait);
    cout<<"\nRunning:";
    showq(run);
    cout<<"\nFinished:";
    showq(fin);
}
void runmultiple(queue <string> multiple,queue <int> size)
{
    queue <string> run;
    queue <string> wait;
    queue <string> fin;
    wait=multiple;
    int check;
    while(!wait.empty())
    {
        clrscr();
        //cout<<"Cycle:"<<j<<endl;
        //for(int i=0;i<multipleprograms;i++)
        // {
        // displayprogs(wait,run,fin);
        run.push(wait.front());
        wait.pop();
        check=size.front();
        size.pop();
        check--;
        //fin.push(run.pop());
        displayprogs(wait,run,fin);
        if(check==0)
        {
            fin.push(run.front());
            for(int l=0;l<256;l++)
            {
                if(mainmemory[l]==run.front())
                {
                    mainmemory[l]="Free";
                }
            }
            run.pop();
            // size.pop();
        }
        else{
            wait.push(run.front());
            run.pop();
            size.push(check);
        }
        // displayprogs(wait,run,fin);
        sleep(1);
        // }
        //j++;
    }
    clrscr();
    displayprogs(wait,run,fin);
    cout<<"\nAll Processes Executed!";
    sleep(3);
    arraytodb();
}
void memory()
{

    int main();
    string loginfo;
    //firsttime();
    dbtoarray();
    char choice='0';
    while(choice!='7')
    {
        //clrscr();
        displaytemplate();
        cout<<"\nYour Apps:"<<endl;
        for(int i=0;i<nofprograms;i++)
        {
            cout<<fat[i].name<<endl;
        }
        cout<<"\n1.Download a new Program\n2.Run a Single Program\n3.Run Multiple Programs\n4.Delete a program\n5.Settings\n6.Log Out\n7.Shut Down\nEnter your choice:";
        cin>>choice;
        switch (choice)
        {
            case '1':
            {
                int c=0;
                string name;
                int size;
                cout<<"Enter the Name of the Program:";
                cin>>name;
                cout<<"Enter the size of "<<name<<":";
                cin>>size;
                if(size>100)
                {
                    cout<<"\nMaximum size of a program is 100 Bytes!";
                    break;
                }
                for(int i=0;i<1024;i++)
                {
                    if(secondarymemory[i]==name)
                        c++;
                }
                if(c==0)
                {
                    newprogram(name,size);
                }
                else{
                    cout<<name<<" already exists!";
                }
                loginfo="Downloaded:"+name;
                log(loginfo);
                break;
            }
            case '2':
            {
                string process;
                cout<<"Enter the name of the Program:";
                cin>>process;
                clrscr();
                runsingle(process);
                loginfo="Single Process Executed:"+process;
                log(loginfo);
                break;
            }
            case '3':
            {
                int z=0;
                string loginfo="Multiple Programs Executed:";
                cout<<"Enter the number of Programs:";
                cin>>multipleprograms;
                if(multipleprograms>nofprograms)
                    cout<<"You don't have "<<multipleprograms<<" Apps"<<endl;
                else{
                    string temp;
                    queue <string> mprograms;
                    queue <int> size;
                    cout<<"Enter the names of the Programs:\n";
                    for(int i=0;i<multipleprograms;i++)
                    {
                        int c=0;
                        cin>>temp;
                        for(int j=0;j<nofprograms;j++)
                        {
                            if(fat[j].name==temp)
                            {
                                int temp=fat[j].size/10;
                                cout<<"Size:"<<temp;
                                size.push(temp);
                                //sizemp[i]=fat[j].size/10;
                                c++;
                                break;
                            }
                        }
                        if(c==0)
                        {
                            cout<<temp<<" doesn't Exists!";
                            z++;
                            break;
                        }
                        else{
                            loginfo+=temp+",";
                            runsingle(temp,1);
                            mprograms.push(temp);
                        }
                    }
                    if(z==0)
                        runmultiple(mprograms,size);
                }
                log(loginfo);
                break;
            }
            case '4':
            {
                string t;
                string name;
                //cout<<superuserpass;
                if(superuserpass!="")
                {
                    cout<<"SuperUser Password required for Deletion.\nEnter Password:";
                    cin>>t;
                }
                if(superuserpass=="" || t==superuserpass){
                    cout<<"Enter the name of the program you want to delete:";
                    cin>>name;
                    deleteprogram(name);
                }
                else{
                    cout<<"Wrong Password!";
                   // sleep(3);
                }

                loginfo="Deleted:"+name;
                log(loginfo);
                 sleep(3);
                break;
            }
            case '5':
            {
                clrscr();
                settings();
                // memorystatus();
                break;
            }
            case '6':
                {

                    cout<<"Logging Out!";
                    sleep(3);
                    main();
                }
            case '7':
            {
                break;
            }
            default:
            {
                cout<<"Please Enter a Valid Input!";
            }
        }
        clrscr();
    }
    //newprogram("",0);
    //arraytodb();
    for(int i=0;i<nofprograms;i++)
        cout<<fat[i].name<<endl;
}
int main()
{
    sleep(2);
    clrscr();
    string temp;
    ifstream read;
    read.open("firsttime.txt");
    getline(read,temp);
    read.close();
    if(temp=="")
    {
        // cout<<"First time!";
        firsttime();
        ofstream write;
        write.open("firsttime.txt");
        write<<"1";
        write.close();
    }
    displaytemplate();
    loginpage();
    sleep(3);
    clrscr();
    // cout<<superuserpass;
    memory();
    clrscr();
    cout<<"Shutting Down";
   sleep(3);
    //displaytemplate();
}

