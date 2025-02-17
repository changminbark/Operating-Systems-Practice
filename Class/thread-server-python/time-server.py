############################################################################
# Server side: open a TCP/IP socket on a port, listen for a message from
# a client, and send an echo reply; this is a simple one-shot listen/reply
# conversation per client, but it goes into an infinite loop to listen for
# more clients as long as this server script runs; the client may run on 
# a remote machine, or on same computer if it uses 'localhost' for server
############################################################################

# revised by A. Fuchsberger 09-20-2024 for CSCI 315 for in-class activity
# revised by X. Meng 01-19-2013 for CSCI 363, converted it to Python 3.x and
# removed extra elements, using only the minimum setup.

# revised by X. Meng 2020-09-10 for CSCI 315 in-class activity
import sys
import string
from socket import *                    # get socket constructor and constants
from datetime import datetime

myHost = ''                             # server machine, '' means local host

if len(sys.argv) != 2:
    print("usage: python " + sys.argv[0] + "port-number (> 1024)")
    sys.exit("error in parameters.")

myPort = int(sys.argv[1])

sockobj = socket(AF_INET, SOCK_STREAM)       # make a TCP socket object
sockobj.bind((myHost, myPort))               # bind it to server port number 
sockobj.listen(5)                            # listen, allow 5 pending connects
     
while True:                                  # listen until process killed
    connection, address = sockobj.accept()   # wait for next client connect
    print('Server connected by', address)    # connection is a new socket
    
    curr_time = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
    connection.send(str.encode(curr_time)) 
                                             # until eof when socket closed
    connection.close() 
