/* *********************MENTOR MANAGEMENT SYSTEM*********************************
Input Formats:
STUDENT:
    USN          : 4CB1[0-9]IS[0-9][0-9][0-9]
    BRANCH       : ISE
    SEM          : 1-8
    PHONE NUMBER : 10 digit number
    MARKS        : 0-20
    ATTEDNDANCE  : 0-100

FACULTY:
    FID                : [A-Z][0-9]
    PHONE NUMBER       : 10 DIGIT NUMBER
    NUMBER OF STUDENTS : 0-9

*/

#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<string>
#include<regex>

using namespace std;
class secondary_index{
    public:
        string name_list[100],student[100],beloAverageStudent[100];
        int counter,address_list[100],studentadr[100],averageCounter = 0;
        int averageMark[100];
        /*name_list[]        : Faculty Names
          i                  : Iterator
          student[]          : student names
          belowAverageStudent: names of students who have marks below average
          counter            : number of records
          address_list[]     : index of faculties in file
          studentaddr[]      : index of studentaddr in file
          acerageCounter     : count of below average students
           */
        void finsert();             //Faculty insert function
        void insertStudent();       //Student Insert function
        void fdisp();               //Faculty display function
        void disp();                //Student display function
        void dispAverageStudent();  //below average students display function
        void removeRecord(string);  //Student record remove function
        void removeFromAverage(string);
        void fremove(string);       //Faculty remove function
        void fsearch(string);       //Faculty search
        void readFromFile(int);     //reading from faculty file
        void readFromStudent(int);  //reading from student file
        void delFromFile(int);      //Deleting from Faculty file
        void delFromStudent(int);   //Deleting from student file
        string extractName(string); //extracting name from student file
        void createIndex();         //Initialising student file   6.txt
        void createIndex1();        //Initialising faculty file   61.txt
        void fsortIndex();          //Sorting name_list[](faculty name) by their name(alphabetically)
        void sortIndex();           //Sorting student[] (students name) by their name(alphabetically)
        int searchIndex(string);    //Searching students by giving name as parameter
        int fSearchIndex(string);   //Searching faculty by giving name as parameter
};

void secondary_index :: fdisp(){
    int i;
    cout<<"\n\t\t\t\t\t\t FACULTY INDEX FILE"<<endl;
    if(name_list[0] == ""){
     cout<<"\n\t\t\t NO RECORDS OF FACULTIES YET"<<endl;
     return;
    }
    for(i=0;i<=counter;i++)
        cout<<name_list[i]<<endl;
}

void secondary_index :: disp(){
    int i;
    cout<<"\n\t\t\t STUDENT INDEX FILE"<<endl;
    if(student[0] == ""){
     cout<<"\n\t\t\t NO STUDENT RECORDS YET"<<endl;
     return;
    }
    for(i=0;i<=counter;i++)
        cout<<student[i]<<endl;
}

void secondary_index :: dispAverageStudent(){
    int i;
    if(beloAverageStudent[0] == ""){
     cout<<"NO BELOW AVERAGE STUDENTS YET"<<endl;
     return;
    }
    cout<<"\n\t\t\tBELOW AVERAGE STUDENTS"<<endl;
    for(i=0;i<averageCounter;i++){
     cout<<beloAverageStudent[i]<<"\t\t"<<averageMark[i]<<endl;
    }
}

void secondary_index :: createIndex(){
    fstream fp;
    int pos;
    string buffer,name;
    counter = -1;
    fp.open("61.txt",ios::in);
    while(!fp.eof()){
        pos = fp.tellg();
        buffer.erase();
        getline(fp,buffer);
        if(buffer[0]!= '*'){
            if(buffer.empty())
             break;
            name = extractName(buffer);
            name_list[++counter] = name;
            address_list[counter] = pos;
        }
    }
    fp.close();
    fsortIndex();
    buffer.erase();
}

