/*-----------------------------------------------------------
 * Includes files
 *----------------------------------------------------------*/

/* lwip includes. */
#include "lwip/apps/sntp.h"

/* segger rtt includes. */
#include "bsp_printlog.h"

/*!
* @brief SNTP 获取时间戳的处理函数
*        执行条件：无
*
* @param [in] : sntp 获取的时间戳
*
* @retval: 无
*/
void sntp_set_time(uint32_t sntp_time)
{
	if(sntp_time == 0)
	{
		print_log("sntp_set_time wrong!@@\n");
		return;
	}
	
	print_log("sntp_set_time enter!\n");
	print_log("get time = %u\n", sntp_time);
	
}


/*!
* @brief 设置 SNTP 的服务器地址
*        执行条件：无
*
* @retval: 无
*/
void set_sntp_server_list(void)
{
	uint32_t server_list[SNTP_MAX_SERVERS] =	{  
													0x279148D2,  //国家授时中心
													0x42041876,
													0x5F066CCA,
													0x0B6C1978,
													0x0B0C5CB6,
													0x58066BCB,
													0x14731978,
													0xC51F70CA,
													0x521D70CA,
													0x820176CA,
													0x510176CA,
												};
	ip_addr_t sntp_server;
												
	for(int i = 0; i < SNTP_MAX_SERVERS; i++)
	{
		sntp_server.addr = server_list[i];
		sntp_setserver(i, &sntp_server);  // 国家授时中心
	}
}

/*!
* @brief Lwip 的 SNTP 初始化封装接口
*        执行条件：无
*
* @retval: 无
*/
void bsp_sntp_init(void)
{
	//设置 SNTP 的获取方式 -> 使用向服务器获取方式
	sntp_setoperatingmode(SNTP_OPMODE_POLL);
	
	//SNTP 初始化
	sntp_init();
	
	//加入授时中心的IP信息
	set_sntp_server_list();
}
