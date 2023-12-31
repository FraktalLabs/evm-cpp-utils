# pragma once

#include <array>
#include <cstdint>
#include <string>

using bytes = std::basic_string<uint8_t>;
using bytes_view = std::basic_string_view<uint8_t>;
using address = std::array<uint8_t, 20>;
