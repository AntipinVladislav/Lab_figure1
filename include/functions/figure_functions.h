#pragma once
#include <iostream>

namespace vlad {

	class Figure;
	using FigurePtr = std::shared_ptr<Figure>;

	struct Point {
		float x;
		float y;
		float LenOfPoints(Point point);
	};

	class Figure {
	protected:
		Figure() = default;
	public:
		Point coordinates[4];
		virtual float GetPerimeter() = 0;
		virtual float GetSquare() = 0;
		Point* GetPoints();
		void virtual SetMinFramingRectangle(Point* coordinates) = 0;
		bool operator==(const Figure& figure);
		bool virtual CheckFigure() = 0;
		void virtual Print() = 0;
		virtual unique_ptr<Figure> Clone() const = 0;
	};

	class Circle : public Figure {
	public:
		Circle();
		Circle(Point* points);

		float GetPerimeter() override;
		float GetSquare() override;
		void SetMinFramingRectangle(Point* coordinates) override;
		bool CheckFigure() override;
		void Print() override;
		unique_ptr<Figure> Clone() const override;
	};

	class Triangle : public Figure {
	public:
		Triangle();
		Triangle(Point* points);

		float GetPerimeter() override;
		float GetSquare() override;
		void SetMinFramingRectangle(Point* coordinates) override;
		bool CheckFigure() override;
		void Print() override;
		unique_ptr<Figure> Clone() const override;
		void Print();
	};

	class Rectangle : public Figure {
	public:
		Rectangle();
		Rectangle(Point* points);

		float GetPerimeter() override;
		float GetSquare() override;
		void SetMinFramingRectangle(Point* coordinates) override;
		bool CheckFigure() override;
		void Print() override;
		unique_ptr<Figure> Clone() const override;
		void Print();
	};


	class FigureArray {
	private:
		std::vector<FigurePtr> figure_array;


	public:
		void Swap(FigureArray& arr) noexcept;

		FigureArray() = default;
		FigureArray(const FigureArray& arr);
		FigurePtr operator[](const int index) const;
		FigureArray& operator=(FigureArray arr);

		int Size();


		void Add(FigurePtr figure);
		void Insert(FigurePtr a, int index);
		void DeleteFigure(int index);
		Figure& MinSquareSearch();
		void Print();
	};

}

