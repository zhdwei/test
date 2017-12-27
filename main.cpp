#include <iostream>
#include "framework.h"

int main()
{
	// while(true)
	// {
		//do something
	int ret = udpdemo("0.0.0.0", 8888);
	printf("%d", ret);
	sleep(3);
	// }
	return 0;
}
