
/*******************************************************************************
* Copyright (c)2010, 恒生信息技术有限公司
* All rights reserved.
*
* 文件名称：hsds_comudata.h
* 文件标识：新版数据通讯结构
* 摘    要：新版数据通讯结构
*
* 当前版本：投资赢家2.0
* 作    者：
* 完成日期：2010-09
*
* 备    注：
*
*
*******************************************************************************/

#pragma once

#include "hsstructnew.h"		
#include "NetEngineInterface.h"

#pragma	pack(1)

//////////////////////////////////////////////////////////////////////////
/* 请求/返回类型 DEFINE BEGIN*/

#define RT_BEGIN			    		0x0100
#define RT_END				    		0x8FFF

#define RT_COMPASKDATA					0x8FFE  /* 组合请求类型						*/
#define RT_ZIPDATA						0x8001  /* 压缩返回包类型					*/

#define RT_JAVA_MARK					0x0010	/* JAVA登录 | RT_LOGIN_*			*/
#define RT_WINCE_MARK					0x0020	/* WINCE登录 | RT_LOGIN_*			*/
#define RT_NOTZIP						0x0040	/* 不使用压缩数据传输				*/
#define RT_DEBUG						0x0080	/* 不使用压缩数据传输				*/

#define RT_INITIALINFO          		0x0101  /* 客户端数据所有初始化				*/
#define RT_LOGIN						0x0102  /* 客户端登录行情服务器				*/
#define RT_SERVERINFO					0x0103  /* 主站信息							*/
#define RT_BULLETIN						0x0104	/* 紧急公告(主推)					*/
#define RT_PARTINITIALINFO				0x0105	/* 客户端数据部分初始化				*/
#define RT_ETF_INIT		          		0x0106  /* 52只股票数据(ETF)				*/
#define RT_LOGIN_HK						0x0107	/* 客户端登录港股服务器				*/
#define RT_LOGIN_FUTURES				0x0108	/* 客户端登录期货服务器				*/
#define RT_LOGIN_FOREIGN				0x0109	/* 客户端登录外汇服务器				*/
#define RT_LOGIN_WP						0x010A	/* 客户端登录外盘服务器				*/
#define RT_LOGIN_INFO					0x010B	/* 客户端登录资讯服务器				*/
#define RT_CHANGE_PWD					0x010C	/* 修改密码							*/
// ghm add level2 登陆请求
#define RT_LOGIN_LEVEL					0x010D  /* level2登陆请求					*/
#define RT_SERVERINFO2					0x010E  /* 主站信息2						*/
#define RT_VERIFYINFO					0x010F  /* 用户认证信息返回					*/
//add by fangly
#define RT_LOGIN_CENTER				    0x0110  /* center登陆请求					*/
// add by lxqi 20081016
#define RT_LOGIN_FTP					0x0111  /* FTP登录返回请求					*/
#define RT_MODIFY_PWD                   0x0112  /*修改密码*/
#define RT_MODIFY_LV2PWD				0x0112  /* 修改Level2用户密码 */
#define RT_DISCONNLEVEL2				0x0113	/* level2断线 */
#define RT_STOCKINFOLIST				0x0114	/* 请求代码列表						*/

#define RT_LOGIN_COMMODITIES			0x0120	/* 商品现货 包含黄金*/
#define RT_LOGIN_CAE					0x0123	/* 文交所登录 */
#define RT_LOGIN_OPTION                 0x0125  /* 期权登录 */  
#define RT_INITIALINFO_VARCODE			0x0134	/* 变长代码的初始化信息 */

#define RT_REALTIME						0x0201  /* 行情报价表:1-6乾隆操作键			*/
#define RT_DYNREPORT					0x0202  /* 强弱分析;指标排序;热门板块分析;区间分析;跑马灯股票列表数据;预警	*/
#define RT_REPORTSORT					0x0203  /* 排名报价表:61-66、点击列排序		*/
#define RT_GENERALSORT					0x0204  /* 综合排名报表:81-86				*/
#define RT_GENERALSORT_EX				0x0205  /* 综合排名报表:81-86加入自定义分钟排名	*/
#define RT_SEVER_EMPTY					0x0206  /* 服务器无数据返回空包	*/
#define RT_SEVER_CALCULATE				0x0207  /* 服务器计算数据包,包括涨停、跌停	*/
#define RT_ANS_BYTYPE					0x0208  /* 根据类型返回数据包	*/
#define RT_QHMM_REALTIME				0x0209  /* 期货买卖盘	*/
#define RT_LEVEL_REALTIME				0x020A  /* level	*/
#define RT_CLASS_REALTIME				0x020B  /* 根据分类类别获取行情报价*/
// ghm add level2其他数据查询消息
#define RT_LEVEL_ORDERQUEUE				0x020C  /* level2买卖队列*/
#define RT_LEVEL_TRANSACTION			0x020D  /* LEVEL2逐笔成交*/
#define RT_QHARB_REALTIME				0x020E	/* 期货套利报价 maxy add */
#define RT_REPORTSORT_EXT				0x0212  /* 排名报价表扩展:61-66、点击列排序	*/

// 报价新排序功能（H5支持）
#define RT_HQCOL_VALUE		            0x0216	/* 按行情列ID查询行情字段值 */
#define RT_MARKETSORT		            0x0217	/* 按指定的行情列对市场排序 */

#define RT_ASSIST_QUERY                 0x0218  /* 退市整理代码表 */
#define RT_DYNAUCTION_REALTIME			0x0219	/* 文交所动态竞价实时数据*/
#define RT_DYNAUCTION_TICK				0x021A	/* 文交所动态竞价Tick数据*/
#define RT_FIXED_PRICE_REALTIME	        0x021C	/* 定价交易实时报价 */

#define RT_TREND						0x0301  /* 分时走势							*/
#define RT_ADDTREND						0x0302  /* 走势图叠加、多股同列				*/
#define RT_BUYSELLPOWER					0x0303  /* 买卖力道							*/
#define RT_HISTREND						0x0304  /* 历史回忆;多日分时;右小图下分时走势*/
#define RT_TICK							0x0305  /* TICK图							*/
#define RT_ETF_TREND					0x0306  /* ETF分时走势						*/
#define RT_ETF_NOWDATA					0x0307  /* ETF时时数据						*/
#define RT_ETF_TREND_TECH				0x0308  /* ETFtech分时走势						*/
#define RT_HISTREND_INDEX				0x0309  /* 对于大盘领先-历史回忆;多日分时;右小图下分时走势*/
#define RT_AUTOARBPUSH					0x030A	/* 期货套利报价 maxy add */
#define RT_HISTREND_EXT                 0x030C
#define RT_VIRTUAL_AUCTION				0x030E  /* 查询集合竞价数据 */


#define RT_TECHDATA						0x0400  /* 盘后分析							*/
#define RT_FILEDOWNLOAD					0x0401	/* 文件请求（盘后数据下载）			*/
#define RT_TECHDATA_EX					0x0402	/* 盘后分析扩展 -- 支持基金净值*/
#define RT_DATA_WEIHU					0x0403	/* 数据维护处理 */
#define RT_FILEDOWNLOAD2				0x0404	/* 下载服务器指定目录文件			*/
#define RT_FILED_CFG					0x0405	/* 配置文件升级/更新			    */
#define RT_FILL_DATA					0x0406	/* 补线处理 */
#define RT_TECHDATA_BYPERIOD			0x0407	/* 盘后分析扩展 -- 支持不同周期转换*/
#define RT_ONE_BLOCKDATA				0x0408	/* 一个板块数据请求 */
#define RT_TECHDATA_INCREMENT			0x0409	/* 盘后分析扩展 -- 增量数据请求    */
#define RT_TECHDATA_RANGE			    0x0410	/* 分段盘后分析*/
#define RT_TECHDATA_BIGINT              0x0411  /* 盘后分析大数据月线以及年线      */
#define RT_TECHDATA_RANGE_BIGINT		0x0412	/* 按时间区段请求K线 盘后分析大数据月线以及年线      */


#define RT_TEXTDATAWITHINDEX_PLUS		0x0501	/* 正序资讯索引数据					*/
#define RT_TEXTDATAWITHINDEX_NEGATIVE	0x0502	/* 倒序资讯索引数据					*/
#define RT_BYINDEXRETDATA				0x0503  /* 资讯内容数据						*/
#define RT_USERTEXTDATA		    		0x0504  /* 自定义资讯请求（如菜单等）		*/
#define RT_FILEREQUEST					0x0505  /* 配置文件文件						*/
#define RT_FILESimplify					0x0506  /* 精简文件请求						*/
#define RT_ATTATCHDATA					0x0507  /* 附件数据							*/
#define RT_PROMPT_INFO					0x0508	/* 服务器设置的提示信息				*/

#define RT_STOCKTICK					0x0601  /* 个股分笔、个股详细的分笔数据		*/
#define RT_BUYSELLORDER 				0x0602  /* 个股买卖盘						*/
#define RT_LIMITTICK            		0x0603  /* 指定长度的分笔请求				*/
#define RT_HISTORYTICK					0x0604  /* 历史的分笔请求					*/
#define RT_MAJORINDEXTICK				0x0605  /* 大盘明细							*/
#define RT_VALUE						0x0606	/* 右小图“值”						*/
#define RT_BUYSELLORDER_HK 				0x0607  /* 个股买卖盘(港股）				*/		
#define RT_BUYSELLORDER_FUTURES			0x0608  /* 个股买卖盘(期货）				*/		
#define RT_VALUE_HK						0x0609	/* 右小图“值”(港股),右小图也发此请求*/		
#define RT_VALUE_FUTURES				0x060A	/* 右小图“值”(期货),左下小图也发此请求*/		
#define RT_TOTAL						0x060B	/* 总持请求包 */


#define RT_LEAD							0x0702  /* 大盘领先指标						*/
#define RT_MAJORINDEXTREND				0x0703  /* 大盘走势							*/
#define RT_MAJORINDEXADL				0x0704  /* 大盘走势－ADL					*/
#define RT_MAJORINDEXDBBI	    		0x0705  /* 大盘走势－多空指标				*/
#define RT_MAJORINDEXBUYSELL    		0x0706  /* 大盘走势－买卖力道				*/
#define RT_SERVERFILEINFO    			0x0707  /* 服务器自动推送要更新的文件信息				*/
#define RT_DOWNSERVERFILEINFO    		0x0708  /* 下载-服务器自动推送要更新的文件信息				*/

#define RT_CURRENTFINANCEDATA			0x0801  /* 最新的财务数据					*/
#define RT_HISFINANCEDATA				0x0802  /* 历史财务数据						*/
#define RT_EXRIGHT_DATA					0x0803	/* 除权数据							*/
#define RT_HK_RECORDOPTION				0x0804	/* 港股期权							*/
#define RT_BROKER_HK					0x0805	/* 港股经纪席位下委托情况			*/				// 看我们的服务器是否生成此数据
#define RT_BLOCK_DATA					0x0806	/* 板块数据							*/
#define RT_STATIC_HK					0x0807	/* 港股静态数据						*/
#define RT_USER_BLOCK_DATA				0x0810	/* 后台自定义板块数据					*/		//add by lxqi 20090907

#define RT_MASSDATA             		0x0901  /* 大单								*/
#define RT_SERVERTIME					0x0902  /* 服务器当前时间					*/
#define RT_KEEPACTIVE					0x0903  /* 保活通信包						*/
#define RT_TEST							0x0904	/* 测试通信包						*/
#define RT_TESTSRV						0x0905	/* 测试客户端到服务器是否通畅		*/
#define RT_PUSHINFODATA					0x0906	/* 资讯实时主推						*/

/*短线精灵*/
#define RT_MARKET_MONITOR_SUPPORT_QUERY	0x0907		// 短线精灵订阅功能号
#define RT_MARKET_MONITOR_STOCK_QUERY	0x0908		// 短线精灵按股票查询
#define RT_MARKET_MONITOR_DATE_QUERY	0x0909		// 短线精灵按日期查询

#define RT_AUTOPUSH             		0x0A01	/* 常用主推							*/		// 改RealTimeData 为 CommRealTimeData
#define RT_AUTOPUSHSIMP         		0x0A02	/* 精简主推				*/					// 改为请求主推
#define RT_REQAUTOPUSH					0x0A03  /* 请求主推,应用于：预警、跑马灯	*/		// 改RealTimeData 为 CommRealTimeData
#define RT_ETF_AUTOPUSH					0x0A04  /* ETF主推	*/
#define RT_AUTOBROKER_HK				0x0A05	/* 经纪主推							*/
#define RT_AUTOTICK_HK					0x0A06	/* 港股分笔主推						*/
#define RT_AUTOPUSH_QH					0x0A07	/* 期货最小主推						*/
#define RT_PUSHREALTIMEINFO				0x0A08	/* 实时解盘主推						*/
#define RT_RAW_AUTOPUSH					0x0A09  /* 数据源原始数据主推	*/
#define RT_AUTOPUSH_RES					0x0A12 /* 预留的常用主推 maxy add */
#define RT_AUTOPUSH_LV2RES				0x0A13 /* 预留的level2主推 */
#define RT_QHMM_AUTOPUSH				0x0A0A  /* 期货买卖盘主推	*/
#define RT_LEVEL_AUTOPUSH				0x0A0B  /* level主推	*/
#define RT_MARKET_MONITOR_AUTOPUSH		0x0A17	// 短线精灵主推功能号
#define RT_DYNAUCTION_AUTOPUSH			0x0A18	/* 文交所动态竞价主推*/
#define RT_FIXPRICE_AUTOPUSH			0x0A1A  /*武汉光谷定价交易主推*/

#define RT_AUTO_TOTALMAX        0x0A10
#define RT_AUTO_SINGLEMAX       0x0A11
#define RT_LEVEL_TOTALMAX       0x2001
#define RT_LEVEL_SINGLEMAX      0x2002

#define RT_AUTOPUSH_EXT         0x0A0F
#define RT_TREND_EXT            0x030B
#define	RT_REALTIME_EXT         0x020F
// ghm add level2其他数据主推消息
#define RT_LEVEL_BORDERQUEUE_AUTOPUSH	0x0A0C  /* LEVEL2买卖队列买方向主推*/
#define RT_LEVEL_SORDERQUEUE_AUTOPUSH	0x0A0D  /* LEVEL2买卖队列卖方向主推*/
#define RT_LEVEL_TRANSACTION_AUTOPUSH	0x0A0E	/* LEVEL2逐笔成交主推*/


#define RT_UPDATEDFINANCIALDATA			0x0B01	/* 增量的财务报表数据 */
#define RT_SYNCHRONIZATIONDATA			0x0B02	/* 数据同步处理 */

#define RT_Level_OrderQueue				0x0B03	// 买卖队列 - level2 买卖队列数据
#define RT_Level_Cancellation			0x0B04	// 撤单 - 单笔委托数量最大的10笔买/卖撤单
#define RT_Level_Consolidated			0x0B05	// 累计 - 撤消买入/卖出委托累计数量最多的前10只股票
#define RT_Level_LargeTick				0x0B06	// 成交逐笔
#define RT_HISTORYTICKEx		        0x0B07	//历史分笔成交扩展请求

// 
#define RT_Send_Notice				    0x0C01 // 发表公告
#define RT_Send_ScrollText				0x0C02 // 发表滚动信息
#define RT_Change_program				0x0C03 // 更改服务器程序
#define RT_Send_File_Data				0x0C04 // 发送文件到服务器
#define RT_RequestDBF					0x0C05 // 请求DBF文件

