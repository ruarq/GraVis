#pragma once

#include <cmath>

template<typename T>
float Length(const T &a)
{
	return std::sqrt(a.x * a.x + a.y * a.y);
}

template<typename T>
float Distance(const T &a, const T &b)
{
	return Length(a - b);
}

template<typename T>
T Normalized(const T &a)
{
	return a / Length(a);
}