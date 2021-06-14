import socket
import json

MIN_LEGAL_PORT = 1024
MAX_LEGAL_PORT = 65535
SERVER_IP = '127.0.0.1'
MESSAGE = 'Hello'
JSON_LOGIN = {
  "username": "user1",
  "password": "1234"
}

JSON_SIGNUP = {
      "username": "user1",
      "password": "1234",
      "mail": "user1@gmail.com"
}


def main():
    server_port = int(input("Please, enter server port: "))
    if not MIN_LEGAL_PORT <= server_port <= MAX_LEGAL_PORT:
        print("Illegal port, only between 1024 - 65535!")
    else:
        #Create a TCP/IP socket
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        #Connecting to remote computer server_port
        server_address = (SERVER_IP, server_port)
        sock.connect(server_address)
        data = json.dumps(JSON_LOGIN)
        print(data)
        res = ''.join(format(ord(i), '08b') for i in data)
        print(res)
        print("11001001" + (("{0:b}".format(len(res) // 8).zfill(8 - len("{0:b}".format(len(res) // 8)))).zfill(32)))
        sock.sendall(("00000011" + (("{0:b}".format(len(res) // 8).zfill(8 - len("{0:b}".format(len(res) // 8)))).zfill(32)) + res).encode()) # Sending the message.
        server_msg = sock.recv(1024)
        print(server_msg.decode())
        sock.close()


if __name__ == "__main__":
    main()
