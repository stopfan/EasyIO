#include "api/api.h"
static void recv_weichat(const char *from , const char *msg , int(*relpy)(char *msg))
{
	SerialPrintf("recv we chat msg : %s \n",msg);
	relpy("msg");
}
static void recv_xmpp(char *from , char *msg)
{
	SerialPrintf("recv xmpp msg : %s %s  \n",from,msg);
	//xmpp_send_msg(from,msg);
}
static void recv_sms(const char *num , const unsigned char *body)
{
	SerialPrintf("RECV SMS FOMR : %s , %s\n",num,body);
	if (SendSms("13821783003",body) != EI_OK)
		SerialPrintf("Send sms Error \n");
}

static void recv_tcp_data(unsigned char * buffer , int size)
{

	
	SerialPrintf("RECV TCP DATA : %s\n",buffer);
	SerialPrintf("RECV END\n");
	WriteSerial(buffer,size);
	SendTcpData(buffer,size);
	//
}

void InitBoard()
{
	//
}

void  Startup()
{
	//
	struct DtuOption opt;
	RecvWeChat = recv_weichat;
	RecvXmppMsg = recv_xmpp;
	RecvSms = recv_sms;
	RecvTcpData = recv_tcp_data;

	snprintf(opt.host,sizeof(opt.host),"%s","liud-home.f3322.org");
	snprintf(opt.port,sizeof(opt.port),"%s","5000");
	snprintf(opt.heartbeat_buffer,sizeof(opt.heartbeat_buffer),"%s","Hello EasyIO \n");
	opt.heartbeat_len = strlen(opt.heartbeat_buffer);
	opt.heartbeat_cycle = 60;
	SerialPrintf("init Dtu res %d \n",InitDtu(&opt));
	InitEasyIOCloud();

	SerialPrintf("ÖÐÎÄ¶ÌÐÅ.chinese\n");

}

void MainLoop()
{
	char *buffer = EI_MALLOC(128);
	int len = 0;
	while(1)
	{
		//Tprintf("Mainloop\n");
		memset(buffer,0x0,128);
		len = ReadSerial(buffer,128,10);
		if (len > 0)
		{
			SerialPrintf("RecvSerualBuffer : %s\n",buffer);
			SendTcpData(buffer,len);
		}
	}
}

