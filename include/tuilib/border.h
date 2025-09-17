#pragma once

#include <string_view>
#include "tuilib/line.h"

namespace tuilib {
namespace border {
struct Set {
    std::string_view top_left;
    std::string_view top_right;
    std::string_view bottom_left;
    std::string_view bottom_right;
    std::string_view vertical_left;
    std::string_view vertical_right;
    std::string_view horizontal_top;
    std::string_view horizontal_bottom;
};

constexpr auto plain() -> Set {
    return {
        line::TOP_LEFT, line::TOP_RIGHT, line::BOTTOM_LEFT, line::BOTTOM_RIGHT,
        line::VERTICAL, line::VERTICAL,  line::HORIZONTAL,  line::HORIZONTAL,
    };
}


}  // namespace border
}  // namespace tuilib
