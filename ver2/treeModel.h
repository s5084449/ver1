#pragma once

class Trunk 
{
	double length = 10.0;
	double length_shrink = 0.75;
	double radius = 0.75;
	double radius_shrink = 0.65;
	double leap_x = 35.00;
	double leap_y = 30.00;
	double leap_z = 30.00;
	Trunk() {}

	void update_length(double len, double len_shrink) {
		length = len;
		length_shrink = length_shrink;
		//update length
	}

	void update_raidus(double r, double r_shrink) {
		radius = r;
		radius_shrink = r_shrink;
		// update radius
	}

	void update_leap(double x, double y, double z) {
		leap_x = x;
		leap_y = y;
		leap_z = z;
		//update facing position
	}
	~Trunk() {}
};