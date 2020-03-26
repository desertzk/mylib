#include<memory>
#include<string>
#include"callback.h"
#include"function.h"
#include<iostream>
#include<utility>
#include<tuple>

//using std::string;
//using std::shared_ptr;
//using std::cout;
//using std::endl;
//using std::make_shared;
using namespace std;

class context {
public:
	static void dispatch(shared_ptr<string> const& pool, shared_ptr<context> const& self, std::string const& url)
	{
		printf("oooooooooooooooooooooooooooooooooooo");
	}
};



struct dispatcher {
	void (*func)(shared_ptr<string> const&, shared_ptr<context> const&, std::string const&);
	shared_ptr<string> pool;
	shared_ptr<context> ctx;
	std::string url;
	void operator()() {
		func(pool, ctx, url);
	}
};


void post(ztest::function<void()>  const& job)
{
	job();
}


template<typename  T> void execute_t(T&& args)
{
	cout << "ins" << args << endl;
}

template<typename ... T> void execute_impl(T&& ... args)
{
	//cout << "ins" << typeid(args).name << endl;
	execute_t(std::forward<T>(args));
}




template<class Tuple, std::size_t... Is>
void invoke(const Tuple& t,
	std::index_sequence<Is...>) {
	execute_impl(std::get<Is>(t)...);

}

//
//template<typename Tuple, typename size_t... I>
//void invoke(const Tuple& args, index_sequence<I...>) {
//	//execute_impl(std::get<I>(args)...);
//
//}


int main()
{
	tuple<double, char, std::string> t = make_tuple(3.8, 'A', "Lisa Simpson");
	//tuple<int,int,int> t1 = make_tuple(3, 4, 6);
	invoke(t, index_sequence_for<double, char, std::string>{});
	execute_impl( "1",2,"3" );

	dispatcher dt;
	dt.func = &context::dispatch;
	dt.pool = make_shared<string>();
	dt.ctx = make_shared<context>();
	dt.url = "/network/1/ap_list";
	post(dt);
	return 0;
}