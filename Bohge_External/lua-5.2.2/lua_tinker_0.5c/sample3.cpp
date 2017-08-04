// sample3.cpp : LuaTinker �� Ŭ���� ����� �˾ƺ���.
//

extern "C" 
{
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
};

#include "lua_tinker.hpp"

struct A
{
	A(int v) : value(v) {}
	int value;
};

struct base
{
	base() {}

	const char* is_base(){ return "this is base"; }
};

class test : public base
{
public:
	test(int val) : _test(val) {}
	~test() {}

	const char* is_test(){ return "this is test"; }

	void ret_void() {}
	int ret_int()				{ return _test;			}
	int ret_mul(int m) const	{ return _test * m;		}
	int ret_mul() const			{ return _test;		}
	A get()						{ return A(_test);		}
	void set(A a)				{ _test = a.value;		}

	int _test;
};

test g_test(11);


int main()
{
	// Lua �� �ʱ�ȭ �Ѵ�.
	lua_State* L = luaL_newstate();

	// Lua �⺻ �Լ����� �ε��Ѵ�.- print() ���
	luaL_openlibs(L);
	// Lua ���ڿ� �Լ����� �ε��Ѵ�.- string ���
	luaopen_string(L);

	// base Ŭ������ Lua �� �߰��Ѵ�.
	lua_tinker::class_add<base>(L, "base");
	// base �� �Լ��� ����Ѵ�.
	lua_tinker::class_def<base>(L, "is_base", &base::is_base);

	// test Ŭ������ Lua �� �߰��Ѵ�.
	lua_tinker::class_add<test>(L, "test");
	// test �� base �� ��� �޾����� �˷��ش�.
	lua_tinker::class_inh<test, base>(L);
	// test Ŭ���� �����ڸ� ����Ѵ�.
	lua_tinker::class_con<test>(L, lua_tinker::constructor<test,int>);
	// test �� �Լ����� ����Ѵ�.
	lua_tinker::class_def<test>(L, "is_test", &test::is_test);
	lua_tinker::class_def<test>(L, "ret_void", &test::ret_void);
	lua_tinker::class_def<test>(L, "ret_int", &test::ret_int);
	lua_tinker::class_def<test, int (test::*)(int) const >(L, "ret_mul", &test::ret_mul);
	lua_tinker::class_def<test>(L, "get", &test::get);
	lua_tinker::class_def<test>(L, "set", &test::set);
	lua_tinker::class_mem<test>(L, "_test", &test::_test);
	
	// Lua ���� ����ȣ g_test �� �����͸� ����Ѵ�.
	lua_tinker::setglobal(L, "g_test", &g_test);

	// sample3.lua ������ �ε�/�����Ѵ�.
	lua_tinker::dofile(L, "D:\\Lord\\Librarys\\Bohge\\External\\lua-5.2.2\\lua_tinker_0.5c\\sample3.lua");

	// ���α׷� ����
	lua_close(L);

	return 0;
}
