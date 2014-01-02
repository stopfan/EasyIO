/**
* @file                 api_type.h
* @brief                结构体类型
* @details		
* @author               stopfan
* @date         2013-11-11
* @version      A001
* @par Copyright (c): 
*               新动力科技
* @par History:         
*       version: stopfan, 2013-12-12, desc\n
*/

#ifndef __api_type_h__
#define __api_type_h__

#define EIResult_t int

struct SerialOption {
	int Baud;				/**< 串口波特率		*/
	int StopBits;				/**< 串口停止位		*/
	int Parityl;				/**< 串口校验 1或0	*/
};

struct DtuOption {
	char host[64];				/**< 目的服务器IP或域名	*/
	char port[8];				/**< 目的服务器端口	*/
	int heartbeat_cycle;			/**< 心跳周期，单位秒	*/
	char heartbeat_buffer[32];		/**< 心跳内容		*/
	int heartbeat_len;			/**< 心跳内容长度	*/
};

struct XmppOption {
	char username[32];				/**< 即时通讯服务器用户名	*/
	char password[32];				/**< 即时通讯服务器用户密码	*/
	char domain[64];				/**< 即时通讯服务器域		*/
	char port[8];					/**< 即时通讯服务器端口		*/
	char host[64];					/**< 即时通讯服务器主机地址	*/
};

struct SysInfo {
	unsigned int uptime;				/**< 模块运行时间，单位：秒	*/
	unsigned int totalmem;				/**< 动态内存总量		*/
	unsigned int freemem;				/**< 可用内存总量		*/
	unsigned int usemem;				/**< 已用内存			*/
};

typedef enum {
	SYSEVENT_TCP_DISCONNECT,		/**< TCP连接断开事件	*/
	SYSEVENT_TCP_CONNECTED,			/**< TCP连接成功事件	*/
	SYSEVENT_XMPP_DISCONNECT,		/**< XMPP连接断开事件	*/
	SYSEVENT_XMPP_CONNECTED,		/**< XMPP连接成功事件	*/
	SYSEVENT_NULL
}SYSEVENT;

typedef enum {
	EI_ADC0,
	EI_ADC1,
	EI_ADC_NULL
}ADC_PORT;

#endif
