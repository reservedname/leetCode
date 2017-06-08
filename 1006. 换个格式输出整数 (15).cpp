#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;

void coutSerial(int num) {
	for(int i = 1 ; i <= num; ++i) {
		cout<<i;
	}
}

void coutChar(char ch, int n) {
	for(int i = 0; i < n; ++ i) {
		putchar(ch);
	}
}

void coutNum(int n, int site) {
	if(n == 0) return ;
	
	switch(site){
		case 0:
			coutSerial(n);
			break;
		case 1:
			coutChar('S',n);
			break;
		case 2:
			coutChar('B',n);
			break;
		default:
			cout<<"ERROR!"<<endl;
			break;
	}
}



int main(){
	int g = 0,s = 0,b = 0;
	int num = 0;
	cin >> num;
	b = num/100;
	num %= 100;
	s = num/10;
	num %= 10;
	g = num;
	coutNum(b,2);
	coutNum(s,1);
	coutNum(g,0);
	return 0;
}
