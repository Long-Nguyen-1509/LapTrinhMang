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

int main(int argc, char *argv[]) {

    // Khoi tao winsock
    WSADATA wsa;
    printf("Initialising Winsock...");
    if(WSAStartup(MAKEWORD(2,2),&wsa) !=0){
        printf("Failed. Error code: %d", WSAGetLastError());
        return 1;
    }
    printf("Initialised\n");
    
    // Khai bao socket
    int client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // Khai bao dia chi server
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    addr.sin_port = htons(atoi(argv[2]));
    
    // Ket noi den server
    int res = connect(client, (struct sockaddr *)&addr, sizeof(addr));
    if (res == -1) {
        printf("Khong ket noi duoc den server!");
        return 1;
    }   
    printf("Ket noi thanh cong den server\n");

    // Nhan du lieu tu server
    char buf[2048];
    res = recv(client, buf, sizeof(buf), 0);
    if (res < sizeof(buf))
        buf[res] = 0;
    printf("%s", buf);

    // Nhap tu ban phim 
    while (1)
    {
        printf("Enter string:");
        fgets(buf, sizeof(buf), stdin);

        send(client, buf, strlen(buf), 0);

        if (strncmp(buf, "exit", 4) == 0)
            break;
    }

    // Ket thuc, dong socket
    close(client);
    printf("Dong ket noi");
    return 0;
}
