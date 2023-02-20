#pragma once

namespace function {
	enum FigureType {
		Circle,
		Triangle,
		Rectangle
	};

	class Figure {
	private:
		FigureType current_type;
		float coordinates[5];
		
		
	public:
		void set_coordinates(Figure current_figure, float* coordinates);

		float get_perimeter(Figure current_figure);

		float get_area(Figure current_figure);

		float find_minimal_outer_rectangle(Figure current_figure);

		float get_type(Figure current_figure);

		void get_coordinates(Figure current_figure, float* coordinates);
	};
	
}
