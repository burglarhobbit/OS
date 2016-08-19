from bs4 import BeautifulSoup as BS
import urllib
import json
import os
import time
import platform

a = 1 # Beep time in seconds
b = 400 # Frequency of beep

my_url = 'https://www.instagram.com/p/BJQJf0pBBY1/'

r = urllib.urlopen(my_url).read() # Reading the source page

soup = BS(r,"html.parser") 
js = soup.find_all('script',type="text/javascript")[4].string # Extract the javascript portion
jsonValue = '{%s}' % (js.split('{', 1)[1].rsplit('}', 1)[0],) # Extracting the json dictionary
value = json.loads(jsonValue) # Converting the json dictionary to Python dictionary

last_comment = value['entry_data']['PostPage'][0]['media']['comments']['nodes'][-1]['text'] # Extracting Last comment of the post

while True:
	r = urllib.urlopen(my_url).read() # Reading the source page again, for processing to find a new comment

	soup = BS(r,"html.parser")
	js = soup.find_all('script',type="text/javascript")[4].string

	jsonValue = '{%s}' % (js.split('{', 1)[1].rsplit('}', 1)[0],)
	value = json.loads(jsonValue)

	new_comment = value['entry_data']['PostPage'][0]['media']['comments']['nodes'][-1]['text'] # Extracting last comment again

	if new_comment != last_comment: # Check if there's a new comment, if so, beep for 3 times
		for i in range(3):
			if platform.system() == 'Linux': # For Beeping in Linux based systems
				os.system('play --no-show-progress --null --channels 1 synth %s sine %f' % (a, b))
			elif platform.system() == 'Windows': # For Beeping in Windows
				import winsound
				winsound.Beep(b,a*1000)
			time.sleep(1)
		last_comment = new_comment # Resetting last comment as new comment for and the cycle continues
		print new_comment
