#include "Thread.h"
#include<stdio.h>
#include<string.h>

void *_ou_thread_proc(void *param)
{
	Thread* tp = (Thread*)param;
	tp->Run();
	return param;
}


Thread::Thread():m_hThread(0), m_threadParam(NULL),m_detach(true)
{
	
}


Thread::~Thread()
{
}

int Thread::Start()
{
    //printf("new thread");
	int ret = pthread_create(&m_hThread, NULL, _ou_thread_proc, this);
	if (!ret)
	{
        if(m_detach) pthread_detach(m_hThread);
		m_isRunning = true;
	}
	else {
		m_isRunning = false;
		m_errInfo=strerror(ret);
        printf(m_errInfo.c_str());
	}
}

void Thread::Stop(long wait_time /*= INFINITE*/)
{
    if(0==wait_time)
    {
         pthread_cancel(m_hThread);
         printf("thread cancel");      
    }
    else{
         pthread_join(m_hThread,NULL);
         printf("thread join");      
    }
}

