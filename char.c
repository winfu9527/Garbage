/*************************************************************************
    > File Name: char.c
    > Author: winfu
    > Created Time: Thu 15 Jun 2017 03:16:07 PM CST
 ************************************************************************/

#include<stdio.h>

#define STR "Hello"

void fun(char *s)
{
	printf("[winfu] -- %s",s);
}

int main()
{
	char *st = "wenfu" "hehe" "11111" "\n";

	//fun(STR "world!\n");
	fun(st);
	return 0;
}
