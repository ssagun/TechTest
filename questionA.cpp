#include <iostream>
using namespace std;

bool linesOverlap(int x1, int x2, int x3, int x4) {
    // Ensure x1 is less than x2 and x3 is less than x4
    if (x1 > x2) swap(x1, x2);
    if (x3 > x4) swap(x3, x4);

    // Check if the lines overlap
    return (x1 <= x4 && x3 <= x2);
}

int main() {
    int x1, x2, x3, x4;
    cout << "Enter the coordinates of the first line (x1 x2): ";
    cin >> x1 >> x2;
    cout << "Enter the coordinates of the second line (x3 x4): ";
    cin >> x3 >> x4;

    if (linesOverlap(x1, x2, x3, x4)) {
        cout << "The lines overlap." << endl;
    } else {
        cout << "The lines do not overlap." << endl;
    }

    return 0;
}
