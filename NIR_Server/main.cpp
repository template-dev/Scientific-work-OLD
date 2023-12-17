#include "App.hpp"

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
		ex.what();
	}

	return 0;
}