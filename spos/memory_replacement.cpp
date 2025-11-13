#include <bits/stdc++.h>
using namespace std;

// 🧠 FIRST FIT → Allocate to the first block large enough to hold the process
void firstFit(vector<int> blocks, vector<int> process) {
    vector<int> allocation(process.size(), -1);
    for (int i = 0; i < process.size(); i++) {
        for (int j = 0; j < blocks.size(); j++) {
            if (blocks[j] >= process[i]) {     // first block that fits
                allocation[i] = j;
                blocks[j] -= process[i];       // reduce block size
                break;
            }
        }
    }
    cout << "\n--- First Fit ---\n";
    for (int i = 0; i < process.size(); i++) {
        cout << "Process " << i + 1 << " (" << process[i] << ") -> ";
        if (allocation[i] != -1)
            cout << "Block " << allocation[i] + 1 << "\n";
        else
            cout << "Not Allocated\n";
    }
}

// 🧠 BEST FIT → Allocate to the smallest block that can fit the process
void bestFit(vector<int> blocks, vector<int> process) {
    vector<int> allocation(process.size(), -1);
    for (int i = 0; i < process.size(); i++) {
        int bestIdx = -1;
        for (int j = 0; j < blocks.size(); j++) {
            if (blocks[j] >= process[i]) {
                if (bestIdx == -1 || blocks[j] < blocks[bestIdx])
                    bestIdx = j;               // choose smallest fitting block
            }
        }
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blocks[bestIdx] -= process[i];
        }
    }
    cout << "\n--- Best Fit ---\n";
    for (int i = 0; i < process.size(); i++) {
        cout << "Process " << i + 1 << " (" << process[i] << ") -> ";
        if (allocation[i] != -1)
            cout << "Block " << allocation[i] + 1 << "\n";
        else
            cout << "Not Allocated\n";
    }
}

// 🧠 NEXT FIT → Similar to First Fit, but starts searching from the last allocated position
void nextFit(vector<int> blocks, vector<int> process) {
    vector<int> allocation(process.size(), -1);
    int lastPos = 0;                           // remember last allocated block
    for (int i = 0; i < process.size(); i++) {
        int count = 0;
        bool allocated = false;
        while (count < blocks.size()) {
            int j = (lastPos + count) % blocks.size(); // wrap around search
            if (blocks[j] >= process[i]) {
                allocation[i] = j;
                blocks[j] -= process[i];
                lastPos = j;                   // update last position
                allocated = true;
                break;
            }
            count++;
        }
    }
    cout << "\n--- Next Fit ---\n";
    for (int i = 0; i < process.size(); i++) {
        cout << "Process " << i + 1 << " (" << process[i] << ") -> ";
        if (allocation[i] != -1)
            cout << "Block " << allocation[i] + 1 << "\n";
        else
            cout << "Not Allocated\n";
    }
}

// 🧠 WORST FIT → Allocate to the largest block available to minimize leftover fragmentation
void worstFit(vector<int> blocks, vector<int> process) {
    vector<int> allocation(process.size(), -1);
    for (int i = 0; i < process.size(); i++) {
        int worstIdx = -1;
        for (int j = 0; j < blocks.size(); j++) {
            if (blocks[j] >= process[i]) {
                if (worstIdx == -1 || blocks[j] > blocks[worstIdx])
                    worstIdx = j;              // choose largest fitting block
            }
        }
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            blocks[worstIdx] -= process[i];
        }
    }
    cout << "\n--- Worst Fit ---\n";
    for (int i = 0; i < process.size(); i++) {
        cout << "Process " << i + 1 << " (" << process[i] << ") -> ";
        if (allocation[i] != -1)
            cout << "Block " << allocation[i] + 1 << "\n";
        else
            cout << "Not Allocated\n";
    }
}

int main() {
    int nb, np;
    cout << "Enter number of memory blocks: ";
    cin >> nb;
    vector<int> blocks(nb);
    cout << "Enter block sizes:\n";
    for (int i = 0; i < nb; i++) cin >> blocks[i];

    cout << "Enter number of processes: ";
    cin >> np;
    vector<int> process(np);
    cout << "Enter process sizes:\n";
    for (int i = 0; i < np; i++) cin >> process[i];

    bestFit(blocks, process);
    firstFit(blocks, process);
    nextFit(blocks, process);
    worstFit(blocks, process);

    return 0;
}


/*
Sample run

Enter number of memory blocks: 5
Enter block sizes:
100 500 200 300 600
Enter number of processes: 4
Enter process sizes:
212 417 112 426

--- Best Fit ---
Process 1 (212) -> Block 3
Process 2 (417) -> Block 5
Process 3 (112) -> Block 1
Process 4 (426) -> Not Allocated

--- First Fit ---
Process 1 (212) -> Block 2
Process 2 (417) -> Block 5
Process 3 (112) -> Block 3
Process 4 (426) -> Not Allocated

--- Next Fit ---
Process 1 (212) -> Block 2
Process 2 (417) -> Block 5
Process 3 (112) -> Block 3
Process 4 (426) -> Not Allocated

--- Worst Fit ---
Process 1 (212) -> Block 5
Process 2 (417) -> Block 2
Process 3 (112) -> Block 5
Process 4 (426) -> Not Allocated

*/
