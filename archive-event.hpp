#pragma once

#include <string>
#include <cassert>

#include "vector2f.hpp"

namespace g {
    class event {
    public:
        enum type_t {
            None = 0,
            Unsupported,
            MousePress,
            MouseRelease,
        };

        type_t type;
        g::vector2f pos;

        event(type_t t, g::vector2f p = {0, 0}) : type(t), pos(p) {};
        event& operator=(const event &other)
        {
            type = other.type;
            pos = other.pos;
            return *this;
        }
    };
}
