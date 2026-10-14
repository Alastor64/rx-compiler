#pragma once
#include <string>
class MyErr {
    std::string text;

  public:
    MyErr(std::string tmp);
    MyErr(const char *s);
    const char *what() const;
};