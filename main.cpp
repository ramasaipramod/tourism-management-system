#include<iostream>
#include<conio.h>
#include<cstring>
#include<unistd.h>
#include<cstdlib>
#include<math.h>
#include<mysql.h>
#include<mysqld_error.h>
#include<sstream>
#include<windows.h>

using namespace std;
char host[]="localhost";
char user[]="root";
char pass[]="pramod";

class managers{
	public:
    char name[20];
    double mobile;
    char password[15];
};

class customer : public managers{
    public:
    int userid;
};

class trip{
    protected:
    int members;
    int package_id;
};

int first=1;

HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);

void heading(){
    system("CLS");
     SetConsoleTextAttribute(h,11);
    cout<<"---------------------------------------------------------------------------------------------------------------------------------------------------------------\n"<<endl<<endl;
    if(first==1){
    cout<<"                                                                      Welcome to Wanderlust.co\n"<<endl<<endl;
    first=0;
    }
    else{
    cout<<"                                                                          The Wanderlust.co\n"<<endl<<endl;
    }
    cout<<"----------------------------------------------------------------------------------------------------------------------------------------------------------------\n"<<endl<<endl;
}

string convertToString(char* a, int size){
    int i;
    string s = "";
    for (i = 0; i < size; i++) {
        s = s + a[i];
    }
    return s;
}

int check(int ch,int *arr,int t){
        for(int i=0;i<t;i++){
        if(arr[i]==ch)
        return 1;
		}
		return 0;
	}

int registeruser(char Password[15],char Name[20],double PhoneNO){
	
	MYSQL *obj;
	int answer;
	char *consult;
	char *sentence;
	string sentence_aux;
	if(!(obj=mysql_init(0))){
		cout<<"     Error: Mysql object could not be created."<<endl<<endl;
	}else{
		if(!mysql_real_connect(obj,host,user,pass,"Tourism",3306,NULL,0)){
			cout<<"     Error: some database info is wrong or do not exist,"<<endl<<endl;
		}else{      
				sentence_aux="INSERT INTO customer(Name,Password,PhoneNO) VALUES('%s','%s','%lf')";
				sentence=new char[sentence_aux.length()+1];
				strcpy(sentence,sentence_aux.c_str());
				consult=new char[strlen(sentence)+sizeof(Name)+sizeof(Password)+sizeof(double)];
				sprintf(consult,sentence,Name,Password,PhoneNO);
				if(mysql_ping(obj)){
					cout<<"     Error: Can't connect."<<endl<<endl;
					cout<<mysql_error(obj)<<endl<<endl;
				}
				if(mysql_query(obj,consult)){
					cout<<"     Error: "<<mysql_error(obj)<<endl<<endl;
					rewind(stdin);
					getchar();
				}else{
					cout<<"     Info added correctly"<<endl<<endl;
				}
				mysql_store_result(obj);
		}
	}
	MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    string pswd;
    char* res_str;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,host,user,pass,"tourism", 3306, NULL, 0);
    if(conn){
        int qstate = mysql_query(conn, "SELECT  MAX(User_ID) FROM customer");

        if(!qstate){
            res = mysql_store_result(conn);
          
            while(row = mysql_fetch_row(res)){
               return atoi(row[0]);
        }
    }
}
	
}

int registertrip(int pkgid,int userid){
    MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,host,user,pass,"tourism",3306,NULL,0);
    if(conn){
    int qstate = 0;
    int p1=pkgid,t=0;
    while(p1!=0){
        p1=p1/10;
        t++;
    }
    int tripid=pkgid;
	tripid= tripid+userid*pow(10,t);
	int adults,kids;
    string dt;
    cout<<"     Enter number of adults:";
    cin>>adults;
    cout<<"     Enter number of kids:";
    cin>>kids;
    cout<<"     Enter date of your choice for journey (DD-MM-YYYY):";
    cin>>dt;
    int budget;
    MYSQL* conn1;
    MYSQL_ROW row;
    MYSQL_RES* res;
    char* res_str;
    conn1 = mysql_init(0);
    conn1 = mysql_real_connect(conn1,host,user,pass,"tourism", 3306, NULL, 0);
    if(conn1){
        int qstate = mysql_query(conn1, "select id,selector,place,budget,night,day,duration,desp from packages");
        if(!qstate){
            res = mysql_store_result(conn1);
            while(row = mysql_fetch_row(res)){if(atoi(row[0])==tripid){
            budget=atoi(row[3]);
            }
        }
    }
  }
    
    int amnt=(adults+0.7*kids)*budget;
	stringstream ss;
	    
        ss << "INSERT INTO trip (tripid,userid,adults,kids,dt,pkgid,amnt) VALUES ("<<tripid<<"," <<userid<<","<<adults<<","<<kids<<",'"<<dt<<"',"<<pkgid<<","<<amnt<<")";
        
        string query = ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if(qstate == 0){
            cout << "\n     Your booking is completed..Pls pay the bill in reception!!" << endl;
        }else{
            cout << "\n     Error obtained" << mysql_error(conn) << endl;
        }
        }else{
        cout << "\n     Connection Error" << endl;
    }
}

