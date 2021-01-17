#pragma once
#include <iostream>

void printBin(int value)
{
	std::cout << "bits(" << value << "): ";

	for (int i = sizeof(int) * 8 - 1; i >= 0; i--)
	{
		int v = value >> i;
		std::cout << (v & 1);
	}

	std::cout << std::endl;
}