void secondary_index :: createIndex1(){
    fstream fp;
    int pos;
    string buffer,name;
    counter = -1;
    fp.open("6.txt",ios::in);
    while(!fp.eof()){
        pos = fp.tellg();
        buffer.erase();
        getline(fp,buffer);
        if(buffer[0]!= '*'){
            if(buffer.empty())
             break;
            name = extractName(buffer);
            student[++counter] = name;
            studentadr[counter] = pos;
        }
    }
    fp.close();
    fsortIndex();
    buffer.erase();
}

string secondary_index :: extractName(string buffer){
    string usn,name;
    int i=0;
    usn.erase();
    while(buffer[i] != '|') // | is indicator because after each entity we concatenated it with '|' , see 6.txt file
     usn+= buffer[i++];
    name.erase();
    i++;
    while(buffer[i] != '|')
     name+= buffer[i++];
    return name;
}

void secondary_index :: fsortIndex(){
    //Bubble sort algorithm
    int i,j,tempAddress;
    string tempName;
    for(i=0;i<=counter;i++)
     for(j=i+1;j<=counter;j++)
      if(name_list[i] > name_list[j]){
        tempName = name_list[i];
        name_list[i] = name_list[j];
        name_list[j] = tempName;

        tempAddress = address_list[i];
        address_list[i] = address_list[j];
        address_list[j] = tempAddress;
      }
}

void secondary_index :: sortIndex(){
    //Bubble Sort
    int i,j,tempAddress;
    string tempName;
    for(i=0;i<=counter;i++)
     for(j=i+1;j<=counter;j++)
      if(student[i] > student[j]){
        tempName = student[i];
        student[i] = student[j];
        student[j] = tempName;

        tempAddress = studentadr[i];
        studentadr[i] = studentadr[j];
        studentadr[j] = tempAddress;
      }
}

