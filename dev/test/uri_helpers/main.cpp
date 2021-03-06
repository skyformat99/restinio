/*
	restinio
*/

/*!
	Tests for settings parameters that have default constructor.
*/

#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>

#include <restinio/uri_helpers.hpp>
#include <restinio/cast_to.hpp>

using namespace restinio;

TEST_CASE( "Escape percent encoding" , "[escape][percent_encoding]" )
{
	{
		const std::string input_data{
			"0123456789"
			"abcdefghijklmnopqrstuvwxyz"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"-~._" };
		const std::string expected_result{ input_data };

		std::string result;

		REQUIRE_NOTHROW( result = restinio::utils::escape_percent_encoding( input_data ) );

		REQUIRE( expected_result == result );
	}
	{
		const std::string input_data{
			"0123456789" " "
			"abcdefghijklmnopqrstuvwxyz" "\r\n"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ" ";"
			"-~._" };
		const std::string expected_result{
			"0123456789" "%20"
			"abcdefghijklmnopqrstuvwxyz" "%0D%0A"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ" "%3B"
			"-~._" };

		std::string result;

		REQUIRE_NOTHROW( result = restinio::utils::escape_percent_encoding( input_data ) );

		REQUIRE( expected_result == result );
	}
}

TEST_CASE( "Unescape percent encoding" , "[unescape][percent_encoding]" )
{
	{
		const std::string input_data{
			"0123456789"
			"abcdefghijklmnopqrstuvwxyz"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"-~._" };
		const std::string expected_result{ input_data };

		std::string result;

		REQUIRE_NOTHROW( result = restinio::utils::unescape_percent_encoding( input_data ) );

		REQUIRE( expected_result == result );
	}
	{
		const std::string input_data{
			"0123456789" "%20"
			"abcdefghijklmnopqrstuvwxyz" "%0D%0A"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ" "%3B"
			"-~._" };
		const std::string expected_result{
			"0123456789" " "
			"abcdefghijklmnopqrstuvwxyz" "\r\n"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ" ";"
			"-~._" };

		std::string result;

		REQUIRE_NOTHROW( result = restinio::utils::unescape_percent_encoding( input_data ) );

		REQUIRE( expected_result == result );
	}

	{
		const std::string input_data{
			"0123456789" "%20"
			"abcdefghijklmnopqrstuvwxyz" "%0d%0a"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ" "%3b"
			"-~._" };
		const std::string expected_result{
			"0123456789" " "
			"abcdefghijklmnopqrstuvwxyz" "\r\n"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ" ";"
			"-~._" };

		std::string result;

		REQUIRE_NOTHROW( result = restinio::utils::unescape_percent_encoding( input_data ) );

		REQUIRE( expected_result == result );
	}

	{
		const std::string input_data{
			"0123456789" "%20"
			"abcdefghijklmnopqrstuvwxyz" "%0D%ZA"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ" "%3B"
			"-~._" };

		std::string result;

		REQUIRE_THROWS( result = restinio::utils::unescape_percent_encoding( input_data ) );
	}

	{
		const std::string input_data{
			"0123456789" "%20"
			"abcdefghijklmnopqrstuvwxyz" "%0D%" };

		std::string result;

		REQUIRE_THROWS( result = restinio::utils::unescape_percent_encoding( input_data ) );
	}
	{
		const std::string input_data{
			"0123456789" "%20"
			"abcdefghijklmnopqrstuvwxyz" "%0D%0" };

		std::string result;

		REQUIRE_THROWS( result = restinio::utils::unescape_percent_encoding( input_data ) );
	}

	{
		const std::string input_data{ "+%20+" };
		const std::string expected_result{ "   "};

		std::string result;

		REQUIRE_NOTHROW( result = restinio::utils::unescape_percent_encoding( input_data ) );
		REQUIRE( expected_result == result );
	}
}

TEST_CASE( "In-place unescape percent encoding" , "[unescape][percent_encoding][inplace]" )
{
	{
		const std::string input_data{
			"0123456789" "%20"
			"abcdefghijklmnopqrstuvwxyz" "%0D%0A"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ" "%3B"
			"-~._" };
		const std::string expected_result{
			"0123456789" " "
			"abcdefghijklmnopqrstuvwxyz" "\r\n"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ" ";"
			"-~._" };

		std::string result = input_data;

		REQUIRE_NOTHROW( result.resize(
				restinio::utils::inplace_unescape_percent_encoding(
					&result[0], result.size() ) ) );

		REQUIRE( expected_result == result );
	}

	{
		const std::string input_data{
			"0123456789" "%20"
			"abcdefghijklmnopqrstuvwxyz" "%0d%0a"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ" "%3b"
			"-~._" };
		const std::string expected_result{
			"0123456789" " "
			"abcdefghijklmnopqrstuvwxyz" "\r\n"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ" ";"
			"-~._" };

		std::string result = input_data;

		REQUIRE_NOTHROW( result.resize(
				restinio::utils::inplace_unescape_percent_encoding(
					&result[0], result.size() ) ) );

		REQUIRE( expected_result == result );
	}

	{
		const std::string input_data{
			"0123456789" "%20"
			"abcdefghijklmnopqrstuvwxyz" "%0D%ZA"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ" "%3B"
			"-~._" };

		std::string result = input_data;

		REQUIRE_THROWS( result.resize(
				restinio::utils::inplace_unescape_percent_encoding(
					&result[0], result.size() ) ) );
	}

	{
		const std::string input_data{
			"0123456789" "%20"
			"abcdefghijklmnopqrstuvwxyz" "%0D%" };

		std::string result;

		REQUIRE_THROWS( result = restinio::utils::unescape_percent_encoding( input_data ) );
	}
	{
		const std::string input_data{
			"0123456789" "%20"
			"abcdefghijklmnopqrstuvwxyz" "%0D%0" };

		std::string result = input_data;

		REQUIRE_THROWS( result.resize(
				restinio::utils::inplace_unescape_percent_encoding(
					&result[0], result.size() ) ) );
	}

	{
		const std::string input_data{ "+%20+" };
		const std::string expected_result{ "   "};

		std::string result = input_data;

		REQUIRE_NOTHROW( result.resize(
				restinio::utils::inplace_unescape_percent_encoding(
					&result[0], result.size() ) ) );
		REQUIRE( expected_result == result );
	}
}

