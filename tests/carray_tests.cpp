// Copyright 2018 (с) The Creep Brothers. All rights reserved.
// Created by antidotcb on 08/29/18.
//
#include "carray_tests.h"

namespace g5_task
{
namespace test
{
namespace helpers
{
int Helper::m_s_Instances = 0;
int Helper::m_s_CtorCalls = 0;
int Helper::m_s_DtorCalls = 0;

int Object::m_s_Instances = 0;
int Object::m_s_CtorCalls = 0;
int Object::m_s_DtorCalls = 0;
int Object::m_s_CopyCtorCalls = 0;
int Object::m_s_MoveCtorCalls = 0;
int Object::m_s_CopyAssignCalls = 0;
int Object::m_s_MoveAssignCalls = 0;

}  // namespace helpers

}  // namespace test

}  // namespace g5_task
