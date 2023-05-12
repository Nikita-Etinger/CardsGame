#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <thread>//потоки
#include <chrono>//время
#include <SFML/Audio.hpp>
#include <Windows.h>


#define random(a,b) a+rand()%(b+1-a)
using namespace std;
using namespace sf;