//command to compile : g++ init.cpp sqlite3.io -I . -o init

#include<cstdio>
#include<conio.h>
#include<sqlite3.h>
#include<bits/stdc++.h>

using namespace std;

// declare classes and functions
class sqlFunc{
private:
	string query;
	sqlite3* db;
	static int callback(void *NotUsed, int argc, char **argv, char **azColName) {

		for(int i = 0; i < argc; i++) {
	        cout << azColName[i] << ": " << argv[i] << endl;
	    }
	    cout << endl;
	    return 0;
	}

public:
	sqlFunc(sqlite3* con){db = con; return;}
	
	void registerCC(){
		query = "Insert into centre('apple', 'orange', 'banana', 'mango', 'guava') values (0.0, 0.0, 0.0, 0.0, 0.0);";
		int rc = sqlite3_exec(db, query.c_str(), NULL, NULL, NULL);
		if(rc) cout << "Error encountered on registering centre" << endl;
		else cout << "Centre registered successfully" << endl;
	}
	
	void deleteCC(int id){
		query = "Delete from centre where id = " + to_string(id) + ";";
		int rc = sqlite3_exec(db, query.c_str(), NULL, NULL, NULL);
		if(rc) cout << "Error encountered on deleting centre" << endl;
		else cout << "Centre deleted successfully" << endl;
	}

	void viewCC(){
		query = "Select * from centre;";
		int rc = sqlite3_exec(db, query.c_str(), callback, NULL, NULL);
		if(rc) cout << "Error encountered on viewing data" << endl;
	}
};

// define global variables
int N = 8;

// main code
int main(){
	// Initiate database
	sqlite3* db;
	int con = sqlite3_open("fruit_mart.db", &db);
	if(con){ cout << "Error connecting database" << endl; return 0;}
	sqlFunc sql(db);
	
	// Interface to get request from user
	char func;
	cout << "Enter 'r' to register, 'd' to delete or 'v' to view : ";
	IN:
	cin >> func;
	cout << endl;

	// Actions on requests made by users
	if(func == 'r') for(int i = 1; i <= N; i++) sql.registerCC();
	else if (func == 'd') for(int i = 1; i <= N; i++) sql.deleteCC(i);
	else if(func == 'v') sql.viewCC();
	else {cout << "Please enter a valid argument : "; goto IN;}
	return 0;
}