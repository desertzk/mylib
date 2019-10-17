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








// 缓存类
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
					nTotalLenth += pageInfo.m_nCount * m_nOneStructSize; // 累加存储的信息大小
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
		unsigned int nCopyLenth = 0; // 记录已经复制的长度
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
					listPageNo.push_back(pageInfo.m_nPageNo); // 记录页面编号
					nTotalLenth += pageInfo.m_nCount * m_nOneStructSize; // 累加存储的信息大小
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
					{// 已经读取完成
						break;
					}

					if (m_pMMFContent->Read((nPageNo - 1) * nOneContentSize + sizeof(MMFCachePageInfo<IndexKey>), pBuffer + nCopyLenth, nCurrentLenth))
					{
						nCopyLenth += nCurrentLenth;
					}
					else
					{// 索引文件和内容文件不匹配
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
	//					listPageNo.push_back(pageInfo.m_nPageNo); // 记录页面编号
	//				}

	//				nTotalLenth += pageInfo.m_nCount * m_nOneStructSize; // 累加存储的信息大小
	//			}
	//			else
	//			{
	//				break;
	//			}
	//		}

	//		if (pBuffer != NULL && !listPageNo.IsEmpty() && nTotalLenth > nOffsetLenth)
	//		{
	//			nRetLenth = nTotalLenth - nOffsetLenth; // 需要读取的字节

	//			unsigned int nOneContentSize = GetContentSize();
	//			unsigned int nOnePageMaxSize = GetOnePageMaxSize();
	//			unsigned int nPageOffset = nOffsetLenth % nOnePageMaxSize; // 页的偏移位置

	//			unsigned int nCopyLenth = 0; // 记录已经复制的长度
	//			POSITION pos = listPageNo.GetHeadPosition();
	//			while (pos)
	//			{
	//				unsigned int nPageNo = listPageNo.GetNext(pos);
	//				assert(nPageNo != 0);

	//				unsigned int nCurrentLenth = min(nOnePageMaxSize - nPageOffset, nRetLenth - nCopyLenth); // 当前需要复制的个数
	//				if (nCurrentLenth == 0)
	//				{// 已经读取完成 不需要再读取
	//					break;
	//				}

	//				if (m_pMMFContent->Read((nPageNo - 1) * nOneContentSize + sizeof(MMFCachePageInfo) + nPageOffset, pBuffer + nCopyLenth, nCurrentLenth))
	//				{
	//					nCopyLenth += nCurrentLenth;
	//					nPageOffset = 0; // 只有第一次会需要计算偏移位置，之后都是从开头开始读取
	//				}
	//				else
	//				{// 索引文件和内容文件不匹配
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
	{// 选择写入的方式
		return bAppend ? WriteAppend(codeInfo, pBuffer, nBufferLenth)
			: WriteOverlap(codeInfo, pBuffer, nBufferLenth);
	};

	unsigned int		GetIndexSize() const   // 一只代码索引的大小
	{
		return sizeof(IndexKey) + m_indexHead.m_nIndexCapability * sizeof(MMFCachePageInfo<IndexKey>);
	};
	
	unsigned int      GetContentSize() const // 一条数据存储信息的大小
	{
		return sizeof(MMFCachePageInfo<IndexKey>) + GetOnePageMaxSize();
	};

	unsigned int      GetOnePageMaxSize() const     // 一页能够存储信息的最大大小
	{
		return m_indexHead.m_nPageCapability * m_nOneStructSize;
	};

	unsigned int      GetOneCodeInfoMaxSize() const // 获取一只代码最大能够存储的容量
	{
		return m_indexHead.m_nIndexCapability * m_indexHead.m_nPageCapability * m_nOneStructSize;
	};
	bool        IsPageFull(const MMFCachePageInfo<IndexKey>& pageInfo) const       // 判断一页是否已经填满
	{
		return pageInfo.m_nCount == m_indexHead.m_nPageCapability;
	};
	unsigned int      GetPageEmptySpace(const MMFCachePageInfo<IndexKey>& pageInfo) const// 获取一页里面的空余内容 
	{
		return min(GetOnePageMaxSize(), (m_indexHead.m_nPageCapability - pageInfo.m_nCount) * m_nOneStructSize);
	};

	//static bool GetMarketName(HSMarketDataType nMarketType, CString& strMarketName) {
	//	switch (MakeMainMarket(nMarketType))
	//	{
	//	case SH_Bourse:	strMarketName = _T("国内股票-上证证券");	break;
	//	case SZ_Bourse:	strMarketName = _T("国内股票-深证证券");	break;

	//	case (OPTION_MARKET | OPTION_SH): strMarketName = _T("期权-上海期权");	break;
	//	case (OPTION_MARKET | OPTION_SZ): strMarketName = _T("期权-深圳期权");	break;
	//	case (OPTION_MARKET | OPTION_FUTURES_GUZHI): strMarketName = _T("期权-中金期权");	break;
	//	case (OPTION_MARKET | OPTION_FUTURES_SH): strMarketName = _T("期权-上海期货期权");	break;
	//	case (OPTION_MARKET | OPTION_FUTURES_DL): strMarketName = _T("期权-大连期货期权");	break;
	//	case (OPTION_MARKET | OPTION_FUTURES_ZZ): strMarketName = _T("期权-郑州期货期权");	break;

	//	case (FUTURES_MARKET | DALIAN_BOURSE):		strMarketName = _T("期货-大连期货");		break;
	//	case (FUTURES_MARKET | SHANGHAI_BOURSE): 	strMarketName = _T("期货-上海期货");		break;
	//	case (FUTURES_MARKET | ZHENGZHOU_BOURSE):	strMarketName = _T("期货-郑州期货");		break;
	//	case (FUTURES_MARKET | HUANGJIN_BOURSE):	strMarketName = _T("期货-黄金期货");		break;
	//	case (FUTURES_MARKET | GUZHI_BOURSE):		strMarketName = _T("期货-股指期货");		break;

	//	case (CAE_MARKET | AUCTION_AGGREGATE):      strMarketName = _T("文交所-集合竞价");	break;
	//	case (CAE_MARKET | AUCTION_DYNAMIC):        strMarketName = _T("文交所-动态竞价");	break;
	//	case (CAE_MARKET | AUCTION_GENERAL):        strMarketName = _T("文交所-常规");	    break;

	//	case (COMMODITIES_MARKET | SGE_BOURSE):     strMarketName = _T("商品-黄金白银");    break;
	//	case (COMMODITIES_MARKET | SP_CG_BOURSE):   strMarketName = _T("商品-常规商品");    break;
	//	case (COMMODITIES_MARKET | SP_GT_BOURSE):   strMarketName = _T("商品-跨天交易");    break;
	//	case (COMMODITIES_MARKET | BARGAIN_BOURSE): strMarketName = _T("商品-协商议价");    break;
	//	case (COMMODITIES_MARKET | PRICE_BOURSE):   strMarketName = _T("商品-定价交易");    break;

	//		//case (FOREIGN_MARKET | WH_BASE_RATE):		strMarketName = _T("外汇-基本汇率");  	break;
	//		//case (FOREIGN_MARKET | WH_ACROSS_RATE): 	strMarketName = _T("外汇-交叉汇率");  	break;
	//		//case (FOREIGN_MARKET | WH_FUTURES_RATE):	strMarketName = _T("外汇-期汇");  		break;

	//	case (HK_MARKET | HK_BOURSE):		strMarketName = _T("港股-主板市场");      	break;
	//	case (HK_MARKET | GE_BOURSE):		strMarketName = _T("港股-创业板市场");   	break;
	//	case (HK_MARKET | INDEX_BOURSE):		strMarketName = _T("港股-指数市场");	        break;

	//	default:
	//	{
	//		strMarketName = _T("未知市场");
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
			{// 版本号不匹配 清空文件
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
				{// 存储每一个代码页的起始位置
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
			m_nIndexEndOff = nOffer; // 记录末尾的偏移量

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

		unsigned int nCopyLenth = 0;         // 实际拷贝长度
		const char* pCopyBegin = NULL; // 起始位置
		unsigned int nCopyLenthBackUp = 0;   // 已经写入的长度
		unsigned int nPageFullCount = 0;     // 记录已经填充满的页数量
		std::list<MMFCachePageInfo<IndexKey>> listPageNoBackUpNotFull;// 已经写入数据并且没有写满的页号

		unsigned int nOffset = 0;
		unsigned int nCodeOffset = 0;
		std::unordered_map<IndexKey, int>::iterator it = m_mapCodeToIndex.find(codeInfo);
		if (it != m_mapCodeToIndex.end())
		{// 代码已经存在 
			nOffset = it->second;
			MMFCachePageInfo<IndexKey> pageInfo;
			for (unsigned int i = 0; i < m_indexHead.m_nIndexCapability; ++i)
			{
				if (m_pMMFIndex->Read(nOffset + i * sizeof(MMFCachePageInfo<IndexKey>), (char*)&pageInfo, sizeof(MMFCachePageInfo<IndexKey>))
					&& pageInfo.m_nPageNo>0)
				{
					nCopyLenthBackUp += (pageInfo.m_nCount * m_nOneStructSize);// 累积已经写入的长度
					//int overflowcount = pageInfo.m_nCount + nBufferLenth / m_nOneStructSize - m_indexHead.m_nPageCapability;
					
					//pageInfo.m_nCount + nBufferLenth / m_nOneStructSize;
					//if (overflowcount <=0)
					if(!IsPageFull(pageInfo))
					{// 记录未写满的页面编号

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
			{// 本地已经写满了 无法写入
				return bRet;
			}
		}
		else
		{// 新增加代码

		 // 偏移到最后
			nOffset = m_nIndexEndOff + sizeof(IndexKey);
			m_nIndexEndOff += GetIndexSize();
			++m_indexHead.m_nIndexCount;
			// 加入到缓存
			m_mapCodeToIndex.insert(std::make_pair(codeInfo, nOffset));
		}
		nCodeOffset = nOffset - sizeof(IndexKey);
		nCopyLenth = min(nBufferLenth, GetOneCodeInfoMaxSize() - nCopyLenthBackUp);
		pCopyBegin = pBuffer + (nBufferLenth - nCopyLenth);
		/*nCopyLenth = min(nBufferLenth, GetOnePageMaxSize() - nCopyLenthBackUp);
		pCopyBegin = pBuffer;
		int remainLenth = nBufferLenth - nCopyLenth;*/
		// 根据页号开始写文件 从内容文件开始写 万一在写的时候程序崩溃了 这样不会引起根据索引读取到错误的内容
		while (nCopyLenth != 0)
		{
			if (!listPageNoBackUpNotFull.empty())
			{// 先从未写满的页 继续写
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
				m_pMMFContent->Write(nPageOffset, (char*)&pageInfo, sizeof(MMFCachePageInfo<IndexKey>));   // 写页面信息

				m_pMMFContent->Write(pageInfoBackUp.m_nOffSet, pCopyBegin, nOnePageLenth);       // 写数据
				pCopyBegin += nOnePageLenth;

				m_pMMFIndex->Write(nOffset + nPageFullCount * sizeof(MMFCachePageInfo<IndexKey>), (char*)&pageInfo, sizeof(MMFCachePageInfo<IndexKey>));  // 写索引文件

				nCopyLenth = nCopyLenth < nOnePageLenth ? 0 : nCopyLenth - nOnePageLenth;
				nPageFullCount++; // 填充完之后 数量加一
			}
			else
			{// 新申请页 
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

				m_pMMFContent->Write(nPageOffset, (char*)&pageInfo, sizeof(MMFCachePageInfo<IndexKey>));           // 写页面信息
				m_pMMFContent->Write(nPageOffset + sizeof(MMFCachePageInfo<IndexKey>), pCopyBegin, nOnePageLenth); // 写数据
				pCopyBegin += nOnePageLenth;

				m_pMMFIndex->Write(nOffset + nPageFullCount * sizeof(MMFCachePageInfo<IndexKey>), (char*)&pageInfo, sizeof(MMFCachePageInfo<IndexKey>));  // 写索引文件		

				nCopyLenth = nCopyLenth < nOnePageLenth ? 0 : nCopyLenth - nOnePageLenth;
				nPageFullCount++; // 填充完之后 数量加一
			}
		}

		m_pMMFIndex->Write(nCodeOffset, (char*)&codeInfo, sizeof(IndexKey));          // 写索引文件代码信息
		m_pMMFIndex->Write(0, (char*)&m_indexHead, sizeof(MMFCacheIndexFileHead));    // 写索引文件头部信息

		return bRet;
	};
	
	bool   WriteOverlap(const IndexKey& codeInfo, const char* pBuffer, unsigned int nBufferLenth) {
		bool bRet = FALSE;
		if (pBuffer == NULL || nBufferLenth == 0)
		{
			return bRet;
		}

		// 实际拷贝长度 和 起始位置
		unsigned int nCopyLenth = min(GetOneCodeInfoMaxSize(), nBufferLenth);
		const char* pCopyBegin = pBuffer + (nBufferLenth - nCopyLenth);
		// 计算需要的页数
		unsigned int nPageInfoCount = (nCopyLenth + GetOnePageMaxSize() - 1) / GetOnePageMaxSize();

		std::list<unsigned int> listPageNo;
		unsigned int nOffset = 0;
		unsigned int nCodeOffset = 0;
		std::unordered_map<IndexKey, int>::iterator it = m_mapCodeToIndex.find(codeInfo);
		if (it != m_mapCodeToIndex.end())
		{// 代码已经存在 
			nOffset = it->second;
			std::list<unsigned int> listPageNoBackUp;
			MMFCachePageInfo<IndexKey> pageInfo;
			for (unsigned int i = 0; i < m_indexHead.m_nIndexCapability; i++)
			{
				if (m_pMMFIndex->Read(nOffset + i * sizeof(MMFCachePageInfo<IndexKey>), (char*)&pageInfo, sizeof(MMFCachePageInfo<IndexKey>))
					&& pageInfo.m_nPageNo>0)
				{
					listPageNoBackUp.push_back(pageInfo.m_nPageNo); // 记录页面编号
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
			{// 之前写过的页数量不够 需要申请新的页
				m_indexHead.m_nPageNo++;
				listPageNo.push_back(m_indexHead.m_nPageNo);
			}
		}
		else
		{// 新增加代码

		 // 偏移到最后
			nOffset = m_nIndexEndOff + sizeof(IndexKey);
			m_nIndexEndOff += GetIndexSize();
			++m_indexHead.m_nIndexCount;
			// 加入到缓存
			m_mapCodeToIndex.insert(std::make_pair(codeInfo, nOffset));

			// 开始生成当前数据所需要写入的页号
			for (unsigned int i = 0; i < nPageInfoCount; i++)
			{// 页号是当前页总数之后累加 全部采用新页
				listPageNo.push_back(m_indexHead.m_nPageNo + i + 1);
			}
			m_indexHead.m_nPageNo += nPageInfoCount;
		}
		nCodeOffset = nOffset - sizeof(IndexKey);

		// 根据页号开始写文件 从内容文件开始写 万一在写的时候程序崩溃了 这样不会引起根据索引读取到错误的内容
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

			m_pMMFContent->Write(nPageOffset, (char*)&pageInfo, sizeof(MMFCachePageInfo<IndexKey>));           // 写页面信息
			m_pMMFContent->Write(nPageOffset + sizeof(MMFCachePageInfo<IndexKey>), pCopyBegin, nOnePageLenth); // 写数据
			pCopyBegin += nOnePageLenth;

			m_pMMFIndex->Write(nOffset, (char*)&pageInfo, sizeof(MMFCachePageInfo<IndexKey>));  // 写索引文件页信息
			nOffset += sizeof(MMFCachePageInfo<IndexKey>);
		}

		m_pMMFIndex->Write(nCodeOffset, (char*)&codeInfo, sizeof(IndexKey));          // 写索引文件代码信息
		m_pMMFIndex->Write(0, (char*)&m_indexHead, sizeof(MMFCacheIndexFileHead));    // 写索引文件头部信息

		return bRet;
	};
private:
	MMFCacheIndexFileHead  m_indexHead; // 索引头部信息
	unsigned int      m_nOneStructSize;       // 存储的单个结构体大小

	CMMF*       m_pMMFIndex;           // 索引文件
	// 索引文件缓存
	std::unordered_map<IndexKey,int> m_mapCodeToIndex;
	unsigned int      m_nIndexEndOff;         // 索引文件末尾偏移量
	
	CMMF*       m_pMMFContent;          // 内容文件
	
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
//					listPageNo.push_back(pageInfo.m_nPageNo); // 记录页面编号
//					nTotalLenth += pageInfo.m_nCount * m_nOneStructSize; // 累加存储的信息大小
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
//				unsigned int nCopyLenth = 0; // 记录已经复制的长度
//				for (auto it = listPageNo.begin(); it != listPageNo.end(); ++it)
//				{
//					unsigned int nPageNo = *it;
//					assert(nPageNo != 0);
//
//					unsigned int nCurrentLenth = min(nRetLenth - nCopyLenth, nOnePageMaxSize);
//					if (nCurrentLenth == 0)
//					{// 已经读取完成
//						break;
//					}
//
//					if (m_pMMFContent->Read((nPageNo - 1) * nOneContentSize + sizeof(MMFCachePageInfo<CodeInfo>), pBuffer + nCopyLenth, nCurrentLenth))
//					{
//						nCopyLenth += nCurrentLenth;
//					}
//					else
//					{// 索引文件和内容文件不匹配
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
//	//					listPageNo.push_back(pageInfo.m_nPageNo); // 记录页面编号
//	//				}
//
//	//				nTotalLenth += pageInfo.m_nCount * m_nOneStructSize; // 累加存储的信息大小
//	//			}
//	//			else
//	//			{
//	//				break;
//	//			}
//	//		}
//
//	//		if (pBuffer != NULL && !listPageNo.IsEmpty() && nTotalLenth > nOffsetLenth)
//	//		{
//	//			nRetLenth = nTotalLenth - nOffsetLenth; // 需要读取的字节
//
//	//			unsigned int nOneContentSize = GetContentSize();
//	//			unsigned int nOnePageMaxSize = GetOnePageMaxSize();
//	//			unsigned int nPageOffset = nOffsetLenth % nOnePageMaxSize; // 页的偏移位置
//
//	//			unsigned int nCopyLenth = 0; // 记录已经复制的长度
//	//			POSITION pos = listPageNo.GetHeadPosition();
//	//			while (pos)
//	//			{
//	//				unsigned int nPageNo = listPageNo.GetNext(pos);
//	//				assert(nPageNo != 0);
//
//	//				unsigned int nCurrentLenth = min(nOnePageMaxSize - nPageOffset, nRetLenth - nCopyLenth); // 当前需要复制的个数
//	//				if (nCurrentLenth == 0)
//	//				{// 已经读取完成 不需要再读取
//	//					break;
//	//				}
//
//	//				if (m_pMMFContent->Read((nPageNo - 1) * nOneContentSize + sizeof(MMFCachePageInfo) + nPageOffset, pBuffer + nCopyLenth, nCurrentLenth))
//	//				{
//	//					nCopyLenth += nCurrentLenth;
//	//					nPageOffset = 0; // 只有第一次会需要计算偏移位置，之后都是从开头开始读取
//	//				}
//	//				else
//	//				{// 索引文件和内容文件不匹配
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
//	{// 选择写入的方式
//		return bAppend ? WriteAppend(codeInfo, pBuffer, nBufferLenth)
//			: WriteOverlap(codeInfo, pBuffer, nBufferLenth);
//	};
//
//	unsigned int		GetIndexSize() const   // 一只代码索引的大小
//	{
//		return sizeof(CodeInfo) + m_indexHead.m_nIndexCapability * sizeof(MMFCachePageInfo<CodeInfo>);
//	};
//
//	unsigned int      GetContentSize() const // 一条数据存储信息的大小
//	{
//		return sizeof(MMFCachePageInfo<CodeInfo>) + GetOnePageMaxSize();
//	};
//
//	unsigned int      GetOnePageMaxSize() const     // 一页能够存储信息的最大大小
//	{
//		return m_indexHead.m_nPageCapability * m_nOneStructSize;
//	};
//
//	unsigned int      GetOneCodeInfoMaxSize() const // 获取一只代码最大能够存储的容量
//	{
//		return m_indexHead.m_nIndexCapability * m_indexHead.m_nPageCapability * m_nOneStructSize;
//	};
//	bool        IsPageFull(const MMFCachePageInfo<CodeInfo>& pageInfo) const       // 判断一页是否已经填满
//	{
//		return pageInfo.m_nCount == m_indexHead.m_nPageCapability;
//	};
//	unsigned int      GetPageEmptySpace(const MMFCachePageInfo<CodeInfo>& pageInfo) const// 获取一页里面的空余内容 
//	{
//		return min(GetOnePageMaxSize(), (m_indexHead.m_nPageCapability - pageInfo.m_nCount) * m_nOneStructSize);
//	};
//
//	static bool GetMarketName(HSMarketDataType nMarketType, std::string& strMarketName) {
//		switch (MakeMainMarket(nMarketType))
//		{
//		case SH_Bourse:	strMarketName = _T("国内股票-上证证券");	break;
//		case SZ_Bourse:	strMarketName = _T("国内股票-深证证券");	break;
//
//		case (OPTION_MARKET | OPTION_SH): strMarketName = _T("期权-上海期权");	break;
//		case (OPTION_MARKET | OPTION_SZ): strMarketName = _T("期权-深圳期权");	break;
//		case (OPTION_MARKET | OPTION_FUTURES_GUZHI): strMarketName = _T("期权-中金期权");	break;
//		case (OPTION_MARKET | OPTION_FUTURES_SH): strMarketName = _T("期权-上海期货期权");	break;
//		case (OPTION_MARKET | OPTION_FUTURES_DL): strMarketName = _T("期权-大连期货期权");	break;
//		case (OPTION_MARKET | OPTION_FUTURES_ZZ): strMarketName = _T("期权-郑州期货期权");	break;
//
//		case (FUTURES_MARKET | DALIAN_BOURSE):		strMarketName = _T("期货-大连期货");		break;
//		case (FUTURES_MARKET | SHANGHAI_BOURSE): 	strMarketName = _T("期货-上海期货");		break;
//		case (FUTURES_MARKET | ZHENGZHOU_BOURSE):	strMarketName = _T("期货-郑州期货");		break;
//		case (FUTURES_MARKET | HUANGJIN_BOURSE):	strMarketName = _T("期货-黄金期货");		break;
//		case (FUTURES_MARKET | GUZHI_BOURSE):		strMarketName = _T("期货-股指期货");		break;
//
//		case (CAE_MARKET | AUCTION_AGGREGATE):      strMarketName = _T("文交所-集合竞价");	break;
//		case (CAE_MARKET | AUCTION_DYNAMIC):        strMarketName = _T("文交所-动态竞价");	break;
//		case (CAE_MARKET | AUCTION_GENERAL):        strMarketName = _T("文交所-常规");	    break;
//
//		case (COMMODITIES_MARKET | SGE_BOURSE):     strMarketName = _T("商品-黄金白银");    break;
//		case (COMMODITIES_MARKET | SP_CG_BOURSE):   strMarketName = _T("商品-常规商品");    break;
//		case (COMMODITIES_MARKET | SP_GT_BOURSE):   strMarketName = _T("商品-跨天交易");    break;
//		case (COMMODITIES_MARKET | BARGAIN_BOURSE): strMarketName = _T("商品-协商议价");    break;
//		case (COMMODITIES_MARKET | PRICE_BOURSE):   strMarketName = _T("商品-定价交易");    break;
//
//			//case (FOREIGN_MARKET | WH_BASE_RATE):		strMarketName = _T("外汇-基本汇率");  	break;
//			//case (FOREIGN_MARKET | WH_ACROSS_RATE): 	strMarketName = _T("外汇-交叉汇率");  	break;
//			//case (FOREIGN_MARKET | WH_FUTURES_RATE):	strMarketName = _T("外汇-期汇");  		break;
//
//		case (HK_MARKET | HK_BOURSE):		strMarketName = _T("港股-主板市场");      	break;
//		case (HK_MARKET | GE_BOURSE):		strMarketName = _T("港股-创业板市场");   	break;
//		case (HK_MARKET | INDEX_BOURSE):		strMarketName = _T("港股-指数市场");	        break;
//
//		default:
//		{
//			strMarketName = _T("未知市场");
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
//			{// 版本号不匹配 清空文件
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
//				{// 存储每一个代码页的起始位置
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
//			m_nIndexEndOff = nOffer; // 记录末尾的偏移量
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
//		unsigned int nCopyLenth = 0;         // 实际拷贝长度
//		const char* pCopyBegin = NULL; // 起始位置
//		unsigned int nCopyLenthBackUp = 0;   // 已经写入的长度
//		unsigned int nPageFullCount = 0;     // 记录已经填充满的页数量
//		std::list<MMFCachePageInfo<CodeInfo>> listPageNoBackUpNotFull;// 已经写入数据并且没有写满的页号
//
//		unsigned int nOffset = 0;
//		unsigned int nCodeOffset = 0;
//		std::unordered_map<CodeInfo, int>::iterator it = m_mapCodeToIndex.find(codeInfo);
//		if (it != m_mapCodeToIndex.end())
//		{// 代码已经存在 
//			nOffset = it->second;
//			MMFCachePageInfo<CodeInfo> pageInfo;
//			for (unsigned int i = 0; i < m_indexHead.m_nIndexCapability; i++)
//			{
//				if (m_pMMFIndex->Read(nOffset + i * sizeof(MMFCachePageInfo<CodeInfo>), (char*)&pageInfo, sizeof(MMFCachePageInfo<CodeInfo>))
//					&& pageInfo.m_code.CompareCodeByMainMarket(&codeInfo)
//					)
//				{
//					nCopyLenthBackUp += (pageInfo.m_nCount * m_nOneStructSize);// 累积已经写入的长度
//					if (!IsPageFull(pageInfo))
//					{// 记录未写满的页面编号
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
//			{// 本地已经写满了 无法写入
//				return bRet;
//			}
//		}
//		else
//		{// 新增加代码
//
//		 // 偏移到最后
//			nOffset = m_nIndexEndOff + sizeof(CodeInfo);
//			m_nIndexEndOff += GetIndexSize();
//			// 加入到缓存
//			m_mapCodeToIndex.insert(std::make_pair(codeInfo, nOffset));
//		}
//		nCodeOffset = nOffset - sizeof(CodeInfo);
//
//		nCopyLenth = min(nBufferLenth, GetOneCodeInfoMaxSize() - nCopyLenthBackUp);
//		pCopyBegin = pBuffer + (nBufferLenth - nCopyLenth);
//
//		// 根据页号开始写文件 从内容文件开始写 万一在写的时候程序崩溃了 这样不会引起根据索引读取到错误的内容
//		while (nCopyLenth != 0)
//		{
//			if (!listPageNoBackUpNotFull.empty())
//			{// 先从未写满的页 继续写
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
//				m_pMMFContent->Write(nPageOffset, (char*)&pageInfo, sizeof(MMFCachePageInfo<CodeInfo>));   // 写页面信息
//
//				m_pMMFContent->Write(pageInfoBackUp.m_nOffSet, pCopyBegin, nOnePageLenth);       // 写数据
//				pCopyBegin += nOnePageLenth;
//
//				m_pMMFIndex->Write(nOffset + nPageFullCount * sizeof(MMFCachePageInfo<CodeInfo>), (char*)&pageInfo, sizeof(MMFCachePageInfo<CodeInfo>));  // 写索引文件
//
//				nCopyLenth = nCopyLenth < nOnePageLenth ? 0 : nCopyLenth - nOnePageLenth;
//				nPageFullCount++; // 填充完之后 数量加一
//			}
//			else
//			{// 新申请页 
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
//				m_pMMFContent->Write(nPageOffset, (char*)&pageInfo, sizeof(MMFCachePageInfo<CodeInfo>));           // 写页面信息
//				m_pMMFContent->Write(nPageOffset + sizeof(MMFCachePageInfo<CodeInfo>), pCopyBegin, nOnePageLenth); // 写数据
//				pCopyBegin += nOnePageLenth;
//
//				m_pMMFIndex->Write(nOffset + nPageFullCount * sizeof(MMFCachePageInfo<CodeInfo>), (char*)&pageInfo, sizeof(MMFCachePageInfo<CodeInfo>));  // 写索引文件		
//
//				nCopyLenth = nCopyLenth < nOnePageLenth ? 0 : nCopyLenth - nOnePageLenth;
//				nPageFullCount++; // 填充完之后 数量加一
//			}
//		}
//
//		m_pMMFIndex->Write(nCodeOffset, (char*)&codeInfo, sizeof(CodeInfo));          // 写索引文件代码信息
//		m_pMMFIndex->Write(0, (char*)&m_indexHead, sizeof(MMFCacheIndexFileHead));    // 写索引文件头部信息
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
//		// 实际拷贝长度 和 起始位置
//		unsigned int nCopyLenth = min(GetOneCodeInfoMaxSize(), nBufferLenth);
//		const char* pCopyBegin = pBuffer + (nBufferLenth - nCopyLenth);
//		// 计算需要的页数
//		unsigned int nPageInfoCount = (nCopyLenth + GetOnePageMaxSize() - 1) / GetOnePageMaxSize();
//
//		std::list<unsigned int> listPageNo;
//		unsigned int nOffset = 0;
//		unsigned int nCodeOffset = 0;
//		std::unordered_map<CodeInfo, int>::iterator it = m_mapCodeToIndex.find(codeInfo);
//		if (it != m_mapCodeToIndex.end())
//		{// 代码已经存在 
//			nOffset = it->second;
//			std::list<unsigned int> listPageNoBackUp;
//			MMFCachePageInfo<CodeInfo> pageInfo;
//			for (unsigned int i = 0; i < m_indexHead.m_nIndexCapability; i++)
//			{
//				if (m_pMMFIndex->Read(nOffset + i * sizeof(MMFCachePageInfo<CodeInfo>), (char*)&pageInfo, sizeof(MMFCachePageInfo<CodeInfo>))
//					&& pageInfo.m_code.CompareCodeByMainMarket(&codeInfo)
//					)
//				{
//					listPageNoBackUp.push_back(pageInfo.m_nPageNo); // 记录页面编号
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
//			{// 之前写过的页数量不够 需要申请新的页
//				m_indexHead.m_nPageNo++;
//				listPageNo.push_back(m_indexHead.m_nPageNo);
//			}
//		}
//		else
//		{// 新增加代码
//
//		 // 偏移到最后
//			nOffset = m_nIndexEndOff + sizeof(CodeInfo);
//			m_nIndexEndOff += GetIndexSize();
//			// 加入到缓存
//			m_mapCodeToIndex.insert(std::make_pair(codeInfo, nOffset));
//
//			// 开始生成当前数据所需要写入的页号
//			for (unsigned int i = 0; i < nPageInfoCount; i++)
//			{// 页号是当前页总数之后累加 全部采用新页
//				listPageNo.push_back(m_indexHead.m_nPageNo + i + 1);
//			}
//			m_indexHead.m_nPageNo += nPageInfoCount;
//		}
//		nCodeOffset = nOffset - sizeof(CodeInfo);
//
//		// 根据页号开始写文件 从内容文件开始写 万一在写的时候程序崩溃了 这样不会引起根据索引读取到错误的内容
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
//			m_pMMFContent->Write(nPageOffset, (char*)&pageInfo, sizeof(MMFCachePageInfo<CodeInfo>));           // 写页面信息
//			m_pMMFContent->Write(nPageOffset + sizeof(MMFCachePageInfo<CodeInfo>), pCopyBegin, nOnePageLenth); // 写数据
//			pCopyBegin += nOnePageLenth;
//
//			m_pMMFIndex->Write(nOffset, (char*)&pageInfo, sizeof(MMFCachePageInfo<CodeInfo>));  // 写索引文件页信息
//			nOffset += sizeof(MMFCachePageInfo<CodeInfo>);
//		}
//
//		m_pMMFIndex->Write(nCodeOffset, (char*)&codeInfo, sizeof(CodeInfo));          // 写索引文件代码信息
//		m_pMMFIndex->Write(0, (char*)&m_indexHead, sizeof(MMFCacheIndexFileHead));    // 写索引文件头部信息
//
//		return bRet;
//	};
//private:
//	MMFCacheIndexFileHead  m_indexHead; // 索引头部信息
//	unsigned int      m_nOneStructSize;       // 存储的单个结构体大小
//
//	CMMF*       m_pMMFIndex;           // 索引文件
//												// 索引文件缓存
//	std::unordered_map<CodeInfo, int> m_mapCodeToIndex;
//	unsigned int      m_nIndexEndOff;         // 索引文件末尾偏移量
//
//	CMMF*       m_pMMFContent;          // 内容文件
//
//};