string askcurrentid(int userid){
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    string pswd;
    char* res_str;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,host,user,pass,"tourism", 3306, NULL, 0);
    if(conn){
        int qstate = mysql_query(conn, "SELECT  User_ID, Password,Name,phoneNO FROM customer");
        if(!qstate){
            res = mysql_store_result(conn);
            while(row = mysql_fetch_row(res)){if(atoi(row[0])==userid){
                return row[1];
             }
        }
    }
  }}

int addpackage(){
    MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,host,user,pass,"tourism",3306,NULL,0);
    if(conn){
       int qstate = 0;
        int type;
   string place;
   int budget;
   int night;
   int day;
   int duration;
   string desp;
    cout<<"     Enter number for Package"<<endl<<endl;
    cout<<"     1.For International"<<endl<<endl;
    cout<<"     2.For National"<<endl<<endl;
    cout<<"     3.For Piligrimage"<<endl<<endl;
    cout<<endl<<endl<<"     option:";
    cin>>type;
    
    cout<<"     Enter the Package Name:";
    cin>>place;
    cout<<"     Enter total number of days:";
    cin>>duration;
    cout<<"     Enter number of days:";
    cin>>day;
    cout<<"     Enter number of nights:";
    cin>>night;
    cout<<"     Enter budget per person:";
    cin>>budget;
    cout<<"     Enter Description about place:";
    cin.ignore(100,'\n');
    getline(cin,desp);

        stringstream ss;
        ss << "INSERT INTO packages (selector, Place, Budget, Night, DAY,DURATION,Desp) VALUES("<< type <<",'"<<place<<"',"<<budget<<","<<night<<","<<day<<","<<duration<<",'"<<desp<<"')";

        string query = ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if(qstate == 0){
            cout << "     Package created!!" << endl;
            
            
        }else{
            cout << "     Error obtained" << mysql_error(conn) << endl;
          
        }
    }else{
        cout << "     Connection Error" << endl;
        
    }
    
    sleep(3);
    return 0;
}

int showpackage(int type,int userid){
	heading();
	int arr[50],total=0,t=0;
    cout<<"     Package Type:";
    if(type==1)
     cout<<" International";
    if(type==2)
     cout<<" National";
    if(type==3)
     cout<<" Piligrimage";
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,host,user,pass,"tourism",3306,NULL,0);
    if(conn){
        int qstate = mysql_query(conn, "SELECT * FROM packages");
        if(!qstate){
            res = mysql_store_result(conn);
            while(row = mysql_fetch_row(res)){
            	if(atoi(row[1])==type){
                cout <<"\n     Trip ID :"<<row[0] <<"\n     Destination :" << row[2] <<"\n     Budget per person in INR :" << row[3]<<"\n     Duration :" << row[6]<<"days"<<"\n     Description :" << row[7]<< endl << endl;
                arr[t]=atoi(row[0]);
                t++;
            }
		}
        }
    }

    int opt;
	cout<<"     Enter trip id for booking or Enter 0 for back:";
    cin>>opt;
    while(opt!=0 && check(opt,arr,t)!=1){
    cout<<"     Invalid entry Enter again:";
    cin>>opt;
	}
	if(opt==0)
	return 0;
	else{
	cout<<endl<<endl;
	registertrip(opt,userid);
	sleep(2);
	}
}

