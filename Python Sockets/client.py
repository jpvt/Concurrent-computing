import socket

HEADERSIZE = 10
#AF_INET = ipv4
#SOCK_STREAM = TCP

PORT = 1241
IP = socket.gethostname()
BUFFER_SIZE = 16

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((IP,PORT))

while True:
    new_msg = True
    full_msg = ""
    while True:
        msg = s.recv(BUFFER_SIZE)
        
        if new_msg:
            print("new msg len:",msg[:HEADERSIZE])
            msglen = int(msg[:HEADERSIZE])
            new_msg = False

        print(f"full message length: {msglen}")

        full_msg += msg.decode("utf-8")

        if len(full_msg) - HEADERSIZE == msglen:
            print('Full Message received')
            print(full_msg[HEADERSIZE:])
            new_msg = True
            full_msg = ''