void secondary_index :: insertStudent(){
    regex USN("4CB1[0-9]IS[0-9][0-9][0-9]");
    regex SEM("[1-8]");
    regex BRANCH("ISE");
    regex PHNO("[0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9]");
    //Regular expressions are used to get the desired format of inputs
    string mentor,attendance,usn,name,branch,sem,buffer,phno,m1,m2,m3,m4,m5,m6;
    int pos,n,i,j,k,d,usnFlag;
    int average;
    int mark1,mark2,mark3,mark4,mark5,mark6;
    fstream fp;
    buffer.erase();

    cout<<"\n\t\tEnter the number of students";
    cin>>n;
    outer : for(i=0;i<n;i++){
        usnFlag = 0;
        cout<<"\n\t\tEnter student details"<<endl;
        cout<<"\n\t\tUSN: ";
        cin>>usn;
        for(d=0;d<=counter;d++)
         if(usn.compare(student[i])){
          usnFlag = 1;
          break;
        }
        if(usnFlag){
         cout<<"\n\t\t\t USN ALREADY EXISTS"<<endl;
         continue;
        }
        //regex_match(a,b) compares the regular language of a and b
        if(!regex_match(usn,USN)){
         cout<<"\n\t\tUSN invalid"<<endl;
         continue;
        }
        cout<<"\n\t\tNAME: ";
        cin>>name;
        cout<<"\n\t\tBRANCH: ";
        cin>>branch;
        if(!regex_match(branch,BRANCH)){
         cout<<"\n\t\tOnly ISE branch allowed"<<endl;
         continue;
        }
        cout<<"\n\t\tSEMESTER: ";
        cin>>sem;
        if(!regex_match(sem,SEM)){
         cout<<"\n\t\tOnly 1-8 semester entry allowed"<<endl;
         continue;
        }
        cout<<"\n\t\tPHONE NUMBER: ";
        cin>>phno;
        if(!regex_match(phno,PHNO)){
         cout<<"\n\t\tInvalid phone number format"<<endl;
         continue;
        }
        cout<<"\n\t\tSUBJECT1 MARKS: ";
        cin>>m1;
        if(stoi(m1)<0 || stoi(m1) > 30){
         cout<<"\n\t\tInvalid marks value"<<endl;
         continue;
        }
        cout<<"\n\t\tSUBJECT2 MARKS: ";
        cin>>m2;
        if(stoi(m2)<0 || stoi(m2) > 30){
         cout<<"\n\t\tInvalid marks value"<<endl;
         continue;
        }
        cout<<"\n\t\tSUBJECT3 MARKS: ";
        cin>>m3;
        if(stoi(m3)<0 || stoi(m3) > 30){
         cout<<"\n\t\tInvalid marks value"<<endl;
         continue;
        }
        cout<<"\n\t\tSUBJECT4 MARKS: ";
        cin>>m4;
        if(stoi(m4)<0 || stoi(m4) > 30){
         cout<<"\n\t\tInvalid marks value"<<endl;
         continue;
        }
        cout<<"\n\t\tSUBJECT5 MARKS: ";
        cin>>m5;
        if(stoi(m5)<0 || stoi(m5) > 30){
         cout<<"\n\t\tInvalid marks value"<<endl;
         continue;
        }
        cout<<"\n\t\tSUBJECT6 MARKS: ";
        cin>>m6;
        if(stoi(m6)<0 || stoi(m6) > 30){
         cout<<"\n\t\tInvalid marks value"<<endl;
         continue;
        }
        cout<<"\n\t\tENTER MENTOR NAME: ";
        cin>>mentor;
        cout<<"\n\t\tATTENDANCE: ";
        cin>>attendance;
        if(stoi(attendance)< 0 || stoi(attendance) > 100){
         cout<<"\n\t\tInvalid attendance value"<<endl;
         continue;
        }
        //stoi() is used tp convert string to integer
        mark1 = stoi(m1);
        mark2 = stoi(m2);
        mark3 = stoi(m3);
        mark4 = stoi(m4);
        mark5 = stoi(m5);
        mark6 = stoi(m6);
        average = (mark1 + mark2 + mark3 + mark4 + mark5 + mark6)/6;
        buffer = usn + "\t|\t" + name + "\t|\t" + branch + "\t|\t" + phno + "\t|\t" + m1 + "\t|\t" + m2 + "\t|\t" + m3 + "\t|\t" + m4 + "\t|\t" + m5 + "\t|\t" + m6 + "\t|\t" + mentor + "\t|\t" + attendance + "$\n";
        fp.open("6.txt",ios::out|ios::app);
        pos = fp.tellp();
        fp<<buffer;
        fp.close();
        student[++counter] = name;
        studentadr[counter] = pos;
        if(average < 18){ //need not be 18
         beloAverageStudent[averageCounter] = name;
         averageMark[averageCounter] = average;
         averageCounter++;
        }
        sortIndex();
        cout<<"\n\t\tStudent Details Recorded Successfully"<<endl;
    }
}

void secondary_index :: finsert(){
    string st1,st2,fid,name,buffer,phno,st_name[10],number;
    regex FID("[A-Z][0-9]"); //Format of ID should be 'A4' 'B8' like this.
    regex PHNO("[0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9]");
    regex NUMBER("[1-9]");
    int k,pos,m,i,j;
    fstream fp;
    buffer.erase();
    cout<<"\n\t\tENTER Faculty DETAILS"<<endl;
    cout<<"\n\t\tFID: (format [A-Z][0-9])";
    cin>>fid;
    if(!regex_match(fid,FID)){
     cout<<"\n\t\tInvalid fid"<<endl;
     return;
    }
    cout<<"\n\t\tNAME: ";
    cin>>name;
    cout<<"\n\t\tPHONE: ";
    cin>>phno;
    if(!regex_match(phno,PHNO)){
     cout<<"\n\t\tInavlid phone number format"<<endl;
     return;
    }
    cout<<"\n\t\tEnter number of students";
    cin>>number;
    if(!regex_match(number,NUMBER)){
     cout<<"\n\t\tOnly maximum 9 students can be allotted"<<endl;
     return;
    }
    buffer = fid + "\t|\t" + name + "\t|\t" + phno + "|"+ number +"$\n";
    fp.open("61.txt",ios::out|ios::app);
    pos = fp.tellp();
    fp<<buffer;
    fp.close();
    name_list[++counter] = name;
    address_list[counter] = pos;
    fsortIndex();
    cout<<"\n\t\tFaculty Inserted Successully"<<endl;
}

