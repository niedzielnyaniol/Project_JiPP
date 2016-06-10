#pragma once
#include "my_coord.h"

class my_node : public my_coord
{
	int numb;       //numer wierzcho³ku
	char str[512];  //nazwa wierzcho³ku
public:
	my_node(int nb, char *st, double xx, double yy);
	my_node();
	my_node(const my_node & ob);
	my_node & operator = (const my_node &ob);
	friend istream & operator >> (istream &strm, my_node &ob);
	friend ostream & operator << (ostream &strm, const my_node &ob);
	friend fstream & operator << (fstream &strm, const my_node *ob);
	friend fstream & operator >> (fstream &strm, my_node *ob);
	bool operator == (const my_node & left) const;
};