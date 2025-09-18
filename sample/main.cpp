#include <algorithm>
#include <cassert>
#include <print>
#include <random>
#include <ranges>
#include <thread>
#include <vector>

auto random_value(size_t begin, size_t end) -> size_t {
    std::random_device r;
    std::default_random_engine e(r());
    std::uniform_int_distribution<size_t> uniform_dist(begin, end);
    return uniform_dist(e);
}

auto multiple_progress_bar(size_t count) {
    std::vector<size_t> all_progress(count, 0);
    const auto new_lines = std::string(count, '\n');
    std::fputs(new_lines.c_str(), stdout);
    const auto not_finished = [](auto v) { return v < 100; };
    while (std::ranges::any_of(all_progress, not_finished)) {
        auto unfinished = all_progress | std::views::enumerate |
                          std::views::filter([](const auto& tuple) {
                              const auto& value = std::get<1>(tuple);
                              assert(value <= 100);
                              return value < 100;
                          }) |
                          std::ranges::to<std::vector>();
        assert(!unfinished.empty());
        const auto unfinished_size = unfinished.size();
        const auto random_index = random_value(0, unfinished_size - 1);
        const auto& [i, v] = unfinished[random_index];
        all_progress[(size_t)i] += 1;

        // draw the progress bar
        std::print("\u001b[1000D");       // move left
        std::print("\u001b[{}A", count);  // move up
        for (const auto& p : all_progress) {
            const auto width = p / 4;
            assert(width <= 25);
            const auto bar = std::string(width, '#');
            std::print("[{:<25}]\n", bar);
            std::fflush(stdout);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

/*
 * Inspired by
 * https://www.lihaoyi.com/post/BuildyourownCommandLinewithANSIescapecodes.html
 */

auto first_steps() {
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
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    std::fputs(NEWLINE, stdout);
}

auto main() -> int {
    multiple_progress_bar(6);
}
