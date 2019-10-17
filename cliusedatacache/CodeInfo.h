#pragma once
#pragma warning(disable : 4996)
#include<cstdio>
#include<string>
#include<windows.h>

/*
市场类别定义：
各位含义表示如下：
15		   12		8					0
|			|	  	  |					|
| 金融分类	|市场分类 |	交易品种分类	|
*/
typedef unsigned short HSMarketDataType;			  // 市场分类数据类型
													  /*金融大类*/
#define STOCK_MARKET			 0X1000   // 股票
#	define SH_BOURSE			 0x0100   // 上海
#	define SZ_BOURSE			 0x0200   // 深圳
#	define SYSBK_BOURSE			 0x0400   // 系统板块
#	define USERDEF_BOURSE		 0x0800   // 自定义（自选股或者自定义板块）

#	define B2H_BOURSE			 0x0A00	  // B2H 特殊处理只针对 KIND_STOCKB
#   define TRANSFER_BOURSE       0x0C00   // 股转系统 目前支持(KIND_THREEBOAD KIND_SMALLSTOCK KIND_PREFERRED SC_Others)

#			define KIND_INDEX		 0x0000   // 指数 
#			define KIND_STOCKA		 0x0001   // A股 
#			define KIND_STOCKB		 0x0002   // B股 
#			define KIND_BOND		 0x0003   // 债券
#			define KIND_FUND		 0x0004   // 基金
#			define KIND_THREEBOAD	 0x0005   // 三板
#			define KIND_SMALLSTOCK	 0x0006   // 中小盘股
#			define KIND_PREFERRED    0x0007	  // 优先股
#			define KIND_LOF			 0x0008	  // LOF
#			define KIND_ETF			 0x0009   // ETF
#			define KIND_QuanZhen	 0x000A   // 权证
#           define KIND_OEF          0x000B   // 开放式基金
#			define KIND_STOCKGE		 0x000D	  // 创业板(Growth Enterprise)

#			define KIND_OtherIndex	 0x000E   // 第三方行情分类，如:中信指数

#			define SC_Others		 0x000F   // 其他 0x09
#			define KIND_USERDEFINE	 0x0010   // 自定义指数
#			define KIND_STOCKA_SELECTED	0x0011	//光大行情报价保留
#			define KIND_STOCKA_NOTSEL	0x0012	//光大行情报价剔除


													  // 港股市场
#define HK_MARKET				 0x2000 // 港股分类
#	define HK_BOURSE			 0x0100 // 主板市场
#           define KIND_HK_BOND         0x0001  // 债券
#           define KIND_HK_BWARRANT     0x0002  // 认证股B
#			define KIND_HK_STOCK		0x0003  // 股票
#           define KIND_HK_TRST         0x0004  // 信托
#			define KIND_HK_WARRANT      0x0005  // 认证股
#           define KIND_HK_OTHER        0x0000  // 其他

#	define	GE_BOURSE			 0x0200 // 创业板市场
#			define KIND_HKGE_STOCK        0x0000  // 股票

#	define	INDEX_BOURSE		 0x0300	// 指数市场	
#           define KIND_HKINDEX_INDEX     0x0000  // 指数

#   define  NTSD_BOURSE          0x0400 // Nasdaq AMX市场(纳通股)
#           define KIND_HKNTSD_STOCK      0x0000  // NTSD

#   define  ETS_BOURSE           0x0500 // 扩充交易证券
#           define KIND_HKETS_STOCK       0x0000  // ETS

#   define  HGT_BOURSE           0x0600 // 沪港通(客户端需要屏蔽)

													  /*文交所大类*/
#define CAE_MARKET                 0x3000 // 文交所
#       define AUCTION_AGGREGATE     0x0100 // 集合竞价
#       define AUCTION_DYNAMIC       0x0200 // 动态竞价
#		        define KIND_GUQUAN       0x0001 // 股权
#               define KIND_WUQUAN       0x0002 // 物权
#               define KIND_YISHUPIN     0x0003 // 艺术品
#       define AUCTION_GENERAL       0x0300 // 常规文交所
#               define KIND_CAEINDEX     0x0000 // 文交所指数

													  /*期货大类*/
