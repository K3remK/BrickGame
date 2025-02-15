#pragma once

#include "raylib.h"
#include "Vec2.h"
#include <cmath>

#define DARKRED        CLITERAL(Color){ 139, 0, 0, 255 }     // DARKRed
#define DARKYELLOW        CLITERAL(Color){ 139, 128, 0, 255 }     // DARKYELLOW
#define DARKSKYBLUE        CLITERAL(Color){ 0, 139, 139, 255 }     // DARKYELLOW
#define LIGHTBLUE        CLITERAL(Color){ 173, 216, 230, 255 }     // LIGHTBLUE
#define LIGHTGREEN        CLITERAL(Color){ 144, 238, 144, 255 }     // LIGHTGREEN
#define LIGHTRED        CLITERAL(Color){ 255, 204, 203, 255 }     // LIGHTRED
#define LIGHTYELLOW        CLITERAL(Color){ 255, 255, 143, 255 }     // LIGHTYELLOW
#define LIGHTMAGENTA        CLITERAL(Color){ 218, 108, 175, 255 }     // LIGHTMAGENTA
#define LIGHTSKYBLUE        CLITERAL(Color){ 135, 206, 250, 255 }     // LIGHTSKYBLUE


const static int screenWidth = 960;
const static int screenHeight = 800;
const static int FPS = 60;
const static int brickSize = 40;
const static Vec2 playerSize = Vec2(150.0f, 30.0f);
const static int row = 5;
const static int column = 20;
const static int playerLife = 5;
const static int topMargin = 50;
const static float ballSpeed = 5.0f;
const static float ballRadius = 10.0f;
const static Color baseColors[] = {BLUE, GREEN, RED, YELLOW, MAGENTA, SKYBLUE};
const static Color lightColors[] = {LIGHTBLUE, LIGHTGREEN, LIGHTRED, LIGHTYELLOW, LIGHTMAGENTA, LIGHTSKYBLUE};
const static Color darkColors[] = {DARKBLUE, DARKGREEN, DARKRED, DARKYELLOW, DARKPURPLE, DARKSKYBLUE};
const int nBrickColors = 6;
const static Color playerColor = BLACK;
const static Color ballColor = RED;
const static Color backGroundColor = WHITE;