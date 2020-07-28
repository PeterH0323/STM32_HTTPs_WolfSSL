/*-----------------------------------------------------------
 * Includes files
 *----------------------------------------------------------*/

/* FreeRTOS includes. */
#include "FreeRTOS.h"

/* lwip includes. */
#include "lwip.h"
#include "lwip/api.h"
#include "lwip/dns.h"

/* wolfssl includes. */
#include <wolfssl/ssl.h>
#include <wolfssl/internal.h>


/* bsp includes. */
#include "bsp_wolfssl.h"

// 需要访问的服务器的 CA 证书

#define USE_BAIDU_TEST // 直接使用 百度 接口测试，返回的网页需要使用 debug 去看， Segger 无法打印

#ifdef USE_BAIDU_TEST
static const unsigned char __ssl_root_certificate[] =
"-----BEGIN CERTIFICATE-----"
"MIIKLjCCCRagAwIBAgIMclh4Nm6fVugdQYhIMA0GCSqGSIb3DQEBCwUAMGYxCzAJ"
"BgNVBAYTAkJFMRkwFwYDVQQKExBHbG9iYWxTaWduIG52LXNhMTwwOgYDVQQDEzNH"
"bG9iYWxTaWduIE9yZ2FuaXphdGlvbiBWYWxpZGF0aW9uIENBIC0gU0hBMjU2IC0g"
"RzIwHhcNMjAwNDAyMDcwNDU4WhcNMjEwNzI2MDUzMTAyWjCBpzELMAkGA1UEBhMC"
"Q04xEDAOBgNVBAgTB2JlaWppbmcxEDAOBgNVBAcTB2JlaWppbmcxJTAjBgNVBAsT"
"HHNlcnZpY2Ugb3BlcmF0aW9uIGRlcGFydG1lbnQxOTA3BgNVBAoTMEJlaWppbmcg"
"QmFpZHUgTmV0Y29tIFNjaWVuY2UgVGVjaG5vbG9neSBDby4sIEx0ZDESMBAGA1UE"
"AxMJYmFpZHUuY29tMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAwamw"
"rkca0lfrHRUfblyy5PgLINvqAN8p/6RriSZLnyMv7FewirhGQCp+vNxaRZdPrUEO"
"vCCGSwxdVSFH4jE8V6fsmUfrRw1y18gWVHXv00URD0vOYHpGXCh0ro4bvthwZnuo"
"k0ko0qN2lFXefCfyD/eYDK2G2sau/Z/w2YEympfjIe4EkpbkeBHlxBAOEDF6Speg"
"68ebxNqJN6nDN9dWsX9Sx9kmCtavOBaxbftzebFoeQOQ64h7jEiRmFGlB5SGpXhG"
"eY9Ym+k1Wafxe1cxCpDPJM4NJOeSsmrp5pY3Crh8hy900lzoSwpfZhinQYbPJqYI"
"jqVJF5JTs5Glz1OwMQIDAQABo4IGmDCCBpQwDgYDVR0PAQH/BAQDAgWgMIGgBggr"
"BgEFBQcBAQSBkzCBkDBNBggrBgEFBQcwAoZBaHR0cDovL3NlY3VyZS5nbG9iYWxz"
"aWduLmNvbS9jYWNlcnQvZ3Nvcmdhbml6YXRpb252YWxzaGEyZzJyMS5jcnQwPwYI"
"KwYBBQUHMAGGM2h0dHA6Ly9vY3NwMi5nbG9iYWxzaWduLmNvbS9nc29yZ2FuaXph"
"dGlvbnZhbHNoYTJnMjBWBgNVHSAETzBNMEEGCSsGAQQBoDIBFDA0MDIGCCsGAQUF"
"BwIBFiZodHRwczovL3d3dy5nbG9iYWxzaWduLmNvbS9yZXBvc2l0b3J5LzAIBgZn"
"gQwBAgIwCQYDVR0TBAIwADBJBgNVHR8EQjBAMD6gPKA6hjhodHRwOi8vY3JsLmds"
"b2JhbHNpZ24uY29tL2dzL2dzb3JnYW5pemF0aW9udmFsc2hhMmcyLmNybDCCA04G"
"A1UdEQSCA0UwggNBggliYWlkdS5jb22CDGJhaWZ1YmFvLmNvbYIMd3d3LmJhaWR1"
"LmNughB3d3cuYmFpZHUuY29tLmNugg9tY3QueS5udW9taS5jb22CC2Fwb2xsby5h"
"dXRvggZkd3ouY26CCyouYmFpZHUuY29tgg4qLmJhaWZ1YmFvLmNvbYIRKi5iYWlk"
"dXN0YXRpYy5jb22CDiouYmRzdGF0aWMuY29tggsqLmJkaW1nLmNvbYIMKi5oYW8x"
"MjMuY29tggsqLm51b21pLmNvbYINKi5jaHVhbmtlLmNvbYINKi50cnVzdGdvLmNv"
"bYIPKi5iY2UuYmFpZHUuY29tghAqLmV5dW4uYmFpZHUuY29tgg8qLm1hcC5iYWlk"
"dS5jb22CDyoubWJkLmJhaWR1LmNvbYIRKi5mYW55aS5iYWlkdS5jb22CDiouYmFp"
"ZHViY2UuY29tggwqLm1pcGNkbi5jb22CECoubmV3cy5iYWlkdS5jb22CDiouYmFp"
"ZHVwY3MuY29tggwqLmFpcGFnZS5jb22CCyouYWlwYWdlLmNugg0qLmJjZWhvc3Qu"
"Y29tghAqLnNhZmUuYmFpZHUuY29tgg4qLmltLmJhaWR1LmNvbYISKi5iYWlkdWNv"
"bnRlbnQuY29tggsqLmRsbmVsLmNvbYILKi5kbG5lbC5vcmeCEiouZHVlcm9zLmJh"
"aWR1LmNvbYIOKi5zdS5iYWlkdS5jb22CCCouOTEuY29tghIqLmhhbzEyMy5iYWlk"
"dS5jb22CDSouYXBvbGxvLmF1dG+CEioueHVlc2h1LmJhaWR1LmNvbYIRKi5iai5i"
"YWlkdWJjZS5jb22CESouZ3ouYmFpZHViY2UuY29tgg4qLnNtYXJ0YXBwcy5jboIN"
"Ki5iZHRqcmN2LmNvbYIMKi5oYW8yMjIuY29tggwqLmhhb2thbi5jb22CDyoucGFl"
"LmJhaWR1LmNvbYIRKi52ZC5iZHN0YXRpYy5jb22CEmNsaWNrLmhtLmJhaWR1LmNv"
"bYIQbG9nLmhtLmJhaWR1LmNvbYIQY20ucG9zLmJhaWR1LmNvbYIQd24ucG9zLmJh"
"aWR1LmNvbYIUdXBkYXRlLnBhbi5iYWlkdS5jb20wHQYDVR0lBBYwFAYIKwYBBQUH"
"AwEGCCsGAQUFBwMCMB8GA1UdIwQYMBaAFJbeYfG9HBYpUxzAzH07gwBA5hp8MB0G"
"A1UdDgQWBBSeyXnX6VurihbMMo7GmeafIEI1hzCCAX4GCisGAQQB1nkCBAIEggFu"
"BIIBagFoAHYAXNxDkv7mq0VEsV6a1FbmEDf71fpH3KFzlLJe5vbHDsoAAAFxObU8"
"ugAABAMARzBFAiBphmgxIbNZXaPWiUqXRWYLaRST38KecoekKIof5fXmsgIhAMkZ"
"tF8XyKCu/nZll1e9vIlKbW8RrUr/74HpmScVRRsBAHYAb1N2rDHwMRnYmQCkURX/"
"dxUcEdkCwQApBo2yCJo32RMAAAFxObU85AAABAMARzBFAiBURWwwTgXZ+9IV3mhm"
"E0EOzbg901DLRszbLIpafDY/XgIhALsvEGqbBVrpGxhKoTVlz7+GWom8SrfUeHcn"
"4+9Dn7xGAHYA9lyUL9F3MCIUVBgIMJRWjuNNExkzv98MLyALzE7xZOMAAAFxObU8"
"qwAABAMARzBFAiBFBYPxKEdhlf6bqbwxQY7tskgdoFulPxPmdrzS5tNpPwIhAKnK"
"qwzch98lINQYzLAV52+C8GXZPXFZNfhfpM4tQ6xbMA0GCSqGSIb3DQEBCwUAA4IB"
"AQC83ALQ2d6MxeLZ/k3vutEiizRCWYSSMYLVCrxANdsGshNuyM8B8V/A57c0Nzqo"
"CPKfMtX5IICfv9P/bUecdtHL8cfx24MzN+U/GKcA4r3a/k8pRVeHeF9ThQ2zo1xj"
"k/7gJl75koztdqNfOeYiBTbFMnPQzVGqyMMfqKxbJrfZlGAIgYHT9bd6T985IVgz"
"tRVjAoy4IurZenTsWkG7PafJ4kAh6jQaSu1zYEbHljuZ5PXlkhPO9DwW1WIPug6Z"
"rlylLTTYmlW3WETOATi70HYsZN6NACuZ4t1hEO3AsF7lqjdA2HwTN10FX2HuaUvf"
"5OzP+PKupV9VKw8x8mQKU6vr"
"-----END CERTIFICATE-----"
;

