﻿#include "pch.h"
#include <iostream>
#include <condition_variable>

std::condition_variable cv;
std::mutex mtx;
bool ready = fasle;

void do_print_id(int id)
{
	std::unique_lock<std::mutex> lck(mtx);
	while (!ready)
	{
		cv.wait(lck);
	}
	std::cout << "thread " << id << std::endl;
}

int main()
{
	std::cout << "Hello World!\n";
}