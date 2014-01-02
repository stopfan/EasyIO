/**
* @file                 api_result.h
* @brief                API函数返回值描述
* @details		使用EasyIO Framework 需要引入此头文件，此文件包含了所有功能和方法的API函数和系统的钩子函数
* @author               stopfan
* @date         2013-11-11
* @version      A001
* @par Copyright (c): 
*               新动力科技
* @par History:         
*       version: stopfan, 2013-12-12, desc\n
*/


#ifndef __api_resault_h__
#define __api_resault_h__

enum {
	EI_OK = 0,			/**< 成功       */
	EI_ERROR = 1,			/**< 失败       */
	EI_PARAM_ERR,			/**< 输入参数错误	*/
	EI_ALLOC_MEM_ERR,		/**< 内存申请失败	*/
	EI_RINGBUFFER_FULL,		/**< 环形缓冲区满	*/
};



#endif
