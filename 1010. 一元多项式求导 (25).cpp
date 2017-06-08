//19:51-
#include<cstdio>
#include<iostream>
using namespace std;

int main() {
	int x[100] = { 0 };
	int z[100] = { 0 };
	int i = 0, j = 0;

	while (scanf("%d%d", &x[i], &z[i]) == 2)
	{
		++i;
	}

	for (j = 0; j < i; j++)
	{
		if (x[j] == 0 && z[j] == 0) {
			cout << "0 0";
			if (j != i - 1) cout << " ";
		}
		else if (z[j] == 0);
		else
		{
			cout << x[j] * z[j] << " " << z[j] - 1;
			if (j != i - 1) cout << " ";
		}
	}
	return 0;
}
