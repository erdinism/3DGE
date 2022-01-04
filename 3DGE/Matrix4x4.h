#pragma once

#include <memory>
#include "Vector3D.h"
#include "Vector4D.h"

class Matrix4x4
{
public:
	// Row major matrix
	float MATRIX[4][4] = {};

	void setId() 
	{
		::memset(MATRIX, 0, sizeof(float) * 16);
		MATRIX[0][0] = 1;
		MATRIX[1][1] = 1;
		MATRIX[2][2] = 1;
		MATRIX[3][3] = 1;
	}

	void translate(const Vector3D& translation)
	{
		MATRIX[3][0] = translation.coord_x;
		MATRIX[3][1] = translation.coord_y;
		MATRIX[3][2] = translation.coord_z;
	}

	void scale(const Vector3D& scale)
	{
		MATRIX[0][0] = scale.coord_x;
		MATRIX[1][1] = scale.coord_y;
		MATRIX[2][2] = scale.coord_z;
	}

	void setXRotation(float x)
	{
		MATRIX[1][1] = cos(x);
		MATRIX[1][2] = sin(x);
		MATRIX[2][1] = -sin(x);
		MATRIX[2][2] = cos(x);
	}

	void setYRotation(float y)
	{
		MATRIX[0][0] = cos(y);
		MATRIX[0][2] = -sin(y);
		MATRIX[2][0] = sin(y);
		MATRIX[2][2] = cos(y);
	}

	void setZRotation(float z)
	{
		MATRIX[0][0] = cos(z);
		MATRIX[0][1] = sin(z);
		MATRIX[1][0] = -sin(z);
		MATRIX[1][1] = cos(z);
	}

	float getDeterminant()
	{
		Vector4D minor, v1, v2, v3;
		float det;

		v1 = Vector4D(this->MATRIX[0][0], this->MATRIX[1][0], this->MATRIX[2][0], this->MATRIX[3][0]);
		v2 = Vector4D(this->MATRIX[0][1], this->MATRIX[1][1], this->MATRIX[2][1], this->MATRIX[3][1]);
		v3 = Vector4D(this->MATRIX[0][2], this->MATRIX[1][2], this->MATRIX[2][2], this->MATRIX[3][2]);

		minor.cross(v1, v2, v3);

		det = -(this->MATRIX[0][3] * minor.coord_x + this->MATRIX[1][3] * minor.coord_y + this->MATRIX[2][3] * minor.coord_z + this->MATRIX[3][3] * minor.coord_w);

		return det;
	}

	void inverse()
	{
		int a, i, j;
		Matrix4x4 out;
		Vector4D v, vec[3];
		float det = 0.0f;

		det = this->getDeterminant();
		if (!det) return;

		for (i = 0; i < 4; i++) 
		{
			for (j = 0; j < 4; j++)
			{
				if (j != i)
				{
					a = j;
					if (j > i) a = a - 1;
					vec[a].coord_x = (this->MATRIX[j][0]);
					vec[a].coord_y = (this->MATRIX[j][1]);
					vec[a].coord_z = (this->MATRIX[j][2]);
					vec[a].coord_w = (this->MATRIX[j][3]);
				}
			}

			v.cross(vec[0], vec[1], vec[2]);

			out.MATRIX[0][i] = pow(-1.0f, i) * v.coord_x / det;
			out.MATRIX[1][i] = pow(-1.0f, i) * v.coord_y / det;
			out.MATRIX[2][i] = pow(-1.0f, i) * v.coord_z / det;
			out.MATRIX[3][i] = pow(-1.0f, i) * v.coord_w / det;
		}

		this->setMatrix(out);
	}

	void operator *=(const Matrix4x4 & matrix)
	{
		Matrix4x4 result;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				result.MATRIX[i][j] = MATRIX[i][0] * matrix.MATRIX[0][j] + MATRIX[i][1] * matrix.MATRIX[1][j] + MATRIX[i][2] * matrix.MATRIX[2][j] + MATRIX[i][3] * matrix.MATRIX[3][j];
			}
		}

		setMatrix(result);
	}

	void setMatrix(const Matrix4x4& target) 
	{
		::memcpy(MATRIX, target.MATRIX, sizeof(float) * 16);
	}

	Vector3D getZdirection()
	{
		return Vector3D(MATRIX[2][0], MATRIX[2][1], MATRIX[2][2]);
	}

	Vector3D getXdirection()
	{
		return Vector3D(MATRIX[0][0], MATRIX[0][1], MATRIX[0][2]);
	}

	Vector3D getTranslation()
	{
		return Vector3D(MATRIX[3][0], MATRIX[3][1], MATRIX[3][2]);
	}

	void perspectiveProjection(float FOV, float aspect_ratio, float z_near, float z_far)
	{
		float yscale = 1.0f / tan(FOV / 2.0f);
		float xscale = yscale / aspect_ratio;

		MATRIX[0][0] = xscale;
		MATRIX[1][1] = yscale;
		MATRIX[2][2] = z_far / (z_far - z_near);
		MATRIX[2][3] = 1.0f;
		MATRIX[3][2] = (-z_near * z_far) / (z_far - z_near);

	}

	void orthogonalProjection(float width, float height, float near_plane, float far_plane)
	{
		setId();
		MATRIX[0][0] = 2.0f / width;
		MATRIX[1][1] = 2.0f / height;
		MATRIX[2][2] = 1.0f / (far_plane - near_plane);
		MATRIX[3][2] = -(near_plane / (far_plane - near_plane));
	}
};