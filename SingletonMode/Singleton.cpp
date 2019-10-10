#include "stdafx.h"
#include "Singleton.h"


Singleton3 Singleton3::_instance;  

SingletonNotGood* SingletonNotGood::_pInstance;//这个得放cpp中，不然编译报错,静态成员默认赋null。
std::mutex SingletonNotGood::m_cs;//这个得放cpp中，不然编译报错,
SingletonNotGood::GarbageCollect SingletonNotGood::gc;//这个得放cpp中，不然编译报错,

std::unique_ptr<SingletonUsePtr> SingletonUsePtr::_ptr;//这个得放cpp中，不然编译报错,

std::mutex SingletonUsePtr::m_cs;

std::unique_ptr<SingletonUsePtr2> SingletonUsePtr2::_ptr;

std::mutex SingletonUsePtr2::m_cs;
