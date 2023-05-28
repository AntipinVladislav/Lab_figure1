#include <functions/figure_functions.h>

#include <cmath>
#include<stdexcept>
#include<iostream>

using namespace vlad;
using namespace std;


Point Figure::MinPoint(Point* coordinates) {
	float min_x = coordinates[0].x;
	float min_y = coordinates[0].y;
	for (int i = 1; i < 3; i++) {
		if (coordinates[i].x < min_x)
			min_x = coordinates[i].x;
		if (coordinates[i].y < min_y)
			min_y = coordinates[i].y;
	}
	Point result = { min_x, min_y };
	return result;
}

Point Figure::MaxPoint(Point* coordinates) {
	float max_x = coordinates[0].x;
	float max_y = coordinates[0].y;
	for (int i = 1; i < 3; i++) {
		if (coordinates[i].x > max_x)
			max_x = coordinates[i].x;
		if (coordinates[i].x > max_y)
			max_y = coordinates[i].x;
	}
	Point result = { max_x, max_y };
	return result;
}





float Point::LenOfPoints(Point point) {
	return(sqrt(pow(point.x - this->x, 2) + pow(point.y - this->y, 2)));
}


Point* Figure::GetPoints() {
	return coordinates;
}


bool Figure::operator== (const Figure& figure){
	for (int i = 0; i < 3; i++) {
		if ((this->coordinates[i].x != figure.coordinates[i].x) || (this->coordinates[i].y != figure.coordinates[i].y))
			return false;
	}
	return true;
}

Circle::Circle() {
	for (int i = 0; i < 4; ++i)
		coordinates[i].x = coordinates[i].y = 0;
}

Circle::Circle(Point* points) {
	for (int i = 0; i < 4; ++i) {
		coordinates[i] = points[i];
	}
}

float Circle::GetPerimeter() {
	return 2 * 3.14 * this->coordinates[0].LenOfPoints(this->coordinates[1]);
}

float Circle::GetSquare() {
	return 3.14 * pow(this->coordinates[0].LenOfPoints(this->coordinates[1]), 2);
}

void Circle::SetMinFramingRectangle(Point* points) {
	for (int i = 0; i < 4; ++i)
		points[i] = coordinates[i];
}

bool Circle::CheckFigure() {
	return ((coordinates[0].x == coordinates[2].x)
		&& (coordinates[1].y == coordinates[3].y)
		&& (coordinates[0].x < coordinates[1].x)
		&& (coordinates[0].x > coordinates[3].x)
		&& (coordinates[1].y < coordinates[0].y)
		&& (coordinates[1].y > coordinates[2].y))

}

void Circle::Print() {
	cout << "rectangle" << " ";
	for (int i = 0; i < 4; ++i)
		cout << coordinates[i].x << " " << coordinates[i].y << " ";
}


unique_ptr<Figure> Circle::Clone() const {
	Point points[4];
	for (int i = 0; i < 4; ++i) {
		points[i].x = coordinates[i].x;
		points[i].y = coordinates[i].y;
	}
	return  make_unique<Circle>(points);
}


Triangle::Triangle() {
	for (int i = 0; i < 3; ++i)
		coordinates[i].x = coordinates[i].y = 0;
}

Triangle::Triangle(Point* points) {
	for (int i = 0; i < 3; ++i) {
		coordinates[i] = points[i];
	}
}

float Triangle::GetPerimeter() {
	float perimeter = 0;
	for (int i = 0; i < 3; i++) {
		perimeter += this->coordinates[i].LenOfPoints(this->coordinates[(i + 1) % 3]);
	}
}

float Triangle::GetSquare() {
	float square = 1;
	for (int i = 0; i < 3; i++) {
		square *= halfperimeter - this->coordinates[i].LenOfPoints(this->coordinates[(i + 1) % 3]);
	}
	square = sqrt(square * halfperimeter);
	return square;
}

void Triangle::SetMinFramingRectangle(Point* points) {
	points[0] = MaxPoint(coordinates);
	points[2] = MinPoint(coordinates);

	points[1] = {points[0].x, points[2].y};
	points[3] = {points[2].x, points[0].y};

}

