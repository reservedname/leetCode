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

/**

 * You are given two non-empty linked lists representing two non-negative integers. 
 * The digits are stored in reverse order and each of their nodes contain a single digit.
 * Add the two numbers and return it as a linked list.

 * You may assume the two numbers do not contain any leading zero, except the number 0 itself.
 * Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
 * Output: 7 -> 0 -> 8

 *//*
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

class Solution5 {
public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		if (!l1&&!l2) return nullptr;
		if (!l1) return l2;
		if (!l2) return l1;

		ListNode* l3 = new ListNode(l1->val + l2->val);
		l1 = l1->next;
		l2 = l2->next;
		ListNode* p = l3;
		while (l1&&l2) {
			ListNode* s = new ListNode(l1->val + l2->val);
			p->next = s;
			p = s;
			l1 = l1->next;
			l2 = l2->next;
		}
		if (l1) {
			p->next = l1;
		}
		else if (l2) {
			p->next = l2;
		}
		p = l3;
		while (p) {
			if (p->val >= 10) {
				if (nullptr == p->next) {
					ListNode* s = new ListNode(p->val / 10);
					p->next = s;
				}
				else
				{
					p->next->val += p->val / 10;
				}
				p->val %= 10;
			}
			p = p->next;
		}
		return l3;
	}
};*/

/**

 * Given two non - negative integers num1 and num2 represented as strings, return the product of num1 and num2.
 * Note:
 *   1. The length of both num1 and num2 is < 110.
 *   2. Both num1 and num2 contains only digits 0 - 9.
 *   3. Both num1 and num2 does not contain any leading zero.
 *   4. You must not use any built - in BigInteger library or convert the inputs to integer directly.
 */
class Solution6 {
public:
	string num_multiply(string num, int n) {
		string str = "";
		if (n == 0) return "0";
		else if (n == 1) return num;
		else if (n == 10) {
			str = num;
			str.append("0");
			return str;
		}
		else if (n % 10 == 0) {
			int bei = n / 10;
			str = num_multiply(num, bei);
			int new_num = n / bei;
			while (new_num == 10) {
				str = num_multiply(str, 10);
				new_num /= 10;
			}
			return str;
		}

		int arr[300] = { 0 };
		int length = num.size();

		for (int i = 0; i < length; i++)
		{
			arr[length - i - 1] = num[i] - '0';
		}
		for (int i = 0; i < length; i++)
		{
			arr[i] *= n;
		}
		for (int i = 0; i < length; i++)
		{
			if (arr[i] >= 10) {
				arr[i + 1] += arr[i] / 10;
				arr[i] %= 10;
			}
		}
		if (arr[length] > 0) ++length;
		for (int i = length - 1; i >= 0; i--)
		{
			str.append(1, (arr[i] + '0'));
		}
		return str;
	}

	string sum_string(string a, string b) {
		string c = "";
		int _a[300] = { 0 }, _b[300] = { 0 }, _c[300] = { 0 };
		int ma = a.size(), mb = b.size();
		for (int i = 0; i < ma; i++)
		{
			_a[ma - i - 1] = a[i] - '0';
		}
		for (int i = 0; i < mb; i++)
		{
			_b[mb - i - 1] = b[i] - '0';
		}
		int max = ma > mb ? ma : mb;
		for (int i = 0; i < max; i++)
		{
			_c[i] = _a[i] + _b[i];
		}
		for (int i = 0; i < max; i++)
		{
			if (_c[i] >= 10) {
				_c[i + 1] += _c[i] / 10;
				_c[i] %= 10;
			}
		}
		if (_c[max] > 0) ++max;
		for (int i = max - 1; i >= 0; i--)
		{
			c.append(1, (_c[i] + '0'));
		}

		return c;
	}

	string multiply(string num1, string num2) {
		string a = "", b = "", c = "";
		int len1 = num1.size(), len2 = num2.size();
		if (len2 == 1) return num_multiply(num1, num2[0] - '0');
		int i = 0;
		a = num_multiply(num1, num2[i] - '0');
		for (i = 1; i < len2; i++)
		{
			a.append("0");
			b = num_multiply(num1, num2[i] - '0');
			c = sum_string(a, b);
			a = c;
		}
		if (c[0] == '0') return "0";
		return c;
	}
};

