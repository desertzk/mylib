#pragma once
#pragma warning(disable : 4996)
#include<cstdio>
#include<string>
#include<windows.h>

/*
�г�����壺
��λ�����ʾ���£�
15		   12		8					0
|			|	  	  |					|
| ���ڷ���	|�г����� |	����Ʒ�ַ���	|
*/
typedef unsigned short HSMarketDataType;			  // �г�������������
													  /*���ڴ���*/
#define STOCK_MARKET			 0X1000   // ��Ʊ
#	define SH_BOURSE			 0x0100   // �Ϻ�
#	define SZ_BOURSE			 0x0200   // ����
#	define SYSBK_BOURSE			 0x0400   // ϵͳ���
#	define USERDEF_BOURSE		 0x0800   // �Զ��壨��ѡ�ɻ����Զ����飩

#	define B2H_BOURSE			 0x0A00	  // B2H ���⴦��ֻ��� KIND_STOCKB
#   define TRANSFER_BOURSE       0x0C00   // ��תϵͳ Ŀǰ֧��(KIND_THREEBOAD KIND_SMALLSTOCK KIND_PREFERRED SC_Others)

#			define KIND_INDEX		 0x0000   // ָ�� 
#			define KIND_STOCKA		 0x0001   // A�� 
#			define KIND_STOCKB		 0x0002   // B�� 
#			define KIND_BOND		 0x0003   // ծȯ
#			define KIND_FUND		 0x0004   // ����
#			define KIND_THREEBOAD	 0x0005   // ����
#			define KIND_SMALLSTOCK	 0x0006   // ��С�̹�
#			define KIND_PREFERRED    0x0007	  // ���ȹ�
#			define KIND_LOF			 0x0008	  // LOF
#			define KIND_ETF			 0x0009   // ETF
#			define KIND_QuanZhen	 0x000A   // Ȩ֤
#           define KIND_OEF          0x000B   // ����ʽ����
#			define KIND_STOCKGE		 0x000D	  // ��ҵ��(Growth Enterprise)

#			define KIND_OtherIndex	 0x000E   // ������������࣬��:����ָ��

#			define SC_Others		 0x000F   // ���� 0x09
#			define KIND_USERDEFINE	 0x0010   // �Զ���ָ��
#			define KIND_STOCKA_SELECTED	0x0011	//������鱨�۱���
#			define KIND_STOCKA_NOTSEL	0x0012	//������鱨���޳�


													  // �۹��г�
#define HK_MARKET				 0x2000 // �۹ɷ���
#	define HK_BOURSE			 0x0100 // �����г�
#           define KIND_HK_BOND         0x0001  // ծȯ
#           define KIND_HK_BWARRANT     0x0002  // ��֤��B
#			define KIND_HK_STOCK		0x0003  // ��Ʊ
#           define KIND_HK_TRST         0x0004  // ����
#			define KIND_HK_WARRANT      0x0005  // ��֤��
#           define KIND_HK_OTHER        0x0000  // ����

#	define	GE_BOURSE			 0x0200 // ��ҵ���г�
#			define KIND_HKGE_STOCK        0x0000  // ��Ʊ

#	define	INDEX_BOURSE		 0x0300	// ָ���г�	
#           define KIND_HKINDEX_INDEX     0x0000  // ָ��

#   define  NTSD_BOURSE          0x0400 // Nasdaq AMX�г�(��ͨ��)
#           define KIND_HKNTSD_STOCK      0x0000  // NTSD

#   define  ETS_BOURSE           0x0500 // ���佻��֤ȯ
#           define KIND_HKETS_STOCK       0x0000  // ETS

#   define  HGT_BOURSE           0x0600 // ����ͨ(�ͻ�����Ҫ����)

													  /*�Ľ�������*/
#define CAE_MARKET                 0x3000 // �Ľ���
#       define AUCTION_AGGREGATE     0x0100 // ���Ͼ���
#       define AUCTION_DYNAMIC       0x0200 // ��̬����
#		        define KIND_GUQUAN       0x0001 // ��Ȩ
#               define KIND_WUQUAN       0x0002 // ��Ȩ
#               define KIND_YISHUPIN     0x0003 // ����Ʒ
#       define AUCTION_GENERAL       0x0300 // �����Ľ���
#               define KIND_CAEINDEX     0x0000 // �Ľ���ָ��

													  /*�ڻ�����*/
