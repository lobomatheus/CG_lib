#ifndef QUATERNIONS
#define QUATERNIONS

struct Quaternion{
	float a, b, c, d;
};

Quaternion operator+(Quaternion q1, Quaternion q2);

Quaternion operator*(float alpha, Quaternion q1);

Quaternion operator*(Quaternion q1, Quaternion q2);

#endif // QUATERNIONS
