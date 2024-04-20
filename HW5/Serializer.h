#pragma once

#include <iostream>

#include <string>

#include <sstream>

enum class Error
{
    NoError,
    CorruptedArchive,
    WrongData
};

class Serializer
{
    static constexpr char Separator = ' ';
    std::ostream* out_;
public:
    explicit Serializer(std::ostream* out)
        : out_(out)
    {
    }

    template <class T>
    Error save(const T& object)
    {
        return object.serialize(this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT... args)
    {
        return process(args...);
    }
private:
    Error process(bool arg);
    Error process(uint64_t arg);
    template <class T>
    Error process(const T& arg) {
        return Error::WrongData;
    }
    template <class Arg, class... ArgsT>
    Error process(Arg arg, ArgsT... args) {
        Error first = process(arg);
        Error second = process(args...);
       
        if (first == second)
            return first;
        return Error::WrongData;
    }
};

class Deserializer {
    static constexpr char Separator = ' ';
    std::istream* in_;
public:
    explicit Deserializer(std::istream* in): in_(in) {}

    template <class T>
    Error load(T* object) {
        return (*object).deserialize(this);
    }
    template <class... Args>
    Error operator()(Args... args) {
        return process(args...);
    }

private:
    Error process(bool*);
    Error process(uint64_t*);

    template <class Arg, class... Args>
    Error process(Arg arg, Args... args) {
        Error first = process(arg);
        Error second = process(args...);
        if (first == second)
            return first;
        else
            return Error::CorruptedArchive;
    }
};
