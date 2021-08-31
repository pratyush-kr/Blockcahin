import socket as soc
import hashlib

def hash(data):
    return hashlib.sha256(data)

if __name__ == '__main__':
    host = '127.0.0.1'
    port = 1025
    try:
        ssocket = soc.socket(family=soc.AF_INET, type = soc.SOCK_DGRAM, proto=0)
    except soc.error as err:
        print(f"socket creation failed with error {err}")
    ssocket.bind((host, port))
    print('Socket is listining')
    while True:
        data, addr = ssocket.recvfrom(1025)
        print("Sending Hash...")
        h = hash(data)
        ssocket.sendto(h.hexdigest().encode(), addr)