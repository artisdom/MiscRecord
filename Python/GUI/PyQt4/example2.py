#An Expression Evaluator in 30 Lines
from __future__ import division
import sys
from math import *
from PyQt4.QtCore import *
from PyQt4.QtGui import *
class Form(QDialog):
	def __init__(self,parent=None):
		super(Form,self).__init__(parent)
		self.browser = QTextBrowser()
		self.browser.setFont(QFont("Consolas",12,QFont.StyleItalic))
		self.lineedit = QLineEdit('Type an express and press Enter')
		self.lineedit.selectAll()
		layout = QVBoxLayout()
		layout.addWidget(self.browser)
		layout.addWidget(self.lineedit)
		self.setLayout(layout)
		self.lineedit.setFocus()
		self.connect(self.lineedit,SIGNAL('returnPressed()'),self.updateUi)
		self.setWindowTitle('Calculate')
	def updateUi(self):
		try:
			text = unicode(self.lineedit.text())
			self.browser.append('%s = %s' % (text, eval(text)))
		except:
			self.browser.append('%s is invalid!' % text)
app = QApplication(sys.argv)
app.setFont(QFont("Consolas",10,italic=1))
form = Form()
form.show()
app.exec_()