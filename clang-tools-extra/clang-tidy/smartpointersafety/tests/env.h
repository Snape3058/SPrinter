#ifndef ENV__H
#define ENV__H

#include <bits/stdc++.h>

using namespace std;

// disable warnings on auto_ptr
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

class obj_ty {
public:
  int x;
  int &use() { return x; }
};

#endif
