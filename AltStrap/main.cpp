#include "yanapp3D.h"
#include <crtdbg.h>

int main()
{

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

auto App = new application3D();

App->run("YanApp", 1280, 720);

delete App;


return 0;
}