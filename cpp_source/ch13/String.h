#ifndef STRING_H
#define STRING_H
#include <memory>


class String {
    friend std::ostream& operator<<(std::ostream& os, const String& s);
    friend std::istream& operator>>(std::istream& is, String& s);
public:
    String() : String("") {};
    String(const char *);
    String(const String&);
    String(String &&) noexcept;
    String &operator=(String &&) noexcept;
    ~String();
    String& operator=(const String&);

    const char *c_str() const {return elements;}
    size_t length() const {return end - elements;};
    size_t size() const {return end - elements - 1;};

private:
    std::pair<char *, char *> alloc_n_copy(const char *, const char *);
    void range_initializer(const char *, const char *);
    void free();
    char *elements;
    char *end;
    static std::allocator<char> alloc;
};

std::ostream& operator<<(std::ostream& os, const String& s);
std::istream& operator>>(std::istream& is, String& s);
#endif //STRING_H
