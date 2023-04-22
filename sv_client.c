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

int main() {
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
        
    // Truyen nhan du lieu
    char mssv[9];
    char hoten[64];
    char ns[11];
    float dtb;
    char buf[256];

    while (1)
    {
        printf("Nhap thong tin cua sinh vien:\n");
        printf("Nhap MSSV: ");
        scanf("%s", mssv);
        
        // Xoa \n trong bo dem
        getchar();

        if (strncmp(mssv, "0000", 4) == 0)
            break;

        printf("Nhap Ho ten: ");
        fgets(hoten, sizeof(hoten), stdin);
        hoten[strlen(hoten) - 1] = 0;

        printf("Nhap Ngay sinh: ");
        scanf("%s", ns);

        // Xoa \n trong bo dem
        getchar();

        printf("Nhap Diem TB: ");
        scanf("%f", &dtb);

        // Xoa \n trong bo dem
        getchar();

        sprintf(buf, "%s %s %s %.2f", mssv, hoten, ns, dtb);
        send(client, buf, strlen(buf), 0);
    }

    // Ket thuc, dong socket
    close(client);

    return 0;
}
