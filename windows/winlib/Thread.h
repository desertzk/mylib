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
	*���״̬Ϊtrue���ʾ�߳�����,û�������ɹ����Բ鿴m_errInfo
	*/
	bool IsRunning() const
	{
		return m_isRunning;
	}
	///�����߳�
	int Start();
	///�߳���ֹ
	virtual void Stop(long dwWait = 0);
	
	std::string ErrInfo() const { return m_errInfo; }
private:
	///��ֹ���ƺ͸�ֵ
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

