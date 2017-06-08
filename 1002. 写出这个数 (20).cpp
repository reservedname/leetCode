/*
读入一个自然数n，计算其各位数字之和，用汉语拼音写出和的每一位数字。 

输入格式：每个测试输入包含1个测试用例，即给出自然数n的值。这里保证n小于10100。

输出格式：在一行内输出n的各位数字之和的每一位，拼音数字间有1 空格，但一行中最后一个拼音数字后没有空格。 
输入样例：1234567890987654321123456789

输出样例：yi san wu
*/
//≈30 min
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;

int cacuSum(char s[]){
	int sum=0;
	
	for(int i=0;i<strlen(s);++i){
		sum+=(s[i]-'0');
	}
	return sum;
}

int cacuSize(int a){
	int n = 0;
	
	while(a){
		a/=10;
		++n;
	}
	return n;
}

void printC(int a){
	switch(a){
		case 0:
			printf("ling");
			break;
		case 1:
			printf("yi");
			break;
		case 2:
			printf("er");
			break;
		case 3:
			printf("san");
			break;
		case 4:
			printf("si");
			break;
		case 5:
			printf("wu");
			break;
		case 6:
			printf("liu");
			break;
		case 7:
			printf("qi");
			break;
		case 8:
			printf("ba");
			break;
		case 9:
			printf("jiu");
			break;
	}
}

int pows(int n){
	int ans = 1;
	
	if(n == 1) return 10;
	for(int i=1;i<n;++i){
		ans*=10;
	}
	return ans;
}

int main(){
	char s[110];
	int sum = 0;
	int n = 0;
	int size = 0;
	int poto = 0;
	scanf("%s",s);
	sum = cacuSum(s);
	size = cacuSize(sum);
	
	while(size){
		poto=pows(size);
		--size;
		if(size!=0){
			n=sum/poto;
			sum%=poto;
		}else{
			n=sum;
		}
		printC(n);	
		if(size!=0) putchar(' ');
	}
}
