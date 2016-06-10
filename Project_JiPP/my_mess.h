#pragma once

class my_mess
{
public:
	enum MY_MESSAGE
	{
		ERR_ALLOC_MEM,     //b��d alokacji pami�ci
		WARN_ARR_FULL,     //tablica jest wypelniona (last > ndim)
		WARN_ARR_EMPT,     //tablica jest pusta (last = 0)
		WARN_ARR_UNKN,     //niepoprawny kod dzia�ania (interfejs)
		WARN_ARR_SMALL,
		ERR_ARR_POINTER,
		ERR_FILE_OPEN,
		ERR_FILE_READ,
		ERR_FILE_WRITE,
		WARN_EXCEL_WRITE,
		WARN_FILE_READ_TYPE,
		WARN_CIN_FAIL,
		TOT_NUMB                 //og�lna ilo�� komunikat�w
	};

	static char *strtab[TOT_NUMB];  //tablica tekstowa komunikat�w

public:
	void mess(enum MY_MESSAGE ms)const;    //Przy wywo�ani tej funkcji na ekran //pozostaje wyprowadzony komunikat. Je�li to b��d, obliczenia trzeba //sko�czy�, je�li nie � kontynuowa�. ms � sk�adowa enumeration, kt�ra podaje //numer komunikatu
};