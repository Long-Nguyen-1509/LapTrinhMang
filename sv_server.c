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

    // Tao socket
    int listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listener == -1)
    {
        perror("socket() failed");
        return 1;
    }

    // Khai bao cau truc dia chi
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(atoi(argv[1]));

    // Gan dia chi voi socket
    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr))){
        printf("bind() failed.\n");
    }

    // Doi ket noi
    if (listen(listener, 5)) 
    {
        printf("listen() failed.\n");
        exit(1);
    }
    printf("Waiting for a new client ...\n");

    // Chap nhan ket noi tu client
    struct sockaddr_in clientAddr;
    int clientAddrLen = sizeof(addr);
    int client = accept(listener, (struct sockaddr *)&clientAddr, &clientAddrLen);
    if (client == -1)
    {
        printf("accept() failed.\n");
        exit(1);
    }
    printf("New client connected: %d\n");
    printf("Client IP: %s : %d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

    // Nhan du lieu tu client ghi ra file
    char buf[2048];
    FILE *f = fopen(argv[2], "w");
    printf("Recieving client input...\n");
    while(1){
        // Lay current time
        time_t current_time;
        time(&current_time);
        struct tm *local_time = localtime(&current_time);
        char formatted_time[100];
        strftime(formatted_time, sizeof(formatted_time), "%Y-%m-%d %H:%M:%S", local_time);

        //
        char str[256];
        strcpy(str, inet_ntoa(clientAddr.sin_addr));
        strcat(str, " ");
        strcat(str, formatted_time);
        strcat(str, " ");

        int res = recv(client, buf, sizeof(buf), 0);
        if (strncmp(buf, "exit", 4) == 0)
            break;
        fwrite(str, 1, strlen(str), f);
        fwrite(buf, 1, res, f);
    }
    printf("Da ghi du lieu vao file\n");

    // Dong ket noi
    fclose(f);
    close(client);
    close(listener);
    printf("Dong ket noi");
    return 0;
}
