#include<cstdio>
#include<cstring>

typedef struct{
	char name[15];
	char id[15];
	int score; 
}stu;

void showStu(stu a){
	printf("%s %s\n",a.name,a.id);
}

int main(){
	int n = 0;
	stu a[10000];
	stu max,min;
	scanf("%d",&n);
	for(int i=0;i<n;++i){
		scanf("%s %s %d",a[i].name,a[i].id,&a[i].score);
	}
	if(n == 0){
		showStu(a[0]);
		return 0;
	}
	min = a[0];
	max = a[0];
	
	for(int i=1;i<n;++i){
		if(a[i].score>max.score){
			max = a[i];
		}
		if(a[i].score<min.score){
			min = a[i];
		}
	}
	showStu(max);
	showStu(min);
	return 0;
}
