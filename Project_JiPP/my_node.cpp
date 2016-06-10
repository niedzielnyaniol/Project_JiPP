#include "stdafx.h"
#include "my_node.h"
#include <fstream>

my_node::my_node(int nb, char *st, double xx, double yy) : my_coord(xx, yy)
{
	numb = nb;
	sprintf_s(str, 512 * sizeof(char), st);
}

my_node::my_node() : my_coord()
{
	numb = 0;
	sprintf_s(str, "");
}

my_node::my_node(const my_node &ob)
{
	if (ob.pcoord)
	{
		if (!pcoord)
			alloc();
			pcoord[0] = ob.pcoord[0];
			pcoord[1] = ob.pcoord[1];
	}

	else
	{
		if (pcoord)
			delete[] pcoord;
		pcoord = NULL;
	}

	numb = ob.numb;
	strcpy_s(str, 512 * sizeof(char), ob.str);
}

my_node & my_node::operator = (const my_node &ob)
{ 
	if (ob.pcoord)
	{
		if (!pcoord)
			alloc();
		pcoord[0] = ob.pcoord[0];
		pcoord[1] = ob.pcoord[1];
	}
	else
	{
		if (pcoord)
			delete[] pcoord;
		pcoord = NULL;
	}

	numb = ob.numb;
	strcpy_s(str, 512 * sizeof(char), ob.str);
	
	return *this; 
}

istream & operator >> (istream &strm, my_node &ob)
{
	cout << "x :";
	strm >> ob.pcoord[0];

	cout << "y :";
	strm >> ob.pcoord[1];

	cout << "numb :";
	strm >> ob.numb;

	cout << "name :";
	strm >> ob.str;

	return strm;
}

ostream & operator << (ostream &strm, const my_node &ob)
{
	strm << ob.pcoord[0] << " " << ob.pcoord[1] << " "
		<< ob.numb << " " << ob.str;
	return strm;
}

fstream & operator << (fstream &strm, const my_node *ob)
{
	for (int i = 0; i < 2; i++)
	{
		double temp = ob->pcoord[i];
		strm.write((char*)(&temp), static_cast<streamsize>(sizeof(double)));
		if (strm.bad() || strm.fail())
			ob->msg.mess(my_mess::ERR_FILE_WRITE);
	}

	strm.write((char*)(&ob->numb), static_cast<streamsize>(sizeof(int)));
	if (strm.bad() || strm.fail())
		ob->msg.mess(my_mess::ERR_FILE_WRITE);

	strm.write((char*)(&ob->str), static_cast<streamsize>(sizeof(char)* 512));
	if (strm.bad() || strm.fail())
		ob->msg.mess(my_mess::ERR_FILE_WRITE);
	return strm;
}

fstream & operator >> (fstream &strm, my_node *ob)
{
	for (int i = 0; i < 2; i++)
	{
		double temp;
		strm.read(reinterpret_cast<char *>(&temp), static_cast<streamsize>(sizeof(double)));
		if (strm.bad() || strm.fail() || strm.gcount() != sizeof(double))
			ob->msg.mess(my_mess::ERR_FILE_READ);
		ob->pcoord[i] = temp;
	}

	strm.read(reinterpret_cast<char *>(&ob->numb),  static_cast<streamsize>(sizeof(int)));
	if (strm.bad() || strm.fail() || strm.gcount() != sizeof(int))
		ob->msg.mess(my_mess::ERR_FILE_READ);

	strm.read(reinterpret_cast<char *>(&ob->str), static_cast<streamsize>(sizeof(char)* 512));
	if (strm.bad() || strm.fail() || strm.gcount() != sizeof(char)* 512)
		ob->msg.mess(my_mess::ERR_FILE_READ);

	return strm;
}

bool my_node::operator == (const my_node & left) const
{
	return(pcoord[0] == left.pcoord[0] &&
		pcoord[1] == left.pcoord[1] && 
		numb == left.numb && (strcmp(str, left.str) == 0));
}