void typeselector(int type){
    cout<<"     Package Type:";
    if(type==1)
     cout<<"     International";
    if(type==2)
     cout<<"     National";
    if(type==3)
     cout<<"     Piligrimage";
}

int budgetselector1(int userid){
    int amnt;
    int arr[50],total=0,t=0;
    heading();
    cout<<"     Enter"<<endl<<endl;
    cout<<"     1.For Package less than INR 2000"<<endl<<endl;
    cout<<"     2.For Package between INR 2000 and INR 5000"<<endl<<endl;
    cout<<"     3.For Package between INR 5000 and INR 10000"<<endl<<endl;
    cout<<"     4.For Package between INR 10000 and INR 50000"<<endl<<endl;
    cout<<"     5.For Package between INR 50000 and INR 150000"<<endl<<endl;
    cout<<"     6.Exit"<<endl<<endl;
    cout<<endl<<"     option:";
    int opt;
    cin>>opt;
    
    int ub,lb;
    switch(opt){
    	case 1:{
		    lb=0;
    		ub=2000;
		}
			break;
    		

		case 2:{
    		lb=2000;
    		ub=5000;
		}
			break;
    	
    	case 3:{
    		lb=5000;
    		ub=10000;
		}
    	    break;
    	    
    	case 4:{
    		lb=10000;
    		ub=50000;
		}
    	    break;
    	    
    	case 5:{
    		lb=50000;
    		ub=150000;
		}
    	    break;
    	    
    	case 6:
    		return 0;
    	break;
	}
	MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,host,user,pass,"tourism",3306,NULL,0);
    if(conn){
        int qstate = mysql_query(conn, "SELECT * FROM packages");

        if(!qstate){
            res = mysql_store_result(conn);

            while(row = mysql_fetch_row(res)){
            	if(lb<=atoi(row[3]) && atoi(row[3])<=ub)
                cout <<"     Trip ID:"<<row[0] <<"\n     Destination:" << row[2] <<"\n     Budget per person in INR:" << row[3]<<"\n     Duration :" << row[6]<<"days"<<"\n     Description :" << row[7]<< endl << endl;
                arr[t]=atoi(row[0]);
                t++;                
			 }
        }
    }
    int opt1;
	cout<<"     Enter trip id for booking or enter 0 for exit:";
    cin>>opt1;
    while(opt1!=0 && check(opt1,arr,t)!=1){
    cout<<"     Invalid entry Enter again:";
    cin>>opt1;
	}
	if(opt1==0)
	return 0;
	else{
	cout<<endl<<endl;
	registertrip(opt1,userid);
	sleep(2);
	}
}

int budgetselector(int userid){
    int amnt;
    int arr[50],total=0,t=0;
    int p=1;
    while(p){
    heading();
    int ub,lb;
    cout<<"     Your budget friendly packages"<<endl<<endl;
    cout<<"     Enter the minimum amount per person:";
    cin>>lb;
    cout<<"     Enter the maximum amount per person:";
    cin>>ub;
    
	MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,host,user,pass,"tourism",3306,NULL,0);
    if(conn){
        int qstate = mysql_query(conn, "SELECT * FROM packages");

        if(!qstate){
            res = mysql_store_result(conn);

            while(row = mysql_fetch_row(res)){
            	if(lb<=atoi(row[3]) && atoi(row[3])<=ub)
                cout <<"     Trip ID:"<<row[0] <<"\n     Destination:" << row[2] <<"\n     Budget per person in INR:" << row[3]<<"\n     Duration :" << row[6]<<"days"<<"\n     Description :" << row[7]<< endl << endl;
                arr[t]=atoi(row[0]);
                t++;                
			 }
        }
    }
	if(t==0){
	cout<<"     No packages in this range :(";
    }
    if(t!=0){
    int opt1;
	cout<<"     Enter trip id for booking or Enter 0 for back:";
    cin>>opt1;
    while(opt1!=0 && check(opt1,arr,t)!=1){
    cout<<"     Invalid entry Enter again:";
    cin>>opt1;
	}
	if(opt1==0){
		p=0;
		return 0;
	}
	else{
	cout<<endl<<endl;
	registertrip(opt1,userid);
    p=0;
	sleep(2);
	}
    }
    t=0;
    }
}

