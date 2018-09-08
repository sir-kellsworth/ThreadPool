/**********************************************************************
 *
 * Filename:    ThreadPool.h
 * 
 * Description: Definition of ThreadPool class
 *
 * Notes:
 *
 * 
 * Copyright (c) 2018 by Kelly Klein.  This software is placed into
 * the public domain and may be used for any purpose.  However, this
 * notice must not be changed or removed and no warranty is either
 * expressed or implied by its publication or distribution.
 **********************************************************************/

#ifndef ThreadPool_h
#define ThreadPool_h

#include <thread>
#include <vector>
#include <functional>
#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>

class ThreadPool{
public:
	/*
	create the pool with the number of threads wanted.
	if numThreads is greated that the MAX_THREADS, then
	the MAX_THREADS is used
	*/
	ThreadPool(int numThreads);

	/*
	pushes a new function to run on another thread.
	I couldnt get it to work with the std::function.
	maybe you can but I would recomend using lambda functions.
	You can push as many functions as you want but only
	numThreads will run at a time
	*/
	void push(std::function<void()> m);

	/*
	blocks until all the threads are done running
	*/
	void join();

	/*
	Esential for stopping the ThreadPool. It stops
	all the threads from running
	*/
	void kill();

	/*
	Seems kinda silly but if you need to resize the ThreadPool
	then use this method. Still cannot allow more threads than MAX_THREADS
	*/
	void setSize(int numThreads);
private:
	void threadRun(int threadNum);

	std::vector<std::thread> workers;
	int maxThreads;
	bool running;
	std::queue<std::function<void()>> queue;
	int waiting;
	std::mutex lock;
	std::condition_variable cv;

	//change this to the max number of cores you have.
	//for example, my computer has 8 cores and 16 with hyperthreading.
	const int MAX_THREADS = 16;
	
};

#endif