#define RT_InfoSend						0x0C06  // 发布信息
#define RT_InfoUpdateIndex				0x0C07  // 更新信息索引
#define RT_InfoUpdateOneIndex			0x0C08  // 更新一条信息索引
#define RT_NoteMsgData					0x0C09	/* 定制短信数据传送 */
#define RT_InfoDataTransmit				0x0C0A  // 验证转发
#define RT_InfoCheckPurview				0x0C0B  // 返回注册详细分类信息
#define RT_InfoClickTime				0x0C0C  // 点击次数

#define RT_REPORTSORT_Simple			0x0D01  /* 排名报价表:61-66、点击列排序（精简）	*/
#define RT_PARTINITIALINFO_Simple		0x0D02  /* 代码返回	*/
#define RT_RETURN_EMPTY					0x0D03  /* 返回空的数据包	*/
#define RT_InfoDataRailing				0x0D04  // 请求栏目

#define RT_Srv_SrvStatus				0x0F01 // 后台程序运行状态
#define RT_SRV_SYNC                     0x0F02//客户端和服务器维护一个Session同步

// 公告信息配置
#define Notice_Option_WinCE				0x0001 // 公告信息只对WinCE用户//
#define Notice_Option_SaveSrv			0x0002 // 公告信息在服务器自动保存。
#define Login_Option_Password			0x0004 // 登陆时使用新的加密方式。
#define Login_Option_NotCheck			0x0008 // 不检测用户。

// AskData 中 m_nOption 指向的类型,为子类型
#define ByType_LevelStatic				0x1000  // 数据类型 LevelStatic  
#define ByType_LevelRealTime			0x2000  // 数据类型 LevelRealTime  

// 市场到掩码转换
#define Market_STOCK_MARKET				0x0001	 // 股票
#define	Market_HK_MARKET				0x0002   // 港股
#define Market_WP_MARKET				0x0004   // 外盘
#define Market_FUTURES_MARKET			0x0008   // 期货
#define Market_FOREIGN_MARKET			0x0010   // 外汇

#define Market_Address_Changed			0x0020   // 当前服务器需要地址切换
#define Market_Client_ForceUpdate		0x0040   // 当前客户端必须升级才能够使用
#define Market_DelayUser				0x0080   // 当前用户为延时用户，在港股连接时使用
#define Market_TestSrvData				0x0100   // 是否支持测试
#define Market_UserCheck				0x0200   // 返回数据中包含用户资讯权限信息
#define Market_LOGIN_INFO				0x0400   // 资讯

#define Market_STOCK_LEVEL				0x0800   // level2

// 服务器
//
#define RT_Srv_Sub_Restart		0x0001 // 重新启动程序
#define RT_Srv_Sub_Replace		0x0002 // 替换程序

#define RT_Srv_Sub_DownCFG		0x0003 // 下载配置文件
#define RT_Srv_Sub_UpCFG		0x0004 // 上传配置文件

#define RT_Srv_Sub_DownUserDB	0x0005 // 下载用户管理文件文件
#define RT_Srv_Sub_UpUserDB		0x0006 // 上传用户管理文件文件

#define RT_Srv_Sub_DownReport	0x0007 // 下载后台程序报告文件
#define RT_Srv_Sub_LimitPrompt	0x0008 // 权限错误提示

#define RT_Srv_Sub_Succ			0x1000 // 操作成功提示

/* 请求/返回 DEFINE END*/

/* 实时数据俺码　DEFINE BEGIN*/
#define MASK_REALTIME_DATA_OPEN					0X00000001      //今开盘
#define MASK_REALTIME_DATA_MAXPRICE				0X00000002      //最高价
#define MASK_REALTIME_DATA_MINPRICE				0X00000004      //最低价
#define MASK_REALTIME_DATA_NEWPRICE				0X00000008      //最新价

#define MASK_REALTIME_DATA_TOTAL				0X00000010      //成交量(单位:股)
#define MASK_REALTIME_DATA_MONEY				0X00000020	    //成交金额(单位:元)

#define MASK_REALTIME_DATA_BUYPRICE1			0x00000040	    // 买１价
#define MASK_REALTIME_DATA_BUYCOUNT1			0x00000080		// 买１量
#define MASK_REALTIME_DATA_BUYPRICE2			0x00000100	    // 买２价
#define MASK_REALTIME_DATA_BUYCOUNT2			0x00000200		// 买２量
#define	MASK_REALTIME_DATA_BUYPRICE3			0x00000400	    // 买３价
#define MASK_REALTIME_DATA_BUYCOUNT3			0x00000800		// 买３量
#define MASK_REALTIME_DATA_BUYPRICE4			0x00001000	    // 买４价
#define MASK_REALTIME_DATA_BUYCOUNT4			0x00002000		// 买４量
#define MASK_REALTIME_DATA_BUYPRICE5			0x00004000	    // 买５价
#define MASK_REALTIME_DATA_BUYCOUNT5			0x00008000		// 买５量

#define MASK_REALTIME_DATA_SELLPRICE1			0x00010000		// 卖１价
#define MASK_REALTIME_DATA_SELLCOUNT1			0x00020000		// 卖１量
#define MASK_REALTIME_DATA_SELLPRICE2			0x00040000		// 卖２价
#define MASK_REALTIME_DATA_SELLCOUNT2			0x00080000		// 卖２量
#define MASK_REALTIME_DATA_SELLPRICE3			0x00100000		// 卖３价
#define MASK_REALTIME_DATA_SELLCOUNT3			0x00200000		// 卖３量
#define MASK_REALTIME_DATA_SELLPRICE4			0x00400000		// 卖４价
#define MASK_REALTIME_DATA_SELLCOUNT4			0x00800000		// 卖４量
#define MASK_REALTIME_DATA_SELLPRICE5			0x01000000		// 卖５价
#define MASK_REALTIME_DATA_SELLCOUNT5			0x02000000		// 卖５量

#define MASK_REALTIME_DATA_PERHAND				0x04000000      //股/手 单位
#define MASK_REALTIME_DATA_NATIONAL_DEBT_RATIO  0x08000000      //国债利率
//以下为高32位  m_lReqMask1 对应StockOtherData结构
#define MASK_REALTIME_DATA_TIME					0x00000001      //距开盘分钟数
#define MASK_REALTIME_DATA_CURRENT				0x00000002	    //现手
#define MASK_REALTIME_DATA_OUTSIDE				0x00000004		//外盘
#define MASK_REALTIME_DATA_INSIDE				0x00000008		//内盘
#define MASK_REALTIME_DATA_OPEN_POSITION		0x00000010      //今开仓
#define MASK_REALTIME_DATA_CLEAR_POSITION		0x00000020      //今平仓
#define MASK_REALTIME_DATA_CODEINFO				0x10000000		//代码

// 增加列定义说明
#define MASK_REALTIME_DATA_BUYORDER1			0x00000080		// 买1盘数
#define MASK_REALTIME_DATA_BUYORDER2			0x00000100	    // 买2盘数
#define MASK_REALTIME_DATA_BUYORDER3			0x00000200		// 买3盘数
#define	MASK_REALTIME_DATA_BUYORDER4			0x00000400	    // 买4盘数
#define MASK_REALTIME_DATA_BUYORDER5			0x00000800		// 买5盘数

#define MASK_REALTIME_DATA_SELLORDER1			0x00001000	    // 卖1盘数
#define MASK_REALTIME_DATA_SELLORDER2			0x00002000		// 卖2盘数
#define MASK_REALTIME_DATA_SELLORDER3			0x00004000	    // 卖3盘数
#define MASK_REALTIME_DATA_SELLORDER4			0x00008000		// 卖4盘数
#define MASK_REALTIME_DATA_SELLORDER5			0x00010000		// 卖5盘数

#define MASK_REALTIME_DATA_SELLCOUNT1			0x00020000		// 卖１量
#define MASK_REALTIME_DATA_SELLPRICE2			0x00040000		// 卖２价
#define MASK_REALTIME_DATA_SELLCOUNT2			0x00080000		// 卖２量
#define MASK_REALTIME_DATA_SELLPRICE3			0x00100000		// 卖３价
#define MASK_REALTIME_DATA_SELLCOUNT3			0x00200000		// 卖３量
#define MASK_REALTIME_DATA_SELLPRICE4			0x00400000		// 卖４价
#define MASK_REALTIME_DATA_SELLCOUNT4			0x00800000		// 卖４量
#define MASK_REALTIME_DATA_SELLPRICE5			0x01000000		// 卖５价
#define MASK_REALTIME_DATA_SELLCOUNT5			0x02000000		// 卖５量

/* 实时数据俺码　DEFINE END*/

/* 综合排名排序类型掩码 DEFINE BEGIN*/
#define	RT_RISE					0x0001		//涨幅排名
#define	RT_FALL					0x0002		//跌幅排名
#define	RT_5_RISE				0x0004		//5分钟涨幅排名
#define	RT_5_FALL				0x0008		//5分钟跌幅排名
#define RT_AHEAD_COMM			0x0010		//买卖量差(委比)正序排名
#define RT_AFTER_COMM			0x0020		//买卖量差(委比)倒序排名
#define	RT_AHEAD_PRICE			0x0040		//成交价震幅正序排名
#define	RT_AHEAD_VOLBI			0x0080		//成交量变化(量比)正序排名
#define	RT_AHEAD_MONEY			0x0100		//资金流向正序排名
/* 综合排名排序类型掩码 DEFINE END*/

/* K线请求的周期类型 BEGIN*/
#define PERIOD_TYPE_DAY			0x0010		//分析周期：日
#define PERIOD_TYPE_HISDAY		0x0020		//分析周期：日
#define PERIOD_TYPE_MINUTE0		0x0000		//分笔成交
#define PERIOD_TYPE_MINUTE1		0x00C0		//分析周期：1分钟
#define PERIOD_TYPE_MINUTE5		0x0030		//分析周期：5分钟
#define PERIOD_TYPE_MINUTE15	0x0040		//分析周期：15分钟
#define PERIOD_TYPE_MINUTE30	0x0050		//分析周期：30分钟
#define PERIOD_TYPE_MINUTE60	0x0060		//分析周期：60分钟
#define PERIOD_TYPE_MINUTE120   0x00B0      //
#define PERIOD_TYPE_WEEK		0x0080		//分析周期：周
#define PERIOD_TYPE_MONTH		0x0090		//分析周期：月
#define PERIOD_TYPE_SEASON		0x00D0		//分析周期：季
#define PERIOD_TYPE_YEAR		0x00E0		//分析周期：年
/* K线请求的周期类型 END*/
//////////////////////////////////////////////////////////////////////////

#define AUTOPUSH_RES_TRADE_TYPE				0x0001		//交易持仓数据主推
#define AUTOPUSH_RES_STRATEGY_TYPE			0x0002		//策略交易监视数据主推
#define AUTOPUSH_RES_LV2EX_TYPE				0x0004      //交易Level2拓展主推,区分于AUTOPUSH_RES_TRADE_TYPE，以保证相同功能号不同通道的请求之间不互相干扰
#define AUTOPUSH_RES_FREQUENCYDATA_TYPE		0x0008		//订阅高频数据(客户未使用)
//////////////////////////////////////////////////////////////////////////

// level 2 源数据结构

// 逐笔成交数据
struct LevelTransaction
{
	//CodeInfo m_sCode;		//证券代码,由外部决定

	int		DataStatus;	   //
	int		TradeIndex;	   // 成交序号
	int		TradeChannel;  // 成交通道
	int		TradeRef;	   // 成交编号
	int		TradeTime;	   // 成交时间
	float	TradePrice;	   // 成交价格
	float	TradeQty;      // 成交数量
	float	TradeMoney;    // 成交金额
};

// 买卖队列
struct LevelOrderQueue_Item
{
	float Price;		 // 价格
	int	  NumOrders;	 // 委托笔数
	float OrderQty[1];   // 订单数量,max 50
};

struct LevelOrderQueue
{
	int		 DataTimeStamp;	// 163025 stands for 16:30:25.
	int		 DataStatus;
	int		 Side;			//买卖方向
	//CodeInfo m_sCode;		//证券代码,由外部决定

	int m_nSize;
	LevelOrderQueue_Item data[1];   // max 10
};


// 行业排名
struct LevelTotalValue
{
	int			Ranking;			// 排名序号
	CodeInfo	m_sCode;			// 证券代码
	float		TotalValueTraded;   // 成交金额
};

struct LevelByIndustry
{
	int   IndustryRanking;			// 排名序号
	char  IndustryCode[4];			// 行业代码
	float IndustryTotalValueTraded;	// 行业成交金额

	int   m_nSize;

	LevelTotalValue data[5];
};

struct LevelTransactionRankingByIndustry
{
	int		DataTimeStamp;			// 163025 stands for 16:30:25
	int		DataStatus;				//
	float   MarketTotalValueTraded; // 市场总成交金额

	char	CFICode[4];				// 证券类别
	char	SecuritySubType[4];		// 证券子类别

	int		m_nSize;

	LevelByIndustry data[1];
};

//
struct LevelWeiTuo
{
	int		DataTimeStamp;		// 163025 stands for 16:30:25
	int		DataStatus;			//
	int		Side;				// 买卖方向
	char	CFICode[4];			// 证券类别
	char	SecuritySubType[4];	// 证券子类别
};

// 委托排名－－委托买入数量最多的前十只证券
struct LevelOrderRanking_Item
{
	int		 Ranking;			// rank in list

	CodeInfo m_sCode;			// 证券代码

	float	 TotalOrderQty;		// 委托总量
	float	 TotalVolumeTraded; // 已成交总量
	float	 TotalValueTraded;	// 成交金额
};

struct LevelOrderRanking
{
	LevelWeiTuo m_sLevelWeiTuo;

	int		m_nSize;
	LevelOrderRanking_Item data[10];   // 前100名,现在是前10名
};

// 单笔委托数量最大的10笔买/卖撤单
struct LevelSingleOrderCancellationRanking_Item
{
	int		 Ranking;		// 排名序号
	CodeInfo m_sCode;		// 证券代码
	int		 OrderEntryTime;// 委托时间
	float	 Quantity;		// 委托数量
	float	 Price;			// 委托价格
};

struct LevelSingleOrderCancellationRanking
{
	LevelWeiTuo m_sLevelWeiTuo;

	int		m_nSize;
	LevelSingleOrderCancellationRanking_Item data[10];
};

// 撤消买入/卖出委托累计数量最多的前10只股票
struct LevelConsolidatedOrderCancellationRanking_Item
{
	int		 Ranking;				 // 排名序号
	CodeInfo m_sCode;				 // 证券代码
	float	 TotalWithdrawnQty;      // 撤消委托累计数量
};

struct LevelConsolidatedOrderCancellationRanking
{
	LevelWeiTuo m_sLevelWeiTuo;

	int		m_nSize;
	LevelConsolidatedOrderCancellationRanking_Item data[10];
};

//////////////////////////////////////////////////////////////////////////
//验证数据
struct HSPrivateKey
{
	CodeInfo m_pCode;	// 商品代码
	HSPrivateKey()
	{
		memset(this,0,sizeof(HSPrivateKey));
	}