int imp_details(){
	int t=0;
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,host,user,pass,"tourism",3306,NULL,0);
    if(conn){
        int qstate = mysql_query(conn, "SELECT * FROM imp_details");

        if(!qstate){
            res = mysql_store_result(conn);

            while(row = mysql_fetch_row(res)){
            cout <<"\n     Name:"<<row[0] <<"\n     Contact:" << row[1] <<"\n     Work description:" << row[2] << endl << endl;
            t++;            	
             }
        }
    }
    if(t==0){
    	cout <<"\n     No important details added..";
	}
    cout <<"\n\n     Press any key to exit  ";
	char ch;
	if(cin>>ch){
		return 1;
	}
	
}

int addimp_details(){
    MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,host,user,pass,"tourism",3306,NULL,0);
    if(conn){
       int qstate = 0;
      string name;
      string contact;
      string type;    
    cout<<"     Enter Name of person:";
    cin>>name;
    cin.ignore(100,'\n');
    cout<<"     Enter Contact Number:";
    getline(cin,contact);
    cout<<"     Enter work description:";
    getline(cin,type);
        stringstream ss;
        ss << "INSERT INTO imp_details( Name, Contact, type) VALUES('"<<name<<"','"<<contact<<"','"<<type<<"')";

        string query = ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if(qstate == 0){
            cout << "     Details added..." << endl;  
        }else{
        cout << "     Insertion Error" << mysql_error(conn) << endl;
          
        }
       }else{
        cout << "     Connection Error" << endl;
    }
    cout <<"\n\n     Press any char to exit  ";
	char ch;
	if(cin>>ch){
		return 1;
	}
}

string newpass(){
    char ch,ch1;
    string pass,pass1;
    cout<<"     Set a Password:";
     while (true) {
        ch = getch();
        if (ch == 13) {
            cout << endl;
           break;
        }
        else if (ch == 8
                 && pass.length() != 0) {
            pass.pop_back();
            cout << "\b \b";
 
            continue;
        }
        else if (ch == 8
                 && pass.length() == 0) {
            continue;
        }
        pass.push_back(ch);
        cout << "*";
        
    }
    cout<<"     Enter again Password:"; 
    while (true) {

        ch1 = getch();
        if (ch1 == 13) {
            cout << endl;
           break;
        }
        else if (ch1 == 8
                 && pass1.length() != 0) {
            pass1.pop_back();
            cout << "\b \b";
 
            continue;
        }
        else if (ch1 == 8
                 && pass1.length() == 0) {
            continue;
        }
        pass1.push_back(ch1);
        cout << "*";
        
    }
    if(pass==pass1)
    return pass;
    else
    return 0;
}

int passcheck(string pswd){
    int times=3;
    char ch;
    string pass;
    while(times>0){
        times--;
    cout<<"     Enter Password:";    
    while (true) {

        ch = getch();
        if (ch == 13) {
            cout << endl;
           break;
        }
        else if (ch == 8
                 && pass.length() != 0) {
            pass.pop_back();
            cout << "\b \b";
 
            continue;
        }
        else if (ch == 8
                 && pass.length() == 0) {
            continue;
        }
        pass.push_back(ch);
        cout << "*";
        
    }
    if(pass==pswd){
        cout<<"\n     Logged in!";
        sleep(2);
        return 0;
    }
    else{
        pass.clear();
        cout<<"\n     Try Again\n";
    }
    }

}

int approvecheck(int tripid){
	MYSQL* conn;
    MYSQL_ROW row1;
    MYSQL_RES* res1;
    char* res_str;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,host,user,pass,"tourism", 3306, NULL, 0);
    if(conn){
        int qstate = mysql_query(conn, "select tripid,approval from approvals");
        if(!qstate){
            res1 = mysql_store_result(conn);
            while(row1 = mysql_fetch_row(res1)){
                if(tripid==atoi(row1[0])){
                    return atoi(row1[1]);
                }
            }
                    return 3;
        }
    }
	
}

