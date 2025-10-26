#pragma once
#include <functional>
#include "delete.hpp"

namespace wjl {
    template <typename T>
    class SharedPointer;
    template <typename T>
    auto swap(SharedPointer<T>&lhs, SharedPointer<T>&rhs) {
        using std::swap;
        swap(lhs.ptr, rhs.ptr);
        swap(lhs.ref_count, rhs.ref_count);
        swap(lhs.deleter, rhs.deleter);
    };

    template <typename T>
    class SharedPointer {
    public:
        // Default Ctor
        // Binding the Deleter at Run Time
        SharedPointer() : ptr(nullptr), ref_count(new std::size_t(1)), deleter(wjl::Delete{}) {};
        // Ctor that takes raw pointer
        SharedPointer(T* raw_ptr, std::function<void(T*)> d=wjl::Delete()) : ptr(raw_ptr), ref_count(new std::size_t(1)), deleter(d) {};
        // Copy Ctor
        SharedPointer(const SharedPointer& rhs): ptr(rhs.ptr), ref_count(rhs.ref_count), deleter(rhs.deleter) {
            ++*ref_count;
        };
        // Move Ctor
        SharedPointer(SharedPointer && rhs) noexcept: ptr(rhs.ptr), ref_count(rhs.ref_count), deleter(std::move(rhs.deleter)) {
            rhs.ptr = nullptr;
            rhs.ref_count = nullptr;
        }
        // Copy assgiment
        SharedPointer& operator=(const SharedPointer& rhs) {
            //increment first to ensure safty for self-assignment
            // 或者使用 *this != rhs 判断
            ++*ref_count;
            decrement_and_destroy();
            ptr = rhs.ptr;
            ref_count = rhs.ref_count;
            deleter = rhs.deleter;
            return *this;
        }
        // Move assignment
        SharedPointer& operator=(SharedPointer&& rhs) {
            wjl::swap(*this, rhs);
            rhs.decrement_and_destroy();
            return *this;
        }
        //
        //  Conversion operator
        //
        operator bool() const
        {
            return ptr ? true : false;
        }
        //
        //  Dereference
        //
        T& operator* () const
        {
            return *ptr;
        }
        //
        //  Arrow
        //
        T* operator->() const
        {
            return &*ptr;
        }
        //
        //  Use count
        //
        auto use_count() const
        {
            return *ref_count;
        }
        //
        //  Get underlying pointer
        //
        auto get() const
        {
            return ptr;
        }
        //
        //  Check if the unique user
        //
        auto unique() const
        {
            return 1 == *ref_count;
        }
        //
        //  Swap
        //
        auto swap(SharedPointer& rhs) {
            wjl::swap(*this, rhs);
        }
        //
        // Free the object pointed to, if unique
        //
        auto reset()
        {
            decrement_and_destroy();
        }
        //
        // Reset with the new raw pointer
        //
        auto reset(T *pointer) {
            if (ptr != pointer) {
                decrement_and_destroy();
                ptr = pointer;
                ref_count = new std::size_t(1);
            }
        }
        //
        //  Reset with raw pointer and deleter
        //
        auto reset(T *pointer, const std::function<void(T*)>& d) {
            reset(pointer);
            deleter = d;
        }
        //
        //  Dtor
        //
        ~SharedPointer() {
            decrement_and_destroy();
        }
    private:
        T* ptr;
        std::size_t* ref_count;
        std::function<void(T*)> deleter;
        auto decrement_and_destroy() {
            if (ptr && 0 == --*ref_count) {
                delete ref_count;
                deleter(ptr);
            } else if (!ptr) {
                delete ref_count;
            }
            ref_count = nullptr;
            ptr = nullptr;
        }
    };
}