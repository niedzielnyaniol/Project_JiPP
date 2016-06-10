#pragma once

#include "my_mess.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

template <class T> class my_vect
{
	T *dat;						//wskaznik do danych typu ogolnego
	size_t ndim;				//rozmiar tablicy, na ktory pozostala zaalokowana
	size_t last;				//wskazuje na pierwsza pusta pozycje w tablice
	my_mess msg;
	//ifstream flinp;  // strumieñ dla odczytu z pliku binarnego
	//ofstream flout;  // strumieñ dla zapisu w plik binarny
	fstream flinp;
	char filename[FILENAME_MAX];

public:
	my_vect(size_t dm);			//konstruktor - alokuje pamiec dla tablicy typu T 
								//na dm elementow
	my_vect() { dat = NULL; ndim = last = 0; }
	~my_vect();
	void init(size_t dm);		//alokuje pamiec o dm elementow, jesli dat = NULL
	T *get_begin();				//zwraca wskaŸnik do pocz¹tku tablicy dat
	T *get_end();				//zwraca wskaŸnik do dat[last]
	void disp();				//wyswietla stan tablicy
	void push(const T &ob);		//dodaje element typu T do pierwszej wolnej 
								//pozycji w tablice
	T *pop();					//zwraca wskaznik do ostatniego elementu tablicy 
								//i usuwa jego, lub NULL (tablica pusta)
	T & operator [] (const size_t ind); //0 <= ind < last
	void remove(size_t ind);	//usuwa element tablicy o indeksie ind, kompresuje tablicu
	void insert(const T &ob, size_t ind);	//wstawia element ob w tablicê odrazu 
											//po elemencie dat[ind]
	void insert(const T &ob, size_t ind, size_t numb);  // wstawia tablicê 				
								//elementów ob w tablicê dat odrazu po elemencie dat[ind]
								//numb - iloœæ elementow w tablice ob
	void clear_all();			//usuniêcie wszystkich elementów tablicy
	bool Prep_excel();			//wyprowadzenie danych w plik tekstowy w formacie Excel (*.csv)
	bool save();
	bool read();
	void modify(size_t ind, const T & ob);
	bool is_empty();


private:
	bool alloc();				//alocuje pamiêæ
	bool my_realloc();
	char* conv_to_excel(stringstream & strm);
};

template <class T>
my_vect<T> ::my_vect(size_t dm)
{
	ndim = dm;
	if (!alloc())
		msg.mess(my_mess::ERR_ALLOC_MEM);
	else
		last = dm;
}

template<class T>
my_vect<T>::~my_vect()
{
	delete[] dat;
}

template<class T>
bool my_vect<T>::alloc()
{
	try
	{
		dat = new T[ndim];
		return 1;
	}
	catch (bad_alloc)
	{
		return 0;
	}
}

template<class T>
void my_vect<T>::init(size_t dm)
{
	if (!dat)
	{
		ndim = dm;
		if (!alloc())
			msg.mess(my_mess::ERR_ALLOC_MEM);
		else
		last = 0;
		sprintf_s(filename, "testy.dat");
	}
	else
		return;
}

template<class T>
T * my_vect<T>::get_begin()
{
	return dat;
}

template<class T>
T * my_vect<T>::get_end()
{
	return &dat[last];
}

template<class T>
void my_vect<T>::disp()
{
	if (last > 0)
	{
		size_t it;
		for (it = 0; it < last; it++)
		{
			cout << "it = " << it << " :  " << dat[it] << endl;
			//przeciazyc operator << dla obiektu klasy T
		}
	}
	else
		msg.mess(my_mess::WARN_ARR_EMPT);
}

template<class T>
void my_vect<T>::push(const T &ob)
{
	if (last >= ndim)
	{
		msg.mess(my_mess::WARN_ARR_FULL);
		if (!my_realloc())
			msg.mess(my_mess::ERR_ALLOC_MEM);
	}
	dat[last] = ob;
	last++;
}

template<class T>
T * my_vect<T>::pop()
{
	if (last > 0)
	{
		last--;
		return &dat[last];
	}
	else
	{
		return NULL;
	}
}

template<class T>
T & my_vect<T>::operator [] (const size_t ind)
{
	if (!dat || ind < 0 || ind >= last)
	{
		msg.mess(my_mess::ERR_ARR_POINTER);
	}
	return dat[ind];
}

