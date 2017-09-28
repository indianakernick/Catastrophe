//
//  parse string.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 28/9/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "parse string.hpp"

#include <cassert>

ParseStringError::ParseStringError(const char *what)
  : std::runtime_error(what) {}

ParseString::ParseString(const std::experimental::string_view view)
  : mData(view.data()), mSize(view.size()) {
  assert(mData);
}

ParseString::ParseString(const char *data, const size_t size)
  : mData(data), mSize(size) {
  assert(data);
}

const char *ParseString::data() const {
  return mData;
}

size_t ParseString::size() const {
  return mSize;
}

LineCol ParseString::lineCol() const {
  return mLineCol;
}

std::experimental::string_view ParseString::view() const {
  return {mData, mSize};
}

bool ParseString::empty() const {
  return mSize == 0;
}

char ParseString::operator[](const size_t i) const {
  if (i >= mSize) {
    throw ParseStringError("Index on parse string out of range");
  }
  return mData[i];
}

char ParseString::front() const {
  if (mSize == 0) {
    throw ParseStringError("Got character from empty parse string");
  }
  return *mData;
}

void ParseString::advance(const size_t numChars) {
  if (numChars > mSize) {
    throw ParseStringError("Advanced parse string too many characters");
  }
  mLineCol.putString(mData, numChars);
  mData += numChars;
  mSize -= numChars;
}

void ParseString::advance() {
  if (mSize == 0) {
    throw ParseStringError("Advanced parse string too many characters");
  }
  mLineCol.putChar(*mData);
  ++mData;
  --mSize;
}

void ParseString::skipWhitespace() {
  size_t numSpace = 0;
  while (numSpace < mSize && std::isspace(mData[numSpace])) {
    ++numSpace;
  }
  advance(numSpace);
}

void ParseString::expect(const char c) {
  if (mSize == 0 || *mData != c) {
    throw ParseStringError((std::string("Expected character ") + c).c_str());
  }
  advance();
}

void ParseString::expectAfterWhitespace(const char c) {
  skipWhitespace();
  expect(c);
}

bool ParseString::check(const char c) {
  if (mSize == 0 || *mData != c) {
    return false;
  } else {
    advance();
    return true;
  }
}

bool ParseString::check(const char *data, const size_t size) {
  if (mSize < size) {
    return false;
  }
  if (size == 0) {
    return true;
  }
  if (std::memcmp(mData, data, size) == 0) {
    advance(size);
    return true;
  } else {
    return false;
  }
}

bool ParseString::check(const std::experimental::string_view view) {
  return check(view.data(), view.size());
}
