#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <strings.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
int udpdemo(const char *ip, uint16_t port);
int tcpdemo(const char *ip, uint16_t port);



int udpclient(const char *ip, uint16_t port);
