#pragma once

struct Color {
    int r;
    int g;
    int b;

    Color(int r, int g, int b) {
        this->r = r;
        this->g = g;
        this->b = b;
    }
};

std::ostream& operator<<(std::ostream& os, const Color& color);