// Project_Levenshtein.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <string>
#include <thread>
#include "vld.h"
#include <fstream>



typedef int(*Levenshtein_function)(int*, const char*, const char*, int, int);



int memory_and_lev(std::string words_array, std::string user_s_choice, int tmp);
void search_dictionary_result(std::string user_s_word, std::string*& words_array, int beginning, int words_count, int*& result_int, std::string*& result_str, int iteration, int tmp);
void file_to_array(std::string*& words_array, int* num_of_words);
void load_program_threads(int tmp);



int memory_and_lev(std::string words_array_1, std::string user_s_choice, int tmp)
{
	int result, dimension1, dimension2;

	const char* s1 = words_array_1.c_str(); //changing object of string class to C string version.
	const char* s2 = user_s_choice.c_str(); //changing object of string class to C string version.
	int* matrix;

	dimension1 = words_array_1.length() + 1;
	dimension2 = user_s_choice.length() + 1;

	matrix = new int[dimension1 * dimension2]; //one-dimensional array which got as many elements as two-dimensional version with dimension1 rows and dimension2 columns

	if (tmp == '1')
	{
		HINSTANCE hInstLibrary_cpp = LoadLibrary(L"Cpp_Levenshtein.dll");

		if (hInstLibrary_cpp)
		{
			Levenshtein_function lev_cpp;

			lev_cpp = (Levenshtein_function)GetProcAddress(hInstLibrary_cpp, "Levenshtein");

			if (lev_cpp)
			{
				result = lev_cpp(matrix, s1, s2, dimension1, dimension2);
			}
			FreeLibrary(hInstLibrary_cpp);
		}
	}

	else if (tmp == '2')
	{
		HINSTANCE hInstLibrary_asm = LoadLibrary(L"Asm_Levenshtein.dll");

		if (hInstLibrary_asm)
		{
			Levenshtein_function lev_asm;

			lev_asm = (Levenshtein_function)GetProcAddress(hInstLibrary_asm, "Levenshtein");

			if (lev_asm)
			{
				result = lev_asm(matrix, s1, s2, dimension1, dimension2);
			}

			FreeLibrary(hInstLibrary_asm);
		}
	}

	else std::cout << "\nERROR in search directory\n";

	delete[] matrix;

	return result;
}

void search_dictionary_result(std::string user_s_word, std::string*& words_array, int beginning, int words_count, int*& result_int, std::string*& result_str, int iteration, int tmp)
{
	int distance_additional;

	result_int[iteration] = memory_and_lev(words_array[beginning], user_s_word, tmp);
	result_str[iteration] = words_array[beginning];

	for (int i = beginning + 1; i < beginning + words_count; ++i)
	{
		distance_additional = memory_and_lev(words_array[i], user_s_word, tmp);

		if (distance_additional < result_int[iteration])
		{
			result_int[iteration] = distance_additional;
			result_str[iteration] = words_array[i];
		}
	}
}

void file_to_array(std::string*& words_array, int* num_of_words) //function that gets data from file and saves it in array of words
{
	std::fstream data_f;
	std::string Buffor;
	int i = 0;

	data_f.open("data_file.txt", std::ios::in); //make sure that file exists

	if (!data_f.good()) //if file doesn't exists...
	{
		data_f.open("data_file.txt", std::ios::out); //... create new one
		data_f.close();
		std::cout << "File doesn't exists.\nPress enter.\n";
		return;
	}

	data_f.open("data_file.txt", std::ios::in); //open existing file

	data_f.clear();
	data_f.seekg(0, std::ios::beg); //going back to start of file

	while (std::getline(data_f, Buffor))++*num_of_words; //counting words in text file

	words_array = new std::string[*num_of_words]; //allocating memory for array of words

	data_f.clear();
	data_f.seekg(0, std::ios::beg); //going back to start of file

	while ((std::getline(data_f, Buffor))) //saving words from file to array
	{
		words_array[i] = Buffor;
		++i;
	}

	data_f.close();
}

void load_program_threads(int tmp)
{
	std::thread* array_of_threads; //for storing threads in one place
	std::string* array_of_words; //for storing all words in one place
	std::string user_s_choice; //for storing user's choice
	std::string* results_str; //for storing string results given by each thread in one place
	int* results_int; //for storing integer results given by each thread in one place
	std::string final_result_str; //for final string result
	int final_result_int; //for final int result
	int thread_number = 1;
	int number_of_words = 0;
	int words_per_thread;
	int leftover; //for saving rest of words
	int thread_beginning;
	int i; //for iterate

	file_to_array(array_of_words, &number_of_words); //count and load words from file to array

	std::cout << "Type any word or DNA sequence you want\t";
	std::cin >> user_s_choice;

	do
	{
		std::cout << "\nHow many threads do you want to use? You can choose number from 1 to 64.\t";
		std::cin >> thread_number; //works only for 1 - 64 threads

	} while (thread_number < 1 || thread_number > 64); //checking if user gave correct number of working threads


	words_per_thread = number_of_words / thread_number; //number of words to process for one thread
	leftover = number_of_words % thread_number; //excess of words that I'll add to the last thread

	array_of_threads = new std::thread[thread_number]; //dynamically allocating memory for threads
	results_int = new int[thread_number]; //array of results (smallest editing distances) returned by each thread
	results_str = new std::string[thread_number]; //array of results (most similar words) returned by each thread


	auto start = std::chrono::steady_clock::now(); //starting counting time

	for (i = 0; i < thread_number - 1; ++i)
	{
		thread_beginning = (i + 1) * words_per_thread - words_per_thread; //formula for getting thread_beginning
		array_of_threads[i] = std::thread(search_dictionary_result, user_s_choice, std::ref(array_of_words), thread_beginning, words_per_thread, std::ref(results_int), std::ref(results_str), i, tmp);
	}

	thread_beginning = (i + 1) * words_per_thread - words_per_thread; //formula for getting thread_beginning (for last thread)
	words_per_thread += leftover; //number of words for last thread (there is average number of words per thread plus rest of them

	array_of_threads[thread_number - 1] = std::thread(search_dictionary_result, user_s_choice, std::ref(array_of_words), thread_beginning, words_per_thread, std::ref(results_int), std::ref(results_str), i, tmp);

	for (int i = 0; i < thread_number; ++i) array_of_threads[i].join(); //threads synchronization

	final_result_str = results_str[0];
	final_result_int = results_int[0];
	for (int j = 1; j < thread_number; ++j) //j = 0
	{


		//std::cout << results_int[j] << "\t" << results_str[j] << std::endl;
		if (results_int[j] < final_result_int)
		{
			final_result_int = results_int[j];
			final_result_str = results_str[j];
		}
	}

	auto stop = std::chrono::steady_clock::now(); //stopping counting time

	std::cout << "\n\n\tFinal results: DNA \"" << final_result_str << "\" with editing distance \"" << final_result_int << "\"" << std::endl;

	__int64 time = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count(); //getting final result containing proper time
	std::cout << "\n\nCode executed in " << time << " milliseconds\n\n";

	delete[] results_int;
	delete[] results_str;
	delete[] array_of_words;
	delete[] array_of_threads;

}



int main()
{
	char tmp_c;
	std::cout << "Which dll: \"1\" for cpp, \"2\" for asm.\t";
	std::cin >> tmp_c;

	switch (tmp_c)
	{
	case '1':
	case '2':
	{
		load_program_threads(tmp_c);
		break;
	}
	default:
	{
		std::cout << "No option has been chosen";
		break;
	}
	}

	getchar();
	getchar();
	return 0;
}

