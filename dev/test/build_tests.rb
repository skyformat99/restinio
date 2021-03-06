#!/usr/bin/ruby
require 'mxx_ru/cpp'
require 'restinio/openssl_find.rb'
require 'restinio/pcre_find.rb'
require 'restinio/pcre2_find.rb'

MxxRu::Cpp::composite_target {

	required_prj( "test/header/prj.ut.rb" )
	required_prj( "test/default_constructed_settings/prj.ut.rb" )
	required_prj( "test/ref_qualifiers_settings/prj.ut.rb" )
	required_prj( "test/buffers/prj.ut.rb" )
	required_prj( "test/response_coordinator/prj.ut.rb" )
	required_prj( "test/string_view/prj.ut.rb" )
	required_prj( "test/from_string/prj.ut.rb" )
	required_prj( "test/uri_helpers/prj.ut.rb" )

	if not $sanitizer_build or $sanitizer_build != 'thread_sanitizer'
		required_prj( "test/socket_options/prj.ut.rb" )
	end

	if RestinioOpenSSLFind.has_openssl(toolset)
		if not $sanitizer_build or $sanitizer_build != 'thread_sanitizer'
			required_prj( "test/socket_options_tls/prj.ut.rb" )
		end
	end

	required_prj( "test/start_stop/prj.ut.rb" )

	required_prj( "test/handle_requests/method/prj.ut.rb" )
	required_prj( "test/handle_requests/echo_body/prj.ut.rb" )
	required_prj( "test/handle_requests/timeouts/prj.ut.rb" )
	required_prj( "test/handle_requests/slow_transmit/prj.ut.rb" )
	required_prj( "test/handle_requests/throw_exception/prj.ut.rb" )
	required_prj( "test/handle_requests/user_controlled_output/prj.ut.rb" )
	required_prj( "test/handle_requests/chunked_output/prj.ut.rb" )
	required_prj( "test/handle_requests/output_and_buffers/prj.ut.rb" )

	required_prj( "test/http_pipelining/sequence/prj.ut.rb" )
	required_prj( "test/http_pipelining/timeouts/prj.ut.rb" )


	# ================================================================
	# Express router
	required_prj( "test/router/express/prj.ut.rb" )
	required_prj( "test/router/express_router/prj.ut.rb" )
	required_prj( "test/router/express_router_bench/prj.rb" )

	if RestinioPCREFind.has_pcre(toolset)
		required_prj( "test/router/express_pcre/prj.ut.rb" )
		required_prj( "test/router/express_router_pcre/prj.ut.rb" )
		required_prj( "test/router/express_router_pcre_bench/prj.rb" )
	end

	if RestinioPCRE2Find.has_pcre2(toolset)
		required_prj( "test/router/express_pcre2/prj.ut.rb" )
		required_prj( "test/router/express_router_pcre2/prj.ut.rb" )
		required_prj( "test/router/express_router_pcre2_bench/prj.rb" )
	end

	required_prj( "test/router/cmp_router_bench/prj.rb" )

	# ================================================================
	required_prj( "test/encoders/prj.ut.rb" )

	# ================================================================
	# Benches for implementation tuning.
	required_prj( "test/to_lower_bench/prj.rb" )

	# ================================================================
	# Websocket tests

	required_prj( "test/handle_requests/upgrade/prj.ut.rb" )
	required_prj( "test/websocket/parser/prj.ut.rb" )
	required_prj( "test/websocket/validators/prj.ut.rb" )
	required_prj( "test/websocket/ws_connection/prj.ut.rb" )
}
