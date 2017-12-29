#include "framework.h"

int ServerBase::SendAndRecvUdpPkg(const char *ip, uint16_t port, void *send_buff, uint32_t send_len,
                      void *recv_buff, uint32_t &recv_len)
{
    if(send_buff == NULL || recv_buff == NULL || send_len <= 0 || recv_len <= 0)
    {
        printf("invalid parma\n");
        return -1;
    }
    sockaddr_in addr;
    bzero(&addr, sizeof(sockaddr_in));
    addr.sin_port = htons(port);
    addr.sin_family = AF_INET;
    if( 0 == inet_aton(ip, &addr.sin_addr))
    {
        return -2;
    }

    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(fd < 0)
    {
        return -3;
    }

    struct sockaddr_in server_addr;

    socklen_t len = sizeof(addr);
    int n = 0;
    if(send_len != (n = sendto(fd, send_buff, send_len, 0, (sockaddr *)&addr, len)))
    {
        return -5;
    }

    printf("client: sendto succ\n");

    if(-1 == (recv_len = recvfrom(fd, recv_buff, recv_len, 0, NULL, NULL)))
    {
        printf("client:recv failed\n");
        return -4;
    }
    return 0;
}

int ServerBase::tcpdemo(const char *ip, uint16_t port)
{
	sockaddr_in addr;

	bzero(&addr, sizeof(sockaddr_in));
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;
	if( 0 == inet_aton(ip, &(addr.sin_addr)))
	{
		return -1;
	}


	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if(fd < 0)
	{
		return -2;
	}

	return 0;
}

int ServerBase::Init(const char *ip, uint16_t port)
{
    sockaddr_in addr;

    bzero(&addr, sizeof(sockaddr_in));
    addr.sin_port = htons(port);
    addr.sin_family = AF_INET;
    if( 0 == inet_aton(ip, &addr.sin_addr))
    {
        return -1;
    }

    m_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(m_fd < 0)
    {
        return -2;
    }

    if(-1 == bind(m_fd, (struct sockaddr *)&addr, sizeof(addr)))
    {
        printf("error:%d,%s", errno, strerror(errno));
        return -3;
    }
    return 0;
}

int ServerBase::Start()
{
    char buff[64];
    bzero(buff, sizeof(buff));

    int n = 0;

    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);
    while(true)
    {
        if((n = recvfrom(m_fd, buff, sizeof(buff), 0, (sockaddr *)&client_addr, &len)) == -1)
        {
            return -4;
        }
        callback(m_fd, &client_addr, (void *)buff, n);
    }
}

void DemoServer::callback(int fd, struct sockaddr_in *addr, void *pkg, uint32_t len)
{
    char *p = (char *)pkg;
    printf("test:%d,%s\n", len, p);
    static int count = 0;
//    printf("%d recv:%s,%d\n", i, buff, n);
    sleep(1);
    int n;
    char buff[1024*64] = {0};
    snprintf(buff, sizeof(buff), "%d:%s", count++, p);
    if(-1 == (n = sendto(fd, buff, strlen(buff)+1, 0, (sockaddr *)addr, sizeof(sockaddr_in))))
    {
        printf("error:%d,%s", errno, strerror(errno));
        //	return -5;
    }

    printf("send back succ,%d\n", n);
    return;
}
