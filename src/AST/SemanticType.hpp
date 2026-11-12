#pragma once
#include "MyClasses.hpp"
#include "MyDef.hpp"
class SemanticType {
  public:
    class Layer {
      public:
        enum {
            UNDEF,
            VEC,
            BOX,
            ID,
            UNIT,
            NEVER,
            INT,
        };
        vector<int> muts; // head:inner tail:outter
        string id;
        int type;
        int len; // 0 not array ; >0 array
        Layer(string);
        Layer(string, ASTCrate *);
        Layer();
    };
    vector<Layer> layers; // head:inner tail:outter
};