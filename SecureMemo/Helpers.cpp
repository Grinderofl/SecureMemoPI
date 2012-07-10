#include "Helpers.h"
#include "Base64.h"

#include <time.h>
#include <random>

std::string Helpers::GenerateRandomString(int length)
{
	unsigned char* arr = new unsigned char[length];
	
	srand(time(NULL));
	int random = 0;

	for(int i = 0; i < length; i++)
	{
		random = rand() % 255;
		arr[i] = (char)random;
	}

	Base64 b;
	return b.Encode(arr, length);
}