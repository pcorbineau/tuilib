#include <gtest/gtest.h>
#include <tuilib/border.h>

#include <format>
#include <string>

namespace {
auto render(const auto& set) -> std::string {
    return std::format(
        "░░░░░░"
        "░{}{}{}{}░"
        "░{}░░{}░"
        "░{}░░{}░"
        "░{}{}{}{}░"
        "░░░░░░",
        set.top_left, set.horizontal_top, set.horizontal_top, set.top_right,
        set.vertical_left, set.vertical_right, set.vertical_left,
        set.vertical_right, set.bottom_left, set.horizontal_bottom,
        set.horizontal_bottom, set.bottom_right);
}
}  // namespace

TEST(BorderTests, Plain) {
    constexpr auto expected =
        "░░░░░░"
        "░┌──┐░"
        "░│░░│░"
        "░│░░│░"
        "░└──┘░"
        "░░░░░░";
    ASSERT_EQ(render(tuilib::border::plain()), expected);
}
