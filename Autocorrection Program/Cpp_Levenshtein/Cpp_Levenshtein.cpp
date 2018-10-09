// Cpp_Levenshtein.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <thread>

#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c))) //sprawdz kt�re z a,b lub c jest min

extern "C" __declspec(dllexport) int Levenshtein(int* matrix, char* s1, char* s2, int dimension_1, int dimension_2);


//zrobic new poza funkcja levenshtein - zrobione
//tablica jednowymiarowa - zrobione
//wskaznik na �ancuch char zamiast string - zrobione
int Levenshtein(int* matrix, char* s1, char* s2, int dimension_1, int dimension_2)
{


	//i, x i y to liczniki wykorzystywane w p�tlach do wype�niania i poruszania si� po elementach tablicy, dimension 1 i dimension 2 to zmienne, kt�re b�d� wymiarami tablicy
	int x, y, result;

	//pierwszy element pierwszej kolumny i wiersza(pierwszy element tablicy) jest warto�ci� 0)
	matrix[0] = 0;

	//wypelnianie co x*rozmiar wyrazu wybranego przez uzytkownika elementu kolejn� liczb� tzn. 1, 2 itd.
	//czyli powstaje tablica wygladajaca tak: 0, (dim2) 1, (dim2) 2, (dim2) 3... itd.
	for (x = 1; x * dimension_2 < dimension_1 * dimension_2; ++x)
		matrix[x * dimension_2] = matrix[(x - 1) * dimension_2] + 1;

	//wypelnianie co y-tego elementu kolejn� liczb� tzn. 1, 2 itd.
	// czyli powstaje tablica wygladajaca tak: 0, 1, 2, 3... (dop�ki y nie osi�gnie dim2)
	for (y = 1; y < dimension_2; ++y)
		matrix[y] = matrix[y - 1] + 1;

	//obie te formu�y daj� w wyniku tablic� wygl�daj�c� tak:
	//0, 1, 2, 3, 4 (dop�ki y nie osi�gnie dim2), 1, (wolne elementy w ilo�ci = dim2), 2, (wolne elementy w ilo�ci = dim2), 3... itd. dop�ki ilo�� element�w nie wynosi dim1 * dim2

	for (x = 1; x * dimension_2 < dimension_1 * dimension_2; ++x)
		for (y = 1; y < dimension_2; ++y)
			matrix[x * dimension_2 + y] = MIN3(matrix[(x - 1) * dimension_2 + y] + 1, matrix[x * dimension_2 + (y - 1)] + 1, matrix[(x - 1) * dimension_2 + (y - 1)] + (s1[x - 1] == s2[y - 1] ? 0 : 1)); //matrix of values which in result gives levenshtein distance


	//szukana odleg�o�� edycyjna
	result = matrix[dimension_1*dimension_2 - 1];

	//zwr�cenie odleg�o�ci edycyjnej
	return result;
}