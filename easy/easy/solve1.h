#pragma once
#include "stdafx.h"

class Solution1 {
public:
	vector<int> twoSum(vector<int>& numbers, int target) {

		int begin = 0, end = numbers.size() - 1;
		vector<int> res = { 0,0 };
		int sum = numbers[begin] + numbers[end];
		while (sum != target) {
			sum = numbers[begin] + numbers[end];
			if (sum > target) {
				if (numbers[begin + 1] <= numbers[begin]) {
					++begin;
					continue;
				}
				else if (numbers[end - 1] <= numbers[end]) {
					--end;
					continue;
				}
			}
			else if (sum < target) {
				if (numbers[begin + 1] >= numbers[begin]) {
					++begin;
					continue;
				}
				else if (numbers[end - 1] >= numbers[end]) {
					--end;
					continue;
				}
			}
			else break;
		}
		if (begin == end) {
			if (begin != 0 && numbers[begin] == numbers[begin - 1]) --begin;
			else if (numbers[begin] == numbers[begin + 1]) ++begin;
			else if (numbers[end] == numbers[end - 1]) --end;
			else if (numbers[end] == numbers[end + 1]) ++end;
		}
		res[0] = begin + 1;
		res[1] = end + 1;
		return res;
		/*		int begin = 0, end = nums.size();
		vector<int> res = { 0,0 };
		int sum = 0;
		for (; begin < end - 1; ++begin) {
		for (int i = begin + 1; i < end; i++)
		{
		sum = nums[begin] + nums[i];
		if (sum == target) {
		res[0] = begin;
		res[1] = i;
		return res;
		}
		}
		}*/
	}
};

/**
 *
 * Reverse digits of an integer.
 * Example1: x = 123, return 321
 * Example2: x = -123, return -321
 * Note:
 * The input is assumed to be a 32-bit signed integer.
 * Your function should return 0 when the reversed integer overflows.
 *
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
 *
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
 *
 * Determine whether an integer is a palindrome. Do this without extra space.
 *
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
 *
 * You are given two non-empty linked lists representing two non-negative integers.
 * The digits are stored in reverse order and each of their nodes contain a single digit.
 * Add the two numbers and return it as a linked list.
 *
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
 *
 * Given two non - negative integers num1 and num2 represented as strings, return the product of num1 and num2.
 * Note:
 *   1. The length of both num1 and num2 is < 110.
 *   2. Both num1 and num2 contains only digits 0 - 9.
 *   3. Both num1 and num2 does not contain any leading zero.
 *   4. You must not use any built - in BigInteger library or convert the inputs to integer directly.
 *
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
			if (stk.size() == 0) end_char = 'n';
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
class Solution12 {
public:
	// Forward declaration of isBadVersion API.
	bool isBadVersion(int version) {
		if (version >= 1702766719) return true;
		return false;
	}

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

/**
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

/**
 *
 * Given a string s, find the longest palindromic substring in s.
 * You may assume that the maximum length of s is 1000.
 *
 * Example:
 * Input: "babad"
 * Output: "bab"
 * Note: "aba" is also a valid answer.
 * Example:
 * Input: "cbbd"
 * Output: "bb"
 *
 */
class Solution14 {
public:
	/*	
	bool valid(string main, int begin, int end) {
		while (begin < end) {
			if (main[begin] != main[end]) {
				return false;
			}
			++begin;
			--end;
		}
		return true;
	}
	*/

