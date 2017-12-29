#include <iostream>
#include "../framework.h"

int main()
{
	DemoServer test;
	while(true)
	{
		//do something
        static int i = 0;
        char buff[1024];
        snprintf(buff, sizeof(buff), "hello world, %d", i++);
        uint32_t len = sizeof(buff);
		int ret = test.SendAndRecvUdpPkg("127.0.0.1", 8888, (void *)buff, strlen(buff)+1, (void *)buff, len);
        printf("%d,%d:%s\n",i, len, buff);
	}
	return 0;
}
