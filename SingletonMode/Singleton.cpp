#include "stdafx.h"
#include "Singleton.h"


Singleton3 Singleton3::_instance;  

SingletonNotGood* SingletonNotGood::_pInstance;//����÷�cpp�У���Ȼ���뱨��,��̬��ԱĬ�ϸ�null��
std::mutex SingletonNotGood::m_cs;//����÷�cpp�У���Ȼ���뱨��,
SingletonNotGood::GarbageCollect SingletonNotGood::gc;//����÷�cpp�У���Ȼ���뱨��,

std::unique_ptr<SingletonUsePtr> SingletonUsePtr::_ptr;//����÷�cpp�У���Ȼ���뱨��,

std::mutex SingletonUsePtr::m_cs;

std::unique_ptr<SingletonUsePtr2> SingletonUsePtr2::_ptr;

std::mutex SingletonUsePtr2::m_cs;
