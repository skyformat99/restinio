#pragma once


#include <asio.hpp>

#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>


constexpr std::uint16_t
utest_default_port()
{
// Make it possible to run unit-tests for g++/clang in parallel.
#if defined(__clang__)
	return 8086;
#else
	return 8085;
#endif
}

template < typename LAMBDA >
void
do_with_socket(
	LAMBDA && lambda,
	const std::string & addr = "127.0.0.1",
	std::uint16_t port = utest_default_port() )
{
	asio::io_context io_context;
	asio::ip::tcp::socket socket{ io_context };

	asio::ip::tcp::resolver resolver{ io_context };
	asio::ip::tcp::resolver::query
		query{ asio::ip::tcp::v4(), addr, std::to_string( port ) };
	asio::ip::tcp::resolver::iterator iterator = resolver.resolve( query );

	asio::connect( socket, iterator );

	lambda( socket, io_context );
	socket.close();
}

inline std::string
do_request(
	const std::string & request,
	const std::string & addr = "127.0.0.1",
	std::uint16_t port = utest_default_port() )
{
	std::string result;
	do_with_socket(
		[ & ]( auto & socket, auto & /*io_context*/ ){

			asio::streambuf b;
			std::ostream req_stream(&b);
			req_stream << request;
			asio::write( socket, b );

			std::ostringstream sout;
			asio::streambuf response_stream;
			asio::read_until( socket, response_stream, "\r\n\r\n" );

			sout << &response_stream;

			// Read until EOF, writing data to output as we go.
			asio::error_code error;
			while( asio::read( socket, response_stream, asio::transfer_at_least(1), error) )
				sout << &response_stream;

			if ( error != asio::error::eof )
				throw asio::system_error(error);

			result = sout.str();
		},
		addr,
		port );

	return result;
}

template<typename Http_Server>
class other_work_thread_for_server_t
{
	Http_Server & m_server;

	std::thread m_thread;
public:
	other_work_thread_for_server_t(
		Http_Server & server )
		: m_server(server)
	{}

	void
	run()
	{
		m_thread = std::thread( [this] {
			m_server.open_sync();
			m_server.io_context().run();
		} );

		// Ensure server was started:
		std::promise< void > p;
		asio::post(
			m_server.io_context(),
			[&]{
				p.set_value();
			} );
		p.get_future().get();
	}

	void
	stop_and_join()
	{
		asio::post(
			m_server.io_context(),
			[&]{
				m_server.close_sync();
				m_server.io_context().stop();
			} );

		m_thread.join();
	}
};