	// 操作符 复制数据
	const HSPrivateKey& operator=(const HSPrivateKey& data)
	{
		memcpy(&m_pCode,&data.m_pCode,sizeof(m_pCode));
		return *this;
	}
	// 操作符 复制数据
	const HSPrivateKey& operator=(const StockUserInfo& pStockCode)
	{
		memcpy(&m_pCode,&pStockCode.m_ciStockCode,sizeof(m_pCode));
		return *this;
	}
	// 操作符 复制数据
	const HSPrivateKey& operator=(const CodeInfo& pCode)
	{
		memcpy(&m_pCode,&pCode,sizeof(m_pCode));
		return *this;
	}
	// 操作符 复制数据
	const HSPrivateKey& operator=(const long& pStockCode);
	// 复制数据
	void Copy(const HSPrivateKey& data)
	{
		memcpy(&m_pCode,&data.m_pCode,sizeof(m_pCode));
	}
	// 复制数据
	void Copy(const CodeInfo& pCode)
	{
		memcpy(&m_pCode,&pCode,sizeof(m_pCode));
	}
	// 比较代码 返回TRUE or FALSE
	BOOL Compare(const CodeInfo& pCode);
	BOOL Compare(const CodeInfo* pCode);
	// 比较代码 返回TRUE or FALSE
	BOOL Compare(const StockUserInfo& pCode);
	BOOL Compare(const StockUserInfo* pCode);
	// 返回对应的StockUserInfo结构地址
	const StockUserInfo* GetStock();
};

/*
通讯包格式说明:

单包请求包结构
说明：
1、	m_nIndex、m_cOperor、m_lKey、m_nPrivateKey为客户端专用的一些信息，
服务器端处理时直接拷贝返回,下同。
2、	宏定义：HS_SUPPORT_UNIX_ALIGN为使用于UNIX服务器4字节对齐使用，下同。
3、	所有请求都发送此包，根据m_nType类型具体情况来确定m_nSize和m_pCode[1]
内容来实现各种各样的请求。
4、	常用请求：指的是m_nSize取值为n个，m_pCode[1]内容只有n个CodeInfo，
即只请求n个股票数据，根据m_nType来识别请求类型。
*/
static char FormatSvrType(short nMarketType)
{
	char cType = CEV_Connect_ALL;
	switch (MakeMarket(nMarketType))
	{
	// 期货
	case FUTURES_MARKET:
		cType = CEV_Connect_FUTURES;
		break;
	// 港股
	case HK_MARKET:
		cType = CEV_Connect_HK;
		break;
	// 外盘
	case WP_MARKET:
		cType = CEV_Connect_WP;
		break;
	// 商品
	case COMMODITIES_MARKET:
		cType = CEV_Connect_COMMODITIES;
		break;
	// 文交所
	case CAE_MARKET:
		cType = CEV_Connect_CAE;
		break;
	// 期权
	case OPTION_MARKET:
		cType = CEV_Connect_OPTION;
		break;
	// 行情
	case STOCK_MARKET:
		cType = CEV_Connect_HQ;
		break;
	// 板块指数
	case EXTEND_MARKET: 
		cType = CEV_Connect_HQ;
		break;
	default:
		break;
	}
	return cType;
}

// 行情，板块指数不判断 主要用于数据引擎来判断是否发到level2服务器
static char FormatSvrTypeExceptionHQ(short nMarketType)
{
	char cType = CEV_Connect_ALL;
	switch (MakeMarket(nMarketType))
	{
		// 期货
	case FUTURES_MARKET:
		cType = CEV_Connect_FUTURES;
		break;
		// 港股
	case HK_MARKET:
		cType = CEV_Connect_HK;
		break;
		// 外盘
	case WP_MARKET:
		cType = CEV_Connect_WP;
		break;
		// 商品
	case COMMODITIES_MARKET:
		cType = CEV_Connect_COMMODITIES;
		break;
		// 文交所
	case CAE_MARKET:
		cType = CEV_Connect_CAE;
		break;
		// 期权
	case OPTION_MARKET:
		cType = CEV_Connect_OPTION;
		break;
		// 股票
	case STOCK_MARKET:
		{
			int nMidMarket = MakeMidMarket(nMarketType);
			if ( nMidMarket == TRANSFER_BOURSE )
			{// 新三板
				cType = CEV_Connect_HQ;
			}
		}
		break;
	default:
		break;
	}
	return cType;
}

static BOOL IsAutoPush(unsigned short nType)
{
	return ((nType & 0x0F00) == 0x0A00);
}

struct AskData
{
	unsigned short 		m_nType;	     // 请求类型
	char				m_nIndex;     	 // 请求索引，与请求数据包一致

	union
	{
		struct
		{
			char			m_cNotEmptyPacket:2;   // 客户端使用，服务器：=1时，当前请求包不能清，=0时，清除
			char			m_cOperator:6;	      // 客户端使用，当前所属的服务器类别，指向CEV_Connect_HQ_等的定义。
		};
		char			m_cSrv;				  // 服务器使用
	};

	long				m_lKey;		 	 // 一级标识，通常为窗口句柄
	HSPrivateKey	    m_nPrivateKey;	 // 二级标识

	short     			m_nSize;         // 请求证券总数，小于零时，
	// 其绝对值代表后面的字节数
	short 				m_nOption;       // 为了4字节对齐而添加的字段

	CodeInfo			m_pCode[1];      // 证券信息

	AskData()
	{
		Emtpy();
	}

	void Emtpy()
	{
		m_nType     = 0;
		m_cSrv      = 0;
		m_nSize     = 0;
		m_lKey      = 0;
		m_nOption   = 0;
	}
};

//组合包请求格式
struct CompAskData               
{
	unsigned short	m_nType;	      // 请求类型 = COMPASKDATA

	char			m_nIndex;		  // 请求索引，与请求数据包一致

	union
	{
		struct
		{
			char			m_cNotEmptyPacket:2;   // 客户端使用，服务器：=1时，当前请求包不能清，=0时，清除
			char			m_cOperator:6;   // 客户端使用，当前所属的服务器类别，指向CEV_Connect_HQ_等的定义。
		};
		char			m_cSrv;          // 服务器使用
	};

	long			m_lKey;			  // 一级标识，通常为窗口句柄
	HSPrivateKey	m_nPrivateKey;    // 二级标识

	short			m_nAsk;		      // 请求数据包的个数
	short			m_nLength[1];     // 每个请求数据包的长度，有 m_nAsk	个
};

//压缩返回包格式
struct TransZipData
{
	unsigned short	m_nType;		// 请求类型,恒为RT_ZIPDATA

	short 			m_nAlignment;	// 为了4字节对齐而添加的字段

	long			m_lZipLen;		// 压缩后的长度
	long			m_lOrigLen;		// 压缩前的长度
	char		    m_cData[1];		// 压缩后的数据
};

//返回包头结构
struct DataHead
{
	unsigned short		m_nType;         // 请求类型，与请求数据包一致
	char				m_nIndex;     	 // 请求索引，与请求数据包一致

	union
	{
		struct
		{
			char			m_cNotEmptyPacket:2;   // 客户端使用，服务器：=1时，当前请求包不能清，=0时，清除
			char			m_cOperator:6;   // 客户端使用，当前所属的服务器类别，指向CEV_Connect_HQ_等的定义。
		};
		char			m_cSrv;          // 服务器使用
	};

	long				m_lKey;		 	 // 一级标识，通常为窗口句柄
	HSPrivateKey		m_nPrivateKey;	 // 二级标识
};

//////////////////////////////////////////////////////////////////////////
//以下为请求应答包结构详细说明
// RT_NoteMsgData
// 请求
struct NoteMsgDataReq
{
	int  m_nType;		// 数据类型
	int  m_nSize;		// 数据长度
	char m_cData[1];    // 具体数据根据需要定义,服务器不做任何处理
};
// 应答
struct NoteMsgDataAns
{
	DataHead m_dhHead;	// 数据报头

	int  m_nType;		// 数据类型
	int  m_nSize;		// 数据长度
	char m_cData[1];	// 具体数据根据需要定义,服务器不做任何处理
};

/*
请求类型: RT_LOGIN、RT_LOGIN_INFO、RT_LOGIN_HK、RT_LOGIN_FUTURES、RT_LOGIN_FOREIGN
功能说明: 客户端登录请求
备	  注: 
*/
/* 请求结构 */
struct ReqLogin
{
	char			m_szUser[64];	// 用户名
	char			m_szPWD[64];	// 密码(加密密文），详细参加协议
	char			m_cLoginType;   //1、账号登录 2、昵称登录
};

struct AnsLoginLevel2
{
	short		m_nError;	// 错误标识 0: 校验通过 1:用户名或密码错误 
	// 2:客户已登陆 3:未开通 4:过期等等
	int			m_nGrant;	// 权限位 二进制位：每位代表一种权限，具体权限按需求定
	int 		m_nValidDay;	// 有效天数,提供客户端快到期提醒使用
};

/*修改密码*/
struct ReqModifyPwd
{
	char m_szUser[20];
	char m_szOldPwd[20];
	char m_szNewPwd[20];
};

/* 请求结构 */
struct ReqChangePassword
{
	char			m_szUser[64];	// 用户名
	char			m_szOldPWD[64];	// 密码(加密密文），详细参加协议
	char			m_szNewPWD[64];	// 密码(加密密文），详细参加协议
};

#define AnsLogin_Normal 0x0001   // 一般用户
#define AnsLogin_Midlle 0x0002   // 中级用户
#define AnsLogin_Hight  0x0004   // 高级用户

/* 返回结构 */
struct AnsLogin0
{
	DataHead		m_dhHead;	//数据报头

	long			m_nError:2;	// 错误号 见RT_LOGIN说明1
	long			m_nSize:30;	// 长度

	char			m_szRet[1];	// 配置文件数据或者返回错误信息字符串 见RT_LOGIN说明1
};

struct AnsLogin
{
	DataHead		m_dhHead;	//数据报头

	//long			m_nError:2;	// 错误号 见RT_LOGIN说明1
	//long			m_nSize:30;	// 长度

	short			m_nError;
	short 			m_nAlignment;	// 为了4字节对齐而添加的字段
	long			m_nSize;
	char			m_szRet[1];	// 配置文件数据或者返回错误信息字符串 见RT_LOGIN说明1
};
/*
RT_LOGIN说明1:
１、m_nError 等于0，则m_szRet为配置文件数据。
２、m_nError 小于0，则m_szRet为服务器返回错误信息字符串。
３、m_nError 等于ERROR_*(错误ID)，则m_szRet为空。
*/

struct AnsPwdModify
{
	DataHead m_dhHead;
	long     m_nSize;
	char     m_szRet[1];
};

/*
请求类型: RT_INITIALINFO
功能说明: 代码表的验证和初始化
备	  注: 
*/

/*
请求结构：
代码表的验证和初始化请求
*/
struct ReqInitSrv
{
	short            m_nSrvCompareSize;		// 服务器比较个数
	short 			 m_nAlignment;    		// 为了4字节对齐而添加的字段
	ServerCompare    m_sServerCompare[1];   // 服务器比较信息
};

/*
请求类型: RT_STOCKINFOLIST 
功能说明: 请求股票代码列表
备	  注: 

请求结构 : ReqStockInfoList
返回结构 : 
*/
struct ReqStockInfoList
{
	int						m_nSize;				// 市场个数
	HSMarketDataType	m_nMarketType[1];		// 所有市场类别
};

struct AnsStockInfoList
{
	DataHead				m_dhHead;		 // 数据报头
	short					m_nSize;		 // 报价表数据个数
	short 					m_nAlignment;    // 为了4字节对齐而添加的字段
	StockUserInfo			m_pnowData[1];	 // 报价表数据
};
/*
返回结构：
代码表的验证和初始化应答
股票初始化信息
*/
/* 单个股票信息 */
struct StockInitInfo
{
	char		m_cStockName[16];	// 股票名称
	CodeInfo	m_ciStockCode;		// 股票代码结构
	long		m_lPrevClose;		// 昨收
	long		m_l5DayVol;			// 5日量(是否可在此加入成交单位？？？？）
};

/* 单个市场包含的信息 */
struct OneMarketData
{
	CommBourseInfo  m_biInfo;		 // 市场信息

	short           m_nSize;        // 股票个数据
	short 		    m_nAlignment;    // 为了4字节对齐而添加的字段
	StockInitInfo   m_pstInfo[1];    // (m_biInfo）里指定分类的代码数据
};


#define AnsInitialData_AutoPush 0x0001  // 服务器主动初始化
#define AnsInitialData_All      0x0002  // 当前市场所有分类数据

/* 返回结构 */
struct  AnsInitialData  
{
	DataHead		m_dhHead;		// 数据报头

	short		    m_nSize;		// 市场个数
	union
	{
		short 			m_nAlignment;   // 是否为主推初始化包(0：请求初始化包，非0：主推初始化包)
		short			m_nOpertion;    // 返回选项,参见:AnsInitialData_All 定义
	};
	OneMarketData   m_sOneMarketData [1]; // 市场数据
};

/* 市场初始化信息中股票名中文编码类别 */
#define ENCODING_ANSII		1
#define ENCODING_GB2312	2
#define ENCODING_GB18030	3
#define ENCODING_BIG5		4
#define ENCODING_Unicode	5
#define ENCODING_UTF8		6


/// 市场信息结构
struct CommBourseInfo_VarCode
{
	StockTypeName	m_stTypeName;	// 市场名称(对应市场类别)
	UINT16			m_nMarketType;	// 市场类别(最高俩位)
	INT16 			m_cCount;		// 有效的证券类型个数

	INT16 			m_nCodeLen;		// 股票代码的长度。
	// 须定义成4的倍数，此字段不能为0

	INT16 			m_nChNameLen;	// 股票中文名长度。
	// 须定义成4的倍数，为0则无中文名

	INT16 			m_nEnNameLen;	// 股票英文名长度。
	// 须定义成4的倍数，为0则无英文名

	INT16 			m_nDSTFlag;		// 夏令时标志
	// 0，非夏令时。1，夏令时。

	INT16 			m_nTimeZone;	// 时区格式±HHMM。
	// 如东八区为800，西11区为-1100。

	INT16 			m_nEncodingType;// 中文编码类型。
	// 参见ENCODING_*一系列宏定义

	INT16 			m_nHand;		// 每股手数

	UINT			m_lDate;		// 今日日期（19971230）
	UINT			m_dwCRC;		// CRC校验码（分类）

	StockType		m_stNewType[1];	// 证券信息
};


/* 单个股票信息 */
struct StockInitInfo_VarCode
{
	UINT		m_lPrevClose;		// 昨收
	UINT		m_l5DayVol;		    // 5日量(是否可在此加入成交单位？？？？）

	char		m_cStockCode[1];		// 股票名称，包括代码、英文名和中文名。
	// 顺序为：代码、中文名、英语名
	// 其中代码、英文名和中文名的长度定义
	// 在CommBourseInfo_VarCode结构中。
	// 若对应长度为0，则无对应字段
};



/* 单个市场包含的信息 */
struct OneMarketData_VarCode
{
	CommBourseInfo_VarCode	m_biInfo;		// 市场信息

	INT16					m_nSize;		// 股票个数据
	INT16 					m_nAlignment;   // 为了4字节对齐而添加的字段
	StockInitInfo_VarCode	m_pstInfo[1];   // (m_biInfo）里指定分类的代码数据
};

/* 返回结构 */
struct AnsInitialData_VarCode
{
	DataHead		m_dhHead;		// 数据报头

	INT16 			m_nSize;		// 市场个数
	union
	{
		INT16 		m_nAlignment;	// 是否为主推初始化包
		// (0：请求初始化包，非0：主推初始化包)
		INT16		    m_nOpertion;	// 返回选项,参见:AnsInitialData_All 定义
	};
	OneMarketData_VarCode	m_sOneMarketData[1];	// 市场数据
};


struct CommRealTimeData
{	
	CodeInfo		m_ciStockCode;		// 股票代码

