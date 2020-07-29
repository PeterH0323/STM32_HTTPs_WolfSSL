/*-----------------------------------------------------------
 * Includes files
 *----------------------------------------------------------*/

/* segger rtt includes. */
#include "SEGGER_RTT.h"
#include "SEGGER_RTT_Conf.h"

#define BUFFER_INDEX 0

/*!
* @brief 封装 RTT 打印接口
*        执行条件：无
*
* @retval: 无
*/
void print_log(const char * sFormat, ...)
{	
	va_list ParamList;
	va_start(ParamList, sFormat);
	SEGGER_RTT_vprintf(BUFFER_INDEX, sFormat, &ParamList);
	va_end(ParamList);
}

/*!
* @brief 初始化 RTT 打印接口
*        执行条件：无
*
* @retval: 无
*/
void segger_rtt_init(char * str)
{
	SEGGER_RTT_Init();
	print_log("==================================\n");
	print_log("==================================\n");
	print_log("========= %s =========\n",str);  // 封装接口，无需填写 BUFFER_INDEX
	print_log("==================================\n");
	print_log("==================================\n");
}

