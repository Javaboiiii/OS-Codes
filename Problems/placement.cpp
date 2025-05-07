#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

void printBlockMatrix(const vector<int>& originalBlock, const vector<int>& remainingBlock, const string& strategy) {
    cout << "\n=== " << strategy << " Block Allocation Matrix ===\n";
    cout << left << setw(15) << "Block No" << setw(20) << "Original Size" << "Remaining Size\n";
    for (int i = 0; i < originalBlock.size(); i++) {
        cout << left << setw(15) << i + 1 << setw(20) << originalBlock[i] << remainingBlock[i] << endl;
    }
}

void printAllocationMatrix(const vector<int>& allocation, const vector<int>& processSize) {
    cout << left << "\nProcess Allocation:\n";
    cout << left << setw(15) << "Process No" << setw(20) << "Process Size" << "Allocated Block\n";
    for (int i = 0; i < allocation.size(); i++) {
        cout << left << setw(15) << i + 1 << setw(20) << processSize[i];
        if (allocation[i] != -1)
            cout << allocation[i] + 1;
        else
            cout << "Not Allocated";
        cout << endl;
    }
}

void firstFit(const vector<int>& originalBlockSize, const vector<int>& processSize) {
    vector<int> blockSize = originalBlockSize;
    vector<int> allocation(processSize.size(), -1);

    for (int i = 0; i < processSize.size(); i++) {
        for (int j = 0; j < blockSize.size(); j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }

    cout << "\n======== First Fit Strategy ========";
    printAllocationMatrix(allocation, processSize);
    printBlockMatrix(originalBlockSize, blockSize, "First Fit");
}

void nextFit(const vector<int>& originalBlockSize, const vector<int>& processSize) {
    vector<int> blockSize = originalBlockSize;
    vector<int> allocation(processSize.size(), -1);
    int j = 0;

    for (int i = 0; i < processSize.size(); i++) {
        int count = 0;
        while (count < blockSize.size()) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
            j = (j + 1) % blockSize.size();
            count++;
        }
    }

    cout << "\n======== Next Fit Strategy ========";
    printAllocationMatrix(allocation, processSize);
    printBlockMatrix(originalBlockSize, blockSize, "Next Fit");
}

void bestFit(const vector<int>& originalBlockSize, const vector<int>& processSize) {
    vector<int> blockSize = originalBlockSize;
    vector<int> allocation(processSize.size(), -1);

    for (int i = 0; i < processSize.size(); i++) {
        int bestIdx = -1;
        for (int j = 0; j < blockSize.size(); j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx])
                    bestIdx = j;
            }
        }

        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }

    cout << "\n======== Best Fit Strategy ========";
    printAllocationMatrix(allocation, processSize);
    printBlockMatrix(originalBlockSize, blockSize, "Best Fit");
}

void worstFit(const vector<int>& originalBlockSize, const vector<int>& processSize) {
    vector<int> blockSize = originalBlockSize;
    vector<int> allocation(processSize.size(), -1);

    for (int i = 0; i < processSize.size(); i++) {
        int worstIdx = -1;
        for (int j = 0; j < blockSize.size(); j++) {
            if (blockSize[j] >= processSize[i]) {
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx])
                    worstIdx = j;
            }
        }

        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            blockSize[worstIdx] -= processSize[i];
        }
    }

    cout << "\n======== Worst Fit Strategy ========";
    printAllocationMatrix(allocation, processSize);
    printBlockMatrix(originalBlockSize, blockSize, "Worst Fit");
}

int main() {
    vector<int> blockSize = {100, 500, 200, 300, 600};
    vector<int> processSize = {212, 417, 112, 426};

    firstFit(blockSize, processSize);
    nextFit(blockSize, processSize);
    bestFit(blockSize, processSize);
    worstFit(blockSize, processSize);

    return 0;
}
