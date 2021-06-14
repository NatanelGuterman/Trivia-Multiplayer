import socket
import json

MIN_LEGAL_PORT = 1024
MAX_LEGAL_PORT = 65535
SERVER_IP = '127.0.0.1'
MESSAGE = 'Hello'
json_login = {
  "username": "user1",
  "password": "1234"
}


def main():
    server_port = int(input("Please, enter server port: "))
    if not MIN_LEGAL_PORT <= server_port <= MAX_LEGAL_PORT:
        print("Illegal port, only between 1024 - 65535!")
    else:
        # Create a TCP/IP socket
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        # Connecting to remote computer server_port
        server_address = (SERVER_IP, server_port)
        sock.connect(server_address)
        sock.sendall(json_login.dump().encode())  # Sending the message.
        server_msg = sock.recv(1024)
        print(server_msg.decode())
        sock.close()


if __name__ == "__main__":
    main()
