#pragma once
//#include <windows.h>
#include<string>

//struct BaseCache
//{
//	virtual UINT32  ReadData(CodeInfo* pCode, UINT32& nDateInFile, char* pBuf, UINT32 nBufLenth);
//	virtual int   WriteData(CodeInfo* pCode, UINT32 nDateNow, const char* pBuf, UINT32 nBufLenth);
//};


struct IBaseCacheMMF
{
	virtual UINT64     GetFileSize()  = 0;
	virtual BOOL       Read(UINT64 nOfferSet, char* pBuffer, UINT32 nBufLenth) = 0;
	virtual BOOL       Write(UINT64 nOfferSet, const char* pBuffer, UINT32 nBufLenth) = 0;
	virtual std::string     getFilePath() = 0;
	virtual BOOL       ClearFile() = 0;   // Çå¿ÕÎÄ¼þ

	//virtual BOOL       CreateMap(BOOL bClearExist) = 0;
	//virtual BOOL       ReleaseMap()=0;
	//virtual BOOL       ExpandMap(const UINT32& nExpandSize)=0;
};