#define FUTURES_MARKET			 0x4000 // �ڻ�
#		define DALIAN_BOURSE		 0x0100	// ����
#				define KIND_BEAN		 0x0001	// ����
#				define KIND_YUMI		 0x0002	// ��������
#				define KIND_SHIT		 0x0003	// ����ʳ��
#				define KIND_DZGY		 0x0004	// ���ڹ�ҵ1
#				define KIND_DZGY2		 0x0005	// ���ڹ�ҵ2
#				define KIND_DOUYOU		 0x0006	// ������
#				define KIND_JYX			 0x0007	// ����ϩ
#				define KIND_ZTY			 0x0008	// �����

#		define SHANGHAI_BOURSE	  0x0200	// �Ϻ�
#				define KIND_METAL		 0x0001	// �Ϻ�����
#				define KIND_RUBBER		 0x0002	// �Ϻ���
#				define KIND_FUEL		 0x0003	// �Ϻ�ȼ��
													  //#				define KIND_GUZHI		 0x0004	// ��ָ�ڻ�
#				define KIND_QHGOLD		 0x0005	// �Ϻ��ƽ�

#		define ZHENGZHOU_BOURSE	  0x0300	// ֣��
#				define KIND_XIAOM		 0x0001	// ֣��С��
#				define KIND_MIANH		 0x0002	// ֣���޻�
#				define KIND_BAITANG		 0x0003	// ֣�ݰ���
#				define KIND_PTA			 0x0004	// ֣��PTA
#				define KIND_CZY			 0x0005	// ������

#		define HUANGJIN_BOURSE	  0x0400	// �ƽ�����
#				define KIND_GOLD		 0x0001	// �Ϻ��ƽ�

#		define GUZHI_BOURSE		  0x0500	// ��ָ�ڻ�
#				define KIND_GUZHI		 0x0001	// ��ָ�ڻ�

													  /*���̴���*/
#define WP_MARKET				 ((HSMarketDataType)0x5000) // ����
#		define WP_INDEX				0x0100	// ����ָ�� // ������
#		define WP_LME				0x0200	// LME		// ������
#			define WP_LME_CLT			0x0210 //"����ͭ";
#			define WP_LME_CLL			0x0220 //"������";
#			define WP_LME_CLM			0x0230 //"������";
#			define WP_LME_CLQ			0x0240 //"����Ǧ";
#			define WP_LME_CLX			0x0250 //"����п";
#			define WP_LME_CWT			0x0260 //"������";
#			define WP_LME_CW			0x0270 //"����";
#			define WP_LME_SUB			0x0000

#			define WP_CBOT				0x0300	// CBOT			
#			define WP_NYMEX	 			0x0400	// NYMEX	 	
#			define WP_NYMEX_YY			0x0000	//"ԭ��";
#			define WP_NYMEX_RY			0x0001	//"ȼ��";
#			define WP_NYMEX_QY			0x0002	//"����";

#			define WP_COMEX	 			0x0500	// COMEX	 	
#			define WP_TOCOM	 			0x0600	// TOCOM	 	
#			define WP_IPE				0x0700	// IPE			
#			define WP_NYBOT				0x0800	// NYBOT		
#			define WP_NOBLE_METAL		0x0900	// �����	
#				define WP_NOBLE_METAL_XH	0x0000  //"�ֻ�";
#				define WP_NOBLE_METAL_HJ	0x0001  //"�ƽ�";
#				define WP_NOBLE_METAL_BY	0x0002  //"����";

#			define WP_FUTURES_INDEX		0x0a00	// ��ָ
#			define WP_SICOM				0x0b00	// SICOM		
#			define WP_LIBOR				0x0c00	// LIBOR		
#			define WP_NYSE				0x0d00	// NYSE
#			define WP_CEC				0x0e00	// CEC

#			define WP_INDEX_AZ	 		0x0110 //"����";
#			define WP_INDEX_OZ	 		0x0120 //"ŷ��";
#			define WP_INDEX_MZ	 		0x0130 //"����";
#			define WP_INDEX_TG	 		0x0140 //"̩��";
#			define WP_INDEX_YL	 		0x0150 //"ӡ��";
#			define WP_INDEX_RH	 		0x0160 //"�պ�";
#			define WP_INDEX_XHP 		0x0170 //"�¼���";
#			define WP_INDEX_FLB 		0x0180 //"���ɱ�";
#			define WP_INDEX_CCN 		0x0190 //"�й���½";
#			define WP_INDEX_TW  		0x01a0 //"�й�̨��";
#			define WP_INDEX_MLX 		0x01b0 //"��������";
#			define WP_INDEX_SUB 		0x0000 

