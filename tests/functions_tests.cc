#include <gtest/gtest.h>

#include <functions/functions.h>

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
    float testing_point = test_figure.GetCoordinate(2).x;
    EXPECT_EQ(testing_point, 2);
}

TEST(FunctionsTests, GetPerimeter_ForCircle_Test4) {
    Point test_points[4] = { 0,0, 4,0, 1,-1,-1,-1 };
    Figure test_figure(circle, test_points);
    float test_perimeter = test_figure.GetPerimeter();
    EXPECT_NEAR(test_perimeter, 25,12, 0.01);
}
TEST(FunctionsTests, GetPerimeter_ForTriangle_Test5) {
    Point test_points[4] = { 0,0, 0,3, 4,0, 0,0 };
    Figure test_figure(triangle, test_points);
    float test_perimeter = test_figure.GetPerimeter();
    EXPECT_NEAR(test_perimeter, 12, 0.1);
}
TEST(FunctionsTests, GetPerim_ForRectangle_Test6) {
    Point test_points[4] = { -1,1, -1,-1, 7,-1, 7,1 };
    Figure test_figure(rectangle, test_points);
    float test_perimeter = test_figure.GetPerimeter();
    EXPECT_NEAR(test_perimeter, 20, 0.1);
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
    Point test_points[4] = { -2,2, 2,2, 2,-2, -2,-2 };
    Figure test_figure(rectangle, test_points);
    float cur_square = test_figure.GetSquare();
    EXPECT_NEAR(cur_square, 16, 0.1);
}

TEST(FunctionsTests, SetMinFramingRectangle_ForCircle_Test10) {
    Point test_points[4] = { -1,-1, -1,1, 0,0,0,0 };
    Figure test_figure(circle, test_points);
    Figure framing_rectangle;
    bool flag = false;
    Point true_points[4] = { 1,1, 1,-3, -3,-3, -3,1 };

    framing_rectangle.SetMinFramingRectangle(test_figure);
    Figure true_rectangle(rectangle, true_points);
    if (framing_rectangle == true_rectangle)
        flag = true;
    EXPECT_TRUE(flag);
}

TEST(FunctionsTests, SetMinFramingRectangle_ForTriangle_Test11) {
    Point test_points[4] = { 1,1, 3,1, 1,4, 0,0 };
    Figure test_figure(triangle, test_points);
    Figure framing_rectangle;
    bool flag = false;
    Point true_points[4] = { 1,1, 3,1, 3,4, 1,4 };
    
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
    Point test_points[4] = { -1,1,1,1,1,-1,-1,-1 };
    Figure test_figure(rectangle, test_points);

    test_figure_list.AddFigure(test_figure);
    test_figure_list.AddFigure(test_figure);
    int quantity = test_figure_list.GetCount();
    EXPECT_EQ(quantity, 2);
}

TEST(FunctionsTests, SetFigureOnIndex_GetFigureOnIndex_Test14) {
    FigureArray test_figure_list;
    Point test_points[4] = { -1,1,1,1,1,-1,-1,-1 };
    Figure test_figure1(rectangle, test_points);
    bool flag = false;

    test_figure_list.SetFigureOnIndex(test_figure1, 0);
    Figure test_figure2 = test_figure_list.GetFigureOnIndex(0);
    
    if (test_figure1 == test_figure2) {
        flag = true;
    }
    EXPECT_TRUE(flag);
}

TEST(FunctionsTests, AddFigure_Test15) {
    FigureArray test_figure_list;
    Point test_points[4] = { -1,1,1,1,1,-1,-1,-1 };
    bool flag = false;
    Figure test_figure1(rectangle, test_points);

    test_figure_list.SetFigureOnIndex(test_figure1, 0);

    test_figure_list.AddFigure(test_figure1);
    Figure test_figure2 = test_figure_list.GetFigureOnIndex(1);

    
    if (test_figure2 == test_figure1) {
        flag = true;
    }
    EXPECT_TRUE(flag);
}

TEST(FunctionsTests, DeleteFigureOnIndex_Test16) {
    FigureArray test_figure_list;
    Point test_points[4] = { -1,1,1,1,1,-1,-1,-1 };
    Figure test_figure(rectangle, test_points);
    Figure empty_figure;

    test_figure_list.AddFigure(test_figure);
    Figure test_figure1 = test_figure_list.GetFigureOnIndex(0);
    test_figure_list.DeleteFigureOnIndex(0);
    Figure test_figure2 = test_figure_list.GetFigureOnIndex(0);

    bool flag = false;
    if ((test_figure2 == empty_figure) && (test_figure1 == test_figure)) {
        flag = true;
    }
    EXPECT_TRUE(flag);
}

TEST(FunctionsTests, GetMinSquareFigure_Test17) {
    FigureArray test_figure_list;
    Point circle_points1[4] = { 0,0, 0,6, 0,0, 0,0 };
    Point circle_points2[4] = { 1,1, 8,1, 0,0, 0,0 };
    Point rectangle_points1[4] = { 7,7, 7,0, 0,0, 0,7 };
    Point rectangle_points2[4] = { 1,1, 1,2, 2,2, 2,1 };
    Point triangle_points[4] = { -6,0, 6,0, 0,6, 0,0 };

    Figure test_circle1(circle, circle_points1);
    Figure test_circle2(circle, circle_points2);
    Figure test_rectangle1(rectangle, rectangle_points1);
    Figure test_rectangle2(rectangle, rectangle_points2);
    Figure test_triangle(triangle, triangle_points);

    test_figure_list.AddFigure(test_circle1);
    test_figure_list.AddFigure(test_circle2);
    test_figure_list.AddFigure(test_rectangle1);
    test_figure_list.AddFigure(test_rectangle2);
    test_figure_list.AddFigure(test_triangle);

    Figure result_figure = test_figure_list.GetMinSquareFigure();
    bool flag = false;
    if (result_figure == test_rectangle2) {
        flag = true;
    }
    EXPECT_TRUE(flag);
}