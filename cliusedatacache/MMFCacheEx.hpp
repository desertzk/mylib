#pragma once
//#define _CRT_SECURE_NO_WARNINGS
//#include <windows.h>
#ifdef MFCPRO
#include"stdafx.h"
//#include "hsstructnew.h"
#endif

#include "MMFCacheDefine.h"
#include "MMF.h"
//#include"DataCacheReader.h"
#include<unordered_map>
#include<utility>
//#include"BaseCache.h"
#include<list>
#include <cstdio>
#include<assert.h>
#include<string>
#include"CodeKey.h"

//extern 








// ������
template<class IndexKey,class CacheType>
class CMMFCacheEx
{
public:
	CMMFCacheEx(const char *strIndexFilePath, const char *strContentFilePath, unsigned int nIndexCapability = 5, unsigned int nPageCapability = 5000, unsigned int nOneStructSize = sizeof(CacheType)) :m_nOneStructSize(nOneStructSize),
		m_pMMFIndex(NULL),
		m_pMMFContent(NULL)
	{
		m_indexHead.m_nVersion = FILE_VERSION;
		m_indexHead.m_nIndexCount = 0;
		m_indexHead.m_nIndexCapability = nIndexCapability;
		m_indexHead.m_nPageCapability = nPageCapability;
		m_indexHead.m_nPageNo = 0;
		m_nIndexEndOff = 0;
		Init(strIndexFilePath, strContentFilePath);
	};
	~CMMFCacheEx(void)
	{
		Release();
	};

	static bool file_exists(const std::string& name) {
		struct stat buffer;
		return (stat(name.c_str(), &buffer) == 0);
	}

	bool Init(const char *strIndexFilePath, const char *strContentFilePath)
	{
		char empty[1024] = { 0 };
		if (!file_exists(strIndexFilePath))
		{
			FILE *fpindex = fopen(strIndexFilePath,"a");
			fwrite(empty,sizeof(empty),1,fpindex);
			fclose(fpindex);
		}
		if (!file_exists(strContentFilePath))
		{
			FILE *fpcontent = fopen(strContentFilePath, "a");
			fclose(fpcontent);
		}
		//Release();

		m_pMMFIndex = new CMMF(strIndexFilePath,512*1024,1024);
		InitIndexFile();
		//m_pMMFContent = DataCacheReader::GetDataCacheReader()->NewBaseCacheMMF(strContentFilePath);
		m_pMMFContent = new CMMF(strContentFilePath);
		return TRUE;
	};

	int    GetReadLenth(const IndexKey& codeInfo)
	{
		unsigned int nTotalLenth = 0;
		std::unordered_map<IndexKey, int>::iterator it = m_mapCodeToIndex.find(codeInfo);
		if (it != m_mapCodeToIndex.end())
		{
			int nOffset = it->second;
			
			MMFCachePageInfo<IndexKey> pageInfo;
			for (unsigned int i = 0; i < m_indexHead.m_nIndexCapability; ++i)
			{
				if (m_pMMFIndex->Read(nOffset + i * sizeof(MMFCachePageInfo<IndexKey>), (char*)&pageInfo, sizeof(MMFCachePageInfo<IndexKey>))
					&& pageInfo.m_nCount != 0
					)
				{
					nTotalLenth += pageInfo.m_nCount * m_nOneStructSize; // �ۼӴ洢����Ϣ��С
				}
				else
				{
					break;
				}
			}
		}
		return nTotalLenth;
	}

	std::unordered_map<IndexKey, int>    *GetIndexMap()
	{
		return &m_mapCodeToIndex;
	}

//return bytes already read
	int		Read(const IndexKey& codeInfo, char* pBuffer, unsigned int nBufferLenth)
	{
		//HSLOG_DEBUG(_T("codeInfo in read '%s'  '%s'"), codeInfo.GetCode(), codeInfo.GetMarket());
		unsigned int nRetLenth = 0;
		unsigned int nTotalLenth = 0;
		unsigned int nOffset = 0;
		unsigned int nCopyLenth = 0; // ��¼�Ѿ����Ƶĳ���
		std::unordered_map<IndexKey, int>::iterator it = m_mapCodeToIndex.find(codeInfo);
		if (it!= m_mapCodeToIndex.end())
		{
			nOffset = it->second;
			std::list<unsigned int> listPageNo;
			MMFCachePageInfo<IndexKey> pageInfo;
			for (unsigned int i = 0; i < m_indexHead.m_nIndexCapability; ++i)
			{
				if (m_pMMFIndex->Read(nOffset + i * sizeof(MMFCachePageInfo<IndexKey>), (char*)&pageInfo, sizeof(MMFCachePageInfo<IndexKey>))
					&& pageInfo.m_nCount != 0
					)
				{
					//HSLOG_DEBUG(_T("m_nPageNo'%d'"), pageInfo.m_nPageNo);
					listPageNo.push_back(pageInfo.m_nPageNo); // ��¼ҳ����
					nTotalLenth += pageInfo.m_nCount * m_nOneStructSize; // �ۼӴ洢����Ϣ��С
				}
				else
				{
					break;
				}
			}

			nRetLenth = nTotalLenth;
			if (pBuffer != NULL && nTotalLenth != 0)
			{
				//nRetLenth = min(nBufferLenth, nTotalLenth);

				unsigned int nOneContentSize = GetContentSize();
				unsigned int nOnePageMaxSize = GetOnePageMaxSize();

				
				for (auto it = listPageNo.begin(); it != listPageNo.end(); ++it)
				{
					unsigned int nPageNo = *it;
					//assert(nPageNo != 0);

					unsigned int nCurrentLenth = min(nRetLenth - nCopyLenth, nOnePageMaxSize);
					if (nCurrentLenth == 0)
					{// �Ѿ���ȡ���
						break;
					}

					if (m_pMMFContent->Read((nPageNo - 1) * nOneContentSize + sizeof(MMFCachePageInfo<IndexKey>), pBuffer + nCopyLenth, nCurrentLenth))
					{
						nCopyLenth += nCurrentLenth;
					}
					else
					{// �����ļ��������ļ���ƥ��
						//assert(FALSE);
						nRetLenth = 0;
						break;
					}
				}
			}
		}
		return nCopyLenth;
	};


	//unsigned int      ReadOffset(const IndexKey& codeInfo, unsigned int nOffsetLenth, char* pBuffer, unsigned int nBufferLenth)
	//{
	//	unsigned int nRetLenth = 0;
	//	unsigned int nTotalLenth = 0;
	//	unsigned int nOffset = 0;
	//	if (m_mapCodeToIndex.Lookup(codeInfo.MakeIntKey(), nOffset))
	//	{
	//		std::list<unsigned int> listPageNo;
	//		MMFCachePageInfo pageInfo;
	//		for (unsigned int i = 0; i < m_indexHead.m_nIndexCapability; i++)
	//		{
	//			if (m_pMMFIndex->Read(nOffset + i * sizeof(MMFCachePageInfo), (char*)&pageInfo, sizeof(MMFCachePageInfo))
	//				&& pageInfo.m_code.CompareCodeByMainMarket(&codeInfo)
	//				&& pageInfo.m_nCount != 0
	//				)
	//			{
	//				if (nTotalLenth + pageInfo.m_nCount * m_nOneStructSize > nOffsetLenth)
	//				{
	//					listPageNo.push_back(pageInfo.m_nPageNo); // ��¼ҳ����
	//				}

	//				nTotalLenth += pageInfo.m_nCount * m_nOneStructSize; // �ۼӴ洢����Ϣ��С
	//			}
	//			else
	//			{
	//				break;
	//			}
	//		}

