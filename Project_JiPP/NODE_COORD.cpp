#include "stdafx.h"
#include "NODE_COORD.h"

NODE_COORD::NODE_COORD(double x, double y, double z)
{
	alloc();

	pcoord[0] = x;
	pcoord[1] = y;
	pcoord[2] = z;
}

NODE_COORD::NODE_COORD(const NODE_COORD &copy)
{
	alloc();
	pcoord[0] = copy.pcoord[0];
	pcoord[1] = copy.pcoord[1];
	pcoord[2] = copy.pcoord[2];
}

NODE_COORD::~NODE_COORD()
{
	if (pcoord)
		delete[] pcoord;
}

void NODE_COORD::set(double x, double y, double z)
{
	if (!pcoord)
	{
		alloc();

		pcoord[0] = x;
		pcoord[1] = y;
		pcoord[2] = z;
	}

	else
	{
		pcoord[0] = x;
		pcoord[1] = y;
		pcoord[2] = z;
	}
}

void NODE_COORD::disp(char *str)
{
	if (pcoord)
		cout << str << "\t: " << " (" << pcoord[0] << ", " << pcoord[1] << ", " << pcoord[2] << ")" << endl;
	else
		cout << str << " :  niezaincjowany" << endl;
}

void NODE_COORD::disp(char *str, int index)
{
	if (pcoord)
		//cout << str << " : " << " (" << pcoord[0] << ", " << pcoord[1] << ", " << pcoord[2] << ")" << endl;
		printf("%s_%d\t: (%lf, %lf, %lf)\n", str, index, pcoord[0], pcoord[1], pcoord[2]);
	else
		cout << str << " :  niezaincjowany" << endl;
}

void NODE_COORD::crash()
{
	std::cout << "Blad alokacji pamieci" << endl;
	exit(1);
}

void NODE_COORD::my_free()
{
	if (pcoord)
	{
		delete[] pcoord;
		pcoord = NULL;
	}
}

void NODE_COORD::alloc()
{
	try
	{
		pcoord = new double[3];
	}
	catch (bad_alloc)
	{
		crash();
	}
}

NODE_COORD & NODE_COORD::operator = (const NODE_COORD & praw)
{
	if (pcoord == NULL && praw.pcoord != NULL)
	{
		alloc();
		memset(pcoord, 0, 3);
		pcoord[0] = praw.pcoord[0];
		pcoord[1] = praw.pcoord[1];
		pcoord[2] = praw.pcoord[2];
		return *this;
	}

	else if (pcoord != NULL && praw.pcoord == NULL)
	{
		delete[] pcoord;
		pcoord = NULL;
		return *this;
	}

	else if (pcoord != NULL && praw.pcoord != NULL)
	{
		memset(pcoord, 0, 3);
		pcoord[0] = praw.pcoord[0];
		pcoord[1] = praw.pcoord[1];
		pcoord[2] = praw.pcoord[2];
		return *this;
	}

	else
	{
		return *this;
	}
}

NODE_COORD NODE_COORD::operator + (const NODE_COORD & praw)
{
	if (pcoord == NULL && praw.pcoord != NULL)
	{
		alloc();
		memset(pcoord, 0, 3);
		NODE_COORD ret;
		ret.alloc();
		ret.pcoord[0] = pcoord[0] + praw.pcoord[0];
		ret.pcoord[1] = pcoord[1] + praw.pcoord[1];
		ret.pcoord[2] = pcoord[2] + praw.pcoord[2];
		return ret;
	}

	else if (pcoord != NULL && praw.pcoord == NULL)
	{
		NODE_COORD ret;
		ret.alloc();
		ret.pcoord[0] = pcoord[0];
		ret.pcoord[1] = pcoord[1];
		ret.pcoord[2] = pcoord[2];
		return ret;
	}

	else if (pcoord != NULL && praw.pcoord != NULL)
	{

		NODE_COORD ret;
		ret.alloc();
		ret.pcoord[0] = pcoord[0] + praw.pcoord[0];
		ret.pcoord[1] = pcoord[1] + praw.pcoord[1];
		ret.pcoord[2] = pcoord[2] + praw.pcoord[2];
		return ret;
	}

	else
	{
		NODE_COORD ret;
		ret.alloc();
		return ret;
	}
}
/*
NODE_COORD NODE_COORD::operator * (const NODE_COORD & praw)
{
	if (pcoord != NULL && praw.pcoord != NULL)
	{
		NODE_COORD ret;
		ret.alloc();
		ret.pcoord[0] = pcoord[0] * praw.pcoord[0];
		ret.pcoord[1] = pcoord[1] * praw.pcoord[1];
		ret.pcoord[2] = pcoord[2] * praw.pcoord[2];
		return ret;
	}

	else
	{
		NODE_COORD ret;
		ret.alloc();
		return ret;
	}
}
*/

NODE_COORD NODE_COORD::operator * (const NODE_COORD * praw)
{
	if (pcoord != NULL && praw->pcoord != NULL)
	{
		NODE_COORD ret;
		ret.alloc();
		ret.pcoord[0] = pcoord[0] * praw->pcoord[0];
		ret.pcoord[1] = pcoord[1] * praw->pcoord[1];
		ret.pcoord[2] = pcoord[2] * praw->pcoord[2];
		return ret;
	}

	else
	{
		NODE_COORD ret;
		ret.alloc();
		return ret;
	}
}

double NODE_COORD::operator * (const NODE_COORD & lew) const
{
	double dot = lew.pcoord[0] * pcoord[0] +
		lew.pcoord[1] * pcoord[1] +
		lew.pcoord[2] * pcoord[2];
	return dot;
}

bool NODE_COORD::operator > (const NODE_COORD & lew) const
{
	double scalThis, scalLew;
	scalThis = pcoord[0] * pcoord[0] + pcoord[1] * pcoord[1] +
		pcoord[2] * pcoord[2];
	scalLew = lew.pcoord[0] * lew.pcoord[0] + 
		lew.pcoord[1] * lew.pcoord[1] +
		lew.pcoord[2] * lew.pcoord[2];
	return (scalLew > scalThis);
}

bool NODE_COORD::operator < (const NODE_COORD & lew) const
{
	double scalThis, scalLew;
	scalThis = pcoord[0] * pcoord[0] + pcoord[1] * pcoord[1] +
		pcoord[2] * pcoord[2];
	scalLew = lew.pcoord[0] * lew.pcoord[0] +
		lew.pcoord[1] * lew.pcoord[1] +
		lew.pcoord[2] * lew.pcoord[2];
	return (scalLew < scalThis);
}

bool NODE_COORD::operator == (const NODE_COORD & lew) const
{
	return(pcoord[0] == lew.pcoord[0] &&
		pcoord[1] == lew.pcoord[1] &&
		pcoord[2] == lew.pcoord[2]);
}

bool NODE_COORD::operator == (const double & praw) const
{
	for (int i = 0; i < 3; ++i)
		if (pcoord[i] == praw)
			return true;
	return false;
}