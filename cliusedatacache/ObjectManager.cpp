#include "StdAfx.h"
#include "Winner.h"
#include "ObjectManager.h"
#include "PluginMgr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CObjectManager::CObjectManager(void)
{
}

CObjectManager::~CObjectManager(void)
{
	OutputDebugString(_T("[CObjectManager::~CObjectManage] freeing...\n"));
}

BOOL CObjectManager::AddObj(const CString& strName, CObject *pObj)
{
	void* pObjExist = NULL;
	if(m_objMap.Lookup(strName, pObjExist))
		return FALSE;
	m_objMap.SetAt(strName, pObj);
	return TRUE;
}

void* CObjectManager::GetObj(LPCTSTR lpszObjectLocation, LPCTSTR lpszPreFix/* =NULL */)
{
	if (0 == _tcscmp(lpszObjectLocation, _T("IMainWnd")))
	{
		return HsGetMainWnd();
	}
	else 
	{
		void* pObj = NULL;
		if( m_objMap.Lookup(lpszObjectLocation, pObj) ) 
			return pObj;

		//返回插件内的对象
		extern CModulePluginMgr g_PluginMgr;
		pObj = g_PluginMgr.GetServicePluginObject(lpszObjectLocation, lpszPreFix);
		return pObj;
	}
	
}

void CObjectManager::FreeObject()
{
	POSITION pos;
	CString key;
	void* pObj = NULL;
	for( pos = m_objMap.GetStartPosition(); pos != NULL; )
	{
		m_objMap.GetNextAssoc( pos, key, pObj);
		if(pObj)
		{
			delete (CObject*)pObj;
		}
	}
	m_objMap.RemoveAll();
}