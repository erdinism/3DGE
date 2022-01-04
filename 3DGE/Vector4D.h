#pragma once

class Vector4D
{
public:
	float coord_x, coord_y, coord_z, coord_w;

	Vector4D() :coord_x(0), coord_y(0), coord_z(0), coord_w(0) {}

	Vector4D(float x, float y, float z, float w) :coord_x(x), coord_y(y), coord_z(z), coord_w(w) {}

	Vector4D(const Vector4D& refference) :coord_x(refference.coord_x), coord_y(refference.coord_y), coord_z(refference.coord_z), coord_w(refference.coord_w) {}

	void cross(Vector4D& v1, Vector4D& v2, Vector4D& v3)
	{
		this->coord_x = v1.coord_y * (v2.coord_z * v3.coord_w - v3.coord_z * v2.coord_w) - v1.coord_z * (v2.coord_y * v3.coord_w - v3.coord_y * v2.coord_w) + v1.coord_w * (v2.coord_y * v3.coord_z - v3.coord_y * v2.coord_z);
		this->coord_y = -(v1.coord_x * (v2.coord_z * v3.coord_w - v3.coord_z * v2.coord_w) - v1.coord_z * (v2.coord_x * v3.coord_w - v3.coord_x * v2.coord_w) + v1.coord_w * (v2.coord_x * v3.coord_z - v3.coord_x * v2.coord_z));
		this->coord_z = v1.coord_x * (v2.coord_y * v3.coord_w - v3.coord_y * v2.coord_w) - v1.coord_y * (v2.coord_x * v3.coord_w - v3.coord_x * v2.coord_w) + v1.coord_w * (v2.coord_x * v3.coord_y - v3.coord_x * v2.coord_y);
		this->coord_w = -(v1.coord_x * (v2.coord_y * v3.coord_z - v3.coord_y * v2.coord_z) - v1.coord_y * (v2.coord_x * v3.coord_z - v3.coord_x * v2.coord_z) + v1.coord_z * (v2.coord_x * v3.coord_y - v3.coord_x * v2.coord_y));
	}
};