#			define WP_FRGNFUTURES_CME			0x0310			// CMEz
#			define WP_FRGNFUTURES_ICE			0x0320			// ICE
#			define WP_FRGNFUTURES_IDEM			0x0330			// IDEM
#			define WP_FRGNFUTURES_LIFFE			0x0340			// Liffe
#			define WP_FRGNFUTURES_LME			0x0350			// LME
#			define WP_FRGNFUTURES_MEFF			0x0360			// Meff
#			define WP_FRGNFUTURES_MONTREAL		0x0370			// Montreal
#			define WP_FRGNFUTURES_NYBOT			0x0380			// NYBOT
#			define WP_FRGNFUTURES_OSE			0x0390			// OSE
#			define WP_FRGNFUTURES_SFE			0x03a0			// SFE
#			define WP_FRGNFUTURES_SGX			0x03b0			// SGX
#			define WP_FRGNFUTURES_CME_E$		0x03c0			// CME_E$
#			define WP_FRGNFUTURES_TIFFE			0x03d0			// Tiffe
#			define WP_FRGNFUTURES_TOCOM			0x03e0			// TOCOM
#			define WP_FRGNFUTURES_TSE			0x03f0			// TSE
#			define WP_FRGNFUTURES_CURRENEX		0x0400			// Currenex
#			define WP_FRGNFUTURES_DGCX			0x0410			// DGCX
#			define WP_FRGNFUTURES_DME			0x0420			// DME
#			define WP_FRGNFUTURES_ECBOT			0x0430			// eCBOT
#			define WP_FRGNFUTURES_ENEXTVF		0x0440			// ENextVF
#			define WP_FRGNFUTURES_EUREX			0x0450			// Eurex
#			define WP_FRGNFUTURES_GAIN_FX		0x0460			// GAIN FX

#define COMMODITIES_MARKET		((HSMarketDataType)0x6000)		///��Ʒ
#	define SGE_BOURSE			0x0100		///�ƽ����
#   define SP_CG_BOURSE			0x0700			///��Ʒ����
#		define	SP_CG_KIND_HX						0x0001  /// ������Ʒ���� 
#   define SP_GT_BOURSE			0x0800		///��Ʒ����
#       define  SP_GT_KIND_HX						0x0001  /// ������Ʒ����
#   define BARGAIN_BOURSE       0x0900      ///Э�����
#		define	BAGRAIN_KIND_CARBON					0x0001  /// �人������Э����� 
#   define PRICE_BOURSE         0x0A00      ///���۽���
#       define  PRICE_KIND_CARBON                   0x0001  /// �人���������۽���

#define OPTION_MARKET           ((HSMarketDataType)0x7000)      ///��Ȩ
#   define OPTION_SH            0x0100      ///�Ϻ���Ȩ
#		define OPTION_STOCK                         0x0001      // ��Ʊ��Ȩ
#       define OPTION_ETF                           0x0002      // ETF��Ȩ
#       define OPTION_OTHER                         0x000F      // ������Ȩ
#   define OPTION_SZ            0x0200      ///������Ȩ
#   define OPTION_FUTURES_GUZHI 0x0300      ///�����ڻ���Ȩ
#       define OPTION_GUZHI_INDEX                   0x0001      // ��ָ�ڻ�
#       define OPTION_GUZHI_OTHER                   0x000F      // �н���Ȩ����
#   define OPTION_FUTURES_SH    0x0400      ///�Ϻ��ڻ���Ȩ
#   define OPTION_FUTURES_DL    0x0500      ///�����ڻ���Ȩ
#   define OPTION_FUTURES_ZZ    0x0600      ///֣���ڻ���Ȩ

													  /*������*/
