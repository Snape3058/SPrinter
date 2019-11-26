SPrinter
========

A Static Checker for Finding Smart Pointer Errors in C++ Programs

Introduction
------------

A static coding style checker for detecting API misuses of C++ smart pointers that will probably lead to memory errors like memory leak, use after free, and double free.

Error Patterns
--------------

### smartpointersafety-autoptr-in-container

Report an `auto_ptr` template argument used in an STL container.

```cpp
std::vector<std::auto_ptr<int>> vi;
^
Warn here
```

### smartpointersafety-autoptr-ownership-transfer

Report all the memory transfer from one `auto_ptr` to another.

```cpp
std::auto_ptr<int> p1(new int(42));
void foo(std::auto_ptr<int> p);

foo(p1);
    ^
Warn here
```

### smartpointersafety-deallocating-observer-pointer

Report the operation that `delete`s the pointer from smart pointer observers.

```cpp
std::unique_ptr<int> p = std::make_unique<int>(42);
delete p.get();
       ^
   Warn here
```

### smartpointersafety-non-allocated-memory-initiation

Report the initiations with non-allocated memory.

```cpp
int I;
std::unique_ptr<int> p(&I);
                       ^
                   Warn here
```

### smartpointersafety-private-autoptr-in-class

Report a private `auto_ptr` field in a class without copy constructors and assignment operators.

```cpp
class Type {
  private:
    std::auto_ptr<int> p;
    ^
Warn here
};
```

### smartpointersafety-raw-pointer-initiation

Report the construction of a smart pointer with a raw pointer variable.

```cpp
void foo(int *p) {
    std::unique_ptr<int> sp(p);
                            ^
                        Warn here
}
```

### smartpointersafety-type-mismatch-initiation

Report the mismatched type of template argument and `new` operator for smart pointer constructions.

```cpp
std::auto_ptr<int> sp(new int[42]);
                      ^
                  Warn here
```

### smartpointersafety-unchecked-locked-weak-pointer

Report the usages of unchecked locked `weak_ptr`s.

```cpp
std::weak_ptr<int> wp;
   ...
*wp.lock() = 42;
^
Warn here
```

### smartpointersafety-undeallocated-released-pointer

Report the `release`d pointer that are not dealocated.

```cpp
std::unique_ptr<int> sp;
   ...
*sp.release() = 42;
 ^
Warn here
```

Usage
-----

### Download

[clang-tidy with SPrinter](http://lcs.ios.ac.cn/~maxt/SPrinter/clang-tidy) (SHA256SUM 2c237c9a7e280f91d705ed6e16189c0a63b17643f09f3e233b2f7e6ecc712272)

Please contact us if you need the source code.

### Tool Usage

- [Using clang-tidy](https://clang.llvm.org/extra/clang-tidy/#using-clang-tidy).
- [Using clang-tidy with IDEs or editors](https://clang.llvm.org/extra/clang-tidy/Integrations.html).
- To use SPrinter, please enable the `smartpointersafety-` prefix for all the error patterns mentioned above.

E.g.

```sh
$ clang-tidy -checks='-*,smartpointersafety-*' source.cpp
```


Publication
-----------

- [YouTube Video Introduction](https://youtu.be/xD1b3cJ8s2g).
- [ASE 2019 Tool Demonstration Paper](http://lcs.ios.ac.cn/~maxt/SPrinter/ASE-2019-Tool.pdf).
