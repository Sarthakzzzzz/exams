import socket
import json

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(("127.0.0.1", 8081))

user = input("Account: ")

while True:
    cmd = input("Command (BAL/DEP/WIT amount): ").split()
    if cmd[0].lower() == "exit":
        break

    request = {
        "method": cmd[0].upper(),
        "user": user,
        "amount": int(cmd[1]) if len(cmd) > 1 else 0
    }

    client.send(json.dumps(request).encode())
    result = json.loads(client.recv(1024).decode())

    if "error" in result:
        print(f"Error: {result['error']}")
    else:
        print(f"Balance: ${result['balance']}")

client.close()
