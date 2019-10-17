#ifndef __LOCKER_H
#define __LOCKER_H
#define WIN32_LEAN_AND_MEAN // ��ֹwindows.h ���� winsock.h
#include <Windows.h>
class Locker
{
public:
	Locker();
	~Locker();
	void Lock();
	void UnLock();
	bool Locked();
private:
	CRITICAL_SECTION m_CritSect;
	int m_TotalLockCount;
};

#endif //__LOCK_H