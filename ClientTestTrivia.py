import socket
import json

MIN_LEGAL_PORT = 1024
MAX_LEGAL_PORT = 65535
SERVER_IP = '127.0.0.1'
MESSAGE = 'Hello'
CODE_LOGIN = "11001001"
CODE_SIGNUP = "11001010"
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
    operation = int(input("Choose your operation: \t\n1 - Signup!\t\n2 - Login!\nAnswer: "))
    while True:
        username = input("Please, enter username: ")

        # test four - check username validation
        if username.isalnum():
            break
    password = input("Please, enter password: ")
    mail = ""
    if operation == 1:
        mail = input("Please, enter mail: ")

    server_port = int(input("Please, enter server port: "))
    if not MIN_LEGAL_PORT <= server_port <= MAX_LEGAL_PORT:
        print("Illegal port, only between 1024 - 65535!")
    else:
        #  Create a TCP/IP socket
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        #  Connecting to remote computer server_port
        server_address = (SERVER_IP, server_port)
        sock.connect(server_address)

        # PLEASE DO NOT ALL THE TEST TOGETHER, EACH TEST FOR IT'S OWN!

        #  first test - already signup to login (database clear)
        data = json.dumps(JSON_LOGIN)
        res = ''.join(format(ord(i), '08b') for i in data)
        sock.sendall((CODE_LOGIN + (("{0:b}".format(len(res) // 8).zfill(8 - len("{0:b}".format(len(res) // 8)))).zfill(32)) + res).encode()) # Sending the message.
        server_msg = sock.recv(1024)
        print(server_msg.decode())# should print status : 0

        #  second test - cannot signup with the same username
        data = json.dumps(JSON_SIGNUP)
        res = ''.join(format(ord(i), '08b') for i in data)
        sock.sendall((CODE_SIGNUP + (("{0:b}".format(len(res) // 8).zfill(8 - len("{0:b}".format(len(res) // 8)))).zfill(32)) + res).encode()) # Sending the message.
        server_msg = sock.recv(1024)
        print(server_msg.decode())# should print status : 1

        data = json.dumps(JSON_SIGNUP)
        res = ''.join(format(ord(i), '08b') for i in data)
        sock.sendall((CODE_SIGNUP + (("{0:b}".format(len(res) // 8).zfill(8 - len("{0:b}".format(len(res) // 8)))).zfill(32)) + res).encode()) # Sending the message.
        server_msg = sock.recv(1024)
        print(server_msg.decode())# should print status : 0

        #  third test - login twice while connected
        data = json.dumps(JSON_LOGIN)
        res = ''.join(format(ord(i), '08b') for i in data)
        sock.sendall((CODE_LOGIN + (("{0:b}".format(len(res) // 8).zfill(8 - len("{0:b}".format(len(res) // 8)))).zfill(32)) + res).encode()) # Sending the message.
        server_msg = sock.recv(1024)
        print(server_msg.decode()) # should print status : 1

        data = json.dumps(JSON_LOGIN)
        res = ''.join(format(ord(i), '08b') for i in data)
        sock.sendall((CODE_LOGIN + (("{0:b}".format(len(res) // 8).zfill(8 - len("{0:b}".format(len(res) // 8)))).zfill(32)) + res).encode()) # Sending the message.
        server_msg = sock.recv(1024)
        print(server_msg.decode()) # should print status : 0

        sock.close()


if __name__ == "__main__":
    main()
