import random
import time

print("Enter the number of processes")
n = int(input())
processes =  []
print("Enter the processes")
processes = list(map(int,input().split()))
failed_node = max(processes)
active_pro = [p for p in processes if p != failed_node]

if not active_pro:
	print("No active process left")
	exit()

det_ran_fail = random.choice(active_pro)
print(f"\n The process has {failed_node} (Co-ordinator)has failed.\n")
print(f"The process {det_ran_fail} has detected the failure.\n")
curr_initiator = det_ran_fail
leader = -1
while True:
	high_pro = []
	for p  in active_pro:
		if  p >  curr_initiator:
			high_pro.append(p)

	if not high_pro:
		leader = curr_initiator
		print(f"Process {curr_initiator} sends election, but gets no 'OK' response.")
		break

	else:
		print(f"Process {curr_initiator} sends ELECTION to: {high_pro}")
		time.sleep(1)
		print(f"Process {high_pro} responds ok")
		print(f"process {curr_initiator} gives up its election")

		curr_initiator = max(high_pro)
		print(f"Process {curr_initiator} starts its *own* election.\n" )
		time.sleep(1)

print(f"\n -- Process {leader} is a new cordinator!---")
print(f"It sends 'coordinator' message to all other active process" )
for p in  active_pro:
	if p!= leader:
		print(f"-> sending co-ordinator message to process {p}")