	StockOtherData	m_othData;			// 实时其它数据
	char			m_cNowData[1];		// 指向ShareRealTimeData的任意一个
	// 根据代码得到下一个位置ptr
	CommRealTimeData* GetNext(CodeInfo* pCode,int& nNowSize,int* pTotal = NULL,int nFixSize = 0)
	{
		if( pCode == NULL )
			return this;

		if( nFixSize != 0 )
			nNowSize = nFixSize;
		else
		{
			nNowSize = GetStructSize( pCode );
			if( nNowSize == 0 )
				return this;
		}

		short nSize = nNowSize + GetAddSize();
		if( pTotal )
			*pTotal += nSize;

		char* pp = (char*)this;
		pp += nSize;

		return (CommRealTimeData*)pp;
	}

	ShareRealTimeData* GetShareData()
	{
		return (ShareRealTimeData*)m_cNowData;
	}

	static int GetAddSize()
	{
		return (sizeof(CommRealTimeData) - sizeof(char));//(sizeof(CodeInfo) + sizeof(StockOtherData));
	}

	// 结构大小(目前只支持相同结构处理，否则错误)
	static int GetStructSize(CodeInfo* pCode,int nAdd = 0)
	{
		if( pCode == NULL )
			return 0;

		switch(MakeMarket(pCode->m_cCodeType))
		{
		case (HSMarketDataType)STOCK_MARKET:		     // 股票
			if( MakeIndexMarket(pCode->m_cCodeType) )
				return (sizeof(HSIndexRealTime) + nAdd); // 指数实时基本数据
			return (sizeof(HSStockRealTime) + nAdd);
		case (HSMarketDataType)EXTEND_MARKET:            // 扩展指数
		case (HSMarketDataType)CAE_MARKET:               // 文交所
			return (sizeof(HSStockRealTime) + nAdd);
		case (HSMarketDataType)FUTURES_MARKET:			 // 期货
		case (HSMarketDataType)WP_MARKET:                // 外盘
			return (sizeof(HSQHRealTime) + nAdd);
		case (HSMarketDataType)COMMODITIES_MARKET:       // 商品
			return (sizeof(HSSpotRealTime) + nAdd);
		case (HSMarketDataType)HK_MARKET:                // 港股
			return (sizeof(HSHKStockRealTime) + nAdd);  
		case (HSMarketDataType)OPTION_MARKET:            // 期权
			return (sizeof(HSOPTRealTime) + nAdd); 
		default:
			break;
		}

		return 0;
	}
};

/* 返回结构 */
struct AnsRealTime 
{
	DataHead				m_dhHead;		 // 数据报头
	short					m_nSize;		 // 报价表数据个数
	short 					m_nAlignment;    // 为了4字节对齐而添加的字段
	CommRealTimeData	  	m_pnowData[1];	 // 报价表数据
}; 

/*
代码表初始化说明：
代码表初始化校验方式：校验每个分类的CRC（分类即最低级的品种）。
代码表初始化数据包被服务器推送的情况有以下两种：
1.客户端边上初始化，此类情况分：
a.某个市场所有品种校验相同，则不返回代码表。
b.某个市场中某些品种校验不同，则只返回不同品种的品种信息及品种代码表。
c.某个市场所有品种校验不同，则返回所有市场信息
2.服务器代码表变动时（如清盘），主推代码表，则中给客户端推送变
动品种的品种信息及品种代码表。并且，所有品种按市场归类，同类的品种
组成一个OneMarketData返回。

注：说明中提到的“品种信息”指StockType，
“品种代码表”指CommBourseInfo指定品种包含的所有代码,存放于OneMarketData::m_pstInfo
*/


/*
请求类型: RT_SERVERINFO
功能说明: 主站信息
备	  注: 
*/
/* 请求结构 : 常用请求*/
/* 
返回结构 :
主站返回信息结构
*/

#define AnsServerInfo_SupportMarket  0x0001 // 支持分类代码请求

struct AnsServerInfo
{
	DataHead	m_dhHead;			// 数据报头
	char		m_pName[32];		// 服务器名
	char		m_pSerialNo[12];    // 序列号，验证正版性
	long		m_lTotalCount;		// 已连接过的总数

	long		m_lToDayCount;		// 当日连接总数
	long		m_lNowCount;		// 当前连接数
};


struct AnsServerInfo2
{
	DataHead	m_dhHead;			// 数据报头

	long		m_lTotalCount;		// 已连接过的总数

	char		m_strAddr[20];      // ip  127.123.123.123
	short		m_nPort;			// 下个连接端口

	short		m_nMaxCount;

	long		m_lResever[2];		//
};

/*
请求类型: 
类型ID							含义
RT_TEXTDATAWITHINDEX_NEGATIVE	倒序资讯索引数据
RT_BYINDEXRETDATA				资讯内容数据
RT_TEXTDATAWITHINDEX_PLUS		正序资讯索引数据
RT_USERTEXTDATA					自定义资讯请求（如菜单等）
RT_FILEREQUEST					纯粹文件请求（例如配置文件等）
功能说明: 
1、	倒序资讯索引数据：例如信息地雷的请求与应答
2、	资讯内容数据请求与应答
3、	正序资讯索引数据：目前一般为F10资料索引请求与应答
4、	自定义资讯请求（如菜单等）：目前为券商自定义菜单请求与应答
5、	纯粹文件请求：包括主要配置以及数据文件的下载请求与应答

*/
/* 倒序资讯索引和资讯内容数据项 */
struct TextMarkData
{
	long	m_lCRC;	      		//ＣＲＣ值
	long	m_lBeginPos;     	// 开始位置，直接针对索引文件或内容文件的偏移（字节）
	long	m_lEndPos;			// 终止位置,同上,参见说明

	long	m_lCheckCRC;		//是否进行校验ＣＲＣ　非０进行校验，０则不校验， 

	/*指向字串,客户端使用,字串格式为: aa;bb;cc;dd
	其中aa为:
	#define INFO_PATH_KEY_F10			 "F10-%i"
	#define INFO_PATH_KEY_TREND			 "TREND-%i"
	#define INFO_PATH_KEY_TECH			 "TECH-%i"
	#define INFO_PATH_KEY_REPORT			 "REPORT-%i"
	其中bb为: 配置的段名 
	其中cc为: 配置的取值名
	其中dd为: 配置文件名*/
	char	m_szInfoCfg[128];	//包含配置文件名称等信息的字符串，客户端使用
	char	m_cTitle[64];		// 标题,客户端本地使用
	char	m_cFilePath[192];	// 文件名/路径
};

/*请求结构*/
struct ReqTextData	  //索引和内容请求包
{
	TextMarkData    m_sMarkData;		//校验数据项
};
/*返回结构*/
struct AnsTextData		// 详细文本信息返回
{
	DataHead			m_dhHead;	// 数据报头
	TextMarkData        m_sMarkData;// 索引和内容
	unsigned long		m_nSize;	// 数据长度
	char				m_cData[1]; // 数据
};

// 资讯类别
enum InfoClassType
{
	InfoClassType_D1    = 1,	// 金阳光资讯
	InfoClassType_D2    = 2,	// 金阳光策略
	InfoClassType_D3    = 3,	// 金股池
	InfoClassType_D4    = 4,	// 稳健型投资组合
	InfoClassType_D5    = 5,	// 晨会纪要
	InfoClassType_D6    = 6,	// 信息简报
	InfoClassType_D7    = 7,	// 分析师快报
	InfoClassType_E1    = 8,	// 晨会报告
	InfoClassType_E2    = 9,	// 宏观策略
	InfoClassType_E3    = 10,	// 行业研究
	InfoClassType_E4    = 11,	// 公司研究
	InfoClassType_E5    = 12,	// 权证研究
	InfoClassType_E6    = 13,	// 基金研究
	InfoClassType_E7    = 14,	// 债券研究
	InfoClassType_N1    = 15,	// 新增资讯
	InfoClassType_N2    = 16,	// 新增资讯
	InfoClassType_N3    = 17,	// 新增资讯
	InfoClassType_N4    = 18,	// 新增资讯
	InfoClassType_N5    = 19,	// 新增资讯
	InfoClassType_N6    = 20,	// 新增资讯
	InfoClassType_N7    = 21,	// 新增资讯
	InfoClassType_N8    = 22,	// 新增资讯
	InfoClassType_N9    = 23,	// 新增资讯
	InfoClassType_NA    = 24,	// 新增资讯
	InfoClassType_NB    = 25,	// 新增资讯
	InfoClassType_NC    = 26,	// 新增资讯
	InfoClassType_ND    = 27,	// 新增资讯
	InfoClassType_NE    = 28,	// 新增资讯
};

// 操作状态
enum InfoOperator
{
	InfoOperator_ChuShi  = 0x0000, // 初始状态
	InfoOperator_ShenHe  = 0x0001, // 已审核
	InfoOperator_ShanChu = 0x0002, // 已删除
	InfoOperator_ZuoFei	 = 0x0004, // 已作废
	InfoOperator_TuiHui	 = 0x0008, // 已退回

	InfoOperator_DianJiLv = 0x1000, // 更新点击率

	InfoOperator_FengKongShenHe = 0x40000000,   // 风险控制审核
	InfoOperator_FengKong = 0x80000000, // 风险控制属性

	//InfoOperator_TianJia = 0x0004, // 添加
};

// 用户属性
enum UserAttribute
{
	// 注意:1~n类用户可以对应以下名称,根据实际需要而定
	//“试用”、“黄金”、“铂金”、“钻石”
	// 最大支持28个用户类型
	UserAttribute_0     = 0x00000000, // 所有用户都可以看
	UserAttribute_1     = 0x00000001, //  1类用户
	UserAttribute_2     = 0x00000002, //  2类用户
	UserAttribute_3     = 0x00000004, //  3类用户
	UserAttribute_4     = 0x00000008, //  4类用户
	UserAttribute_5     = 0x00000010, //  5类用户
	UserAttribute_6     = 0x00000020, //  6类用户
	UserAttribute_7     = 0x00000040, //  7类用户
	UserAttribute_8     = 0x00000080, //  8类用户
	UserAttribute_9     = 0x00000100, //  9类用户
	UserAttribute_10    = 0x00000200, // 10类用户
	UserAttribute_11    = 0x00000400, // 11类用户
	UserAttribute_12    = 0x00000800, // 12类用户
	UserAttribute_13    = 0x00001000, // 13类用户
	UserAttribute_14    = 0x00002000, // 14类用户
	UserAttribute_15    = 0x00004000, // 15类用户
	UserAttribute_16    = 0x00008000, // 16类用户
	UserAttribute_17    = 0x00010000, // 17类用户
	UserAttribute_18    = 0x00020000, // 18类用户
	UserAttribute_19    = 0x00040000, // 19类用户
	UserAttribute_20    = 0x00080000, // 20类用户
	UserAttribute_21    = 0x00100000, // 21类用户
	UserAttribute_22    = 0x00200000, // 22类用户
	UserAttribute_23    = 0x00400000, // 23类用户
	UserAttribute_24    = 0x00800000, // 24类用户
	UserAttribute_25    = 0x01000000, // 25类用户
	UserAttribute_26    = 0x02000000, // 26类用户
	UserAttribute_27    = 0x04000000, // 27类用户
	UserAttribute_28    = 0x08000000, // 28类用户

	UserAttribute_29    = 0x10000000, // 超级用户
	UserAttribute_30    = 0x20000000, // 审核用户
	UserAttribute_31    = 0x40000000, // 发布用户
	UserAttribute_32    = 0x80000000, // 删除用户
};

// 信息状态
struct InfoCheckStatus
{
	unsigned int	m_InfoClassType;	    // 信息类别,参见 InfoClassType 定义
	unsigned int	m_InfoOperator;		    // 资讯状态,参见 InfoOperator  定义,可以多个并集
	unsigned int	m_UserAttribute;	    // 用户属性,参见 UserAttribute 定义,可以多个并集
	unsigned int	m_Atattch[5];		    // 附件名称,用CTime保存
	unsigned int    m_nSalesDepartmentNum;  // 营业部号  参见 SalesDepartmentNum 定义
	unsigned int	m_nSenderNum;			// 发布号(用户ID)（可以指向：发布人、发布单位、发布商）,参见SenderNum定义
	unsigned int	m_nAreaNum;			    // 点击次数
	//add by lxqi 20090223
	union
	{
		unsigned int	m_nRankNo;				//资讯标题星级
		unsigned int	m_nAuditNum;			// 审核
	};
	//add by lxqi 20081016
	unsigned int    m_index_no;             //发布后的资讯索引编号
};

// 服务器返回的用户信息
struct SrvCheckInfo
{
	unsigned int	m_InfoClassType;	    // 信息类别,参见 InfoClassType 定义
	unsigned int    m_InfoOperator;		    // 操作状态,参见 InfoOperator  定义,可以多个并集
	unsigned int    m_UserAttribute;	    // 用户属性,参见 UserAttribute 定义,可以多个并集
	unsigned int    m_nSalesDepartmentNum;  // 营业部号,参见 SalesDepartmentNum 定义
	unsigned int	m_nSenderNum;			// 发布号(用户ID)（可以指向：发布人、发布单位、发布商）,参见SenderNum定义
	unsigned int	m_nAreaNum;			    // 点击次数	

	char			m_szUserName[20];		// 用户名称

	unsigned int	m_nClassNum;			// 等级提示编号
	char            m_cCurRank[20];         // yangdl 2008.05.23 等级名称   
	char			m_cResever[30];
};

#define InfoIndexDataEx_mark (0x7F) // 发布索引标志

// 索引文件记录,兼容InfoIndex结构
struct InfoIndexDataEx
{
	char m_cType; // Bit0：     加密标志 (0:不加密,1:加密)
	// Bit1-Bit6：保留
	// Bit7： 无效记录标志位(0:有效记录，1:无效记录)
	// 0x00	普通信息索引
	// 0x01	加密信息索引
	// 0x80	无效记录
	// 0x7F	发布的资讯(注意使用)

	char m_cGroup;   // Bit0-Bit3为第一大类（共支持16种类型）
	//（此4Bit为资讯厂商必须告诉xx的信息）
	// Bit0-3值	信息类型
	// 0x00	    交易所公告
	// 0x01	    财经新闻
	// 0x02	    个股历史资讯 (公司大事记)
	// 0x03	    个股实时资讯
	// 0x04	    F10资料
	// 0x05-0x0e	保留
	// 0x0f	    其它	

	char m_cMarket;  // Bit0-Bit7为市场分类（共支持8个市场），
	// 和本信息相关的市场Bit置为1，
	// 当信息不属于任何市场时，Bit0-Bit7全为0。
	// 0	上海
	// 1	深圳
	// 2	创业
	// 3	香港
	// 4	台湾
	// 5	美国
	// 6	保留
	// 7	其它

	long m_lDate;	   // 年*10000+月*100+日
	long m_lTime;      // 时*10000+分*100+秒
	char m_cTitle[64]; // 字符串必须用0x00结尾
	// 个股历史资讯	相关个股历史资讯内容的标题。内容最多63个字节，必须用0x00结尾。
	// 个股实时资讯	相关个股实时资讯内容的标题。内容最多63个字节，必须用0x00结尾。
	// 个股F10资料	即为F10资料页上的分类名称，最多支持4个汉字。
	// 资讯厂商的特色资讯	相关特色资讯内容的标题。内容最多63个字节，必须用0x00结尾。

	union
	{
		char m_CYlsFilePath[80]; // 源文件路径 // 130
		char m_cFilePath[80];    // 源文件路径 // 130
	};

	long m_lOffset;		  // 偏移位置
	long m_lLength;	      // 信息长度
	//char m_cCode[4][9];   // 相关代码
	// 最多支持4个相关个股代码。每个相关个股代码占9字节，其中第1字节是该个股所在市场种类(编码见附表三)，其它8个字节用于填写相关个股代码，不足填0x00。
	char m_write[8];    //资讯发布的作者
	char m_source[12];  //资讯来源 
	char m_cCode[2][8];   // 相关代码


