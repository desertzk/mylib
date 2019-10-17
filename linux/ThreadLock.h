#pragma once
#include<pthread.h>
#include<stdio.h>


class ThreadMutex
{
public:
    ThreadMutex():m_hmutex(0)
    {
        if(pthread_mutex_init(&m_hmutex,NULL))
        {
            printf("pthread_mutex_init error");
        }
    }
    
    virtual ~ThreadMutex()
    {
        if(pthread_mutex_destroy(&m_hmutex))
        {
            printf("pthread_mutex_destroy");
        }
    }

public:
    int Lock()
    {
        return pthread_mutex_lock(&m_hmutex);
    }

    int UnLock()
    {
        return pthread_mutex_unlock(&m_hmutex);
    }
private:
    pthread_mutex_t m_hmutex;
}

class ThreadMutexGuard
{
public:
    explicit ThreadMutexGuard(pthread_mutex_t *pmutex):m_mutex(pmutex)
    {
        if(m_mutex->Lock())
        {
            printf("lock failed");    
        }        
    }

    ~ThreadMutexGuard()
    {
        if(m_mutex->UnLock())
        {
            printf("unlock failed");
        }
    }
private:
    ThreadMutex *m_mutex;
}
