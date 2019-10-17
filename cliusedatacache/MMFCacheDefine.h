//#include"CodeInfo.h"
//#include "hsstructnew.h"
#include<windows.h>
// 定义

#define FILE_VERSION          0x0001  // 版本号



struct MMFCacheIndexFileHead
{
	UINT32		m_nVersion;          // 版本号
	UINT32		m_nIndexCount;       // 索引数当前数量
	UINT32		m_nIndexCapability;  // 单个索引容量
	UINT32		m_nPageCapability;   // 单页容量 可放结构体数量
	UINT32		m_nPageNo;           // 当前页数
};

template<class CacheType>
struct MMFCachePageInfo
{
	UINT32		  m_nPageNo;  		  // 编号
	CacheType	  m_code;     		  // 存放的代码
	UINT32		  m_nCount;    		  // 页中存放的日线个数
	UINT32		  m_nOffSet;  		  // 该页的偏移位置
};