int approvals(){
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,host,user,pass,"tourism",3306,NULL,0);
    if(conn){
        int qstate = mysql_query(conn, "SELECT * FROM trip");
        if(!qstate){
            res = mysql_store_result(conn);
            while(row = mysql_fetch_row(res)){
                if(approvecheck(atoi(row[0]))==3)
                cout <<"\n     Trip ID:"<<row[0] <<"\n     User ID:" << row[1] <<"\n     No of Adults:" << row[2]<<"\n     No of Kids:" << row[3]<<"\n     Date:" << row[4]<<"\n     Amount in INR:" << row[6]<< endl << endl;
		    }
        }
    }
    cout<<"     Enter trip id for approval or 0 for exit:";
    int tripid;
	cin>>tripid;
	if(conn){
	int qstate = 0;
    if(tripid!=0){
    	int approval=0;
    	stringstream ss;
        ss << "INSERT INTO approvals (tripid,approval) VALUES("<< tripid <<","<< approval <<")";
        string query = ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if(qstate == 0){
            cout << "     Package approved!!" << endl;
            sleep(2);
        }else{
            cout << "     Error obtained" << mysql_error(conn) << endl;
        }	
	}
    }else{
        cout << "     Connection Error" << endl; 
    }
    return 0;
}

int viewbooked(int userid){
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,host,user,pass,"tourism",3306,NULL,0);
    if(conn){
        int qstate = mysql_query(conn, "SELECT * FROM trip");
        if(!qstate){
            res = mysql_store_result(conn);
            while(row = mysql_fetch_row(res)){
                if(approvecheck(atoi(row[0]))==0)
                cout <<"\n     Trip ID: "<<row[0] <<"\n     User ID: " << row[1] <<"\n     No of Adults: " << row[2]<<"\n     No of Kids: " << row[3]<<"\n     Date: " << row[4]<<"\n     Amount in INR :" << row[6]<< endl << endl;
		   }
        }
    } 
}

