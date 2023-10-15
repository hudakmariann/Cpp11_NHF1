#include <iostream>
#include <cstring>
#include <cctype>
#include "mystring.h"

MyString::MyString() {
    size = 0;
    refcount_  = new int{1};
    str = new char[1];
    str[0] = '\0';
}

MyString::MyString(char const * s) {
if (s){
    refcount_  = new int{1};
    size = strlen(s);
    str = new char[size + 1];
    strcpy(str, s);
    }
else
    refcount_ = nullptr;
}

//copy ctr
MyString::MyString(const MyString& masik) : refcount_{masik.refcount_} { //ha ertek szerint lenne adadva a parameter, akkor a masolo kontruktor hivodna, de azt meg pont itt definialjuk epp. Ezert referencia kell
    if (masik.str){
        size = masik.size;
        str = new char[size + 1];
        strcpy(str, masik.str);
        ++ *refcount_;
    }
}


//copy =
MyString& MyString::operator=(const MyString& masik) {
    if(this != &masik) {            // (*)
        delete[] str;                   // régi felszabadítása
        size = masik.size;
        str = new char[size + 1];       // új hely foglalása
        strcpy(str, masik.str);     // sztring másolása
    }
    return *this;                       // magyarázat nemsokára
}



//move ctr
MyString::MyString(MyString && the_other) noexcept {
    size = the_other.size;
    the_other.size = 0;
    str = the_other.str;    // elveszi a tömböt
    the_other.str = nullptr;
}



MyString& MyString::operator=(MyString && rhs) noexcept {
    if (this != &rhs) {
        delete[] str;
        size = rhs.size;
        rhs.size = 0;
        str = rhs.str;    // elveszi a tömböt
        rhs.str = nullptr;
    }
    return *this;
}



MyString::~MyString() {
    if(str) {
    -- *refcount_;
            if (*refcount_ == 0) {
                delete refcount_;
                delete str;
            }
    }

}


MyString MyString::operator+(MyString const& rhs) const {
    MyString uj;
    delete[] uj.str;
    uj.size = size + rhs.size;
    uj.str = new char[uj.size + 1];
    strcpy(uj.str, str);
    strcat(uj.str, rhs.str);
    return uj;
}

MyString& MyString::operator+=(MyString const& rhs) {
    return (*this = *this + rhs);
}

MyString& MyString::operator+=(char rhs) {
    /*int len = strlen(str);
    str[len] = rhs;
    str[len+1] = '\0';
    return *this;*/

    // nem a leghatékonyabb megvalósítás
    char tomb[2] = {rhs, '\0'};
    return (*this = *this + MyString(tomb));
}

int MyString::length() const {
    return strlen(str);
}

char& MyString::operator[](int i) {
     if(i < 0 || i >= size)
        throw std::out_of_range("String: index out of range");
    return str[i];
}

char MyString::operator[](int i) const {
    if(i < 0 || i >= size)
        throw std::out_of_range("String: index out of range");

    return str[i];
}



std::ostream& operator<<(std::ostream& os, MyString const& rhs) {
    os << rhs.get_str();
    return os;
}

std::istream& operator>>(std::istream& is, MyString& rhs) {
    char c;
    MyString masik;
    while(is.get(c) && !isspace(c))
        masik += c;

    rhs = masik;
    return is;
}

