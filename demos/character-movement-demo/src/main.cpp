#include "CharacterMovementDemo.hpp"

int main(int argc, char* argv[])
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    CharacterMovementDemo characterMovementDemo;
    characterMovementDemo.run();
}
