
#include <vector>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <iomanip>
using namespace std;

void printMatrix(const vector<vector<int>>& mat, const vector<int>& ref) {
    cout << "\n=== Page Replacement Matrix ===\n   ";
    for (int r : ref)
        cout << setw(3) << r;
    cout << "\n";

    for (int i = 0; i < mat.size(); ++i) {
        cout << "F" << i + 1 << " ";
        for (int j = 0; j < mat[0].size(); ++j) {
            if (mat[i][j] == -1) cout << "  -";
            else cout << setw(3) << mat[i][j];
        }
        cout << "\n";
    }
}

void FIFO(vector<int> pages, int frames) {
    cout << "\n=== FIFO Page Replacement ===\n";
    queue<int> q;
    unordered_map<int, bool> inMemory;
    vector<vector<int>> matrix(frames, vector<int>(pages.size(), -1));

    int pageFaults = 0, idx = 0;

    for (int i = 0; i < pages.size(); i++) {
        if (!inMemory[pages[i]]) {
            pageFaults++;
            if (q.size() == frames) {
                int out = q.front(); q.pop();
                inMemory[out] = false;
                for (int j = 0; j < frames; j++)
                    if (matrix[j][i - 1] == out) { matrix[j][i] = pages[i]; break; }
            } else {
                for (int j = 0; j < frames; j++) {
                    if (matrix[j][i] == -1 || (i > 0 && matrix[j][i - 1] == -1)) {
                        matrix[j][i] = pages[i];
                        break;
                    }
                }
            }
            q.push(pages[i]);
            inMemory[pages[i]] = true;
        }

        for (int j = 0; j < frames; j++) {
            if (i > 0 && matrix[j][i] == -1)
                matrix[j][i] = matrix[j][i - 1];
        }
    }

    printMatrix(matrix, pages);
    cout << "Total Page Faults (FIFO): " << pageFaults << "\n";
}

void LRU(vector<int> pages, int frames) {
    cout << "\n=== LRU Page Replacement ===\n";
    vector<vector<int>> matrix(frames, vector<int>(pages.size(), -1));
    unordered_map<int, int> lastUsed;

    vector<int> mem;
    int pageFaults = 0;

    for (int i = 0; i < pages.size(); i++) {
        if (find(mem.begin(), mem.end(), pages[i]) == mem.end()) {
            pageFaults++;
            if (mem.size() == frames) {
                int lru = mem[0];
                for (int p : mem)
                    if (lastUsed[p] < lastUsed[lru]) lru = p;

                replace(mem.begin(), mem.end(), lru, pages[i]);
            } else mem.push_back(pages[i]);
        }

        lastUsed[pages[i]] = i;

        for (int j = 0; j < frames; j++) {
            if (j < mem.size())
                matrix[j][i] = mem[j];
            else if (i > 0)
                matrix[j][i] = matrix[j][i - 1];
        }
    }

    printMatrix(matrix, pages);
    cout << "Total Page Faults (LRU): " << pageFaults << "\n";
}

void Optimal(vector<int> pages, int frames) {
    cout << "\n=== Optimal Page Replacement ===\n";
    vector<vector<int>> matrix(frames, vector<int>(pages.size(), -1));
    vector<int> mem;
    int pageFaults = 0;

    for (int i = 0; i < pages.size(); i++) {
        if (find(mem.begin(), mem.end(), pages[i]) == mem.end()) {
            pageFaults++;
            if (mem.size() == frames) {
                int index = -1, farthest = i;
                for (int j = 0; j < mem.size(); j++) {
                    int k;
                    for (k = i + 1; k < pages.size(); k++)
                        if (pages[k] == mem[j])
                            break;

                    if (k > farthest) {
                        farthest = k;
                        index = j;
                    }
                }

                if (index == -1) mem[0] = pages[i];
                else mem[index] = pages[i];
            } else mem.push_back(pages[i]);
        }

        for (int j = 0; j < frames; j++) {
            if (j < mem.size())
                matrix[j][i] = mem[j];
            else if (i > 0)
                matrix[j][i] = matrix[j][i - 1];
        }
    }

    printMatrix(matrix, pages);
    cout << "Total Page Faults (Optimal): " << pageFaults << "\n";
}

int main() {
    int n, f;
    cout << "Enter number of pages: ";
    cin >> n;

    vector<int> pages(n);
    cout << "Enter page reference string: ";
    for (int i = 0; i < n; i++) cin >> pages[i];

    cout << "Enter number of frames: ";
    cin >> f;

    FIFO(pages, f);
    LRU(pages, f);
    Optimal(pages, f);

    return 0;
}

