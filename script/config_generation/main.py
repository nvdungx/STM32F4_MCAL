import os, sys, pathlib, logging, time
import multiprocessing

import PySide6.QtCore
from PySide6.QtWidgets import QApplication, QMainWindow

from ui.src.CfgGenerateTool import *

class MainWindow(QMainWindow):
  def __init__(self):
    super(MainWindow, self).__init__()
    self.ui = Ui_MainWindow()
    self.ui.setupUi(self)

if __name__ == "__main__":
  app = QApplication(sys.argv)
  window = MainWindow()
  window.show()
  sys.exit(app.exec())