	//char m_cReserved[55]; // 保留 // 5
	union
	{
		char FilePK[12];	  // 新闻序号（当天新闻序号唯一，不保证连续）(易富新闻序号)
		char m_cReserved[55]; // 保留 // 5

		InfoCheckStatus m_sInfoCheckStatus; // 对于索引特定处理,只针对发布的资讯
	};

	char m_cSubType;	  // 信息子分类 0-8
	// 0 	提示
	// 1	说明
	// 2	公司动态
	// 3	分析点评
	// 4	分红配股
	// 5	业绩报告
	// 6 	招股上市
	// 7	公司其它公告

	// 100 文件
	// 101 文件索引

	char m_cChksum;		  // 校验
	char* m_pSubContent;  // add by lxqi 20081105 资讯内容概要。注意：主要在个人提示时使用，使用时要分配空间，用完后要手动释放
};

/*
请求类型: RT_BULLETIN 
功能说明: 主推紧急公告
备	  注: 
*/
/* 请求结构 : 无请求*/
/* 返回结构 */
struct AnsBulletin
{
	DataHead		m_dhHead;		//数据报头

	long			m_nSize;		//公告内容长度	
	char			m_cData[1];		//公告内容
};


// 实时数据
struct HSStockRealTimeOther
{
	long				m_lExt1;		// 目前只在ETF时有用，为其IOPV值（例如510050时为510051的最新价）
	long				m_lStopFlag;	// 停盘标志。0：正常，1：停盘
	union
	{
		struct 
		{
			float m_fSpeedUp; // 五分钟涨速
			long m_lRes[2]; // 预留
		};
		long m_lOther[3]; // 预留 
	};
};

// 板块指数数据
struct HSIndexRealTimeOther 
{
	char m_szRiseCode[8];	// 领涨代码
	char m_szFallCode[8];	// 领跌代码
	char m_szClassifiedCode[8]; // 指数分级编码，目前不知有什么用途，暂时这样传输
	// 服务器过来扩大10000
	long m_lRise;		    // 领涨代码涨幅
	long m_lFall;			// 领跌代码跌幅
};

// 板块指数扩展数据
struct HSIndexRealTime_Ext 
{
	unsigned short			m_cSize;		// 结构体长度
	unsigned short			m_nVersion;		// 版本号
	HSIndexRealTime			m_indexRealTime;
	HSIndexRealTimeOther	m_indexRealTimeOther;
};

// 股票
struct HSStockRealTime_Ext 
{
	unsigned short			m_cSize;		// 结构体长度
	unsigned short			m_nVersion;		// 版本号
	union
	{
		HSIndexRealTime			m_indData;		  // 指数实时基本数据
		HSStockRealTime			m_stockRealTime;  // 时时数据
	};
	HSStockRealTimeOther	m_stockOther;	// 股票扩展数据
};

// 时时数据分类
union ShareRealTimeData_Ext
{
	HSStockRealTime_Ext		m_nowDataExt;		// 个股实时基本数据
	HSStockRealTime_Ext		m_stStockDataExt;

	HSQHRealTime			m_qhData;		    // 期货实时基本数据
	HSSpotRealTime          m_spotData;         // 商品实时基本数据
	//HSQHRealTime_Min		m_qhMin;            // (暂时不知道哪个功能号支持)
	HSIndexRealTime_Ext		m_indBlockData;     // 板块指数
	HSOPTRealTime           m_optionData;       // 期权实时基本数据
	HSHKStockRealTime_Ext   m_hkDataExt;        // 港股实时基本数据
};

/*
请求类型: RT_AUTOPUSH_EXT
功能说明: 常用主推扩展
备	  注: 
*/

struct CommRealTimeData_Ext
{	
	unsigned short		m_cSize;		// 结构体长度
	unsigned short		m_nVersion;		// 版本号
	CodeInfo		    m_ciStockCode;  // 股票代码

	StockOtherData		m_othData;			// 实时其它数据
	char			    m_cNowData[1];		// 指向ShareRealTimeData_Ext的任意一个

	ShareRealTimeData_Ext * GetShareData()
	{
		return (ShareRealTimeData_Ext *)m_cNowData;
	}

	CommRealTimeData_Ext* GetNext(CodeInfo* pCode,int& nNowSize,int* pTotal = NULL,int nFixSize = 0)
	{
		if( pCode == NULL )
			return this;

		if( nFixSize != 0 )
			nNowSize = nFixSize;
		else
		{
			nNowSize = GetStructSize( pCode );
			if( nNowSize == 0 )
				return this;
		}
		int nSize = nNowSize + GetAddSize();
		if( pTotal )
			*pTotal += nNowSize;

		char* pp = (char*)this;
		pp += nSize;

		return (CommRealTimeData_Ext*)pp;
	}
	static int GetAddSize()
	{
		return (sizeof(CommRealTimeData_Ext) - sizeof(char));//(sizeof(CodeInfo) + sizeof(StockOtherData));
	}

	// 结构大小(目前只支持相同结构处理，否则错误)
	static int GetStructSize(CodeInfo* pCode,int nAdd = 0)
	{
		if( pCode == NULL )
			return 0;

		switch(MakeMarket(pCode->m_cCodeType))
		{
		case (HSMarketDataType)STOCK_MARKET:		     // 股票
		case (HSMarketDataType)EXTEND_MARKET:            // 扩展指数
		case (HSMarketDataType)CAE_MARKET:               // 文交所
			return (sizeof(HSStockRealTime_Ext) + nAdd);
		case (HSMarketDataType)FUTURES_MARKET:			 // 期货
		case (HSMarketDataType)WP_MARKET:                // 外盘
			return (sizeof(HSQHRealTime) + nAdd);
		case (HSMarketDataType)COMMODITIES_MARKET:       // 商品
			return (sizeof(HSSpotRealTime) + nAdd);
		case (HSMarketDataType)OPTION_MARKET:            // 期权
			return (sizeof(HSOPTRealTime) + nAdd);
 		case (HSMarketDataType)HK_MARKET:				 // 港股
 			return (sizeof(HSHKStockRealTime_Ext) + nAdd);
// 		case (HSMarketDataType)FOREIGN_MARKET:			 // 外汇
// 			return (sizeof(HSWHRealTime) + nAdd);
		default:
			break;
		}

		return 0;
	}
};

struct AnsHSAutoPushData_Ext
{
	DataHead	 	m_dhHead;				// 数据报头

	long		 	m_nSize;				// 数据个数
	CommRealTimeData_Ext 	m_pstData[1];	// 主机实时发送的数据
};

/*
请求类型: RT_DYNREPORT 
功能说明: 
1.	强弱分析
2.	指标排序
3.	热门板块分析
4.	区间分析
5.	跑马灯股票列表数据
6.	预警
7.	星空图
备	  注: 
*/
/* 请求结构 */
struct ReqDynReportData
{
	long                m_lReqMask0;	// 掩码 0-31位
	long                m_lReqMask1;	// 掩码 32-63位 

	HSMarketDataType	m_cCodeType;	// 类别，见下面说明
	short				m_nSize;		// 后续代码长度对齐

	CodeInfo			m_pCode[1];		// 股票列表
};
/* 返回结构 ：
说明:
1、	m_cCodeType 可参考RT_REPORTSORT说明
2、	m_lReqMask0为0-31bit，m_lReqMask1为32-63bit
3、	每一块数据以代码CodeInfo起始，后接数据；
数据单位为4字节长度，不足4字节则作补零处理;
返回数据按照低位至高位的顺序排列数据
4、	代码为固定返回数据内容

*/
struct AnsDynamicData
{
	DataHead			m_dhHead;		//数据报头
	long				m_lReqMask0; 	//当前要返回的结构俺码
	long				m_lReqMask1; 	//当前要返回的结构俺码

	unsigned long		m_nSize;		//数据长度
	char				m_cData[1];		//数据地址
};

/*
请求类型: RT_REPORTSORT 
功能说明: 
1、排名报价表（61-66乾隆操作键，下同）
2、点击列排序
备	  注: 
*/
/*（排名报价表--61-66、点击列排序）
请求结构
说明：
m_cCodeType有以下几种分类：
1、	标准分类：上A、深A
m_nSize = 0，m_sAnyReportData不指向任何东西
2、	系统板块：SYSBK_BOURSE
m_sAnyReportData指向ReqOneBlock
注：目前版本不进行板块CRC校验，直接发送报价数据。
3、	自选股和自定义板块（USERDEF_Bourse） 
m_sAnyReportData指向AnyReportData
4、	“所有A股”等
HSMarketDataType为二级分类取或运算，例如“所有A股”可以表示为：
STOCK_MARKET| SH_BOURSE| SZ_BOURSE| KIND_STOCKA
*/
/* 请求结构 */
struct AnyReportData
{
	CodeInfo		m_ciStockCode;	//股票代码
};

struct ReqAnyReport
{
	HSMarketDataType	m_cCodeType; 		// 类别，见RT_REPORTSORT说明1
	short				m_nBegin;			// 显示开始
	short				m_nCount; 			// 显示个数
	char				m_bAscending;		// 升序/降序
	char 				m_cAlignment;		//为了4字节对齐而添加的字段
	int					m_nColID;			// 排名列id 

	short				m_nSize;			// 个数
	short				m_nAlignment;		//为了4字节对齐而添加的字段
	AnyReportData		m_sAnyReportData[1];//客户端给参考数据给服务器端
};

// RT_REPORTSORT_Simple

struct CommRealTimeData_Simple
{	
	CodeInfo m_ciStockCode;		// 股票代码

	long	 m_lPrevClose;		// 昨收
	char	 m_szValue[12];

	short	 m_nSize;			// 大小
	char	 m_szName[8];		// 名称	
};

struct AnsReportData_Simple 
{
	DataHead					m_dhHead;			// 数据头

	short						m_nSize;			// 数据个数
	CommRealTimeData_Simple 	m_prptData[1];		// 数据
};


/*
RT_REPORTSORT说明1:
m_cCodeType有以下几种分类：
1、	标准分类：上A、深A
m_nSize = 0，m_sAnyReportData不指向任何东西
2、	系统板块：SysBK_Bourse -- 当前版本暂时不支持验证板块。
m_sAnyReportData指向ReqOneBlock
板块文件采用配置文件＋单个文件方式，客户端请求时将板块CRC校验码发送给服务器，服务器	将服务器板块CRC与客户端板块CRC进行检查，如果两者不匹配，则发送系统板块压缩数据包；然后发送报价数据，否则直接发送报价数据。
3、	自选股和自定义板块：UserDefBk_Bourse  
m_sAnyReportData指向AnyReportData
*/

#define BLOCK_NAME_LENGTH		32			// 板块名称长度
/* 请求结构 单个板块请求*/
struct ReqOneBlock
{
	long   m_lCRC;            // 板块CRC
	char   m_szBlockName[BLOCK_NAME_LENGTH];  // 板块名
};

/* 返回结构 */
struct AnsReportData 
{
	DataHead		m_dhHead;			// 数据头

	short			m_nSize;			// 数据个数
	short 			m_nAlignment;		// 为了4字节对齐而添加的字段
	CommRealTimeData 	m_prptData[1];		// 数据	
};

/*
请求类型: RT_GENERALSORT
功能说明: 综合排名报表
备	  注: 
*/
/* 请求结构 */
struct ReqGeneralSort
{
	HSMarketDataType m_cCodeType;   // 市场类别
	short            m_nRetCount;   // 返回总数
	short            m_nSortType;   // 排序类型 见RT_GENERALSORT说明1
	short 			 m_nAlignment;  // 为了4字节对齐而添加的字段
	// 目前(2004年3月11日)用于新增功能的使用
	// 用于综合排名中快速排名窗口的几份钟排名设置。
};
/*
RT_GENERALSORT说明1:
m_nSortType掩码如下：（可取多值）
1、RT_RISE			涨幅排名
2、RT_FALL			跌幅排名
3、RT_5_RISE		5分钟涨幅排名
4、RT_5_FALL		5分钟跌幅排名
5、RT_AHEAD_COMM	买卖量差（委比）正序排名
6、RT_AFTER_COMM	买卖量差（委比）倒序排名
7、RT_AHEAD_PRICE	成交价震幅正序排名
8、RT_AHEAD_VOLBI	成交量变化（量比）正序排名
9、RT_AHEAD_MONEY	资金流向正序排名
*/

/* 综合排名报表数据项 */
struct GeneralSortData
{
	CodeInfo		m_ciStockCode;		// 股票代码
	long			m_lNewPrice;		// 最新价
	long			m_lValue;			// 计算值
};

/*返回结构*/
struct AnsGeneralSort
{
	DataHead			m_dhHead;		// 数据报头
	short				m_nSortType;    // 排序类型
	short				m_nSize;		// 单个子包所含数据GeneralSortData个数
	// 当m_ nSortType为单值时（只有一位为1）,
	// 表示m_prptData数组的个数为m_nSize个。
	// 当m_ nSortType为多值相或时（如N位为1），表示此返回包针对N个子包，
	// 每个子包所含GeneralSortData个数为m_nSize，数组m_prptData的长度为N*m_nSize。
	GeneralSortData		m_prptData[1];	// 数据		
};

/* 
RT_SEVER_CALCULATE
返回计算数据数据包，使用常用请求包
*/

struct AnsSeverCalculate
{
	DataHead m_dhHead;

	int		 m_nSize;
	char     m_cData[1];
};

// 计算数据
struct SeverCalculateData
{
	//CodeInfo m_sCodeInfo;
	HSMarketDataType	m_cCodeType;	// 证券类型
	char				m_cCode[6];		// 证券代码

	float				m_fUpPrice;     // 涨停板价
	float				m_fDownPrice;   // 跌停板价
};

/*
RT_ANS_BYTYPE
返回指定类型的数据,由数据内部决定什么类型
请求包,注意:AskData 中 m_nOption 指向的类型
*/

struct AnsDataByType
{
	DataHead m_dhHead;

	short	 m_nSubType;   // 数据类型，根据此类类型确定 m_cData 里的数据,参见ByType_*定义
	short	 m_nResever;

	int		 m_nSize;
	char     m_cData[1];
};

/* 
RT_SEVER_EMPTY
服务器没有数据时返回空包情况，一般日线无数据时
*/
struct AnsSeverEmpty
{
	DataHead			m_dhHead;		// 数据报头
	unsigned short		m_nOldType;     // 数据请求类型
	unsigned short		m_nAlignment;   // 
	int					m_nSize;
	char				m_cData[1];
};

/*
请求类型: RT_GENERALSORT_EX
功能说明: 综合排名报表(加入了几分钟排名设置)
备	  注: 
*/
/* 请求结构 */
struct ReqGeneralSortEx
{
	HSMarketDataType m_cCodeType;   // 市场类别
	short            m_nRetCount;   // 返回总数
	short            m_nSortType;   // 排序类型 见RT_GENERALSORT说明1
	short 			 m_nMinuteCount;// 用于综合排名中快速排名窗口的几份钟排名设置。
	// 0 使用服务器默认分钟数
	// 1 ... 15为合法取值(一般可能的取值为1,2,3,4,5,10,15)
};

