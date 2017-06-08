#include<cstdio>
#include<iostream>

int count = 0;

void loop(int a){
	if(a==1) return;
	++count;
	
	if(a%2==0){
		a/=2;
		loop(a);
	} else {
		a=(3*a+1)/2;
		loop(a);
	}
}

int main(){
	int a = 0;
	scanf("%d",&a);
	loop(a);
	printf("%d\n", count);
}
