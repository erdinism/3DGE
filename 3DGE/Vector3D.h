#pragma once

class Vector3D
{
public:
	float coord_x, coord_y, coord_z;

	Vector3D():coord_x(0), coord_y(0), coord_z(0){}

	Vector3D(float x, float y, float z):coord_x(x), coord_y(y), coord_z(z){}

	Vector3D(const Vector3D & refference) :coord_x(refference.coord_x), coord_y(refference.coord_y), coord_z(refference.coord_z){}

	// We have to apply lerp on CPU side
	static Vector3D lerp(const Vector3D & start, const Vector3D & end, float delta)
	{
		Vector3D result;

		result.coord_x = start.coord_x * (1.0f - delta) + end.coord_x * (delta);
		result.coord_y = start.coord_y * (1.0f - delta) + end.coord_y * (delta);
		result.coord_z = start.coord_z * (1.0f - delta) + end.coord_z * (delta);

		return result;
	}

	Vector3D operator* (float num)
	{
		return Vector3D(coord_x * num, coord_y * num, coord_z * num);
	}

	Vector3D operator+ (Vector3D other)
	{
		return Vector3D(coord_x + other.coord_x, coord_y + other.coord_y, coord_z + other.coord_z);
	}
};