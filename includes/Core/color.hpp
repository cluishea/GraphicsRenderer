#pragma once
#include <cstdint>

namespace gfx{

    struct Color
    {
        std::uint8_t r,g,b,a;

        constexpr Color(std::uint8_t red = 255, std::uint8_t green = 255, std::uint8_t blue = 255, std::uint8_t alpha = 255): r(red), g(green), b(blue), a(alpha){

        }

        constexpr std::uint32_t ToRGBA() const{
            return ((static_cast<std::uint32_t>(a)<< 24) | (static_cast<std::uint32_t>(b) << 16) | (static_cast<std::uint32_t>(g) << 8) | (static_cast<std::uint32_t>(r)));
        }

        Color operator*(float scale) const {
            return Color{
                static_cast<std::uint8_t>(r * scale),
                static_cast<std::uint8_t>(g * scale),
                static_cast<std::uint8_t>(b * scale),
                static_cast<std::uint8_t>(a * scale)
            };
        }

        Color operator+(Color other) const{
            return Color{
                static_cast<std::uint8_t>(r + other.r),
                static_cast<std::uint8_t>(g + other.g),
                static_cast<std::uint8_t>(b + other.b),
                static_cast<std::uint8_t>(a + other.a)
            };
        }

    };
    

}