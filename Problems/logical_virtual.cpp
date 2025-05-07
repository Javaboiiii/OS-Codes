#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

void paging() {
    cout << "\n=== Paging ===\n";
    int pageSize, numPages;
    cout << "Enter page size: ";
    cin >> pageSize;
    cout << "Enter number of pages: ";
    cin >> numPages;

    vector<int> pageTable(numPages);
    cout << "Enter frame number for each page:\n";
    for (int i = 0; i < numPages; i++) {
        cout << "Page " << i << ": ";
        cin >> pageTable[i];
    }

    int logicalAddress;
    cout << "Enter logical address: ";
    cin >> logicalAddress;

    int pageNumber = logicalAddress / pageSize;
    int offset = logicalAddress % pageSize;

    if (pageNumber >= numPages) {
        cout << "Invalid logical address!\n";
        return;
    }

    int frameNumber = pageTable[pageNumber];
    int physicalAddress = frameNumber * pageSize + offset;

    cout << "Physical Address: " << physicalAddress << "\n";
}

void segmentation() {
    cout << "\n=== Segmentation ===\n";
    int numSegments;
    cout << "Enter number of segments: ";
    cin >> numSegments;

    vector<int> base(numSegments), limit(numSegments);
    cout << "Enter base and limit for each segment:\n";
    for (int i = 0; i < numSegments; i++) {
        cout << "Segment " << i << " - Base: ";
        cin >> base[i];
        cout << "Segment " << i << " - Limit: ";
        cin >> limit[i];
    }

    int segmentNumber, offset;
    cout << "Enter logical address (segment_number offset): ";
    cin >> segmentNumber >> offset;

    if (segmentNumber >= numSegments || offset >= limit[segmentNumber]) {
        cout << "Invalid segment or offset!\n";
        return;
    }

    int physicalAddress = base[segmentNumber] + offset;
    cout << "Physical Address: " << physicalAddress << "\n";
}

int main() {
    paging();
    segmentation();
    return 0;
}

