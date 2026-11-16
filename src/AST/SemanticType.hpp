#pragma once
#include "MyClasses.hpp"
#include "MyDef.hpp"
#include <cfloat>
class SemanticType {
  public:
    class Layer {
      public:
        enum {
            ERRMARK = -1,
            UNDEF,
            VEC,
            BOX,
            STRUCT,
            UNIT,
            NEVER,
            INT,
            BOOL,
            I32,
            U32,
            ISIZE,
            USIZE,
        };
        vector<int> muts; // head:inner tail:outter
        ASTStruct *_struct;
        int type;
        int len; // 0 not array ; >0 array
        Layer(string, ASTCrate *);
        Layer();
        Layer(int);
        bool operator==(const Layer &) const;
        bool operator!=(const Layer &) const;
        static int getIntType(string s) {
            if (s == "i32")
                return I32;
            if (s == "u32")
                return U32;
            if (s == "isize")
                return ISIZE;
            if (s == "usize")
                return USIZE;
            return ERRMARK;
        }
        int unsign() const;
        int ifint() const;
    };
    void setBool();
    void setInt();
    void setType(string, ASTCrate *);
    Layer &outter();
    const Layer &outter() const;
    vector<Layer> layers; // head:inner tail:outter
    bool operator==(const SemanticType &) const;
    bool operator!=(const SemanticType &) const;
};