#include "env.h"

namespace {
void UseAutoPtrInsideSTLContainers() {
  // Sequence Containers:
  array<auto_ptr<obj_ty>, 42> Array;
  vector<auto_ptr<obj_ty>> Vector;
  deque<auto_ptr<obj_ty>> Deque;
  forward_list<auto_ptr<obj_ty>> ForwardList;
  list<auto_ptr<obj_ty>> List;

  // Container adaptors:
  stack<auto_ptr<obj_ty>> Stack;
  queue<auto_ptr<obj_ty>> Queue;
  priority_queue<auto_ptr<obj_ty>> PriorityQueue;

  // Associative containers:
  set<auto_ptr<obj_ty>> Set;
  multiset<auto_ptr<obj_ty>> Multiset;
  // map<auto_ptr<obj_ty>, auto_ptr<obj_ty>> Map;
  // multimap<auto_ptr<obj_ty>, auto_ptr<obj_ty>> Multimap;
  // pair<auto_ptr<obj_ty>, auto_ptr<obj_ty>> Pair;

  // Unordered associative containers:
  struct auto_hash {
    size_t operator()(const auto_ptr<obj_ty> &ap) const noexcept {
      return reinterpret_cast<size_t>(ap.get());
    }
  };
  unordered_set<auto_ptr<obj_ty>, auto_hash> UnorderedSet;
  unordered_multiset<auto_ptr<obj_ty>, auto_hash> UnorderedMultiset;
  // unordered_map<auto_ptr<obj_ty>, auto_hash> UnorderedMap;
  // unordered_multimap<auto_ptr<obj_ty>, auto_hash> UnorderedMultimap;
}
} // namespace
