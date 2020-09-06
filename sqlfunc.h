#include<iostream>

using namespace std;

class sqlFunc{
private:
	string query;
	sqlite3* db;
	int rc;
	
	static int callback(void* NotUsed, int argc, char **argv, char **azColName) {
		vector<int>* v = static_cast<vector<int>*>(NotUsed);
		for(int i = 0; i < argc; i++) {
	        v->push_back(atoi(argv[i]));
	    }
	    return 0;
	}

	static int callback3(void* NotUsed, int argc, char **argv, char **azColName) {
	    centre* x1 = static_cast<centre*>(NotUsed);	    
	    x1->quantity = atof(argv[2]);
	    x1->price = atof(argv[3]);
	    return 0;
	}

public:
	
	sqlFunc(sqlite3* con){db = con; return;}

// Centre fucntions	
	bool checkCC(int cid){
		vector<int> v;
		query = "Select count(*) from centre where centre_id = " + to_string(cid) + ";";
		rc = sqlite3_exec(db, query.c_str(), callback, &v, NULL);
		if(rc){
			cout << "Error encountered on fetching centre" << endl;
		}
		else if(v[0] > 0) return true;
		return false;
	}

	void getCC(centre& x1){
		query = "Select * from centre where centre_id = " + to_string(x1.id) + " and fruit_type = '" + x1.fruit + "';";
		rc = sqlite3_exec(db, query.c_str(), callback3, &x1, NULL);
		if(rc) cout << "Error encountered on fetching centrer" << endl;
	}

	void updateCC(centre& x1){
		query = "Update centre set quantity = " + to_string(x1.quantity) + " where centre_id = " + to_string(x1.id) + " and fruit_type = '" + x1.fruit + "';";
		rc = sqlite3_exec(db, query.c_str(), NULL, NULL, NULL);
		if(rc) cout << "Error encountered on updating centre" << endl;
	}

	bool checkFruit(centre &x1){
		vector<int> v;
		query = "Select count(*) from centre where centre_id = " + to_string(x1.id) + " and fruit_type = '" + x1.fruit + "';";
		rc = sqlite3_exec(db, query.c_str(), callback, &v, NULL);
		if(rc){
			cout << "Error encountered on fetching centre" << endl;
		}
		else if(v[0] > 0) return true;
		return false;
	}

// Consumer functions
	void registerCons(consumer& c1){
		query = "Insert into consumer('contact_id', 'name', 'dob') values ('" + c1.contact + "', '" + c1.name + "', '" + c1.dob + "')";
		rc = sqlite3_exec(db, query.c_str(), NULL, NULL, NULL);
		if(rc) cout << "Error encountered on registering consumer" << endl;
	}
	
	bool checkCons(string contact){
		vector<int> v;
		query = "Select count(*) from consumer where contact_id = '" + contact + "';";
		rc = sqlite3_exec(db, query.c_str(), callback, &v, NULL);
		if(rc){
			cout << "Error encountered on fetching centre" << endl;
		}
		else if(v[0] > 0) return true;
		return false;
	}

	void updateCons(consumer& c1){
		query = "Insert into transactions('user_type', 'contact_id', 'centre_id', 'fruit_type', 'quantity', 'price', 'net_change') values('consumer', '" + c1.contact + "', " + to_string(c1.cid) + ", '" + c1.fruit + "', " + to_string(c1.quantity) + ", " + to_string(c1.price) + ", " + to_string(c1.price*c1.quantity) + ");";
		rc = sqlite3_exec(db, query.c_str(), NULL, NULL, NULL);
		if(rc) cout << "Error encountered on updating centre" << endl;
	}

// Producer functions
	void registerProd(producer& p1){
		query = "Insert into producer('contact_id', 'name', 'dob') values ('" + p1.contact + "', '" + p1.name + "', '" + p1.dob + "')";
		rc = sqlite3_exec(db, query.c_str(), NULL, NULL, NULL);
		if(rc) cout << "Error encountered on registering producer" << endl;
	}

	bool checkProd(string contact){
		vector<int> v;
		query = "Select count(*) from producer where contact_id = '" + contact + "';";
		rc = sqlite3_exec(db, query.c_str(), callback, &v, NULL);
		if(rc){
			cout << "Error encountered on fetching centre" << endl;
		}
		else if(v[0] > 0) return true;
		return false;
	}

	void updateProd(producer& p1){
		query = "Insert into transactions('user_type', 'contact_id', 'centre_id', 'fruit_type', 'quantity', 'price', 'net_change') values('producer', '" + p1.contact + "', " + to_string(p1.cid) + ", '" + p1.fruit + "', " + to_string(p1.quantity) + ", " + to_string(p1.price) + ", " + to_string(p1.price*p1.quantity) + ");";
		rc = sqlite3_exec(db, query.c_str(), NULL, NULL, NULL);
		if(rc) cout << "Error encountered on updating centre" << endl;
	}
};