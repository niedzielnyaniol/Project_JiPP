#pragma once

#include "my_vect.h"
#include "my_coord.h"
#include "my_node.h"


typedef my_coord variable; //a variable in container vect

class my_interf
{
public:
	enum MY_INTERF
	{
		MY_INTERF_PUSH,
		MY_INTERF_POP,
		MY_INTERF_CLROBJ,
		MY_INTERF_CLRALL,
		MY_INTERF_MODIFI,
		MY_INTERF_INSERT,
		MY_INTERF_INSERT_ARR,
		MY_INTERF_FIND,
		MY_INTERF_SAVE,
		MY_INTERF_READ,
		MY_INTERF_DISP,
		MY_INTERF_EXCEL,
		MY_INTERF_FINISH,
		MY_INTERF_TOT
	};
private:
	my_vect<variable> vect;
	char str_interf[MY_INTERF_TOT][512];  //komunikaty, wyœwietlane na monitorze
	my_mess msg;

public:
	bool run;

	my_interf();
	my_interf(size_t dim);
	void menu();
	void push();
	void pop();
	void disp();
	void find();
	void save();
	void read();
	void finish();
	void defaul();
	void clear_all();
	void clear_object();
	void modification();
	void insert_obj();
	void insert_arr();
	void excel_exp();
};