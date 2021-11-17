/*
* @author Nickel_Angel (1239004072@qq.com)
* @copyright Copyright (c)
*/

#include <algorithm>
#include <cstring>
#include <cctype>
#include <map>
#include <set>
#include <vector>
#include "conj.hpp"
#include "command.hpp"

std::vector<char> order, suffix, calc_answer;
std::set<char> alphabet;
std::map<char, int> assign_table;
std::map<char, int> operator_priority;

bool calc_flag;

void init()
{
	operator_priority['n'] = 1;
	operator_priority['a'] = 2;
	operator_priority['o'] = 2;
	operator_priority['c'] = 3;
	operator_priority['b'] = 3;
}

bool data_input()
{
	order.clear();
	static char c;
	static int length;
	c = getchar(), length = 0;
	do
	{
		if (c == 32 || c == '\n')
		{
			c = getchar();
			continue;
		}
		order.push_back(c);
		++length;
		if (length > 100)
			return false;
		c = getchar();
	}while (c != '\n');
	return true;
}

void table()
{
	if (!data_input() || order.size() > 10 || order.empty())
	{
		puts("Invaild input!");
		return;
	}
	switch (order[0])
	{
	case 'n':
		puts("P !P");
		puts("1 0");
		puts("0 1");
		break;
	case 'a':
		puts("P Q P and Q");
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 1; j >= 0; --j)
			{
				printf("%d ", (i >> j) & 1);
			}
			printf("%d\n", ((i >> 1) & 1) & (i & 1));
		}
		break;
	case 'o':
		puts("P Q P or Q");
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 1; j >= 0; --j)
			{
				printf("%d ", (i >> j) & 1);
			}
			printf("%d\n", ((i >> 1) & 1) | (i & 1));
		}
		break;
	case 'c':
		puts("P Q P condition Q");
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 1; j >= 0; --j)
			{
				printf("%d ", (i >> j) & 1);
			}
			printf("%d\n", condition(((i >> 1) & 1), (i & 1)));
		}
		break;
	case 'b':
		puts("P Q P bicondition Q");
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 1; j >= 0; --j)
			{
				printf("%d ", (i >> j) & 1);
			}
			printf("%d\n", bicondition(((i >> 1) & 1), (i & 1)));
		}
		break;
	default:
		puts("Invaild input!");
	}
}

void suffix_transfer()
{
	suffix.clear();
	static char st[1010]; //stack
	static int top;
	memset(st, 0, sizeof(st));
	top = 0;
	//to reverse polish notation
	for (unsigned i = 0; i < order.size(); ++i)
	{
		if (calc_flag || top < 0)
		{
			calc_flag = true;
			return;
		}
		if (order[i] == '\n' || order[i] == 32)
			continue;
		if (isupper(order[i]))
		{
			suffix.push_back(order[i]);
			if (top && st[top] == 'n')
			{
				suffix.push_back('n');
				--top;
			}
			continue;
		}
		if (order[i] == 'n')
		{
			st[++top] = order[i];
			while (islower(order[i]))
				++i;
			--i;
			continue;
		}
		if (order[i] == '(')
		{
			st[++top] = order[i];
			continue;
		}
		if (order[i] == ')')
		{
			while (st[top] != '(')
			{
				suffix.push_back(st[top]);
				--top;
				if (top <= 0)
				{
					calc_flag = true;
					return;
				}
			}
			--top;
			if (top > 0 && st[top] == 'n')
			{
				suffix.push_back('n');
				--top;
			}
			continue;
		}
		while (top && st[top] != '(' && operator_priority[st[top]] <= operator_priority[order[i]])
		{
			suffix.push_back(st[top]);
			--top;
		}
		st[++top] = order[i];
		while (islower(order[i]))
			++i;
		--i;
	}
	while (top > 0)
	{
		suffix.push_back(st[top]);
		--top;
	}
}

bool suffix_calc()
{
	static int st[1010], top;
	top = 0;
	for (unsigned i = 0; i < suffix.size(); ++i)
	{
		if (isupper(suffix[i]))
		{
			st[++top] = assign_table[suffix[i]];
			continue;
		}
		if (suffix[i] == 'n')
		{
			if (top < 1)
			{
				calc_flag = true;
				return false;
			}
			st[top] = st[top] ? 0 : 1;
			continue;
		}
		if (top < 2)
		{
			calc_flag = true;
			return false;
		}
		switch (suffix[i])
		{
		case 'a':
			--top;
			st[top] = st[top] & st[top + 1];
			break;
		case 'o':
			--top;
			st[top] = st[top] | st[top + 1];
			break;
		case 'c':
			--top;
			st[top] = condition(st[top], st[top + 1]);
			break;
		case 'b':
			--top;
			st[top] = bicondition(st[top], st[top + 1]);
			break;
		default:
			calc_flag = true;
			return false;
		}
	}
	return st[top];
}

void calc_work()
{
	calc_flag = false;
	//input
	if (!data_input())
	{
		puts("Invaild input!");
		return;
	}
	//init
	alphabet.clear();
	assign_table.clear();
	calc_answer.clear();

	for (unsigned i = 0; i < order.size(); ++i)
	{
		if (isupper(order[i]))
			alphabet.insert(order[i]);
	}
	//transfer
	suffix_transfer();
	//calculate
	int alpha_cnt = alphabet.size();
	for (int i = 0, j; i < (1 << alpha_cnt); ++i)
	{
		j = 0;
		for (auto it = alphabet.begin(); it != alphabet.end(); ++it)
		{
			assign_table[*it] = (i & (1 << j)) ? 1 : 0;
			++j;
		}
		calc_answer.push_back(suffix_calc());
	}
	if (calc_flag)
		return;
	//output
	for (auto c : alphabet)
		printf("%c ", c);
	puts("notation");
	for (int i = 0; i < (1 << alpha_cnt); ++i)
	{
		for (int j = 0; j < alpha_cnt; ++j)
			printf("%d ", (i & (1 << j)) ? 1 : 0);
		printf("%d\n", calc_answer[i]);
	}
}

void work()
{
	init();
	static char mode;
	while (true)
	{
		mode = getchar();
		while (mode == '\n' || mode == 32)
			mode = getchar();
		switch (mode)
		{
		case 't':
			table();
			break;
		case 'c':
			calc_work();
			if (calc_flag)
				puts("Invaild input!");
			break;
		case 'q':
			exit(0);
			break;
		default:
			puts("Invaild input!");
		}
	}
}