#pragma once

class my_mess
{
public:
	enum MY_MESSAGE
	{
		ERR_ALLOC_MEM,     //b³¹d alokacji pamiêci
		WARN_ARR_FULL,     //tablica jest wypelniona (last > ndim)
		WARN_ARR_EMPT,     //tablica jest pusta (last = 0)
		WARN_ARR_UNKN,     //niepoprawny kod dzia³ania (interfejs)
		WARN_ARR_SMALL,
		ERR_ARR_POINTER,
		ERR_FILE_OPEN,
		ERR_FILE_READ,
		ERR_FILE_WRITE,
		WARN_EXCEL_WRITE,
		WARN_FILE_READ_TYPE,
		WARN_CIN_FAIL,
		TOT_NUMB                 //ogólna iloœæ komunikatów
	};

	static char *strtab[TOT_NUMB];  //tablica tekstowa komunikatów

public:
	void mess(enum MY_MESSAGE ms)const;    //Przy wywo³ani tej funkcji na ekran //pozostaje wyprowadzony komunikat. Jeœli to b³¹d, obliczenia trzeba //skoñczyæ, jeœli nie – kontynuowaæ. ms – sk³adowa enumeration, która podaje //numer komunikatu
};