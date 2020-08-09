//command to compile : g++ Fruit_Mart.cpp sqlite3.io -I . -o fm

#include<cstdio>
#include<conio.h>
#include<bits/stdc++.h>
#include<stdlib.h>
#include<sqlite3.h>

using namespace std;

struct fruits{
	float apple, orange, banana, mango, guava;
	fruits(){apple = orange = banana = mango = guava = 0; return;}
	void operator+= (const fruits& f){
		apple += f.apple;
		orange += f.orange;
		banana += f.banana;
		mango += f.mango;
		guava += f.guava;
	}
	void operator-= (const fruits& f){
		apple -= f.apple;
		orange -= f.orange;
		banana -= f.banana;
		mango -= f.mango;
		guava -= f.guava;
	}
	bool operator>= (const fruits& f){
		if(apple >= f.apple && orange >= f.orange && banana >= f.banana && mango >= f.mango && guava >= f.guava) return true;
		return false; 
	}
};

class producer{
	public:
		int id;
		int cid = -1;
		fruits f;
		producer(int x){id = x; return;}
		producer(){return;}
};

class cc{ // collection centre
	public:
		int id;
		fruits f;
		cc(int x){id = x; return;}
		cc(){return;}
};

class consumer{
	public:
		int id;
		int cid = -1;
		fruits f;
		consumer(int x){id = x; return;}
		consumer(){return;}
};

istream& operator>> (istream& is, fruits& f){
	is >> f.apple >> f.orange >> f.banana >> f.mango >> f.guava;
	return is;
}

ostream& operator<< (ostream& os, const producer& p){
	os << "User ID : " << p.id << endl;
	os << "Centre ID : " << p.cid << endl;
	os << "apple : " << p.f.apple << endl;
	os << "orange : " << p.f.orange << endl;
	os << "banana : " << p.f.banana << endl;
	os << "mango : " << p.f.mango << endl;
	os << "guava : " << p.f.guava << endl;
	return os;
}

ostream& operator<< (ostream& os, const consumer& c){
	os << "User ID : " << c.id << endl;
	os << "Centre ID : " << c.cid << endl;
	os << "apple : " << c.f.apple << endl;
	os << "orange : " << c.f.orange << endl;
	os << "banana : " << c.f.banana << endl;
	os << "mango : " << c.f.mango << endl;
	os << "guava : " << c.f.guava << endl;
	return os;
}

class sqlFunc{
private:
	string query;
	sqlite3* db;
	int rc;
	static int callback1(void* NotUsed, int argc, char **argv, char **azColName) {
		consumer* c1 = static_cast<consumer*>(NotUsed);
	    c1->id = atoi(argv[0]);
	    c1->cid = atoi(argv[1]);
	    c1->f.apple = atof(argv[2]);
	    c1->f.orange = atof(argv[3]);
	    c1->f.guava = atof(argv[4]);
	    c1->f.mango = atof(argv[5]);
	    c1->f.banana = atof(argv[6]);
	    return 0;
	}
	static int callback2(void* NotUsed, int argc, char **argv, char **azColName) {
	    producer* p1 = static_cast<producer*>(NotUsed);
	    p1->id = atoi(argv[0]);
	    p1->cid = atoi(argv[1]);
	    p1->f.apple = atof(argv[2]);
	    p1->f.orange = atof(argv[3]);
	    p1->f.guava = atof(argv[4]);
	    p1->f.mango = atof(argv[5]);
	    p1->f.banana = atof(argv[6]);
	    return 0;
	}
	static int callback3(void* NotUsed, int argc, char **argv, char **azColName) {
	    cc* x1 = static_cast<cc*>(NotUsed);
	    x1->id = atoi(argv[0]);
	    x1->f.apple = atof(argv[1]);
	    x1->f.orange = atof(argv[2]);
	    x1->f.guava = atof(argv[3]);
	    x1->f.mango = atof(argv[4]);
	    x1->f.banana = atof(argv[5]);
	    return 0;
	}

public:
	
	sqlFunc(sqlite3* con){db = con; return;}
	
	void registerCons(int cid){
		query = "Insert into consumer('cid', 'apple', 'orange', 'banana', 'mango', 'guava') values (" + to_string(cid) + ", 0.0, 0.0, 0.0, 0.0, 0.0)";
		rc = sqlite3_exec(db, query.c_str(), NULL, NULL, NULL);
		if(rc) cout << "Error on registering consumer" << endl;
		else cout << "Consumer registered successfully with User ID : " << sqlite3_last_insert_rowid(db) << endl;
	}
	
