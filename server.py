import socket as soc

if __name__ == '__main__':
    host = '127.0.0.1'
    port = 1025
    ssocket = soc.socket(family=soc.AF_INET, type = soc.SOCK_DGRAM, proto=0)
    ssocket.bind((host, port))
    ssocket
    print('Socket is listining')
    while True:
        conn, addr = ssocket.recvfrom(25)
        print("")