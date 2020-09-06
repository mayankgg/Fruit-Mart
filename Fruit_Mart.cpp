//command to compile : g++ Fruit_Mart.cpp sqlite3.o -I . -o fm

#include<iostream>
#include<bits/stdc++.h>
#include<conio.h>
#include<stdlib.h>
#include<sqlite3.h>
#include"entities.h"
#include"sqlfunc.h"

using namespace std;

int main(){
// Initiate database
	sqlite3* db;
	int con = sqlite3_open("fruit_mart.db", &db);
	if(con){ cout << "Error connecting database" << endl; return 0;}
	sqlFunc sql(db);

// Choose a collection centre for which the application is initialized
	int cid;
I:
	cout << "Centre ID : "; cin >> cid;
	if(!sql.checkCC(cid)){
		cout << "Please enter a valid Centre ID ...\n" << endl;
		goto I;
	}

// Initialize application
	string query1, query2;
S:
	system("cls");
	cout << "*** APPLICATION OF FRUIT MART INDIA PVT LTD ***" << endl;
	cout << "\nEnter 'p' to feed producer data or 'c' to feed consumer data";

// Get first query
Q1:
	cout << "\nYour input : ", cin >> query1;
	if(query1 != "p" && query1 != "c"){
		cout << "Please enter a valid query ... " << endl; 
		goto Q1;
	}
	
	cout << "\nTo register a new account > enter 'r'" << endl;
	cout <<	"To add a new transaction > enter 'u'";

// Get second query
Q2:
	cout << "\nYour input : "; cin >> query2;
	if(query2 != "r" && query2 != "u"){
		cout << "Please enter a valid query ... " << endl;
		goto Q2;
	}

// Actions on request made by users 
	if(query1 == "p"){
		if(query2 == "r"){
			producer p1;
			cout << "\nContact Number : "; cin >> p1.contact;
			cout << "Name : "; cin >> p1.name;
			cout << "DOB : "; cin >> p1.dob;
			sql.registerProd(p1);
		}
		else{
			producer p1;
			centre x1;
			p1.cid = cid;
			x1.id = p1.cid;
P:
			cout << "\nContact Number : "; cin >> p1.contact;
			if(!sql.checkProd(p1.contact)){
				cout << "There is no producer with this contact number ..." << endl; 
				goto P;
			}
P1:		
			cout << "\nFruit Type : "; cin >> p1.fruit;
			transform(p1.fruit.begin(), p1.fruit.end(), p1.fruit.begin(), ::toupper);
			x1.fruit = p1.fruit;
			if(!sql.checkFruit(x1)){
				cout << "This fruit is currently not being sold. Please check the input ..." << endl;
				goto P2;
			}
			cout << "Quantity (in kg) : "; cin >> p1.quantity;
			cout << "Price : "; cin >> p1.price;
			
			sql.getCC(x1);
			x1.quantity += p1.quantity;
			sql.updateCC(x1);
			sql.updateProd(p1);
P2:
			cout << "\nPress ENTER to make another entry or ESC to exit ..." << endl;
			while(1){
				char c = getch();
				if(c == 27) break;
				if(c == 13) goto P1;
			}
		}
	}
	else{
		if(query2 == "r"){
			consumer c1;
			cout << "\nContact Number : "; cin >> c1.contact;
			cout << "Name : "; cin >> c1.name;
			cout << "DOB : "; cin >> c1.dob;
			sql.registerCons(c1);
		}
		else {
			consumer c1;
			centre x1;
			c1.cid = cid;
			x1.id = c1.cid;
C:			
			cout << "\nContact Number : "; cin >> c1.contact;
			if(!sql.checkCons(c1.contact)){
				cout << "There is no consumer with this contact number ..." << endl; 
				goto C;
			}
C1:
			cout << "\nFruit Type : "; cin >> c1.fruit;
			transform(c1.fruit.begin(), c1.fruit.end(), c1.fruit.begin(), ::toupper);
			x1.fruit = c1.fruit;
			if(!sql.checkFruit(x1)){
				cout << "This fruit is currently not being sold. Please check the input ..." << endl;
				goto C2;
			}
			cout << "Quantity (in kg) : "; cin >> c1.quantity;
			
			sql.getCC(x1);
			if(x1.quantity < c1.quantity) cout << "Entered quantity is greater than available. Please check the input!!!" << endl;
			else{
				x1.quantity -= c1.quantity;
				sql.updateCC(x1);
				c1.price = x1.price;
				sql.updateCons(c1);
			}
C2:
			cout << "\nPress ENTER to make another entry or ESC to exit ..." << endl;
			while(1){
				char c = getch();
				if(c == 27) break;
				if(c == 13) goto C1;
			}
		}
	}

// Refresh or Exit
	cout << endl;
	cout << "\nPress ENTER to start fresh or ESC to exit the program ...";
	while(1){
		char c = getch();
		if(c == 27) break;
		if(c == 13) {system("cls"); goto S;}
	}
	return 0;
}