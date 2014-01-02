/**
* @file                 api.h
* @brief                EasyIO-GPRS 接口文件
* @details		使用EasyIO Framework 需要引入此头文件，此文件包含了所有功能和方法的API函数和系统的钩子函数
* @author               stopfan
* @date         2013-11-11
* @version      A001
* @par Copyright (c): 
*               新动力科技
* @par History:         
*       version: stopfan, 2013-12-12, desc\n
*/


#ifndef __easy_io_api_h__
#define __easy_io_api_h__

#include "api_type.h"
#include "api_result.h"

#define HOOK			/**< 不具备任何意义，只是作为前缀方面区分函数功能	*/
#define INTERFACE extern	/**< extern 						*/

#define EI_MALLOC rt_malloc 	/**< 定义 EI_MALLOC	*/
#define EI_FREE rt_free		/**< 定义 EI_FREE	*/


/****************************************************************
        EasyIO 功能接口函数
****************************************************************/

/** 读取串口数据
 *
 * @param[in] max : 读取缓冲的长度
 * @param[out] buffer : 存储读出内容的缓冲
 * @param[in] timeout : 超时等待 ，最小时间间隔为百分之一秒
 *
 * @return int 返回读取出的数据长度 -1 为读取错误
 **/
INTERFACE int ReadSerial(unsigned char *buffer , int max , int timeout);

/** 格式化输出字符串到串口
 *
 * @param[in] fmt : 格式化字符串
 *
 * @return
 **/
INTERFACE int SerialPrintf(char *fmt, ...);

/** 将内容写入串口
 *
 * @param[in] buffer : 写入缓冲
 * @param[in] size : 写入长度
 *
 * @return
 **/
INTERFACE EIResult_t WriteSerial(unsigned char *buffer , int size);


/** 读取EEPROM中的内容
 *
 * @param[in] pos : 要读取的位置
 * @param[out] buffer : 存储读出内容的缓冲
 * @param[in] size : 读取长度
 *
 * @return
 **/
INTERFACE EIResult_t ReadEEPROM(int pos , unsigned char *buffer , int size);

/** 将内容写入EEPROM
 *
 * @param[in] pos : 要写入的位置
 * @param[out] buffer : 写入缓冲
 * @param[in] size : 写入长度
 *
 * @return
 **/
INTERFACE EIResult_t WriteEEPROM(int pos , unsigned char *buffer , int size);

/** 获取基站位置信息
 *
 * @return
 **/
INTERFACE EIResult_t GetLocation();

/** 发送短信
 *
 * @param[in] phonenum : 目标手机号码
 * @param[in] body : 发送内容
 *
 * @return
 **/
INTERFACE EIResult_t SendSms(const char *phonenum ,const char *body);

/** 发DTU送数据
 *
 * @param[in] buffer : 发送缓冲
 * @param[in] size : 发送长度
 *
 * @return
 **/
INTERFACE EIResult_t SendTcpData(const char *buffer , int size);

/** 发送P2p消息
 *
 * @param[in] imei : 目的IMEI
 * @param[in] body ：内容
 *
 * @return
 **/
INTERFACE EIResult_t SendP2paMsg(const char *imei , const char *body);

/** 发送XMPP消息
 *
 * @param[in] to : 目的ID
 * @param[in] body ：内容
 *
 * @return
 **/
INTERFACE EIResult_t SendXmppMsg(const char * to , const char *body);

/** 发起HTTP请求，目前仅支持GET请求
 *
 * @param[in] url : 要请求的URL
 * @param[in] Userheader ：用户字定义请求头，一般为 NULL
 * @param[in] RespBuffer : HTTP请求的返回结果保存在此缓冲中
 * @param[in] RespBufSize: HTTP缓冲的大小
 * @return 返回真正获取到的数据长度 返回“0代表”失败
 **/
INTERFACE int HttpRequest(const char *url, const char *UserHeader ,char *RespBuffer , int RespBufSize);


/** 获取系统信息
 *
 * #param[out] info : 输出系统信息结构体
 * @return
 **/
INTERFACE EIResult_t GetSysInfo(struct SysInfo *info);

/** 设备重启 ,执行此函数后，模块和MCU都将重启
 *
 * @return
 **/
INTERFACE EIResult_t ResetSystem();

/** GPRS 模块重启 ,只针对 gprs 模块进行复位重启
 *
 * @return
 **/
INTERFACE EIResult_t ResetGprs();


/****************************************************************
	钩子函数
****************************************************************/

/** 接收到短信的回调函数
 *
 * @param[in] phonenum : 电话号码
 * @param[in] str : 短信内容
 *
 * @return
 **/
extern HOOK void (*RecvSms)(const char *phonenum , const unsigned char *str);

/** 接收到微信的回调函数
 *
 * @param[in] from : 发送者的微信Id
 * @param[in] msg : 信息内容
 * @param[in] relpy : 回复本条微信的函数
 *
 * @return
 **/
extern HOOK void (*RecvWeChat)(const char *from , const char *msg , EIResult_t(*relpy)(char *msg));

/** 接收到Tcp数据的回调函数
 *
 * @param[in] buffer : 数据缓冲
 * @param[in] size : 数据长度
 *
 * @return
 **/
extern HOOK void (*RecvTcpData)(unsigned char * buffer , int size);

/** 接收P2p消息
 *
 * @param[in] imei : 发送者IMEI
 * @param[in] body ：接收内容
 *
 * @return
 **/
extern HOOK void (*RecvP2pMsg)(char *imei , char *msg);

/** 接受XMPP消息的回调函数
 *
 * @param[in] from : 发送者ID
 * @param[in] body ：接收内容
 *
 * @return
 **/
extern HOOK void (*RecvXmppMsg)(char *from , char *body);


/****************************************************************
	初始化函数
****************************************************************/

/** 初始化串口
 *
 * @param[in] option : 串口参数
 *
 * @return
 **/
INTERFACE EIResult_t InitSerial(struct SerialOption *option);

/** 初始化Dtu
 *
 * @param[in] option : Dtu参数
 *
 * @return
 **/
INTERFACE EIResult_t InitDtu(struct DtuOption *option);

/** 初始化Xmpp客户端
 *
 * @param[in] option : Xmpp服务器参数
 *
 * @return
 **/
INTERFACE EIResult_t InitXmpp(struct XmppOption *option);

/** 初始化EasyIO云,初始化此功能后，可使用微信，Web，手机等 设备与设备进行通讯
 *
 * @return
 **/
INTERFACE EIResult_t InitEasyIOCloud();

/****************************************************************
	系统级回调函数
****************************************************************/

/** 硬件初始化
 *
 * @return
 **/
void InitBoard();

/** 启动函数，EasyIO 启动时将调用此函数,系统相关的初始化和回调函数注册需要在这里进行。
 *
 * @return
 **/
void Startup();

/** 主循环,一切从这里开始... | 主循环最大使用的栈空间为1Kbyte 请尽量多的使用(EI_MALLOC/EI_FREE)动态使用内存分配
 *
 * @return
 **/
void MainLoop();

#endif
