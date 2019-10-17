#include "KlineCacheManage.h"
#include<forward_list>
#include<memory>
using namespace std;

KlineCacheManage::KlineCacheManage()
{
	m_dayLineCache = new CMMFCacheEx<CodeKey, StockCompDayDataEx>("indexday.dat", "contentday.dat");
	//CMMFCacheEx<CodeKey, StockCompDayDataEx> *pmf = new CMMFCacheEx<CodeKey, StockCompDayDataEx>("indexday.dat", "contentday.dat");
}


KlineCacheManage::~KlineCacheManage()
{
	if (m_dayLineCache)
		delete m_dayLineCache;

	for (auto mmfcache : m_minLineCache)
	{
		if(mmfcache.second)
			delete mmfcache.second;
	}
		


}

int KlineCacheManage::SetMiniteKline(const CodeKey &ck, StockCompDayDataEx * stkkbegin, UINT bytelength, bool bAppend)
{
	int length = 0;
	StockInfo si = { 0 };
	strcpy(si.code, ck.code);
	si.market = ck.GetMarket();
	auto it = m_minLineCache.find(si);
	if (it != m_minLineCache.end()) {
		CMMFCacheEx<CodeKey, StockCompDayDataEx> *pmf = m_minLineCache[si];
		length = pmf->Write(ck, (char *)stkkbegin, bytelength, bAppend);
	}
	else {
		char fileindex[32] = { 0 };
		char filecontent[32] = { 0 };
		sprintf(fileindex, "%d%sindex.dat",si.market,si.code);
		sprintf(filecontent, "%d%scontent.dat", si.market, si.code);
		
		CMMFCacheEx<CodeKey, StockCompDayDataEx> *pmf = new CMMFCacheEx<CodeKey, StockCompDayDataEx>(fileindex, filecontent,1,250);
		length=pmf->Write(ck, (char *)stkkbegin, bytelength, bAppend);
		m_minLineCache.insert(make_pair(si, pmf));
	}

	
	return length;
}

int KlineCacheManage::GetMiniteKLine(const CodeKey &ck, StockCompDayDataEx * stkkbegin)
{
	int length = 0;
	StockInfo si = { 0 };
	strcpy(si.code, ck.code);
	si.market = ck.GetMarket();
	auto it = m_minLineCache.find(si);
	if (it != m_minLineCache.end()) {
		CMMFCacheEx<CodeKey, StockCompDayDataEx> *pmf = m_minLineCache[si];
		length = pmf->Read(ck, (char *)stkkbegin, 0);/**/
	}
	else {
		char fileindex[32] = { 0 };
		char filecontent[32] = { 0 };
		sprintf(fileindex, "%d%sindex.dat", si.market, si.code);
		sprintf(filecontent, "%d%scontent.dat", si.market, si.code);
		if (CMMFCacheEx<CodeKey, StockCompDayDataEx>::file_exists(fileindex) && CMMFCacheEx<CodeKey, StockCompDayDataEx>::file_exists(filecontent))
		{//file exist can read
			CMMFCacheEx<CodeKey, StockCompDayDataEx> *pmf = new CMMFCacheEx<CodeKey, StockCompDayDataEx>(fileindex, filecontent);
			
			length = pmf->Read(ck, (char *)stkkbegin, 0);/**/
			m_minLineCache.insert(make_pair(si, pmf));
		}

	}
	return length;
}