	//		if (pBuffer != NULL && !listPageNo.IsEmpty() && nTotalLenth > nOffsetLenth)
	//		{
	//			nRetLenth = nTotalLenth - nOffsetLenth; // ��Ҫ��ȡ���ֽ�

	//			unsigned int nOneContentSize = GetContentSize();
	//			unsigned int nOnePageMaxSize = GetOnePageMaxSize();
	//			unsigned int nPageOffset = nOffsetLenth % nOnePageMaxSize; // ҳ��ƫ��λ��

	//			unsigned int nCopyLenth = 0; // ��¼�Ѿ����Ƶĳ���
	//			POSITION pos = listPageNo.GetHeadPosition();
	//			while (pos)
	//			{
	//				unsigned int nPageNo = listPageNo.GetNext(pos);
	//				assert(nPageNo != 0);

	//				unsigned int nCurrentLenth = min(nOnePageMaxSize - nPageOffset, nRetLenth - nCopyLenth); // ��ǰ��Ҫ���Ƶĸ���
	//				if (nCurrentLenth == 0)
	//				{// �Ѿ���ȡ��� ����Ҫ�ٶ�ȡ
	//					break;
	//				}

	//				if (m_pMMFContent->Read((nPageNo - 1) * nOneContentSize + sizeof(MMFCachePageInfo) + nPageOffset, pBuffer + nCopyLenth, nCurrentLenth))
	//				{
	//					nCopyLenth += nCurrentLenth;
	//					nPageOffset = 0; // ֻ�е�һ�λ���Ҫ����ƫ��λ�ã�֮���Ǵӿ�ͷ��ʼ��ȡ
	//				}
	//				else
	//				{// �����ļ��������ļ���ƥ��
	//					assert(FALSE);
	//					nRetLenth = 0;
	//					break;
	//				}
	//			}
	//		}
	//	}
	//	return nRetLenth;
	//};


	bool        Write(const IndexKey& codeInfo, const char* pBuffer, unsigned int nBufferLenth, bool bAppend = FALSE)
	{// ѡ��д��ķ�ʽ
		return bAppend ? WriteAppend(codeInfo, pBuffer, nBufferLenth)
			: WriteOverlap(codeInfo, pBuffer, nBufferLenth);
	};

	unsigned int		GetIndexSize() const   // һֻ���������Ĵ�С
	{
		return sizeof(IndexKey) + m_indexHead.m_nIndexCapability * sizeof(MMFCachePageInfo<IndexKey>);
	};
	
	unsigned int      GetContentSize() const // һ�����ݴ洢��Ϣ�Ĵ�С
	{
		return sizeof(MMFCachePageInfo<IndexKey>) + GetOnePageMaxSize();
	};

	unsigned int      GetOnePageMaxSize() const     // һҳ�ܹ��洢��Ϣ������С
	{
		return m_indexHead.m_nPageCapability * m_nOneStructSize;
	};

	unsigned int      GetOneCodeInfoMaxSize() const // ��ȡһֻ��������ܹ��洢������
	{
		return m_indexHead.m_nIndexCapability * m_indexHead.m_nPageCapability * m_nOneStructSize;
	};
	bool        IsPageFull(const MMFCachePageInfo<IndexKey>& pageInfo) const       // �ж�һҳ�Ƿ��Ѿ�����
	{
		return pageInfo.m_nCount == m_indexHead.m_nPageCapability;
	};
	unsigned int      GetPageEmptySpace(const MMFCachePageInfo<IndexKey>& pageInfo) const// ��ȡһҳ����Ŀ������� 
	{
		return min(GetOnePageMaxSize(), (m_indexHead.m_nPageCapability - pageInfo.m_nCount) * m_nOneStructSize);
	};

	//static bool GetMarketName(HSMarketDataType nMarketType, CString& strMarketName) {
	//	switch (MakeMainMarket(nMarketType))
	//	{
	//	case SH_Bourse:	strMarketName = _T("���ڹ�Ʊ-��֤֤ȯ");	break;
	//	case SZ_Bourse:	strMarketName = _T("���ڹ�Ʊ-��֤֤ȯ");	break;

	//	case (OPTION_MARKET | OPTION_SH): strMarketName = _T("��Ȩ-�Ϻ���Ȩ");	break;
	//	case (OPTION_MARKET | OPTION_SZ): strMarketName = _T("��Ȩ-������Ȩ");	break;
	//	case (OPTION_MARKET | OPTION_FUTURES_GUZHI): strMarketName = _T("��Ȩ-�н���Ȩ");	break;
	//	case (OPTION_MARKET | OPTION_FUTURES_SH): strMarketName = _T("��Ȩ-�Ϻ��ڻ���Ȩ");	break;
	//	case (OPTION_MARKET | OPTION_FUTURES_DL): strMarketName = _T("��Ȩ-�����ڻ���Ȩ");	break;
	//	case (OPTION_MARKET | OPTION_FUTURES_ZZ): strMarketName = _T("��Ȩ-֣���ڻ���Ȩ");	break;

	//	case (FUTURES_MARKET | DALIAN_BOURSE):		strMarketName = _T("�ڻ�-�����ڻ�");		break;
	//	case (FUTURES_MARKET | SHANGHAI_BOURSE): 	strMarketName = _T("�ڻ�-�Ϻ��ڻ�");		break;
	//	case (FUTURES_MARKET | ZHENGZHOU_BOURSE):	strMarketName = _T("�ڻ�-֣���ڻ�");		break;
	//	case (FUTURES_MARKET | HUANGJIN_BOURSE):	strMarketName = _T("�ڻ�-�ƽ��ڻ�");		break;
	//	case (FUTURES_MARKET | GUZHI_BOURSE):		strMarketName = _T("�ڻ�-��ָ�ڻ�");		break;

	//	case (CAE_MARKET | AUCTION_AGGREGATE):      strMarketName = _T("�Ľ���-���Ͼ���");	break;
	//	case (CAE_MARKET | AUCTION_DYNAMIC):        strMarketName = _T("�Ľ���-��̬����");	break;
	//	case (CAE_MARKET | AUCTION_GENERAL):        strMarketName = _T("�Ľ���-����");	    break;

	//	case (COMMODITIES_MARKET | SGE_BOURSE):     strMarketName = _T("��Ʒ-�ƽ����");    break;
	//	case (COMMODITIES_MARKET | SP_CG_BOURSE):   strMarketName = _T("��Ʒ-������Ʒ");    break;
	//	case (COMMODITIES_MARKET | SP_GT_BOURSE):   strMarketName = _T("��Ʒ-���콻��");    break;
	//	case (COMMODITIES_MARKET | BARGAIN_BOURSE): strMarketName = _T("��Ʒ-Э�����");    break;
	//	case (COMMODITIES_MARKET | PRICE_BOURSE):   strMarketName = _T("��Ʒ-���۽���");    break;

	//		//case (FOREIGN_MARKET | WH_BASE_RATE):		strMarketName = _T("���-��������");  	break;
	//		//case (FOREIGN_MARKET | WH_ACROSS_RATE): 	strMarketName = _T("���-�������");  	break;
	//		//case (FOREIGN_MARKET | WH_FUTURES_RATE):	strMarketName = _T("���-�ڻ�");  		break;

	//	case (HK_MARKET | HK_BOURSE):		strMarketName = _T("�۹�-�����г�");      	break;
	//	case (HK_MARKET | GE_BOURSE):		strMarketName = _T("�۹�-��ҵ���г�");   	break;
	//	case (HK_MARKET | INDEX_BOURSE):		strMarketName = _T("�۹�-ָ���г�");	        break;

