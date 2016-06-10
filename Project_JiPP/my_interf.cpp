#include "stdafx.h"
#include "my_interf.h"

#define MAX_INTERF_CHAR 255

using namespace std;

template <typename T, typename K>
T* my_find(const T* p_begin, const T* p_end, const K &key)
{
	T* tmp = const_cast <T*> (p_begin);
	for (; tmp != p_end; ++tmp)
	if (*tmp == key)
		return tmp;
	return NULL;
}

my_interf::my_interf(size_t dim)
{
	sprintf_s(str_interf[MY_INTERF_PUSH], MAX_INTERF_CHAR*sizeof(char), "%d - push", MY_INTERF_PUSH);
	sprintf_s(str_interf[MY_INTERF_POP], MAX_INTERF_CHAR*sizeof(char), "%d - pop", MY_INTERF_POP);
	sprintf_s(str_interf[MY_INTERF_CLROBJ], MAX_INTERF_CHAR*sizeof(char), "%d - delete an object", MY_INTERF_CLROBJ);
	sprintf_s(str_interf[MY_INTERF_CLRALL], MAX_INTERF_CHAR*sizeof(char), "%d - clear all", MY_INTERF_CLRALL);
	sprintf_s(str_interf[MY_INTERF_MODIFI], MAX_INTERF_CHAR*sizeof(char), "%d - object modification", MY_INTERF_MODIFI);
	sprintf_s(str_interf[MY_INTERF_INSERT], MAX_INTERF_CHAR*sizeof(char), "%d - object insert", MY_INTERF_INSERT);
	sprintf_s(str_interf[MY_INTERF_INSERT_ARR], MAX_INTERF_CHAR*sizeof(char), "%d - insert an array of objects", MY_INTERF_INSERT_ARR);
	sprintf_s(str_interf[MY_INTERF_FIND], MAX_INTERF_CHAR*sizeof(char), "%d - find", MY_INTERF_FIND);
	sprintf_s(str_interf[MY_INTERF_SAVE], MAX_INTERF_CHAR*sizeof(char), "%d - save", MY_INTERF_SAVE);
	sprintf_s(str_interf[MY_INTERF_READ], MAX_INTERF_CHAR*sizeof(char), "%d - read", MY_INTERF_READ);
	sprintf_s(str_interf[MY_INTERF_DISP], MAX_INTERF_CHAR*sizeof(char), "%d - disp", MY_INTERF_DISP);
	sprintf_s(str_interf[MY_INTERF_EXCEL], MAX_INTERF_CHAR*sizeof(char), "%d - excel export", MY_INTERF_EXCEL);
	sprintf_s(str_interf[MY_INTERF_FINISH], MAX_INTERF_CHAR*sizeof(char), "%d - finish", MY_INTERF_FINISH);
	vect.init(dim);
	run = true;
}

void my_interf::menu()
{
	int i;
	for (i = 0; i<MY_INTERF_TOT; i++)
	{
		cout << str_interf[i] << endl;
	}
}

void my_interf::push()
{
	variable ob;
	cout << "Add new object of " << typeid(ob).name() << endl;
	cin >> ob;
	if (cin.fail())
	{
		cin.clear();
		cin.sync();
		msg.mess(my_mess::WARN_CIN_FAIL);
		return;
	}
	vect.push(ob);
}

void my_interf::pop()
{
	variable *ptr = NULL;
	cout << "POP" << endl;
	ptr = vect.pop();
	if (ptr)
	{
		cout << *ptr << endl;
	}
	else
	{
		msg.mess(my_mess::WARN_ARR_EMPT);
	}
}

void my_interf::disp()
{
	if (vect.is_empty())
	{
		msg.mess(my_mess::WARN_ARR_EMPT);
		return;
	}

	cout << "DISPLAY" << endl;
	vect.disp();
}

void my_interf::find()
{
	if (vect.is_empty())
	{
		msg.mess(my_mess::WARN_ARR_EMPT);
		return;
	}
	int i = 0;
	variable ob;
	variable *ptr = NULL;
	cout << "INPUT OBJECT TO FIND" << endl;
	cin >> ob;
	if (cin.fail())
	{
		cin.clear();
		cin.sync();
		msg.mess(my_mess::WARN_CIN_FAIL);
		return;
	}
	ptr = vect.get_begin();
	size_t dist;
	
	while (ptr)
	{
		ptr = my_find(ptr, vect.get_end(), ob);
		if (ptr)
		{
			dist = ptr - vect.get_begin();
			cout << "it[" << dist << "] " << *ptr << endl;
			ptr++;
			i++;
		}
		else
		{
			if (i > 0) cout << i << " OBJECTS FOUND." << endl;
			else cout << "NO OBJECT FOUND" << endl;
		}
	}
}

void my_interf::finish()
{
	run = 0;
}

void my_interf::defaul()
{
	cin.clear();
	cin.sync();
	msg.mess(my_mess::WARN_ARR_UNKN);
}