/**
 * 
 * Given a roman numeral, convert it to an integer.
 * Input is guaranteed to be within the range from 1 to 3999.
 *
 */
class Solution7 {
	//TODO:罗马数字是从前向后遍历的，我这里理解反了，算法应该是没什么大问题的，这里知道方法就可以了，有空再改回来
public:
	int compareNum(char a, char b) {
		if (a == b)return 0;
		char arr[7] = { 'I','V','X','L','C','D','M' };	// 1 5 10 50 100 500 1000
		for (int i = 0; i < 7; i++)
		{
			if (arr[i] == a) return -1;
			else if (arr[i] == b) return 1;
		}
	}

	int getNum(char ch) {
		switch (ch)
		{
		case 'I':return 1;
		case 'V':return 5;
		case 'X':return 10;
		case 'L':return 50;
		case 'C':return 100;
		case 'D':return 500;
		case 'M':return 1000;
		default:
			break;
		}
	}

	int romanToInt(string s) {
		int n = s.size();
		if (n == 0) return 0;
		char ch = s[n - 1], toGet;
		if (n == 1) return getNum(ch);
		int res = 0;
		int num = 0;
		int flag_add = 0, flag_jian = 0;

		for (auto i = 0; i < n; i += 2)
		{
			toGet = s[i];
			if (i == 0) {
				num += getNum(toGet);
				break;
			}
			ch = s[i + 1];
			res = compareNum(toGet, ch);
			if (flag_add && res == 1) {
				num += getNum(ch);
				--i;
			}
			else if (flag_jian && res == -1 && (toGet != 'I' && toGet == 'X' && toGet == 'C')) {
				num += getNum(ch);
				--i;
			}
			else if (res == 1) {
				num += (getNum(toGet) + getNum(ch));
				flag_add = 1;
			}
			else if (res == 0) {
				num += (2 * getNum(toGet));
			}
			else if (res == -1) {
				if (toGet == 'I' || toGet == 'X' || toGet == 'C') {
					num += (getNum(ch) - getNum(toGet));
					flag_jian = 1;
				}
				else {
					num += getNum(ch);
					--i;
				}
			}
		}
		return num;
	}
};

/**
 *
 * Given a sorted array, remove the duplicates in place such that each element appear only once
 * and return the new length.
 * Do not allocate extra space for another array, you must do this in place with constant memory.
 * For example,
 * Given input array nums = [1,1,2],
 * Your function should return length = 2, with the first two elements of nums being 1 and 2 respectively. 
 * It doesn't matter what you leave beyond the new length.
 *
 */
class Solution8 {
public:
	int removeDuplicates(vector<int>& nums) {
		if (nums.size() == 0) return 0;
		int same = nums[0];
		int length = 1;
		int t = 0;
		for (int i = 1; i < nums.size(); i++)
		{
			int j = 0;
			if (nums[i] <= nums[i - 1]) {
				for (j = i; j < nums.size(); j++) {
					if (nums[j] > nums[i - 1]) break;
					if (j == nums.size() - 1) return length;
				}
				nums[i] = nums[j];
			}
			++length;
		}
		return length;
	}
};

/**
 *
 * Given a string containing just the characters '(', ')', '{', '}', '[' and ']', 
 * determine if the input string is valid.
 * The brackets must close in the correct order, 
 * "()" and "()[]{}" are all valid but "(]" and "([)]" are not.
 *
 */
class Solution9 {
public:
	bool isValid(string s) {
		vector<char> stk;
		for (int i = 0; i < s.size(); i++)
		{
			char end_char;
			if (stk.size() == 0) end_char= 'n';
			else end_char = *(stk.end() - 1);
			switch (s[i])
			{
			case '(':
			case '[':
			case '{':
				stk.push_back(s[i]);
				break;
			case ')':
				if (end_char == 'n' || end_char != '(') return false; stk.pop_back(); break;
			case ']':
				if (end_char == 'n' || end_char != '[') return false; stk.pop_back(); break;
			case '}':
				if (end_char == 'n' || end_char != '{') return false; stk.pop_back(); break;
			default:
				break;
			}
		}
		if (stk.size() == 0) return true;
		return false;
	}
};

