#pragma once
#include <string>
class MyErr {
    std::string text;

  public:
    MyErr(std::string tmp);
    const char *what() const;
};