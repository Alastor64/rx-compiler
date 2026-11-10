#pragma once
#include "ASTvisitor.hpp"
#include "Constant.hpp"
#include "Crate.hpp"
#include "FuncDef.hpp"
#include "Impl.hpp"
#include "MyDef.hpp"
#include "Struct.hpp"
#include <type_traits>
#include <vector>
class NameCollect : public ASTvisitor {
  public:
    using MP = map<string, int>;

  private:
    template <typename T> static string &getID(T *node) {
        if constexpr (std::is_same_v<ASTImpl, T>) {
            return node->id;
        }
        return node->name;
    }
    template <typename T>
    static int collect(MP &mp, vector<T *> &s, map<string, T *> &_s) {
        static string x;
        while (!s.empty()) {
            auto i = s.back();
            x = getID(i);
            if (mp.find(x) != mp.end())
                return 1;
            mp[x] = 1;
            _s[x] = i;
            s.pop_back();
        }
        return 0;
    }

    template <typename T, typename U>
    static int collectImpl(vector<T *> &s, map<string, T *> &_s,
                           const map<string, U *> &t) {
        static string x;
        while (!s.empty()) {
            auto i = s.back();
            x = getID(i);
            if (_s.find(x) != _s.end() || t.find(x) != t.end())
                return 1;
            _s[x] = i;
            s.pop_back();
        }
        return 0;
    }

  public:
    static MP tmp;
    ASTCrate *root;
    int visitCrate(ASTCrate *) override;
    int visitStruct(ASTStruct *) override;
    int visitImpl(ASTImpl *) override;
};