void secondary_index :: readFromStudent(int pos){
    int address,i;
    string buffer;
    fstream fp;
    fp.open("6.txt",ios::in);
    address = studentadr[pos];
    fp.seekp(address,ios::beg);
    getline(fp,buffer);
    cout<<"\n\t\t\t\t Found the record:"<<buffer;
    fp.close();
}

void secondary_index ::readFromFile(int pos){
    int address,i;
    string buffer;
    fstream fp;
    fp.open("61.txt",ios::in);
    address = address_list[pos];
    fp.seekp(address,ios::beg);
    getline(fp,buffer);
    cout<<buffer;
    fp.close();
}

void secondary_index :: fremove(string key){
    int pos = 0,t,choice;
    string buffer;
    buffer.erase();
    pos = fSearchIndex(key);
    if(pos == -1)
     cout<<"\n\t\t\t Record not found"<<endl;
    else if(pos>=0){
        readFromFile(pos);
        delFromFile(pos);
        t = pos;
        while(name_list[t] == key && t>=0){
            readFromFile(t);
            delFromFile(t);
            t++;
        }
    }
}

void secondary_index :: removeRecord(string key){
    int pos = 0,t,choice;
    string buffer;
    buffer.erase();
    pos = searchIndex(key);
    if(pos == -1)
     cout<<"\n\t\t\t Record not found"<<endl;
    else if(pos>=0){
        removeFromAverage(key);
        readFromStudent(pos);
        delFromStudent(pos);
        t = pos;
        while(name_list[t] == key && t>=0){
            readFromStudent(t);
            delFromStudent(t);
            t++;
        }
    }
}

void secondary_index :: removeFromAverage(string key){
    int k,flag = 0,position;
    for(k=0;k<averageCounter;k++){
     if(beloAverageStudent[k] == key){
        flag = 1;
        position = k;
        break;
     }
    }
    if(flag){
     for(k=position;k<averageCounter;k++){
        beloAverageStudent[k] = beloAverageStudent[k+1];
     averageCounter--;
     }
    }
}

void secondary_index :: delFromFile(int pos){
    char delch = '*';
    int i,address;
    fstream fp;
    fp.open("61.txt");
    address = address_list[pos];
    fp.seekp(address,ios::beg);
    fp.put(delch);
    cout<<"\n\t\t\t\t Record deleted"<<endl;
    for(i=pos;i<counter;i++){
        name_list[i] = name_list[i+1];
        address_list[i] = address_list[i+1];
    }
    counter--;
}

void secondary_index :: delFromStudent(int pos){
    char delch = '*';
    int i,address;
    fstream fp;
    fp.open("6.txt");
    address = studentadr[pos];
    fp.seekp(address,ios::beg);
    fp.put(delch);
    cout<<"\n\t\t\t\t Record deleted"<<endl;
    for(i=pos;i<counter;i++){
        student[i] = student[i+1];
        studentadr[i] = studentadr[i+1];
    }
    counter--;
}

int secondary_index :: searchIndex(string key){
    int low=0,high = counter,mid=0,flag = 0,pos;
    while(low<=high){
        mid = (low+high)/2;
        if(student[mid] == key){
            flag = 1;
            break;
        }
        if(student[mid] > key)
         high = mid - 1;
        if(student[mid] < key)
         low = mid + 1;
    }
    if(flag){
     readFromStudent(mid);
     return mid;
    }
    else{
     cout<<"\n\t\t\tStudent Not Found"<<endl;
     return -1;
    }
}

