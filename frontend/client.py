import socket
import sys
import random
from PySide6 import *
from PySide6.QtWidgets import *
from PySide6.QtGui import *


# 접속 정보 설정
SERVER_IP = '127.0.0.1'
SERVER_PORT = 1235
SIZE = 1024
SERVER_ADDR = (SERVER_IP, SERVER_PORT)
'''
# 클라이언트 소켓 설정
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client_socket:
    client_socket.connect(SERVER_ADDR)
    while True:
        ssid = input("Input SSID: ")
        client_socket.send(ssid.encode())
'''
class MainWindow(QtWidgets.QWidget):
    def __init__(self):
        super().__init__()

        self.setWindowFlag(Qt.FramelessWindowHint)
        self.setStyleSheet("\
        color: white;\
        background-color: #232326;\
        ")

        self.button = QtWidgets.QPushButton('Click me!')
        self.text = QtWidgets.QLabel('Beacon Flooding',
                                    alignment=QtCore.Qt.AlignCenter)

        self.layout = QVBoxLayout()

        self.queryEdit = QLineEdit()
        self.requestTable = QTableView()
        self.queryLayout = QHBoxLayout()
        self.queryLayout.addWidget(self.queryEdit)
        
        self.mainLayout = QVBoxLayout()

        self.label = QLabel(self, alignment=QtCore.Qt.AlignCenter)
        self.pixmap = QPixmap('../assets/img/logo.png')
        self.label.setPixmap(self.pixmap)
        self.mainLayout.addWidget(self.label)

        self.mainLayout.addWidget(self.text)
        self.mainLayout.addLayout(self.queryLayout)
        self.mainLayout.addWidget(self.requestTable)
        
        self.setLayout(self.mainLayout)

        self.mainLayout.addWidget(self.button)
        self.button.clicked.connect(self.callbackExample)

        self.model = QStandardItemModel()


        self.requestTable.setModel(self.model)
        self.requestTable.verticalHeader().hide()
        self.requestTable.horizontalHeader().setStretchLastSection(True)

    @QtCore.Slot()
    def callbackExample(self):
        self.showMaximized()

if __name__ == "__main__":
    app = QtWidgets.QApplication([])

    window = MainWindow()
    window.resize(800, 600)
    window.showFullScreen()
    sys.exit(app.exec())