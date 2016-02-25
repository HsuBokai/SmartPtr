
#ifndef _SMART_PTR_H_
#define _SMART_PTR_H_

template < class T >
class shared_ptr {
public:
	// shared_ptr<int> p;
	shared_ptr() : _ptr(NULL), _count(NULL) {}

	// shared_ptr<int> p(nullptr);
	shared_ptr(std::nullptr_t) : shared_ptr() {}

	// shared_ptr<int> p(new int);
	shared_ptr(T* p) : _ptr(p), _count( new long int(1) ) {}

	// shared_ptr<int> p6 (p5);
	shared_ptr (const shared_ptr& x) : _ptr(x._ptr), _count(x._count) {
		if(_ptr) _count[0]++;
	}

	// shared_ptr<int> p7 (std::move(p6));
	shared_ptr (shared_ptr<T>&& x) : _ptr(x._ptr), _count(x._count)  {
		x._ptr = NULL;
		x._count = NULL;
	}

	virtual ~shared_ptr() {
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

	void reset() {
		if(!_count) return;
		if(*_count==1){
			delete _ptr;
			_ptr = NULL;
			delete _count;
			_count = NULL;	
		}
		else if(*_count>1){
			_count[0]--;
			_ptr = NULL;
			_count = NULL;
		}
		else {
			std::cerr<<"Error!! *_count <=0 \n";
		}
	}

	void reset (T* p) {
		reset();
		_ptr = p;
		_count = new long int(1);
	}

	void swap (shared_ptr& x) {
		if(this==&x) return;
		T* temp = _ptr;
		_ptr = x._ptr;
		x._ptr = temp;
		return;
	}

	bool unique() const { return use_count()==1; }

	long int use_count() const { return (_count) ? *_count : 0; }
private:
	T* _ptr;
	long int * _count;
};

#endif

