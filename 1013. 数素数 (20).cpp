#include<cstdio>
#include<cmath>
#include<iostream>
using namespace std;

int isPrime(int a) {
	int i,j;
	int n=sqrt(a);
	
	if(a==0||a==1) return 0;
	if(a==2) return 1;
	for(i=2;i<=n;++i){
		if(a%i==0) return 0;
	}
	return 1;
}

int main(){
	int count=0;
	int j=0;
	int i=2;
	int m,n;
	cin>>m>>n;
	
	while(count<n){
		if(isPrime(i)){
			++count;
			if(count>=m){
				cout<<i;
				++j;
				if(j%10==0) cout<<endl;
				else if(count == n);
				else cout<<"¿Õ¸ñ";
			}
		}
		++i;
	}
	return 0;
}
/*
#define MAX 10010
int a[MAX] = {0};

void getPrime() {
	a[2] = 1;
	int i = 0,j = 0;
	
	for(i = 2; i < MAX; ++i) {
		if(i % 2 == 1) {
			a[i] = 1;
		}
	}
	
	for(i = 2; i < sqrt(MAX); ++i) {
		if(a[i] == 1) {
			for(j = i + i; j < MAX; j += i) {
				a[j] = 0;
			}
		}
	}
}

int main() {
	int m,n;
	int i = 0;
	int count;
	int j = 0;
	
	getPrime();
	cin >> m >> n;
	while(count <= n) {
		if(a[i] == 1) {
			
			if(count >= m) {
				++j;
				cout << i;
				j % 10 == 0 ? cout << endl : cout << " ";
			}
			++count;
		}
		++i;
	}
	return 0;
}*/