#else

// 该证书是接口【https://www.baifubao.com/callback?cmd=1059&callback=phone&phone=15900000000】的证书
static const unsigned char __ssl_root_certificate[] =
"-----BEGIN CERTIFICATE-----"
"MIIGXDCCBUSgAwIBAgIQCsAGQPI+2sCQEaPBeCd8dDANBgkqhkiG9w0BAQsFADBN"
"MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMScwJQYDVQQDEx5E"
"aWdpQ2VydCBTSEEyIFNlY3VyZSBTZXJ2ZXIgQ0EwHhcNMTkxMTE4MDAwMDAwWhcN"
"MjAxMTE4MTIwMDAwWjCBmjELMAkGA1UEBhMCQ04xEDAOBgNVBAgTB0JlaWppbmcx"
"OTA3BgNVBAoTMEJlaUppbmcgQmFpZHUgTmV0Y29tIFNjaWVuY2UgVGVjaG5vbG9n"
"eSBDby4sIEx0ZDElMCMGA1UECxMcc2VydmljZSBvcGVyYXRpb24gZGVwYXJ0bWVu"
"dDEXMBUGA1UEAwwOKi5iYWlmdWJhby5jb20wggEiMA0GCSqGSIb3DQEBAQUAA4IB"
"DwAwggEKAoIBAQCq+PuJJk+KFM0hh3Jj8SzZkJIVM9xFAHeAZQ6nAdYkaegL1NjS"
"rHIchTUhGk3U0ydAPOqFU7t4LMEazUAZ8xPp6GmckkVBzph8GjuUxOJQjoMSEKh4"
"9GSS/PbvXFeNKpQVCKXUP1T+k17FiJY7lf9NKx7hJVls6WbnqLocc2ncppbxmu/2"
"L8NGJw0tPSXiCAIii2M2wS4edlWLumh4xtwOgxTKvCGbVfkX0o+268wnQBiBZUqY"
"lmAuw0luzo1tQiSSAo6+NK9L8SvppWzgVXb/9bX7RBssQaAbE1vyqmmZp+UsTuNJ"
"pUqn4Uh6nv6EEw5AmyUF7+mag1GbbMvyBcKVAgMBAAGjggLoMIIC5DAfBgNVHSME"
"GDAWgBQPgGEcgjFh1S8o541GOLQs4cbZ4jAdBgNVHQ4EFgQU2L6+hxvVYFBVDNUa"
"D2gLrJqUp4MwJwYDVR0RBCAwHoIOKi5iYWlmdWJhby5jb22CDGJhaWZ1YmFvLmNv"
"bTAOBgNVHQ8BAf8EBAMCBaAwHQYDVR0lBBYwFAYIKwYBBQUHAwEGCCsGAQUFBwMC"
"MGsGA1UdHwRkMGIwL6AtoCuGKWh0dHA6Ly9jcmwzLmRpZ2ljZXJ0LmNvbS9zc2Nh"
"LXNoYTItZzYuY3JsMC+gLaArhilodHRwOi8vY3JsNC5kaWdpY2VydC5jb20vc3Nj"
"YS1zaGEyLWc2LmNybDBMBgNVHSAERTBDMDcGCWCGSAGG/WwBATAqMCgGCCsGAQUF"
"BwIBFhxodHRwczovL3d3dy5kaWdpY2VydC5jb20vQ1BTMAgGBmeBDAECAjB8Bggr"
"BgEFBQcBAQRwMG4wJAYIKwYBBQUHMAGGGGh0dHA6Ly9vY3NwLmRpZ2ljZXJ0LmNv"
"bTBGBggrBgEFBQcwAoY6aHR0cDovL2NhY2VydHMuZGlnaWNlcnQuY29tL0RpZ2lD"
"ZXJ0U0hBMlNlY3VyZVNlcnZlckNBLmNydDAJBgNVHRMEAjAAMIIBBAYKKwYBBAHW"
"eQIEAgSB9QSB8gDwAHYApLkJkLQYWBSHuxOizGdwCjw1mAT5G9+443fNDsgN3BAA"
"AAFufW7kQgAABAMARzBFAiEAkFAxrazuXkKJ+lOj6uYh8CSdKHdoifpw6jAOnvOM"
"T+cCICFpj29CI2V9zP9T/0sIPCw0M+Vyy5bqoSpbvZ4YM4pwAHYAXqdz+d9WwOe1"
"Nkh90EngMnqRmgyEoRIShBh1loFxRVgAAAFufW7j7QAABAMARzBFAiAVhzvLuEJ5"
"SymG76frVmV3sLptmofSLBnruiGdyB94/gIhAOAQ+VnmUvR6GnRLGfxCfYJr+kto"
"eZbnRNbV8YvnFu/WMA0GCSqGSIb3DQEBCwUAA4IBAQBBx2szQdx50AdnAJXtzMTo"
"4OiyKW/kZldMPcUkyFz13ekjNnMgFI1FaDmG21pvDaI1yH3Mp9goYV4TQ0eD47t3"
"sS1gFvwjNeS7b6+r5MoOr7x7YS0QfJOi2lkR6wdo3KYROcQfCqtxsPTPAZZQF/qt"
"Jtuc0PvKFv9wdz7XD8NmkHg+H1FL2jigdQHKPPDwdI5SmnHuLS8uQZTHtyymisC6"
"mc/+NeZeWzcLcmTpBUUWWy131gYy8pMSog0n+qrMns1KECJpskQuSeUt/njMUoJo"
"AFQH/VKTirn/wiA6VnyxgvXGfsq1uU/9KDfXE6IWqBw1UsjPT8MktIaPRHCvtdBu"
"-----END CERTIFICATE-----"
;

