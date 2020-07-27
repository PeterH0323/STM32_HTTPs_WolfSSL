/*-----------------------------------------------------------
 * Includes files
 *----------------------------------------------------------*/

/* FreeRTOS includes. */
#include "FreeRTOS.h"

/* lwip includes. */
#include "lwip.h"
#include "lwip/api.h"

/* wolfssl includes. */
#include <wolfssl/ssl.h>
#include <wolfssl/internal.h>


/* bsp includes. */
#include "bsp_wolfssl.h"

// 需要访问的服务器的 CA 证书，
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

static const size_t __ssl_root_certificate_len = sizeof(__ssl_root_certificate);



/*!
* @brief 重写 wolfssl 的时间获取函数
*        执行条件：无
*
* @retval: 返回时间戳
*/
time_t XTIME(time_t * timer)
{
	time_t timestamp = 1595856796; // 没有实现 SNTP，先使用网上获取的最新时间的时间戳
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
	HTTPS_HTTPS_WRITE_FAIL = -8,
	HTTPS_HTTPS_READ_FAIL = -9,
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


/* GET request header*/
#define HTTPS_GET_API 	"GET /callback?cmd=1059&callback=phone&phone=15900000000 HTTP/1.1\r\n" /* HOST, host-port, URI */\
								"User-Agent: wolfssl_https_demo\r\n" /* User-Agent */ \
								"Accept: */*\r\n" \
								"Host: www.baifubao.com\r\n" /* server name */ \
								"Connection: Close\r\n" /* we don't support persistent connections, yet */ \
								"\r\n"

//#define HTTPS_GET_API_FORMAT(req_uri, host_name) HTTPS_GET_API, req_uri, host_name

/*!
* @brief 测试 wolfssl https 拉取淘宝https接口
*        执行条件：无
*
* @retval: 拉取状态
*/
int test_https(void)
{
	char URL[] = "https://www.baifubao.com/callback?cmd=1059&callback=phone&phone=15900000000";
//	char request_buffer[126] = "/callback?cmd=1059&callback=phone&phone=15900000000";
	
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
//	ip_addr_t server_ip ;
//	char host_name[] = "www.baifubao.com";
//	netconn_gethostbyname(host_name, &server_ip);
//	if(server_ip.addr == 0)
//	{
//        return HTTPS_CA_LOAD_FAIL;
//	}

	ip_addr_t server_ip ;
	ip4_addr_set_u32(&server_ip, ipaddr_addr("180.97.34.159"));
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
	char http_head[] = HTTPS_GET_API;
	if (wolfSSL_write(ssl, HTTPS_GET_API, strlen(http_head)) != strlen(http_head))
	{
		return HTTPS_HTTPS_WRITE_FAIL;
	}

	//==================================================================	
	//接收
	char __https_recv_buffer[2048] = {0x00};
	int recv_len = 0;
	if ((recv_len = wolfSSL_read(ssl, __https_recv_buffer, sizeof(__https_recv_buffer))) <= 0)
	{
		return HTTPS_HTTPS_READ_FAIL;
	}
	
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