void my_interf::save()
{
	if (vect.is_empty())
	{
		msg.mess(my_mess::WARN_ARR_EMPT);
		return;
	}
	if (vect.save())
		cout << "DATA STORED" << endl;
	else
		msg.mess(my_mess::ERR_FILE_WRITE);
}

void my_interf::read()
{
	if (vect.read())
	cout << "DATA HAS BEEN READ" << endl;
}

void my_interf::clear_all()
{
	if (vect.is_empty())
	{
		msg.mess(my_mess::WARN_ARR_EMPT);
		return;
	}
	vect.clear_all();
	cout << "DATA WERE REMOVED" << endl;
}

void my_interf::clear_object()
{
	if (vect.is_empty())
	{
		msg.mess(my_mess::WARN_ARR_EMPT);
		return;
	}
	variable ob;
	variable *ptr = NULL;
	cout << "INPUT OBJECT FOR DELETE" << endl;
	cin >> ob;
	if (cin.fail())
	{
		cin.clear();
		cin.sync();
		msg.mess(my_mess::WARN_CIN_FAIL);
		return;
	}
	ptr = vect.get_begin();
	size_t dist;

	ptr = my_find(ptr, vect.get_end(), ob);
	if (ptr)
	{
		dist = ptr - vect.get_begin();
		cout << "it [" << dist << "] " << *ptr << " HAS BEEN DELETED" << endl;
		vect.remove(dist);
	}
	else
		cout << "NO OBJECT FOUND" << endl;
}

void my_interf::modification()
{
	if (vect.is_empty())
	{
		msg.mess(my_mess::WARN_ARR_EMPT);
		return;
	}
	variable ob, mod;
	variable *ptr = NULL;
	cout << "INPUT OBJECT FOR MODIFICATION" << endl;
	cin >> ob;
	if (cin.fail())
	{
		cin.clear();
		cin.sync();
		msg.mess(my_mess::WARN_CIN_FAIL);
		return;
	}
	ptr = vect.get_begin();
	size_t dist;

	ptr = my_find(ptr, vect.get_end(), ob);
	if (ptr)
	{
		dist = ptr - vect.get_begin();
		cout << "INPUT NEW OBJECT" << endl;
		cin >> ob;
		if (cin.fail())
		{
			cin.clear();
			cin.sync();
			msg.mess(my_mess::WARN_CIN_FAIL);
			return;
		}
		cout << "it [" << dist << "] " << *ptr << " HAS BEEN MODIFIED" << endl;
		vect.modify(dist, ob);
	}
	else
		cout << "NO OBJECT FOUND" << endl;
}

void my_interf::insert_obj()
{
	variable ob;
	size_t ind;
	cout << "INPUT A NEW OBJECT" << endl;
	cin >> ob;
	if (cin.fail())
	{
		cin.clear();
		cin.sync();
		msg.mess(my_mess::WARN_CIN_FAIL);
		return;
	}
	cout << "INPUT IND - AN INDEX" << endl << "ind:";
	cin >> ind;
		if (cin.fail())
	{
		cin.clear();
		cin.sync();
		msg.mess(my_mess::WARN_CIN_FAIL);
		return;
	}
	vect.insert(ob, ind);
}

void my_interf::insert_arr()
{
	variable *arr = NULL;
	size_t ind;
	size_t numb;
	cout << "INPUT NUMBER OF OBJECTS" << endl;
	cin >> numb;
	if (cin.fail())
	{
		cin.clear();
		cin.sync();
		msg.mess(my_mess::WARN_CIN_FAIL);
		return;
	}
	//SF tu Pan alokuje pamiêæ dla obiektu lokalnego arr
	//A gdzie Pan zwalnia t¹ pamieæ?
	try
	{
		arr = new variable[numb];
	}
	catch (bad_alloc)
	{
		msg.mess(my_mess::ERR_ALLOC_MEM);
	}

	for (int i = 0; i < numb; ++i)
	{
		cout << "INPUT A NEW OBJECT" << endl;
		cin >> arr[i];
		if (cin.fail())
		{
			cin.clear();
			cin.sync();
			msg.mess(my_mess::WARN_CIN_FAIL);
			return;
		}
	}
	cout << "INPUT IND - AN INDEX" << endl << "ind:";
	cin >> ind;
	if (cin.fail())
	{
		cin.clear();
		cin.sync();
		msg.mess(my_mess::WARN_CIN_FAIL);
		return;
	}
	vect.insert(*arr, ind, numb);

	delete[] arr;
}

void my_interf::excel_exp()
{
	if (vect.is_empty())
	{
		msg.mess(my_mess::WARN_ARR_EMPT);
		return;
	}
	if (vect.Prep_excel())
		cout << "DATA WERE EXPORTED" << endl;
	else
		msg.mess(my_mess::WARN_EXCEL_WRITE);
}