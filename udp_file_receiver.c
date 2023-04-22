#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#ifdef __WIN32__
# include <winsock2.h>
#else
# include <sys/socket.h>
#endif

int main(int argc, char *argv[]){
    // Khoi tao winsock
    WSADATA wsa;
    printf("Initialising Winsock...");
    if(WSAStartup(MAKEWORD(2,2),&wsa) !=0){
        printf("Failed. Error code: %d", WSAGetLastError());
        return 1;
    }
    printf("Initialised\n");

    // Tạo socket theo giao thức UDP
    int receiver = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    // Khai báo địa chỉ bên nhận
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(atoi(argv[1]));
    bind(receiver, (struct sockaddr *)&addr, sizeof(addr));

    // Nhận tin nhắn
    char buf[256];
    int ret = recvfrom(receiver, buf, sizeof(buf), 0, NULL, NULL);
    if (ret == -1) {
        printf("recvfrom() failed\n");
    } 
    else{
    buf[ret] = 0;
    } 

    FILE *f = fopen(argv[2], "w");
    fprintf(f, "%s", buf);

}