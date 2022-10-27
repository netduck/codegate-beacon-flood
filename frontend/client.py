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

        # Main Window Setting
        self.setWindowFlag(Qt.FramelessWindowHint)
        self.setStyleSheet("\
        color: white;\
        background-color: #232326;\
        ")

        # Widget Generation
        self.button = QtWidgets.QPushButton('Click me!')
        self.text = QtWidgets.QLabel('Beacon Flooding',
                                    alignment=QtCore.Qt.AlignCenter)
        self.requestTable = QTableWidget(0,2)

        # Query Layout Setting
        self.queryEdit = QLineEdit()
        self.queryLayout = QHBoxLayout()
        self.queryButton = QtWidgets.QPushButton('Submit')
        
        self.queryLayout.addWidget(self.queryEdit)
        self.queryLayout.addWidget(self.queryButton)
        
        # Table Widget Setting
        self.requestTable.setStyleSheet("\
        QHeaderView::section {background-color: #232326; width:100%}\
        ")
        self.requestTable.setHorizontalHeaderLabels(("No.","Wi-Fi Name"))
        self.requestTable.horizontalHeader().setSectionResizeMode(1, QtWidgets.QHeaderView.Stretch)
        self.requestTable.verticalHeader().hide()
        self.requestTable.horizontalHeader().setStretchLastSection(True)
        self.requestTable.setEditTriggers(QAbstractItemView.NoEditTriggers)
        
        # Table Test Case
        self.requestTable.insertRow(0)
        self.requestTable.setItem(0,0,QTableWidgetItem("1"))
        self.requestTable.setItem(0,1,QTableWidgetItem("TEST CASE"))

        self.mainLayout = QVBoxLayout()

        # Image Widget Setting
        self.label = QLabel(self, alignment=QtCore.Qt.AlignCenter)
        self.pixmap = QPixmap('../assets/img/logo.png')
        self.label.setPixmap(self.pixmap)
        self.mainLayout.addWidget(self.label)

        # Widgets -> MainWindow
        self.mainLayout.addWidget(self.text)
        self.mainLayout.addLayout(self.queryLayout)
        self.mainLayout.addWidget(self.requestTable)
        
        self.setLayout(self.mainLayout)

        self.mainLayout.addWidget(self.button)
        self.button.clicked.connect(self.callbackExample)

        self.model = QStandardItemModel()

        #self.requestTable.setModel(self.model)
        

    @QtCore.Slot()
    def callbackExample(self):
        self.showMaximized()

if __name__ == "__main__":
    app = QtWidgets.QApplication([])

    window = MainWindow()
    window.resize(800, 600)
    window.showFullScreen()
    sys.exit(app.exec())