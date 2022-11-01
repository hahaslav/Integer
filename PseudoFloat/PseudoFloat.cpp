#include "PseudoFloat.h"

PseudoFloat::operator std::string() const {
    return "0." + TInteger::operator std::string();
}