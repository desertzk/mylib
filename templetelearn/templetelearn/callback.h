#pragma once
#include"intrusive_ptr.h"
#include<stdexcept>

class  atomic_counter {
public:
	///
	/// Create a counter with initial value v
	///
	explicit atomic_counter(long v);
	~atomic_counter();

	///
	/// Increment and return the result after increment atomically
	///
	long operator++()
	{
		return inc();
	}
	///
	/// Decrement and return the result after decrement atomically
	///
	long operator--()
	{
		return dec();
	}
	///
	/// Return current value - atomically
	///
	operator long() const
	{
		return get();
	}
private:
	long inc();
	long dec();
	long get() const;

	atomic_counter(atomic_counter const&);
	atomic_counter& operator=(atomic_counter const&);

	mutable union {
		int i;
		unsigned ui;
		long l;
		unsigned long ul;
		long long ll;
		unsigned long long ull;
	} value_;
	// Is actually used for platforms without lock
	// it would not be used when atomic operations
	// available
	void* mutex_;
};

class refcounted;
void intrusive_ptr_add_ref(refcounted* ptr);
void intrusive_ptr_release(refcounted* ptr);

///
/// brief This class is used as base class for reference counted
/// objects that use intrusive_ptr. Deriving from this class
/// allows simple way to manage reference counting for single object
///
class refcounted {
public:
	refcounted() :
		refs_(0)
	{
	}

	virtual ~refcounted()
	{
	}

private:
	friend void intrusive_ptr_add_ref(refcounted*);
	friend void intrusive_ptr_release(refcounted*);

	refcounted(refcounted const& other);
	refcounted const& operator=(refcounted const& other);
	atomic_counter refs_;
};

///
/// Increase reference count
///	
inline void intrusive_ptr_add_ref(refcounted* p)
{
	++p->refs_;
}
///
/// Decrease reference count, if it goes to 0, destroy the object
///
inline void intrusive_ptr_release(refcounted* p)
{
	if (p && --p->refs_ == 0)
		delete p;
}






template<typename Type>
class callback;

template<typename Type>
struct callable;
///
/// \brief this exception is thrown in case of calling unassigned/empty
/// function
///
class bad_callback_call : public std::runtime_error {
public:
	bad_callback_call() :
		std::runtime_error("bad_callback_call")
	{
	}
};

template<typename Result, typename P1>
struct callable<Result(P1)> :public refcounted
{
	virtual Result operator()(P1 a1) = 0;
	virtual ~callable() {}
};

template<typename Result ,typename P1 >
class callback<Result(P1)>
{
public:
	typedef Result result_type;

	typedef callable<Result(P1)>
		callable_type;
	typedef intrusive_ptr<callable_type> pointer_type;

	template<typename R, typename F>
	struct callable_impl : public callable_type {

		F func;
		callable_impl(F f) : func(f) {}
		virtual R operator()(P1 a1)
		{
			return func(a1);
		}
	};

	template<typename F>
	struct callable_impl<void, F> : public callable_type {

		F func;
		callable_impl(F f) : func(f) {}
		virtual void operator()(P1 a1)
		{
			func(a1);
		}
	};

	callback() {}

	template<typename Call>
	callback(intrusive_ptr<Call> c) : call_ptr(c)
	{}

	template<typename Call>
	callback(std::auto_ptr<Call> ptr) : call_ptr(ptr.release())
	{}

	template<typename Call>
	callback const& operator=(intrusive_ptr<Call> c)
	{
		call_ptr = c; return *this;
	}

	template<typename Call>
	callback const& operator=(std::auto_ptr<Call> c)
	{
		call_ptr = 0; call_ptr = c.release(); return *this;
	}

	template<typename F>
	callback(F func) : call_ptr(new callable_impl<Result, F>(func))
	{}

	callback(callback const& other) : call_ptr(other.call_ptr) {}

	template<typename F>
	callback const& operator=(F func)
	{
		call_ptr = new callable_impl<Result, F>(func);
		return *this;
	}

	callback const& operator=(callback const& other)
	{
		if (this != &other) { call_ptr = other.call_ptr; }
		return *this;
	}

	Result operator()(P1 a1) const
	{
		if (!call_ptr.get()) throw bad_callback_call();
		return (*call_ptr)(a1);
	}

	bool empty() const { return call_ptr.get() == 0; }

	operator bool() const { return !empty(); }

	void swap(callback& other) { call_ptr.swap(other.call_ptr); }
	pointer_type const& get_pointer() const { return call_ptr; }
	pointer_type& get_pointer() { return call_ptr; }

private:
	pointer_type call_ptr;
};


