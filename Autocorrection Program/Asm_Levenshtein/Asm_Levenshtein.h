#pragma once
#ifdef ASM_LEVENSHTEIN_EXPORTS
#define ASM_LEVENSHTEIN_API __declspec(dllexport)
#else
#define ASM_LEVENSHTEIN_API __declspec(dllimport)
#endif

extern "C"
{
	ASM_LEVENSHTEIN_API int _stdcall testMMX();
}