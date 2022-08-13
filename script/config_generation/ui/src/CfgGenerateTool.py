# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'CfgGenerateTool.ui'
##
## Created by: Qt User Interface Compiler version 6.3.1
##
## WARNING! All changes made in this file will be lost when recompiling UI file!
################################################################################

from PySide6.QtCore import (QCoreApplication, QDate, QDateTime, QLocale,
    QMetaObject, QObject, QPoint, QRect,
    QSize, QTime, QUrl, Qt)
from PySide6.QtGui import (QAction, QBrush, QColor, QConicalGradient,
    QCursor, QFont, QFontDatabase, QGradient,
    QIcon, QImage, QKeySequence, QLinearGradient,
    QPainter, QPalette, QPixmap, QRadialGradient,
    QTransform)
from PySide6.QtWidgets import (QApplication, QHeaderView, QMainWindow, QMenu,
    QMenuBar, QScrollArea, QSizePolicy, QStatusBar,
    QTreeView, QWidget)

import os
class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        if not MainWindow.objectName():
            MainWindow.setObjectName(u"MainWindow")
        MainWindow.resize(1117, 894)
        application_path = os.path.dirname(__file__)
        self.uidir = os.path.abspath(os.path.join(application_path, "../."))
        icon = QIcon()
        icon.addFile(os.path.join(self.uidir, u"icons/icon-app.png"), QSize(), QIcon.Normal, QIcon.Off)
        MainWindow.setWindowIcon(icon)
        self.action_importPDF = QAction(MainWindow)
        self.action_importPDF.setObjectName(u"action_importPDF")
        self.action_saveCDF = QAction(MainWindow)
        self.action_saveCDF.setObjectName(u"action_saveCDF")
        self.action_generate = QAction(MainWindow)
        self.action_generate.setObjectName(u"action_generate")
        self.centralwidget = QWidget(MainWindow)
        self.centralwidget.setObjectName(u"centralwidget")
        self.treeView = QTreeView(self.centralwidget)
        self.treeView.setObjectName(u"treeView")
        self.treeView.setGeometry(QRect(10, 10, 201, 841))
        self.scrollArea = QScrollArea(self.centralwidget)
        self.scrollArea.setObjectName(u"scrollArea")
        self.scrollArea.setGeometry(QRect(230, 10, 821, 841))
        self.scrollArea.setWidgetResizable(True)
        self.scrollAreaWidgetContents = QWidget()
        self.scrollAreaWidgetContents.setObjectName(u"scrollAreaWidgetContents")
        self.scrollAreaWidgetContents.setGeometry(QRect(0, 0, 819, 839))
        self.scrollArea.setWidget(self.scrollAreaWidgetContents)
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QMenuBar(MainWindow)
        self.menubar.setObjectName(u"menubar")
        self.menubar.setGeometry(QRect(0, 0, 1117, 21))
        self.menu_File = QMenu(self.menubar)
        self.menu_File.setObjectName(u"menu_File")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QStatusBar(MainWindow)
        self.statusbar.setObjectName(u"statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.menubar.addAction(self.menu_File.menuAction())
        self.menu_File.addAction(self.action_importPDF)
        self.menu_File.addAction(self.action_saveCDF)
        self.menu_File.addAction(self.action_generate)

        self.retranslateUi(MainWindow)

        QMetaObject.connectSlotsByName(MainWindow)
    # setupUi

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(QCoreApplication.translate("MainWindow", u"CfgGenerateTool", None))
        self.action_importPDF.setText(QCoreApplication.translate("MainWindow", u"Import PDF file", None))
        self.action_saveCDF.setText(QCoreApplication.translate("MainWindow", u"Save as CDF...", None))
        self.action_generate.setText(QCoreApplication.translate("MainWindow", u"Generate", None))
        self.menu_File.setTitle(QCoreApplication.translate("MainWindow", u"File", None))
    # retranslateUi


