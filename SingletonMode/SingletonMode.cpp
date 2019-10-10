// SingletonMode.cpp : 定义控制台应用程序的入口点。
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

