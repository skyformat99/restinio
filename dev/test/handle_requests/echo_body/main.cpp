/*
	restinio
*/

/*!
	Tests for settings parameters that have default constructor.
*/

#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>

#include <asio.hpp>

#include <restinio/all.hpp>

#include "../common/pub.hpp"

TEST_CASE( "HTTP echo server" , "[echo]" )
{
	using http_server_t = restinio::http_server_t<>;

	http_server_t http_server{
		restinio::create_child_io_service( 1 ),
		[]( auto & settings ){
			settings
				.port( utest_default_port() )
				.address( "127.0.0.1" )
				.request_handler( []( auto req, auto conn ){

					if( restinio::http_method_post() == req->m_header.method() )
					{
						restinio::response_builder_t{ req->m_header, std::move( conn ) }
							.append_header( "Server", "RESTinio utest server" )
							.append_header_date_field()
							.append_header( "Content-Type", "text/plain; charset=utf-8" )
							.set_body( req->m_body )
							.done();

						return restinio::request_accepted();
					}

					return restinio::request_rejected();
				} );
		}
	};

	http_server.open();

	std::string response;
	auto create_request = []( const std::string & body ){
		return
			"POST /data HTTP/1.0\r\n"
			"From: unit-test\r\n"
			"User-Agent: unit-test\r\n"
			"Content-Type: application/x-www-form-urlencoded\r\n"
			"Content-Length: " + std::to_string( body.size() ) + "\r\n"
			"Connection: close\r\n"
			"\r\n" +
			body;
	};

	{
		const auto body = "01234567890123456789";
		REQUIRE_NOTHROW( response = do_request( create_request( body ) ) );

		REQUIRE_THAT( response, Catch::Matchers::EndsWith( body ) );
	}

	{
		const auto body =
			"0123456789012345678901234567890123456789\r\n"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ\r\n"
			"abcdefghijklmnopqrstuvwxyz\r\n"
			"~!@#$%^&*()_+";

		REQUIRE_NOTHROW( response = do_request( create_request( body ) ) );

		REQUIRE_THAT( response, Catch::Matchers::EndsWith( body ) );
	}

	{
		const std::string body( 2048, 'a' );

		REQUIRE_NOTHROW( response = do_request( create_request( body ) ) );

		REQUIRE_THAT( response, Catch::Matchers::EndsWith( body ) );
	}

	http_server.close();
}