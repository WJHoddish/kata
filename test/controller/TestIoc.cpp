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
  CLASS_FUNCTION(DerivedB)

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

struct D {
  explicit D(Base* p)
      : m_p(p) {
    print("D(Base*)");
  }

  ~D() {
    print("~D()");

    DELETE(m_p)
  }

  void Run() const { m_p->Run(); }

  Base* m_p;
};

TEST(TestController, ioc) {
  using namespace kata;

  Ioc ioc;

  ioc.RegisterType<D, DerivedB>("B");
  auto b = ioc.ResolveShared<D>("B");

  b->Run();

  ioc.RegisterType<D, DerivedC, int>("C");
  auto c = ioc.ResolveShared<D>("C", 99);

  c->Run();
}
