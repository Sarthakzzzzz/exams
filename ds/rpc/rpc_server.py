import socket
import json
import threading

accounts = {"Sarthak": 5000, "Devang": 3000, "Adwait": 10000}


def handle_client(conn, addr):
    while True:
        try:
            data = json.loads(conn.recv(1024).decode())
            method = data["method"]
            user = data["user"]
            amount = data.get("amount", 0)

            if user not in accounts:
                result = {"error": "User not found"}
            elif method == "BAL":
                result = {"balance": accounts[user]}
            elif method == "DEP":
                accounts[user] += amount
                result = {"balance": accounts[user]}
            elif method == "WIT":
                if accounts[user] >= amount:
                    accounts[user] -= amount
                    result = {"balance": accounts[user]}
                else:
                    result = {"error": "Insufficient funds"}
            else:
                result = {"error": "Unknown method"}

            conn.send(json.dumps(result).encode())
        except:
            break
    conn.close()


if __name__ == "__main__":
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server.bind(("127.0.0.1", 8081))
    server.listen(5)
    print("RPC Server on port 8081...")
    try:
        while True:
            conn, addr = server.accept()
            threading.Thread(target=handle_client, args=(
                conn, addr), daemon=True).start()
    except KeyboardInterrupt:
        print("\nStopped")
    finally:
        server.close()
