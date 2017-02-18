#include "fontBuilder.h"



gameObject * fontBuilder::makeToText(int number, Point p, float size)
{
	gameObject* obj = new gameObject(p);
	obj->setPosition(p);
	switch (number) {
	case 0: {
		GLfloat points[10];
		points[0] = this->segments[0].x * size;
		points[1] = this->segments[0].y * size;
		points[2] = this->segments[1].x * size;
		points[3] = this->segments[1].y * size;
		points[4] = this->segments[5].x * size;
		points[5] = this->segments[5].y * size;
		points[6] = this->segments[4].x * size;
		points[7] = this->segments[4].y * size;
		points[8] = this->segments[0].x * size;
		points[9] = this->segments[0].y * size;
		obj->setOutline(5, points);
		break;
	}

	case 1: {
		GLfloat points[4];
		points[0] = this->segments[1].x * size;
		points[1] = this->segments[1].y * size;
		points[2] = this->segments[5].x * size;
		points[3] = this->segments[5].y * size;
		obj->setOutline(2, points);
		break;
	}

	case 2: {
		GLfloat points[12];
		points[0] = this->segments[0].x * size;
		points[1] = this->segments[0].y * size;
		points[2] = this->segments[1].x * size;
		points[3] = this->segments[1].y * size;
		points[4] = this->segments[3].x * size;
		points[5] = this->segments[3].y * size;
		points[6] = this->segments[2].x * size;
		points[7] = this->segments[2].y * size;
		points[8] = this->segments[4].x * size;
		points[9] = this->segments[4].y * size;
		points[10] = this->segments[5].x * size;
		points[11] = this->segments[5].y * size;
		obj->setOutline(6, points);
		break;
	}

	case 3: {
		GLfloat points[14];
		points[0] = this->segments[0].x * size;
		points[1] = this->segments[0].y * size;
		points[2] = this->segments[1].x * size;
		points[3] = this->segments[1].y * size;
		points[4] = this->segments[3].x * size;
		points[5] = this->segments[3].y * size;
		points[6] = this->segments[2].x * size;
		points[7] = this->segments[2].y * size;
		points[8] = this->segments[3].x * size;
		points[9] = this->segments[3].y * size;
		points[10] = this->segments[5].x * size;
		points[11] = this->segments[5].y * size;
		points[12] = this->segments[4].x * size;
		points[13] = this->segments[4].y * size;
		obj->setOutline(7, points);
		break;
	}
	case 4: {
		GLfloat points[10];
		points[0] = this->segments[0].x * size;
		points[1] = this->segments[0].y * size;
		points[2] = this->segments[2].x * size;
		points[3] = this->segments[2].y * size;
		points[4] = this->segments[3].x * size;
		points[5] = this->segments[3].y * size;
		points[6] = this->segments[1].x * size;
		points[7] = this->segments[1].y * size;
		points[8] = this->segments[5].x * size;
		points[9] = this->segments[5].y * size;
		obj->setOutline(5, points);
		break;
	}
	case 5: {
		GLfloat points[12];
		points[0] = this->segments[1].x * size;
		points[1] = this->segments[1].y * size;
		points[2] = this->segments[0].x * size;
		points[3] = this->segments[0].y * size;
		points[4] = this->segments[2].x * size;
		points[5] = this->segments[2].y * size;
		points[6] = this->segments[3].x * size;
		points[7] = this->segments[3].y * size;
		points[8] = this->segments[5].x * size;
		points[9] = this->segments[5].y * size;
		points[10] = this->segments[4].x * size;
		points[11] = this->segments[4].y * size;
		obj->setOutline(6, points);
		break;
	}
	case 6: {
		GLfloat points[12];
		points[0] = this->segments[1].x * size;
		points[1] = this->segments[1].y * size;
		points[2] = this->segments[0].x * size;
		points[3] = this->segments[0].y * size;
		points[4] = this->segments[4].x * size;
		points[5] = this->segments[4].y * size;
		points[6] = this->segments[5].x * size;
		points[7] = this->segments[5].y * size;
		points[8] = this->segments[3].x * size;
		points[9] = this->segments[3].y * size;
		points[10] = this->segments[2].x * size;
		points[11] = this->segments[2].y * size;
		obj->setOutline(6, points);
		break;
	}
	case 7: {
		GLfloat points[6];
		points[0] = this->segments[0].x * size;
		points[1] = this->segments[0].y * size;
		points[2] = this->segments[1].x * size;
		points[3] = this->segments[1].y * size;
		points[4] = this->segments[5].x * size;
		points[5] = this->segments[5].y * size;
		obj->setOutline(3, points);
		break;
	}

	case 8: {
		GLfloat points[14];
		points[0] = this->segments[2].x * size;
		points[1] = this->segments[2].y * size;
		points[2] = this->segments[4].x * size;
		points[3] = this->segments[4].y * size;
		points[4] = this->segments[5].x * size;
		points[5] = this->segments[5].y * size;
		points[6] = this->segments[1].x * size;
		points[7] = this->segments[1].y * size;
		points[8] = this->segments[0].x * size;
		points[9] = this->segments[0].y * size;
		points[10] = this->segments[2].x * size;
		points[11] = this->segments[2].y * size;
		points[12] = this->segments[3].x * size;
		points[13] = this->segments[3].y * size;
		obj->setOutline(7, points);
		break;
	}

	case 9: {
		GLfloat points[10];
		points[0] = this->segments[3].x * size;
		points[1] = this->segments[3].y * size;
		points[2] = this->segments[2].x * size,
			points[3] = this->segments[2].y * size;
		points[4] = this->segments[0].x * size;
		points[5] = this->segments[0].y * size;
		points[6] = this->segments[1].x * size;
		points[7] = this->segments[1].y * size;
		points[8] = this->segments[5].x * size;
		points[9] = this->segments[5].y * size;
		obj->setOutline(5, points);
		break;
	}
	default:
		GLfloat points[8];
		points[0] = 0.15 * size;
		points[1] = -0.01 * size;
		points[2] = 0.3 * size;
		points[3] = -0.3 * size;
		points[4] = 0.01 * size;
		points[5] = -0.3 * size;
		points[6] = 0.15 * size;
		points[7] = -0.01 * size;
		obj->setOutline(4, points);
		break;
	}
	return obj;
}