	//	default:
	//	{
	//		strMarketName = _T("δ֪�г�");
	//		//assert(FALSE);
	//		return FALSE;
	//	}
	//	}
	//	return TRUE;
	//};
protected:
	bool   Release() 
	{
		if (m_pMMFIndex)
		{
			delete m_pMMFIndex;
			m_pMMFIndex = NULL;
		}
		m_mapCodeToIndex.clear();

		if (m_pMMFContent)
		{
			delete m_pMMFContent;
			m_pMMFContent = NULL;
		}

		return FALSE;
	};

	bool   InitIndexFile() {
		assert(m_pMMFIndex);
		unsigned int nFileSize = (unsigned int)m_pMMFIndex->GetFileSize();
		unsigned int nHeadSize = sizeof(MMFCacheIndexFileHead);
		if (nFileSize < nHeadSize)
		{
			return FALSE;
		}

		MMFCacheIndexFileHead head;
		if (m_pMMFIndex->Read(0, (char*)&head, nHeadSize))
		{
			if (head.m_nVersion != FILE_VERSION)
			{// �汾�Ų�ƥ�� ����ļ�
				m_pMMFIndex->ClearFile();
				m_pMMFIndex->Write(0, (char*)&m_indexHead, sizeof(MMFCacheIndexFileHead));
				m_nIndexEndOff = sizeof(MMFCacheIndexFileHead);

				if (m_pMMFContent)
				{
					m_pMMFContent->ClearFile();
				}
				return FALSE;
			}

			memcpy(&m_indexHead, &head, sizeof(MMFCacheIndexFileHead));

			unsigned int nOneIndexSize = GetIndexSize();
			unsigned int nOffer = nHeadSize;
			IndexKey codeInfo;
			for (int indexnum=0; indexnum < m_indexHead.m_nIndexCount && nOffer< nFileSize;++indexnum)
			{
				if (m_pMMFIndex->Read(nOffer, (char*)&codeInfo, sizeof(IndexKey)))
				{// �洢ÿһ������ҳ����ʼλ��
					//HSLOG_DEBUG(_T("codeInfo in index '%s'  '%s' ,file %s ,%d"), codeInfo.GetCode(), codeInfo.GetMarket(), m_pMMFIndex->getFilePath(), nOffer);
					m_mapCodeToIndex.insert(std::make_pair(codeInfo, nOffer + sizeof(IndexKey)));
				}
				else
				{
					assert(FALSE);
					return FALSE;
				}

				nOffer += nOneIndexSize;
			}
			m_nIndexEndOff = nOffer; // ��¼ĩβ��ƫ����

			return TRUE;
		}
		return FALSE;
	};


	bool   WriteAppend(const IndexKey& codeInfo, const char* pBuffer, unsigned int nBufferLenth) {
		//HSLOG_DEBUG(_T("codeInfo in write append '%s'  '%s'"), codeInfo.GetCode(), codeInfo.GetMarket());
		bool bRet = FALSE;
		if (pBuffer == NULL || nBufferLenth == 0)
		{
			return bRet;
		}

		unsigned int nCopyLenth = 0;         // ʵ�ʿ�������
		const char* pCopyBegin = NULL; // ��ʼλ��
		unsigned int nCopyLenthBackUp = 0;   // �Ѿ�д��ĳ���
		unsigned int nPageFullCount = 0;     // ��¼�Ѿ��������ҳ����
		std::list<MMFCachePageInfo<IndexKey>> listPageNoBackUpNotFull;// �Ѿ�д�����ݲ���û��д����ҳ��

		unsigned int nOffset = 0;
		unsigned int nCodeOffset = 0;
		std::unordered_map<IndexKey, int>::iterator it = m_mapCodeToIndex.find(codeInfo);
		if (it != m_mapCodeToIndex.end())
		{// �����Ѿ����� 
			nOffset = it->second;
			MMFCachePageInfo<IndexKey> pageInfo;
			for (unsigned int i = 0; i < m_indexHead.m_nIndexCapability; ++i)
			{
				if (m_pMMFIndex->Read(nOffset + i * sizeof(MMFCachePageInfo<IndexKey>), (char*)&pageInfo, sizeof(MMFCachePageInfo<IndexKey>))
					&& pageInfo.m_nPageNo>0)
				{
					nCopyLenthBackUp += (pageInfo.m_nCount * m_nOneStructSize);// �ۻ��Ѿ�д��ĳ���
					//int overflowcount = pageInfo.m_nCount + nBufferLenth / m_nOneStructSize - m_indexHead.m_nPageCapability;
					
					//pageInfo.m_nCount + nBufferLenth / m_nOneStructSize;
					//if (overflowcount <=0)
					if(!IsPageFull(pageInfo))
					{// ��¼δд����ҳ����

						listPageNoBackUpNotFull.push_back(pageInfo);
						break;
					}
					else
					{
						//listPageNoBackUpNotFull.push_back(pageInfo);
						++nPageFullCount;
					}
				}
				else
				{
					break;
				}
			}

			if (nCopyLenthBackUp >= GetOneCodeInfoMaxSize())
			{// �����Ѿ�д���� �޷�д��
				return bRet;
			}
		}
		else
		{// �����Ӵ���

		 // ƫ�Ƶ����
			nOffset = m_nIndexEndOff + sizeof(IndexKey);
			m_nIndexEndOff += GetIndexSize();
			++m_indexHead.m_nIndexCount;
			// ���뵽����
			m_mapCodeToIndex.insert(std::make_pair(codeInfo, nOffset));
		}
		nCodeOffset = nOffset - sizeof(IndexKey);
		nCopyLenth = min(nBufferLenth, GetOneCodeInfoMaxSize() - nCopyLenthBackUp);
		pCopyBegin = pBuffer + (nBufferLenth - nCopyLenth);
		/*nCopyLenth = min(nBufferLenth, GetOnePageMaxSize() - nCopyLenthBackUp);
		pCopyBegin = pBuffer;
		int remainLenth = nBufferLenth - nCopyLenth;*/
		// ����ҳ�ſ�ʼд�ļ� �������ļ���ʼд ��һ��д��ʱ���������� ���������������������ȡ�����������
		while (nCopyLenth != 0)
		{
			if (!listPageNoBackUpNotFull.empty())
			{// �ȴ�δд����ҳ ����д
				MMFCachePageInfo<IndexKey> pageInfoBackUp = listPageNoBackUpNotFull.front();
				listPageNoBackUpNotFull.pop_front();
				unsigned int nPageOffset = (pageInfoBackUp.m_nPageNo - 1) * GetContentSize();
				unsigned int nOnePageLenth = min(GetPageEmptySpace(pageInfoBackUp), nCopyLenth);

				MMFCachePageInfo<IndexKey> pageInfo;
				pageInfo.m_nPageNo = pageInfoBackUp.m_nPageNo;
				pageInfo.m_code = pageInfoBackUp.m_code;
				pageInfo.m_nCount = pageInfoBackUp.m_nCount + nOnePageLenth / m_nOneStructSize;
				assert(pageInfo.m_nCount <= m_indexHead.m_nPageCapability);
				pageInfo.m_nOffSet = pageInfoBackUp.m_nOffSet + nOnePageLenth;
				m_pMMFContent->Write(nPageOffset, (char*)&pageInfo, sizeof(MMFCachePageInfo<IndexKey>));   // дҳ����Ϣ

				m_pMMFContent->Write(pageInfoBackUp.m_nOffSet, pCopyBegin, nOnePageLenth);       // д����
				pCopyBegin += nOnePageLenth;

				m_pMMFIndex->Write(nOffset + nPageFullCount * sizeof(MMFCachePageInfo<IndexKey>), (char*)&pageInfo, sizeof(MMFCachePageInfo<IndexKey>));  // д�����ļ�

				nCopyLenth = nCopyLenth < nOnePageLenth ? 0 : nCopyLenth - nOnePageLenth;
				nPageFullCount++; // �����֮�� ������һ
			}
			else
			{// ������ҳ 
				unsigned int nPageNo = m_indexHead.m_nPageNo + 1;
				m_indexHead.m_nPageNo++;

				unsigned int nPageOffset = (nPageNo - 1) * GetContentSize();
				//unsigned int nOnePageLenth = min(GetOnePageMaxSize(), remainLenth);
				unsigned int nOnePageLenth = min(GetOnePageMaxSize(), nCopyLenth);
				
				MMFCachePageInfo<IndexKey> pageInfo;
				pageInfo.m_nPageNo = nPageNo;
				pageInfo.m_code = codeInfo;
				pageInfo.m_nCount = nOnePageLenth / m_nOneStructSize;
				//assert(pageInfo.m_nCount <= m_indexHead.m_nPageCapability);
				pageInfo.m_nOffSet = nPageOffset + sizeof(MMFCachePageInfo<IndexKey>) + nOnePageLenth;

				m_pMMFContent->Write(nPageOffset, (char*)&pageInfo, sizeof(MMFCachePageInfo<IndexKey>));           // дҳ����Ϣ
				m_pMMFContent->Write(nPageOffset + sizeof(MMFCachePageInfo<IndexKey>), pCopyBegin, nOnePageLenth); // д����
				pCopyBegin += nOnePageLenth;

				m_pMMFIndex->Write(nOffset + nPageFullCount * sizeof(MMFCachePageInfo<IndexKey>), (char*)&pageInfo, sizeof(MMFCachePageInfo<IndexKey>));  // д�����ļ�		

				nCopyLenth = nCopyLenth < nOnePageLenth ? 0 : nCopyLenth - nOnePageLenth;
				nPageFullCount++; // �����֮�� ������һ
			}
		}

		m_pMMFIndex->Write(nCodeOffset, (char*)&codeInfo, sizeof(IndexKey));          // д�����ļ�������Ϣ
		m_pMMFIndex->Write(0, (char*)&m_indexHead, sizeof(MMFCacheIndexFileHead));    // д�����ļ�ͷ����Ϣ

		return bRet;
	};
	