template<class T>
void my_vect<T>::remove(size_t ind)
{
	//SF wykreœlanie elementu tablicy nie powinno alokowaæ pamiêæ dla kopii tej tablicy.
	//Proszê zastanowiæ siê nad tym, jak tego unikn¹æ. 

	/*
	T* temp = NULL;
	try
	{
		temp = new T[ndim];
	}
	catch (bad_alloc)
	{
		msg.mess(my_mess::ERR_ALLOC_MEM);
	}

	for (int i = 0; i < ind; i++)
		temp[i] = dat[i];
	for (int i = ind; i < last; ++i)
		temp[i] = dat[i + 1];
	last--;
	delete[] dat;
	if (!alloc())
		msg.mess(my_mess::ERR_ALLOC_MEM);
	for (int i = 0; i < last; i++)
		dat[i] = temp[i];
	*/

	for (int i = ind; i < last; ++i)
		dat[i] = dat[i + 1];
	last--;
}

template<class T>
bool my_vect<T>::my_realloc()
{
	//SF Ten algorytm nie jest optymalny. Pan wykonuje dwa alokowania i dwa kopiowania.
	//Optymalny algorytm wykonuje jedno alokowanie i jedno kopiowanie.
	//Proszê o poprawieniu.

	ndim += 20;
	T* temp;

	try
	{
		temp = new T[ndim];
	}
	catch (bad_alloc)
	{
		return 0;
	}

	for (int i = 0; i < last; i++)
		temp[i] = dat[i];
	delete[] dat;
	/*
	if (!alloc())
		return 0;
	for (int i = 0; i < last; i++)
		dat[i] = temp[i];
	*/
	dat = temp;
	return 1;
}

template <class T> 
bool my_vect<T>::read()
{
	//SF uwagi s¹ takie same jak i w metodzie save().
	char tmpstr[512];
	size_t tmplast;
	flinp.open(filename, ios::in | ios::binary);
	if (!flinp.is_open())
		msg.mess(my_mess::ERR_FILE_OPEN);
	T tmp;
	last = 0;

	flinp.read(tmpstr, static_cast<streamsize>(sizeof(char)* 512));
	if (flinp.bad() || flinp.fail() || flinp.gcount() != sizeof(char)* 512)
		msg.mess(my_mess::ERR_FILE_READ);

	//flinp >> tmpstr;

	if ((strcmp(tmpstr , typeid(tmp).name())) != 0)
	{
		msg.mess(my_mess::WARN_FILE_READ_TYPE);
		return false;
	}

	flinp.read(reinterpret_cast<char *>(&tmplast), static_cast<streamsize>(sizeof(size_t)));
	if (flinp.bad() || flinp.fail() || flinp.gcount() != sizeof(size_t))
		msg.mess(my_mess::ERR_FILE_READ);

	for (size_t i = 0; i < tmplast && !flinp.eof(); ++i)
	{
		flinp >> &tmp;
		if (flinp.eof())
			break;
		push(tmp);
	}
	flinp.close();
	return true;
}

template <class T>
bool my_vect<T>::save()
{
	if (last == 0)
	{
		msg.mess(my_mess::WARN_ARR_EMPT);
		return 0;
	}
	flinp.open(filename, ios::out | ios::binary);

	//SF flaga good nie jest w³aœciw¹ w tym przypadku.
	//dla tego s³u¿y !flinp.is_open() 

	if (!flinp.is_open())
		msg.mess(my_mess::ERR_FILE_OPEN);

	//SF typeid(...).name() zwraca wiersz tekstowy.
	//Zapis stream << typeid(...).name() wyprowadzi wiersz tekstowy
	// w strumieñ typu fstream w formacie tekstowym, a nie binarnym.
	//W zadaniu by³o wykonaæ IO system w postaci binarnej.

	char temp[512];
	sprintf_s(temp, typeid(T).name());
	
	flinp.write(temp, static_cast<streamsize>(sizeof(char)* 512));	//zapisanie na poczatku pliku nazwy zmiennej
	if (flinp.bad() || flinp.fail())
		msg.mess(my_mess::ERR_FILE_WRITE);

	//flinp << temp;

	flinp.write(reinterpret_cast<char *>(&last), static_cast<streamsize>(sizeof(size_t)));	//iloœæ obiektów w pliku
	if (flinp.bad() || flinp.fail())
		msg.mess(my_mess::ERR_FILE_WRITE);

	for (int i = 0; i < last; ++i)
	{
		flinp << &dat[i];  
		//SF w klasie danych tu ma byæ przeci¹¿enie operatora <<, który realizuje zapis 
		//binarny, a nie tekstowy

		//if (i != last - 1) //SF dla pliku binarnego to jest nie dla czego.
		//	flinp << endl;
	}
	flinp.close();
	return true;
}

