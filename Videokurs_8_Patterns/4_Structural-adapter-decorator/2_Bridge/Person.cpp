#include "stdafx.h"
#include "Person.h"

struct Person::PersonImpl
{
  void greet(Person *p);
};

void Person::PersonImpl::greet(Person *p)
{
  printf("hello, my name is %s", p->name.c_str());
}

Person::Person()
  : impl(new PersonImpl)
{
}

Person::~Person()
{
  delete impl;
}

void Person::greet()
{ 
  impl->greet(this);
}