#endif

static const size_t __ssl_root_certificate_len = sizeof(__ssl_root_certificate);



/*!
* @brief 重写 wolfssl 的时间获取函数
*        执行条件：无
*
* @retval: 返回时间戳
*/
time_t XTIME(time_t * timer)
{
	time_t timestamp = 1595908571; // 没有实现 SNTP，先使用网上获取的最新时间的时间戳
	return timestamp;
}

enum {
	HTTPS_SUCCESS = 0,
	HTTPS_INIT_FAIL = -1,
	HTTPS_CTX_NEW_FAIL = -2,
	HTTPS_CA_LOAD_FAIL = -3,
	HTTPS_DNS_FAIL = -4,
	HTTPS_NOSOCKET = -5,
	HTTPS_SSL_NEW_FAIL = -6,
	HTTPS_SOCKET_SET_FAIL = -7,
	HTTPS_WRITE_FAIL = -8,
	HTTPS_READ_FAIL = -9,
	HTTPS_DNS_IP_FAIL = -10,
};

/*!
* @brief 获取用于 socket 连接的 套接字描述器
*        执行条件：无
*
* @param [in] : family
* @param [in] : type
* @param [in] : protocol
*
* @retval: 用于 socket 连接的 套接字描述器
*/
int https_socket_create(int family, int type, int protocol)
{
	int fd = 0;

	if ((fd = socket(family, type, protocol)) < 0)
    {
		return 1;
    }
	return(fd);
}