template <class T>
void my_vect<T>::clear_all()
{
	delete[] dat;
	dat = NULL;
	init(ndim);
}

template <class T>
void my_vect<T>::modify(size_t ind, const T & ob)
{
	dat[ind] = ob;
}

template <class T>
void my_vect<T>::insert(const T &ob, size_t ind)
{
	if (ind == last + 1) push(ob);
	else if (ind > last + 1)
		msg.mess(my_mess::WARN_ARR_SMALL);
	else
	{
		if (last + 1 >= ndim)
		{
			msg.mess(my_mess::WARN_ARR_FULL);
			if (!my_realloc())
				msg.mess(my_mess::ERR_ALLOC_MEM);
		}

		//SF nie powinno byæ ¿adnego alokowania i kopiowania
		/*
		T* temp = NULL;
		try
		{
		temp = new T[ndim];
		}
		catch (bad_alloc)
		{
		msg.mess(my_mess::ERR_ALLOC_MEM);
		}
		*/
		last++;
		for (int i = last; i > ind; i--)
			dat[i] = dat[i - 1];
		dat[ind] = ob;

		/*
		i = ind;
		j = 0;
		while (i < last)
		temp[j++] = dat[i++];

		dat[ind++] = ob;
		last++;

		i = ind;
		j = 0;
		while (i < last)
		dat[i++] = temp[j++];
		*/
	}
}

template <class T>
void my_vect<T>::insert(const T &ob, size_t ind, size_t numb)
{
	//SF wywo³anie wpêtle element po elemencie dla wstawiania elementów tablicy ob
	//jest bardzo nie optymalna procedura
	//Tu powinien dzia³aæ inny algorytm

	if (ind > last + 1)
		msg.mess(my_mess::WARN_ARR_SMALL);
	else
	{
		if ((last + numb) >= ndim)
		{
			msg.mess(my_mess::WARN_ARR_FULL);
			if (!my_realloc())
				msg.mess(my_mess::ERR_ALLOC_MEM);
		}


		size_t i;

		for (i = (last); i > ind; i--) 
			dat[i + numb - 1] = dat[i - 1];
		for (i = 0; i<numb; i++) 
			dat[i + ind] = (&ob)[i];

		last += numb;	
	}
	/*
	for (int i = 0; i < numb; ++i)
	insert(ob[i], ind++);
	*/
}

template <class T>
bool my_vect<T>::Prep_excel()
{
	if (last == 0)
	{
		msg.mess(my_mess::WARN_ARR_EMPT);
		return 0;
	}
	fstream flinp;
	stringstream tmpStream;
	tmpStream.clear();
	flinp.open("excel_exp.csv", ios::out);
	if (!flinp.good())
		msg.mess(my_mess::ERR_FILE_OPEN);

	for (int i = 0; i < last; ++i)
	{
		tmpStream << dat[i];
		if (i != last - 1)
			tmpStream << endl;
	}
	flinp << typeid(T).name() << endl;
	flinp << conv_to_excel(tmpStream);
	flinp.close();
	string openString = "start excel_exp.csv"; // the string for the command

	system(openString.c_str()); // sends the command and converts from type string to constant char

	return true;
}

template <class T>
char* my_vect<T>::conv_to_excel(stringstream & strm)
{
	string tmpString;
	char* tmpChar = NULL;
	size_t len;

	tmpString = strm.str();
	len = tmpString.length() + 1;

	try
	{
		tmpChar = new char[len];
	}
	catch (bad_alloc)
	{
		msg.mess(my_mess::ERR_ALLOC_MEM);
	}

	memcpy((void*)tmpChar, (void*)tmpString.c_str(), len);
	
	for (size_t i = 0; i < len; ++i)
	if (tmpChar[i] == ' ')
			tmpChar[i] = ';';

	return tmpChar;
}
	
template <class T>
bool my_vect<T>::is_empty()
{
	if (last == 0) return 1;
	else return 0;
}