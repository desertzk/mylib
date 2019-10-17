
#include<iostream>
#include<cstdlib>
#include"MMFCacheEx.hpp"
#include"KlineCacheManage.h"
#include<unordered_map>

//#include"ObjectManager.h"
//#include "log4cplus/logger.h"
//#include "log4cplus/fileappender.h"
//#include "log4cplus/loglevel.h"
//#include "log4cplus/configurator.h"
using namespace std;




struct test
{
	char str[1024];
	double dd;
	int i;
};


void main()
{
	//using namespace cache;
	KlineCacheManage *g_klmgr = new KlineCacheManage();
	//cin.getline()
	char reportcode[64] = { 0 };
	int marketnum=  0 ;

	cout << "please entry marketno:";
	while (cin>>marketnum)
	{
		cin.get();//³Ôµô\n
		if (marketnum == 9999) {
			break;
		}
		cout << "please entry reportcode:";
		cin.getline(reportcode, sizeof(reportcode));
		CodeKey ck = { 0 };
		strcpy(ck.code, reportcode);
		ck.type = marketnum;//4352;
		int nSize = 8000;
		StockCompDayDataEx *pBarData = new StockCompDayDataEx[nSize * 3];
		int length = g_klmgr->GetDayKLine(ck, pBarData);
		for (int i = 0; i < length/sizeof(StockCompDayDataEx); ++i)
		{
			cout << (pBarData + i)->m_lDate << endl;
		}
		/*cout << "-----------------------------" << endl;
		forward_list<StockCompDayDataEx> sl;
		g_klmgr->GetDayKLine(ck, sl, 20100101, 20110101);
		for (auto it = sl.begin(); it != sl.end(); ++it)
		{
			cout << it->m_lDate << it->m_lTotal << endl;
		}*/
		cout << "please entry marketno:";
	}
	delete g_klmgr;
	cin.get();
}


void mainmin()
{
	//using namespace cache;
	KlineCacheManage *g_klmgr = new KlineCacheManage();
	//cin.getline()
	char reportcode[64] = { 0 };
	int marketnum = 0;

	cout << "please entry marketno:";
	while (cin >> marketnum)
	{
		cin.get();//³Ôµô\n
		if (marketnum == 9999) {
			break;
		}
		cout << "please entry reportcode:";
		cin.getline(reportcode, sizeof(reportcode));
		CodeKey ck = { 0 };
		strcpy(ck.code, reportcode);
		ck.type = marketnum;//4353;
		cin>>ck.time;
		cin.get();//³Ôµô\n
		int nSize = 240;
		StockCompDayDataEx *pBarData = new StockCompDayDataEx[nSize * 3];
		int length = g_klmgr->GetMiniteKLine(ck, pBarData);
		for (int i = 0; i < nSize * 1; ++i)
		{
			cout << (pBarData + i)->m_lDate << endl;
		}
		cout << "-----------------------------" << endl;
		forward_list<StockCompDayDataEx> sl;
		g_klmgr->GetMiniteKLine(ck, sl, 20170601, 20170701);
		for (auto it = sl.begin(); it != sl.end(); ++it)
		{
			cout << it->m_lDate << it->m_lTotal << endl;
		}/**/
		cout << "please entry marketno:";
	}
	delete g_klmgr;
	cin.get();
}


