import random
import time
print("Enter the number of processes")
n = int(input())
processes = []
print("Enter the processes in ring order")
processes = list(map(int, input().split()))
failed_node = max(processes)
active_pro = [p for p in processes if p != failed_node]
det_fail_node = random.choice(active_pro)

print(f"\n The process has {failed_node} (Co-ordinator)has failed.\n")
print(f"The process {det_fail_node} has detected the failure.\n")
current_index = processes.index(det_fail_node)
election_message = [det_fail_node]
print(
    f"Process {det_fail_node} sends election message {election_message} to next process.\n")
while True:
    current_index = (current_index + 1) % n
    curr_process = processes[current_index]
    if curr_process == failed_node:
        print(f"Process {curr_process} is failed. Skipping to next process.")
        continue

    print(
        f"process {curr_process} received election message with IDs{election_message}.")
    time.sleep(1)
    if curr_process not in election_message:
        election_message.append(curr_process)
        print(
            f"process {curr_process} adds its ID to election message. New message: {election_message}")
    if curr_process == det_fail_node:
        print(
            f"\n Election message has returned to initiator {det_fail_node}.")
        break

leader = max(election_message)
print(f"\n The new leader is {leader}.")