#define FOREIGN_MARKET			 ((HSMarketDataType)0x8000) // ���
#	define WH_BASE_RATE			0x0100	// ��������
#	define WH_ACROSS_RATE		0x0200	// �������
#		define FX_TYPE_AU 			0x0000 // AU	��Ԫ
#		define FX_TYPE_CA 			0x0001 // CA	��Ԫ
#		define FX_TYPE_CN 			0x0002 // CN	�����
#		define FX_TYPE_DM 			0x0003 // DM	���
#		define FX_TYPE_ER 			0x0004 // ER	ŷԪ	 
#		define FX_TYPE_HK 			0x0005 // HK	�۱�
#		define FX_TYPE_SF 			0x0006 // SF	��ʿ 
#		define FX_TYPE_UK 			0x0007 // UK	Ӣ��
#		define FX_TYPE_YN 			0x0008 // YN	��Ԫ

#	define WH_FUTURES_RATE			0x0300  // �ڻ�

													  /*��չָ��ҵ��*/
#define EXTEND_MARKET            0xA000 // 
#	define ZX_INDEX					0x0500  // ����ָ��
#		define BLOCK_REGION				0x0001 // ������
#		define BLOCK_CONCEPT            0x0002 // ������
#		define BLOCK_CSRC               0x0003 // ֤�����ҵ���
#       define BLOCK_INDUSTRY           0x0004 // ��ҵ���
#		define BLOCK_INDEX              0x0005 // ָ�����


													  // �ڲ����࣬����Ʊ��������
#define STOCK_WHILOM_NAME_MARKET ((HSMarketDataType)0xF000)


													  //#define	MakeMarket(x)			((HSMarketDataType)((x) & 0xF000))
													  //#define MakeMainMarket(x)		((HSMarketDataType)((x) & 0xFFF0))
													  //#define	MakeMidMarket(x)		((HSMarketDataType)((x) & 0x0F00)) // ����ڶ�λ

static int	MakeMarket(HSMarketDataType x)
{
	return ((HSMarketDataType)((x) & 0xF000));
}
static int  MakeMainMarket(HSMarketDataType x)
{
	return ((HSMarketDataType)((x) & 0xFFF0));
}
static int	MakeMidMarket(HSMarketDataType x)
{
	return ((HSMarketDataType)((x) & 0x0F00)); // ����ڶ�λ
}

static bool IsSameMarket(HSMarketDataType x, HSMarketDataType y)
{
	int a = MakeMarket(x);
	int b = MakeMarket(y);

	if (a && b && a != b)
		return false;

	a = MakeMidMarket(x);
	b = MakeMidMarket(y);

	if (a && b && a != b)
		return false;

	a = x & 0x00F0;
	b = y & 0x00F0;

	if (a && b && a != b)
		return false;

	a = x & 0x000F;
	b = y & 0x000F;

	if (!a || !b)
		return true;

	return a == b ? true : false;
}

//#define MakeSubMarket(x)		((HSMarketDataType)((x) & 0x000F))
static int MakeSubMarket(HSMarketDataType x)
{
	return ((HSMarketDataType)((x) & 0x000F));
}

//#define MakeHexSubMarket(x)		( (HSMarketDataType)((x) & 0x000F) )
//#define MakeSubMarketPos(x)		( ((MakeHexSubMarket(x) / 16) * 10) + (MakeHexSubMarket(x) % 16) )

static int MakeHexSubMarket(HSMarketDataType x)
{
	return ((HSMarketDataType)((x) & 0x000F));
}

static int MakeSubMarketPos(HSMarketDataType x)
{
	return (((MakeHexSubMarket(x) / 16) * 10) + (MakeHexSubMarket(x) % 16));
}

// �Ƿ�Ϊ���ڹ�Ʊָ��
//#define MakeIndexMarket(x)		( (MakeMarket(x) == STOCK_MARKET) && (MakeSubMarket(x) == KIND_INDEX))
static int MakeIndexMarket(HSMarketDataType x)
{
	return ((MakeMarket(x) == STOCK_MARKET) &&
		(MakeMidMarket(x) != 0) &&
		((MakeSubMarket(x) == KIND_INDEX) ||
		(MakeSubMarket(x) == KIND_OtherIndex))
		// #ifdef SUPPORT_GG
		// 			 || (MakeMarket(x) == HK_MARKET && MakeMidMarket(x) == INDEX_BOURSE 
		// 			   && MakeSubMarket(x) == 0)
		// #endif
		);
}

