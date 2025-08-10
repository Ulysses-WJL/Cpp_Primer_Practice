#ifndef STRVEC_H
#define STRVEC_H
#include <string>
#include <vector>


class StrVec {
public:
    StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) {}
    StrVec(std::initializer_list<std::string>);
    StrVec(const StrVec &);
    // Move constructors and move assignment operators that cannot throw exceptions
    // should be marked as noexcept
    // 1. 避免异常处理开销:
    // 2. 使移动语义更有效 std::vector 和其他 STL 容器在实现时会优先使用移动构造函数。
    // 如果移动构造函数是 noexcept 的，容器在扩展或重新分配内存时会更倾向于使用移动而不是复制。
    //
    StrVec(StrVec &&) noexcept;
    StrVec &operator=(const StrVec &);
    StrVec &operator=(StrVec &&) noexcept;
    ~StrVec();

    void push_back(const std::string &);
    size_t size() const {return first_free - elements;}
    size_t capacity() const {return cap - elements;}
    std::string *begin() const {return elements;}
    std::string *end() const {return first_free;}
private:
    static std::allocator<std::string> alloc;  // 使用allocator 分配内存
    // allocate space and copy a given range of elements.
    std::pair<std::string*, std::string*> alloc_n_copy(const std::string * , const std::string *);
    // 当first_free == cap, 即没有足够的空间添加新元素时，重新allocate
    void chk_n_alloc() {if (size() == capacity()) reallocate();}
    // destroy the elements and free the space
    void free();
    // get more space and copy the existing elements
    void reallocate();
    std::string *elements;  // pointer to the first element in the array
    std::string *first_free;  // pointer to the first free element in the array
    std::string *cap;  // pointer to one past the end of the array
};



#endif //STRVEC_H
