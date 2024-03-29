#include "quaternions.h"

Quaternion operator+(Quaternion q1, Quaternion q2){
	Quaternion q;
	q.a = q1.a + q2.a;
	q.b = q1.b + q2.b;
	q.c = q1.c + q2.c;
	q.d = q1.d + q2.d;
	return q;
}

Quaternion operator*(float alpha, Quaternion q1){
	Quaternion q;
	q.a = alpha*q1.a;
	q.b = alpha*q1.b;
	q.c = alpha*q1.c;
	q.d = alpha*q1.d;
	return q;
}

Quaternion operator*(Quaternion q1, Quaternion q2)
{
    Quaternion q;

    q.a = q1.a*q2.a - q1.b*q2.b - q1.c*q2.c - q1.d*q2.d;
    q.b = q1.a*q2.b + q1.b*q2.a + q1.c*q2.d - q1.d*q2.c;
    q.c = q1.a*q2.c - q1.b*q2.d + q1.c*q2.a + q1.d*q2.b;
    q.d = q1.a*q2.d + q1.b*q2.c - q1.c*q2.b + q1.d*q2.a;

    return q;
}