	void registerProd(int cid){
		query = "Insert into producer('cid', 'apple', 'orange', 'banana', 'mango', 'guava') values (" + to_string(cid) + ", 0.0, 0.0, 0.0, 0.0, 0.0)";
		rc = sqlite3_exec(db, query.c_str(), NULL, NULL, NULL);
		if(rc) cout << "Error on registering producer" << endl;
		else cout << "Producer registered successfully with User ID : " << sqlite3_last_insert_rowid(db) << endl;
	}

	void getCons(consumer& c1){
		query = "Select * from consumer where id = " + to_string(c1.id) + ";";
		rc = sqlite3_exec(db, query.c_str(), callback1, &c1, NULL);
		if(rc) cout << "Error encountered on fetching consumer" << endl;
	}

	void getProd(producer& p1){
		query = "Select * from producer where id = " + to_string(p1.id) + ";";
		rc = sqlite3_exec(db, query.c_str(), callback2, &p1, NULL);
		if(rc) cout << "Error encountered on fetching producer" << endl;
	}

	void getCC(cc& x1){
		query = "Select * from centre where id = " + to_string(x1.id) + ";";
		rc = sqlite3_exec(db, query.c_str(), callback3, &x1, NULL);
		if(rc) cout << "Error encountered on fetching centrer" << endl;
	}

	void updateCC(cc& x1){
		query = "Update centre set apple = " + to_string(x1.f.apple) + ", orange = " + to_string(x1.f.orange) + ", banana = " + to_string(x1.f.banana)
				+ ", mango = " + to_string(x1.f.mango) + ", guava = " + to_string(x1.f.guava) + " where id = " + to_string(x1.id) + ";";
		rc = sqlite3_exec(db, query.c_str(), NULL, NULL, NULL);
		if(rc) cout << "Error encountered on updating centre" << endl;
	}

	void updateCons(consumer& x1){
		query = "Update consumer set apple = " + to_string(x1.f.apple) + ", orange = " + to_string(x1.f.orange) + ", banana = " + to_string(x1.f.banana)
				+ ", mango = " + to_string(x1.f.mango) + ", guava = " + to_string(x1.f.guava) + " where id = " + to_string(x1.id) + ";";
		rc = sqlite3_exec(db, query.c_str(), NULL, NULL, NULL);
		if(rc) cout << "Error encountered on updating consumer" << endl;
		else cout << "Consumer updated successfully" << endl;
	}

	void updateProd(producer& x1){
		query = "Update producer set apple = " + to_string(x1.f.apple) + ", orange = " + to_string(x1.f.orange) + ", banana = " + to_string(x1.f.banana)
				+ ", mango = " + to_string(x1.f.mango) + ", guava = " + to_string(x1.f.guava) + " where id = " + to_string(x1.id) + ";";
		rc = sqlite3_exec(db, query.c_str(), NULL, NULL, NULL);
		if(rc) cout << "Error encountered on updating producer" << endl;
		else cout << "Producer updated successfully" << endl;
	}

	void deleteCons(int id){
		query = "Delete from consumer where id = " + to_string(id) + ";";
		rc = sqlite3_exec(db, query.c_str(), NULL, NULL, NULL);
		if(rc) cout << "Error encountered on deleting consumer" << endl;
		else cout << "Consumer deleted successfully" << endl;
	}

	void deleteProd(int id){
		query = "Delete from producer where id = " + to_string(id) + ";";
		rc = sqlite3_exec(db, query.c_str(), NULL, NULL, NULL);
		if(rc) cout << "Error encountered on deleting producer" << endl;
		else cout << "Producer deleted successfully" << endl;
	}
};

int N = 8;

