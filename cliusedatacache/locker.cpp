#include "Locker.h"
Locker::Locker()
{
	InitializeCriticalSection(&m_CritSect);
	m_TotalLockCount = 0;
}

Locker::~Locker()
{
	DeleteCriticalSection(&m_CritSect);
}

void Locker::Lock()
{
	EnterCriticalSection(&m_CritSect);
	++m_TotalLockCount;
}

void Locker::UnLock()
{
	LeaveCriticalSection(&m_CritSect);
	--m_TotalLockCount;
}

bool Locker::Locked()
{
	if (m_TotalLockCount != 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}
