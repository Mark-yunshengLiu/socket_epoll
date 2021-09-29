/**
 * ClassName: thread_task
 * Description: thread task
 * Author: Mark yunsheng.Liu
 * Date: 2021/05/21
 * Version: V1.0
 * QQ:120772981
 **/ 
#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_
#include <list>
#include <mutex>
#include <queue>
#include <atomic>
#include <vector>
#include <string>
#include <thread>  
#include <iostream>
#include <condition_variable>

#include "thread_task.h"
using namespace std;

#define THREAD_POOL_MAX_NUM 128

class thread_pool
{ 
public: 
    void init(unsigned int pthdnum, unsigned int timeout);
    void destory();
    void add_task(thread_task ptask);
private:    
    unsigned int thread_timeout;
    condition_variable condition;
    vector<thread> pool;
    queue<thread_task> tasks; 
    atomic<bool> thread_run { true };
    atomic<int> thread_free_num { 0 };   
    void init_thread_pool(unsigned int pthdnum); 
};
#endif