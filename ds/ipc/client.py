import socket

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(("127.0.0.1", 8080))

print("Connected to server")
user = input("Enter account name: ")

while True:
    cmd = input("Enter command (BAL/DEP/WIT amount) or exit: ").split()
    if cmd[0].lower() == "exit":
        break

    if len(cmd) == 1:
        msg = f"{user} {cmd[0].upper()} 0"
    else:
        msg = f"{user} {cmd[0].upper()} {cmd[1]}"

    client.send(msg.encode())
    response = client.recv(1024).decode()
    print(response)

client.close()
print("Disconnected")
