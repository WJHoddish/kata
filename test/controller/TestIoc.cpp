// Created by Jiaheng on 2021/5/10.
// Copyright (c) 2021 Jiaheng Wang <wjhgeneral@outlook.com> All rights reserved.
//

#include <Test.h>

#include "kata/controller/ioc.h"

struct Base {
  virtual ~Base() = default;

  virtual void Run() = 0;
};

struct DerivedB : public Base {
  CLASS(DerivedB)

  void Run() override { std::cout << "DerivedB::Run()" << std::endl; }
};

struct DerivedC : public Base {
  explicit DerivedC(int data)
      : m_data(data) {}

  void Run() override {
    std::cout << "DerivedC::Run()" << '\t' << m_data << std::endl;
  }

  int m_data;
};

struct A {
  explicit A(Base* p)
      : m_p(p) {
    print("A(Base*)");
  }

  ~A() {
    print("~A()");

    DELETE(m_p)
  }

  void Run() const { m_p->Run(); }

  Base* m_p;
};

TEST(TestController, ioc) {
  using namespace kata;

  Ioc ioc;

  ioc.RegisterType<A, DerivedB>("B");
  auto b = ioc.ResolveShared<A>("B");

  b->Run();

  ioc.RegisterType<A, DerivedC, int>("C");
  auto c = ioc.ResolveShared<A>("C", 99);

  c->Run();
}
