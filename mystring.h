
class MyString {
    size_t size;
    char* str;
    int* refcount_;
  public:

    MyString();
    MyString(char const * s);

    MyString(const MyString& masik);
    MyString& operator=(const MyString& masik);  //copy constructor and =

    MyString(MyString && ) noexcept;             //move constructor and =
    MyString& operator=(MyString &&) noexcept;

    ~MyString();

    int getRefCount() {return *refcount_;}



    MyString operator+(MyString const& rhs) const;

    MyString& operator+=(MyString const& rhs);
    MyString& operator+=(char rhs);

    char& operator[](int i);
    char operator[](int i) const;

    int length() const;
    char const * get_str() const {
        return str;
    }
};

std::ostream& operator<<(std::ostream& os, MyString const& rhs);
std::istream& operator>>(std::istream& is, MyString& rhs);
