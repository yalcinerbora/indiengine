#include "IEMath.h"
#include "IEFunctions.h"
#include "IEQuaternion.h"
#include "IEVector3.h"
#include "IEMath.h"
#include "IEVector4.h"

const IEQuaternion IEQuaternion::IdentityQuat = IEQuaternion(1.0f, 0.0f, 0.0f, 0.0f);

IEQuaternion::IEQuaternion() : w(1.0f),
								x(0.0f),
								y(0.0f),
								z(0.0f)
{}

IEQuaternion::IEQuaternion(float w, float x, float y, float z) : w(w), 
																	x(x), 
																	y(y), 
																	z(z)
{}

IEQuaternion::IEQuaternion(const float* data) : w(data[0]),
												x(data[1]),
												y(data[2]),
												z(data[3])
{}

IEQuaternion::IEQuaternion(float angle, const IEVector3& axis)
{
	angle *= 0.5f;
	float sinAngle = IEMath::Sin(angle);

	IEVector3 normAxis = axis.Normalize();

	x = normAxis.getX() * sinAngle;
	y = normAxis.getY() * sinAngle;
	z = normAxis.getZ() * sinAngle;
	w = IEMath::Cos(angle);
}

IEQuaternion IEQuaternion::operator*(const IEQuaternion& quat) const
{
	return IEQuaternion(w * quat.w - x * quat.x - y * quat.y - z * quat.z,		// W
						w * quat.x + x * quat.w + y * quat.z - z * quat.y,		// X
						w * quat.y + y * quat.w + z * quat.x - x * quat.z,		// Y
						w * quat.z + z * quat.w + x * quat.y - y * quat.x		// Z
						);

}

IEQuaternion IEQuaternion::operator*(float t) const
{
	return IEQuaternion(w * t,
						x * t,
						y * t,
						z * t
						);
}

IEQuaternion IEQuaternion::operator+(const IEQuaternion& quat) const
{
	return IEQuaternion(w + quat.w,
						x + quat.x,
						y + quat.y,
						z + quat.z
						);
}

IEQuaternion IEQuaternion::operator-(const IEQuaternion& quat) const
{
	return IEQuaternion(w - quat.w,
						x - quat.x,
						y - quat.y,
						z - quat.z
						);
}

IEQuaternion IEQuaternion::operator-() const
{
	return IEQuaternion(-w,
						-x,
						-y,
						-z
						);
}

IEQuaternion IEQuaternion::operator/(float t) const
{
	assert(t != 0.0f);
	float tInv = 1.0f / t;

	return IEQuaternion(w * tInv,
						x * tInv,
						y * tInv,
						z * tInv
						);
}

void IEQuaternion::operator*=(const IEQuaternion& quat)
{
	IEQuaternion copy(*this);
	w =	copy.w * quat.w - copy.x * quat.x - copy.y * quat.y - copy.z * quat.z;		// W
	x =	copy.w * quat.x + copy.x * quat.w + copy.y * quat.z - copy.z * quat.y;		// X
	y = copy.w * quat.y + copy.y * quat.w + copy.z * quat.x - copy.x * quat.z;		// Y
	z =	copy.w * quat.z + copy.z * quat.w + copy.x * quat.y - copy.y * quat.x;		// Z
}

void IEQuaternion::operator*=(float t)
{
	w *= t;
	x *= t;
	y *= t;
	z *= t;
}

void IEQuaternion::operator+=(const IEQuaternion& quat)
{
	w += quat.w;
	x += quat.x;
	y += quat.y;
	z += quat.z;
}

void IEQuaternion::operator-=(const IEQuaternion& quat)
{
	w -= quat.w;
	x -= quat.x;
	y -= quat.y;
	z -= quat.z;
}

void IEQuaternion::operator/=(float t)
{
	assert(t != 0.0f);
	float tInv = 1.0f / t;

	w *= tInv;
	x *= tInv;
	y *= tInv;
	z *= tInv;
}

bool IEQuaternion::operator==(const IEQuaternion& quat)
{
	return std::equal(v, v + 4, quat.v);
}

bool IEQuaternion::operator!=(const IEQuaternion& quat)
{
	return !std::equal(v, v + 4, quat.v);
}

IEQuaternion IEQuaternion::Normalize() const
{
	float length = Length();
	if(length != 0.0f)
		length = 1.0f / length;

	return IEQuaternion(w * length,
						x * length,
						y * length,
						z * length);
}

IEQuaternion& IEQuaternion::NormalizeSelf()
{
	float length = Length();
	if(length != 0.0f)
		length = 1.0f / length;

	w *= length;
	x *= length;
	y *= length;
	z *= length;
	return *this;
}

float IEQuaternion::Length() const
{
	return sqrtf(w * w + x * x + y * y + z * z);
}

float IEQuaternion::LengthSqr() const
{
	return w * w + x * x + y * y + z * z;
}

IEQuaternion IEQuaternion::Conjugate() const
{
	return IEQuaternion(w, -x, -y, -z);
}

IEQuaternion& IEQuaternion::ConjugateSelf()
{
	x = -x;
	y = -y;
	z = -z;
	return *this;
}

float IEQuaternion::DotProduct(const IEQuaternion& quat) const
{
	return w * quat.w + x * quat.x + y * quat.y + z * quat.z;
}

IEVector3 IEQuaternion::ApplyRotation(const IEVector3& vector)
{
	// q * v * qInv
	IEQuaternion qInv = this->Normalize().ConjugateSelf();
	IEQuaternion vectorQ(0.0f, vector.getX(), vector.getY(), vector.getZ());
	IEQuaternion result	((*this) * (vectorQ * qInv));

	return IEVector3(result.x, result.y, result.z);
}

IEQuaternion IEQuaternion::NLerp(const IEQuaternion& start, const IEQuaternion& end, float percent)
{
	if(percent >= 1.0f)
		return end;
	if(percent <= 0.0f)
		return start;
	return (start + percent * (end - start)).Normalize();
}

IEQuaternion IEQuaternion::SLerp(const IEQuaternion& start, const IEQuaternion& end, float percent)
{
	IEQuaternion result;
	float startWeight, endWeight, difference;

	if(percent >= 1.0f)
		return end;
	if(percent <= 0.0f)
		return start;

    difference = start.DotProduct(end);
	if (difference > IEMath::Abs(1.0f - SLERP_TO_LERP_SWITCH_THRESHOLD))
	{
		// SLerp
		// Theta is angle between quats
		float theta, sinTehtaInv;
		theta = IEMath::Acos(IEMath::Abs(difference));
		sinTehtaInv = 1.0f / IEMath::Sin(theta);

		startWeight = (IEMath::Sin(theta * (1.0f - percent)) * sinTehtaInv);
		endWeight = (sin(theta * percent) * sinTehtaInv);

		result.x = (start.x * startWeight) + (end.x * endWeight);
		result.y = (start.y * startWeight) + (end.y * endWeight);
		result.z = (start.z * startWeight) + (end.z * endWeight);
		result.w = (start.w * startWeight) + (end.w * endWeight);
		return result.Normalize();
	}
	else
	{
		// Not Worth
		// Do NLerp instead
		return NLerp(start, end, percent);
	}
}

// Left Scalar operators
IEQuaternion operator*(float scalar, const IEQuaternion& quat)
{
	return quat * scalar;
}