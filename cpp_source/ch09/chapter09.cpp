#include <iostream>
#include <vector>
#include <list>
#include <deque>

using std::vector;
using std::list;
using std::deque;



void q_9_2() {
    list<deque<int>> l;
}

bool q_9_3(vector<int>::const_iterator beg, vector<int>::const_iterator end, const int val) {
    while (beg != end) {
        if (*beg++ == val) {
            return true;
        }
    }
    return false;
}

vector<int>::const_iterator q_9_4(vector<int>::const_iterator beg, vector<int>::const_iterator end, const int val) {
    while (beg != end) {
        if (*beg == val) {
            break;
        }
        ++beg;
    }
    return beg;
}

int main(int argc, char **argv) {
    vector<int> vec{1, 2, 3, 4, 5};
    auto flag = q_9_3(vec.begin(), vec.end(), 1);
    std::cout << flag << std::endl;
    return 0;
}
