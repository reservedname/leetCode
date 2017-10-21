// easy.cpp: 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include "solution.h"

int main()
{
	Solution a;
	vector<int> vec = { 2,1 };
	cout << a.findShortestSubArray(vec) << endl;
    return 0;
}

