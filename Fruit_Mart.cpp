#include<cstdio>
#include<iostream>
#include<bits/stdc++.h>

using namespace std;

struct fruits{
	public:
		float apple, orange, banana, mango, guava;
		fruits(){apple = orange = banana = mango = guava = 0; return;}
};

class producer{
	public:
		int id;
		int cid;
		fruits f;
		producer(int x, int y){id = x; cid = y; return;}
};

class cc{ // collection centre
	public:
		int id;
		fruits f;
		cc(int x){id = x; return;}
};

class consumer{
	public:
		int id;
		int cid;
		fruits f;
		consumer(int x, int y){id = x;  cid = y; return;}
};

int main(){
	int v;
	cout << "Please share a value" << endl;
	cin >> v;
	cout << "You shared the value " << v << endl;
	while(1){
		char c = getchar();
		if(c == 'x') break;
	}
	return 0;
}