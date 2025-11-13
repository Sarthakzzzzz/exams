import socket
import time
import struct
import threading

PORT = 8080


def handle_client(client_socket, addr):
    try:
        # Receive t1 (client's request time)
        raw_data = client_socket.recv(8)
        t1 = struct.unpack("!q", raw_data)[0]

        # t2 = server received request
        t2 = int(time.time() * 1000)
        time.sleep(2)  # Simulate processing delay

        # t3 = server sends reply
        t3 = int(time.time() * 1000)

        print(f"\nClient {addr} request:")
        print(f"  t1 (client sent): {t1}")
        print(f"  t2 (server received): {t2}")
        print(f"  t3 (server reply): {t3}")

        # Send t2 and t3 back to client
        response = struct.pack("!qq", t2, t3)
        client_socket.send(response)
        print(f"Response sent to {addr}")
    except Exception as e:
        print(f"Error: {e}")
    finally:
        client_socket.close()


def start_server():
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server_socket.bind(('127.0.0.1', PORT))
    server_socket.listen(5)
    print(f"NTP Server on port {PORT}...")

    try:
        while True:
            client_socket, addr = server_socket.accept()
            thread = threading.Thread(target=handle_client, args=(
                client_socket, addr), daemon=True)
            thread.start()
    except KeyboardInterrupt:
        print("\nServer stopped")
    finally:
        server_socket.close()


if __name__ == "__main__":
    start_server()
