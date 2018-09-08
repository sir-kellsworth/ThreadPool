/**********************************************************************
 *
 * Filename:    ThreadPool.cpp
 * 
 * Description: Implementation of ThreadPool class
 *
 * Notes:
 *
 * 
 * Copyright (c) 2018 by Kelly Klein.  This software is placed into
 * the public domain and may be used for any purpose.  However, this
 * notice must not be changed or removed and no warranty is either
 * expressed or implied by its publication or distribution.
 **********************************************************************/

#include "ThreadPool.h"

ThreadPool::ThreadPool(int numThreads){
	if(numThreads > MAX_THREADS){
		MAX_THREADS = 16;
	}else{
		maxThreads = numThreads;
	}
	running = true;
	waiting = 0;
	workers.resize(maxThreads);
	for(int i = 0; i < workers.capacity(); i++){
		workers[i] = std::thread([this,i](){
				threadRun(i);
			});
	}
}

void ThreadPool::push(std::function<void()> m){
	std::unique_lock<std::mutex> lk(lock);
	queue.push(m);
	cv.notify_all();
}

void ThreadPool::join(){
	std::unique_lock<std::mutex> lk(lock);
	cv.wait(lk,[this]{return (waiting == maxThreads && queue.empty());});
}

void ThreadPool::kill(){
	running = false;
	cv.notify_all();
	for(int i = 0; i < workers.size(); i++){
		workers[i].join();
	}
}

void ThreadPool::setSize(int numThreads){
	maxThreads = numThreads;
	workers.resize(maxThreads);
	for(int i = 0; i < workers.capacity(); i++){
		workers[i] = std::thread([this,i](){
				threadRun(i);
			});
	}
}

void ThreadPool::threadRun(int threadNum){
	while(true){
		std::function<void()> func;
		{
			std::unique_lock<std::mutex> lk(lock);
			waiting++;
			cv.notify_all();
			while(running && queue.empty()){
				cv.wait(lk);
			}

			if(!running){
				return;
			}

			waiting--;
			func = queue.front();
			queue.pop();
			cv.notify_all();
		}
		func();
	}
}