// �Ƿ�Ϊ�Ľ���ָ��
static int MakeCAEIndexMarket(HSMarketDataType x)
{
	return ((MakeMarket(x) == CAE_MARKET) &&
		(MakeMidMarket(x) != 0) &&
		(MakeSubMarket(x) == KIND_CAEINDEX)
		);
}

static int MakeIndexSelf(HSMarketDataType x)
{
	return ((MakeMarket(x) == STOCK_MARKET) &&
		(MakeMidMarket(x) != 0) &&
		((MakeSubMarket(x) == KIND_OtherIndex)));
}

// �Ƿ�Ϊ����
static int MakeFundMarket(HSMarketDataType x)
{
	return ((MakeMarket(x) == STOCK_MARKET) &&
		(MakeMidMarket(x) != 0) &&
		(MakeSubMarket(x) == KIND_FUND));
}

// �Ƿ�Ϊ�۹�ָ��
//#define MakeHKIndex(x)          ( MakeMainMarket(x) == (HK_MARKET | INDEX_BOURSE) )
static int MakeHKIndex(HSMarketDataType x)
{
	return (MakeMainMarket(x) == (HK_MARKET | INDEX_BOURSE));
}

// �Ƿ�Ϊ��ָ�ڻ�
static int MakeGZIndex(HSMarketDataType x)
{
	return ((MakeMainMarket(x) == (FUTURES_MARKET | GUZHI_BOURSE)) &&
		(MakeSubMarket(x) == KIND_GUZHI));
}

// �Ƿ�Ϊ�ƽ��ڻ�
static int MakeGoldIndex(HSMarketDataType x)
{
	return ((MakeMainMarket(x) == (FUTURES_MARKET | HUANGJIN_BOURSE)) &&
		(MakeSubMarket(x) == KIND_GOLD));
}
//yangdl 2008.03.06 ���⴦��۸�
// �Ƿ�Ϊ��Ҫ���⴦��۸�ķ���
static int MakeNegativeIndex(HSMarketDataType x)
{
	return ((MakeMainMarket(x) == (FOREIGN_MARKET | WH_FUTURES_RATE)) &&
		((MakeSubMarket(x) == FX_TYPE_AU) || (MakeSubMarket(x) == FX_TYPE_YN)));
}

//#define MakeWPIndex(x)          ( (MakeMainMarket(x) >= (WP_MARKET | WP_INDEX_AZ)) && (MakeMainMarket(x) <= (WP_MARKET | WP_INDEX_MLX)) )
//#define MakeWP_LME(x)           ( (MakeMainMarket(x) >= (WP_MARKET | WP_LME_CLT))  && (MakeMainMarket(x) <= (WP_MARKET | WP_LME_CW)) )
static int MakeWPIndex(HSMarketDataType x)
{
	return ((MakeMainMarket(x) >= (WP_MARKET | WP_INDEX_AZ)) && (MakeMainMarket(x) <= (WP_MARKET | WP_INDEX_MLX)));
}

static int MakeWP_LME(HSMarketDataType x)
{
	return ((MakeMainMarket(x) >= (WP_MARKET | WP_LME_CLT)) && (MakeMainMarket(x) <= (WP_MARKET | WP_LME_CW)));
}

static int MakeBlockIndex(HSMarketDataType x)
{
	return (MakeMainMarket(x) == (EXTEND_MARKET | ZX_INDEX));
}

//#define	WhoMarket(x,y)			( MakeMarket(x) == MakeMarket(y) )
static int	WhoMarket(HSMarketDataType x, HSMarketDataType y)
{
	return (MakeMarket(x) == MakeMarket(y));
}

// �Ƿ�Ϊ���ڹ�ƱETF
//#define MakeETF(x)				( (MakeMarket(x) == STOCK_MARKET) && (MakeSubMarket(x) == KIND_ETF))
static int MakeETF(HSMarketDataType x)
{
	return ((MakeMarket(x) == STOCK_MARKET) && (MakeSubMarket(x) == KIND_ETF));
}

// �Ƿ�Ϊ��Ʊ��Ȩ
static int MakeStockOption(HSMarketDataType x)
{
	return ((MakeMainMarket(x) == (OPTION_MARKET | OPTION_SH))
		|| (MakeMainMarket(x) == (OPTION_MARKET | OPTION_SZ))
		);
}

