// Created by Modar Nasser on 11/09/2021.

#include "JavaWrapper.hpp"

using namespace ns;
using namespace ns::android;

JClass::JClass(const char* pname) : name(pname)
{}

auto JClass::object() -> jobject {
    return current_object;
}

JClassMember::JClassMember(JClass* pcls, const char* pname) :
cls(pcls),
name(pname),
fullname(std::string(cls->name) + "/" + name)
{}


JMethodBase::JMethodBase(JClass* pcls, const char* pname, const char* psig) :
JClassMember(pcls, pname),
sig(psig)
{
    cls->methods.push_back(this);
}

JStaticMethodBase::JStaticMethodBase(JClass* pcls, const char* pname, const char* psig) :
JClassMember(pcls, pname),
sig(psig)
{
    cls->static_methods.push_back(this);
}


JStaticFieldBase::JStaticFieldBase(JClass* pcls, const char* pname, const char* ptype) :
JClassMember(pcls, pname),
type(ptype)
{
    cls->static_fields.push_back(this);
}
