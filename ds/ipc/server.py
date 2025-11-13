import socket
import threading

accounts = {"Sarthak": 5000, "Devang": 3000, "Adwait": 10000}


def handle_client(conn, addr):
    while True:
        try:
            data = conn.recv(1024).decode()
            if not data:
                break

            user, action, amount = data.split()
            amount = int(amount)

            if user not in accounts:
                conn.send(b"User not found")
                continue

            if action == "BAL":
                conn.send(f"Balance: ${accounts[user]}".encode())
            elif action == "DEP":
                accounts[user] += amount
                conn.send(
                    f"Deposited ${amount}. New Balance: ${accounts[user]}".encode())
            elif action == "WIT":
                if accounts[user] >= amount:
                    accounts[user] -= amount
                    conn.send(
                        f"Withdrawn ${amount}. New Balance: ${accounts[user]}".encode())
                else:
                    conn.send(b"Insufficient funds!")
            else:
                conn.send(b"Invalid action")
        except:
            break

    conn.close()


if __name__ == "__main__":
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server.bind(("127.0.0.1", 8080))
    server.listen(5)
    print("Server running on port 8080...")
    try:
        while True:
            conn, addr = server.accept()
            thread = threading.Thread(
                target=handle_client, args=(conn, addr), daemon=True)
            thread.start()
    except KeyboardInterrupt:
        print("\nServer stopped")
    finally:
        server.close()
