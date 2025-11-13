#include <bits/stdc++.h>
using namespace std;

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
    unordered_map<int, int> recent;  // page → most recent use index
    int pageFaults = 0;

    for (int i = 0; i < n; i++) {
        int page = pages[i];

        // If page not in frames → page fault
        if (find(frames.begin(), frames.end(), page) == frames.end()) {
            if (frames.size() < capacity)
                frames.push_back(page);
            else {
                // Find least recently used page
                int lruPage = frames[0], lruIndex = recent[lruPage];
                for (int f : frames)
                    if (recent[f] < lruIndex) {
                        lruPage = f;
                        lruIndex = recent[f];
                    }
                // Replace it
                replace(frames.begin(), frames.end(), lruPage, page);
            }
            cout<< "Page fault occured, new count is: "<<(++pageFaults)<<"\n";
        }

        // Update recent use for this page
        recent[page] = i;

        // Print current frame state
        cout << "After page " << page << " -> [ ";
        for (int f : frames) cout << f << " ";
        cout << "]" << endl;
    }

    cout << "\nTotal Page Faults: " << pageFaults << endl;
    return 0;
}
