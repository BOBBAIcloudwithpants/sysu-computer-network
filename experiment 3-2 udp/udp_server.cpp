#include <iostream>

#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>

using namespace std;
#define BUFF_SIZE 256
#define PORT 8888
void receive_msg(int socket_fd){
    char buf[BUFF_SIZE];
    sockaddr client_socket;

    int count;
    while(1){
        memset(buf, BUFF_SIZE, 0);
        socklen_t length = sizeof(client_socket);
        int count = recvfrom(socket_fd, buf, BUFF_SIZE, 0, &client_socket,&length);

        if(count < 0){
            cout << "Receive message failed" << endl;
        }

        cout << "Receive: " << buf << "from client" << endl;

        memset(buf, BUFF_SIZE, 0);
        
        char send_buf[BUFF_SIZE] = "Server has received your packet";
        sendto(socket_fd, send_buf, BUFF_SIZE, 0, &client_socket, length);
    }
}

int main(){

    int socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in server_addr;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    
    bind(socket_fd, (sockaddr*)&server_addr, sizeof(server_addr));

    cout << "Server start at port: " << PORT << endl;

    receive_msg(socket_fd);
    close(socket_fd);

}
