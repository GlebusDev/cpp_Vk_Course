#include <gtest/gtest.h>

#include "Serializer.h"

struct Data
{
    uint64_t a;
    bool b;
    uint64_t c;

    template <class Serializer>
    Error serialize(Serializer* serializer) const
    {
        return (*serializer)(a, b, c);
    }

    template <class Deserializer>
    Error deserialize(Deserializer* deserializer) {
        return (*deserializer)(&a, &b, &c);
    }
};

// тест сериализатора
TEST(TestSerializer, SerializerTest) {
    Data obj {83454, false, 34841};
    std::stringstream stream;

    Serializer Serializer(&stream);
    auto error = Serializer.save(obj);

    ASSERT_EQ(Error::NoError, error);
    uint64_t a, c;
    bool b;

    std::string temp;
    stream >> temp;
    a = std::stoull(temp);
    stream >> temp;
    if (temp == "true")
        b = true;
    else
        b = false;
    stream >> temp;
    c = std::stoull(temp);


    ASSERT_EQ(83454, a);
    ASSERT_EQ(false, b);
    ASSERT_EQ(34841, c);
}

// тест десериализатора
TEST(TestSerializer, DeserializerTest) {
    std::stringstream stream;

    stream << "83454 " << "false " << "34841";
    Deserializer deserializer(&stream);
    Data obj;
    auto error = deserializer.load(&obj);

    ASSERT_EQ(Error::NoError, error);
    ASSERT_EQ(83454, obj.a);
    ASSERT_EQ(false, obj.b);
    ASSERT_EQ(34841, obj.c);
}

// тест из примера на github
TEST(TestSerializer, MainTest) {
    Data x { 1, true, 2 };

    std::stringstream stream;

    Serializer serializer(&stream);
    serializer.save(x);

    Data y { 0, false, 0 };

    Deserializer deserializer(&stream);
    const Error err = deserializer.load(&y);

    ASSERT_EQ(err, Error::NoError);

    ASSERT_EQ(x.a, y.a);
    ASSERT_EQ(x.b, y.b);
    ASSERT_EQ(x.c, y.c);
}

struct Data2
{
    uint64_t a;
    bool b;
    std::string c;

    template <class Serializer>
    Error serialize(Serializer* serializer) const
    {
        return (*serializer)(a, b, c);
    }

    template <class Deserializer>
    Error deserialize(Deserializer* deserializer) {
        return (*deserializer)(&a, &b, &c);
    }
};

// тест ошибки при сериализации
TEST(TestSerializer, SerializerErrorTest) {
    Data2 obj {83454, false, "hello"};
    std::stringstream stream;

    Serializer Serializer(&stream);
    auto error = Serializer.save(obj);

    ASSERT_EQ(Error::WrongData, error);
}

// тест ошибки при десерилизации
TEST(TestSerializer, DeserializerErrorTest) {
    std::stringstream stream;
    stream << "354322 " << "hello " << "-43243";

    Deserializer deserializer(&stream);
    Data obj;
    auto error = deserializer.load(&obj);
    ASSERT_EQ(error, Error::CorruptedArchive);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
