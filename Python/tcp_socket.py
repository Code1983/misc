#!/usr/bin/env python3

# can access the data from terminal using following command
# nc localhost 8866
import socket
import sys
import time
import signal

# handles signal for clean exit
def signal_handler(sig, frame):
        print('You pressed Ctrl+C!')
        connection.close()
        sys.exit(0)
signal.signal(signal.SIGINT, signal_handler)


def eprint(*args):
    print(*args, file=sys.stderr)


A_PACKET_ID = 'A'
B_PACKET_ID = 'B'



if __name__ == "__main__":
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_address = ('localhost', 8866)
    sock.bind(server_address)
    sock.listen(1)

    eprint('waiting for a connection on %s port %s' % server_address)
    connection, client_address = sock.accept()

    try:
        eprint('connection from', client_address)

        tick = 0
        while True:
            eprint('sending data for tick %s' % tick)
            num = str(tick)[0]
            
            #ord() is used to convert the raw data to displayable format.
            #may remove if interfacing it with some other program.

            connection.send(bytes([ord('0'), ord(A_PACKET_ID), ord(str(tick)[0]), ord('\n')]))
            connection.send(bytes([ord('0'), ord(B_PACKET_ID), ord(str(tick)[0]), ord('\n')]))
            time.sleep(1)

            tick += 1
    except:
        # Clean up the connection
        eprint('exception occured')
        connection.close()
    finally:
        # Clean up the connection
        eprint('closing connection')
        connection.close()

