#include "myErr.hpp"
MyErr::MyErr(std::string tmp) : text(tmp) {}
MyErr::MyErr(const char *s) : text(s) {}
const char *MyErr::what() const { return text.c_str(); }