int secondary_index :: fSearchIndex(string key){
    int low=0,high=counter,mid=0,flag = 0,pos;
    while(low<=high){
        mid = (low+high)/2;
        if(name_list[mid] == key){
            flag = 1;
            break;
        }
        if(name_list[mid] >key)
         high = mid - 1;
        if(name_list[mid] < key)
         low = mid + 1;
    }
    if(flag){
     cout<<"\n\t\tFaculty Found"<<endl;
     readFromFile(mid);
     return mid;
     }
    else{
     cout<<"\n\t\tFaculty Not Found"<<endl;
     return -1;
    }
}

int main(){
    int choice;
    string key;
    secondary_index i1,i2;
    i1.createIndex();
    i2.createIndex1();
    cout<<"\n\t\t     WELCOME TO MENTOR MANAGEMENT SYSTEM"<<endl;
    while(1){
        cout<<"\n\t\t\  *************************************"<<endl;
        cout<<"\n\n\t\t FACULTY :\n\n\t\t\t1:Add Faculty \n\n\t\t\t2.Faculty Search \n\n\t\t\t3.Faculty Delete\n\n\n\t\t STUDENT :\n\n\t\t\t4.Add Student\n\n\t\t\t5.Student Search\n\n\t\t\t6.Student Delete\n\n\n\t\t DISPLAY:\n\n\t\t\t7.Display Faculties\n\n\t\t\t8.Display Students\n\n\n\t\t9.Below Average Students\n\n\n\n\t\t10.Exit"<<endl;
        cout<<"\n\n\t\t\tEnter your choice:\t";
        cin>>choice;

        switch(choice){
            case 1:
                cout<<"\n\t\t\  *************************************"<<endl;
                i1.finsert();
                cout<<"\n\t\t\  *************************************"<<endl;
                break;
            case 2:
                cout<<"\n\t\t\  *************************************"<<endl;
                cout<<"\n\t\t\t Enter the name to display records:";
                cin>>key;
                i1.fSearchIndex(key);
                cout<<"\n\t\t\  *************************************"<<endl;
                break;
            case 3:
                cout<<"\n\t\t\  *************************************"<<endl;
                cout<<"\n\t\tEnter the name to remove";
                cin>>key;
                i1.fremove(key);
                cout<<"\n\t\t\  *************************************"<<endl;
                break;
            case 4:
                cout<<"\n\t\t\  *************************************"<<endl;
                i2.insertStudent();
                cout<<"\n\t\t\  *************************************"<<endl;
                break;
            case 5:
                cout<<"\n\t\t\  *************************************"<<endl;
                cout<<"\n\t\t\t Enter the name to display records:";
                cin>>key;
                i2.searchIndex(key);
                cout<<"\n\t\t\  *************************************"<<endl;
                break;
            case 6:
                cout<<"\n\t\t\  *************************************"<<endl;
                cout<<"\n\t\tEnter the name to remove from records:";
                cin>>key;
                i2.removeRecord(key);
                cout<<"\n\t\t\  *************************************"<<endl;
                break;
            case 7:
                cout<<"\n\t\t\  *************************************"<<endl;
                i1.fdisp();
                cout<<"\n\t\t\  *************************************"<<endl;
                break;
            case 8:
                cout<<"\n\t\t\  *************************************"<<endl;
                i2.disp();
                cout<<"\n\t\t\  *************************************"<<endl;
                break;
            case 9:
                cout<<"\n\t\t\  *************************************"<<endl;
                i2.dispAverageStudent();
                cout<<"\n\t\t\  *************************************"<<endl;
                break;
            case 10:
                return 0;
            default:
                cout<<"\n\t\tWrong choice"<<endl;
                break;
        }
    }
}
