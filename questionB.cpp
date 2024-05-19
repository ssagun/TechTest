#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Version {

private:
    static vector<int> split(const string &version) {
        vector<int> result;
        stringstream ss(version);
        string item;

        while (getline(ss, item, '.')) {
            if(item == "") result.push_back(0);
            result.push_back(stoi(item));
        }

        return result;
    }

public:
    static int compare(const string &version1, const string &version2) {
        vector<int> v1 = split(version1);
        vector<int> v2 = split(version2);

        for (size_t i = 0; i < max(v1.size(), v2.size()); ++i) {
            int num1 = (i < v1.size()) ? v1[i] : 0;
            int num2 = (i < v2.size()) ? v2[i] : 0;

            if (num1 < num2) return -1;
            if (num1 > num2) return 1;
        }

        return 0;
    }
};

void runTestCases() {
    struct TestCase {
        string version1;
        string version2;
        int expected;
    };

    vector<TestCase> testCases = {
        {"1.0", "1.0", 0},
        {"1.0", "1.1", -1},
        {"1.1", "1.0", 1},
        {"2.0", "1.1", 1},
        {"1.0.1", "1.0", 1},
        {"1.0", "1.0.1", -1},
        {"1.2.3", "1.2.3", 0},
        {"1.2.3", "1.2.3.4", -1},
        {"1.2.3.4", "1.2.3", 1},
        {"1.10", "1.2", 1},
        {"1.2", "1.10", -1},
        {"1.0.0", "1.0", 0},
        {"1.0", "1..0", 0},
        {"1.0.0.0", "1.0.0.1", -1},
        {"1.0.0.1", "1.0.0.0", 1},
        {"1.0.0", "1.0.0.0.0", 0},
        {"1.0.1", "1.0.0.9", 1},
        {"1.0.0.9", "1.0.1", -1}
    };

    for (const auto& testCase : testCases) {
        int result = Version::compare(testCase.version1, testCase.version2);
        cout << "Comparing " << testCase.version1 << " and " << testCase.version2 << ": ";
        if (result == testCase.expected) {
            cout << "PASS";
        } else {
            cout << "FAIL (expected " << testCase.expected << ", got " << result << ")";
        }
        cout << endl;
    }
}

int main() {
    runTestCases();
    return 0;
}
