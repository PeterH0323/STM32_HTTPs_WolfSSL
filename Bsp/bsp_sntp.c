/*-----------------------------------------------------------
 * Includes files
 *----------------------------------------------------------*/

/* arm lib includes. */
#include <time.h>

/* stm32 lib includes. */
#include "rtc.h"

/* lwip includes. */
#include "lwip/apps/sntp.h"

/* segger rtt includes. */
#include "bsp_printlog.h"

/*!
 * @brief 获取当前时间戳
 *
 * @param [in] none
 *
 * @retval 当前时间戳
 */
uint32_t get_timestamp(void)
{
    struct tm stm;
    static RTC_DateTypeDef g_Date = {0};
    static RTC_TimeTypeDef g_Time = {0};

    ///获取时间必须在获取日期前
    HAL_RTC_GetTime(&hrtc, &g_Time, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, &g_Date, RTC_FORMAT_BIN);

    stm.tm_year = g_Date.Year + 100;    //RTC_Year rang 0-99,but tm_year since 1900
    stm.tm_mon = g_Date.Month - 1;      //RTC_Month rang 1-12,but tm_mon rang 0-11
    stm.tm_mday = g_Date.Date;          //RTC_Date rang 1-31 and tm_mday rang 1-31

    stm.tm_hour = g_Time.Hours;         //RTC_Hours rang 0-23 and tm_hour rang 0-23
    stm.tm_min = g_Time.Minutes;        //RTC_Minutes rang 0-59 and tm_min rang 0-59
    stm.tm_sec = g_Time.Seconds;

	return (mktime(&stm) - (8 * 60 * 60));///配置时由于东八区增加8小时，现为时间戳，需减去
}

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
		print_log("sntp_set_time: wrong!@@\n");
		return;
	}
	
	print_log("sntp_set_time: c00, enter!\n");
	print_log("sntp_set_time: c01, get time = %u\n", sntp_time);

	struct tm *time;
	RTC_TimeTypeDef sTime = {0};
	RTC_DateTypeDef sDate = {0};

	sntp_time += (8 * 60 * 60); ///北京时间是东8区需偏移8小时

	time = localtime(&sntp_time);

	/*
	 * Initialize RTC and set the Time and Date
	 */
	sTime.Hours = time->tm_hour;
	sTime.Minutes = time->tm_min;
	sTime.Seconds = time->tm_sec;
	sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	sTime.StoreOperation = RTC_STOREOPERATION_RESET;
	if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
	{
		Error_Handler();
	}
	sDate.WeekDay = time->tm_wday;
	sDate.Month = (time->tm_mon) + 1;
	sDate.Date = time->tm_mday;
	sDate.Year = (time->tm_year) + 1900 - 2000;

	if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
	{
		Error_Handler();
	}

	print_log("sntp_set_time: c02, decode time: 20%d-%02d-%02d %d:%d:%d\n", sDate.Year, sDate.Month, sDate.Date, sTime.Hours, sTime.Minutes, sTime.Seconds);
	
	print_log("sntp_set_time: c03, test get = %u\n", get_timestamp());
	print_log("sntp_set_time: c04, set rtc time done\n");
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
