//19:00-19:32
//方向考虑错了,我的锅我的锅QAQ
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;

void swap(int &a, int &b)
{
	int t = 0;
	t = a;
	a = b;
	b = t;
}

int main() {
	int a[110] = { 0 };
	int count = 0;
	int n = 0;
	int end = 0;

	cin >> n;
	cin >> count;
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	

	for (int i = 0; i < count; i++)
	{
		end = a[n - 1];
		for (int j = n - 1; j > 0; j--)
		{
			a[j] = a[j - 1];
		}
		a[0] = end;
	}

	for (int i = 0; i < n; i++)
	{
		cout << a[i];
		if (i != n - 1)
		{
			cout << " ";
		}
	}
	return 0;
}
