#pragma once

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

const float PADDLE_WIDTH = 120.f;
const float PADDLE_HEIGHT = 20.f;
const float PADDLE_SPEED = 400.f;

const float BALL_RADIUS = 10.f;
const float BALL_SPEED = 300.f;

const float BLOCK_WIDTH = 75.f;
const float BLOCK_HEIGHT = 25.f;
const float BLOCK_PADDING = 5.f;

enum class BlockType { Normal, Indestructible, WithBonus, SpeedUp, Durability };
