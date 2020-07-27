/*-----------------------------------------------------------
 * Includes files
 *----------------------------------------------------------*/

/* FreeRTOS includes. */
#include "FreeRTOS.h"

/* wolfssl includes. */
#include <wolfssl/ssl.h>
#include <wolfssl/internal.h>

/*!
* @brief 重写 wolfssl 的时间获取函数
*        执行条件：无
*
* @retval: 返回时间戳
*/
time_t XTIME(time_t * timer)
{
	time_t timestamp = 1595836376; // 没有实现 SNTP，先使用网上获取的最新时间的时间戳
	return timestamp;
}