	string longestPalindrome(string s) {
		// 下面是马拉车算法
		/*		string t = "$#";
		for (int i = 0; i < s.size(); ++i) {
		t += s[i];
		t += '#';
		}
		int p[t.size()] = { 0 }, id = 0, mx = 0, resId = 0, resMx = 0;
		for (int i = 0; i < t.size(); ++i) {
		p[i] = mx > i ? min(p[2 * id - i], mx - i) : 1;
		while (t[i + p[i]] == t[i - p[i]]) ++p[i];
		if (mx < i + p[i]) {
		mx = i + p[i];
		id = i;
		}
		if (resMx < p[i]) {
		resMx = p[i];
		resId = i;
		}
		}
		return s.substr((resId - resMx) / 2, resMx - 1);*/
		/*
		// 下面这个算法不好，时间复杂度太高，基本相当于枚举
		int begin = 0, end = s.size() - 1;
		int len = s.size();
		int maxLength = 0;
		int i;
		int max_begin = 0, max_end = 0;
		//int begin_valid = begin, end_valid = end;

		if (s.size() == 0) return "";
		if (s.size() == 1) return s;
		if (s.size() == 2) {
		if (s[0] == s[1]) return s;
		else return s.substr(0, 1);
		}

		for (i = 1; i < len; i++)
		{
		if (s[i] != s[0]) break;
		}
		if (i == len) return s;

		while (begin < end) {
		while (end != begin) {
		if (valid(s, begin, end)) {
		if (end - begin > maxLength) {
		maxLength = end - begin;
		max_begin = begin;
		max_end = end;
		}
		end = begin;
		break;
		}
		--end;
		}
		++begin;
		end += 2;
		while (end != len) {
		if (valid(s, begin, end)) {
		if (end - begin > maxLength) {
		maxLength = end - begin;
		max_begin = begin;
		max_end = end;
		}
		}
		++end;
		}
		--end;
		++begin;
		}
		return s.substr(max_begin, maxLength + 1);*/
	}
};

/**
 *
 * The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows
 * like this: (you may want to display this pattern in a fixed font for better legibility)
 * P   A   H   N
 * A P L S I I G
 * Y   I   R
 * And then read line by line: "PAHNAPLSIIGYIR"
 * Write the code that will take a string and make this conversion given a number of rows:
 * string convert(string text, int nRows);
 * convert("PAYPALISHIRING", 3) should return "PAHNAPLSIIGYIR".
 *
 */
class Solution15 {
public:
	string convert(string s, int numRows) {
		string res = "";
		int len = s.size();
		int i = 0;
		vector<string> ans;
		for (int j = 0; j < numRows; j++)
		{
			ans.push_back("");
		}

		int n = 2 * numRows - 2;
		int key = 0, site = 0;
		for (i = 0; i < len; i++)
		{
			key = i % n;
			site = key >= numRows ? n - key : key;
			ans[site] += s[i];
		}
		for (i = 0; i < numRows; i++)
		{
			res += ans[i];
		}
		return res;
	}
};

/**
 *
 * Implement strStr().
 * Returns the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.
 *
 */
class Solution16 {
	// 单纯的KMP算法，这里我直接用我上面写过的那个
public:
	vector<int> getNextArray(string str) {
		vector<int> next(str.size() + 1);
		int i = 0, j = -1;
		next[0] = -1;
		while (i < str.size()) {
			if (j == -1 || str[i] == str[j]) {
				next[++i] = ++j;	// 之前j已经在上一个最大公共缀处，所以当str[i] == str[j]时最大公共缀长度+1
			}
			else {
				j = next[j];	// 跳转到最大公共缀处
			}
		}
		return next;
	}

	int strStr(string main, string pattern) {
		vector<int> next = getNextArray(pattern);
		int i = 0, j = 0;
		int mainLength = main.size(), patternLength = pattern.size();

		while (i < mainLength && j < patternLength) {
			if (j == -1 || main[i] == pattern[j]) {	// 假如第一个位置就不匹配或当前位置匹配
				i++; j++;
			}
			else {
				j = next[j];
			}
		}
		if (j == pattern.size()) return i - patternLength;	// 由于匹配完模式串(子串)而跳出才返回真
		return -1;
	}
};

/**
 *
 * Find the contiguous subarray within an array (containing at least one number) which has the largest sum.
 * For example, given the array [-2,1,-3,4,-1,2,1,-5,4],
 * the contiguous subarray [4,-1,2,1] has the largest sum = 6.
 *
 */
class Solution17 {
	// Kadane算法: 按序累加，每次更新max值，如果累加值小于0则从0开始(算法的关键)
	// 原理: 最大子序列的前缀和后缀不可能小于0
public:
	int maxSubArray(vector<int>& nums) {
		int sum = 0, max = -2147483647;
		int i = 0;
		while (i < nums.size()) {
			sum += nums[i];
			if (sum > max) {
				max = sum;
			}
			if (sum < 0) sum = 0;
			++i;
		}
		return max;
	}
};

/**
 *
 * Given a string s consists of upper/lower-case alphabets and empty space characters ' ',
 * return the length of last word in the string.
 * If the last word does not exist, return 0.
 * Note: A word is defined as a character sequence consists of non-space characters only.
 * For example,
 * Given s = "Hello World",
 * return 5.
 *
 */