int main(){
    int times=3,t;
    string Managerpswd="1234";
    while (1)
    {
    start:
    heading();
    cout<<"     Enter"<<endl<<endl;
    cout<<"     1. For Customer"<<endl<<endl;
    cout<<"     2. For Manager"<<endl<<endl;
    cout<<"     3. Exit"<<endl<<endl;
    cout<<endl<<"     option:";
    int opt,opt1;
    cin>>opt;
    if(opt<3)
    user:
    heading();

    switch(opt){

        case 1:
        
        cout<<"     1. Login"<<endl<<endl;
        cout<<"     2. Sign Up"<<endl<<endl;
        cout<<"     3. Exit"<<endl<<endl;
        cout<<endl<<"     option:";
        cin>>opt1;
        if(opt1==3)
        goto start;
        if(0<opt1<3)
        heading();
        switch(opt1){

        case 1:{
        cout<<"     Login"<<endl<<endl;
        int userid;
        int k=0;
        cout<<"     Enter User Id :";
        cin>>userid;
        string PASS=askcurrentid(userid);
        int key=passcheck(PASS);
        if(key==0){
        user1:
        heading();
        int opt3;
		cout<<"     Enter"<<endl<<endl;
        cout<<"     1. View Packages"<<endl<<endl;
        cout<<"     2. View booked package"<<endl<<endl;
        cout<<"     3. Exit"<<endl<<endl;
        cout<<endl<<"     option:";
        cin>>opt3;
        switch(opt3){
        case 1:
        user2:
        heading();
        cout<<"     Select a package list"<<endl<<endl<<endl;
            cout<<"     1. International"<<endl<<endl;
            cout<<"     2. National"<<endl<<endl;
            cout<<"     3. Piligrimage"<<endl<<endl;
            cout<<"     4. Your budget Holiday Trip"<<endl<<endl;
            cout<<"     5. Exit"<<endl<<endl;
        cout<<endl<<endl<<"     choice:";
        int opt4;
        int choice1;
        cin>>opt4;
        int b;
        switch(opt4){
        	case 1:
        	 heading();
        	 b=showpackage(1,userid);
        	 if(b==0){
        	 	b=1;
        	 	goto user2;
			 }
        	 break;
        	case 2:
        	 heading();
        	 b=showpackage(2,userid);
        	 if(b==0){
        	 	b=1;
        	 	goto user2;
			 }
        	 break;
        	case 3:
        	 heading();
        	 b=showpackage(3,userid);
        	 if(b==0){
        	 	b=1;
        	 	goto user2;
			 }
        	 break;
        	case 4:
        	 heading();
        	 b=budgetselector(userid);
        	 if(b==0){
        	 	b=1;
        	 	goto user2;
			 }
        	 break;
        	case 5:
        	 goto user1;
		}
        break;
        case 2:
       	heading();
        viewbooked(userid);
        cout<<"\n    Enter b for back";
      	getch();
      	t=0;
    	if(t==0){
        goto user1;
	    }
        break;
        case 3:
        cout<<"\n     Logging out";
        for(int i=0;i<4;i++){
        sleep(1);
        cout<<".";
		}
        goto user;
        break;
		}
        }
        }
        break;
       
        case 2:{
        cout<<"     Sign Up"<<endl<<endl;
        customer A;
        char choice;
		cin.ignore(100,'\n');
        cout<<"     Enter Your Name :";
		cin.getline(A.name,20,'\n');
        cout<<"     Enter Your Mobile no :";
        cin>>A.mobile;
        string newcheck=newpass();
        if(newcheck!=""){
        strcpy(A.password,newcheck.c_str());
        int user_id=registeruser(A.password,A.name,A.mobile);
        cout<<endl<<endl<<"     Your have been registered! "<<endl<<endl;
        cout<<"     Your User id :"<<user_id<<endl<<endl;
        cout<<"     Would like to Explore Our Packages [y/n]:";
        cin>>choice;
            heading();
        if(choice=='Y' || choice == 'y'){
        cout<<"     ----Select a package list----"<<endl<<endl;
            cout<<"     1. International"<<endl<<endl;
            cout<<"     2. National"<<endl<<endl;
            cout<<"     3. Piligrimage"<<endl<<endl;
            cout<<"     4. Your budget Holiday Trip"<<endl<<endl;
            cout<<"     5. Exit"<<endl<<endl;
            cout<<endl<<endl<<"     option:";
            int selector;
            cin>>selector;
            if(selector<4)
            showpackage(selector,user_id);
            if(selector==4)
            budgetselector(user_id);
            if(selector==5)
            goto user;
           
        }
        if(choice=='N' || choice == 'n'){
        cout<<"     Thank you! "<<endl<<endl;  
        sleep(2);
        }
        }
        else{
            cout<<"     Not registered try again!!"<<endl<<endl;
        }
        break;
        }
        }
        break;
        
        case 2:
        {
         heading();
         int m;
         cout<<"     Welcome Manager\n\n";
         int checker=passcheck(Managerpswd);
         if(checker==0){
            int opt2;
            manager:
            heading();
            cout<<"     Manager\n\n\n";
            cout<<"     Enter"<<endl<<endl;
            cout<<"     1. Add Package"<<endl<<endl;
            cout<<"     2. Approvals"<<endl<<endl;
            cout<<"     3. Important details"<<endl<<endl;
            cout<<"     4. Add Important details"<<endl<<endl;
            cout<<"     5. Exit"<<endl<<endl;
            cout<<endl<<endl<<"     option:";
            cin>>opt2;
            switch (opt2)
            {
            case 1:
            {
            heading();
            cout<<"     Manager\n\n\n";
            cout<<"     ----Add Package----"<<endl<<endl;
            addpackage();
            cout<<"\n\n     Enter b to exit";
            getch();
      	    t=0;
    	    if(t==0){
            goto manager;
	        }
            }
            break;
            case 2:
            {
            heading();
            cout<<"     Manager\n\n";
            cout<<"     ----Approvals----"<<endl<<endl;
            m=approvals();
            if(m==0){
            	goto manager;
			}
            }
            break;
            case 3:
            {
            heading();
            cout<<"     Manager\n\n";
            cout<<"     ----Important Details----"<<endl<<endl;
            m=imp_details();
            if(m==1){
            	goto manager;
			}
            }
            break;
            case 4:
            {
            heading();
            cout<<"     Manager\n\n";
            cout<<"     ----Add Details----"<<endl<<endl;
            m=addimp_details();
            if(m==1){
            	goto manager;
			}
            
            }
            break;
            case 5:
            {
            cout<<"\n     Logging out";
            for(int i=0;i<4;i++){
            sleep(1);
            cout<<".";
		    }
            goto start;		
			}
            default:
            break;
            }
         }
        }
        
        break;
        case 3:
        return 0;
    
    }
    }
    


}