#define FUTURES_MARKET			 0x4000 // 期货
#		define DALIAN_BOURSE		 0x0100	// 大连
#				define KIND_BEAN		 0x0001	// 连豆
#				define KIND_YUMI		 0x0002	// 大连玉米
#				define KIND_SHIT		 0x0003	// 大宗食糖
#				define KIND_DZGY		 0x0004	// 大宗工业1
#				define KIND_DZGY2		 0x0005	// 大宗工业2
#				define KIND_DOUYOU		 0x0006	// 连豆油
#				define KIND_JYX			 0x0007	// 聚乙烯
#				define KIND_ZTY			 0x0008	// 棕榈油

#		define SHANGHAI_BOURSE	  0x0200	// 上海
#				define KIND_METAL		 0x0001	// 上海金属
#				define KIND_RUBBER		 0x0002	// 上海橡胶
#				define KIND_FUEL		 0x0003	// 上海燃油
													  //#				define KIND_GUZHI		 0x0004	// 股指期货
#				define KIND_QHGOLD		 0x0005	// 上海黄金

#		define ZHENGZHOU_BOURSE	  0x0300	// 郑州
#				define KIND_XIAOM		 0x0001	// 郑州小麦
#				define KIND_MIANH		 0x0002	// 郑州棉花
#				define KIND_BAITANG		 0x0003	// 郑州白糖
#				define KIND_PTA			 0x0004	// 郑州PTA
#				define KIND_CZY			 0x0005	// 菜籽油

#		define HUANGJIN_BOURSE	  0x0400	// 黄金交易所
#				define KIND_GOLD		 0x0001	// 上海黄金

#		define GUZHI_BOURSE		  0x0500	// 股指期货
#				define KIND_GUZHI		 0x0001	// 股指期货

													  /*外盘大类*/
#define WP_MARKET				 ((HSMarketDataType)0x5000) // 外盘
#		define WP_INDEX				0x0100	// 国际指数 // 不用了
#		define WP_LME				0x0200	// LME		// 不用了
#			define WP_LME_CLT			0x0210 //"场内铜";
#			define WP_LME_CLL			0x0220 //"场内铝";
#			define WP_LME_CLM			0x0230 //"场内镍";
#			define WP_LME_CLQ			0x0240 //"场内铅";
#			define WP_LME_CLX			0x0250 //"场内锌";
#			define WP_LME_CWT			0x0260 //"场外铝";
#			define WP_LME_CW			0x0270 //"场外";
#			define WP_LME_SUB			0x0000

#			define WP_CBOT				0x0300	// CBOT			
#			define WP_NYMEX	 			0x0400	// NYMEX	 	
#			define WP_NYMEX_YY			0x0000	//"原油";
#			define WP_NYMEX_RY			0x0001	//"燃油";
#			define WP_NYMEX_QY			0x0002	//"汽油";

#			define WP_COMEX	 			0x0500	// COMEX	 	
#			define WP_TOCOM	 			0x0600	// TOCOM	 	
#			define WP_IPE				0x0700	// IPE			
#			define WP_NYBOT				0x0800	// NYBOT		
#			define WP_NOBLE_METAL		0x0900	// 贵金属	
#				define WP_NOBLE_METAL_XH	0x0000  //"现货";
#				define WP_NOBLE_METAL_HJ	0x0001  //"黄金";
#				define WP_NOBLE_METAL_BY	0x0002  //"白银";

#			define WP_FUTURES_INDEX		0x0a00	// 期指
#			define WP_SICOM				0x0b00	// SICOM		
#			define WP_LIBOR				0x0c00	// LIBOR		
#			define WP_NYSE				0x0d00	// NYSE
#			define WP_CEC				0x0e00	// CEC

#			define WP_INDEX_AZ	 		0x0110 //"澳洲";
#			define WP_INDEX_OZ	 		0x0120 //"欧洲";
#			define WP_INDEX_MZ	 		0x0130 //"美洲";
#			define WP_INDEX_TG	 		0x0140 //"泰国";
#			define WP_INDEX_YL	 		0x0150 //"印尼";
#			define WP_INDEX_RH	 		0x0160 //"日韩";
#			define WP_INDEX_XHP 		0x0170 //"新加坡";
#			define WP_INDEX_FLB 		0x0180 //"菲律宾";
#			define WP_INDEX_CCN 		0x0190 //"中国大陆";
#			define WP_INDEX_TW  		0x01a0 //"中国台湾";
#			define WP_INDEX_MLX 		0x01b0 //"马来西亚";
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

