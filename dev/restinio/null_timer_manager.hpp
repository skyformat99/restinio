/*
	restinio
*/

/*!
	No-op timer factory implementation.
*/

#pragma once

#include <chrono>

#include <asio.hpp>

#include <restinio/timer_common.hpp>

namespace restinio
{

//
// null_timer_manager_t
//

//! Timer factory implementation using asio timers.
struct null_timer_manager_t final
{
	//! Timer guard for async operations.
	struct timer_guard_t
	{
		// Schedule timeouts check invocation.
		template <typename... Args >
		constexpr void
		schedule( Args &&... ) const
		{}

		// Cancel timeout guard if any.
		constexpr void
		cancel() const
		{}
	};

	// Create guard for connection.
	constexpr timer_guard_t
	create_timer_guard() const
	{
		return timer_guard_t{};
	}

	//! Start/stop timer manager.
	//! \{
	constexpr void start() const {}
	constexpr void stop() const {}
	//! \}

	struct factory_t final
	{
		auto
		create( asio::io_context & ) const
		{
			return std::make_shared< null_timer_manager_t >();
		}
	};
};

} /* namespace restinio */