/*!
* @brief 将字符串的 ip 转化为 ip类型
*        执行条件：无
*
* @param [in] : family
* @param [in] : strptr ：字符串的 ip
* @param [in] : addrptr ：ip类型
*
* @retval: 无
*/
void https_socket_inet_pton(int family, const char *strptr, void *addrptr)
{
    if ( (NULL == strptr) || (NULL == addrptr) )
    {
		return ;
    }
	int n = 0;

	if ((n = inet_pton(family, strptr, addrptr)) < 0)
    {
		/* errno set */
    }
	else if (n == 0)
    {
		/* errno not set */
    }
	/* nothing to return */
}


/*!
* @brief Socket 连接
*        执行条件：无
*
* @param [in] : Socket 套接字描述器
* @param [in] : sa
* @param [in] : salen
*
* @retval:  0 成功
* @retval: -1 失败
*/
int https_connect_socket(int fd, const struct sockaddr *sa, socklen_t salen)
{
    if ( (NULL == sa) || (NULL == salen) )
    {
		return -1;
    }

	if (connect(fd, sa, salen) < 0)
    {
		return -2;
    }
    
	return 0;
}


/*!
* @brief Socket 关闭
*        执行条件：无
*
* @param [in] : Socket 套接字描述器
*
* @retval:  0 成功
* @retval: -1 失败
*/
int https_close_socket(int fd)
{
	return closesocket(fd);
}