#define COMMODITIES_MARKET		((HSMarketDataType)0x6000)		///商品
#	define SGE_BOURSE			0x0100		///黄金白银
#   define SP_CG_BOURSE			0x0700			///商品常规
#		define	SP_CG_KIND_HX						0x0001  /// 海西商品常规 
#   define SP_GT_BOURSE			0x0800		///商品跨天
#       define  SP_GT_KIND_HX						0x0001  /// 海西商品跨天
#   define BARGAIN_BOURSE       0x0900      ///协商议价
#		define	BAGRAIN_KIND_CARBON					0x0001  /// 武汉交易所协商议价 
#   define PRICE_BOURSE         0x0A00      ///定价交易
#       define  PRICE_KIND_CARBON                   0x0001  /// 武汉交易所定价交易

#define OPTION_MARKET           ((HSMarketDataType)0x7000)      ///期权
#   define OPTION_SH            0x0100      ///上海期权
#		define OPTION_STOCK                         0x0001      // 股票期权
#       define OPTION_ETF                           0x0002      // ETF期权
#       define OPTION_OTHER                         0x000F      // 其他期权
#   define OPTION_SZ            0x0200      ///深圳期权
#   define OPTION_FUTURES_GUZHI 0x0300      ///金融期货期权
#       define OPTION_GUZHI_INDEX                   0x0001      // 股指期货
#       define OPTION_GUZHI_OTHER                   0x000F      // 中金期权其他
#   define OPTION_FUTURES_SH    0x0400      ///上海期货期权
#   define OPTION_FUTURES_DL    0x0500      ///大连期货期权
#   define OPTION_FUTURES_ZZ    0x0600      ///郑州期货期权

													  /*外汇大类*/
#define FOREIGN_MARKET			 ((HSMarketDataType)0x8000) // 外汇
#	define WH_BASE_RATE			0x0100	// 基本汇率
#	define WH_ACROSS_RATE		0x0200	// 交叉汇率
#		define FX_TYPE_AU 			0x0000 // AU	澳元
#		define FX_TYPE_CA 			0x0001 // CA	加元
#		define FX_TYPE_CN 			0x0002 // CN	人民币
#		define FX_TYPE_DM 			0x0003 // DM	马克
#		define FX_TYPE_ER 			0x0004 // ER	欧元	 
#		define FX_TYPE_HK 			0x0005 // HK	港币
#		define FX_TYPE_SF 			0x0006 // SF	瑞士 
#		define FX_TYPE_UK 			0x0007 // UK	英镑
#		define FX_TYPE_YN 			0x0008 // YN	日元

#	define WH_FUTURES_RATE			0x0300  // 期汇

													  /*扩展指数业务*/
#define EXTEND_MARKET            0xA000 // 
#	define ZX_INDEX					0x0500  // 中信指数
#		define BLOCK_REGION				0x0001 // 地域板块
#		define BLOCK_CONCEPT            0x0002 // 概念板块
#		define BLOCK_CSRC               0x0003 // 证监会行业板块
#       define BLOCK_INDUSTRY           0x0004 // 行业板块
#		define BLOCK_INDEX              0x0005 // 指数板块


													  // 内部分类，给股票曾用名用
#define STOCK_WHILOM_NAME_MARKET ((HSMarketDataType)0xF000)


													  //#define	MakeMarket(x)			((HSMarketDataType)((x) & 0xF000))
													  //#define MakeMainMarket(x)		((HSMarketDataType)((x) & 0xFFF0))
													  //#define	MakeMidMarket(x)		((HSMarketDataType)((x) & 0x0F00)) // 分类第二位

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
	return ((HSMarketDataType)((x) & 0x0F00)); // 分类第二位
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

// 是否为国内股票指数
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

// 是否为文交所指数
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

// 是否为基金
static int MakeFundMarket(HSMarketDataType x)
{
	return ((MakeMarket(x) == STOCK_MARKET) &&
		(MakeMidMarket(x) != 0) &&
		(MakeSubMarket(x) == KIND_FUND));
}

// 是否为港股指数
//#define MakeHKIndex(x)          ( MakeMainMarket(x) == (HK_MARKET | INDEX_BOURSE) )
static int MakeHKIndex(HSMarketDataType x)
{
	return (MakeMainMarket(x) == (HK_MARKET | INDEX_BOURSE));
}

// 是否为股指期货
static int MakeGZIndex(HSMarketDataType x)
{
	return ((MakeMainMarket(x) == (FUTURES_MARKET | GUZHI_BOURSE)) &&
		(MakeSubMarket(x) == KIND_GUZHI));
}

