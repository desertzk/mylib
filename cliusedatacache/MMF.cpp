//#include "StdAfx.h"
#include<cassert>
#include "MMF.h"
#include<iostream>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace std;

CMMF::CMMF(const char *lpszFilePath, unsigned long long extendSize, unsigned long long initSize):
m_strFilePath(lpszFilePath),
m_hFileMap(NULL),
m_nFileSize(0),
m_extendSize(extendSize),
m_initSize(initSize)
{
	SYSTEM_INFO sinf;
	GetSystemInfo(&sinf);
	m_nAllocationGranularity = sinf.dwAllocationGranularity;
	if (m_initSize < m_nAllocationGranularity)
		m_initSize = m_nAllocationGranularity;
	CreateMap();
}

CMMF::~CMMF(void)
{
	ReleaseMap();
}

bool CMMF::Read(unsigned long long nOfferSet, char* pBuffer, unsigned int nBufLenth)
{
	if ( nOfferSet + nBufLenth > m_nFileSize )
	{// 超过当前大小
		return FALSE;
	}
	
	unsigned long long nMapOfferSet = nOfferSet / m_nAllocationGranularity * m_nAllocationGranularity;
	unsigned int nMapLenth = (nBufLenth + (nOfferSet - nMapOfferSet) + m_nAllocationGranularity - 1) / m_nAllocationGranularity * m_nAllocationGranularity;

	LPVOID lpMapViewStart = MapViewOfFile(m_hFileMap, 
		FILE_MAP_WRITE | FILE_MAP_READ, 
		(DWORD)(nMapOfferSet >> 32),
		(DWORD)(nMapOfferSet & 0xFFFFFFFF), 
		nMapLenth);
	
	if ( lpMapViewStart )
	{
		memcpy(pBuffer, (char*)lpMapViewStart + nOfferSet - nMapOfferSet, nBufLenth);
		
		UnmapViewOfFile(lpMapViewStart);
		return TRUE;
	}
	assert(FALSE);
	DWORD dwErr = GetLastError();
	return FALSE;
}

bool CMMF::Write(unsigned long long nOfferSet, const char* pBuffer, unsigned int nBufLenth)
{
	if ( pBuffer == NULL || nBufLenth == 0 )
	{
		return TRUE;
	}
	else if ( nOfferSet + nBufLenth > m_nFileSize )
	{// 需要扩大文件
		ExpandMap(max(m_extendSize, nOfferSet + nBufLenth - m_nFileSize));
	}

	unsigned long long nMapOfferSet = nOfferSet / m_nAllocationGranularity * m_nAllocationGranularity;
	unsigned int nMapLenth = (nBufLenth + (nOfferSet - nMapOfferSet) + m_nAllocationGranularity - 1) / m_nAllocationGranularity * m_nAllocationGranularity;

	LPVOID lpMapViewStart = MapViewOfFile(m_hFileMap, 
		FILE_MAP_WRITE | FILE_MAP_READ, 
		(DWORD)(nMapOfferSet >> 32),
		(DWORD)(nMapOfferSet & 0xFFFFFFFF), 
		nMapLenth);

	if ( lpMapViewStart )
	{
		memcpy((char*)lpMapViewStart + nOfferSet - nMapOfferSet, pBuffer, nBufLenth);

		UnmapViewOfFile(lpMapViewStart);
		return TRUE;
	}
	assert(FALSE);
	DWORD dwErr = GetLastError();
	return FALSE;
}

bool CMMF::ClearFile()
{
	ReleaseMap();
	CreateMap(TRUE);

	return TRUE;
}

bool CMMF::CreateMap(bool bClearExist/* = FALSE*/)
{
	HANDLE hfile=CreateFile(m_strFilePath.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ| FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hfile== INVALID_HANDLE_VALUE)
	{
		cout << GetLastError() << endl;
		return FALSE;
	}
	struct stat st;
	stat(m_strFilePath.c_str(), &st);
	_off_t filesize = st.st_size;
	if (hfile)
	{
		m_nFileSize = max(m_initSize, filesize);
		m_hFileMap = CreateFileMapping(hfile,
			NULL, 
			PAGE_READWRITE, 
			(DWORD)(m_nFileSize >> 32), 
			(DWORD)(m_nFileSize & 0xFFFFFFFF), 
			NULL);

		assert(m_hFileMap != NULL);
		CloseHandle(hfile);
	}
	else
	{
		cout << GetLastError() << endl;
		assert(FALSE);
	
	}
	return (m_hFileMap != NULL);
}

bool CMMF::ReleaseMap()
{
	if ( m_hFileMap )
	{
		CloseHandle(m_hFileMap);
	}

	return TRUE;
}

bool CMMF::ExpandMap(const unsigned int& nExpandSize)
{
	m_nFileSize += nExpandSize; // 大小增加
	CloseHandle(m_hFileMap);    // 视图句柄关闭
	HANDLE hfile = CreateFile(m_strFilePath.c_str(), GENERIC_READ | GENERIC_WRITE, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	struct stat st;
	stat(m_strFilePath.c_str(), &st);
	_off_t filesize = st.st_size;
	if (hfile!= INVALID_HANDLE_VALUE)
	{
		m_hFileMap = CreateFileMapping(hfile,
			NULL, 
			PAGE_READWRITE, 
			(DWORD)(m_nFileSize >> 32), 
			(DWORD)(m_nFileSize & 0xFFFFFFFF), 
			NULL);

		CloseHandle(hfile);
	}
	else {
		cout << GetLastError() << endl;
	}
	return (m_hFileMap != NULL);
}




