#include "Image.h"


void Image::OnUpdate()
{
	if (GetPosition().x >= -640) {
		GoToPosition(-7200, 360, mSpeed);
	}
	else {
		SetPosition(1280, 0, 0, 0);
		std::cout << "parallax";
	}



}

