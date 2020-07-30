/*-----------------------------------------------------------
 * Includes files
 *----------------------------------------------------------*/

/* bsp includes. */
#include "FreeRTOS.h"
#include "timers.h"

/* bsp includes. */
#include "lwip/dhcp.h"
#include "lwip/dns.h"
//#include "lwip/apps/netbiosns.h"

/* bsp includes. */
#include "bsp_printlog.h"

// 最大 DHCP 次数，设置一个 大点的值
#define MAX_DHCP_COUNT (50000)

/*!
* @brief 封装 dhcp 接口
*        执行条件：无
*
* @retval: 无
*/
err_t bsp_dhcp(void)
{
    struct dhcp *dhcp;
	uint32_t over_time = 0;
	
	struct netif *netif_p = netif_default;
	
	if(netif_p == NULL)
	{
		return ERR_VAL;
	}
//    netif->hostname = "THOSTP";

    /* Start DHCP negotiation for a network interface (IPv4) */
//    dhcp_start(netif);

	//设置计算机名 (测试方法: (1)ping 计算机名 (2)用浏览器访问 http://计算机名/)
//	netbiosns_init();
//	netbiosns_set_name(netif->hostname);

	// 外部定义了 netif_default
    while(!dhcp_supplied_address(netif_p))
    {
		over_time++;
        print_log("dhcp_connect: DHCP discovering... for %d times\r\n", over_time);
		
		if(over_time > MAX_DHCP_COUNT)
		{
			print_log("dhcp_connect: overtime, not doing dhcp\r\n");
			return ERR_TIMEOUT;
		}
        vTaskDelay(pdMS_TO_TICKS(500));
    }

    dhcp = netif_dhcp_data(netif_p);
    print_log("DHCP IP address: %s\n", ip4addr_ntoa(&dhcp->offered_ip_addr));
    print_log("DHCP Subnet mask: %s\n", ip4addr_ntoa(&dhcp->offered_sn_mask));
    print_log("DHCP Default gateway: %s\n", ip4addr_ntoa(&dhcp->offered_gw_addr));

#if LWIP_DNS
    print_log("DHCP DNS Server: %s\n", ip4addr_ntoa(dns_getserver(0)));

	#ifdef DNS_SERVER_ADDRESS
	  /* initialize default DNS server address */
	  ip_addr_t dnsserver;
	  DNS_SERVER_ADDRESS(&dnsserver);
	  dns_setserver(0, &dnsserver);
	#endif /* DNS_SERVER_ADDRESS */

    print_log("after set DHCP DNS Server: %s\n", ip4addr_ntoa(dns_getserver(0)));
#endif

    print_log("dhcp_connect: DHCP success\r\n");

	return ERR_OK;
}

