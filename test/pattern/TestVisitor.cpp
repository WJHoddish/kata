// Created by Jiaheng on 2021/5/7.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//

#include <Test.h>

#include "kata/pattern/visitor.h"

// know concrete elements
class eleA;
class eleB;

// element base class (visitor base class & pure virtual Accept)
struct Element {
 public:
  using visitor_t = kata::visitor<eleA, eleB>;

  virtual void Accept(visitor_t&) = 0;
};

// define concrete elements
class eleA : public Element {
 public:
  void Accept(Element::visitor_t& visitor) override { visitor.Visit(*this); }
};

class eleB : public Element {
 public:
  void Accept(Element::visitor_t& visitor) override { visitor.Visit(*this); }
};

// define one of the concrete visitors
class PrintVisitor : public Element::visitor_t {
  void Visit(const eleA& a) override { std::cout << "from A" << std::endl; }

  void Visit(const eleB& b) override { std::cout << "from B" << std::endl; }
};

TEST(TestPattern, visitor) {
  PrintVisitor visitor;
  eleA         a;
  eleB         b;

  a.Accept(visitor);
  b.Accept(visitor);
}
