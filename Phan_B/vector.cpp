#ifndef My_vector
#define My_vector

#include <iostream>
using namespace std;

template <class T>
class Vector {
private:
    T *V;
    int cap, num;
public:
    Vector() {
        cap = 0;
        num = 0;
        V = new T[1];
    }
    Vector(int n, T value) {
        cap = n;
        num = n;
        V = new T[n];
        for(int i = 0; i < n; i++) {
            V[i] = value;
        }
    }
    Vector(int n) {
        cap = n;
        num = n;
        V = new T[n];
        for(int i = 0; i < n; ++i) {
            V[i] = 0;
        }
    }
    ~Vector() {
        if(V != 0) {
            delete[] V;
        }
    }
    int size() {
        return num;
    }
    bool empty() {
        return num == 0;
    }
    int capacity() {
        return cap;
    }
    void pop_back() {
        if(num > 0){
            num--;
        }
        else{
            cout << "Khong co phan tu nao!";
        }
    }
    T &back() {
        return V[num - 1];
    }
    T &front() {
        return V[0];
    }
    void extend(int newCap) {
        if(newCap < cap) {
            return;
        }
        cap = newCap;
        T *tmp = new T[cap];
        for(int i = 0; i < num; i++) {
            tmp[i] = V[i];
        }
        if(V) delete[] V;
        V = tmp;
    }
    void push_back(T value) {
        if(num == cap) {
            extend(cap * 2);
        }
        V[num] = value;
        ++num;
    }
    void insert(int pos, T x) {
        if(num == cap) {
            extend(cap * 2);
        }
        for(int i = num - 1; i >= pos; i--) {
            V[i+1] = V[i];
        }
        V[pos] = x;
        ++num;
    }
    void erase(int pos)  {
        if(pos < 0 || pos >= size()) {
            cout << "Chi so khong hop le!";
            return;
        }
        for(; pos < num; pos++) {
            V[pos] = V[pos + 1];
        }
        num--;
    }
    void swap(Vector &x) {
        Vector tmp = *this;
        *this = x;
        x = tmp;
    }

    void clear() {
        for(int i = 0; i < num; ++i) {
            V[i] = 0;
        }
    }

    T &operator [](int i) {
        return V[i];
    }

    Vector &operator =(Vector<T> b) {
        num = b.num;
        cap = b.cap;
        if(cap != 0) {
            V = new T[cap];
            for(int i = 0; i < num; i++) {
                V[i] = b.V[i];
            }
        }
        else {
            V = nullptr;
        }
        return *this;
    }
    typedef T *iterator;
    iterator begin() {
        return V;
    }
    iterator end() {
        return V + num;
    }

    typedef T *reverse_iterator;
    reverse_iterator rbegin() {
        return V + num - 1;
    }

    reverse_iterator rend() {
        return V - 1;
    }
};

#endif
