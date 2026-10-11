#include "myErr.hpp"
MyErr::MyErr(std::string tmp) : text(tmp) {}
const char *MyErr::what() const { return text.c_str(); }