cmake_minimum_required(VERSION 2.8)
project(saber_stl)

set (CMAKE_CXX_STANDARD 14)

include_directories(./include)

aux_source_directory(./src GENERAL_SRC)
add_library(saber ${GENERAL_SRC})

add_executable(AllocatorTest "./testcase/testcase_allocator.cpp")
add_executable(DequeTest "./testcase/testcase_deque.cpp")
add_executable(ForwardListTest "./testcase/testcase_flist_1.cpp")
add_executable(FreeTreeTest "./testcase/testcase_freetree.cpp")
add_executable(IteratorTest "./testcase/testcase_iterator.cpp")
add_executable(ListTest "./testcase/testcase_list.cpp")
add_executable(SetTest "./testcase/testcase_set_1.cpp")
add_executable(TraitsTest "./testcase/testcase_traits.cpp")
add_executable(VectorTest "./testcase/testcase_vector.cpp")

target_link_libraries(AllocatorTest saber)
target_link_libraries(DequeTest saber)
target_link_libraries(ForwardListTest saber)
target_link_libraries(FreeTreeTest saber)
target_link_libraries(IteratorTest saber)
target_link_libraries(ListTest saber)
target_link_libraries(SetTest saber)
target_link_libraries(TraitsTest saber)
target_link_libraries(VectorTest saber)
