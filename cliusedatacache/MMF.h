#pragma once
// 内存映射文件操作类
#include<windows.h>
#include<string>
class CMMF 
{
public:
	CMMF(const char *lpszFilePath, unsigned long long extendSize= 1024 * 1024 * 10, unsigned long long initSize= 1024 * 1024);
	~CMMF(void);

	unsigned long long     GetFileSize() const { return m_nFileSize; }
	bool       Read(unsigned long long nOfferSet, char* pBuffer, unsigned int nBufLenth);
	bool       Write(unsigned long long nOfferSet, const char* pBuffer, unsigned int nBufLenth);

	bool       ClearFile();   // 清空文件
protected:
	bool       CreateMap(bool bClearExist = FALSE);
	bool       ReleaseMap();
	bool       ExpandMap(const unsigned int& nExpandSize = 1024 * 1024 * 10);

private:
	std::string    m_strFilePath;
	HANDLE     m_hFileMap;
	unsigned long long m_extendSize;
	unsigned long long m_initSize;
	unsigned long long     m_nFileSize;
	unsigned int     m_nAllocationGranularity;
};
