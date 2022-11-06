import socket
import sys
import random
from PySide6 import *
from PySide6.QtWidgets import *
from PySide6.QtGui import *
from PySide6.QtCore import *

import sockcom

class RequestTable(QTableWidget):
    def __init__(self):
        super().__init__(10,2)
        super().setStyleSheet("\
            QHeaderView::section { background-color: #232326; width:100%;}\
            QHeaderView::section:hover { background-color: #FF0C00; width:100%;}\
            QTableWidget::item:hover { background-color: red; }\
        ")
        super().setHorizontalHeaderLabels(("No.\t","Wi-Fi Name"))
        super().setColumnWidth(100, 80)
        super().horizontalHeader().setSectionResizeMode(0, QtWidgets.QHeaderView.Stretch)
        super().horizontalHeader().setSectionResizeMode(1, QtWidgets.QHeaderView.Stretch)
        super().verticalHeader().hide()
        super().horizontalHeader().setStretchLastSection(True)
        super().setEditTriggers(QAbstractItemView.NoEditTriggers)


class QueryLayout(QHBoxLayout):
    def __init__(self, reqTbl):
        super().__init__()

        # Variable Setting
        self.elementIdx = 0
        self.reqTbl =  reqTbl
        
        # Socket
        self.conn = sockcom.SockCom()

        # Editor
        self.queryEdit = QLineEdit()
        self.queryEdit.setStyleSheet('padding :30px')

        # Button
        self.queryButton = QPushButton('Submit')
        self.queryButton.setStyleSheet("border :1px solid #FFFFFF;padding :30px")

        super().addWidget(self.queryEdit)
        super().addWidget(self.queryButton)

        self.queryButton.clicked.connect(self.beaconRequest)
        self.queryEdit.returnPressed.connect(self.beaconRequest)

    @QtCore.Slot()
    def beaconRequest(self):

        if self.queryEdit.text()=="":
            warn('Empty')
            return

        #self.reqTbl.insertRow(self.elementIdx)
        self.reqTbl.setItem(self.elementIdx,0,QTableWidgetItem(str(self.elementIdx+1)))
        
        queryStr = self.queryEdit.text()
        self.reqTbl.setItem(self.elementIdx,1,QTableWidgetItem(queryStr))
        #self.sock.send(queryStr.encode())
        self.conn.sock.send(queryStr.encode())

        self.queryEdit.setText('')
        self.queryEdit.setFocus()
        
        if self.elementIdx<9:
            self.elementIdx+=1
        else:
            self.elementIdx=0

class MainWindow(QtWidgets.QWidget):
    def __init__(self):
        super().__init__()

        # Main Window Setting
        self.setStyleSheet("\
        color: white;\
        background-color: #232326;\
        ")

        # Widget Generation
        self.text = QtWidgets.QLabel('Beacon Flooding', alignment=QtCore.Qt.AlignCenter)
        self.text.setStyleSheet("padding :30px")
        self.text.setFont(QtGui.QFont("Press Start", 30, QtGui.QFont.Normal))

        # Query Layout Setting
        # Request Table Setting
        self.requestTable = RequestTable()
        self.queryLayout = QueryLayout(self.requestTable)

        #Table Test Case
        #for i in range(0,20):
        #    self.requestTable.insertRow(i)
        #    self.requestTable.setItem(i,0,QTableWidgetItem(str(i)))
        #    self.requestTable.setItem(i,1,QTableWidgetItem("TEST CASE"))

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

    def keyPressEvent(self, e):
        if e.key() == 16777265: # F2
            self.showFullScreen()
            self.resize(800, 800)

def warn(warnStr):
    msgBox = QMessageBox()
    msgBox.warning(window, 'Warning', warnStr, QMessageBox.Yes)

def SetFont(app):
    #Font Setting
    id = QFontDatabase.addApplicationFont('../assets/font/PrStart.ttf')
    #print(QFontDatabase.applicationFontFamilies(id))
    app.setFont(QtGui.QFont("Press Start", 36, QtGui.QFont.Normal))

if __name__ == "__main__":
    app = QtWidgets.QApplication([])

    SetFont(app)
    window = MainWindow()
    window.showFullScreen()

    sys.exit(app.exec())
