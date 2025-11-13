#include <bits/stdc++.h>
using namespace std;

int predictNextUse(const vector<int>& pages, const vector<int>& frames, int currentIndex) {
    int farthest = currentIndex, index = -1;

    for (int i = 0; i < frames.size(); i++) {
        int nextUse = INT_MAX;
        for (int j = currentIndex + 1; j < pages.size(); j++) {
            if (frames[i] == pages[j]) {
                nextUse = j;
                break;
            }
        }
        if (nextUse > farthest) {
            farthest = nextUse;
            index = i;
        }
    }
    return (index == -1) ? 0 : index;
}

int main() {
    int n, capacity;
    cout << "Enter number of pages: ";
    cin >> n;

    vector<int> pages(n);
    cout << "Enter page reference string:\n";
    for (int i = 0; i < n; i++) cin >> pages[i];

    cout << "Enter number of frames: ";
    cin >> capacity;

    vector<int> frames;
    int pageFaults = 0;

    for (int i = 0; i < n; i++) {
        int page = pages[i];

        // Page already present
        if (find(frames.begin(), frames.end(), page) != frames.end()) {
            cout << "After page " << page << " -> [ ";
            for (int f : frames) cout << f << " ";
            cout << "] (No Fault)\n";
            continue;
        }

        // Page not present (Page Fault)
        if (frames.size() < capacity)
            frames.push_back(page);
        else {
            int victim = predictNextUse(pages, frames, i);
            frames[victim] = page;
        }

        pageFaults++;
        cout << "After page " << page << " -> [ ";
        for (int f : frames) cout << f << " ";
        cout << "] (Page Fault)\n";
    }

    cout << "\nTotal Page Faults: " << pageFaults << endl;
    return 0;
}
