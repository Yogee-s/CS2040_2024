#include "RGB.h"

#include <iostream>

#define BOUND(x, min, max) ((x) < (min) ? (min) : ((x) > (max) ? (max) : (x)))

RGB::RGB(int red, int green, int blue) :
    red_(BOUND(red, 0, 255)),
    green_(BOUND(green, 0, 255)),
    blue_(BOUND(blue, 0, 255)) { }

RGB::~RGB() { }

void RGB::print() {
  std::cout << "RGB(" << red_ << ", " << green_ << ", " << blue_ << ")"
    << std::endl;
}

RGB RGB::mix(const RGB& other) {
    int mixedRed = red() + other.red();
    int mixedGreen = green() + other.green();
    int mixedBlue = blue() + other.blue();

    return RGB(mixedRed, mixedGreen, mixedBlue);
}


RGB RGB::scale(double factor) {
    int redScaled = std::round(red() * factor);
    int greenScaled = std::round(green() * factor);
    int blueScaled = std::round(blue() * factor);
  return RGB(redScaled, greenScaled, blueScaled);
}


bool RGB::equals(const RGB& input) {
    int red_compare = input.red();
    int green_compare = input.green();
    int blue_compare= input.blue();

    if ((red_compare == red()) && (green_compare == green()) && (blue_compare == blue())) {
        return true;
    }
    else {
        return false;
    }

    
}

int RGB::greyscaleValue() {
    int red_colour = red();
    int green_colour = green();
    int blue_colour = blue();
    
    int result = std::round((red_colour + green_colour + blue_colour) / 3);

    return result;
}

RGB RGB::operator+(const RGB& input) {
    int mixedRed = red() + input.red();
    int mixedGreen = green() + input.green();
    int mixedBlue = blue() + input.blue();

    return RGB(mixedRed, mixedGreen, mixedBlue);
}


RGB RGB::operator*(double scale){
    int redScaled = std::round(red() * scale);
    int greenScaled = std::round(green() * scale);
    int blueScaled = std::round(blue() * scale);

    return RGB(redScaled, greenScaled, blueScaled);
}



bool RGB::operator==(const RGB& input) {
    int red_compare = input.red();
    int green_compare = input.green();
    int blue_compare = input.blue();

    if ((red_compare == red()) && (green_compare == green()) && (blue_compare == blue())) {
        return true;
    }
    else {
        return false;
    }


}
