#include <bits/stdc++.h>
using namespace std;

// 🧠 SJF (Preemptive) → Process with the shortest remaining burst time executes next
void sjfPreemptive(vector<int> bt, vector<int> at) {
    int n = bt.size();
    vector<int> rt = bt, wt(n), tat(n);
    int complete = 0, t = 0, minm = INT_MAX, shortest = 0, finish_time;
    bool check = false;

    while (complete != n) {
        // Find process with minimum remaining time among arrived processes
        for (int j = 0; j < n; j++) {
            if ((at[j] <= t) && (rt[j] < minm) && rt[j] > 0) {
                minm = rt[j];
                shortest = j;
                check = true;
            }
        }

        if (!check) { t++; continue; }

        rt[shortest]--;
        minm = rt[shortest] == 0 ? INT_MAX : rt[shortest];

        if (rt[shortest] == 0) {
            complete++;
            check = false;
            finish_time = t + 1;
            wt[shortest] = finish_time - bt[shortest] - at[shortest];
            if (wt[shortest] < 0) wt[shortest] = 0;
        }
        t++;
    }

    for (int i = 0; i < n; i++) tat[i] = bt[i] + wt[i];

    cout << "\n--- Shortest Job First (Preemptive) ---\n";
    cout << "P\tAT\tBT\tWT\tTAT\n";
    for (int i = 0; i < n; i++)
        cout << "P" << i + 1 << "\t" << at[i] << "\t" << bt[i] << "\t" 
             << wt[i] << "\t" << tat[i] << "\n";

    cout << "Average Waiting Time: " << accumulate(wt.begin(), wt.end(), 0.0) / n << endl;
    cout << "Average Turnaround Time: " << accumulate(tat.begin(), tat.end(), 0.0) / n << endl;
}

// 🧠 PRIORITY (Non-Preemptive) → Process with the highest priority executes first
void priorityNonPreemptive(vector<int> bt, vector<int> at, vector<int> priority) {
    int n = bt.size();
    vector<int> wt(n), tat(n);
    vector<int> remaining(n, 0), done(n, 0);
    int t = 0, completed = 0;

    while (completed != n) {
        int idx = -1, highest = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (at[i] <= t && !done[i] && priority[i] < highest) {
                highest = priority[i];
                idx = i;
            }
        }
        if (idx == -1) { t++; continue; }

        wt[idx] = t - at[idx];
        t += bt[idx];
        tat[idx] = wt[idx] + bt[idx];
        done[idx] = 1;
        completed++;
    }

    cout << "\n--- Priority Scheduling (Non-Preemptive) ---\n";
    cout << "P\tAT\tBT\tPr\tWT\tTAT\n";
    for (int i = 0; i < n; i++)
        cout << "P" << i + 1 << "\t" << at[i] << "\t" << bt[i] << "\t" << priority[i]
             << "\t" << wt[i] << "\t" << tat[i] << "\n";

    cout << "Average Waiting Time: " << accumulate(wt.begin(), wt.end(), 0.0) / n << endl;
    cout << "Average Turnaround Time: " << accumulate(tat.begin(), tat.end(), 0.0) / n << endl;
}

// 🧠 ROUND ROBIN (Preemptive) → Each process gets equal time quantum in cyclic order
void roundRobin(vector<int> bt, vector<int> at, int quantum) {
    int n = bt.size();
    vector<int> rt = bt, wt(n,0), tat(n,0);
    int t = 0, completed = 0;

    queue<int> q;
    vector<bool> inQueue(n, false);
    q.push(0); inQueue[0] = true;
    t = at[0];

    while (!q.empty()) {
        int i = q.front(); q.pop();
        inQueue[i] = false;

        if (rt[i] > quantum) {
            t += quantum;
            rt[i] -= quantum;
        } else {
            t += rt[i];
            wt[i] = t - bt[i] - at[i];
            tat[i] = wt[i] + bt[i];
            rt[i] = 0;
            completed++;
        }

        // Enqueue new processes that have arrived
        for (int j = 0; j < n; j++) {
            if (at[j] <= t && rt[j] > 0 && !inQueue[j]) {
                q.push(j);
                inQueue[j] = true;
            }
        }
        if (rt[i] > 0) q.push(i);
    }

    cout << "\n--- Round Robin (Preemptive) ---\n";
    cout << "P\tAT\tBT\tWT\tTAT\n";
    for (int i = 0; i < n; i++)
        cout << "P" << i + 1 << "\t" << at[i] << "\t" << bt[i] << "\t" 
             << wt[i] << "\t" << tat[i] << "\n";

    cout << "Average Waiting Time: " << accumulate(wt.begin(), wt.end(), 0.0) / n << endl;
    cout << "Average Turnaround Time: " << accumulate(tat.begin(), tat.end(), 0.0) / n << endl;
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<int> bt(n), at(n), priority(n);
    for (int i = 0; i < n; i++) {
        cout << "Enter Arrival Time, Burst Time, and Priority for P" << i + 1 << ": ";
        cin >> at[i] >> bt[i] >> priority[i];
    }

    int quantum;
    cout << "Enter Time Quantum for Round Robin: ";
    cin >> quantum;

    sjfPreemptive(bt, at);
    priorityNonPreemptive(bt, at, priority);
    roundRobin(bt, at, quantum);

    return 0;
}


/*
Sample run

Enter number of processes: 4
Enter Arrival Time, Burst Time, and Priority for P1: 0 8 2
Enter Arrival Time, Burst Time, and Priority for P2: 1 4 1
Enter Arrival Time, Burst Time, and Priority for P3: 2 9 3
Enter Arrival Time, Burst Time, and Priority for P4: 3 5 2
Enter Time Quantum for Round Robin: 3
*/