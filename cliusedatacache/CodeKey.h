#pragma once
#include<string>

#define STOCK_MARKET			 0X1000   // 股票
#	define SH_BOURSE			 0x0100   // 上海
#	define SZ_BOURSE			 0x0200   // 深圳

#ifndef MFCPRO
// 针对RT_TECHDATA_EX请求返回
struct StockCompDayDataEx
{
	unsigned long	m_lDate;		// 日期
	long	m_lOpenPrice;	// 开
	long	m_lMaxPrice;	// 高
	long	m_lMinPrice;	// 低
	long	m_lClosePrice;	// 收
	long	m_lMoney;		// 成交金额(在期货市场下，该字段存放的是持仓量)
	unsigned long	m_lTotal;	  // 成交量
	long	m_lNationalDebtRatio; // 国债利率(单位为0.1分),基金净值(单位为0.1分), 无意义时，须将其设为0 2004年2月26日加入
								  // 期货市场下 表示是结算价
	void To(char cIntelToComputer)
	{
	}
};
#endif

#define IsSH(x) (((x) & 0xFF00))==(SH_BOURSE|STOCK_MARKET)
#define IsSZ(x) (((x) & 0xFF00))==(SZ_BOURSE|STOCK_MARKET)


#define	MakeMarket(x) \
	(((x) & 0x0F00))


class CodeKey
{
public:
	/*CodeKey();
	virtual ~CodeKey();
	*/
	char code[10];
	int type;
	int time;
	int GetMarket() const
	{
		int market_no = 0;
		if(IsSH(type))
			market_no = 1;
		else if(IsSZ(type))
			market_no = 2;
		
		return market_no;
	}
    
};
extern bool operator==(const CodeKey& lci, const CodeKey& otherci);

namespace std {

	//template<>
	//struct hash<CodeInfo>
	//	: public _Bitwise_hash<CodeInfo>
	//{
	//	typedef size_t result_type;
	//	typedef CodeInfo argument_type;
	//	size_t operator()(const CodeInfo& ci) const;
	//};

	//size_t hash<CodeInfo>::operator()(const CodeInfo& ci) const
	//{
	//	//Cstring must change to string
	//	return hash<string>()(ci.GetCode().GetBuffer(0)) ^ hash<int>()(ci.m_cCodeType);
	//}

	template<>
	struct hash<CodeKey>
		: public _Bitwise_hash<CodeKey>
	{
		typedef size_t result_type;
		typedef CodeKey argument_type;
		size_t operator()(const CodeKey& ck) const;
	};
}
