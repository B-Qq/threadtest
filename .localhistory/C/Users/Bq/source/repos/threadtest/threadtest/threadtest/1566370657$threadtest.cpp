#include "pch.h"
#include <iostream>
#include <condition_variable>

int main()
{
	std::condition_variable cv;
	std::mutex mtx;
	bool ready = fasle;
	std::cout << "Hello World!\n";
}