// �Ƿ�Ϊ�ڻ���Ȩ
static int MakeFuturesOption(HSMarketDataType x)
{
	return ((MakeMainMarket(x) == (OPTION_MARKET | OPTION_FUTURES_SH))
		|| (MakeMainMarket(x) == (OPTION_MARKET | OPTION_FUTURES_DL))
		|| (MakeMainMarket(x) == (OPTION_MARKET | OPTION_FUTURES_ZZ))
		|| (MakeMainMarket(x) == (OPTION_MARKET | OPTION_FUTURES_GUZHI))
		);
}


#define IsFund(Type) (MakeMarket(Type) == STOCK_MARKET && (MakeSubMarket(Type) == KIND_FUND || MakeSubMarket(Type) == KIND_LOF))


#define SH_Bourse	((HSMarketDataType)(STOCK_MARKET|SH_BOURSE))
#define SZ_Bourse	((HSMarketDataType)(STOCK_MARKET|SZ_BOURSE))

#define QH_Bourse	FUTURES_MARKET
#define BK_Bourse	(STOCK_MARKET|SYSBK_BOURSE)
#define OT_Bourse	STOCK_WHILOM_NAME_MARKET // (�����г���Ŀǰ��Ҫ�����ڲ����࣬����Ʊ��������)

#define SC_Union			0x40 // ���

#define ToDataType(x) ((HSMarketDataType)(x))

#define NegativeHS(x,y)  ( y ? x&0x0FFFFFFF : x )
//#define Negative(x,y)   x


#define PYJC_MAX_LENGTH		16			// ƴ������
#define STOCK_NAME_SIZE		32			// ��Ʊ���Ƴ���
#define CODE_MAX_LENGTH     32          // ���볤��

extern UINT HashKey(LPCTSTR key, int nKeyCount, const int nHashTableSize);
// ��Ʊ����ṹ
struct CodeInfo
{
	HSMarketDataType	m_cCodeType;	// ֤ȯ����
	char				m_cCode[6];		// ֤ȯ����

	void To(char cIntelToComputer)
	{
	}

	CodeInfo()
	{
		SetEmpty();
	}

	void SetEmpty()
	{
		m_cCodeType = 0;
		memset(m_cCode, 0, 6);
	}

	CodeInfo(HSMarketDataType cCodeType, LPCTSTR lpszCode)
	{
		SetCode(cCodeType, lpszCode);
	}

	void SetCode(HSMarketDataType cCodeType, LPCTSTR lpszCode)
	{
		m_cCodeType = cCodeType;
		ZeroMemory(m_cCode, 6);
		if (MakeStockOption(m_cCodeType))
		{// ��Ʊ��Ȩ
			int nIncode = atoi(lpszCode);
			memcpy(m_cCode, &nIncode, sizeof(int));
		}
		else if (MakeFuturesOption(m_cCodeType))
		{// �ڻ���Ȩ
			int nLenth = strnlen(lpszCode, INT_MAX);
			int nIndex = 0;
			// ǰ׺
			for (int i = nIndex; i < nLenth; i++)
			{
				if (isdigit(lpszCode[i]))
				{// ����
					nIndex = i;
					break;
				}
				else if (i < 3)
				{
					m_cCode[i] = lpszCode[i];
				}
				else
				{
					return;
				}
			}

			// ����
			UINT nDate = 0;
			UINT nYear = 0, nMonth = 0;
			for (int i = nIndex; i < nLenth; i++)
			{
				if (!isdigit(lpszCode[i]))
				{// ��������
					nIndex = i;
					break;
				}
				else if (i - nIndex < 5)
				{
					nDate = nDate * 10 + (lpszCode[i] - '0');
				}
				else
				{
					return;
				}
			}
			nYear = nDate / 100;
			nMonth = nDate % 100;

			// ����
			UINT nType = 0;
			for (int i = nIndex; i < nLenth; i++)
			{
				if (lpszCode[i] == 'c' || lpszCode[i] == 'C')
				{
					nType = 0;
					nIndex = i;
					break;
				}
				else if (lpszCode[i] == 'p' || lpszCode[i] == 'P')
				{
					nType = 1;
					nIndex = i;
					break;
				}
				else if (isdigit(lpszCode[i]))
				{
					return;
				}
			}

			// ��Ȩ��
			UINT nExpPrice = 0;
			for (int i = nIndex; i < nLenth; i++)
			{
				if (isdigit(lpszCode[i]))
				{
					nExpPrice = nExpPrice * 10 + (lpszCode[i] - '0');
				}
			}

			UINT* pZip = (UINT*)(&m_cCode[2]);
			*pZip = (nYear << 25) | (nMonth << 21) | (nType << 20) | nExpPrice;
		}
		else
		{
			strncpy(m_cCode, lpszCode, min(sizeof(m_cCode), strnlen(lpszCode, INT_MAX)));
		}
	}

