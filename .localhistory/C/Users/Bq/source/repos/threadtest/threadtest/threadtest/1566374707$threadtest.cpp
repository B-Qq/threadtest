﻿#include "pch.h"
#include <iostream>
#include <condition_variable>
#include <thread>

std::condition_variable cv;
std::mutex mtx;
bool ready = false;

void do_print_id(int id)
{
	std::unique_lock<std::mutex> lck(mtx);
	while (!ready)
	{
		cv.wait(lck);
	}
	std::cout << "thread " << id << std::endl;
}

void go()
{
	std::unique_lock<std::mutex> lck(mtx);
	ready = true;
	//cv.notify_one();
	cv.notify_all();
}

int main()
{
	std::thread threads[10];

	for (int i = 0; i < 10; i++)
	{
		threads[i] = std::thread(do_print_id, i);
	}

	std::cout << "10 threads ready to race ...." << std::endl;
	go();

	for (auto &th : threads)
	{
		if (th.joinable())
		{
			th.join();
		}
	}
	return 0;
}