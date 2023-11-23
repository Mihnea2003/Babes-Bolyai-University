cmake_minimum_required(VERSION 3.24)
project(OOP_lab4)

set(CMAKE_CXX_STANDARD 17)

add_executable(OOP_lab4 main.cpp Domain.cpp Domain.h DynamicArray.h Service.h Repository.h Repository.cpp errors.h errors.cpp Service.cpp Ui.cpp Ui.h UserRepository.h UserRepository.cpp UserService.h UserService.cpp Tests.h Tests.cpp)
