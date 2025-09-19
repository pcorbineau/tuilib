#include <algorithm>
#include <cassert>
#include <print>
#include <random>
#include <ranges>
#include <thread>
#include <vector>

// NOLINTBEGIN(readability-magic-numbers, cppcoreguidelines-avoid-magic-numbers)
namespace {

auto check_non_negative(auto ret) {
  if (ret < 0) {
    std::terminate();
  }
}

auto check_non_null(auto ret) {
  if (ret != 0) {
    std::terminate();
  }
}

auto random_value(auto begin, auto end) {
    std::random_device random_dev;
    std::default_random_engine engine(random_dev());
    std::uniform_int_distribution<size_t> uniform_dist(begin, end);
    return uniform_dist(engine);
}

auto multiple_progress_bar(size_t count) {
    std::vector<size_t> all_progress(count, 0);
    const auto new_lines = std::string(count, '\n');
    check_non_negative(std::fputs(new_lines.c_str(), stdout));
    constexpr auto MAX_PERCENTAGE = 100;
    const auto not_finished = [](auto value) -> auto {
        return value < MAX_PERCENTAGE;
    };
    while (std::ranges::any_of(all_progress, not_finished)) {
        auto unfinished = all_progress | std::views::enumerate |
                          std::views::filter([](const auto& tuple) -> auto {
                              const auto& value = std::get<1>(tuple);
                              assert(value <= MAX_PERCENTAGE);
                              return value < MAX_PERCENTAGE;
                          }) |
                          std::ranges::to<std::vector>();
        assert(!unfinished.empty());
        const auto unfinished_size = unfinished.size();
        const auto random_index = random_value(0UZ, unfinished_size - 1);
        const auto& [index, value] = unfinished[random_index];
        all_progress[(size_t)index] += 1;

        // draw the progress bar
        std::print("\u001b[1000D");       // move left
        std::print("\u001b[{}A", count);  // move up
        for (const auto& progress : all_progress) {
            const auto width = progress / 4;
            assert(width <= 25);
            const auto bar = std::string(width, '#');
            std::print("[{:<25}]\n", bar);
            check_non_null(std::fflush(stdout));
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

    constexpr auto MAX_WIDTH = 16;

    // foreground color
    for (int i = 0; i < MAX_WIDTH; i++) {
        for (int j = 0; j < MAX_WIDTH; j++) {
            const auto code = (i * MAX_WIDTH) + j;
            std::print("\u001b[38;5;{}m {:<4}", code, code);
        }
        check_non_negative(std::fputs(RESET, stdout));
        check_non_negative(std::fputs(NEWLINE, stdout));
    }
    check_non_negative(std::fputs(NEWLINE, stdout));

    // background color
    for (int i = 0; i < MAX_WIDTH; i++) {
        for (int j = 0; j < MAX_WIDTH; j++) {
            const auto code = (i * MAX_WIDTH) + j;
            std::print("\u001b[48;5;{}m {:<4}", code, code);
        }
        check_non_negative(std::fputs(RESET, stdout));
        check_non_negative(std::fputs(NEWLINE, stdout));
    }
    check_non_negative(std::fputs(NEWLINE, stdout));

    // bold, underline, reversed attributes
    constexpr auto BOLD = "\u001b[1m";
    constexpr auto UNDERLINE = "\u001b[4m";
    constexpr auto REVERSED = "\u001b[7m";
    std::print("{1} BOLD {0}{2} UNDERLINE {0}{3} REVERSED{0}\n", RESET, BOLD,
               UNDERLINE, REVERSED);
    check_non_negative(std::fputs(NEWLINE, stdout));

    // progress indicator
    constexpr auto MAX_PERCENTAGE = 100;
    for (int i = 0; i <= MAX_PERCENTAGE; i++) {
        std::print("\u001b[10D{}%", i);
        check_non_null(std::fflush(stdout));
        constexpr auto SLEEP_TIME_MS = 10;
        std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME_MS));
    }
    check_non_negative(std::fputs(NEWLINE, stdout));

    // ASCII progress bar
    for (size_t i = 0; i <= 100; i++) {
        const auto width = (i + 1) / 4;
        assert(width <= 25);
        const auto bar = std::string(width, '#');
        std::print("\u001b[1000D[{:<25}]", bar);
        check_non_null(std::fflush(stdout));
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    check_non_negative(std::fputs(NEWLINE, stdout));
}

}  // namespace

auto main() -> int {
    first_steps();
    multiple_progress_bar(8);
}

 // NOLINTEND(readability-magic-numbers, cppcoreguidelines-avoid-magic-numbers)