int main(){
	// Initiate database
	sqlite3* db;
	int con = sqlite3_open("fruit_mart.db", &db);
	if(con){ cout << "Error connecting database" << endl; return 0;}
	sqlFunc sql(db);

	// Interface to get request from users
	string query1, query2;
	S:
	cout << "*** APPLICATION OF FRUIT MART INDIA PVT LTD ***\n" << endl;
	cout << "Enter 'p' to access producer data or 'c' to access consumer data : ";

	Q1:
	cin >> query1;
	cout << endl;
	if(query1 == "p"){
		cout << "To register a new producer > enter 'r'" << endl;
		cout <<	"To view total produce > enter 'v'" << endl;
		cout <<	"To update the total produce > enter 'u'" << endl;
		cout <<	"To delete the account > enter 'd'" << endl;
	}
	else if(query1 == "c"){
		cout << "To register a new consumer > enter 'r'" << endl;
		cout << "To view total consumption > enter 'v'" << endl;
		cout << "To update total consumption > enter 'u'" << endl;
		cout << "To delete the account > enter 'd'" << endl;
	}
	else{
		cout << "Please enter a valid query : ";
		goto Q1;
	}
	
	cout << "Your input : ";

	Q2:
	cin >> query2;
	cout << endl;
	if(query2 != "r" && query2 != "v" && query2 != "u" && query2 != "d"){
		cout << "Please enter a valid query : ";
		goto Q2;
	}

	// Actions on request made by users 
	if(query1 == "p"){
		if(query2 == "r"){
			int cid;
			cout << "Please enter the Centre ID : "; cin >> cid; cout << endl;
			sql.registerProd(cid);
		}
		else if(query2 == "v"){
			producer p1;
			cout << "Please enter the User ID : "; cin >> p1.id; cout << endl;
			sql.getProd(p1);
			if(p1.cid == -1) cout << "There is no producer with ID " << to_string(p1.id) << endl;
			else cout << p1 << endl;
		}
		else if(query2 == "u"){
			producer p1;
			cout << "Please enter the User ID : "; cin >> p1.id; cout << endl;
			sql.getProd(p1);
			if(p1.cid == -1) cout << "There is no producer with ID " << to_string(p1.id) << endl;
			else{
				fruits f;
				cout << "\nPlease enter the production details (numeric) in the following sequence ..." << endl;
				cout << "Apple Orange Banana Mango Guava : "; cin >> f; cout << endl;
				p1.f += f;
				sql.updateProd(p1);
				cc x1(p1.cid);
				sql.getCC(x1);
				x1.f += f;
				sql.updateCC(x1);
			}
		}
		else{
			producer p1;
			cout << "Please enter the User ID : "; cin >> p1.id; cout << endl;
			sql.getProd(p1);
			if(p1.cid == -1) cout << "There is no producer with ID " << to_string(p1.id) << endl;
			else sql.deleteProd(p1.id);	
		}
	}
	else{
		if(query2 == "r"){
			int cid;
			cout << "Please enter the Centre ID : "; cin >> cid; cout << endl;
			sql.registerCons(cid);
		}
		else if(query2 == "v"){
			consumer c1;
			cout << "Please enter the User ID : "; cin >> c1.id; cout << endl;
			sql.getCons(c1);
			if(c1.cid == -1) cout << "There is no consumer with ID " << to_string(c1.id) << endl;
			else cout << c1 << endl;
		}
		else if(query2 == "u"){
			consumer c1;
			cout << "Please enter the User ID : "; cin >> c1.id; cout << endl;
			sql.getCons(c1);
			if(c1.cid == -1) cout << "There is no consumer with ID " << to_string(c1.id) << endl;
			else{
				fruits f;
				cout << "\nPlease enter the consumption details (numeric) in the following sequence ..." << endl;
				cout << "Apple Orange Banana Mango Guava : "; cin >> f; cout << endl;
				cc x1(c1.cid);
				sql.getCC(x1);
				if(x1.f >= f){
					c1.f += f; 
					sql.updateCons(c1);
					x1.f -= f;
					sql.updateCC(x1);
				}
				else{
					cout << endl;
					cout << "Unable to update due to insufficent stock" << endl;
				}
			}
		}
		else{
			consumer c1;
			cout << "Please enter the User ID : "; cin >> c1.id; cout << endl;
			sql.getCons(c1);
			if(c1.cid == -1) cout << "There is no consumer with ID " << to_string(c1.id) << endl;
			else sql.deleteCons(c1.id);	
		}
	}

// Refresh or Exit
	cout << endl;
	cout << "Press ENTER to start fresh or ESC to exit the program ...";
	while(1){
		char c = getch();
		if(c == 27) break;
		if(c == 13) {system("cls"); goto S;}
	}
	return 0;
}