class Solution18 {
public:
	int lengthOfLastWord(string s) {
		// 第一遍我看错题了，以为是输出最长单词长度
		int len = s.size();
		int maxLength = 0;
		int flag = 0;

		for (int i = len - 1; i >= 0; i--)
		{
			if (s[i] != ' ') {
				flag = 1;
				++maxLength;
			}
			if (flag && s[i] == ' ') break;
		}

		return maxLength;
	}
};

/***
 *
 * Given a non-negative integer represented as a non-empty array of digits, plus one to the integer.
 * You may assume the integer do not contain any leading zero, except the number 0 itself.
 * The digits are stored such that the most significant digit is at the head of the list.
 *
 */
class Solution19 {
public:
	vector<int> plusOne(vector<int>& digits) {
		vector<int> a = digits;
		int len = digits.size();
		a[len - 1] += 1;
		for (int i = len - 1; i >= 0; i--) {
			if (i > 0) {
				a[i - 1] += a[i] / 10;
				a[i] %= 10;
			}
			else {
				if (a[i] >= 10) {
					a.insert(a.begin(), a[i] / 10);
					a[i + 1] %= 10;
				}
				break;
			}
		}
		int j = 0;
		for (int i = 0; i < a.size(); i++)
		{
			if (a[i] != 0) {
				j = i;
				break;
			}
		}
		vector<int> res;
		for (int i = j; i < a.size(); i++)
		{
			res.push_back(a[i]);
		}
		return res;
	}
};

/***
 *
 * Given a non-empty array of non-negative integers nums, the degree of this array is defined as the maximum frequency of any one of its elements.
 *
 * Your task is to find the smallest possible length of a (contiguous) subarray of nums, that has the same degree as nums.
 *
 * Example 1:
 * Input: [1, 2, 2, 3, 1]
 * Output: 2
 * Explanation:
 * The input array has a degree of 2 because both elements 1 and 2 appear twice.
 * Of the subarrays that have the same degree:
 * [1, 2, 2, 3, 1], [1, 2, 2, 3], [2, 2, 3, 1], [1, 2, 2], [2, 2, 3], [2, 2]
 * The shortest length is 2. So return 2.
 * Example 2:
 * Input: [1,2,2,3,1,4,2]
 * Output: 6
 * Note:
 *
 * nums.length will be between 1 and 50,000.
 * nums[i] will be an integer between 0 and 49,999.
 *
 */
class Solution20 {
public:
	int findShortestSubArray(vector<int>& nums) {
		if (nums.size() == 0) return 0;
		else if (nums.size() == 1) return 1;

		vector<int> copy = nums;
		int start = 0, end = 0;
		int len = copy.size();
		int num = 0;
		int degree = 0;
		int re_st = 0, re_ed = 0, re_dg = 0;

		for (int i = 0; i < len; i++)
		{
			degree = 0;;
			if (copy[i] != -1) {
				start = i;
				num = copy[i];
				for (int j = i; j < len; j++)
				{
					if (copy[j] == num) {
						++degree;
						copy[j] = -1;
						end = j;
					}
				}
				if (degree > re_dg) {
					re_dg = degree;
					re_st = start;
					re_ed = end;
				}
				else if (degree == re_dg) {
					if (end - start < re_ed - re_st) {
						re_ed = end;
						re_st = start;
					}
				}
			}
		}
		return re_ed - re_st + 1;
	}
};

/* KMP算法的实现 */
class KMP {
public:
	vector<int> getNextArray(string str) {
		vector<int> next(str.size() + 1);
		int i = 0, j = -1;
		next[0] = -1;
		while (i < str.size()) {
			if (j == -1 || str[i] == str[j]) {
				next[++i] = ++j;	// 之前j已经在上一个最大公共缀处，所以当str[i] == str[j]时最大公共缀长度+1
			}
			else {
				j = next[j];	// 跳转到最大公共缀处
			}
		}
		return next;
	}

	int kmp(string main, string pattern) {
		vector<int> next = getNextArray(pattern);
		int i = 0, j = 0;
		int mainLength = main.size(), patternLength = pattern.size();

		while (i < mainLength && j < patternLength) {
			if (j == -1 || main[i] == pattern[j]) {	// 假如第一个位置就不匹配或当前位置匹配
				i++; j++;
			}
			else {
				j = next[j];
			}
		}
		if (j == pattern.size()) return i - patternLength;	// 由于匹配完模式串(子串)而跳出才返回真
		return -1;
	}
};