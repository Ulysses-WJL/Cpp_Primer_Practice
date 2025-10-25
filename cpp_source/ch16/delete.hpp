#pragma once

namespace wjl {
    struct Delete {
        template<typename T>
        auto operator() (T *p) {
            std::cout << "Delete ..." << std::endl;
            delete p;
        }
    };
}