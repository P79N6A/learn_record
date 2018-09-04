#include "gmock/gmock.h"
#include "gtest/gtest.h"

class Turtle {
    public:
    virtual ~Turtle() {}
    virtual void PenUp() = 0;
    virtual void PenDown() = 0;
    virtual void Forward(int distance) = 0;
    virtual void Turn(int degrees) = 0;
    virtual void GoTo(int x, int y) = 0;
    virtual int GetX() const = 0;
    virtual int GetY() const = 0;
};

class MockTurtle : public Turtle {
    public:
    MOCK_METHOD0(PenUp, void());
    MOCK_METHOD0(PenDown, void());
    MOCK_METHOD1(Forward, void(int distance));
    MOCK_METHOD1(Turn, void(int degrees));
    MOCK_METHOD2(GoTo, void(int x, int y));
    MOCK_CONST_METHOD0(GetX, int());
    MOCK_CONST_METHOD0(GetY, int());
};

using ::testing::AtLeast;
TEST(PainterTest, PenDownCall) {
    MockTurtle turtle;
    EXPECT_CALL(turtle, PenDown())
        .Times(AtLeast(2));
    // 期望这个函数在本次测试需要至少被调用2次
    // 否则报错

    turtle.PenDown();
    turtle.PenDown();
}

using ::testing::Return;
TEST(PainterTest, GetX) {
    MockTurtle turtle;
    EXPECT_CALL(turtle, GetX())
        .Times(4)
        .WillOnce(Return(100))
        .WillOnce(Return(150))
        .WillRepeatedly(Return(200));
    // 期望这个函数在本次测试需要被调用4次
    // 否则报错
    //第一次调用返回100， 第二次150，之后都是200
    EXPECT_EQ(turtle.GetX(), 100);
    EXPECT_EQ(turtle.GetX(), 150);
    EXPECT_EQ(turtle.GetX(), 200);
    EXPECT_EQ(turtle.GetX(), 200);
}

using ::testing::_;
using ::testing::Ge;
TEST(PainterTest, GoTo) {
    MockTurtle turtle;
    EXPECT_CALL(turtle, GoTo(_, 100));
    // 否则报错
    // 调用参数，第一个任意，第一个必须为 100
    turtle.GoTo(1, 100);

    EXPECT_CALL(turtle, GoTo(_, Ge(101)));
    turtle.GoTo(2, 101);
}

//sticky
TEST(PainterTest, GetY) {
    //设置调用按照期望设置顺序
    using ::testing::InSequence;
    InSequence dummyObj;

    MockTurtle turtle;
    EXPECT_CALL(turtle, GetY())
        .Times(2)
        .WillOnce(Return(100))
        .WillOnce(Return(150))
        .RetiresOnSaturation(); // 匹配后不再生效

    EXPECT_CALL(turtle, GetY())
        .Times(1)
        .WillOnce(Return(200))
        .RetiresOnSaturation();

    EXPECT_EQ(turtle.GetY(), 100);
    EXPECT_EQ(turtle.GetY(), 150);

    EXPECT_EQ(turtle.GetY(), 200);
}


int main(int argc, char** argv) {
    //初始化 gtest 和 gmock
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
