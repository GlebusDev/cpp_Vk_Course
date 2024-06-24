#pragma once

#include <string>

#include <sstream>

namespace Error{

    struct SyntaxError{};
    struct ArgumentCountError{};
};
template <class T>
concept HasOutputOperator =
    requires(std::ostream& stream, T arg) {
        {stream << arg} -> std::same_as<std::ostream&>;
}; //NOLINT

// чтобы компилятор не ругался на отсутствие функции не принимающей args
std::string formatOneArg(std::string expr, size_t index) {return "";}

void checkString(std::string expr, size_t argCount) {
    size_t realArgsCount = 0;
    size_t firstBracket = expr.find("{");
    while (firstBracket != std::string::npos)
    {
        size_t secondBracket = expr.find("}");
        if (secondBracket == std::string::npos)
            throw Error::SyntaxError();
        std::string tempNumString = "";
        for (size_t i = firstBracket + 1; i < secondBracket; i++) {
            if (!isdigit(expr[i]))
                throw Error::SyntaxError();
            tempNumString.push_back(expr[i]);
        }
        size_t tempNum;
        try {
            tempNum = std::stoul(tempNumString);
        } catch(...) {
            throw Error::SyntaxError();
        }
        if ((tempNum < 0) || (tempNum >= argCount))
            throw Error::ArgumentCountError();
        expr.erase(firstBracket, secondBracket+1);
        firstBracket = expr.find("{");
    }
    if (expr.find("}") != std::string::npos)
        throw Error::SyntaxError();
}

template <HasOutputOperator Arg, HasOutputOperator...  Args>
std::string formatOneArg(std::string expr, size_t index, Arg arg, Args... args) {
    std::string brackets = "{"+std::to_string(index)+"}";
    size_t position = expr.find(brackets);
    std::stringstream streamArg;
    streamArg << arg;
    while (position != std::string::npos) {
        expr.replace(position, brackets.length(), streamArg.str());
        position = expr.find(brackets);
    }
    if (sizeof...(args) == 0)
        return expr;
    else
        return formatOneArg(expr, ++index, args...);
}

template <HasOutputOperator... Args>
std::string format(std::string expr, Args... args) {
    checkString(expr, sizeof...(args));
    return formatOneArg(expr, 0, args...);
}
