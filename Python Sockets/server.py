import socket
import time
import pickle

HEADERSIZE = 10

#AF_INET = ipv4
#SOCK_STREAM = TCP

PORT = 1241
IP = socket.gethostname()
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((IP, PORT)) # Bind to IP and Port
s.listen(5) # queue of 5

while True:
    # now our endpoint knows about the OTHER endpoint.
    clientsocket, address = s.accept()
    print(f"Connection from {address} has been established.")

    msg = "Welcome to the server!"
    msg = f"{len(msg):<{HEADERSIZE}}"+msg

    clientsocket.send(bytes(msg,"utf-8"))

    while True:
        time.sleep(3)
        msg = f'The time is: {time.time()}'
        msg = f"{len(msg):<{HEADERSIZE}}"+msg
        clientsocket.send(bytes(msg,"utf-8"))
