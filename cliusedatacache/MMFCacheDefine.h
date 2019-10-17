//#include"CodeInfo.h"
//#include "hsstructnew.h"
#include<windows.h>
// ����

#define FILE_VERSION          0x0001  // �汾��



struct MMFCacheIndexFileHead
{
	UINT32		m_nVersion;          // �汾��
	UINT32		m_nIndexCount;       // ��������ǰ����
	UINT32		m_nIndexCapability;  // ������������
	UINT32		m_nPageCapability;   // ��ҳ���� �ɷŽṹ������
	UINT32		m_nPageNo;           // ��ǰҳ��
};

template<class CacheType>
struct MMFCachePageInfo
{
	UINT32		  m_nPageNo;  		  // ���
	CacheType	  m_code;     		  // ��ŵĴ���
	UINT32		  m_nCount;    		  // ҳ�д�ŵ����߸���
	UINT32		  m_nOffSet;  		  // ��ҳ��ƫ��λ��
};