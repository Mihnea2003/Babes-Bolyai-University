//
// Created by bro_b on 3/29/2023.
//

#ifndef OOP_LAB4_ERRORS_H
#define OOP_LAB4_ERRORS_H
#pragma once

#include <string>
#include <exception>

class ValueError : public std::exception {
private:
    const char* message;
public:
    explicit ValueError(const char* message);
    [[nodiscard]] const char* what() const noexcept;
};

class RepoError : public std::exception {
private:
    const char* message;
public:
    explicit RepoError(const char* message);
    [[nodiscard]] const char* what() const noexcept;
};
#endif //OOP_LAB4_ERRORS_H
