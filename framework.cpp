#include "framework.h"

int udpdemo(const char *ip, uint16_t port)
{
	sockaddr_in addr;

	bzero(&addr, sizeof(sockaddr_in));
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;
	if( 0 == inet_aton(ip, &addr.sin_addr))
	{
		return -1;
	}

	int fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(fd < 0)
	{
		return -2;
	}

	if( -1 == bind(fd, (struct sockaddr *)&addr, sizeof(addr)))
	{
		return -3;
	}

	char buff[64];
	bzero(buff, sizeof(buff));

	int n = 0;

	struct sockaddr_in client_addr;
//	socklen_t len = sizeof(client_addr);
    socklen_t len;
	for(int i = 0; i<200000000; i++)
	{
        printf("%d before %d", i, len);
		if((n = recvfrom(fd, buff, sizeof(buff), 0, (sockaddr *)&client_addr, &len)) == -1)
		{
			return -4;
		}
        printf("%d after %d", i, len);
		// buff[1023]=0;
		printf("%d recv:%s,%d\n", i, buff, n);
        sleep(1);
		if(-1 == (n = sendto(fd, buff, n, 0, (sockaddr *)&client_addr, len)))
		{
            printf("error:%d,%s", errno, strerror(errno));
		//	return -5;
		}

		printf("%d send back succ,%d\n", i,n);
	}
	
	return 0;
}

int tcpdemo(const char *ip, uint16_t port)
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

int udpclient(const char *ip, uint16_t port)
{
	sockaddr_in addr;

	bzero(&addr, sizeof(sockaddr_in));
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;
	if( 0 == inet_aton(ip, &addr.sin_addr))
	{
		return -1;
	}

	int fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(fd < 0)
	{
		return -2;
	}

	char buff[64]="hello world";
	// bzero(buff, sizeof(buff));

	struct sockaddr_in server_addr;
	socklen_t len = sizeof(addr);
	int n = sizeof(buff);
    for(int i=0; i<20; i++)
    {
	    if(0 == (n = sendto(fd, buff, n, 0, (sockaddr *)&addr, len)))
	    {
		    return -5;
	    }
    
	    printf("client %d: sendto succ\n", i);
    
	    if((n = recvfrom(fd, buff, sizeof(buff), 0, (sockaddr *)&server_addr, &len)) == -1)
	    {
		    printf("client:recv failed\n");
		    return -4;
	    }

	    printf("%s", buff);
	    printf("client %d:recv succ\n", i);
    }
	return 0;
}
