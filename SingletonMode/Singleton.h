#pragma once



#define SINGLETON_CTOR(x) \
     private:\
            x() = default;\
			x(const x&)=delete;\
			x& operator=(const x&)=delete;\
			~x()=default;

#define SINGLETON_INSTACNCE(x) SINGLETON_CTOR(x)\
	public:\
	static x* Instance()\
	{static x _instance; return &_instance;}


class Singleton
{
	SINGLETON_CTOR(Singleton);
public:
	static Singleton& Instance()
	{
		static Singleton _instance;
		return _instance;
	}	
};

class Singleton2
{
	SINGLETON_CTOR(Singleton2);
public:
	static Singleton2* Instance()
	{
		static Singleton2 _instance;
		return &_instance;
	}
};

class SingletonOnceMore
{
	SINGLETON_INSTACNCE(SingletonOnceMore);
public:
	void fun(){}
};
class SingletonTwiceMore
{
	SINGLETON_INSTACNCE(SingletonTwiceMore);
public:
	void fun(){}
};



class Singleton3
{
	SINGLETON_CTOR(Singleton3);
public:
	static Singleton3* Instance()
	{
		return &_instance;
	}

	static Singleton3 _instance;
};

#include <mutex>

class SingletonNotGood
{
	SINGLETON_CTOR(SingletonNotGood);
public:
	static SingletonNotGood* Instance()
	{
		if (!_pInstance)  //读操作1
		{
			std::lock_guard<std::mutex> lock_(m_cs);  //只有空的情况下才加锁
			if (!_pInstance)
			{
				_pInstance = new SingletonNotGood;  //写操作2
			}
		}
		return _pInstance;
	}
	static void Release()  
	{
		std::lock_guard<std::mutex> lock_(m_cs);
		if (!_pInstance)
		{
			delete _pInstance;
			_pInstance = nullptr;
		}
	}

private:
	struct GarbageCollect
	{
		~GarbageCollect()
		{
			if (!_pInstance)
			{
				delete _pInstance;
				_pInstance = nullptr;
			}
		}
	};

private:
	static SingletonNotGood* _pInstance;
	static std::mutex m_cs;
	static GarbageCollect gc;
};


#include <memory>
class SingletonUsePtr
{
	SINGLETON_CTOR(SingletonUsePtr);
public:
	static SingletonUsePtr& Instance()
	{
		if (!_ptr)  //读操作1
		{
			std::lock_guard<std::mutex> lock_(m_cs);  //只有空的情况下才加锁
			if (!_ptr)
			{
				_ptr.reset(new SingletonUsePtr);
			}
		}
		return *_ptr;
	}
private:
	static std::unique_ptr<SingletonUsePtr> _ptr;
	static std::mutex m_cs;
};

class SingletonUsePtr2
{
	SINGLETON_CTOR(SingletonUsePtr2);
public:
	static SingletonUsePtr2& Instance()
	{
		static std::once_flag s_flag;
		std::call_once(s_flag, [&]() {
			_ptr.reset(new SingletonUsePtr2);
		});

		return *_ptr;
	}
private:
	static std::unique_ptr<SingletonUsePtr2> _ptr;
	static std::mutex m_cs;
};

//采用模板再实现一次,
//使用方法 class YourSingleton: public SingletonBase<YourSingleton>
template<typename T>  //T 是子类
class SingletonBase
{
	SINGLETON_CTOR(SingletonBase);  //这个还是可以用的
public:
	static T&  Instance()
	{
		static T t;   //饿汉式
		return t;
	}
};

//再加上今天的学习的std::once_call实现懒汉式
template<typename T>  //T 是子类
class SingletonBaseLazy
{
	SINGLETON_CTOR(SingletonBaseLazy);  //这个还是可以用的
public:
	static T&  Instance()
	{
		static std::once_flag flag;
		std::call_once(flag, [&](){_ptr.reset(new T); });
		return *_ptr;
	}
	static std::unique_ptr<T> _ptr;
};
template<typename T>  
std::unique_ptr<T> SingletonBaseLazy<T>::_ptr;


#include <iostream>
class YourSingleton : public SingletonBaseLazy < YourSingleton >
{
public:
	void test()
	{
		std::cout << "hello word" << std::endl;
	}
};



