// Created by Modar Nasser on 11/09/2021.

#include "JavaWrapper.hpp"

using namespace ns;
using namespace ns::android;

JClass::JClass(const char* pname) : name(pname)
{}

auto JClass::object() -> jobject {
    return current_object;
}


JMethodBase::JMethodBase(JClass* pcls, const char* pname, const char* psig) :
cls(pcls),
name(pname),
sig(psig),
fullname(std::string(cls->name) + "/" + name)
{
    cls->methods.push_back(this);
}

