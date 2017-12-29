#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <strings.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

class ServerBase
{
public:
    int Init(const char *ip, uint16_t port);
    int Start();
    virtual void callback(int fd, struct sockaddr_in *addr, void *pkg, uint32_t len) = 0;
    int tcpdemo(const char *ip, uint16_t port);
    int SendAndRecvUdpPkg(const char *ip, uint16_t port, void *send_buff, uint32_t send_len,
                          void *recv_buff, uint32_t &recv_len);
private:
    int m_fd;
};

class DemoServer: public ServerBase
{
    void callback(int fd, struct sockaddr_in *addr, void *pkg, uint32_t len);
};