/*返回结构*/
struct AnsGeneralSortEx
{
	DataHead			m_dhHead;		// 数据报头
	short				m_nSortType;    // 排序类型
	short				m_nSize;		// 单个子包所含数据GeneralSortData个数
	// 当m_ nSortType为单值时（只有一位为1）,
	// 表示m_prptData数组的个数为m_nSize个。
	// 当m_ nSortType为多值相或时（如N位为1），表示此返回包针对N个子包，
	// 每个子包所含GeneralSortData个数为m_nSize，数组m_prptData的长度为N*m_nSize。
	short				m_nAlignment;   // 字节对齐
	short				m_nMinuteCount;	// 用于综合排名中快速排名窗口的几份钟排名设置。
	// 0 使用服务器默认分钟数
	// 1 ... 15为合法取值(一般可能的取值为1,2,3,4,5,10,15)
	GeneralSortData		m_prptData[1];	// 数据		
};

#define Market_SrvCheckError			0x1000   // 登陆验证服务器失败
#define Market_SrvLoad					0x0800   // 需要服务器返回负载信息,参见结构：TestSrvLoadData
#define Market_SrvInfo					0x2000   // 服务器返回信息,参见结构：TestSrvInfoData

struct TestSrvLoadData
{
	long		m_lTotalCount;		// 已连接过的总数
	long		m_nMaxCount;		// 允许的最大连接数
	long		m_nCheckDelay;		// 认证登陆使用时间
	long		m_nCheckErrors;		// 认证登陆失败错误次数
	long		m_nCpu;				// cpu情况
	long		m_nMemory;			// 内存使用情况

	TestSrvLoadData()
	{
		memset(this,0,sizeof(TestSrvLoadData));
	}
};
struct TestSrvInfoData
{
	unsigned long	m_lSrvDate;			// 服务器当前日期，格式为YYYYMMDDhh
	unsigned long	m_lSrvTime;			// 服务器当前时间，格式为hhmmss
	unsigned long	m_lReserve[2];		// 保留
};


/*
主推：
功能：
完成服务器端向客户端推送数据，
有请求主推（即有请求才主推）和固定主推（即服务器自动发送的，如指数）。

规则：
1、所有请求主推都返回，当请求主推的股票个数为0时，则服务器删除此次主推。
2、主机实时发送的数据，只适用于指数。
*/

/*
说明: 常用主推  （在客户端适用于所有页面）
类型: RT_AUTOPUSH

说明: 请求主推，目前用于预警
类型: RT_REQAUTOPUSH 
*/
/*返回结构*/
struct AnsHSAutoPushData
{
	DataHead	 m_dhHead;				// 数据报头

	long		 m_nSize;				// 数据个数
	CommRealTimeData m_pstData[1];	// 主机实时发送的数据
};

// RT_SERVERTIME说明 BEGIN
// 说明：请求服务器时间
// 类型：RT_SERVERTIME
// 请求结构: 常用请求:AskData
// 返回结构
struct AnsServerTime
{
	DataHead				m_dhHead;		// 数据报头
	int						m_nDateTime;	// 当前时间(time_t,从1970/1/1 0:0:0开始的秒计数)
};
// RT_SERVERTIME说明 END

// RT_KEEPACTIVE说明 BEGIN
// 说明：保活通信
// 类型：RT_KEEPACTIVE
// 请求结构:
struct ReqKeepActive
{
	unsigned short m_nType;			 // 请求类型，与请求数据包一致

	char			m_nIndex;     	 // 请求索引，与请求数据包一致
	char			m_cOperator;   	 // 操作（0：清空 1:不清空)
};
// 返回结构
struct AnsKeepActive
{
	unsigned short  m_nType;			// 请求类型，与请求数据包一致
	char			m_nIndex;     	 // 请求索引，与请求数据包一致
	char			m_cOperator;   	 // 操作（0：清空 1:不清空)
	int			    m_nDateTime;		// 当前时间(time_t,从1970/1/1 0:0:0开始的秒计数)
};
/*
说明:
1。服务器收到RT_KEEPACTIVE请求时，如果应答缓冲区中有返回数据，则可不处理此包，不用返回。
2。服务器收到此包时，不可按通用请求的方式处理，即收到此请求时不清应答或请求缓冲区。
*/
// RT_KEEPACTIVE说明 END


//RT_TESTSRV	0x0905	/* 测试客户端到服务器是否通畅 */
typedef unsigned long  SessionID ;
struct ReqSrvSync
{
	SessionID    client_sessionId ;
};

struct AnsSrvSync
{
	DataHead	m_dhHead;
	int        session_stat;
	SessionID  srv_sessionid ;

} ;

struct TestSrvData
{
	unsigned short m_nType;				// 请求类型，与请求数据包一致
	char		   m_nIndex;     		// 请求索引，与请求数据包一致
	char		   m_cOperator;   		// 操作（0：清空 1:不清空)

	TestSrvData()
	{
		m_nType = RT_TESTSRV;
		m_nIndex = 0;
		m_cOperator = 0;
	}
};


// RT_TEST说明 BEGIN
// 说明：测试通信包
// 类型：RT_TEST
// 请求结构:
struct ReqTest
{
	unsigned short m_nType;				// 请求类型，与请求数据包一致
	char		   m_nIndex;     		// 请求索引，与请求数据包一致
	char		   m_cOperator;   		// 操作（0：清空 1:不清空)
	long		   m_nSize;				// 数据长度
	long 		   m_nCSendTick;		// 客户端请求开始发送时间
	long		   m_nCReceiveTick;		// 客户端接收完返回包时间
	char		   m_szData[1];			// 请求数据包
};
// 返回结构:
struct AnsTest
{
	unsigned short m_nType;				// 请求类型，与请求数据包一致
	char		   m_nIndex;     		// 请求索引，与请求数据包一致
	char		   m_cOperator;   		// 操作（0：清空 1:不清空)
	long		   m_nSize;				// 数据长度
	long 		   m_nCSendTick;		// 客户端请求开始发送时间
	long		   m_nCReceiveTick;		// 客户端接收完返回包时间

	long		   m_nSReceiveTick;		// 服务器端收完请求时间
	long		   m_nSBeginCalcTick;	// 服务器端开始计算时间
	long		   m_nSEndCalcTick;		// 服务器端计算完成时间
	long		   m_nSSendTick;		// 服务器端开始发包时间

	char		   m_szData[1];			// 返回数据包
};
/*
说明:
1。所有时间均以毫秒为单位
2。m_szData可能指向所有类型的请求/应答（主推除处）数据包
*/
// RT_TEST说明 END

/*
请求类型: RT_CURRENTFINANCEDATA
功能说明: 最新的财务数据
*/
/* 请求结构 */
struct ReqCurrentFinanceData
{
	long 	m_lLastDate;	//最新日期

};
/* 返回结构 */
struct CurrentFinanceData
{
	CodeInfo		m_ciStockCode;	 	// 股票代码	
	int	   			m_nDate;		 	// 日期
	float   		m_fFinanceData[39]; // 数据项
};

/*港股财务数据结构 内部使用 不是从服务器返回的结构*/
/*货币单位都是港币*/
struct HKCurrentFinanceData
{
	CodeInfo        m_ciStockCode;       		// 股票代码
	int             m_nData;             		// 财务文件报告日期
	double          m_dPaidUpShares;     		// 股本(百万)
	int             m_nPaidUpSharesUnit; 		// 股本单位
	double          m_dEPSTTM;           		// 每股收益TTM
	double          m_dDividendParShare; 		// 每股股息
	double          m_dNaps;             		// 每股净资产
	double          m_dDividendYield;    		// 股息率
	double          m_dShareHolderEquity;		// 净资产
	int             m_nShareHolderEquityUnit;   // 净资产单位
};

// 分析家财务数据结构
struct FxjCaiWu
{
	char   cType[2];
	char   cUnknow[2];
	char   cCode[6];
	float  fCwdata[39];
	char   cNext[1];
};

struct AnsCurrentFinance
{
	DataHead				m_dhHead;			//数据报头

	short            		m_nSize;			//后续数据个数
	short 	        		m_nAlignment;		//为了4字节对齐而添加的字段
	CurrentFinanceData      m_sFinanceData[1]; // 财务数据
};

// 除权数据文件代码信息
struct HSExRight 
{
	CodeInfo	m_CodeInfo;
	long 		m_lLastDate;	//最新日期
	long	    m_lCount;		//参考使用
};
// 除权数据文件结构
struct HSExRightItemInFile
{
	unsigned long  m_nTime;			// 时间
	float 	m_fGivingStock;		// 送股
	float 	m_fPlacingStock;	// 配股
	float 	m_fGivingPrice;		// 送股价
	float 	m_fBonus;			// 分红
};


// 除权数据结构
struct HSExRightItem
{
	HSExRightItem(HSExRightItemInFile* pItemInFile = NULL)
	{
		if ( pItemInFile )
		{
			m_nTime = pItemInFile->m_nTime;
			m_fGivingStock  = pItemInFile->m_fGivingStock;
			m_fPlacingStock = pItemInFile->m_fPlacingStock;
			m_fGivingPrice  = pItemInFile->m_fGivingPrice;
			m_fBonus = pItemInFile->m_fBonus;
			m_fRatioAdjustingFactor = 0.0;
		}
		else
		{
			m_nTime = 0;
			m_fGivingStock  = 0.0;
			m_fPlacingStock = 0.0;
			m_fGivingPrice  = 0.0;
			m_fBonus = 0.0;
			m_fRatioAdjustingFactor = 0.0;
		}
	}
	unsigned long  m_nTime;			 // 时间
	float 	m_fGivingStock;		     // 送股
	float 	m_fPlacingStock;	     // 配股
	float 	m_fGivingPrice;		     // 送股价
	float 	m_fBonus;			     // 分红
	float   m_fRatioAdjustingFactor; // 复权因子
};

// 分析家除权数据结构
struct FxjChuQuan
{
	char   cCode[8];
	int	   nUnknow[2];
	char   cNext[1];
};
/*
struct FxjChuQuanDataItem
{
	unsigned long   nTime;//--2010.11.12 litao修正2012时间问题
	float fSg;
	float fPg;
	float fPgPrice;
	float fGive;
};*/
/* 返回结构 - 除权*/
struct CurrentExRightData
{
private:
	char*			m_pszRightData;
	int				m_nDataLen;
public:
	/*	struct
	{
		CodeInfo		m_ciStockCode;	 	// 股票代码	
		long			m_lCount;			//item项
		char			m_cData[1];			//数据内容 -- 结构是HSExRightItem
	};*/

	CurrentExRightData()
	{
		m_pszRightData = NULL;
		m_nDataLen = 0;
	}

	BOOL Init(int nLen)
	{
		Release();
		m_pszRightData = (char*)malloc(nLen);
		if (m_pszRightData != NULL)
		{
			m_nDataLen = nLen;
			memset(m_pszRightData, 0, nLen);
			return TRUE;
		}
		return FALSE;
	}

	BOOL Copy(CurrentExRightData* pExrightData)
	{
		if ( pExrightData )
		{
			pExrightData->Release();
			if ( m_nDataLen )
			{
				pExrightData->Init(m_nDataLen);
				memcpy(pExrightData->m_pszRightData, m_pszRightData, m_nDataLen);
			}
			return TRUE;
		}
		return FALSE;
	}

	void SetCode(CodeInfo* pCode)
	{
		if (m_pszRightData)
		{
			memcpy(m_pszRightData, pCode, sizeof(CodeInfo));
		}
	}

	CodeInfo* GetCode()
	{
		return (CodeInfo*)m_pszRightData;
	}

	void SetCount(long lCount)
	{
		if (m_pszRightData)
		{
			long* pCount =  (long*)(m_pszRightData + sizeof(CodeInfo));
			*pCount = lCount;
		}		
	}

	long GetCount()
	{
		if (m_pszRightData != NULL)
		{
			long* pCount =  (long*)(m_pszRightData + sizeof(CodeInfo));
			return *pCount;
		}
		return 0;
	}

	void SetExRightDataItem(HSExRightItem* pItem, int nItemIndex)
	{
		if (m_pszRightData)
		{
			HSExRightItem* pItemSet = (HSExRightItem*)(m_pszRightData + sizeof(CodeInfo) + sizeof(long));
			pItemSet += nItemIndex;
			memcpy(pItemSet, pItem, sizeof(HSExRightItem));

			CTime tm = CTime(time_t(pItemSet->m_nTime));
			long lTime = tm.GetYear() * 10000 + tm.GetMonth() * 100 + tm.GetDay();
			pItemSet->m_nTime = lTime;
		}
	}

	HSExRightItem* GetExRightDataItem(int nItemIndex)
	{
		if (m_pszRightData != NULL)
		{
			HSExRightItem* pItemGet = (HSExRightItem*)(m_pszRightData + sizeof(CodeInfo) + sizeof(long));
			pItemGet += nItemIndex;
			return pItemGet;
		}
		return NULL;
	}

	void Release()
	{
		if (m_pszRightData)
		{
			free(m_pszRightData);
			m_pszRightData = NULL;
		}
	}
};
/*
请求类型: RT_HISFINANCEDATA
功能说明: 历史财务数据
请求结构: 常用请求:AskData
*/
/*返回结构*/
struct HisFinanceData
{
	int		m_nDate;		  // 日期
	float   m_fFinanceData[39];  // 数据项
};

struct AnsHisFinance
{
	DataHead		m_dhHead;		//数据报头

	short           m_nSize;			//后续数据个数
	short 	        m_nAlignment;	//为了4字节对齐而添加的字段
	HisFinanceData  m_sFinanceData[1]; // 财务数据
};

/*请求类型:RT_EXRIGHT_DATA
功能:除权数据增量传输
*/
// 请求结构：
struct ReqExRightData
{
	long 	m_lLastDate;	//最新日期
};

// 返回结构：
struct AnsExRightData
{
	DataHead		m_dhHead;		//数据报头
	long           	m_nSize;		//后续数据流长度
	char        	m_cData[1]; 	//除权数据流，格式同文件，参见：除权文件结构
};

// 外汇实时数据
struct HSWHRealTime 
{
	long		m_lOpen;         	// 今开盘(1/10000元)
	long		m_lMaxPrice;     	// 最高价(1/10000元)
	long		m_lMinPrice;     	// 最低价(1/10000元)
	long		m_lNewPrice;     	// 最新价(1/10000元)

	long		m_lBuyPrice;		// 买价(1/10000元)
	long		m_lSellPrice;		// 卖价(1/10000元)

	//long		m_lPrevClose;	    // 昨天收盘
	//long		m_lPriceTimes;	    // 跳动量，一分钟价格变化次数

	void To(char cIntelToComputer )
	{
	}
};

// 历史分时走势数据
struct StockHistoryTrendHead 
{
	long				m_lDate;		// 日期
	long				m_lPrevClose;	// 昨收

	union
	{
		HSStockRealTime			m_stStockData;		// 个股实时基本数据
		HSIndexRealTime			m_stIndexData;		// 指数实时基本数据
		HSHKStockRealTime		m_hkData;		// 港股实时基本数据
		HSQHRealTime			m_qhData;		// 期货实时基本数据
		HSWHRealTime			m_whData;		// 外汇实时基本数据
	};

	short			    m_nSize;		//  每天数据总个数
	short				m_nAlignment;   //  对齐用

	void To(char cIntelToComputer )
	{
	}
};

//历史分时1分钟数据
struct StockCompHistoryData
{
	long	m_lNewPrice;		// 最新价
	unsigned long	m_lTotal;			/* 成交量 //对于股票(单位:股)
										对于指数(单位:百股) */
	float	m_fAvgPrice;		/*成交金额 */
	long	m_lBuyCount;        // 委买量
	long	m_lSellCount;       // 委卖量

	void To(char cIntelToComputer)
	{
	}
};

/*请求结构*/
struct ReqHisTrend
{
	CodeInfo	 m_ciStockCode;	// 股票代码
	long         m_lDate; 		// 日期 见RT_HISTREND说明1

