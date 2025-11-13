class LamportClock:
    def __init__(self):
        self.time = 0

    def send(self):
        self.time += 1
        return self.time

    def receive(self, received_time):
        self.time = max(self.time, received_time) + 1
        return self.time


p1 = LamportClock()
p2 = LamportClock()
p3 = LamportClock()

print("Lamport Clock\n")

print("P1 sends message to P2")
ts1 = p1.send()
print(f"  P1 sends with timestamp: {ts1}")
ts2 = p2.receive(ts1)
print(f"  P2 receives, updates to: {ts2}\n")

print("P2 sends message to P3")
ts2 = p2.send()
print(f"  P2 sends with timestamp: {ts2}")
ts3 = p3.receive(ts2)
print(f"  P3 receives, updates to: {ts3}\n")

print("P3 sends message to P1")
ts3 = p3.send()
print(f"  P3 sends with timestamp: {ts3}")
ts1 = p1.receive(ts3)
print(f"  P1 receives, updates to: {ts1}\n")

print("Final timestamps:")
print(f"  P1: {p1.time}")
print(f"  P2: {p2.time}")
print(f"  P3: {p3.time}")
