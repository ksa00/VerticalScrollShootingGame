#include "Stage.h"
#include"Engine/SceneManager.h"
#include"Engine/time.h"
#include <assert.h>

Stage::Stage(GameObject* parent)
    : GameObject(parent, "Stage"), hBackGround_(-1), backgroundY_(0), scrollSpeed_(100.0f)
{
}

Stage::~Stage()
{
    if (hBackGround_ != -1)
    {
        DeleteGraph(hBackGround_);
        hBackGround_ = -1;
    }
}

void Stage::Initialize()
{
    hBackGround_ = LoadGraph("Assets/BackGround.png");
    assert(hBackGround_ != -1 && "Failed to load image.");
}

void Stage::Update()
{
    // Scroll the background downward
    backgroundY_ += scrollSpeed_ * Time::DeltaTime();

    int bgHeight;
    GetGraphSize(hBackGround_, nullptr, &bgHeight);

    // Reset background position when it moves completely downward
    if (backgroundY_ >= bgHeight)
    {
        backgroundY_ -= bgHeight;
    }
}

void Stage::Draw()
{
    int bgHeight;
    GetGraphSize(hBackGround_, nullptr, &bgHeight);

    // Draw the main background
    DrawGraph(0, static_cast<int>(backgroundY_), hBackGround_, FALSE);

    // Draw a second copy for seamless looping
    DrawGraph(0, static_cast<int>(backgroundY_) - bgHeight, hBackGround_, FALSE);
}

void Stage::Release()
{
    if (hBackGround_ != -1)
    {
        DeleteGraph(hBackGround_);
        hBackGround_ = -1;
    }
}