	void To(char cIntelToComputer )
	{
	}
};

/*
RT_HISTREND说明1:
m_lDate：
如为正数则指具体日期,格式如20030701
如为负数则倒推m_lDate天数的当天分时走势（如-10则返回倒数第10天的）
如等于0,为当天
*/
struct HisTrendData
{
	StockHistoryTrendHead	m_shHead;		// 历史分时走势数据(2004年6月23日 改动处 结构不同）
	StockCompHistoryData	m_shData[1];	// 分钟历史数据

	void To(char cIntelToComputer )
	{

	}
}; 

/*返回结构*/
struct AnsHisTrend
{
	DataHead			m_dhHead;	// 数据报头
	HisTrendData		m_shTend;	// 分时数据

	void To(char cIntelToComputer )
	{
	}
};

/*
请求类型: RT_TECHDATA / RT_TECHDATA_EX
功能说明: 盘后分析
*/

/*请求结构*/
struct ReqDayData 	
{
	short				m_nPeriodNum;		// 周期长度,服务器不用
	unsigned short		m_nSize;			// 本地数据当前已经读取数据起始个数,服务器不用
	long				m_lBeginPosition;	// 起始个数，-1 表示当前位置。 （服务器端已经返回的个数）
	unsigned short		m_nDay;				// 申请的个数
	short				m_cPeriod;			// 周期类型
	CodeInfo			m_ciCode;			// 申请的股票代码

	void To(char cIntelToComputer )
	{
	}
};

struct DateRange
{
	unsigned long m_nBeginDate;
	unsigned long m_nEndDate;
};

struct ReqRangeDayData: public ReqDayData	
{
	long                     m_nDataRangCount;          // m_dataRange数组个数
	DateRange                m_dataRange[1];
};

/* 返回结构 */
// 针对RT_TECHDATA请求返回
struct StockCompDayData
{
	unsigned long	m_lDate;		// 日期
	long	m_lOpenPrice;	// 开
	long	m_lMaxPrice;	// 高
	long	m_lMinPrice;	// 低
	long	m_lClosePrice;	// 收
	long	m_lMoney;		// 成交金额
	unsigned long	m_lTotal;		// 成交量

};
struct AnsDayData
{
	DataHead			m_dhHead;			//数据头

	long				m_nSize;			//日线数据个数	
	//short 			    m_nAlignment;  	 	//为了4字节对齐而添加的字段
	StockCompDayData	m_sdData[1];		//日线数据
};

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
	void To(char cIntelToComputer )
	{
	}
};

// 针对RT_TECHDATA_EX请求返回

struct StockCompDayDataExBig
{
	unsigned long m_lDate;      // 日期
	long m_lOpenPrice;   		// 开
	long m_lMaxPrice;    		// 高
	long m_lMinPrice;    		// 低
	long m_lClosePrice;  		// 收
	float        m_lMoney;      // 成交金额
	float        m_lTotal;      // 成交量 
	long m_lNationalDebtRatio;  // 国债利率(单位为0.1分),基金净值(单位为0.1分), 无意义时，须将其设为0 2004年2月26日加入
	void To(char cIntelToComputer )
	{
	}
};

struct AnsDayDataEx 
{
	DataHead			m_dhHead;			//数据头

	long				m_nSize;			//日线数据个数	
	//short 			    m_nAlignment;  	 	//为了4字节对齐而添加的字段
	StockCompDayDataEx	m_sdData[1];		//日线数据

	void To(char cIntelToComputer )
	{
	}
};

struct StockCompDayDataBigInt
{
	unsigned long   m_lDate;       		// 日期
	long    m_lOpenPrice;   			// 开
	long    m_lMaxPrice;    			// 高
	long    m_lMinPrice;    			// 低
	long    m_lClosePrice;  			// 收
	INT64   m_lMoney;       			// 成交金额 单位：千元(在期货市场下，该字段存放的是持仓量)
	INT64   m_lTotal;       			// 成交量	单位：手
	long    m_lNationalDebtRatio; 		// 国债利率(单位为0.1分),基金净值(单位为0.1分), 无意义时，须将其设为0
										// 期货市场下是结算价
};

struct AnsDayDataBigInt
{
	DataHead            	m_dhHead;			// 数据头
	long						m_nSize;		// K线数据个数
	StockCompDayDataBigInt 	m_sdData[1];		// K线数据
};


/*请求结构：常用请求AskData */
struct PriceVolItem_Ext
{
	unsigned short		m_cSize;		// 结构体长度
	unsigned short		m_nVersion;		// 版本号
	long			    m_lNewPrice;	// 最新价
	unsigned long		m_lTotal;		// 成交量(在外汇时，是跳动量)

	long				m_lExt1;		// ETF时，为其IOPV值（例如510050时为510051的最新价），期权的时候存放持仓量
	long				m_lStopFlag;	// 停盘标志。0：正常，1：停盘
};
/*
请求类型: RT_TREND
功能说明: 分时走势
备	  注: 
*/
/*请求结构：常用请求AskData */
/* 价量数据项 */
struct PriceVolItem
{
	long			    m_lNewPrice;	// 最新价
	unsigned long		m_lTotal;		// 成交量(在外汇时，是跳动量)
};
/*返回结构*/
struct AnsTrendData
{
	DataHead		    m_dhHead;		// 数据报头
	short				m_nHisLen;		// 分时数据个数
	short 			    m_nAlignment;	// 为了4字节对齐而添加的字段
	StockOtherData		m_othData;		// 实时其它数据
	//HSStockRealTime		m_nowData;		// 实时基本数据
	union
	{
		HSStockRealTime			m_nowData;		// 个股实时基本数据
		HSIndexRealTime			m_indData;		// 指数实时基本数据
		HSHKStockRealTime		m_hkData;		// 港股实时基本数据
		HSQHRealTime			m_qhData;		// 期货实时基本数据
		HSWHRealTime			m_whData;		// 外汇实时基本数据
	};
	PriceVolItem		m_pHisData[1];	// 历史分时数据

};

/*返回结构*/
struct AnsTrendData_Ext
{
	DataHead		    m_dhHead;		// 数据报头
	short				m_nHisLen;		// 分时数据个数
	short 			    m_nAlignment;	// 为了4字节对齐而添加的字段
	StockOtherData		m_othData;		// 实时其它数据
	//HSStockRealTime		m_nowData;		// 实时基本数据
	union
	{
		HSStockRealTime_Ext		m_nowDataExt;	// 个股实时基本数据
		HSIndexRealTime			m_indData;		// 指数实时基本数据
		HSHKStockRealTime		m_hkData;		// 港股实时基本数据
		HSQHRealTime			m_qhData;		// 期货实时基本数据
		HSWHRealTime			m_whData;		// 外汇实时基本数据
		HSSpotRealTime			m_spotData;		// 商品实时基本数据
		HSOPTRealTime           m_optionData;   // 期权实时基本数据
	};
	PriceVolItem_Ext		m_pHisData[1];	// 历史分时数据
};

/*
请求类型: RT_TICK
功能说明: TICK图
*/
/* 请求结构：常用请求AskData */
/* 返回结构 */
struct AnsTick
{
	DataHead			m_dhHead;		// 数据报头
	StockOtherData		m_othData;		// 实时其它数据
	//HSStockRealTime		m_nowData;		// 实时基本数据
	union
	{
		HSStockRealTime			m_nowData;		// 个股实时基本数据
		HSIndexRealTime			m_indData;		// 指数实时基本数据
		HSHKStockRealTime		m_hkData;		// 港股实时基本数据
		HSQHRealTime			m_qhData;		// 期货实时基本数据
		HSWHRealTime			m_whData;		// 外汇实时基本数据
		HSOPTRealTime           m_optionData;   // 期权实时基本数据
	};

	long				m_nSize;		// 分笔成交数据
	//short 		    	m_nAlignment;   // 为了4字节对齐而添加的字段
	StockTick			m_traData[1];	// 分笔成交数据 个数
};

/*  
请求类型: RT_LIMITTICK
功能说明: 指定长度的分笔请求
*/
//请求结构：
struct ReqLimitTick
{
	CodeInfo     m_pCode;		// 代码
	short        m_nCount;		// 需要返回的长度
	short 		 m_nAlignment;  // 为了4字节对齐而添加的字段
};

/*
请求类型: RT_STOCKTICK
功能说明: 个股分笔、个股详细的分笔数据
*/
//请求结构：常用请求 AskData
//返回结构：个股分笔返回包
struct AnsStockTick
{
	DataHead	m_dhHead;		// 数据报头
	long		m_nSize;		// 数据个数
	//short 		m_nAlignment;   // 为了4字节对齐而添加的字段
	StockTick	m_traData[1];	// 分笔数据
};

/*
请求类型: RT_MAJORINDEXTICK
功能说明: 大盘明细
请求结构：常用请求 AskData
*/
//返回结构：
struct MajorIndexItem
{
	long			m_lNewPrice;		// 最新价（指数）
	unsigned long	m_lTotal;			// 成交量
	float			m_fAvgPrice;		// 成交额

	short	m_nRiseCount;		// 上涨家数
	short	m_nFallCount;		// 下跌家数
};

struct AnsMajorIndexTick	
{
	DataHead			m_dhHead;			// 数据报头

	short				m_nSize;			// 数据个数
	short 	  		   	m_nAlignment;		// 为了4字节对齐而添加的字段
	MajorIndexItem	    m_ntrData[1];		// 大盘一分钟成交明细
};


/*
请求类型: RT_LEAD
功能说明: 大盘领先指标
请求结构: 常用请求AskData
*/
//返回结构：
struct StockLeadData
{
	long			m_lNewPrice;	// 最新价(指数)
	unsigned long	m_lTotal;		// 成交量

	short	m_nLead;		// 领先指标
	short	m_nRiseTrend;	// 上涨趋势
	short	m_nFallTrend;	// 下跌趋势
	short 	m_nAlignment;   // 为了4字节对齐而添加的字段

	void To(char cIntelToComputer )
	{

	}
};
struct AnsLeadData  
{
	DataHead		m_dhHead;		// 数据头
	HSIndexRealTime	m_indData;		// 指数实时数据

	short			m_nHisLen;		// 领先数据个数
	short 			m_nAlignment;   // 为了4字节对齐而添加的字段
	StockLeadData	m_pHisData[1];	// 领先数据

	void To(char cIntelToComputer )
	{
	}
};

/*请求类型: 	RT_VALUE
功能:请求与应答显示于客户端右小图“值”的数据(股票)
*/
// 请求结构：常用请求
// 返回结构：
struct AnsValueData
{
	DataHead		m_dhHead;			// 数据报头

	long			m_nTime;			// 时间，距离开盘分钟数
	unsigned long	m_lTotal;			// 总手
	float			m_fAvgPrice;		// 总金额
	long			m_lNewPrice;		// 最新价
	//long			m_lPreMaxPrice;		// 昨日最高价
	//long			m_lPreMinPrice;		// 昨日最低价
	long			m_lTickCount;		// 成交笔数	

	union
	{
		struct
		{
			long 			m_lMa10;			// 10天，20天，50天收盘均价
			long 			m_lMa20;
			long 			m_lMa50;
			long 			m_lMonthMax;		// 月最高最低
			long 			m_lMonthMin;		
			long 			m_lYearMax;			// 年最高最低
			long 			m_lYearMin;
			long			m_lHisAmplitude;	// 历史波幅(使用时除1000为百分比数）
		};
		CalcData_Share m_Share;
	};

	void To(char cIntelToComputer )
	{
	}
};

//////////////////////////////////////////////////////////////////////////
// Level2数据结构
// 各股票Level2其他数据
struct LevelStockOtherData
{
	union
	{
		unsigned long					 m_nTimeOld;	  // 现在时间	
		unsigned short					 m_nTime;		  // 现在时间	
		StockOtherDataDetailTime		 m_sDetailTime;
	};

	unsigned long  m_lCurrent;    // 现在总手

	unsigned long  m_lOutside;    // 外盘
	unsigned long  m_lInside;     // 内盘

	union
	{
		unsigned long  m_lKaiCang;    // 今开仓,深交所股票单笔成交数,港股交易宗数
		unsigned long  m_lPreClose;   // 对于外汇时，昨收盘数据		
	};

	union
	{
		unsigned long  m_rate_status; // 对于外汇时，报价状态
		// 对于股票，信息状态标志,
		// MAKELONG(MAKEWORD(nStatus1,nStatus2),MAKEWORD(nStatus3,nStatus4))
		unsigned long  m_lPingCang;   // 今平仓
	};
};

struct RealTimeDataLevel
{	
	CodeInfo			m_ciStockCode;		// 代码
	LevelStockOtherData	m_othData;			// 实时其它数据
	LevelRealTime		m_sLevelRealTime;	// 

	// 根据代码得到下一个位置ptr
	RealTimeDataLevel* GetNext(CodeInfo* pCode,int& nNowSize,int* pTotal = NULL,int nFixSize = 0)
	{
		if( pCode == NULL )
			return this;

		if( nFixSize != 0 )
			nNowSize = nFixSize;
		else
		{
			nNowSize = sizeof(RealTimeDataLevel);
			if( nNowSize == 0 )
				return this;
		}
		if( pTotal )
			*pTotal += nNowSize;

		char* pp = (char*)this;
		pp += nNowSize;

		return (RealTimeDataLevel*)pp;
	}
};

// level主推
struct AnsHSAutoPushLevel
{
	DataHead			 m_dhHead;			// 数据报头

	long				 m_nSize;			// 数据个数
	RealTimeDataLevel	 m_pstData[1];		// 主机实时发送的数据

	void To(char cIntelToComputer )
	{

	}
};


//逐笔成交 查询请求
struct ReqLevelTransaction
{
	CodeInfo 	m_Codeinfo;
	int			m_nSize;
	int			m_nPostion;
};

// 逐笔成交查询返回包
struct AnsLevelTick
{
	DataHead				m_dhHead;		// 数据头
	long					m_nSize;			// 返回代码个数
	HSLevelTransaction		m_Data[1];
};

// 逐笔成交结构
struct LevelTransactionData
{
	CodeInfo			m_CodeInfo;			// 代码
	long          m_nSize;
	HSLevelTransaction	m_Data[1];			// 逐笔成交数据
};

// 逐笔成交订阅返回包
struct AnsHsLevelTransactionAuto
{
	DataHead				m_dhHead;		// 数据头
	long					m_nSize;			// 返回代码个数
	LevelTransactionData	m_Data[1];			// 逐笔成交数据数据 
};


// 买卖队列请求
struct ReqOrderQueue
{
	CodeInfo	m_CodeInfo;		// 代码
	int/*char*/		m_direct;		// 1为买，2为卖
};

// 买卖队列查询返回包
struct AnsQueryOrderQueue
{
	DataHead		  m_dhHead;	// 数据头
	HSLevelOrderQueue	  m_pstData[1];		// 数据 
};

struct HSOrderQueueData
{
	CodeInfo			m_CodeInfo;		// 代码
	HSLevelOrderQueue	m_Data[1];		// 数据
};
// 最佳盘口数据主推应答包，在DataHead里有消息号进行区分
struct AnsHsLevelOrderQueue
{
	DataHead		  m_dhHead;	// 数据头
	long			  m_nSize;			// 买卖方向
	HSOrderQueueData	  m_pstData[1];		// 数据 
};

