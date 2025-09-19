#pragma once

#include <string_view>
#include "tuilib/line.h"


namespace tuilib::border {
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
        .top_left=line::TOP_LEFT, .top_right=line::TOP_RIGHT, .bottom_left=line::BOTTOM_LEFT, .bottom_right=line::BOTTOM_RIGHT,
        .vertical_left=line::VERTICAL, .vertical_right=line::VERTICAL,  .horizontal_top=line::HORIZONTAL,  .horizontal_bottom=line::HORIZONTAL,
    };
}


} // namespace tuilib::border

