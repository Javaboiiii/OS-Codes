#include <iostream>
#include <cmath>
#include <map>
#include <vector>
#include <iomanip>
using namespace std;

int nextPowerOf2(int n) {
    return pow(2, ceil(log2(n)));
}

class BuddySystem {
private:
    int totalSize;
    map<int, vector<int>> freeList;

public:
    BuddySystem(int size) {
        totalSize = nextPowerOf2(size);
        freeList[totalSize].push_back(0);
    }

    void allocate(int processID, int size, map<int, pair<int, int>>& allocation) {
        int blockSize = nextPowerOf2(size);
        bool allocated = false;

        for (int s = blockSize; s <= totalSize; s *= 2) {
            if (!freeList[s].empty()) {
                int startAddr = freeList[s].back();
                freeList[s].pop_back();

                while (s > blockSize) {
                    s /= 2;
                    freeList[s].push_back(startAddr + s);
                }

                allocation[processID] = {startAddr, blockSize};
                allocated = true;
                break;
            }
        }

        if (!allocated) {
            cout << "Process " << processID << " of size " << size << " couldn't be allocated\n";
        }
    }

    void printAllocationMatrix(map<int, pair<int, int>>& allocation) {
        cout << "\n=== Buddy System Allocation Matrix ===\n";
        cout << left << setw(15) << "Process ID" << setw(15) << "Start Addr" << "Block Size\n";
        for (auto& entry : allocation) {
            cout << left << setw(15) << entry.first << setw(15) << entry.second.first << entry.second.second << "\n";
        }
    }

    void printFreeListMatrix() {
        cout << "\n=== Free List Matrix ===\n";
        cout << left << setw(15) << "Block Size" << "Free Start Addresses\n";
        for (auto& block : freeList) {
            cout << left << setw(15) << block.first;
            for (auto addr : block.second)
                cout << addr << " ";
            cout << "\n";
        }
    }
};

int main() {
    int memorySize = 1024;
    BuddySystem buddy(memorySize);

    vector<int> processes = {100, 50, 200, 300, 400, 500};
    map<int, pair<int, int>> allocation;

    for (int i = 0; i < processes.size(); i++) {
        buddy.allocate(i + 1, processes[i], allocation);
    }

    buddy.printAllocationMatrix(allocation);
    buddy.printFreeListMatrix();

    return 0;
}