/*
请求类型: RT_TOTAL
功能说明: 总持
备	  注: 
*/
/*请求结构：常用请求AskData */
/* 总持数据项 */
struct TotalItem
{
	unsigned long		m_nTotal;		// 总持
};
/*返回结构*/
struct AnsTotalData
{
	DataHead		    m_dhHead;		// 数据报头
	short				m_nHisLen;		// 分时数据个数
	short 			    m_nAlignment;	// 为了4字节对齐而添加的字段
	TotalItem			m_pHisData[1];	// 总持数据
};


// 期货买卖盘数据
struct QHMaiMaiRealTime 
{
	long                m_lBuyPrice1;       // 买一价
	unsigned long       m_lBuyCount1;       // 买一量
	long                m_lBuyPrice2;       // 买二价
	unsigned long       m_lBuyCount2;       // 买二量
	long                m_lBuyPrice3;       // 买三价
	unsigned long       m_lBuyCount3;       // 买三量
	long                m_lBuyPrice4;       // 买四价
	unsigned long       m_lBuyCount4;       // 买四量
	long                m_lBuyPrice5;       // 买五价
	unsigned long       m_lBuyCount5;       // 买五量

	long                m_lSellPrice1;       // 卖一价
	unsigned long       m_lSellCount1;       // 卖一量
	long                m_lSellPrice2;       // 卖二价
	unsigned long       m_lSellCount2;       // 卖二量
	long                m_lSellPrice3;       // 卖三价
	unsigned long       m_lSellCount3;       // 卖三量
	long                m_lSellPrice4;       // 卖四价
	unsigned long       m_lSellCount4;       // 卖四量
	long                m_lSellPrice5;       // 卖五价
	unsigned long       m_lSellCount5;       // 卖五量

};


struct RealTimeDataQHMaiMai
{	
	CodeInfo            m_ciStockCode;        // 代码
	QHMaiMaiRealTime    m_sQHMaiMaiRealTime;  // 期货买卖盘数据
};

// 期货买卖盘主推
struct AnsHSAutoPushQHMaiMai
{
	DataHead			 m_dhHead;			// 数据报头

	long				 m_nSize;			// 数据个数
	RealTimeDataQHMaiMai m_pstData[1];		// 主机实时发送的数据
};




/* 期货套利代码数据 */
struct ZMQHArbCodeInfo
{
	HSMarketDataType	m_cCodeType;		// 证券类型	futu_exch_type[2];//交易类别
	char				m_strCode[81];				// 合约代码	
	char				firstLeg_code[40];			//第一腿
	char				secondLeg_code[40];			//第二腿
};
/* 期货套利时时数据 */
struct HSQhArbRealTime
{	
	long    arbi_type;				//组合类型1-SPD, 2 -IPS  
	float	buy_price;				//最高买入价
	long	buy_amount;				//最高买入价买量 
	long	buy_total_amount;		//全部买量 
	float	sale_price;				//最低卖价价格
	long	sale_amount;			//最低卖价卖量 
	long	sale_total_amount;		//全部卖量 
	float	futu_high_price;		//最高价
	float	futu_low_price;			//最低价
	float	uplimited_price;		//涨停板价格
	float	downlimited_price;		//跌停板价格
};

struct AnsArbRealTime 
{
	ZMQHArbCodeInfo m_ciQhCode;		//套利代码
	HSQhArbRealTime m_rtRealTime;   //套利时时数据
};

/** 按行情列ID查询行情字段值请求结构
 *  功能号 RT_HQCOL_VALUE 0x0216
 */
#define MAX_HQCOL_COUNT (8)
struct ReqHQColValue
{
	unsigned long	m_lHQColCount;					// 有效字段的个数
	unsigned long	m_lHQCols[MAX_HQCOL_COUNT];		// 请求字段数据，内容同排序字段行情列定义
	unsigned short	m_lCodeSize;					// 请求的证券代码总数
	unsigned short	m_nReserved;					// 保留
	CodeInfo		m_pCode[1];						// 证券代码数组
};

/** 按行情列ID查询行情字段值应答结构
 *  功能号 RT_HQCOL_VALUE 0x0216
 */

// 返回行情值宽度的定义，客户端缺省用无符号类型解析，如果业务类型是有符号的，就按具体业务处理；以前的float字段类型用64位来返回
struct HQColField
{
	unsigned long	m_lField;						// 行情列ID
	unsigned short	m_lFieldWidth;					// 行情列的值的宽度，目前可选4或8，分别对应32位和64位
	unsigned short	m_nSortPrecision;				// 表示放大10的多少次方。如成交金额等字段排序不需要放大，则置为0，但各市场还在按原来金额放大的值去处理。
};
 
struct AnsHQColValue
{
	DataHead		m_dhHead;						// 数据头
	unsigned long	m_lHQColCount;					// 有效字段的个数
	HQColField		m_HQColFields[MAX_HQCOL_COUNT];	// 请求字段数据，内容同排序字段行情列定义
	unsigned short	m_lCodeSize;					// 证券代码总数
	unsigned short	m_nReserved;					// 保留
	char			m_pData[1];						// 返回指定字段数据。
													// 格式为CodeInfo + m_lFieldSize个行情字段(对应字段的宽度为m_ColFields.m_lFieldWidth)，
													// 如果该值不存在，该值填0，以保证每个代码的数据长度一致
													// 每个证券代码的数据格式大小为:
													// sizeof(CodeInfo) + m_lFieldSize个字段的长度之和，
													// 其中每个字段的长度为m_ColFields[i].m_lFieldWidth，i为当前列的下标
};

/** 按市场排序协议请求结构
 *  功能号：RT_MARKETSORT 0x0217
 */
struct ReqMarketSort
{
	int					m_nColID;					// 排名列id 
	short				m_nBegin;					// 显示开始
	short				m_nCount; 					// 显示个数
	char				m_bAscending;				// 升序/降序
	char				m_nAlignment;				// 为了4字节对齐而添加的字段
	short				m_nSize;			 		// 市场个数
	HSMarketDataType	m_sAnyReportData[1];		// 市场列表 
};


/** 按市场排序协议返回结构
 *  功能号：RT_MARKETSORT 0x0217
 */
struct AnsMarketSort 
{
	DataHead				m_dhHead;					// 数据头
	int						m_nColID;					// 排名列id 
	short					m_nSize;					// 数据个数
	short 					m_nAlignment;				// 为了4字节对齐而添加的字段
	CommRealTimeData_Ext 	m_pData[1];					// 数据	
};

/** 退市板块请求结构
 *  功能号: RT_ASSIST_QUERY 0x0218
 */
struct  ReqAssist
{
	unsigned short 	m_nMarketType;			// 市场类别，只关心高8位。如0x1100, 0x1200
	unsigned short  m_nReserved;				// 保留
	unsigned int	m_nCRC;					// 服务端下传的CRC值。首次为0。
};

/** 退市板块返回结构
 *  功能号: RT_ASSIST_QUERY 0x0218
 */

struct AssistCodeData
{
	CodeInfo m_cCodeInfo;   //代码信息
	UINT     m_nExpireDate; //到期日

	AssistCodeData()
	{
		memset(&m_cCodeInfo,0,sizeof(CodeInfo));
		m_nExpireDate = 0;
	}
};

struct AssistBlockData
{
    char        m_szName[32];          //分类名（不包含’\0’）
    char        m_cBlockType;          //分类方法（目前有警示、整理2个板块）
    char        m_cFilterFlag;         //是否需要过滤代码（排序中过滤，这个行为可以与blocktype关联）
    char        m_cUplimitRate;        //*100 （涨停板限制）
    char        m_cDownlimitRate;      //*100 （跌停板限制）
    unsigned short m_nCodeCount;       //代码个数
    short       m_nReserve;            //保留字段
    AssistCodeData m_stCodeData[1];    //代码组
};

struct AnsAssistData
{
	DataHead        m_dhHead;
	UINT            m_nDate;           //交易日(YYYYMMDD)
	UINT            m_nCrc;            //crc32（这个CRC与初始化代码表没有关联，只是这个附件分类的CRC）
	HSMarketDataType m_nMarketType;    //市场类型
	unsigned short  m_nBlockCount;     //分类数（重复组）
	AssistBlockData m_stBlockData[1];   //分类组
};

// 订阅请求
struct MarketMonitor
{
	unsigned short		m_nMarketType;
};

struct ReqMarketMonitor
{
	unsigned short		m_nMktCount;	// 成功订阅市场的个数
	unsigned short		m_nReserved;	// 保留
	MarketMonitor		m_sMarkets[1];	// 成功订阅的市场列表
};


// 订阅应答
struct AnsMarketMonitor
{
	DataHead 			m_dhHead;
	unsigned short		m_nMktCount;	// 支持市场的个数
	unsigned short		m_nReserved;	// 保留
	MarketMonitor		m_sMarkets[1];	// 返回支持的市场列表
};

// 事件结构
struct MarketEvent
{
	unsigned short		m_nEventID;		// 监控类别ID，用来对应格式串
	unsigned short		m_nReserved;	// 保留
	unsigned int		m_nTime;		// 事件时间hhmmss(客户端目前不展示秒)
	CodeInfo			m_CodeInfo;		// 代码信息
	char				m_cDirection;	// 方向：1 正，0 平，-1 负。用来对应提示信息的颜色
	unsigned char		m_cValueCount;	// 有效值的个数(取值为: 0, 1, 2)
	char				m_cValue1Scale;	// 值1缩放10的多少次方
	char				m_cValue2Scale;	// 值2缩放10的多少次方
	int					m_nValue1;		// 值1
	int					m_nValue2;		// 值2
};

// 主推应答
struct AnsMarketEvent
{
	DataHead 			m_dhHead;
	unsigned int		m_nDate;		// 日期yyyymmdd
	unsigned int		m_nSize;		// MarketEvent的个数
	MarketEvent			m_MarketEvents[1];
};

// 请求某支股票当天的短线精灵事件，功能号为：RT_MARKET_MONITOR_STOCK_QUERY
// 应答结构同RT_MARKET_MONITOR_AUTOPUSH，为AnsMarketEvent

/** 请求某支股票当天的短线精灵事件请求结构
 *  功能号：RT_MARKET_MONITOR_STOCK_QUERY 0x0908
 */
struct ReqStockMarketEvent
{
	CodeInfo			m_CodeInfo;		// 代码信息
	unsigned int 		m_nOffset;		// 正序的偏移
	unsigned int		m_nCount;		// 请求的事件个数
};


// 请求订阅成功的所有市场一天的短线精灵事件
// 应答结构同RT_MARKET_MONITOR_AUTOPUSH，为AnsMarketEvent，当返回条件小于请求条件时，说明请求完了

/** 短线精灵事件按日期查询请求结构
 *  功能号：RT_MARKET_MONITOR_DATE_QUERY 0x0909
 */
struct ReqDateMarketEvent
{
	unsigned int 		m_nDate;		// 日期yyyymmdd
	unsigned int 		m_nOffset;		// 逆序的偏移
	unsigned int		m_nCount;		// 请求的事件个数
	unsigned short		m_nMktCount;	// 需要查询市场的个数
	unsigned short		m_nReserved;	// 保留
	MarketMonitor		m_sMarkets[1];	// 需要查询的市场列表
};

/**
*请求集合竞价的方式类似请求分笔（RT_TICK）；请求集合竞价的功能号为0x030E（RT_VIRTUAL_AUCTION）。请求为AskData
*下面是应答包结构
*/
struct StockVirtualAuction 
{
	long m_lTime;		//虚拟匹配的时间，格式为hhmmssxxx
	long m_lPrice;		//虚拟匹配价格
	float m_fQty;		//虚拟匹配量
	float m_fQtyLeft;	//虚拟未匹配量；如果为正数，表示委买的未匹配量；如果为负数，表示委卖的未匹配量
};

struct AnsVirtualAuction
{
	DataHead			m_dhHead;		// 数据报头
	long				m_nSize;		// 虚拟竞价匹配的次数，如果该股票没有匹配，则，该值为0；
	StockVirtualAuction	m_vaData[1];	// 每次虚拟竞价的详细信息
};

/** 文交所动态竞价报价结构
 *  RT_DYNAUCTION_REALTIME 0x0219
 */
struct DynAuctionRealTimeData
{
	CodeInfo				m_ciStockCode;			// 股票代码
	UINT64					m_lNewPrice;			// 最新价格
	UINT64					m_lListPrice;			// 挂牌价格
	unsigned long			m_lMarginRatio;			// 保证金比例, 放大了10的8次方倍
	unsigned long			m_lDefaultRatio;		// 违约金比例, 放大了10的8次方倍
	unsigned long			m_lListDate;			// 挂牌日期, yyyymmdd
	UINT64					m_lValidListingTime;	// 包括日期的挂牌有效时间, yyyymmddhhmmss
	UINT64					m_lCompleteEndTime;		// 包括日期的补款截止时间, yyyymmddhhmmss
	UINT64					m_lLatestTime;			// 包括日期的最新报价时间, yyyymmddhhmmss
};

/** 文交所动态竞价报价应答结构
 *  RT_DYNAUCTION_REALTIME 0x0219
 */
struct AnsDynAuctionRealTime
{
	DataHead				m_dhHead;				// 数据报头
	unsigned long			m_lTime;				// 当前时间, hhmmss
	unsigned short			m_nSize;				// 报价表数据个数
	unsigned short			m_nReserved;			// 保留字段
	DynAuctionRealTimeData	m_pData[1];				// 报价表数据
};

/** 文交所动态竞价TICK请求结构
 *  RT_DYNAUCTION_TICK 0x021A
 */
struct ReqDynAuctionTick
{
	CodeInfo				m_ciStockCode;			// 股票代码
	unsigned short			m_nOffset;				// 逆序的偏移，0表示最新的一个TICK
	unsigned short			m_nCount;				// 请求Tick的个数
};

/** 文交所动态竞价TICK结构
 *  RT_DYNAUCTION_TICK 0x021A
 */
struct DynAuctionTick
{
	unsigned long			m_lDate;				// yyyymmdd
	unsigned long			m_lTime;				// hhmmss
	UINT64					m_lPrice;				// 最新价
};

/** 文交所动态竞价TICK应答结构
 *  RT_DYNAUCTION_TICK 0x021A
 */
struct AnsDynAuctionTick
{
	DataHead				m_dhHead;				// 数据报头
	unsigned short			m_nSize;				// TICK数据个数
	unsigned short			m_nReserved;			// 保留字段
	DynAuctionTick			m_pData[1];				// TICK数据
};

/** 武汉光谷定价交易实时结构
 *  RT_FIXED_PRICE_REALTIME 0x021C
 */
struct FixedPriceRealtimeData
{
	CodeInfo				m_ciStockCode;			// 股票代码
	UINT64					m_lNewPrice;			// 最新价
	UINT64					m_lMaxPrice;			// 最高报价
	UINT64					m_lListPrice;			// 挂牌价格
	UINT64					m_lListVolume;			// 挂牌数量
	UINT64					m_lMaxVolume;			// 最高数量
	UINT64					m_lTotalDeclareVolume;	// 申报总量
	UINT64					m_lValidListingTime;	// 包括日期的挂牌有效时间, yyyymmddhhmmss
	unsigned long			m_lMinDealRatio;		// 最小成交比例, 放大了10的8次方倍
	char					m_cDealMode;			// 成交方向。字符'1'代表数量优先；'2'代表价格优先
	union 
	{
		char data[15];
	} m_reserved;
};

struct AnsFixedPriceRealTime
{
	DataHead				m_dhHead;				// 数据报头
	unsigned long			m_lTime;				// 当前时间, hhmmss
	unsigned short			m_nSize;				// 报价表数据个数
	unsigned short			m_nStructSize;			// 表示m_pData字段所使用结构的大小
	FixedPriceRealtimeData	m_pData[1];				// 报价表数据
};

#pragma	pack()