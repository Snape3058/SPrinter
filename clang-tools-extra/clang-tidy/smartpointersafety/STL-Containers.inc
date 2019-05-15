//===--- STL-Containers.inc - clang-tidy ----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef NAME
#define NAME(name)
#endif

// Sequence containers:
NAME(array)
NAME(vector)
NAME(deque)
NAME(forward_list)
NAME(list)

// Container adaptors:
NAME(stack)
NAME(queue)
NAME(priority_queue)

// Associative containers:
NAME(set)
NAME(multiset)
NAME(map)
NAME(multimap)
NAME(pair)

// Unordered associtive containers:
NAME(unordered_set)
NAME(unordered_multiset)
NAME(unordered_map)
NAME(unordered_multimap)

#undef NAME
