#include<iostream>

using namespace std;

class producer{
public:
	string contact;
	string name;
	string dob;
	string fruit;
	int cid;
	float quantity;
	float price;
	producer(){return;}
};

class consumer{
public:
	string contact;
	string name;
	string dob;
	string fruit;
	int cid;
	float quantity;
	float price;
	consumer(){return;}
};

class centre{
public:
	int id;
	string fruit;
	float quantity = 0;
	float price;
	centre(){return;}	
};