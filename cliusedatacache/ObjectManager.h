#pragma once

class CObjectManager: public CObject
{
protected:
	CMapStringToPtr   m_objMap;
public:
	CObjectManager(void);
	~CObjectManager(void);

	BOOL AddObj(const CString& strName,CObject *pObj);
	void* GetObj(LPCTSTR lpszObjectLocation, LPCTSTR lpszPreFix=NULL);

	void  FreeObject();
};
