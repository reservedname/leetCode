#include<cstdio>
#include<cmath>
#include<iostream>
using namespace std;

int isGcd(int num){
	int sqt = 0;
	int i = 2;
	if(num == 0) return 0;
	if(num == 1 || num == 2 || num == 3){
		return 1;
	}
	
	sqt = (int)(sqrt((double)num));
	
	for(; i <= sqt; ++ i) {
		if(num % i == 0){
			return 0;
		}
	}
	return 1;
}

int main(){
	int prior = 1;
	int n = 0;
	int count = 0;
	
	cin >> n;
	for(int i = 2; i <= n; ++ i) {
		if(isGcd(i)) {
			if(i - prior == 2)	++count;
			prior = i;
		}
	}
	cout<<count;
	return 0;
}