#define TEST_MODE //开启 Debug 信息输出

/* GET request header*/ 
#ifdef USE_BAIDU_TEST

//https://tcc.taobao.com/cc/json/mobile_tel_segment.htm?tel=15900000000
char s__host_name[] = 	"www.baidu.com";

#define HTTPS_GET_API 	"GET / HTTP/1.1\r\n" /* HOST, host-port, URI */\
						"Host: www.baidu.com\r\n" /* server name */ \
						"\r\n"
#else
//https://www.baifubao.com/callback?cmd=1059&callback=phone&phone=15900000000
char s__host_name[] = 	"www.baifubao.com";

#define HTTPS_GET_API 	"GET /callback?cmd=1059&callback=phone&phone=15900000000 HTTP/1.1\r\n"\
						"Host: www.baifubao.com\r\n"\
						"Connection: keep-alive\r\n"\
						"Cache-Control: max-age=0\r\n"\
						"Upgrade-Insecure-Requests: 1\r\n"\
						"User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/84.0.4147.89 Safari/537.36\r\n"\
						"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9\r\n"\
						"Sec-Fetch-Site: none\r\n"\
						"Sec-Fetch-Mode: navigate\r\n"\
						"Sec-Fetch-User: ?1\r\n"\
						"Sec-Fetch-Dest: document\r\n"\
						"Accept-Encoding: gzip, deflate, br\r\n"\
						"Accept-Language: zh-CN,zh;q=0.9\r\n"\
						"Cookie: BAIDUID=37A941C20A35E8388091D42BEE45BF73:FG=1; __bsi=11302079117392493273_00_42_R_R_61_0303_c02f_Y\r\n"\
						"\r\n"
				
#endif

//#define HTTPS_GET_API_FORMAT(req_uri, host_name) HTTPS_GET_API, req_uri, host_name

