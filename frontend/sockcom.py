import socket

# Socket Communication
class SockCom:
    def __init__(self):
        
        # Connection Information
        self.SERVER_IP = '127.0.0.1'
        self.SERVER_PORT = 1235
        self.SIZE = 1024
        self.SERVER_ADDR = (self.SERVER_IP, self.SERVER_PORT)

        # Socket Setting
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.connect(self.SERVER_ADDR)