/**
 *
 * Merge two sorted linked lists and return it as a new list.
 * The new list should be made by splicing together the nodes of the first two lists.
 *
 *//*
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

class Solution10 {
public:
	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
		ListNode *p = l1, *q = l2;
		ListNode *a = nullptr, *t, *s;
		if (!p) {
			a = q;
			return a;
		}
		else if (!q) {
			a = p;
			return a;
		}
		if (p->val < q->val) {
			a = new ListNode(p->val);
			p = p->next;
		}
		else
		{
			a = new ListNode(q->val);
			q = q->next;
		}
		t = a;
		while (p&&q) {
			if (p->val < q->val) {
				s = new ListNode(p->val);
				p = p->next;
			}
			else
			{
				s = new ListNode(q->val);
				q = q->next;
			}
			t->next = s;
			t = s;
		}
		if (!q) {
			t->next = p;
		}
		if (!p) {
			t->next = q;
		}
		return a;
	}
};*/

/**
 *
 * Given a sorted array and a target value, return the index if the target is found.
 * If not, return the index where it would be if it were inserted in order.
 * You may assume no duplicates in the array.
 *
 * Here are few examples.
 * [1,3,5,6], 5 → 2
 * [1,3,5,6], 2 → 1
 * [1,3,5,6], 7 → 4
 * [1,3,5,6], 0 → 0
 *
 */
class Solution11 {
public:
	int searchInsert(vector<int>& nums, int target) {
		int site = 0;
		if (target > *(nums.end() - 1)) {
			return nums.size();
		}
		else if (target < *(nums.begin())) {
			return 0;
		}
		for (auto i = nums.begin(); i != nums.end(); i++)
		{
			if (target <= *i && target > *(i - 1)) {
				return site;
			}
			++site;
		}
	}
};

/**
 *
 * You are a product manager and currently leading a team to develop a new product.
 * Unfortunately, the latest version of your product fails the quality check.
 * Since each version is developed based on the previous version,
 * all the versions after a bad version are also bad.
 * Suppose you have n versions [1, 2, ..., n] and you want to find out the first bad one,
 * which causes all the following ones to be bad.
 * You are given an API bool isBadVersion(version) 
 * which will return whether version is bad. Implement a function to find the first bad version. 
 * You should minimize the number of calls to the API.
 *
 */
 // Forward declaration of isBadVersion API.
bool isBadVersion(int version) {
	if (version >= 1702766719) return true;
	return false;
}

class Solution12 {
public:
	int firstBadVersion(int n) {
		int start = 1, end = n;
		int sign = n / 2;
		if (n == 1) return 1;
		while (sign != 0 && sign != n) {
			sign = start / 2 + end / 2;	// "(start + end) / 2"会导致越界
			if (isBadVersion(sign)) {
				if (!isBadVersion(sign - 1)) return sign;
				else end = sign - 1;
			}
			else {
				if (isBadVersion(sign + 1)) return sign + 1;
				else start = sign + 1;
			}
		}
	}
};

/***
 *
 * Given an array and a value, remove all instances of that value in place and return the new length.
 * Do not allocate extra space for another array, you must do this in place with constant memory.
 * The order of elements can be changed.It doesn't matter what you leave beyond the new length.
 * Example:
 * Given input array nums = [3, 2, 2, 3], val = 3
 * Your function should return length = 2, with the first two elements of nums being 2.
 *
 */
class Solution13 {
public:
	int removeElement(vector<int>& nums, int val) {
		if (nums.size() == 0) return 0;
		int endSite = nums.size() - 1;
		int i = 0, j = -1;
		while (endSite >= 0 && nums[endSite] == val) --endSite;
		if (endSite == -1) return 0;
		int t = 0;
		int len = endSite;

		for (i = 0; i <= endSite; i++)
		{
			if (nums[i] == val) {
				j = i + 1;
				for (int k = j; k <= endSite; k++)
				{
					if (nums[k] != val) {
						t = nums[i];
						nums[i] = nums[k];
						nums[k] = t;
						len = i;
						break;
					}
				}
			}
		}
		return len + 1;
	}
};