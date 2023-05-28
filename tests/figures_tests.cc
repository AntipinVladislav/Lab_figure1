#include <gtest/gtest.h>

#include <functions/figure_functions.h>

#include <stdexcept>

#include <iostream>


using namespace vlad;

TEST(FunctionsTests, LenOfPoints_Test1) {
    Point p1 = { -2,2 }, p2 = { 2,-1 };
    float len = p1.LenOfPoints(p2);
    EXPECT_NEAR(len, 5, 0.1);
}

TEST(FunctionsTests, GetType_Test2) {
    Point test_points[4] = { -2,2, 2,2, 2,-2, 0,0 };
    Figure test_figure(triangle, test_points);
    FigureType test_type = test_figure.GetType();
    EXPECT_EQ(test_type, triangle);
}

TEST(FunctionsTests, GetCoordinate_Test3) {
    Point test_points[4] = { -2,2, 2,2, 2,-2, -2,-2 };
    Figure test_figure(rectangle, test_points);
    float testing_point = test_figure.GetCoordinate(2)[0];
    EXPECT_EQ(testing_point, 2);
}

TEST(FunctionsTests, GetPerimeter_ForCircle_Test4) {
    Point test_points[4] = { 0,0, 4,0, 1,-1,-1,-1 };
    Figure test_figure(circle, test_points);
    float test_perimeter = test_figure.GetPerimeter();
    EXPECT_NEAR(test_perimeter, 25, 12, 0.01);
}
TEST(FunctionsTests, GetPerimeter_ForTriangle_Test5) {
    Point test_points[4] = { 0,0, 0,3, 4,0, 0,0 };
    Figure test_figure(triangle, test_points);
    float test_perimeter = test_figure.GetPerimeter();
    EXPECT_NEAR(test_perimeter, 12, 0.1);
}
TEST(FunctionsTests, GetPerim_ForRectangle_Test6) {
    Point test_points[4] = { 2,2, 2,-2, -2,-2, -2,2 };
    Figure test_figure(rectangle, test_points);
    float test_perimeter = test_figure.GetPerimeter();
    EXPECT_NEAR(test_perimeter, 16, 0.1);
}
TEST(FunctionsTests, GetSquare_ForCircle_Test7) {
    Point test_points[4] = { 0,0, 0,10, 0,0, 0,0 };
    Figure test_figure(circle, test_points);
    float cur_square = test_figure.GetSquare();
    EXPECT_NEAR(cur_square, 314, 0.1);
}
TEST(FunctionsTests, GetSquare_ForTriangle_Test8) {
    Point test_points[4] = { 0,0, 0,3, 4,0, 0,0 };
    Figure test_figure(triangle, test_points);
    float cur_square = test_figure.GetSquare();
    EXPECT_NEAR(cur_square, 6, 0.1);
}
TEST(FunctionsTests, GetSquare_ForRectangle_Test9) {
    Point test_points[4] = { -2,-2, 2,2, 0,0, 0,0 };
    Figure test_figure(rectangle, test_points);
    float cur_square = test_figure.GetSquare();
    EXPECT_NEAR(cur_square, 16, 0.1);
}

TEST(FunctionsTests, SetMinFramingRectangle_ForCircle_Test10) {
    Point test_points[4] = { 0,1, 1,0, 0,-1,-1,0 };
    Figure test_figure(circle, test_points);
    Figure framing_rectangle;
    bool flag = false;
    Point true_points[4] = { 1,1, 1,-1, -1,-1, -1,1 };

    framing_rectangle.SetMinFramingRectangle(test_figure);
    Figure true_rectangle(rectangle, true_points);
    if (framing_rectangle == true_rectangle)
        flag = true;
    EXPECT_TRUE(flag);
}

