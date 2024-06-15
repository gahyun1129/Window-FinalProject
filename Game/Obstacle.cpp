#include "stdafx.h"

void Obstacle::MoveElevator()
{
	if (isUp && size.top >= minLv ) {
		size.top -= 5;
		size.bottom -= 5;
	}
	if (isDown && size.top <= maxLv) {
		size.top += 5;
		size.bottom += 5;
	}
}
