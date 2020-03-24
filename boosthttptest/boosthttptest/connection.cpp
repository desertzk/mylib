//
// connection.cpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2013 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "connection.hpp"
#include <utility>
#include <vector>
#include<string>
#include "connection_manager.hpp"
#include "request_handler.hpp"
#include<iostream>


using namespace std;

namespace http {
	namespace server {

		connection::connection(boost::asio::ip::tcp::socket socket,
			connection_manager& manager, request_handler& handler)
			: socket_(std::move(socket)),
			connection_manager_(manager),
			request_handler_(handler)
		{
		}

		void connection::start()
		{
			do_read();
		}

		void connection::stop()
		{
			socket_.close();
		}

		void connection::do_read()
		{
			cout << "do_read " << endl;
			auto self(shared_from_this());
			socket_.async_read_some(boost::asio::buffer(buffer_),
				[this, self](boost::system::error_code ec, std::size_t bytes_transferred)
				{
					if (!ec)
					{
						request_parser::result_type result;
						std::tie(result, std::ignore) = request_parser_.parse(
							request_, buffer_.data(), buffer_.data() + bytes_transferred);
						std::string reqstr(buffer_.data());
						cout << "async_read_some:"<< reqstr << endl;
						if (result == request_parser::good)
						{
							request_handler_.handle_request(request_, reply_);
							do_write();
						}
						else if (result == request_parser::bad)
						{
							reply_ = reply::stock_reply(reply::bad_request);
							do_write();
						}
						else
						{
							do_read();
						}
					}
					else if (ec != boost::asio::error::operation_aborted)
					{
						connection_manager_.stop(shared_from_this());
					}
				});
		}

		void connection::do_write()
		{
			cout << "do_write " << endl;
			auto self(shared_from_this());
			boost::asio::async_write(socket_, reply_.to_buffers(),
				[this, self](boost::system::error_code ec, std::size_t)
				{
					if (!ec)
					{
						//auto buf = reply_.to_buffers();
						//std::string rspstr(std::begin(buf), std::end(buf));
						cout << "async_write:" << reply_.content << endl;
						// Initiate graceful connection closure.
						boost::system::error_code ignored_ec;
						socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both,
							ignored_ec);
					}

					if (ec != boost::asio::error::operation_aborted)
					{
						connection_manager_.stop(shared_from_this());
					}
				});
		}

	} // namespace server
} // namespace http