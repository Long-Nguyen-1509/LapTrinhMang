#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#ifdef __WIN32__
#include <winsock2.h>
#else
#include <sys/socket.h>
#endif

int main(){
    // Khoi tao winsock
    WSADATA wsa;
    printf("Initialising Winsock...");
    if(WSAStartup(MAKEWORD(2,2),&wsa) !=0){
        printf("Failed. Error code: %d", WSAGetLastError());
        return 1;
    }
    printf("Initialised\n");
    
    int client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(9000); 

    if (connect(client, (struct sockaddr *)&addr, sizeof(addr))) {
        perror("connect() failed");
        return 1;
    }

    // Truyen du lieu
    char buf[512];
    FILE *f = fopen("streaming_log.txt", "r");
    fgets(buf, sizeof(buf), f);
    if (buf != NULL){
        send(client, buf, strlen(buf), 0);
    }   
    puts(buf);
    fclose(f);

    // Dong ket noi
    close(client);
    return 0;
    
}