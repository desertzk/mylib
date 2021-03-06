#pragma once
#include<stdexcept>
#include"clone_ptr.h"
namespace ztest {


template<typename Type>
class function;

///
/// \brief This exception is thrown in case of an attempt to call to
/// unassigned \ref booster::function
///
class bad_function_call : public std::runtime_error {
public:
	bad_function_call() :
		std::runtime_error("bad_function_call")
	{
	}
};



#define BOOSTER_TEMPLATE_PARAMS
#define BOOSTER_TEMPLATE_TYPE_PARAMS
#define BOOSTER_TYPE_PARAMS
#define BOOSTER_CALL_PARAMS
template<typename Result BOOSTER_TEMPLATE_PARAMS >			
class function<Result(BOOSTER_TEMPLATE_TYPE_PARAMS)>			
{									
public:									
	typedef Result result_type;					
	struct callable {
	
		virtual Result call(BOOSTER_TYPE_PARAMS) = 0;		
		virtual callable* clone() const = 0;			
		virtual ~callable() {}					
};								

template<typename R, typename F>					
struct callable_impl : public callable {
		
			F func;							
			callable_impl(F f) : func(f) {}				
			virtual R call(BOOSTER_TYPE_PARAMS) 			
		{  return func(BOOSTER_CALL_PARAMS); }			
			virtual callable* clone() const				
		{ return new callable_impl<R, F>(func); }		
	};								
		template<typename F>						
			struct callable_impl<void, F> : public callable {
			
				F func;							
				callable_impl(F f) : func(f) {}				
				virtual void call(BOOSTER_TYPE_PARAMS) 			
			{  func(BOOSTER_CALL_PARAMS); }				
				virtual callable* clone() const				
			{ return new callable_impl<void, F>(func); }		
		};								
			function() {}							
				template<typename F>						
				function(F func) : call_ptr(new callable_impl<Result, F>(func)) 	
			{}								
				function(function const& other) : call_ptr(other.call_ptr) {}	
				template<typename F>						
				function const& operator=(F func)				
			{ 								
				call_ptr.reset(new callable_impl<Result, F>(func));	
				return *this;						
			}								
				function const& operator=(function const& other)		
			{ 								
				if (this != &other) { call_ptr = other.call_ptr; } 	
					return *this;						
			}								
				Result operator()(BOOSTER_TYPE_PARAMS) const			
				{ 								
					if (!call_ptr.get()) throw bad_function_call();		
						return call_ptr->call(BOOSTER_CALL_PARAMS); 		
				}								
					bool empty() const { return call_ptr.get() == 0; }		
						operator bool() const { return !empty(); }			
						void swap(function& other) { call_ptr.swap(other.call_ptr); }	
private:								
						clone_ptr<callable> call_ptr;					
};									

#undef BOOSTER_TEMPLATE_PARAMS
#undef BOOSTER_TEMPLATE_TYPE_PARAMS
#undef BOOSTER_TYPE_PARAMS
#undef BOOSTER_CALL_PARAMS


}