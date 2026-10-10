add_executable(test_sha256 unit/test_sha256.cpp)
target_link_libraries(test_sha256 PRIVATE rfrp_core)
add_test(NAME test_sha256 COMMAND test_sha256)

add_executable(test_carver unit/test_carver.cpp)
target_link_libraries(test_carver PRIVATE rfrp_core)
add_test(NAME test_carver COMMAND test_carver)

add_executable(test_case unit/test_case.cpp)
target_link_libraries(test_case PRIVATE rfrp_core)
add_test(NAME test_case COMMAND test_case)
