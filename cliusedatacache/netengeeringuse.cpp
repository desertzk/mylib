//#include "stdafx.h"
#include<iostream>
#include<cstdlib>
#include"NetEngineInterface.h"
#include"WinnerApplication.h"
#include"hsds_comudata.h"
//-------------------net research-----------
/**/
typedef int  (WINAPI *InitEntity)();
//释放插件
typedef int  (WINAPI *UninitEntity)();


typedef int   (WINAPI *OnFrameNotify)(int nFlag);

typedef  void*  (WINAPI *GetServiceObject)(const char* szName, const char* szPrefix);


InitEntity m_init;
UninitEntity m_uninit;
OnFrameNotify m_notify;
GetServiceObject m_getobj;
OnConnectNotify		m_pfnOnConnectNotify;


BOOL WINAPI sFn_OnConnectNotify(ConnectNotify* pszConnectNotify)
{
	printf("sFn_OnConnectNotify");

	return FALSE;
}

extern "C"
{
	HMODULE WINAPI  HswGetModuleHandle(LPCTSTR lpszModuleName)
	{
		AFX_MANAGE_STATE(AfxGetAppModuleState());
		return ::LoadLibrary(lpszModuleName);
	}
}



void  getMethod()
{
	HMODULE m_hdll = ::LoadLibrary("NetEngine.dll");
	if (m_hdll == NULL)
	{
		cout << GetLastError() << endl;
		FreeLibrary(m_hdll);
	}
	m_init = (InitEntity)::GetProcAddress(m_hdll, "InitEntity");
	if (m_init == NULL)
	{
		//PHSLOG->hsWriteError("Get HQFUNC ERROR!");
		return;
	}
	m_uninit = (UninitEntity)::GetProcAddress(m_hdll, "UninitEntity");
	if (m_uninit == NULL)
	{
		//PHSLOG->hsWriteError("Get HQFUNC ERROR!");
		return;
	}
	m_notify = (OnFrameNotify)::GetProcAddress(m_hdll, "OnFrameNotify");
	if (m_notify == NULL)
	{
		//PHSLOG->hsWriteError("Get HQFUNC ERROR!");
		return;
	}

	m_getobj = (GetServiceObject)::GetProcAddress(m_hdll, "GetServiceObject");
	if (m_getobj == NULL)
	{
		//PHSLOG->hsWriteError("Get HQFUNC ERROR!");
		cout << GetLastError() << endl;
		return;
	}

}
//CObjectManager       g_objectManager;       // 对象管理器
//void*  WINAPI HswGetObject(LPCTSTR lpszObjectLocation, LPCTSTR lpszPrefix = NULL)
//{
//	AFX_MANAGE_STATE(AfxGetAppModuleState());
//	return g_objectManager.GetObj(lpszObjectLocation, lpszPrefix);
//}

void*  WINAPI HswGetObject(const char *obj)
{
	return m_getobj(obj, "");
}


int main()
{
	getMethod();
	m_init();
	IChannelManager *m_pChannelManager = (IChannelManager *)HswGetObject("ChannelManager");
	m_pfnOnConnectNotify = sFn_OnConnectNotify;
	if (m_pChannelManager != NULL)
	{
		m_pChannelManager->RegisterNotify(m_pfnOnConnectNotify);
	}
	IChannels* m_pChannels = (IChannels*)m_getobj("Channels", "");

	char *strServerName = "阿里云线路1";

	CommInfo *pComm = new CommInfo();
	pComm->m_cType = CEV_Connect_HQ;
	strcpy(pComm->m_strServerID, "阿里云线路1");
	strcpy(pComm->m_strServerIP, "112.124.211.83");
	pComm->m_nPort = 443;
	pComm->m_nNewworkType = 0;
	ProxyInfo *proxyinfo = new ProxyInfo;
	memset(proxyinfo, 0, sizeof(ProxyInfo));
	proxyinfo->m_nOptions = Socks4;
	strcpy(proxyinfo->m_strUseChannelIP, "127.0.0.1");
	proxyinfo->m_nUsePort = 11111;
	m_pChannelManager->SetSites(pComm, 1, proxyinfo);




	long lConnectHandle = m_pChannelManager->CreateConnector(CEV_Connect_HQ, strServerName);

	int nCodeCount = sizeof(ReqLogin) / sizeof(CodeInfo) + ((sizeof(ReqLogin) % sizeof(CodeInfo)) ? 1 : 0);
	int lRetLen = sizeof(AskData) + sizeof(CodeInfo)*(nCodeCount - 1);

	char* pAskBuffer = new char[lRetLen];
	AskData* pAskData = (AskData*)pAskBuffer;
	memset(pAskData, 0, lRetLen);

	pAskData->m_nType = RT_LOGIN;
	pAskData->m_nSize = nCodeCount;
	ReqLogin* pLogin = (ReqLogin*)pAskData->m_pCode;
	pAskData->m_nOption = Login_Option_Password;
	pAskData->m_lKey = LOGIN_KEY;  // 客户端内部版本

	strncpy(pLogin->m_szPWD, "1", min(sizeof(pLogin->m_szPWD), 1));
	strncpy(pLogin->m_szUser, "", sizeof(pLogin->m_szUser));

	char* szBuf = NULL;
	UINT nLen = 0;
	int nRetVal = m_pChannels->SendRcv(lConnectHandle, (const char *)pAskData, lRetLen, 15000, szBuf, nLen);
	if (szBuf)
	{
		AnsLogin* pAnsLogin = (AnsLogin*)szBuf;
		cout << pAnsLogin->m_szRet << endl;

	}


	//取服务器信息
	int nAskSvrInfoLen = sizeof(AskData);
	char* pAskSvrBuffer = new char[nAskSvrInfoLen];
	AskData* pAskSvrInfo = (AskData*)pAskSvrBuffer;
	memset(pAskSvrInfo, 0, nAskSvrInfoLen);
	pAskSvrInfo->m_nType = RT_SERVERINFO;
	pAskSvrInfo->m_lKey = LOGIN_KEY;
	//m_pChannels->GetPacketID(this->GetConnectHandle());
	if (m_pChannels->SendRcv(lConnectHandle, (char*)pAskSvrInfo, nAskSvrInfoLen, 15000, szBuf, nLen) != -1)
	{
		if (szBuf)
		{
			AnsServerInfo* pServerInfo = (AnsServerInfo*)szBuf;
			cout << pServerInfo->m_pName << endl;
			//m_pChannels->FreeMemory(m_lConnectHandle, szBuf);
		}
	}
	delete[] pAskSvrBuffer;


	//取k





	//if (nRetVal == 0)
	//{
	//	nLen = uLen;
	//	return pszRetBuffer;
	//}
	//else
	//{
	//	uLen = 0;//m_pChannels->GetLastEorror(lConnectHandle);
	//	return NULL;
	//}
	cin.get();
}