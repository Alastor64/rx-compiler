#pragma once
#include "Crate.hpp"
#include "MyDef.hpp"
class SemanticType {
  public:
    class Layer {
      public:
        enum {
            VEC,
            BOX,
            ID,
        };
        vector<int> muts; // head:inner tail:outter
        string id;
        int type;
        Layer(string);
        Layer(string, ASTCrate *);
    };
    vector<Layer> layers; // head:inner tail:outter
};