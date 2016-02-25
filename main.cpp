#include <iostream>

#ifdef _CPP11_STL_
	#include<memory>
	using namespace std;
#else
	#include "smartPtr.h"
#endif

struct CC {int* data;};

int construct_test(){
	shared_ptr<int> p1;
	shared_ptr<int> p2 (nullptr);
	shared_ptr<char> p3 (new char);
	
	shared_ptr<int> p6 (p1);
	shared_ptr<char> p66 (p3);
	shared_ptr<char> p67 (p66);
	
	shared_ptr<char> p7 (std::move(p67));
	
	
	std::cout << "use_count:\n";
	std::cout << "p1: " << p1.use_count() << '\n';
	std::cout << "p2: " << p2.use_count() << '\n';
	std::cout << "p3: " << p3.use_count() << '\n';
	std::cout << "p6: " << p6.use_count() << '\n';
	std::cout << "p66: " << p66.use_count() << '\n';
	std::cout << "p67: " << p67.use_count() << '\n';
	std::cout << "p7: " << p7.use_count() << '\n';
	return 0;
}

int get_test(){
	int* p = new int (10);
	shared_ptr<int> a (p);
	shared_ptr<int> a2 (a);
	shared_ptr<int> a3 (a2);

	if (a.get()==p) std::cout << "a and p point to the same location\n";

	// three ways of accessing the same address:
	std::cout << *a.get() << "\n";
	std::cout << *a << "\n";
	std::cout << *p << "\n";

	if (a2.get()==p) std::cout << "a2 and p point to the same location\n";
	if (a3.get()==p) std::cout << "a3 and p point to the same location\n";
	
	std::cout << *a2.get() << "\n";
	std::cout << *a3 << "\n";
	
	return 0;
}

int bool_test(){
	shared_ptr<int> foo;
	shared_ptr<int> bar (new int(34));

	if (foo) std::cout << "foo points to " << *foo << '\n';
	else std::cout << "foo is null\n";

	if (bar) std::cout << "bar points to " << *bar << '\n';
	else std::cout << "bar is null\n";
	return 0;
}


int value_of_test(){
	shared_ptr<int> foo (new int(3));
	std::cout << foo.use_count() << '\n';
	shared_ptr<int> bar (new int (100));
	std::cout << bar.use_count() << '\n';
	
	shared_ptr<int> foo2 (foo);
	std::cout << foo2.use_count() << '\n';
	std::cout << foo.use_count() << '\n';
	
	if(foo) std::cout << "foo: " << *foo << '\n';
	if(foo2) std::cout << "foo2: " << *foo2 << '\n';

	*foo = *bar * 2;
	
	if(bar) std::cout << "bar: " << *bar << '\n';
	if(foo) std::cout << "foo: " << *foo << '\n';
	if(foo2) std::cout << "foo2: " << *foo2 << '\n';

	return 0;
}

struct C { int a; int b; };

int member_of_test(){
	shared_ptr<C> foo;
	std::cout << foo.use_count() << '\n';
	shared_ptr<C> bar (new C);
	std::cout << bar.use_count() << '\n';
	shared_ptr<C> bar2 (foo);
	std::cout << bar2.use_count() << '\n';

	foo = bar;

	std::cout << foo.use_count() << '\n';
	std::cout << bar.use_count() << '\n';

	foo->a = 10;
	bar->b = 0;

	if (foo) std::cout << "foo: " << foo->a << ' ' << foo->b << '\n';
	if (bar) std::cout << "bar: " << bar->a << ' ' << bar->b << '\n';
	if (bar2) std::cout << "bar2: " << bar2->a << ' ' << bar2->b << '\n';

	bar->b = 20;

	if (foo) std::cout << "foo: " << foo->a << ' ' << foo->b << '\n';
	if (bar) std::cout << "bar: " << bar->a << ' ' << bar->b << '\n';
	if (bar2) std::cout << "bar2: " << bar2->a << ' ' << bar2->b << '\n';

	return 0;
}

int assign_test(){
	shared_ptr<int> foo;
	std::cout << foo.use_count() << '\n';
	shared_ptr<int> bar (new int(10));
	std::cout << bar.use_count() << '\n';

	foo = bar;                          // copy
	
	std::cout << foo.use_count() << '\n';
	std::cout << bar.use_count() << '\n';

	//std::unique_ptr<int> unique (new int(30));
	//foo = std::move(unique);            // move from unique_ptr

	if(foo) std::cout << "*foo: " << *foo << '\n';
	if(bar) std::cout << "*bar: " << *bar << '\n';
	
	shared_ptr<int> foo2 (std::move(foo));
	
	std::cout << foo.use_count() << '\n';
	std::cout << bar.use_count() << '\n';
	std::cout << foo2.use_count() << '\n';
	
	if(foo) std::cout << "*foo: " << *foo << '\n';
	if(bar) std::cout << "*bar: " << *bar << '\n';
	if(foo2) std::cout << "*foo2: " << *foo2 << '\n';
	
	return 0;
}

int reset_test(){
	shared_ptr<int> sp;  // empty
	std::cout << sp.use_count() << '\n';

	sp.reset (new int);       // takes ownership of pointer
	std::cout << sp.use_count() << '\n';
	*sp=10;
	std::cout << *sp << '\n';

	sp.reset (new int(300));       // deletes managed object, acquires new pointer
	std::cout << sp.use_count() << '\n';
	std::cout << *sp << '\n';
	*sp=20;
	std::cout << sp.use_count() << '\n';
	std::cout << *sp << '\n';

	sp.reset();               // deletes managed object
	std::cout << sp.use_count() << '\n';

	return 0;
}

int swap_test(){
	shared_ptr<int> foo (new int(10));
	shared_ptr<int> bar (new int(20));
	
	std::cout << foo.use_count() << '\n';
	std::cout << bar.use_count() << '\n';

	if(foo) std::cout << "*foo: " << *foo << '\n';
	if(bar) std::cout << "*bar: " << *bar << '\n';

	foo.swap(bar);

	std::cout << foo.use_count() << '\n';
	std::cout << bar.use_count() << '\n';

	if(foo) std::cout << "*foo: " << *foo << '\n';
	if(bar) std::cout << "*bar: " << *bar << '\n';

	return 0;
}


int unique_test(){
	shared_ptr<int> foo;
	shared_ptr<int> bar (new int);

	std::cout << "foo unique?\n" << std::boolalpha;

	std::cout << "1: " << foo.unique() << '\n';  // false (empty)
	std::cout << foo.use_count() << '\n';

	foo = bar;
	std::cout << "2: " << foo.unique() << '\n';  // false (shared with bar)
	std::cout << foo.use_count() << '\n';

	bar.reset();
	std::cout << "3: " << foo.unique() << '\n';  // true
	std::cout << foo.use_count() << '\n';

	return 0;
}

int main(){
	std::cout << "\nconstruct_test:\n";
	construct_test();
	std::cout << "\nget_test:\n";
	get_test();
	std::cout << "\nbool_test:\n";
	bool_test();
	std::cout << "\nvalue_of_test:\n";
	value_of_test();
	std::cout << "\nmember_of_test:\n";
	member_of_test();
	std::cout << "\nassign_test:\n";
	assign_test();
	std::cout << "\nreset_test:\n";
	reset_test();
	std::cout << "\nswap_test:\n";
	swap_test();
	std::cout << "\nunique_test:\n";
	unique_test();
	return 0;
}