int KlineCacheManage::GetMiniteKLine(const CodeKey & ck, std::forward_list<StockCompDayDataEx>& sl, unsigned long begindate, unsigned long enddate)
{
	int length = 0;
	StockInfo si = { 0 };
	strcpy(si.code, ck.code);
	si.market = ck.GetMarket();
	CMMFCacheEx<CodeKey, StockCompDayDataEx> *pmf = nullptr;
	unordered_map<CodeKey, int> *pcodeindex = nullptr;
	auto it = m_minLineCache.find(si);
	if (it != m_minLineCache.end()) {
		pmf = m_minLineCache[si];
		pcodeindex = pmf->GetIndexMap();
	}
	else {
		char fileindex[32] = { 0 };
		char filecontent[32] = { 0 };
		sprintf(fileindex, "%d%sindex.dat", si.market, si.code);
		sprintf(filecontent, "%d%scontent.dat", si.market, si.code);
		if (CMMFCacheEx<CodeKey, StockCompDayDataEx>::file_exists(fileindex) && CMMFCacheEx<CodeKey, StockCompDayDataEx>::file_exists(filecontent))
		{//file exist can read
			pmf = new CMMFCacheEx<CodeKey, StockCompDayDataEx>(fileindex, filecontent);
			pcodeindex = pmf->GetIndexMap();
		}
	}
	
	if (pcodeindex == nullptr)
		return 0;
	//by time
	for (auto it = pcodeindex->begin(); it != pcodeindex->end(); ++it)
	{
		if (begindate<it->first.time && enddate>it->first.time)
		{
			int length = pmf->GetReadLenth(it->first);
			//unique_ptr<StockCompDayDataEx> scddex;
			int count = length / sizeof(StockCompDayDataEx);
			StockCompDayDataEx * stkkbegin = new StockCompDayDataEx[count];
			pmf->Read(it->first, (char *)stkkbegin, 0);
			for (int i = 0; i < count; ++i)
			{
				sl.push_front(stkkbegin[i]);
				
			}
			delete[] stkkbegin;
		}
	}

	return 0;
}

int KlineCacheManage::SetDayKLine(const CodeKey& ck, StockCompDayDataEx * stkkbegin, UINT length, bool bAppend)
{
	return m_dayLineCache->Write(ck, (char *)stkkbegin, length, bAppend);
}

int KlineCacheManage::AppendDayKLine(const CodeKey& ck, StockCompDayDataEx * insertbuff, UINT insertlength)
{
	int writelen = 0;
	int insertcount= insertlength/ sizeof(StockCompDayDataEx);


	int length = m_dayLineCache->GetReadLenth(ck);
	//unique_ptr<StockCompDayDataEx> scddex;
	int count = length / sizeof(StockCompDayDataEx);
	StockCompDayDataEx * stkkbegin = new StockCompDayDataEx[count];
	m_dayLineCache->Read(ck, (char *)stkkbegin, 0);/**/
	int bi = 0;
	int ii = 0;
	if (stkkbegin->m_lDate == 0|| insertbuff[ii].m_lDate <= stkkbegin[bi].m_lDate)
	{
		writelen =m_dayLineCache->Write(ck, (char *)insertbuff, insertlength, 0);
		delete[] stkkbegin;
		return writelen;
	}

	//add kline by append
	
	while (insertbuff[ii].m_lDate > stkkbegin[bi].m_lDate)
	{
		++bi;
	}
	while (insertbuff[ii].m_lDate == stkkbegin[bi].m_lDate)
	{
		++bi;
		++ii;
	}
	int addcount = insertcount - ii;
	if (addcount == 0)
	{
		delete[] stkkbegin;
		return writelen;
	}
		
	StockCompDayDataEx * addstkkbegin = new StockCompDayDataEx[addcount];
	memcpy(addstkkbegin, insertbuff + ii, addcount*sizeof(StockCompDayDataEx));

	
	writelen=m_dayLineCache->Write(ck, (char *)insertbuff, length, 1);
	delete[] stkkbegin;
	delete[] addstkkbegin;
	return writelen;
}

int KlineCacheManage::GetDayKLine(const CodeKey& ck, forward_list<StockCompDayDataEx>& sl, unsigned long begindate, unsigned long enddate)
{
	int length = m_dayLineCache->GetReadLenth(ck);
	//unique_ptr<StockCompDayDataEx> scddex;
	int count = length / sizeof(StockCompDayDataEx);
	StockCompDayDataEx * stkkbegin = new StockCompDayDataEx[count];
	m_dayLineCache->Read(ck, (char *)stkkbegin, 0);/**/
	
	for (int i = 0; i < count; ++i)
	{
		//(stkkbegin + i)->m_lDate
		if (begindate<stkkbegin[i].m_lDate&&enddate>stkkbegin[i].m_lDate)
		{
			sl.push_front(stkkbegin[i]);
		}
	}
	delete[] stkkbegin;
	return 0;
}

int KlineCacheManage::GetDayKLine(const CodeKey& ck, StockCompDayDataEx * stkkbegin)
{
	int length = m_dayLineCache->Read(ck, (char *)stkkbegin, 0);/**/
	return length;
}