TEST(FunctionsTests, SetMinFramingRectangle_ForTriangle_Test11) {
    Point test_points[4] = { 0,2, 3,0, -3,0, 0,0 };
    Figure test_figure(triangle, test_points);
    Figure framing_rectangle;
    bool flag = false;
    Point true_points[4] = { 3,3, 3,0, -3,0, -3,3 };

    framing_rectangle.SetMinFramingRectangle(test_figure);
    Figure true_rectangle(rectangle, true_points);
    if (framing_rectangle == true_rectangle)
        flag = true;
    EXPECT_TRUE(flag);
}

TEST(FunctionsTests, SetMinFramingRectangle_ForRectangle_Test12) {
    Point test_points[4] = { -4,-4, 4,-4, 4,4, -4,4 };
    Figure test_figure(rectangle, test_points);
    Figure framing_rectangle;
    bool flag = false;

    framing_rectangle.SetMinFramingRectangle(test_figure);
    if (framing_rectangle == test_figure)
        flag = true;
    EXPECT_TRUE(flag);
}

TEST(FunctionsTests, GetCount_Test13) {
    FigureArray test_figure_list;
    float test_points[8] = { -1,1,1,1,1,-1,-1,-1 };
    Figure test_figure;

    test_figure_list.AddFigure(test_figure.CreateRectangle(test_points));
    test_figure_list.AddFigure(test_figure.CreateRectangle(test_points));
    int quantity = test_figure_list.GetCount();
    EXPECT_EQ(quantity, 2);
}

TEST(FunctionsTests, InsertFigureOnIndex_GetFigureOnIndex_Test14) {
    FigureArray test_figure_list;
    float test_points_f[8] = { -1,1,1,1,1,-1,-1,-1 };
    float test_points_f2[8] = { -2,2,2,2,2,-2,-2,-2 };
    Figure test_figure1;
    bool flag = false;

    test_figure_list.AddFigure(test_figure1.CreateRectangle(test_points_f));
    test_figure_list.InsertFigureOnIndex(test_figure1.CreateRectangle(test_points_f2), 0);
    Figure test_figure2 = *test_figure_list.GetFigureOnIndex(0);

    if (test_figure2 == *test_figure1.CreateRectangle(test_points_f2)) {
        flag = true;
    }
    EXPECT_TRUE(flag);
}

TEST(FunctionsTests, AddFigure_Test15) {
    FigureArray test_figure_list;
    float test_points_f[8] = { -1,1,1,1,1,-1,-1,-1 };
    bool flag = false;
    Figure test_figure1;
    test_figure_list.AddFigure(test_figure1.CreateRectangle(test_points_f));
    Figure test_figure2 = *(test_figure_list.GetFigureOnIndex(1));


    if (test_figure2 == test_figure1) {
        flag = true;
    }
    EXPECT_TRUE(flag);
}

TEST(FunctionsTests, DeleteFigureOnIndex_Test16) {
    FigureArray test_figure_list;
    float test_points[] = { -1,1,1,1,1,-1,-1,-1 };
    Figure test_figure;


    test_figure_list.AddFigure(test_figure.CreateRectangle(test_points));
    Figure test_figure1 = *test_figure_list.GetFigureOnIndex(0);
    test_figure_list.DeleteFigureOnIndex(0);
    Figure test_figure2 = *test_figure_list.GetFigureOnIndex(0);

    bool flag = false;
    if ((test_figure2 == test_figure) && (test_figure1 == *test_figure.CreateRectangle(test_points))) {
        flag = true;
    }
    EXPECT_TRUE(flag);
}


TEST(FunctionsTests, GetFigureOnIndex_AddFigure_Test19) {
    FigureArray test_list;
    Point test_points[4] = { -1,1,1,1,1,-1,-1,-1 };
    Figure test_figure(rectangle, test_points);

    Figure test_figure2 = *test_list.GetFigureOnIndex(-1);
    bool flag = false;
    if (test_figure == test_figure2) {
        flag = true;
    }
    EXPECT_TRUE(flag);
}

