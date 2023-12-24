#include "App.hpp"
#include <iostream>

int main()
{
	try
	{
		App app{1200, 800, "Server"};
		app.onInit();
		app.onRender();
	}
	catch (std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
	}

	return 0;
}