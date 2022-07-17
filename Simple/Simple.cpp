// Simple.cpp : Defines the entry point for the application.
//


#include "Simple.h"

using namespace std::literals::chrono_literals;









int main()
{

	Engine engine;

	while (true) {
		
		if ((GetAsyncKeyState(VK_LEFT) & 0x01) && engine.direction != VK_RIGHT)
		{
			engine.direction = VK_LEFT;
		}
		if ((GetAsyncKeyState(VK_RIGHT) & 0x01) && engine.direction != VK_LEFT)
		{
			engine.direction = VK_RIGHT;
		}
		if ((GetAsyncKeyState(VK_DOWN) & 0x01) && engine.direction != VK_UP)
		{
			engine.direction = VK_DOWN;
		}
		if ((GetAsyncKeyState(VK_UP) & 0x01) && engine.direction != VK_DOWN)
		{
			engine.direction = VK_UP;
		}

		system("cls");
		if (engine.update() == -1)
		{
			cout << "GAME OVER!";
			break;
		}
		
		engine.print();
		std::this_thread::sleep_for(0.5s);


	}
	
	
	return 0;

}
