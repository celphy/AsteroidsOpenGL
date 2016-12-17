#pragma once

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
