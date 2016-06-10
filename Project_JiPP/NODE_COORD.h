#ifndef __NODE_COORD
#define __NODE_COORD
#include <iostream>

using namespace std;

class NODE_COORD
{
	double *pcoord;  //pcoord[0] - x, pcoord[1] - y
public:
	NODE_COORD() : pcoord(NULL) {  }
	NODE_COORD(double x, double y, double z);	//konstruktor sparametryzowany
	NODE_COORD(const NODE_COORD &copy);
	~NODE_COORD();			//destruktor
	void set(double x, double y, double z);	//ustala wspó³rzêdne x, y po inicjowaniu
	void disp(char *str);				//wyœwietla na monitorze x, y
	void disp(char *str, int index);
	void my_free();
	NODE_COORD & operator = (const NODE_COORD & praw);
	NODE_COORD operator + (const NODE_COORD & praw);
	//NODE_COORD operator * (const NODE_COORD & praw);
	NODE_COORD operator * (const NODE_COORD * praw);
	double operator * (const NODE_COORD & lew) const;
	bool operator > (const NODE_COORD & lew) const;
	bool operator < (const NODE_COORD & lew) const;
	bool operator == (const NODE_COORD & lew) const;
	bool operator == (const double & praw) const;

private:
	void alloc();
	void crash();				//obs³uguje b³¹d alokowania pamiêci
};

#endif