#!/usr/bin/python

import time
print("Content-Type: text/html\n\n")  # html markup follows

timeStr = time.strftime("%c") # obtains current time

htmlFormat = """
<html>
  <Title>The Time Now</Title>
<body>
  <p>The current Central date and time is:  {timeStr}</p>
</body>
</html> """

print(htmlFormat.format(**locals())) # see embedded %s ^ above

"""
import cgitb
cgitb.enable(display=0, logdir="/path/to/logdir")

form = cgi.FieldStorage()
if "name" not in form or "addr" not in form:
    print "<H1>Error</H1>"
    print "Please fill in the name and addr fields."
    return
print "<p>name:", form["name"].value
print "<p>addr:", form["addr"].value
"""
