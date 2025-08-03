#ifndef STRVEC_H
#define STRVEC_H
#include <string>
#include <vector>


class StrVec {
public:
    StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) {}
    StrVec(std::initializer_list<std::string>);
    StrVec(const StrVec &);
    StrVec &operator=(const StrVec &);
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
