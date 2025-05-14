import socket

def start_listener(ip='0.0.0.0', port=4444):
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind((ip, port))
    server.listen(5)
    print(f"[+] Listening on {ip}:{port}")

    while True:
        client, addr = server.accept()
        print(f"[+] Connection from {addr}")

        file_name = b""
        while True:
            byte = client.recv(1)
            if byte == b'\n':
                break
            file_name += byte
        file_name = file_name.decode().strip()
        print(f"[+] Receiving file: {file_name}")

        with open(file_name, "wb") as f:
            while True:
                data = client.recv(4096)
                if not data:
                    break
                f.write(data)

        client.close()
        print(f"[+] Saved: {file_name}\n")

if __name__ == "__main__":
    start_listener()
