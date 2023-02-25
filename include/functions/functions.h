#pragma once

namespace vlad {
	enum FigureType {
		circle,
		triangle,
		rectangle
	};

	struct Point {
		float x;
		float y;
		float LenOfPoints(Point point)
	};

	class Figure {
	private:
		FigureType type;
		Point coordinates[4];
	public:
		Figure();
		Figure(FigureType type, Point* coordinates);

		bool operator== (const Figure figure) const;

		void SetType(FigureType Type);
		FigureType GetType();

		void SetCoordinates(Point* points);
		Point GetCoordinate(int index);
		
		float GetPerimeter();
		float GetSquare();
		void SetMinFramingRectangle(Figure figure);
	};
	
}
