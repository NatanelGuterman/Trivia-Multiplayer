import socket

MIN_LEGAL_PORT = 1024
MAX_LEGAL_PORT = 65535
SERVER_IP = '127.0.0.1'
MESSAGE = 'Hello'


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
        server_msg = sock.recv(1024)
        if server_msg.decode() == MESSAGE:
            print("Server sent hello.")
            sock.sendall(MESSAGE.encode()) # Sending the message.
        else:
            print("Error has accrued.")
        sock.close()


if __name__ == "__main__":
    main()
