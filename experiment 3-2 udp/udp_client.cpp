#include <iostream>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

using namespace std;

#define PORT 8888
#define BUFF_SIZE 512
#define SERVER_IP "192.168.50.18"
void send_msg(int socket_fd, struct sockaddr_in client_addr)
{

    string greet = "Hello Server!";
    int times = 100;
    while (times)
    {

        times--;
        char buf[BUFF_SIZE] = "Hello Server!";
        
        sendto(socket_fd, buf, BUFF_SIZE, 0, (sockaddr *)&client_addr, sizeof(client_addr));

        cout << "Send: " << greet << " to the server\n";
        memset(buf, 0, BUFF_SIZE);
        sockaddr server_addr;
        socklen_t server_length = sizeof(server_addr);
        recvfrom(socket_fd, buf, BUFF_SIZE, 0, &server_addr, &server_length);
        cout << "Receive: " << buf << " from server" << endl;
    }
}

int main()
{
    int socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in client_addr;
    client_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
//    client_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(PORT);

    send_msg(socket_fd, client_addr);
    close(socket_fd);
}
