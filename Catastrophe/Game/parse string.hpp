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

class ParseString {
public:
  explicit ParseString(const std::string &);
  explicit ParseString(std::experimental::string_view);
  ParseString(const char *, size_t);
  
  const char *data() const;
  size_t size() const;
  LineCol lineCol() const;
  std::experimental::string_view view() const;
  
  bool empty() const;
  char operator[](size_t) const;
  char front() const;
  
  ///Move the front of the string forward. Increments line and column
  ///numbers accordingly
  void advance(size_t);
  ///Move the front of the string forward by one character. Increments line and
  ///column numbers accordingly
  void advance();
  
  ///Move the front forward while the supplied predicate returns true
  template <typename Pred>
  void skip(Pred &&pred) {
    size_t numChars = 0;
    while (numChars < mSize && pred(mData[numChars])) {
      ++numChars;
    }
    advance(numChars);
  }
  ///Move the front forward while the front is whitespace
  void skipWhitespace();
  
  ///Move the front forward until the supplied predicate returns true
  template <typename Pred>
  void skipUntil(Pred &&pred) {
    //@TODO
    //skip(std::not_fn(pred));
    skip([pred = std::forward<Pred>(pred)](const char c) {
      return !pred(c);
    });
  }
  ///Move the front forward until the front is equal to the supplied character
  void skipUntil(char);
  
  ///Throw a ParseStringError exception if the front character is not equal to
  ///the supplied character
  void expect(char);
  ///Skip characters then throw a ParseStringError exception if the front
  ///character is not equal to the supplied character
  template <typename Pred>
  void expectAfter(Pred &&pred, const char c) {
    skip(pred);
    expect(c);
  }
  ///Skip whitespace then throw a ParseStringError exception if the front
  ///character is not equal to the supplied character
  void expectAfterWhitespace(char);
  
  ///Advances and returns true if the front character is equal to the supplied
  ///character. Does nothing and returns false otherwise
  bool check(char);
  ///Advances and returns true if the front part of the string is equal to the
  ///supplied string. Does nothing and returns false otherwise
  bool check(const char *, size_t);
  ///Advances and returns true if the front part of the string is equal to the
  ///supplied string. Does nothing and returns false otherwise
  bool check(std::experimental::string_view);
  
private:
  const char *mData;
  size_t mSize;
  LineCol mLineCol;
};

#endif
