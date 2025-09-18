#include <cassert>
#include <print>
#include <thread>

/*
 * Inspired by
 * https://www.lihaoyi.com/post/BuildyourownCommandLinewithANSIescapecodes.html
 */

auto main() -> int {
    constexpr auto NEWLINE = "\u001bE";
    constexpr auto RESET = "\u001b[0m";

    // foreground color
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            const auto code = i * 16 + j;
            std::print("\u001b[38;5;{}m {:<4}", code, code);
        }
        std::fputs(RESET, stdout);
        std::fputs(NEWLINE, stdout);
    }
    std::fputs(NEWLINE, stdout);

    // background color
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            const auto code = i * 16 + j;
            std::print("\u001b[48;5;{}m {:<4}", code, code);
        }
        std::fputs(RESET, stdout);
        std::fputs(NEWLINE, stdout);
    }
    std::fputs(NEWLINE, stdout);

    // bold, underline, reversed attributes
    constexpr auto BOLD = "\u001b[1m";
    constexpr auto UNDERLINE = "\u001b[4m";
    constexpr auto REVERSED = "\u001b[7m";
    std::print("{1} BOLD {0}{2} UNDERLINE {0}{3} REVERSED{0}\n", RESET, BOLD,
               UNDERLINE, REVERSED);
    std::fputs(NEWLINE, stdout);

    // progress indicator
    for (int i = 0; i <= 100; i++) {
        std::print("\u001b[10D{}%", i);
        std::fflush(stdout);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    std::fputs(NEWLINE, stdout);

    // ASCII PROGRESS BAR
    for (size_t i = 0; i <= 100; i++) {
        const auto width = (i + 1) / 4;
        assert(width <= 25);
        const auto bar = std::string(width, '#');
        std::print("\u001b[1000D[{:<25}]", bar);
        std::fflush(stdout);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    std::fputs(NEWLINE, stdout);
}
