#include <iostream>
#include "framework.h"

int main()
{
    DemoServer demo;

	int ret = demo.Init("0.0.0.0", 8888);
    printf("ret:%d\n", ret);
    if(ret != 0)
    {
        printf("error:%d,%s", errno, strerror(errno));
    }
    demo.Start();
	return 0;
}
