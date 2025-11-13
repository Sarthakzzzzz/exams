import socket
import time
import struct

SERVER_ADDR = '127.0.0.1'
PORT = 8080


def start_client():
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect((SERVER_ADDR, PORT))

    print(f"Connected to NTP server at {SERVER_ADDR}:{PORT}\n")

    # t1 = client sends request
    t1 = int(time.time() * 1000)
    client_socket.send(struct.pack("!q", t1))
    print(f"Request sent at t1: {t1}")

    # Receive t2 (server received) and t3 (server sent)
    response = client_socket.recv(16)
    t2, t3 = struct.unpack("!qq", response)

    # t4 = client receives reply
    t4 = int(time.time() * 1000)

    print(f"Response received at t4: {t4}")
    print(f"\nTimestamps:")
    print(f"  t1 (client sent): {t1}")
    print(f"  t2 (server received): {t2}")
    print(f"  t3 (server replied): {t3}")
    print(f"  t4 (client received): {t4}")

    # Calculate network delay and clock offset
    network_delay = ((t4 - t1) - (t3 - t2)) / 2
    clock_offset = ((t2 - t1) + (t3 - t4)) / 2

    print(f"\n--- Time Sync Result ---")
    print(f"Network delay: {network_delay:.2f} ms")
    print(f"Clock offset: {clock_offset:.2f} ms")
    print(f"Adjusted time: {t4 + clock_offset:.0f}")
    print("------------------------")

    client_socket.close()


if __name__ == "__main__":
    start_client()
