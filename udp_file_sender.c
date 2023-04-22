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
#include <time.h>

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
    int sender = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    // Khai báo địa chỉ bên nhận
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    addr.sin_port = htons(atoi(argv[2]));

    // Gửi tin nhắn
    char buf[256];
    FILE *f = fopen(argv[3], "r");
    fgets(buf, sizeof(buf), f);
    puts(buf);
    sendto(sender, buf, strlen(buf), 0, (struct sockaddr *)&addr, sizeof(addr));
}