//
//  parse string.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 28/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef parse_string_hpp
#define parse_string_hpp

#include <experimental/string_view>
#include <Simpleton/Utils/line col.hpp>

class ParseStringError final : public std::runtime_error {
public:
  explicit ParseStringError(const char *);
};

using LineCol = Utils::LineCol<unsigned, unsigned>;

//similar to a std::string_view
class ParseString {
public:
  explicit ParseString(std::experimental::string_view);
  ParseString(const char *, size_t);
  
  const char *data() const;
  size_t size() const;
  LineCol lineCol() const;
  std::experimental::string_view view() const;
  
  bool empty() const;
  char operator[](size_t) const;
  char front() const;
  
  void advance(size_t);
  void advance();
  
  void skipWhitespace();
  void expect(char);
  void expectAfterWhitespace(char);
  
  bool check(char);
  bool check(const char *, size_t);
  bool check(std::experimental::string_view);
  
private:
  const char *mData;
  size_t mSize;
  LineCol mLineCol;
};

#endif
