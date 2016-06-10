#include "stdafx.h"
#include "my_coord.h"
#include <fstream>

my_coord & my_coord::operator = (const my_coord &ob)
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
	//msg = ob.msg;

	return *this;
}

istream & operator >> (istream &strm, my_coord &ob)
{
	cout << "x :";
	strm >> ob.pcoord[0];

	cout << "y :";
	strm >> ob.pcoord[1];
	return strm;
}

my_coord::my_coord(const my_coord & ob)
{
		alloc();
		pcoord[0] = ob.pcoord[0];
		pcoord[1] = ob.pcoord[1];
}

ostream & operator << (ostream &strm, const my_coord &ob)
{
	strm << ob.pcoord[0]<< " " << ob.pcoord[1];
	return strm;
}

fstream & operator << (fstream &strm, const my_coord *ob)
{
	for (int i = 0; i < 2; i++)
	{
		double temp = ob->pcoord[i];
		strm.write((char*)(&temp), sizeof(double));
		if (strm.bad() || strm.fail())
		{
			cout << "b³¹d";
		}
	}
	return strm;
}

fstream & operator >> (fstream &strm, my_coord *ob)
{
	for (int i = 0; i < 2; i++)
	{
		double temp;
		strm.read((char*)(&temp), sizeof(double));
		if (strm.bad() || strm.fail() || strm.gcount() != sizeof(double))
		{
			cout << "b³¹d";
		}
		ob->pcoord[i] = temp;
	}
	return strm;
}

void my_coord::alloc()
{
	try
	{
		pcoord = new double[2];
	}
	catch (bad_alloc)
	{
		msg.mess(my_mess::ERR_ALLOC_MEM);
	}
}

my_coord::my_coord(double x, double y)
{
	alloc(); 
	pcoord[0] = x;
	pcoord[1] = y;
}

my_coord::~my_coord()
{
	delete[] pcoord;
	pcoord = NULL;
}

bool my_coord::operator == (const my_coord & left) const
{
	return(pcoord[0] == left.pcoord[0] &&
		pcoord[1] == left.pcoord[1]);
}