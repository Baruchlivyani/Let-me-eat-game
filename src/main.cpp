#include "GameController.h"
#include <iostream>

int main() try
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	std::shared_ptr<LevelBase> level = nullptr;
	GameController().startGame(level);

    return EXIT_SUCCESS;
}

catch (std::exception& ex)
{
    std::cerr << "Exception: " << ex.what() << '\n';
    return EXIT_FAILURE;
}

catch (...)
{
    std::cerr << "Unknown exception\n";
    return EXIT_FAILURE;
}