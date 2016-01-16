from PyQt4 import QtCore, QtGui
import sys
import httplib2
import sys
import json

from apiclient.discovery import build
from oauth2client.file import Storage
from oauth2client.client import AccessTokenRefreshError
from oauth2client.client import OAuth2WebServerFlow
from oauth2client.tools import run
from spyrk import SparkCloud

ACCESS_TOKEN = '261fb2d425b70208381c6eba0ef8445360859448'

spark = SparkCloud(ACCESS_TOKEN)
scope = 'https://www.googleapis.com/auth/calendar'

try:
    _encoding = QtGui.QApplication.UnicodeUTF8
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig, _encoding)
except AttributeError:
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig)

def hex_to_rgb(value):
    value = value.lstrip('#')
    lv = len(value)
    rgbaStr = ''
    for i in range(0, lv, lv // 3):
        rgbaStr += str(int(value[i:i + lv // 3], 16)) + '-'
    return rgbaStr[:len(rgbaStr)-1]

class CalendarParseThread(QtCore.QThread):
    procDone = QtCore.pyqtSignal(bool)
    partDone = QtCore.pyqtSignal(str)

    def __init__(self, clientID, clientSecret, calendarID):
        QtCore.QThread.__init__(self)
        self.client_id = clientID;
        self.client_secret = clientSecret;
        self.calendarId = calendarID;

    def run(self):
        flow = OAuth2WebServerFlow(self.client_id, self.client_secret, scope)
        storage = Storage('credentials.dat')
        credentials = storage.get()
        if credentials is None or credentials.invalid:
            credentials = run(flow, storage)
        http = httplib2.Http()
        http = credentials.authorize(http)
        service = build('calendar', 'v3', http=http)
        try:
            # The Calendar API's events().list method returns paginated results, so we
            # have to execute the request in a paging loop. First, build the
            # request object. The arguments provided are:
            #   primary calendar for user
            request = service.events().list(
                calendarId=self.calendarId,
                timeMin='2015-03-02T00:00:00-08:00',
                timeMax='2015-03-03T00:00:00-08:00',
                singleEvents=True,
                orderBy='startTime')
            # Loop until all pages have been processed.
            while request != None:
                # Get the next page.
                response = request.execute()
                colors = service.colors().get().execute()

                # Accessing the response like a dict object with an 'items' key
                # returns a list of item objects (events).
                for event in response.get('items', []):
                    # The event object is a dict object with a 'summary' key.
                    days = ""
                    try:
                        recurStr = event.get('recurrence', [])
                        if recurStr:
                            days = recurStr[0][recurStr[0].index('BYDAY=')+6:]
                        spark.swagfish.getData(event.get('summary')[:16] + ',' + event.get('location').rstrip() + ' ' + event.get('start').get('dateTime')[-14:-9] + ',' + hex_to_rgb(colors.get('event').get(event.get('colorId', {})).get('background')))
                        #spark.swagfish.getData(days)
                        #print repr(event.get('summary'))
                        self.partDone.emit(event.get('summary') + " added")

                    except:
                        self.partDone.emit("An error has occurred adding " + event.get('summary'))
                # Get the next request object by passing the previous request object to
                # the list_next method.
                request = service.events().list_next(request, response)

        except AccessTokenRefreshError:
            # The AccessTokenRefreshError exception is raised if the credentials
            # have been revoked by the user or they have expired.
            print ('The credentials have been revoked or expired, please re-run the application to re-authorize')
            self.partDone.emit('The credentials have been revoked or expired, please re-run the application to re-authorize')

        self.procDone.emit(True)

class Ui_Form(QtGui.QWidget):
    def __init__(self):
        QtGui.QWidget.__init__(self)
        self.setupUi(self)

    def setupUi(self, Form):
        Form.setObjectName("Form")
        Form.resize(532, 397)
        self.verticalLayout = QtGui.QVBoxLayout(Form)
        self.verticalLayout.setObjectName("verticalLayout")
        self.horizontalLayout = QtGui.QHBoxLayout()
        self.horizontalLayout.setObjectName("horizontalLayout")

        self.verticalLayout.addLayout(self.horizontalLayout)
        self.horizontalLayout_3 = QtGui.QHBoxLayout()
        self.horizontalLayout_3.setObjectName("horizontalLayout_3")
        self.label_2 = QtGui.QLabel(Form)
        self.label_2.setObjectName("label_2")
        self.horizontalLayout_3.addWidget(self.label_2)
        self.clientIDInput = QtGui.QLineEdit(Form)
        self.clientIDInput.setObjectName("clientIDInput")
        self.horizontalLayout_3.addWidget(self.clientIDInput)
        self.verticalLayout.addLayout(self.horizontalLayout_3)

        self.horizontalLayout_4 = QtGui.QHBoxLayout()
        self.horizontalLayout_4.setObjectName("horizontalLayout_4")
        self.label_3 = QtGui.QLabel(Form)
        self.label_3.setObjectName("label_3")
        self.horizontalLayout_4.addWidget(self.label_3)
        self.clientSecretInput = QtGui.QLineEdit(Form)
        self.clientSecretInput.setObjectName("clientSecretInput")
        self.horizontalLayout_4.addWidget(self.clientSecretInput)
        self.verticalLayout.addLayout(self.horizontalLayout_4)

        self.horizontalLayout_5 = QtGui.QHBoxLayout()
        self.horizontalLayout_5.setObjectName("horizontalLayout_5")
        self.label_4 = QtGui.QLabel(Form)
        self.label_4.setObjectName("label_4")
        self.horizontalLayout_5.addWidget(self.label_4)
        self.calendarIDInput = QtGui.QLineEdit(Form)
        self.calendarIDInput.setObjectName("calendarIDInput")
        self.horizontalLayout_5.addWidget(self.calendarIDInput)
        self.verticalLayout.addLayout(self.horizontalLayout_5)

        self.horizontalLayout_2 = QtGui.QHBoxLayout()
        self.horizontalLayout_2.setObjectName("horizontalLayout_2")
        self.configureButton = QtGui.QPushButton(Form)
        self.configureButton.setObjectName("configureButton")
        self.horizontalLayout_2.addWidget(self.configureButton)
        self.verticalLayout.addLayout(self.horizontalLayout_2)
        
        self.horizontalLayout_6 = QtGui.QHBoxLayout()
        self.horizontalLayout_6.setObjectName("horizontalLayout_6")
        self.configOutput = QtGui.QTextEdit(Form)
        self.configOutput.setObjectName("configOutput")
        self.configOutput.setReadOnly(True)
        self.horizontalLayout_6.addWidget(self.configOutput)
        self.verticalLayout.addLayout(self.horizontalLayout_6)

        self.retranslateUi(Form)
        QtCore.QMetaObject.connectSlotsByName(Form)

    def retranslateUi(self, Form):
        Form.setWindowTitle(_translate("Form", "SparkCore LED Google Calendar", None))
        self.label_2.setText(_translate("Form", "Client ID", None))
        self.label_3.setText(_translate("Form", "Client Secret", None))
        self.label_4.setText(_translate("Form", "Google Calendar ID", None))
        self.configureButton.setText(_translate("Form", "Configure", None))
        self.configureButton.clicked.connect(self.configureCalendar)

    def configureCalendar(self):
        '''client_id = self.clientIDInput.text()
        client_secret = self.clientSecretInput.text()
        calendarId = self.calendarIDInput.text()'''

        '''client_id = '1023048382878-tto0qb1oic0lb2cbm00sbhq1kmurn50c.apps.googleusercontent.com'
        client_secret = 'zEW7nHAzjOM5zRy8weUdlbL_'''
        client_id = '724061061894-5veh1fgh50iqkpjfalu6ba4vmef8qh1d.apps.googleusercontent.com'
        client_secret = 'TNeY4QhQ56uDF8q-vBBcglp7'
        calendarId = 'primary'
        self.thread = CalendarParseThread(client_id, client_secret, calendarId)
        self.thread.partDone.connect(self.updateBox)
        self.thread.procDone.connect(self.fin)
        self.thread.start()

    def updateBox(self, val):
        self.configOutput.append(val)

    def fin(self):
        self.configOutput.append("SparkCore calendar configuration successful!\n")

if __name__ == '__main__':
    app = QtGui.QApplication(sys.argv)
    ex = Ui_Form()
    ex.show()
    sys.exit(app.exec_())
