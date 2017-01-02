#pragma once

/// <summary>
/// Point struct of floats. +/- operator inline.
/// </summary>
typedef struct Point {
	float x;
	float y;
	inline Point operator+(Point a) {
		return{ a.x + x, a.y + y };
	}
	inline Point operator-(Point a) {
		return{ a.x + x, a.y + y };
	}
}Point;
