// SingletonMode.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include "Singleton.h"

void test()
{
	
}

int _tmain(int argc, _TCHAR* argv[])
{
	YourSingleton::Instance().test();
	YourSingleton::Instance().test();
	return 0;
}