	bool   WriteOverlap(const IndexKey& codeInfo, const char* pBuffer, unsigned int nBufferLenth) {
		bool bRet = FALSE;
		if (pBuffer == NULL || nBufferLenth == 0)
		{
			return bRet;
		}

		// ʵ�ʿ������� �� ��ʼλ��
		unsigned int nCopyLenth = min(GetOneCodeInfoMaxSize(), nBufferLenth);
		const char* pCopyBegin = pBuffer + (nBufferLenth - nCopyLenth);
		// ������Ҫ��ҳ��
		unsigned int nPageInfoCount = (nCopyLenth + GetOnePageMaxSize() - 1) / GetOnePageMaxSize();

		std::list<unsigned int> listPageNo;
		unsigned int nOffset = 0;
		unsigned int nCodeOffset = 0;
		std::unordered_map<IndexKey, int>::iterator it = m_mapCodeToIndex.find(codeInfo);
		if (it != m_mapCodeToIndex.end())
		{// �����Ѿ����� 
			nOffset = it->second;
			std::list<unsigned int> listPageNoBackUp;
			MMFCachePageInfo<IndexKey> pageInfo;
			for (unsigned int i = 0; i < m_indexHead.m_nIndexCapability; i++)
			{
				if (m_pMMFIndex->Read(nOffset + i * sizeof(MMFCachePageInfo<IndexKey>), (char*)&pageInfo, sizeof(MMFCachePageInfo<IndexKey>))
					&& pageInfo.m_nPageNo>0)
				{
					listPageNoBackUp.push_back(pageInfo.m_nPageNo); // ��¼ҳ����
				}
				else
				{
					break;
				}
			}

			
			for(auto it= listPageNoBackUp.begin();it!= listPageNoBackUp.end();++it)
			{
				listPageNo.push_back(*it);
			}

			while (listPageNo.size() < nPageInfoCount)
			{// ֮ǰд����ҳ�������� ��Ҫ�����µ�ҳ
				m_indexHead.m_nPageNo++;
				listPageNo.push_back(m_indexHead.m_nPageNo);
			}
		}
		else
		{// �����Ӵ���

		 // ƫ�Ƶ����
			nOffset = m_nIndexEndOff + sizeof(IndexKey);
			m_nIndexEndOff += GetIndexSize();
			++m_indexHead.m_nIndexCount;
			// ���뵽����
			m_mapCodeToIndex.insert(std::make_pair(codeInfo, nOffset));

			// ��ʼ���ɵ�ǰ��������Ҫд���ҳ��
			for (unsigned int i = 0; i < nPageInfoCount; i++)
			{// ҳ���ǵ�ǰҳ����֮���ۼ� ȫ��������ҳ
				listPageNo.push_back(m_indexHead.m_nPageNo + i + 1);
			}
			m_indexHead.m_nPageNo += nPageInfoCount;
		}
		nCodeOffset = nOffset - sizeof(IndexKey);

		// ����ҳ�ſ�ʼд�ļ� �������ļ���ʼд ��һ��д��ʱ���������� ���������������������ȡ�����������
		for (auto it = listPageNo.begin(); it != listPageNo.end(); ++it)
		{
			unsigned int nPageNo = *it;
			unsigned int nOnePageLenth = min(GetOnePageMaxSize(), nCopyLenth);
			nCopyLenth = nCopyLenth > GetOnePageMaxSize() ? nCopyLenth - GetOnePageMaxSize() : 0;

			unsigned int nPageOffset = (nPageNo - 1) * GetContentSize();

			MMFCachePageInfo<IndexKey> pageInfo;
			pageInfo.m_nPageNo = nPageNo;
			pageInfo.m_code = codeInfo;
			pageInfo.m_nCount = nOnePageLenth / m_nOneStructSize;
			pageInfo.m_nOffSet = nPageOffset + sizeof(MMFCachePageInfo<IndexKey>) + nOnePageLenth;

			m_pMMFContent->Write(nPageOffset, (char*)&pageInfo, sizeof(MMFCachePageInfo<IndexKey>));           // дҳ����Ϣ
			m_pMMFContent->Write(nPageOffset + sizeof(MMFCachePageInfo<IndexKey>), pCopyBegin, nOnePageLenth); // д����
			pCopyBegin += nOnePageLenth;

			m_pMMFIndex->Write(nOffset, (char*)&pageInfo, sizeof(MMFCachePageInfo<IndexKey>));  // д�����ļ�ҳ��Ϣ
			nOffset += sizeof(MMFCachePageInfo<IndexKey>);
		}

		m_pMMFIndex->Write(nCodeOffset, (char*)&codeInfo, sizeof(IndexKey));          // д�����ļ�������Ϣ
		m_pMMFIndex->Write(0, (char*)&m_indexHead, sizeof(MMFCacheIndexFileHead));    // д�����ļ�ͷ����Ϣ

		return bRet;
	};
private:
	MMFCacheIndexFileHead  m_indexHead; // ����ͷ����Ϣ
	unsigned int      m_nOneStructSize;       // �洢�ĵ����ṹ���С

