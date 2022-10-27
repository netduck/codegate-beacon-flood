import socket
import sys
import random
from PySide6 import *
from PySide6.QtWidgets import *
from PySide6.QtGui import *
from PySide6.QtCore import *


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

        # Variable Setting
        self.elementCnt = 0

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
        self.text.setStyleSheet("padding :30px")
        self.text.setFont(QtGui.QFont("Press Start", 30, QtGui.QFont.Normal))
        self.requestTable = QTableWidget(0,2)

        # Query Layout Setting
        self.queryEdit = QLineEdit()
        self.queryEdit.setStyleSheet("padding :30px")
        self.queryLayout = QHBoxLayout()
        self.queryButton = QtWidgets.QPushButton('Submit')
        self.queryButton.setStyleSheet("border :1px solid #FFFFFF;padding :30px")
        
        self.queryLayout.addWidget(self.queryEdit)
        self.queryLayout.addWidget(self.queryButton)
        
        # Table Widget Setting
        self.requestTable.setStyleSheet("\
        QHeaderView::section { background-color: #232326; width:100%;}\
        QHeaderView::section:hover { background-color: #FF0C00; width:100%;}\
        QTableWidget::item:hover { background-color: red; }\
        ")
        self.requestTable.setHorizontalHeaderLabels(("No.\t","Wi-Fi Name"))
        self.requestTable.setColumnWidth(100, 80)
        self.requestTable.horizontalHeader().setSectionResizeMode(0, QtWidgets.QHeaderView.Stretch)
        self.requestTable.horizontalHeader().setSectionResizeMode(1, QtWidgets.QHeaderView.Stretch)
        self.requestTable.verticalHeader().hide()
        self.requestTable.horizontalHeader().setStretchLastSection(True)
        self.requestTable.setEditTriggers(QAbstractItemView.NoEditTriggers)
        
        # Table Test Case
        #for i in range(0,20):
        #    self.requestTable.insertRow(i)
        #    self.requestTable.setItem(i,0,QTableWidgetItem(str(i)))
        #    self.requestTable.setItem(i,1,QTableWidgetItem("TEST CASE"))

        self.mainLayout = QVBoxLayout()

        # Image Widget Setting
        self.label = QLabel(self, alignment=QtCore.Qt.AlignCenter)
        self.pixmap = QPixmap('../assets/img/logo.png')
        #self.pixmap.scaled(500,500)
        self.label.setPixmap(self.pixmap)
        self.mainLayout.addWidget(self.label)

        # Widgets -> MainWindow
        self.mainLayout.addWidget(self.text)
        self.mainLayout.addLayout(self.queryLayout)
        self.mainLayout.addWidget(self.requestTable)
        
        self.setLayout(self.mainLayout)

        #self.mainLayout.addWidget(self.button)
        #self.button.clicked.connect(self.callbackExample)

        #self.model = QStandardItemModel()
        #self.requestTable.setModel(self.model)
        self.queryButton.clicked.connect(self.beaconRequest)

    @QtCore.Slot()
    def beaconRequest(self):

        if self.queryEdit.text()=="":
            QMessageBox.warning(self, 'Warning', 'Empty',
                                    QMessageBox.Yes)
            return

        self.requestTable.insertRow(self.elementCnt)
        self.requestTable.setItem(self.elementCnt,0,QTableWidgetItem(str(self.elementCnt+1)))
        self.requestTable.setItem(self.elementCnt,1,QTableWidgetItem(self.queryEdit.text()))
        self.queryEdit.setText('')
        self.elementCnt+=1

if __name__ == "__main__":
    app = QtWidgets.QApplication([])

    #fontDB = QFontDatabase()
    id = QFontDatabase.addApplicationFont('../assets/font/PrStart.ttf')
    #print(QFontDatabase.applicationFontFamilies(id))
    app.setFont(QtGui.QFont("Press Start", 28, QtGui.QFont.Normal))
    window = MainWindow()
    window.showFullScreen()
    sys.exit(app.exec())