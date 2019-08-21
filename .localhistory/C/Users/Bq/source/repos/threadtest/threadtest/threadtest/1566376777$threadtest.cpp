//#include "pch.h"
//#include <iostream>
//#include <condition_variable>
//#include <thread>
//
//std::condition_variable cv;
//std::mutex mtx;
//bool ready = false;
//
//void do_print_id(int id)
//{
//	std::unique_lock<std::mutex> lck(mtx);
//	while (!ready)
//	{
//		cv.wait(lck);
//	}
//	std::cout << "thread " << id << std::endl;
//}
//
//void go()
//{
//	std::unique_lock<std::mutex> lck(mtx);
//	ready = true;
//	//cv.notify_one();
//	cv.notify_all();
//}
//
//int main()
//{
//	std::thread threads[10];
//
//	for (int i = 0; i < 10; i++)
//	{
//		threads[i] = std::thread(do_print_id, i);
//	}
//
//	std::cout << "10 threads ready to race ...." << std::endl;
//	go();
//
//	for (auto &th : threads)
//	{
//		if (th.joinable())
//		{
//			th.join();
//		}
//	}
//
//	return 0;
//}
//

#include "pch.h"
#include <algorithm>

std::mutex mtx;

void add(int &num, int &sum)
{
	while (true)
	{
		std::lock_guard<std::mutex> lock(mtx);
		if (num < 100)
		{
			num += 1;
			sum += num;
		}
		else
		{
			break;
		}
	}
}

int main()
{
	int sum = 0;
	int num = 0;
	std::vector<std::thread> ver;
	for (int i = 0; i < 20; i++)
	{
		std::thread t = std::thread(add, num++, sum++);
		ver.push_back(std::move(t));
	}

	std::for_each(ver.begin(), ver.end(), [](std::thread t) {t->join; });
	std::cout << sum << std::endl;
	return 0;
}