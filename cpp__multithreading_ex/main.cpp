// Threading2.cpp : Defines the entry point for the console application.
//
#include <iostream>           // std::cout
#include <fstream>
#include <string>
#include <thread>             // std::thread
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable
#include <future>			  // std::future std::promise
#include <algorithm>
#include <chrono>
#include <queue>
#include <array>
#include "ConsoleColor.h"

using namespace std;

int a, b, c;
mutex mx, mtx, mque;
condition_variable cv;
bool ready = false;

queue<int> q;

void RandomDelay(int nrand)
{
	// simulates a delay in seconds.
	this_thread::sleep_for(chrono::seconds(rand() % nrand + 1));
}

void producer(int quantity)
{
	for (int x = 0; x<quantity; ++x)
	{
		RandomDelay(2);
		mque.lock();
		q.push(x);
		mque.unlock();
		cout << blue << this_thread::get_id() << " Producer: element " << x << " queued." << endl;
		cv.notify_all();
	}
}

void consumer()
{
	unique_lock<mutex> lck(mx);
	int failed_attempts = 0;
	while (true)
	{
		mque.lock();
		if (q.size())
		{
			int element = q.front();
			q.pop();
			mque.unlock();
			failed_attempts = 0;
			cout << yellow << this_thread::get_id() << " Consumer: retrieving " << element << " from queue." << endl;
			RandomDelay(3);
		}
		else
		{
			mque.unlock();
			if (++failed_attempts >1)
			{
				cout << yellow << this_thread::get_id() << " Consumer: two consecutive failed attempts -> Exiting." << endl;
				break;
			}
			else
			{
				cout << yellow << this_thread::get_id() << " Consumer: queue empty -> going to sleep." << endl;
				cv.wait_for(lck, chrono::seconds(2));
			}
		}
	}
}

void Race(ostream& color(ostream &s), int nvalues)
{
	for (int x=0; x<100; x++)
		cout << color << x;
}

void NoRace(ostream& color(ostream &s), int nvalues)
{
	mtx.lock();
	for (int x=0; x<100; x++)
		cout << color << x;
	mtx.unlock();
}

int syncDouble(int value)
{
	cout << yellow << "syncDouble::value " << value << endl;
	return value * value;
}

void printCV(int tid)
{
	unique_lock<mutex> lck(mtx);
	cout << green << "thread " << tid << " waiting...\n";
	while (!ready) cv.wait(lck);  // comment out this line
	// ...
	cout << "thread " << tid << '\n';
}

void startCV()
{
	unique_lock<mutex> lck(mtx);
	ready = true;
	cv.notify_all();
}

void printFuture(future<int>& fut)
{
	int x = fut.get();
	cout << blue << "printFuture - value: " << x << '\n';
}

// Condition variables are synchronization primitives that enable
// threads to wait until a particular condition occurs. Condition
// variables are user-mode objects that cannot be shared across processes.
void ConditionalVariable()
{
	array<thread, 10> threads;
	// start 10 threads:
	for (int i = 0; i<threads.size(); ++i)
		threads[i] = thread(printCV, i);

	cout << yellow << "threads ready to race...\n";
	startCV();	// go!

	for (auto& th : threads) th.join();
}

// C++11 offers future and promise for returning a value from a task
// spawned on a separate thread and packaged_task to help launch tasks.
// The important point about future and promise is that they enable a
// transfer of a value between two tasks without explicit use of a lock;
// "the system" implements the transfer efficiently.
void FuturePromise()
{
	promise<int> prom;                      // create promise
	future<int> fut = prom.get_future();    // engagement with future
	thread th1(printFuture, ref(fut));  // send future to new thread
	RandomDelay(2);
	prom.set_value(123);					// fulfill promise
	RandomDelay(2);
	th1.join();			// (synchronizes with getting the future)
}

// The template function async runs the function asynchronously
// (potentially in a separate thread which may be part of a thread pool)
// and returns a std::future that will eventually hold the result of that
// function call.
void Async()
{
	future<int> r1 = async(launch::async,syncDouble,2);
	future<int> r2 = async(launch::async,syncDouble,4);
	future<int> r3 = async(launch::async,syncDouble,8);

	cout << "r1: " << r1.get() << endl;
	cout << "r2: " << r2.get() << endl;
	cout << "r3: " << r3.get() << endl;
	cout << endl;
}

// A race condition is a situation in which two or more threads
// or processes are reading or writing some shared data, and the
// final result depends on the timing of how the threads are scheduled.
void RaceCondition()
{
	thread thd1(Race,yellow,100);
	thread thd2(Race,green,100);
	thread thd3(Race,blue,100);
	thd1.join();
	thd2.join();
	thd3.join();

	thread thdA(NoRace,yellow,100);
	thread thdB(NoRace,green,100);
	thread thdC(NoRace,blue,100);
	thdA.join();
	thdB.join();
	thdC.join();
}

// A classic concurrent programming design pattern is producer-consumer,
// where processes are designated as either producers or consumers.
// The producers are responsible for adding to some shared data structure
// and the consumers are responsible for removing from that structure.
// Only one party, either a single producer or a single consumer,
// can access the structure at any given time.
void ProducerConsumer()
{
	thread thd(consumer);
	producer(10);
	thd.join();
}

int main()
{
	cout << white << "=-=-= Condition Variable\n";
	ConditionalVariable();
	cout << white << "\n=-=-= FuturePromise\n";
	FuturePromise();
	cout << white << "\n=-=-= Async\n";
	Async();
	cout << white << "\n=-=-= Race Condition\n";
	RaceCondition();
	cout << white << "\n=-=-= Producer Consumer\n";
	ProducerConsumer();

	return 0;
}