// 是否为黄金期货
static int MakeGoldIndex(HSMarketDataType x)
{
	return ((MakeMainMarket(x) == (FUTURES_MARKET | HUANGJIN_BOURSE)) &&
		(MakeSubMarket(x) == KIND_GOLD));
}
//yangdl 2008.03.06 特殊处理价格
// 是否为需要特殊处理价格的分类
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

// 是否为国内股票ETF
//#define MakeETF(x)				( (MakeMarket(x) == STOCK_MARKET) && (MakeSubMarket(x) == KIND_ETF))
static int MakeETF(HSMarketDataType x)
{
	return ((MakeMarket(x) == STOCK_MARKET) && (MakeSubMarket(x) == KIND_ETF));
}

// 是否为股票期权
static int MakeStockOption(HSMarketDataType x)
{
	return ((MakeMainMarket(x) == (OPTION_MARKET | OPTION_SH))
		|| (MakeMainMarket(x) == (OPTION_MARKET | OPTION_SZ))
		);
}

// 是否为期货期权
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
#define OT_Bourse	STOCK_WHILOM_NAME_MARKET // (其它市场，目前主要用于内部分类，给股票曾用名用)

#define SC_Union			0x40 // 组合

#define ToDataType(x) ((HSMarketDataType)(x))

#define NegativeHS(x,y)  ( y ? x&0x0FFFFFFF : x )
//#define Negative(x,y)   x


#define PYJC_MAX_LENGTH		16			// 拼音长度
#define STOCK_NAME_SIZE		32			// 股票名称长度
#define CODE_MAX_LENGTH     32          // 代码长度

extern UINT HashKey(LPCTSTR key, int nKeyCount, const int nHashTableSize);
// 股票代码结构
struct CodeInfo
{
	HSMarketDataType	m_cCodeType;	// 证券类型
	char				m_cCode[6];		// 证券代码

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
		{// 股票期权
			int nIncode = atoi(lpszCode);
			memcpy(m_cCode, &nIncode, sizeof(int));
		}
		else if (MakeFuturesOption(m_cCodeType))
		{// 期货期权
			int nLenth = strnlen(lpszCode, INT_MAX);
			int nIndex = 0;
			// 前缀
			for (int i = nIndex; i < nLenth; i++)
			{
				if (isdigit(lpszCode[i]))
				{// 数字
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

			// 年月
			UINT nDate = 0;
			UINT nYear = 0, nMonth = 0;
			for (int i = nIndex; i < nLenth; i++)
			{
				if (!isdigit(lpszCode[i]))
				{// 不是数字
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

			// 类型
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

			// 行权价
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

	// 建立哈希表, 返回哈希长度
	long GetLongKey(int nHashTableSize = 999999)
	{
		return HashKey(m_cCode, 6, nHashTableSize);
	}

	// 比较类型	返回TRUE or FALSE
	BOOL IsType(HSMarketDataType cType)
	{
		return (MakeSubMarket(m_cCodeType) == cType);
	}

	// 转化为一个整型
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

	// 形成一个Int64位的唯一Key值
	INT64 MakeIntKey() const
	{
		INT64 nCode(0);
		HSMarketDataType nMainMarket = (HSMarketDataType)MakeMainMarket(m_cCodeType);
		memcpy((char*)&nCode, &nMainMarket, 2);
		memcpy((char*)&nCode + 2, m_cCode, 6);
		return nCode;
	}

	// 操作符 复制数据
	void operator=(const CodeInfo* pInfo)
	{
		if (pInfo != NULL)
		{
			memcpy(this, pInfo, sizeof(CodeInfo));
		}
	}
	// 操作符 复制数据
	void operator=(const CodeInfo& pInfo)
	{
		memcpy(this, &pInfo, sizeof(CodeInfo));
	}

	// 返回代码
	std::string GetCode() const
	{
		if (MakeStockOption(m_cCodeType))
		{// 个股期权代码 需要解码 存放的是int型数值 转化为8个字符
			int nDecode = *((int*)m_cCode);
			char szDecode[9] = { 0 };
			_itoa(nDecode, szDecode, 10);
			return szDecode;
		}
		else if (MakeFuturesOption(m_cCodeType))
		{// 期货期权 代码 因为是有损压缩 解压出来的代码不是原代码 但是可以作为一个唯一值有用标识
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

	// 返回市场
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
