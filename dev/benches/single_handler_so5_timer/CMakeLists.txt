set(BENCH _bench.restinio.single_handler_so5_timer)
add_executable(${BENCH} main.cpp)
target_link_libraries(${BENCH} nodejs_http_parser)
target_link_libraries(${BENCH} ${SOBJECTIZER_LIBS})

if(WIN32)
	target_link_libraries(${BENCH} wsock32 ws2_32)
endif()

install(TARGETS ${BENCH} DESTINATION bin)
