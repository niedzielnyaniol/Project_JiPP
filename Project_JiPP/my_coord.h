#pragma once

#include "my_mess.h"
#include <iostream>

using namespace std;

class my_coord
{
protected:
	double *pcoord;  //pcoord[0] -x ; pcoord[1] - y
	my_mess msg;
	void alloc();
public:
	my_coord() { alloc(); pcoord[0] = pcoord[1] = 0; }
	my_coord(double x, double y);
	my_coord(const my_coord & ob);	// SF brak implementacji !!!
	~my_coord();
	my_coord & operator = (const my_coord &ob);
	friend istream & operator >> (istream &strm, my_coord &ob);
	friend ostream & operator << (ostream &strm, const my_coord &ob);
	friend fstream & operator << (fstream &strm, const my_coord *ob);
	friend fstream & operator >> (fstream &strm, my_coord *ob);
	bool operator == (const my_coord & left) const;

};