TEST_CASE( "Parse query params" , "[parse_query_string]" )
{
	{
		const std::string
			uri{ "/locations/25/avg?"
				"toDate=815875200&"
				"fromDate=1133136000&"
				"toAge=38&"
				"gender=f" };

		auto params = restinio::parse_query_string( uri );


		REQUIRE( 4 == params.size() );


		REQUIRE( params.has( "toDate" ) );
		REQUIRE( params.has( "fromDate" ) );
		REQUIRE( params.has( "toAge" ) );
		REQUIRE( params.has( "gender" ) );
		REQUIRE( restinio::cast_to< std::uint64_t >( params[ "toDate" ] ) == 815875200ULL );
		REQUIRE( restinio::cast_to< std::uint64_t >( params[ "fromDate" ] ) == 1133136000ULL );
		REQUIRE( restinio::cast_to< std::uint8_t >( params[ "toAge" ] ) == 38 );
		REQUIRE( restinio::cast_to< std::string >( params[ "gender" ] ) == "f" );
	}
	{
		const std::string
			uri{ "/users/36/visits?"
				"country=%D0%9C%D0%B0%D0%BB%D1%8C%D1%82%D0%B0" };

		auto params = restinio::parse_query_string( uri );

		REQUIRE( 1 == params.size() );

		REQUIRE( params.has( "country" ) );
		REQUIRE( params[ "country" ] == "\xD0\x9C\xD0\xB0\xD0\xBB\xD1\x8C\xD1\x82\xD0\xB0" );
	}

	{
		const std::string
			uri{ "/users/36/visits?"
				"my%20name=my%20value" };

		auto params = restinio::parse_query_string( uri );

		REQUIRE( 1 == params.size() );

		REQUIRE( params.has( "my name" ) );
		REQUIRE( params[ "my name" ] == "my value" );
	}

	{
		const std::string
			uri{ "/users/36/visits?"
				"k1=v1&k2=v2#fragment=value" };

		auto params = restinio::parse_query_string( uri );

		REQUIRE( 2 == params.size() );

		REQUIRE( params[ "k1" ] == "v1" );
		REQUIRE( params[ "k2" ] == "v2" );
	}
}

TEST_CASE( "Parse get params to std::multi_map" , "[parse_query_string_multi_map]" )
{
	{
		const std::string
			uri{ "/locations/25/avg?"
				"toDate=815875200&"
				"fromDate=1133136000&"
				"toAge=38&"
				"gender=f" };

		auto params = restinio::parse_query_string( uri );

		REQUIRE( 4 == params.size() );

		REQUIRE( params.has( "toDate" ) );
		REQUIRE( restinio::cast_to< std::int32_t >(params[ "toDate" ] ) == 815875200L );
		REQUIRE( params.has( "fromDate" ) );
		REQUIRE( restinio::cast_to< std::uint32_t >(params[ "fromDate" ] ) == 1133136000UL );
		REQUIRE( params.has( "toAge" ) );
		REQUIRE( restinio::cast_to< std::int8_t >(params[ "toAge" ] ) == 38 );
		REQUIRE( params.has( "gender" ) );
		REQUIRE( params[ "gender" ] == "f" );
	}
	{
		const std::string
			uri{ "/users/36/visits?"
				"country=%D0%9C%D0%B0%D0%BB%D1%8C%D1%82%D0%B0" };

		auto params = restinio::parse_query_string( uri );

		REQUIRE( 1 == params.size() );

		REQUIRE( params.has( "country" ) );
		REQUIRE( restinio::cast_to< std::string >( params[ "country" ] ) == "\xD0\x9C\xD0\xB0\xD0\xBB\xD1\x8C\xD1\x82\xD0\xB0" );
	}

	{
		const std::string
			uri{ "/users/36/visits?"
				"my%20name=my%20value" };

		auto params = restinio::parse_query_string( uri );

		REQUIRE( 1 == params.size() );

		REQUIRE( params.has( "my name" ) );
		REQUIRE( params[ "my name"] == "my value" );
	}

	{
		const std::string
			uri{ "/users/36/visits?"
				"k1=v1&k2=v2#fragment=value" };

		auto params = restinio::parse_query_string( uri );

		REQUIRE( 2 == params.size() );

		REQUIRE( params.has( "k1" ) );
		REQUIRE( params[ "k1" ] == "v1" );
		REQUIRE( params.has( "k2" ) );
		REQUIRE( params[ "k2" ] == "v2" );
	}
}