//int maintest2()
//{
//	char st[] = "12314123421234123412341341249995634459";
//	test ttr;
//	memcpy(ttr.str, st, sizeof(st));
//	ttr.i = 1000;
//	ttr.dd = 324.3412;
//	char code[] = "600570";
//	CodeInfo ci;
//	memcpy(ci.m_cCode, code, sizeof(code));
//	ci.m_cCodeType = 4567;
//
//	char st1[] = "887871222323113421234123412341341249995634459";
//	test ttr2;
//	memcpy(ttr2.str, st1, sizeof(st1));
//	ttr2.i = 10004352;
//	ttr2.dd = 3214342.3412;
//	
//	CodeInfo ci2;
//	memcpy(ci2.m_cCode, "600579", sizeof("600579"));
//	ci2.m_cCodeType = 4569;
//
//	unordered_map<int, int> um;
//
//	um.insert(std::make_pair(1,2));
//	um.insert(std::make_pair(2,3));
//	um.insert(std::make_pair(1,3));
//	um.insert(std::make_pair(1, 33));
//	um.insert(std::make_pair(1, 32));
//	//DataCacheReader* dr = DataCacheReader::GetDataCacheReader();
//
////	/*key k = { 0 };
//	/*CMMFCacheEx<key, test> *pmfk = new CMMFCacheEx<key, test>();
//	pmfk->Init("indexkeytest.dat", "contentkeytest.dat");*/
////
////
////	pmfk->Write(k, (char *)&ttr, sizeof(test));
////*/
////
////
//	CMMFCacheEx<CodeInfo,test> *pmf = new CMMFCacheEx<CodeInfo,test>("indextest2.dat", "contenttest2.dat");
//	//pmf->Init();
//	
//
//	pmf->Write(ci, (char *)&ttr, sizeof(test));
//	pmf->Write(ci, (char *)&ttr, sizeof(test),1);
//	pmf->Write(ci, (char *)&ttr, sizeof(test), 1);
//	pmf->Write(ci, (char *)&ttr, sizeof(test), 1);
//	pmf->Write(ci, (char *)&ttr, sizeof(test), 1);
//	pmf->Write(ci, (char *)&ttr, sizeof(test), 1);/**/
//	pmf->Write(ci2, (char *)&ttr2, sizeof(test));
//	test ddt1[6] = { 0 };
//	test ddt2 = { 0 };
//	int length = pmf->Read(ci, (char *)&ddt1, 0);
//	int length2 = pmf->Read(ci2, (char *)&ddt2, 0);
//
//
//
//	CMMFCacheEx<int, test> *pmf2 = new CMMFCacheEx<int, test>("indextestiint3.dat", "contenttestint3.dat");
//	//pmf2->Init();
//
//
//	pmf2->Write(1, (char *)&ttr, sizeof(test));
//	pmf2->Write(1, (char *)&ttr, sizeof(test),1);
//	pmf2->Write(1, (char *)&ttr, sizeof(test), 1);
//	pmf2->Write(2, (char *)&ttr, sizeof(test));
//	test ddt3 = { 0 };
//	test ddt4 = { 0 };
//	int length3 = pmf2->Read(1, (char *)&ddt3, 0);
//	int length4 = pmf2->Read(2, (char *)&ddt4, 0);
//
//	key anytype;
//	strcpy(anytype.code, "600900");
//	CMMFCacheEx<key, test> *pmf3 = new CMMFCacheEx<key, test>("indextestiint4.dat", "contenttestint4.dat");
//	//pmf2->Init();
//
//
//	pmf3->Write(anytype, (char *)&ttr, sizeof(test));
//	pmf3->Write(anytype, (char *)&ttr, sizeof(test));
//	ddt3 = { 0 };
//	ddt4 = { 0 };
//	length3 = pmf3->Read(anytype, (char *)&ddt3, 0);
//	length4 = pmf3->Read(anytype, (char *)&ddt4, 0);
//
//
//	
//
//
//
//
//
//
//
//	//CMMFCacheEx<test> mmfc;
//	//
//	//dr->WriteCodeQuateAll(&ci, (char *)&ttr, sizeof(test), sizeof(test));
//
//
//	/*HMODULE hdll = ::LoadLibrary("DataCache.dll");
//	if (hdll == NULL)
//	{
//	cout << GetLastError() << endl;
//	FreeLibrary(hdll);
//	}*/
//	//pfunc gethq = (pfunc)::GetProcAddress(hdll, "getRealHq");
//	/*if (gethq == NULL)
//	{
//	cout << GetLastError() << endl;
//	FreeLibrary(hdll);
//	}*/
//
//	test ddt = { 0 };
//	//dr->ReadCodeQuate(&ci, 0, (char *)&ddt, sizeof(test));
//
//
//	cin.get();
//}






//void main2()
//{
//	IChannelManager *m_pChannelManager = (IChannelManager*)CWinnerApplication::GetObject(OBJ_CHANNELMANAGER);
//	m_pfnOnConnectNotify = sFn_OnConnectNotify;
//	if (m_pChannelManager != NULL)
//	{
//		m_pChannelManager->RegisterNotify(m_pfnOnConnectNotify);
//	}
//	IChannels* m_pChannels = (IChannels*)CWinnerApplication::GetObject(OBJ_CHANNELS);
// 	
//	char *strServerName = "°¢ÀïÔÆÏßÂ·1";
//	long lConnectHandle = m_pChannelManager->CreateConnector(CEV_Connect_HQ, strServerName);
//}

//void CLoginInitHelper::SetSites()
//{
//	ICommData* pCommData = GetCommData();
//	IChannelManager* pChannelManager = m_pManager;
//	if (NULL == pCommData || NULL == pChannelManager)
//	{
//		ASSERT(FALSE);
//		return;
//	}
//	int count = pCommData->GetCount();
//	if (count <= 0)
//	{
//		return;
//	}
//	CArray<CommInfo*, CommInfo*> *SrvAy = pCommData->GetSysServerInfo();
//	CArray<CommInfo*, CommInfo*> *SrvAyUsr = pCommData->GetUsrServerInfo();
//	CCommInfoArray ayCurNetworkTypeSrv;
//	int nNetworkType = pCommData->GetNetworkAreaType();
//	int index = 0;
//	for (int i = 0; i<SrvAy->GetCount(); i++)
//	{
//		CommInfo *p = SrvAy->GetAt(i);
//		if (nNetworkType == NetworkArea_UnKnow || p->m_nNewworkType == nNetworkType)
//		{
//			ayCurNetworkTypeSrv.Add(p);
//		}
//	}
//	for (int j = 0; j<SrvAyUsr->GetCount(); j++)
//	{
//		CommInfo *p = SrvAyUsr->GetAt(j);
//		if (nNetworkType == NetworkArea_UnKnow || p->m_nNewworkType == nNetworkType)
//		{
//			ayCurNetworkTypeSrv.Add(p);
//		}
//	}
//	count = ayCurNetworkTypeSrv.GetCount();
//	if (count > 0)
//	{
//		CommInfo *pComm = new CommInfo[count];
//		for (int i = 0; i<count; i++)
//		{
//			CommInfo *p = ayCurNetworkTypeSrv.GetAt(i);
//
//			pComm[i] = *p;
//
//			//pComm[i].m_cIsDefault = p->m_cIsDefault;
//			//pComm[i].m_cType = p->m_cType;
//			//pComm[i].m_nPort = p->m_nPort;
//			//memcpy(pComm[i].m_strServerID,p->m_strServerID,sizeof(p->m_strServerID));
//			//memcpy(pComm[i].m_strServerIP,p->m_strServerIP,sizeof(p->m_strServerIP));
//			//memcpy(pComm[i].m_strLicenseNo,p->m_strLicenseNo,sizeof(p->m_strLicenseNo));
//		}
//		pChannelManager->SetSites(pComm, count, pCommData->GetProxy());
//		delete[] pComm;
//	}
//}
