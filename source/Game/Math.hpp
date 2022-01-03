#pragma once

#include <cmath>

#include <SFML/System/Vector2.hpp>

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

template<typename T>
T Root(const T a, const T n)
{
	if (n == T(2.0))
	{
		return std::sqrt(a);
	}
	else
	{
		return std::pow(a, 1.0f / n);
	}
}