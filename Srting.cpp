﻿#include <iostream>

using namespace std;

class String {
private:
    char* _str = nullptr;
    int _count;
    int _capacity;

public:
    String(const char* str) {
        set_str(str);
    }

    String(const String& other) {
        _capacity = other._capacity;
        _count = other._count;

        _str = new char[_capacity];
        strcpy_s(_str, _capacity, other._str);
    }

    String(String&& other) noexcept {
        _capacity = other._capacity;
        _count = other._count;
        _str = other._str;

        other._str = nullptr;
        other._capacity = 0;
        other._count = 0;
    }

    ~String() {
        erase_str();
    }

    int count() {
        return _count;
    }

    int capacity() {
        return _capacity;
    }

    void print() {
        cout << _str << endl;
    }

    void set_str(const char* str) {
        erase_str();

        _count = strlen(str);
        _capacity = _count * 2;
        _str = new char[_capacity + 1];

        strcpy_s(_str, _capacity, str);
    }

    void append(char s) {
        if (_count + 1 >= _capacity)
            resize();

        _str[_count] = s;
        _str[++_count] = '\0';
    }

    void append(const char* s) {
        int len = strlen(s);
    }

    void set_symbol(char sym, int index) {
        if (!check_range(index)) return;

        _str[index] = sym;
    }

    String& operator+= (char s) {
        append(s);
        return *this;
    }

    String& operator-= (char s) {
        for (size_t i = 0; i < _count; i++)
        {
            if (_str[i] == s)
                _str[i] = '_';
        }

        return *this;
    }

    char& operator[] (int index) {
        if (!check_range(index))
            exit(1);

        return _str[index];
    }

    friend ostream& operator<< (ostream& out, String& s) {
        out << s._str;
        return out;
    }

private:
    void resize() {
        _capacity *= 2;
        char* tmp_str = new char[_capacity + 1];

        strcpy_s(tmp_str, _capacity, _str);
        erase_str();

        _str = tmp_str;
    }

    bool check_range(int index) {
        return index >= 0 && index < _count;
    }

    void erase_str() {
        if (_str != nullptr)
            delete[] _str;
    }
};

int main() {
    String* str = new String(String("Hello world!"));
    
    String str2("My string");
    String str3 = move(str2);

    cout << "str3: " << str3 << endl;

    str3[3] = 'H';
    cout << "str3 at index 3: " << str3[3] << endl;
    cout << "str3: " << str3 << endl;

    cout << "symbol: " << (*str)[0] << endl;

    delete str;
    return 0;
}