/*!
* @brief 测试 wolfssl https 拉取淘宝https接口
*        执行条件：无
*
* @retval: 拉取状态
*/
int test_https(void)
{
	print_log("test_https enter \n");
	print_log("system total heap size = %d\n", xPortGetFreeHeapSize());

	
//	char request_buffer[126] = "/callback?cmd=1059&callback=phone&phone=15900000000";
	char http_head[] = HTTPS_GET_API;
	vTaskDelay(3000); // 给时间测试 ping
	
	#ifdef TEST_MODE //开启测试模式，会打印调试信息，需要加入宏定义 DEBUG_WOLFSSL，
		wolfSSL_Debugging_ON();
	#endif

	WOLFSSL_CTX* ctx = NULL;
	
	//创建 wolfssl 需要的空间等配置
    if ( WOLFSSL_SUCCESS != wolfSSL_Init())
    {
        return HTTPS_INIT_FAIL;
    }
	
	//==================================================================
	
	//初始化 结构体 WOLFSSL_CTX 
	if ( (ctx = wolfSSL_CTX_new(wolfTLSv1_2_client_method())) == NULL)
    {
        return HTTPS_CTX_NEW_FAIL;
	}

	//==================================================================

    //加载 CA 证书到 WOLFSSL_CTX 
    if ( wolfSSL_CTX_load_verify_buffer(ctx, (unsigned char *)__ssl_root_certificate, __ssl_root_certificate_len, WOLFSSL_FILETYPE_PEM) != SSL_SUCCESS)
    {
        return HTTPS_CA_LOAD_FAIL;
    }
	
	//==================================================================

	//进行域名解析
	ip_addr_t server_ip ;
	err_t err = ERR_OK;
	err = netconn_gethostbyname(s__host_name, &server_ip);
	if(err != ERR_OK)
	{
        return HTTPS_DNS_IP_FAIL;
	}
	
	if(server_ip.addr == 0)
	{
        return HTTPS_DNS_IP_FAIL;
	}
	
//	ip_addr_t server_ip ;
//	ip4_addr_set_u32(&server_ip, ipaddr_addr("180.97.93.57"));
	//==================================================================
	
	// 进行 socket 连接
	int					sockfd;
	struct sockaddr_in	servaddr;

	sockfd = https_socket_create(AF_INET, SOCK_STREAM, 0);

	memset(&servaddr, sizeof(servaddr), 0);
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(443);
	https_socket_inet_pton(AF_INET, inet_ntoa(server_ip), &servaddr.sin_addr);

	/* Connect to socket file descriptor */
	if (0 != https_connect_socket(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr)))
    {
        return HTTPS_NOSOCKET;
    }

	//==================================================================

	//进行 SSL 的初始化
    WOLFSSL* ssl = NULL;

	wolfSSL_CTX_set_verify(ctx, SSL_VERIFY_NONE, 0);	 // 尝试解决 -188, -155

    if( (ssl = wolfSSL_new(ctx)) == NULL)
	{
        return HTTPS_SSL_NEW_FAIL;
    }

	//==================================================================

	//进行 SSL 和 socket 绑定
	if( WOLFSSL_SUCCESS != wolfSSL_set_fd(ssl, sockfd))
    {
        return HTTPS_SOCKET_SET_FAIL;
    }
	
	//==================================================================	
	//访问
	if (wolfSSL_write(ssl, HTTPS_GET_API, strlen(http_head)) != strlen(http_head))
	{
		return HTTPS_WRITE_FAIL;
	}

	//==================================================================	
	//接收
	char __https_recv_buffer_temp[1024] = {0x00};
	int signal_pack_size = sizeof(__https_recv_buffer_temp);
	
	char __https_recv_buffer[1024 * 12] = {0x00};
	int recv_len = 0;
	int total_recv_len = 0;
	int recv_index = 0;
	int packet_index = 0;
	for(;;)
	{
		recv_len = wolfSSL_read(ssl, __https_recv_buffer_temp, signal_pack_size);
		if(recv_len <= 0)
		{
			break;
		}
		
		packet_index += 1;
		if(packet_index == 1)
		{
			//取第一包，第一包是 http header，里面有 Content-Length: 是表示 body 的长度，
			//header 部分的结束是 \r\n\r\n 为结束
			//计算是否是 < Content-Length 的长度，可以判断是否继续接收
		}

		total_recv_len += recv_len;
		if(total_recv_len >= sizeof(__https_recv_buffer))  // 防止溢出
		{
			print_log("out of buffer !!!!!");
			total_recv_len = recv_index;
			// 重新申请内存， 使用类似 realloc 的方法，此处 demo 直接跳出 
			break;
		}
		
		snprintf(&__https_recv_buffer[recv_index], recv_len, "%s", __https_recv_buffer_temp);
		recv_index += recv_len;
		
//		if(recv_len < signal_pack_size)
//		{
			//这种可用这种方法跳出，存疑
//			print_log("recv_len < signal_pack_size, means recv done!!!!!");
//			break;
//		}
	}
	
	print_log("\n ========== \n\n");
//	print_log("https recv data : recv_len = %d, buffer = \n%s\n",total_recv_len, __https_recv_buffer);
	print_log("https recv data : recv_len = %d, buffer is too big, use software debug [Memory] to vertify\n",total_recv_len);
	print_log("\n ========== \n\n");
	
	//==================================================================
	
	//释放空间
	wolfSSL_free(ssl);             /* Free WOLFSSL object */

	wolfSSL_CTX_free(ctx);         /* Free WOLFSSL_CTX object */

	wolfSSL_Cleanup();             /* Free wolfSSL */

	//==================================================================
	
	//关闭 socket
	https_close_socket(sockfd);
	
	return HTTPS_SUCCESS;
	
}
