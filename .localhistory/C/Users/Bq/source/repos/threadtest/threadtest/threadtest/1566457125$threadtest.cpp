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

//#include "pch.h"
//#include <algorithm>
//
//std::mutex mtx;
//
//void add(int &num, int &sum)
//{
//	while (true)
//	{
//		std::lock_guard<std::mutex> lock(mtx);
//		if (num < 100)
//		{
//			num += 1;
//			sum += num;
//		}
//		else
//		{
//			break;
//		}
//	}
//}
//
//int main()
//{
//	int sum = 0;
//	int num = 0;
//	std::vector<std::thread> ver;
//	std::array<int, 4> arrayInt = { 1, 2, 3, 4 };
//	std::tuple<int, std::string, char> cct = { 1, "2", '3' };
//	auto ccs = std::tie("11", "22", "33");
//	auto css = std::make_tuple("11", "23", 1);
//	std::cout << std::get<0>(ccs) << std::endl;
//	std::cout << std::get<1>(ccs) << std::endl;
//	std::cout << std::get<2>(ccs) << std::endl;
//
//	std::cout << std::get<0>(css) << std::endl;
//	std::cout << std::get<1>(css) << std::endl;
//	std::cout << std::get<2>(css) << std::endl;
//
//	std::lock_guard<std::mutex> ccsa(mtx);
//	std::unique_lock<std::mutex> ccsss(mtx);
//	ccsss.unlock();
//
//	//for (auto &t : arrayInt)
//	//{
//	//	std::cout << t << std::endl;
//	//}
//
//	//for (int i = 0; i < 20; i++)
//	//{
//	//	std::thread t = std::thread(add, std::ref(num), std::ref(sum));
//	//	//ver.push_back(std::move(t));
//	//	t.detach();
//	//}
//	//std::cout << sum << std::endl;
//
//	//while (true)
//	//{
//	//	std::this_thread::sleep_for(std::chrono::seconds(2));
//	//}
//
//	return 0;
//}

#include "pch.h"
#include <algorithm>
#include <regex>

//std::mutex mtx;
//
//static int num = 0;
//static int sum = 0;
//
//void add()
//{
//	//std::lock_guard<std::mutex> glock(mtx);
//	if (num < 5)
//	{
//		num += 1;
//		sum += num;
//	}
//}
//
//int main()
//{
//	//std::vector<std::thread *> threads;
//
//	//for (int i = 0; i < 5; i++)
//	//{
//	//	std::thread *t = new std::thread(add);
//	//	threads.emplace_back(t);
//	//}
//
//	//std::for_each(threads.begin(), threads.end(), [](std::thread *t) {t->detach(); });
//
//	//std::cout << "sum" << sum << std::endl;
//
//	//std::string fnames[] = { "foo.txt", "bar.txt", "test", "a0.txt", "AAA.txt" };
//	//std::regex txt_regex(R("[A-Z]+[0-9]+.txt"));
//	//for (const auto &fname : fnames)
//	//	std::cout << fname << ": " << std::regex_match(fname, txt_regex) << std::endl;
//	return 0;
//}

//int sum(int a, int b)
//{
//	std::this_thread::sleep_for(std::chrono::seconds(5));
//	return a + b;
//}
//
//int main()
//{
//	std::packaged_task<int(int, int)> task(sum);
//	std::future<int> future = task.get_future();
//	std::thread t(std::move(task), 1, 2);
//	while (1)
//	{
//		std::this_thread::sleep_for(std::chrono::seconds(1));
//		std::cout << "1 + 2:" << future.get() << std::endl;
//	}
//
//	t.join();
//	return 0;
//}

std::deque<int> q;
std::mutex mtx;
std::condition_variable c;

void function_1()
{
	int count = 50;
	while (count > 0)
	{
		std::unique_lock<std::mutex> locker(mtx);
		q.push_back(count);
		locker.unlock();
		c.notify_one();
		//std::this_thread::sleep_for(std::chrono::seconds(1));
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		count--;
	}
}

void function_2()
{
	int data = 0;
	while (data != 1)
	{
		std::unique_lock<std::mutex> locker(mtx);
		c.wait(locker, []() {return !q.empty(); });
		data = q.back();
		q.pop_back();
		locker.unlock();
		std::cout << "thread::" << std::this_thread::get_id() << " got a value from t1:" << data << std::endl;
	}
}

int main()
{
	std::thread t1(function_1);
	std::vector<std::thread> threads;

	for (int i = 00; i < 10; i++)
	{
		std::thread t2(function_2);
		threads.emplace_back(std::move(t2));
	}
	t1.join();

	std::for_each(threads.begin(), threads.end(), [](std::thread t) {t.join(); });
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	return 0;
}