#include "yanapp3D.h"


int main()
{
auto App = new application3D();

App->run("YanApp", 1280, 720);

delete App;


return 0;
}