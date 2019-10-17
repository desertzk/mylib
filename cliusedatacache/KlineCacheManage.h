#pragma once
//#include"stdafx.h"
#include<map>
#include<string>
#ifdef MFCPRO
#include"stdafx.h"
#include "hsds_comudata.h"
#endif
#include<forward_list>
#include"MMFCacheEx.hpp"

struct  StockInfo
{
	char code[10];
	int market;
	bool operator<(const StockInfo& osi) const
	{
		if (strcmp(code,osi.code)<0)
			return true;
		else if (strcmp(code, osi.code)== 0)//等于时比较证券市场
		{
			return market<osi.market;
		}
		else {
			return false;
		}

	}
};

class KlineCacheManage
{
public:
	KlineCacheManage();
	virtual ~KlineCacheManage();
	int SetMiniteKline(const CodeKey&, StockCompDayDataEx *stkkbegin, UINT bytelength, bool bAppend);
	int GetMiniteKLine(const CodeKey&, StockCompDayDataEx *stkkbegin);
	int GetMiniteKLine(const CodeKey& ck, std::forward_list<StockCompDayDataEx>& sl, unsigned long begindate, unsigned long enddate);
	int SetDayKLine(const CodeKey&, StockCompDayDataEx *stkkbegin, UINT length,bool bAppend);
	int GetDayKLine(const CodeKey&, StockCompDayDataEx *stkkbegin);
	int GetDayKLine(const CodeKey& ck, std::forward_list<StockCompDayDataEx>& sl, unsigned long begindate, unsigned long enddate);
	int AppendDayKLine(const CodeKey& ck, StockCompDayDataEx * insertbuff, UINT insertlength);
private:
	CMMFCacheEx<CodeKey, StockCompDayDataEx> *m_dayLineCache;
	std::map<StockInfo,CMMFCacheEx<CodeKey, StockCompDayDataEx> *> m_minLineCache;
};
