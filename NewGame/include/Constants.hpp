#pragma once
#include <string>

namespace Constants {
    const unsigned int WINDOW_WIDTH = 800;
    const unsigned int WINDOW_HEIGHT = 600;
    const float BIKE_SPEED = 200.0f;
    const float SCROLL_SPEED = 200.0f;
    const float GAME_DURATION = 60.0f; // 60 secondes
    const std::string ASSETS_PATH = "assets/textures/";
    const float BIKE_MARGIN = 15.f;
    // Add these new constants for Bike physics
    const std::string BIKE_TEXTURE = ASSETS_PATH + "spr_bike2man_0.png";
    const float GRAVITY = 800.0f;
    const float GROUND_Y = 500.f; // Adjust this based on where you want the bike to stand
    const float JUMP_FORCE = -500.0f;
    const float DOUBLE_JUMP_FORCE = -800.0f;
    // For Timer speed multiplier
    const float MAX_SPEED_MULTIPLIER = 5.0f;
    const float TOTAL_DURATION = GAME_DURATION; // Assuming this is what you want for mTotalDuration
    const int OBSTACLE_WIDTH = 30;
    const int OBSTACLE_HEIGHT = 60;
    const int OBSTACLE_SPEED = 200;
}