bool Triangle::CheckFigure() {
	if ((coordinates[0].x == coordinates[1].x) && (coordinates[0].y == coordinates[1].y))
		return false;
	if ((coordinates[1].x == coordinates[2].x) && (coordinates[1].y == coordinates[2].y))
		return false;
	if ((coordinates[0].x == coordinates[2].x) && (coordinates[0].y == coordinates[2].y))
		return false;
	return true;
}

void Triangle::Print() {
	cout << "triangle" << " ";
	for (int i = 0; i < 3; ++i)
		cout << coordinates[i].x << " " << coordinates[i].y << " ";
}


unique_ptr<Figure> Triangle::Clone() const {
	Point points[3];
	for (int i = 0; i < 3; ++i) {
		points[i].x = coordinates[i].x;
		points[i].y = coordinates[i].y;
	}
	return  make_unique<Triangle>(points);
}


Rectangle::Rectangle() {
	for (int i = 0; i < 4; ++i)
		coordinates[i].x = coordinates[i].y = 0;
}

Rectangle::Rectangle(Point* points) {
	for (int i = 0; i < 4; ++i) {
		coordinates[i] = points[i];
	}
}

float Rectangle::GetPerimeter() {
	float perimeter = 0;
	for (int i = 0; i < 4; i++) {
		perimeter += this->coordinates[i].LenOfPoints(this->coordinates[(i + 1) % 3]);
	}
}

float Rectangle::GetSquare() {
	float square = 1;
	for (int i = 0; i < 4; i++) {
		square *= halfperimeter - this->coordinates[i].LenOfPoints(this->coordinates[(i + 1) % 3]);
	}
	square = sqrt(square * halfperimeter);
	return square;
}

void Rectangle::SetMinFramingRectangle(Point* points) {
	points[0] = MaxPoint(coordinates);
	points[2] = MinPoint(coordinates);

	points[1] = { points[0].x, points[2].y };
	points[3] = { points[2].x, points[0].y };

}

bool Rectangle::CheckFigure() {
	for (int i = 1; i < 3; i++)
		if ((coordinates[0].x == coordinates[i].x) && (coordinates[0].y == coordinates[i].y))
			return false;
	if ((coordinates[1].x == coordinates[2].x) && (coordinates[1].y == coordinates[2].y))
		return false;
	if ((coordinates[1].x == coordinates[3].x) && (coordinates[1].y == coordinates[3].y))
		return false;

	if ((coordinates[2].x == coordinates[3].x) && (coordinates[2].y == coordinates[3].y))
		return false;

	return true;
}

void Rectangle::Print() {
	cout << "rectangle" << " ";
	for (int i = 0; i < 4; ++i)
		cout << coordinates[i].x << " " << coordinates[i].y << " ";
}


unique_ptr<Figure> Rectangle::Clone() const {
	Point points[4];
	for (int i = 0; i < 4; ++i) {
		points[i].x = coordinates[i].x;
		points[i].y = coordinates[i].y;
	}
	return  make_unique<Triangle>(points);
}




FigureArray& FigureArray::operator=(FigureArray rhs) {
	swap(rhs);
	return *this;
}

void FigureArray::Swap(FigureArray& arr) noexcept {
	std::swap(this->figure_array, arr.figure_array);
}
FigureArray::FigureArray(const FigureArray& arr) {
	for (int i = 0; i < size(); ++i) {
		figure_list.push_back(arr[i]->clone());
	}
}

void FigureArray::DeleteFigure(int index) {
	auto iter = figure_list.cbegin();
	figure_list.erase(iter + index);
}

int FigureArray::Size() {

	return figure_arr.size();
}

void FigureArray::Insert(FigurePtr figure, int index) {
	auto iter = figure_arr.cbegin();
	figure_arr.emplace(iter + index, figure);
}

FigurePtr FigureArray::operator[](const int index) const {
	if (index < 0) {
		throw out_of_range("[FigureArray::operator[]] Index is out of range.");
	}
	return figure_arr[index];
}

void FigureArray::Add(FigurePtr figure) {
	figure_arr.push_back(figure);
}
Figure& FigureArray::MinSquareSearch() {
	int j = 0;
	for (int i = 1; i < figure_arr.size(); ++i)
		if ((figure_arr[j]->GetSquare()) > (figure_arr[i]->GetSquare()))
			j = i;
	return *figure_arr[j];
}

void FigureArray::Print() {
	for (int i = 0; i < Size(); ++i) {
		cout << i << ". ";figure_arr[i]->Print();
		cout << endl;
	}
}