	CMMF*       m_pMMFIndex;           // �����ļ�
	// �����ļ�����
	std::unordered_map<IndexKey,int> m_mapCodeToIndex;
	unsigned int      m_nIndexEndOff;         // �����ļ�ĩβƫ����
	
	CMMF*       m_pMMFContent;          // �����ļ�
	
};









//part 
//template<class CacheType>
//class CMMFCacheEx<CodeInfo,CacheType>
//{
//public:
//	CMMFCacheEx(const char *strIndexFilePath, const char *strContentFilePath, unsigned int nIndexCount = 3000, unsigned int nIndexCapability = 1, unsigned int nPageCapability = 1000, unsigned int nOneStructSize = sizeof(CacheType)) :m_nOneStructSize(nOneStructSize),
//		m_pMMFIndex(NULL),
//		m_pMMFContent(NULL)
//	{
//		m_indexHead.m_nVersion = FILE_VERSION;
//		m_indexHead.m_nIndexCount = nIndexCount;
//		m_indexHead.m_nIndexCapability = nIndexCapability;
//		m_indexHead.m_nPageCapability = nPageCapability;
//		m_indexHead.m_nPageNo = 0;
//		m_nIndexEndOff = 0;
//		Init(strIndexFilePath, strContentFilePath);
//	};
//	~CMMFCacheEx(void)
//	{
//		Release();
//	};
//
//	bool file_exists(const std::string& name) {
//		struct stat buffer;
//		return (stat(name.c_str(), &buffer) == 0);
//	}
//
//	bool Init(const char *strIndexFilePath, const char *strContentFilePath)
//	{
//		char empty[1024] = { 0 };
//		if (!file_exists(strIndexFilePath))
//		{
//			FILE *fpindex = fopen(strIndexFilePath, "a");
//			fwrite(empty, sizeof(empty), 1, fpindex);
//			fclose(fpindex);
//		}
//		if (!file_exists(strContentFilePath))
//		{
//			FILE *fpcontent = fopen(strContentFilePath, "a");
//			fclose(fpcontent);
//		}
//		//Release();
//
//		m_pMMFIndex =new CMMF(strIndexFilePath);
//		InitIndexFile();
//		m_pMMFContent = new CMMF(strContentFilePath);
//		return TRUE;
//	};
//
//
//	unsigned int		Read(const CodeInfo& codeInfo, char* pBuffer, unsigned int nBufferLenth)
//	{
//		//HSLOG_DEBUG(_T("codeInfo in read '%s'  '%s'"), codeInfo.GetCode(), codeInfo.GetMarket());
//		unsigned int nRetLenth = 0;
//		unsigned int nTotalLenth = 0;
//		unsigned int nOffset = 0;
//		std::unordered_map<CodeInfo, int>::iterator it = m_mapCodeToIndex.find(codeInfo);
//		if (it != m_mapCodeToIndex.end())
//		{
//			nOffset = it->second;
//			std::list<unsigned int> listPageNo;
//			MMFCachePageInfo<CodeInfo> pageInfo;
//			for (unsigned int i = 0; i < m_indexHead.m_nIndexCapability; i++)
//			{
//				if (m_pMMFIndex->Read(nOffset + i * sizeof(MMFCachePageInfo<CodeInfo>), (char*)&pageInfo, sizeof(MMFCachePageInfo<CodeInfo>))
//					&& pageInfo.m_code.CompareCodeByMainMarket(&codeInfo)
//					&& pageInfo.m_nCount != 0
//					)
//				{
//					//HSLOG_DEBUG(_T("m_nPageNo'%d'"), pageInfo.m_nPageNo);
//					listPageNo.push_back(pageInfo.m_nPageNo); // ��¼ҳ����
//					nTotalLenth += pageInfo.m_nCount * m_nOneStructSize; // �ۼӴ洢����Ϣ��С
//				}
//				else
//				{
//					break;
//				}
//			}
//
//			nRetLenth = nTotalLenth;
//			if (pBuffer != NULL && nTotalLenth != 0)
//			{
//				//nRetLenth = min(nBufferLenth, nTotalLenth);
//
//				unsigned int nOneContentSize = GetContentSize();
//				unsigned int nOnePageMaxSize = GetOnePageMaxSize();
//
//				unsigned int nCopyLenth = 0; // ��¼�Ѿ����Ƶĳ���
//				for (auto it = listPageNo.begin(); it != listPageNo.end(); ++it)
//				{
//					unsigned int nPageNo = *it;
//					assert(nPageNo != 0);
//
//					unsigned int nCurrentLenth = min(nRetLenth - nCopyLenth, nOnePageMaxSize);
//					if (nCurrentLenth == 0)
//					{// �Ѿ���ȡ���
//						break;
//					}
//
//					if (m_pMMFContent->Read((nPageNo - 1) * nOneContentSize + sizeof(MMFCachePageInfo<CodeInfo>), pBuffer + nCopyLenth, nCurrentLenth))
//					{
//						nCopyLenth += nCurrentLenth;
//					}
//					else
//					{// �����ļ��������ļ���ƥ��
//						assert(FALSE);
//						nRetLenth = 0;
//						break;
//					}
//				}
//			}
//		}
//		return nRetLenth;
//	};
//
//
//	//unsigned int      ReadOffset(const IndexKey& codeInfo, unsigned int nOffsetLenth, char* pBuffer, unsigned int nBufferLenth)
//	//{
//	//	unsigned int nRetLenth = 0;
//	//	unsigned int nTotalLenth = 0;
//	//	unsigned int nOffset = 0;
//	//	if (m_mapCodeToIndex.Lookup(codeInfo.MakeIntKey(), nOffset))
//	//	{
//	//		std::list<unsigned int> listPageNo;
//	//		MMFCachePageInfo pageInfo;
//	//		for (unsigned int i = 0; i < m_indexHead.m_nIndexCapability; i++)
//	//		{
//	//			if (m_pMMFIndex->Read(nOffset + i * sizeof(MMFCachePageInfo), (char*)&pageInfo, sizeof(MMFCachePageInfo))
//	//				&& pageInfo.m_code.CompareCodeByMainMarket(&codeInfo)
//	//				&& pageInfo.m_nCount != 0
//	//				)
//	//			{
//	//				if (nTotalLenth + pageInfo.m_nCount * m_nOneStructSize > nOffsetLenth)
//	//				{
//	//					listPageNo.push_back(pageInfo.m_nPageNo); // ��¼ҳ����
//	//				}
//
//	//				nTotalLenth += pageInfo.m_nCount * m_nOneStructSize; // �ۼӴ洢����Ϣ��С
//	//			}
//	//			else
//	//			{
//	//				break;
//	//			}
//	//		}
//
//	//		if (pBuffer != NULL && !listPageNo.IsEmpty() && nTotalLenth > nOffsetLenth)
//	//		{
//	//			nRetLenth = nTotalLenth - nOffsetLenth; // ��Ҫ��ȡ���ֽ�
//
//	//			unsigned int nOneContentSize = GetContentSize();
//	//			unsigned int nOnePageMaxSize = GetOnePageMaxSize();
//	//			unsigned int nPageOffset = nOffsetLenth % nOnePageMaxSize; // ҳ��ƫ��λ��
//
//	//			unsigned int nCopyLenth = 0; // ��¼�Ѿ����Ƶĳ���
//	//			POSITION pos = listPageNo.GetHeadPosition();
//	//			while (pos)
//	//			{
//	//				unsigned int nPageNo = listPageNo.GetNext(pos);
//	//				assert(nPageNo != 0);
//
//	//				unsigned int nCurrentLenth = min(nOnePageMaxSize - nPageOffset, nRetLenth - nCopyLenth); // ��ǰ��Ҫ���Ƶĸ���
//	//				if (nCurrentLenth == 0)
//	//				{// �Ѿ���ȡ��� ����Ҫ�ٶ�ȡ
//	//					break;
//	//				}
//
//	//				if (m_pMMFContent->Read((nPageNo - 1) * nOneContentSize + sizeof(MMFCachePageInfo) + nPageOffset, pBuffer + nCopyLenth, nCurrentLenth))
//	//				{
//	//					nCopyLenth += nCurrentLenth;
//	//					nPageOffset = 0; // ֻ�е�һ�λ���Ҫ����ƫ��λ�ã�֮���Ǵӿ�ͷ��ʼ��ȡ
//	//				}
//	//				else
//	//				{// �����ļ��������ļ���ƥ��
//	//					assert(FALSE);
//	//					nRetLenth = 0;
//	//					break;
//	//				}
//	//			}
//	//		}
//	//	}
//	//	return nRetLenth;
//	//};
//
//
//	bool        Write(CodeInfo& codeInfo, const char* pBuffer, unsigned int nBufferLenth, bool bAppend = FALSE)
//	{// ѡ��д��ķ�ʽ
//		return bAppend ? WriteAppend(codeInfo, pBuffer, nBufferLenth)
//			: WriteOverlap(codeInfo, pBuffer, nBufferLenth);
//	};
//
//	unsigned int		GetIndexSize() const   // һֻ���������Ĵ�С
//	{
//		return sizeof(CodeInfo) + m_indexHead.m_nIndexCapability * sizeof(MMFCachePageInfo<CodeInfo>);
//	};
//
//	unsigned int      GetContentSize() const // һ�����ݴ洢��Ϣ�Ĵ�С
//	{
//		return sizeof(MMFCachePageInfo<CodeInfo>) + GetOnePageMaxSize();
//	};
//
//	unsigned int      GetOnePageMaxSize() const     // һҳ�ܹ��洢��Ϣ������С
//	{
//		return m_indexHead.m_nPageCapability * m_nOneStructSize;
//	};
//
//	unsigned int      GetOneCodeInfoMaxSize() const // ��ȡһֻ��������ܹ��洢������
//	{
//		return m_indexHead.m_nIndexCapability * m_indexHead.m_nPageCapability * m_nOneStructSize;
//	};
//	bool        IsPageFull(const MMFCachePageInfo<CodeInfo>& pageInfo) const       // �ж�һҳ�Ƿ��Ѿ�����
//	{
//		return pageInfo.m_nCount == m_indexHead.m_nPageCapability;
//	};
//	unsigned int      GetPageEmptySpace(const MMFCachePageInfo<CodeInfo>& pageInfo) const// ��ȡһҳ����Ŀ������� 
//	{
//		return min(GetOnePageMaxSize(), (m_indexHead.m_nPageCapability - pageInfo.m_nCount) * m_nOneStructSize);
//	};
//
//	static bool GetMarketName(HSMarketDataType nMarketType, std::string& strMarketName) {
//		switch (MakeMainMarket(nMarketType))
//		{
//		case SH_Bourse:	strMarketName = _T("���ڹ�Ʊ-��֤֤ȯ");	break;
//		case SZ_Bourse:	strMarketName = _T("���ڹ�Ʊ-��֤֤ȯ");	break;
//
//		case (OPTION_MARKET | OPTION_SH): strMarketName = _T("��Ȩ-�Ϻ���Ȩ");	break;
//		case (OPTION_MARKET | OPTION_SZ): strMarketName = _T("��Ȩ-������Ȩ");	break;
//		case (OPTION_MARKET | OPTION_FUTURES_GUZHI): strMarketName = _T("��Ȩ-�н���Ȩ");	break;
//		case (OPTION_MARKET | OPTION_FUTURES_SH): strMarketName = _T("��Ȩ-�Ϻ��ڻ���Ȩ");	break;
//		case (OPTION_MARKET | OPTION_FUTURES_DL): strMarketName = _T("��Ȩ-�����ڻ���Ȩ");	break;
//		case (OPTION_MARKET | OPTION_FUTURES_ZZ): strMarketName = _T("��Ȩ-֣���ڻ���Ȩ");	break;
//
//		case (FUTURES_MARKET | DALIAN_BOURSE):		strMarketName = _T("�ڻ�-�����ڻ�");		break;
//		case (FUTURES_MARKET | SHANGHAI_BOURSE): 	strMarketName = _T("�ڻ�-�Ϻ��ڻ�");		break;
//		case (FUTURES_MARKET | ZHENGZHOU_BOURSE):	strMarketName = _T("�ڻ�-֣���ڻ�");		break;
//		case (FUTURES_MARKET | HUANGJIN_BOURSE):	strMarketName = _T("�ڻ�-�ƽ��ڻ�");		break;
//		case (FUTURES_MARKET | GUZHI_BOURSE):		strMarketName = _T("�ڻ�-��ָ�ڻ�");		break;
//
//		case (CAE_MARKET | AUCTION_AGGREGATE):      strMarketName = _T("�Ľ���-���Ͼ���");	break;
//		case (CAE_MARKET | AUCTION_DYNAMIC):        strMarketName = _T("�Ľ���-��̬����");	break;
//		case (CAE_MARKET | AUCTION_GENERAL):        strMarketName = _T("�Ľ���-����");	    break;
//
//		case (COMMODITIES_MARKET | SGE_BOURSE):     strMarketName = _T("��Ʒ-�ƽ����");    break;
//		case (COMMODITIES_MARKET | SP_CG_BOURSE):   strMarketName = _T("��Ʒ-������Ʒ");    break;
//		case (COMMODITIES_MARKET | SP_GT_BOURSE):   strMarketName = _T("��Ʒ-���콻��");    break;
//		case (COMMODITIES_MARKET | BARGAIN_BOURSE): strMarketName = _T("��Ʒ-Э�����");    break;
//		case (COMMODITIES_MARKET | PRICE_BOURSE):   strMarketName = _T("��Ʒ-���۽���");    break;
//
//			//case (FOREIGN_MARKET | WH_BASE_RATE):		strMarketName = _T("���-��������");  	break;
//			//case (FOREIGN_MARKET | WH_ACROSS_RATE): 	strMarketName = _T("���-�������");  	break;
//			//case (FOREIGN_MARKET | WH_FUTURES_RATE):	strMarketName = _T("���-�ڻ�");  		break;
//
//		case (HK_MARKET | HK_BOURSE):		strMarketName = _T("�۹�-�����г�");      	break;
//		case (HK_MARKET | GE_BOURSE):		strMarketName = _T("�۹�-��ҵ���г�");   	break;
//		case (HK_MARKET | INDEX_BOURSE):		strMarketName = _T("�۹�-ָ���г�");	        break;
//
//		default:
//		{
//			strMarketName = _T("δ֪�г�");
//			//assert(FALSE);
//			return FALSE;
//		}
//		}
//		return TRUE;
//	};
//protected:
//	bool   Release()
//	{
//		if (m_pMMFIndex)
//		{
//			delete m_pMMFIndex;
//			m_pMMFIndex = NULL;
//		}
//		m_mapCodeToIndex.clear();
//
//		if (m_pMMFContent)
//		{
//			delete m_pMMFContent;
//			m_pMMFContent = NULL;
//		}
//
//		return FALSE;
//	};
//
//	bool   InitIndexFile() {
//		assert(m_pMMFIndex);
//		unsigned int nFileSize = (unsigned int)m_pMMFIndex->GetFileSize();
//		unsigned int nHeadSize = sizeof(MMFCacheIndexFileHead);
//		if (nFileSize < nHeadSize)
//		{
//			return FALSE;
//		}
//
//		MMFCacheIndexFileHead head;
//		if (m_pMMFIndex->Read(0, (char*)&head, nHeadSize))
//		{
//			if (head.m_nVersion != FILE_VERSION)
//			{// �汾�Ų�ƥ�� ����ļ�
//				m_pMMFIndex->ClearFile();
//				m_pMMFIndex->Write(0, (char*)&m_indexHead, sizeof(MMFCacheIndexFileHead));
//				m_nIndexEndOff = sizeof(MMFCacheIndexFileHead);
//
//				if (m_pMMFContent)
//				{
//					m_pMMFContent->ClearFile();
//				}
//				return FALSE;
//			}
//
//			memcpy(&m_indexHead, &head, sizeof(MMFCacheIndexFileHead));
//
//			unsigned int nOneIndexSize = GetIndexSize();
//			unsigned int nOffer = nHeadSize;
//			CodeInfo codeInfo;
//			while (nOffer < nFileSize)
//			{
//				if (m_pMMFIndex->Read(nOffer, (char*)&codeInfo, sizeof(CodeInfo)))
//				{// �洢ÿһ������ҳ����ʼλ��
//				 //HSLOG_DEBUG(_T("codeInfo in index '%s'  '%s' ,file %s ,%d"), codeInfo.GetCode(), codeInfo.GetMarket(), m_pMMFIndex->getFilePath(), nOffer);
//					if (codeInfo.m_cCodeType)
//						m_mapCodeToIndex.insert(std::make_pair(codeInfo, nOffer + sizeof(CodeInfo)));
//					else
//						break;
//				}
//				else
//				{
//					assert(FALSE);
//					return FALSE;
//				}
//
//				nOffer += nOneIndexSize;
//			}
//			m_nIndexEndOff = nOffer; // ��¼ĩβ��ƫ����
//
//			return TRUE;
//		}
//		return FALSE;
//	};
//
//
//	bool   WriteAppend(const CodeInfo& codeInfo, const char* pBuffer, unsigned int nBufferLenth) {
//		//HSLOG_DEBUG(_T("codeInfo in write append '%s'  '%s'"), codeInfo.GetCode(), codeInfo.GetMarket());
//		bool bRet = FALSE;
//		if (pBuffer == NULL || nBufferLenth == 0)
//		{
//			return bRet;
//		}
//
//		unsigned int nCopyLenth = 0;         // ʵ�ʿ�������
//		const char* pCopyBegin = NULL; // ��ʼλ��
//		unsigned int nCopyLenthBackUp = 0;   // �Ѿ�д��ĳ���
//		unsigned int nPageFullCount = 0;     // ��¼�Ѿ��������ҳ����
//		std::list<MMFCachePageInfo<CodeInfo>> listPageNoBackUpNotFull;// �Ѿ�д�����ݲ���û��д����ҳ��
//
//		unsigned int nOffset = 0;
//		unsigned int nCodeOffset = 0;
//		std::unordered_map<CodeInfo, int>::iterator it = m_mapCodeToIndex.find(codeInfo);
//		if (it != m_mapCodeToIndex.end())
//		{// �����Ѿ����� 
//			nOffset = it->second;
//			MMFCachePageInfo<CodeInfo> pageInfo;
//			for (unsigned int i = 0; i < m_indexHead.m_nIndexCapability; i++)
//			{
//				if (m_pMMFIndex->Read(nOffset + i * sizeof(MMFCachePageInfo<CodeInfo>), (char*)&pageInfo, sizeof(MMFCachePageInfo<CodeInfo>))
//					&& pageInfo.m_code.CompareCodeByMainMarket(&codeInfo)
//					)
//				{
//					nCopyLenthBackUp += (pageInfo.m_nCount * m_nOneStructSize);// �ۻ��Ѿ�д��ĳ���
//					if (!IsPageFull(pageInfo))
//					{// ��¼δд����ҳ����
//						listPageNoBackUpNotFull.push_back(pageInfo);
//						break;
//					}
//					else
//					{
//						nPageFullCount++;
//					}
//				}
//				else
//				{
//					break;
//				}
//			}
//
//			if (nCopyLenthBackUp >= GetOneCodeInfoMaxSize())
//			{// �����Ѿ�д���� �޷�д��
//				return bRet;
//			}
//		}
//		else
//		{// �����Ӵ���
//
//		 // ƫ�Ƶ����
//			nOffset = m_nIndexEndOff + sizeof(CodeInfo);
//			m_nIndexEndOff += GetIndexSize();
//			// ���뵽����
//			m_mapCodeToIndex.insert(std::make_pair(codeInfo, nOffset));
//		}
//		nCodeOffset = nOffset - sizeof(CodeInfo);
//
//		nCopyLenth = min(nBufferLenth, GetOneCodeInfoMaxSize() - nCopyLenthBackUp);
//		pCopyBegin = pBuffer + (nBufferLenth - nCopyLenth);
//
//		// ����ҳ�ſ�ʼд�ļ� �������ļ���ʼд ��һ��д��ʱ���������� ���������������������ȡ�����������
//		while (nCopyLenth != 0)
//		{
//			if (!listPageNoBackUpNotFull.empty())
//			{// �ȴ�δд����ҳ ����д
//				MMFCachePageInfo<CodeInfo> pageInfoBackUp = listPageNoBackUpNotFull.front();
//				listPageNoBackUpNotFull.pop_front();
//				unsigned int nPageOffset = (pageInfoBackUp.m_nPageNo - 1) * GetContentSize();
//				unsigned int nOnePageLenth = min(GetPageEmptySpace(pageInfoBackUp), nCopyLenth);
//
//				MMFCachePageInfo<CodeInfo> pageInfo;
//				pageInfo.m_nPageNo = pageInfoBackUp.m_nPageNo;
//				pageInfo.m_code = pageInfoBackUp.m_code;
//				pageInfo.m_nCount = pageInfoBackUp.m_nCount + nOnePageLenth / m_nOneStructSize;
//				assert(pageInfo.m_nCount <= m_indexHead.m_nPageCapability);
//				pageInfo.m_nOffSet = pageInfoBackUp.m_nOffSet + nOnePageLenth;
//				m_pMMFContent->Write(nPageOffset, (char*)&pageInfo, sizeof(MMFCachePageInfo<CodeInfo>));   // дҳ����Ϣ
//
//				m_pMMFContent->Write(pageInfoBackUp.m_nOffSet, pCopyBegin, nOnePageLenth);       // д����
//				pCopyBegin += nOnePageLenth;
//
//				m_pMMFIndex->Write(nOffset + nPageFullCount * sizeof(MMFCachePageInfo<CodeInfo>), (char*)&pageInfo, sizeof(MMFCachePageInfo<CodeInfo>));  // д�����ļ�
//
//				nCopyLenth = nCopyLenth < nOnePageLenth ? 0 : nCopyLenth - nOnePageLenth;
//				nPageFullCount++; // �����֮�� ������һ
//			}
//			else
//			{// ������ҳ 
//				unsigned int nPageNo = m_indexHead.m_nPageNo + 1;
//				m_indexHead.m_nPageNo++;
//
//				unsigned int nPageOffset = (nPageNo - 1) * GetContentSize();
//				unsigned int nOnePageLenth = min(GetOnePageMaxSize(), nCopyLenth);
//
//				MMFCachePageInfo<CodeInfo> pageInfo;
//				pageInfo.m_nPageNo = nPageNo;
//				pageInfo.m_code = codeInfo;
//				pageInfo.m_nCount = nOnePageLenth / m_nOneStructSize;
//				assert(pageInfo.m_nCount <= m_indexHead.m_nPageCapability);
//				pageInfo.m_nOffSet = nPageOffset + sizeof(MMFCachePageInfo<CodeInfo>) + nOnePageLenth;
//
//				m_pMMFContent->Write(nPageOffset, (char*)&pageInfo, sizeof(MMFCachePageInfo<CodeInfo>));           // дҳ����Ϣ
//				m_pMMFContent->Write(nPageOffset + sizeof(MMFCachePageInfo<CodeInfo>), pCopyBegin, nOnePageLenth); // д����
//				pCopyBegin += nOnePageLenth;
//
//				m_pMMFIndex->Write(nOffset + nPageFullCount * sizeof(MMFCachePageInfo<CodeInfo>), (char*)&pageInfo, sizeof(MMFCachePageInfo<CodeInfo>));  // д�����ļ�		
//
//				nCopyLenth = nCopyLenth < nOnePageLenth ? 0 : nCopyLenth - nOnePageLenth;
//				nPageFullCount++; // �����֮�� ������һ
//			}
//		}
//
//		m_pMMFIndex->Write(nCodeOffset, (char*)&codeInfo, sizeof(CodeInfo));          // д�����ļ�������Ϣ
//		m_pMMFIndex->Write(0, (char*)&m_indexHead, sizeof(MMFCacheIndexFileHead));    // д�����ļ�ͷ����Ϣ
//
//		return bRet;
//	};
//
//	bool   WriteOverlap(const CodeInfo& codeInfo, const char* pBuffer, unsigned int nBufferLenth) {
//		bool bRet = FALSE;
//		if (pBuffer == NULL || nBufferLenth == 0)
//		{
//			return bRet;
//		}
//
//		// ʵ�ʿ������� �� ��ʼλ��
//		unsigned int nCopyLenth = min(GetOneCodeInfoMaxSize(), nBufferLenth);
//		const char* pCopyBegin = pBuffer + (nBufferLenth - nCopyLenth);
//		// ������Ҫ��ҳ��
//		unsigned int nPageInfoCount = (nCopyLenth + GetOnePageMaxSize() - 1) / GetOnePageMaxSize();
//
//		std::list<unsigned int> listPageNo;
//		unsigned int nOffset = 0;
//		unsigned int nCodeOffset = 0;
//		std::unordered_map<CodeInfo, int>::iterator it = m_mapCodeToIndex.find(codeInfo);
//		if (it != m_mapCodeToIndex.end())
//		{// �����Ѿ����� 
//			nOffset = it->second;
//			std::list<unsigned int> listPageNoBackUp;
//			MMFCachePageInfo<CodeInfo> pageInfo;
//			for (unsigned int i = 0; i < m_indexHead.m_nIndexCapability; i++)
//			{
//				if (m_pMMFIndex->Read(nOffset + i * sizeof(MMFCachePageInfo<CodeInfo>), (char*)&pageInfo, sizeof(MMFCachePageInfo<CodeInfo>))
//					&& pageInfo.m_code.CompareCodeByMainMarket(&codeInfo)
//					)
//				{
//					listPageNoBackUp.push_back(pageInfo.m_nPageNo); // ��¼ҳ����
//				}
//				else
//				{
//					break;
//				}
//			}
//
//
//			for (auto it = listPageNoBackUp.begin(); it != listPageNoBackUp.end(); ++it)
//			{
//				listPageNo.push_back(*it);
//			}
//
//			while (listPageNo.size() < nPageInfoCount)
//			{// ֮ǰд����ҳ�������� ��Ҫ�����µ�ҳ
//				m_indexHead.m_nPageNo++;
//				listPageNo.push_back(m_indexHead.m_nPageNo);
//			}
//		}
//		else
//		{// �����Ӵ���
//
//		 // ƫ�Ƶ����
//			nOffset = m_nIndexEndOff + sizeof(CodeInfo);
//			m_nIndexEndOff += GetIndexSize();
//			// ���뵽����
//			m_mapCodeToIndex.insert(std::make_pair(codeInfo, nOffset));
//
//			// ��ʼ���ɵ�ǰ��������Ҫд���ҳ��
//			for (unsigned int i = 0; i < nPageInfoCount; i++)
//			{// ҳ���ǵ�ǰҳ����֮���ۼ� ȫ��������ҳ
//				listPageNo.push_back(m_indexHead.m_nPageNo + i + 1);
//			}
//			m_indexHead.m_nPageNo += nPageInfoCount;
//		}
//		nCodeOffset = nOffset - sizeof(CodeInfo);
//
//		// ����ҳ�ſ�ʼд�ļ� �������ļ���ʼд ��һ��д��ʱ���������� ���������������������ȡ�����������
//		for (auto it = listPageNo.begin(); it != listPageNo.end(); ++it)
//		{
//			unsigned int nPageNo = *it;
//			unsigned int nOnePageLenth = min(GetOnePageMaxSize(), nCopyLenth);
//			nCopyLenth = nCopyLenth > GetOnePageMaxSize() ? nCopyLenth - GetOnePageMaxSize() : 0;
//
//			unsigned int nPageOffset = (nPageNo - 1) * GetContentSize();
//
//			MMFCachePageInfo<CodeInfo> pageInfo;
//			pageInfo.m_nPageNo = nPageNo;
//			pageInfo.m_code = codeInfo;
//			pageInfo.m_nCount = nOnePageLenth / m_nOneStructSize;
//			pageInfo.m_nOffSet = nPageOffset + sizeof(MMFCachePageInfo<CodeInfo>) + nOnePageLenth;
//
//			m_pMMFContent->Write(nPageOffset, (char*)&pageInfo, sizeof(MMFCachePageInfo<CodeInfo>));           // дҳ����Ϣ
//			m_pMMFContent->Write(nPageOffset + sizeof(MMFCachePageInfo<CodeInfo>), pCopyBegin, nOnePageLenth); // д����
//			pCopyBegin += nOnePageLenth;
//
//			m_pMMFIndex->Write(nOffset, (char*)&pageInfo, sizeof(MMFCachePageInfo<CodeInfo>));  // д�����ļ�ҳ��Ϣ
//			nOffset += sizeof(MMFCachePageInfo<CodeInfo>);
//		}
//
//		m_pMMFIndex->Write(nCodeOffset, (char*)&codeInfo, sizeof(CodeInfo));          // д�����ļ�������Ϣ
//		m_pMMFIndex->Write(0, (char*)&m_indexHead, sizeof(MMFCacheIndexFileHead));    // д�����ļ�ͷ����Ϣ
//
//		return bRet;
//	};
//private:
//	MMFCacheIndexFileHead  m_indexHead; // ����ͷ����Ϣ
//	unsigned int      m_nOneStructSize;       // �洢�ĵ����ṹ���С
//
//	CMMF*       m_pMMFIndex;           // �����ļ�
//												// �����ļ�����
//	std::unordered_map<CodeInfo, int> m_mapCodeToIndex;
//	unsigned int      m_nIndexEndOff;         // �����ļ�ĩβƫ����
//
//	CMMF*       m_pMMFContent;          // �����ļ�
//
//};



