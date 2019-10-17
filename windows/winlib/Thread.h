#pragma once
#include<string>
#define INFINITE -1
class Thread
{
public:
	Thread();
	virtual ~Thread();
	virtual long Run() = 0;

	unsigned long GetId() const
	{
		return m_hThread;
	}
	
	/**
	*如果状态为true则表示线程启动,没有启动成功可以查看m_errInfo
	*/
	bool IsRunning() const
	{
		return m_isRunning;
	}
	///启动线程
	int Start();
	///线程终止
	virtual void Stop(long dwWait = 0);
	
	std::string ErrInfo() const { return m_errInfo; }
private:
	///禁止复制和赋值
	Thread(const Thread&);
	Thread& operator=(const Thread&);
private:
	friend void* _ou_thread_proc(void* param);
	pthread_t m_hThread;
	pthread_mutex_t m_Mutex;
	bool m_isRunning;
	void *m_threadParam;
	std::string m_errInfo;
    bool m_detach;
};

