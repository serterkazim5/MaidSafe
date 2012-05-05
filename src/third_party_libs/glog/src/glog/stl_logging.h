// Copyright (c) 2003, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Stream output operators for STL containers; to be used for logging *only*.
// Inclusion of this file lets you do:
//
// list<string> x;
// LOG(INFO) << "data: " << x;
// vector<int> v1, v2;
// CHECK_EQ(v1, v2);
//
// Note that if you want to use these operators from the non-global namespace,
// you may get an error since they are not in namespace std (and they are not
// in namespace std since that would result in undefined behavior). You may
// need to write
//
//   using ::operator<<;
//
// to fix these errors.

#ifndef UTIL_GTL_STL_LOGGING_INL_H_
#define UTIL_GTL_STL_LOGGING_INL_H_

#if !1
# error We do not support stl_logging for this compiler
#endif

#include <deque>
#include <list>
#include <map>
#include <ostream>
#include <set>
#include <utility>
#include <vector>

#ifdef __GNUC__
# include <ext/hash_set>
# include <ext/hash_map>
# include <ext/slist>
#endif

template<class First, class Second>
inline std::ostream& operator<<(std::ostream& out,
                                const std::pair<First, Second>& p) {
  out << '(' << p.first << ", " << p.second << ')';
  return out;
}

namespace google {

template<class Iter>
inline void PrintSequence(std::ostream& out, Iter begin, Iter end) {
  using ::operator<<;
  // Output at most 100 elements -- appropriate if used for logging.
  for (int i = 0; begin != end && i < 100; ++i, ++begin) {
    if (i > 0) out << ' ';
    out << *begin;
  }
  if (begin != end) {
    out << " ...";
  }
}

}

#define OUTPUT_TWO_ARG_CONTAINER(Sequence) \
template<class T1, class T2> \
inline std::ostream& operator<<(std::ostream& out, \
                                const Sequence<T1, T2>& seq) { \
  google::PrintSequence(out, seq.begin(), seq.end()); \
  return out; \
}

OUTPUT_TWO_ARG_CONTAINER(std::vector)
OUTPUT_TWO_ARG_CONTAINER(std::deque)
OUTPUT_TWO_ARG_CONTAINER(std::list)
#ifdef __GNUC__
OUTPUT_TWO_ARG_CONTAINER(__gnu_cxx::slist)
#endif

#undef OUTPUT_TWO_ARG_CONTAINER

#define OUTPUT_THREE_ARG_CONTAINER(Sequence) \
template<class T1, class T2, class T3> \
inline std::ostream& operator<<(std::ostream& out, \
                                const Sequence<T1, T2, T3>& seq) { \
  google::PrintSequence(out, seq.begin(), seq.end()); \
  return out; \
}

OUTPUT_THREE_ARG_CONTAINER(std::set)
OUTPUT_THREE_ARG_CONTAINER(std::multiset)

#undef OUTPUT_THREE_ARG_CONTAINER

#define OUTPUT_FOUR_ARG_CONTAINER(Sequence) \
template<class T1, class T2, class T3, class T4> \
inline std::ostream& operator<<(std::ostream& out, \
                                const Sequence<T1, T2, T3, T4>& seq) { \
  google::PrintSequence(out, seq.begin(), seq.end()); \
  return out; \
}

OUTPUT_FOUR_ARG_CONTAINER(std::map)
OUTPUT_FOUR_ARG_CONTAINER(std::multimap)
#ifdef __GNUC__
OUTPUT_FOUR_ARG_CONTAINER(__gnu_cxx::hash_set)
OUTPUT_FOUR_ARG_CONTAINER(__gnu_cxx::hash_multiset)
#endif

#undef OUTPUT_FOUR_ARG_CONTAINER

#define OUTPUT_FIVE_ARG_CONTAINER(Sequence) \
template<class T1, class T2, class T3, class T4, class T5> \
inline std::ostream& operator<<(std::ostream& out, \
                                const Sequence<T1, T2, T3, T4, T5>& seq) { \
  google::PrintSequence(out, seq.begin(), seq.end()); \
  return out; \
}

#ifdef __GNUC__
OUTPUT_FIVE_ARG_CONTAINER(__gnu_cxx::hash_map)
OUTPUT_FIVE_ARG_CONTAINER(__gnu_cxx::hash_multimap)
#endif

#undef OUTPUT_FIVE_ARG_CONTAINER

#endif  // UTIL_GTL_STL_LOGGING_INL_H_