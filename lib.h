#pragma once

#include "version.h"
#include <iostream>

using namespace std;

int version();
size_t factorial(size_t n);

template<typename T, size_t N>
struct Allocator {
    using value_type = T;
    using pointer = T *;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    template <typename U>
    struct rebind {
        using other = Allocator<U, N>;
    };

    pointer allocate(size_t n) {
        if(count + n > N)
            throw bad_alloc();
        if(!ptr)
            ptr = reinterpret_cast<pointer>(malloc(N * sizeof(T)));
        if(!ptr)
            throw bad_alloc();
        T* res = ptr + count;
        count += n;
        return res;
    }

    void deallocate(pointer p, size_t n) {
        if(!p)
            return;
        count -= n;
        if(count != 0)
            return;
        free(ptr);
        ptr = nullptr;
    }

    template <typename ... Args>
    void construct(pointer p, Args&& ... args) {
        new(p) T(std::forward<Args>(args)...);
    }

    void destroy(T* p) {
        p->~T();
    }

private:
    pointer     ptr     = nullptr;
    size_t      count   = 0;
};

template <typename T, class A = allocator<T> >
class List {
public:
    struct Node {
        Node();
        Node(const T& value_) : next(nullptr), value(value_) {}
        Node*   next;
        T       value;
    };

    class Iterator {
    public:
        Iterator(Node* node_ = nullptr) : node(node_) {}
        Iterator& operator++() {
            node = node->next;
            return *this;
        }
        T operator*() {
            return node->value;
        }
        bool operator!=(const Iterator& other) {
            return node != other.node;
        }
    private:
        Node*   node;
    };

    List() = default;
    ~List() {
        auto node = base;
        while(node) {
            auto tmp = node->next;
            allocator.destroy(node);
            allocator.deallocate(node, 1);
            node = tmp;
        }
    }

    Iterator begin() const {
        return Iterator(base);
    }

    Iterator end() const {
        return Iterator(nullptr);
    }

    void append(const T& value) {
        auto node = allocator.allocate(1);
        allocator.construct(node, value);

        if (base == nullptr)
            base = head = node;
        else
            head = head->next = node;
    }

private:
    typename A::template rebind<Node>::other allocator;
    Node*   base;
    Node*   head;
};