	// ������ϣ��, ���ع�ϣ����
	long GetLongKey(int nHashTableSize = 999999)
	{
		return HashKey(m_cCode, 6, nHashTableSize);
	}

	// �Ƚ�����	����TRUE or FALSE
	BOOL IsType(HSMarketDataType cType)
	{
		return (MakeSubMarket(m_cCodeType) == cType);
	}

	// ת��Ϊһ������
	INT64 ToInt64() const
	{
		INT64 nCode = 0;
		memcpy((char*)&nCode, &m_cCodeType, 2);
		memcpy((char*)&nCode + 2, m_cCode, 6);
		return nCode;
	}

	void FromInt64(INT64 nCode)
	{
		memcpy(this, ((char*)&nCode), sizeof(INT64));
	}

	// �γ�һ��Int64λ��ΨһKeyֵ
	INT64 MakeIntKey() const
	{
		INT64 nCode(0);
		HSMarketDataType nMainMarket = (HSMarketDataType)MakeMainMarket(m_cCodeType);
		memcpy((char*)&nCode, &nMainMarket, 2);
		memcpy((char*)&nCode + 2, m_cCode, 6);
		return nCode;
	}

	// ������ ��������
	void operator=(const CodeInfo* pInfo)
	{
		if (pInfo != NULL)
		{
			memcpy(this, pInfo, sizeof(CodeInfo));
		}
	}
	// ������ ��������
	void operator=(const CodeInfo& pInfo)
	{
		memcpy(this, &pInfo, sizeof(CodeInfo));
	}

	// ���ش���
	std::string GetCode() const
	{
		if (MakeStockOption(m_cCodeType))
		{// ������Ȩ���� ��Ҫ���� ��ŵ���int����ֵ ת��Ϊ8���ַ�
			int nDecode = *((int*)m_cCode);
			char szDecode[9] = { 0 };
			_itoa(nDecode, szDecode, 10);
			return szDecode;
		}
		else if (MakeFuturesOption(m_cCodeType))
		{// �ڻ���Ȩ ���� ��Ϊ������ѹ�� ��ѹ�����Ĵ��벻��ԭ���� ���ǿ�����Ϊһ��Ψһֵ���ñ�ʶ
			char strCode[9] = {0};
			UINT* pZip = (UINT*)(&m_cCode[2]);
			if (m_cCode[1] != 0)
			{
				sprintf(strCode,"%c%c%02d%02d%c%d",
					m_cCode[0],
					m_cCode[1],
					*pZip >> 25,
					(*pZip & 0x01E00000) >> 21,
					((*pZip & 0x00100000) >> 20) == 0 ? 'C' : 'P',
					*pZip & 0x000FFFFF
				);
			}
			else
			{
				sprintf(strCode,"%c%02d%02d%c%d",
					m_cCode[0],
					*pZip >> 25,
					(*pZip & 0x01E00000) >> 21,
					((*pZip & 0x00100000) >> 20) == 0 ? 'C' : 'P',
					*pZip & 0x000FFFFF
				);
			}

			return strCode;
		}
		else
		{
			char szKey[7] = { 0 };
			strncpy_s(szKey, m_cCode, 6);
			return szKey;
		}
	}

	// �����г�
	std::string GetMarket() const
	{
		char strMarket[6];
		sprintf(strMarket ,"%d", m_cCodeType);
		return strMarket;
	}

	BOOL CompareCode(const CodeInfo* pDes) const
	{
		if (pDes == NULL)
			return FALSE;

		return (m_cCodeType == pDes->m_cCodeType && memcmp(m_cCode, pDes->m_cCode, 6) == 0);
	}

	BOOL CompareCodeByMainMarket(const CodeInfo* pDes) const
	{
		if (pDes == NULL)
			return FALSE;

		return (MakeMainMarket(m_cCodeType) == MakeMainMarket(pDes->m_cCodeType) && memcmp(m_cCode, pDes->m_cCode, 6) == 0);
	}
};
