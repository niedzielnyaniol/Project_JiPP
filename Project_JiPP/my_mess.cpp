#include "stdafx.h"
#include <iostream>
#include "my_mess.h"

using namespace std;

char *my_mess::strtab[] =
{
	"E  memory alloc error",          //ERR_ALLOC_MEM
	"W  array is full",               //WARN_ARR_FULL
	"W  array is empty",              //WARN_ARR_EMPT
	"W  niepoprawny kod operacji",
	"W  tablica jest mniejsza niz ind",
	"E  bledny wskaznik do tablicy lub indeks przekrocza granice tablicy",
	"E	open file error",
	"E	read file error",
	"E  write file error",
	"W  export to excel error",
	"W  bledny typ w pliku",
	"W  cin fail"
};

void my_mess::mess(enum MY_MESSAGE ms) const
{
	if (strtab[ms][0] == 'E')
	{
		cout << "ERROR: " << &strtab[ms][1] << endl;
		system("pause");
		exit(1);
	}
	else if (strtab[ms][0] == 'W')
	{
		cout << "WARNING: " << &strtab[ms][1] << endl;
	}
}