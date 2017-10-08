#pragma once
#include "stdafx.h"

/** 
	
 * Reverse digits of an integer.
 * Example1: x = 123, return 321
 * Example2: x = -123, return -321
 * Note:
 * The input is assumed to be a 32-bit signed integer. 
 * Your function should return 0 when the reversed integer overflows.

 */
class Solution2 {
public:
	int reverse(int x) {
		if (x >= INT32_MAX || x <= INT32_MIN) return 0;
		int res[10] = { 0 };
		int pos[10] = { 2,1,4,7,4,8,3,6,4,7 };
		int neg[10] = { -2,-1,-4,-7,-4,-8,-3,-6,-4,-8 };
		int ans = 0;
		int i = 0;
		int flag = 0;

		if (x < 0) flag = 1;
		while (x) {
			res[i++] = x % 10;
			x /= 10;
		}
		// check if overflow
		if (flag == 0 && i == 10) {
			for (int j = 0; j < 10; j++)
			{
				if (res[j] < pos[j]) break;
				else if (res[j] > pos[j]) return 0;
				else if (j == 9) return 0;
			}
		}
		else if (flag == 1 && i == 10)
		{
			for (int j = 0; j < 10; j++)
			{
				if (res[j] > neg[j]) break;
				else if (res[j] < neg[j]) return 0;
				else if (j == 9) return 0;
			}
		}
		for (int j = 0; j < i; j++)
		{
			ans *= 10;
			ans += res[j];
		}
		return ans;
	}
};

/** 

 * Implement atoi to convert a string to an integer.

 * Hint: Carefully consider all possible input cases.
 * If you want a challenge, please do not see below and ask yourself what are the possible input cases.

 * Notes: It is intended for this problem to be specified vaguely (ie, no given input specs). 
 * You are responsible to gather all the input requirements up front.

 * trap: 
 *		input			output
 *		  "+"			  0
 *		"b1245"			  0
 *		"  +12"			  12
 *	 "123456748910"	   2147483647
 *       "+-1"			  0
 */
class Solution3 {
public:
	int myAtoi(string str) {
		string pure = "";
		int flag = 0;	// 1表示负数
		int start = 0, real_start = 0;
		int res = 0;
		int neg_count = 0, count = 0;
		string pos = "2147483647";
		string neg = "2147483648";

		if (str.size() == 1 && (str[0] == '+' || str[0] == '-')) return 0;
		for (int i = 0; i < str.size(); i++)
		{
			if (str[i] >= '0' && str[i] <= '9') {
				start = i;
				break;
			}
			else if (str[i] == '-' || str[i] == '+') {
				if (i < str.size() - 1 && (str[i + 1] < '0' || str[i + 1] > '9')) return 0;
				++count;
				if (str[i] == '-') ++neg_count;
			}
			else if (str[i] == ' ');
			else return 0;
		}
		if (count > 1) return 0;
		flag = (neg_count % 2);
		for (int i = start; i < str.size(); i++)
		{
			if (str[i] > '0' && str[i] <= '9') real_start = 1;
			else if (str[i] < '0' || str[i] > '9') break;
			if (!real_start) continue;
			pure.append(1, str[i]);
		}
		if (pure.size() > 10) {
			if (flag) return INT32_MIN;
			else return INT32_MAX;
		}
		else if (pure.size() == 10) {
			if (flag && pure >= neg) return INT32_MIN;
			else if (!flag && pure >= pos) return INT32_MAX;
		}
		if (pure == "") return 0;
		for (int i = 0; i < pure.size(); i++)
		{
			res *= 10;
			res += (pure[i] - '0');
		}
		if (flag) return -res;
		else return res;
	}
};

/**

 * Determine whether an integer is a palindrome. Do this without extra space.

*/
class Solution4 {
public:
	bool isPalindrome(int x) {
		int num = x;
		if (x < 0) return false;
		else if (x < 10) return true;
		int size = 0;
		while (num) {
			num /= 10;
			++size;
		}
		while (size) {
			if (x < 10) return true;
			if (x < 100 && x % 10 == x / 10) return true;
			int end = x % 10;
			int index = 1;
			for (int i = 0; i < size - 1; i++)
			{
				index *= 10;
			}
			int start = x / index;
			if (end != start) return false;
			size -= 2;
			x %= index;
			x -= end;
			x /= 10;
		}
	}
};