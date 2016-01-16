#!/usr/bin/python
#
# Copyright 2012 Google Inc. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

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

# For this example, the client id and client secret are command-line arguments.
#client_id = '724061061894-5veh1fgh50iqkpjfalu6ba4vmef8qh1d.apps.googleusercontent.com'
#client_secret = 'TNeY4QhQ56uDF8q-vBBcglp7'
client_id = '1023048382878-tto0qb1oic0lb2cbm00sbhq1kmurn50c.apps.googleusercontent.com'
client_secret = 'zEW7nHAzjOM5zRy8weUdlbL_'

calendarId = 'sqiou11@gmail.com'
# The scope URL for read/write access to a user's calendar data
scope = 'https://www.googleapis.com/auth/calendar'

# Create a flow object. This object holds the client_id, client_secret, and
# scope. It assists with OAuth 2.0 steps to get user authorization and
# credentials.
flow = OAuth2WebServerFlow(client_id, client_secret, scope)

def main():
    print spark.devices

    if spark.swagfish.connected:
        print "Connected to swagfish!"
        spark.swagfish.test("test")

	# Create a Storage object. This object holds the credentials that your
	# application needs to authorize access to the user's data. The name of the
	# credentials file is provided. If the file does not exist, it is
	# created. This object can only hold credentials for a single user, so
	# as-written, this script can only handle a single user.
	storage = Storage('credentials.dat')

	# The get() function returns the credentials for the Storage object. If no
	# credentials were found, None is returned.
	credentials = storage.get()

	# If no credentials are found or the credentials are invalid due to
	# expiration, new credentials need to be obtained from the authorization
	# server. The oauth2client.tools.run() function attempts to open an
	# authorization server page in your default web browser. The server
	# asks the user to grant your application access to the user's data.
	# If the user grants access, the run() function returns new credentials.
	# The new credentials are also stored in the supplied Storage object,
	# which updates the credentials.dat file.
	if credentials is None or credentials.invalid:
  		credentials = run(flow, storage)

	# Create an httplib2.Http object to handle our HTTP requests, and authorize it
	# using the credentials.authorize() function.
	http = httplib2.Http()
	http = credentials.authorize(http)

	# The apiclient.discovery.build() function returns an instance of an API service
	# object can be used to make API calls. The object is constructed with
	# methods specific to the calendar API. The arguments provided are:
	#   name of the API ('calendar')
	#   version of the API you are using ('v3')
	#   authorized httplib2.Http() object that can be used for API calls
	service = build('calendar', 'v3', http=http)

	try:

	    # The Calendar API's events().list method returns paginated results, so we
	    # have to execute the request in a paging loop. First, build the
	    # request object. The arguments provided are:
	    #   primary calendar for user
	    request = service.events().list(
	    	calendarId=calendarId,
	    	timeMin='2015-02-01T00:00:00-08:00',
	    	timeMax='2015-02-28T00:00:00-08:00')
	    # Loop until all pages have been processed.
	    while request != None:
			# Get the next page.
			response = request.execute()
			colors = service.colors().get().execute()
			print len(response.get('items'))
			# Accessing the response like a dict object with an 'items' key
			# returns a list of item objects (events).
			for event in response.get('items', []):
				# The event object is a dict object with a 'summary' key.
				spark.swagfish.test(event.get('start').get('dateTime')[-14:-9] + ',' + event.get('summary')[:16] + ',' + event.get('location') + ',' + colors.get('event').get(event.get('colorId', '')).get('background') + '\n')
				print repr(event.get('summary')) + '\n'
			# Get the next request object by passing the previous request object to
			# the list_next method.
			request = service.events().list_next(request, response)

	except AccessTokenRefreshError:
	    # The AccessTokenRefreshError exception is raised if the credentials
	    # have been revoked by the user or they have expired.
	    print ('The credentials have been revoked or expired, please re-run'
	           'the application to re-authorize')

if __name__ == '__main__':
  	main()