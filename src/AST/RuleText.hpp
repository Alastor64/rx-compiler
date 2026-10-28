#pragma once
#include "MyDef.hpp"
#include <RuleContext.h>
#include <type_traits>
#include <vector>
class RuleText {
  public:
    RuleText() = delete;
    template <
        typename T,
        std::enable_if_t<std::is_base_of_v<antlr4::RuleContext, T>, int> = 0>
    static vector<string> get(const vector<T *> x) {
        vector<string> tmp;
        for (auto *i : x) {
            tmp.push_back(i->getText());
        }
        return tmp;
    }
};