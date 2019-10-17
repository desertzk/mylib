#pragma once
#include<string>

#define STOCK_MARKET			 0X1000   // ��Ʊ
#	define SH_BOURSE			 0x0100   // �Ϻ�
#	define SZ_BOURSE			 0x0200   // ����

#ifndef MFCPRO
// ���RT_TECHDATA_EX���󷵻�
struct StockCompDayDataEx
{
	unsigned long	m_lDate;		// ����
	long	m_lOpenPrice;	// ��
	long	m_lMaxPrice;	// ��
	long	m_lMinPrice;	// ��
	long	m_lClosePrice;	// ��
	long	m_lMoney;		// �ɽ����(���ڻ��г��£����ֶδ�ŵ��ǳֲ���)
	unsigned long	m_lTotal;	  // �ɽ���
	long	m_lNationalDebtRatio; // ��ծ����(��λΪ0.1��),����ֵ(��λΪ0.1��), ������ʱ���뽫����Ϊ0 2004��2��26�ռ���
								  // �ڻ��г��� ��ʾ�ǽ����
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
