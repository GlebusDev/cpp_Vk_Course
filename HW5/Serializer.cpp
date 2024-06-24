#include "Serializer.h"

Error Serializer::process(bool arg) {
    if (arg) 
        *out_ << "true";
    else
        *out_ << "false";
    *out_ << Separator;
    return Error::NoError;
}

Error Serializer::process(uint64_t arg) {
    *out_ << std::to_string(arg) << Separator;
    return Error::NoError;
}

Error Deserializer::process(bool* value) {
    std::string text;
    *in_ >> text;
    if (text == "true")
        *value = true;
    else if (text == "false")
        *value = false;
    else
        return Error::CorruptedArchive;
    return Error::NoError;
}

Error Deserializer::process(uint64_t* value) {
    std::string text;
    *in_ >> text;
    try {
        *value = std::stoull(text);
    } catch (std::exception ex) {
        return Error::CorruptedArchive;
    }
    return Error::NoError;
}
