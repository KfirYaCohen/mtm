#include <vector>
#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::shared_ptr;

class BadInput : public std::exception {};

template <class T>
std::vector<T> slice(std::vector<T> vec, int start, int step, int stop) {
    if (start < 0 || (unsigned)start >= vec.size() || stop < 0 || (unsigned)stop > vec.size() || step <= 0) {
        throw BadInput();
    }

    std::vector<T> newVector = std::vector<T>();
    if (start >= stop) {
        return newVector;
    }
    for (int i = start; i < stop; i += step) {
        newVector.push_back(vec[i]);
    }
    return newVector;
}

class A {
   public:
    std::vector<shared_ptr<int>> values;
    void add(int x) { values.push_back(shared_ptr<int>(new int(x))); }
};
int main() {
    A a, sliced;
    a.add(0);
    a.add(1);
    a.add(2);
    a.add(3);
    a.add(4);
    a.add(5);
    sliced.values = slice(a.values, 1, 1, 4);
    *(sliced.values[0]) = 800;
    std::cout << *(a.values[1]) << std::endl;
    return 0;
}


