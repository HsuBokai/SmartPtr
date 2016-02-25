
#ifndef _SMART_PTR_H_
#define _SMART_PTR_H_

template < class T >
class shared_ptr {
public:
	// shared_ptr<int> p;
	shared_ptr() : _ptr(NULL), _count(NULL) { std::cerr<<"default construct\n"; }

	// shared_ptr<int> p(nullptr);
	shared_ptr(std::nullptr_t) : shared_ptr() {}

	// shared_ptr<int> p(new int);
	shared_ptr(T* p) : _ptr(p), _count( new long int(1) ) { std::cerr<<"1\n"; }

	// shared_ptr<int> p (new int, std::default_delete<int>());
	template <class D> shared_ptr (T* p, D del)  : shared_ptr(p) {std::cerr<<"2\n";}
	template <class D> shared_ptr (std::nullptr_t p, D del) : shared_ptr() {std::cerr<<"3\n";}

	// shared_ptr<int> p (new int, std::default_delete<int>(), std::allocator<int>());
	template <class D, class Alloc> shared_ptr (T* p, D del, Alloc alloc)  : shared_ptr(p) {std::cerr<<"4\n";}
	template <class D, class Alloc> shared_ptr (std::nullptr_t p, D del, Alloc alloc) : shared_ptr() {std::cerr<<"5\n";}

	// shared_ptr<int> p6 (p5);
	shared_ptr (const shared_ptr& x) : _ptr(x._ptr), _count(x._count) {
		std::cerr<<"6\n";
		if(_ptr) _count[0]++;
	}
	// shared_ptr<int> p666 (weak_p);
	// explicit shared_ptr (const std::weak_ptr<T>& x) {std::cerr<<"8\n";}

	// shared_ptr<int> p7 (std::move(p6));

	shared_ptr (shared_ptr<T>&& x) : _ptr(x._ptr), _count(x._count)  {
		std::cerr<<"9\n";
		x._ptr = NULL;
		x._count = NULL;
	}

	// shared_ptr<int> p7777 (std::auto_ptr<int>(new int));
	shared_ptr (std::auto_ptr<T>&& x) {std::cerr<<"11\n";}

	// shared_ptr<int> p8 (std::unique_ptr<int>(new int));
	template <class D> shared_ptr (std::unique_ptr<T,D>&& x) : _ptr(x.get()), _count(new long int(1)) {
		std::cerr<<"12\n";
		x.reset();
	}

	// shared_ptr<int> p9 (obj, obj->data);
	template <class U> shared_ptr (const shared_ptr<U>& x, T* p) : _ptr(p), _count(new long int(2)) {std::cerr<<"13\n";}

	virtual ~shared_ptr() {
		std::cerr<<"destruct\n";
		reset();
	}

	T* get() const { return _ptr; }
	operator bool () const { return (_ptr) ? true : false; }
	const T& operator * () const { return *_ptr; }
	T& operator * () { return *_ptr; }
	T* operator -> () const { return _ptr; }

	shared_ptr<T>& operator = (const shared_ptr& x) {
		if (this==&x) return *this;
		reset();
		if(!x._ptr) return *this;
		_ptr = x._ptr;
		_count = x._count;
		_count[0]++;
		return *this;
	}

	shared_ptr<T>& operator = (shared_ptr&& x) {
		if (this==&x) return *this;
		reset();
		if(!x._ptr) return *this;
		_ptr = x._ptr;
		_count = x._count;
		x._ptr = NULL;
		x._count = NULL;
		return *this;
	}
	//template <class U> shared_ptr& operator = (const shared_ptr<U>& x) {}
	//template <class U> shared_ptr& operator = (shared_ptr<U>&& x) {}


	void reset() {
		std::cerr<<"empty reset\n";
		std::cerr << "_count: " << use_count() << "\n";
		if(!_ptr) return;
		switch(*_count){
			case 0: 
				std::cerr<<"Error!! *_count==0\n";
				return;
			case 1: 
				delete _ptr;
				_ptr = NULL;
				delete _count;
				_count = NULL;	
				return;
			default:
				_count[0]--;
				_ptr = NULL;
				_count = NULL;
				return;
		}
	}

	void reset (T* p) {
		std::cerr<<"U reset\n";
		reset();
		_ptr = p;
		_count = new long int(1);
	}
	//template <class U, class D> void reset (U* p, D del);
	//template <class U, class D, class Alloc> void reset (U* p, D del, Alloc alloc);

	void swap (shared_ptr& x) {
		if(this==&x) return;
		T* temp = _ptr;
		_ptr = x._ptr;
		x._ptr = temp;
		//_ptr = _ptr - x._ptr;
		//x._ptr = _ptr + x._ptr;
		//_ptr = x._ptr - _ptr;
		return;
	}

	bool unique() const { return use_count()==1; }

	long int use_count() const { return (_count) ? *_count : 0; }
private:
	T* _ptr;
	long int * _count;
};

#endif

