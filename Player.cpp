#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include"EnemyManager.h"
#include <assert.h>
#include"Engine/time.h"
#include <algorithm> // For std::max and std::min
#include <iostream>

Player::Player(GameObject* parent)
    : GameObject(parent, "Player"), hPlayer_(-1), speed_(350.0f), score_(0), enemiesDefeated_(0)
{
}

Player::~Player()
{
    Release();
}

void Player::Initialize()
{
    hPlayer_ = LoadGraph("Assets/Player.png");
    assert(hPlayer_ != -1 && "Failed to load player image.");
    // Get the screen dimensions

    GetScreenState(&screenWidth, &screenHeight, nullptr);

    // Set the player's initial position to the bottom center
    transform_.position_.x = (screenWidth / 2.0f) - 32; // Center X, assuming sprite width is 64
    transform_.position_.y = screenHeight - 100.0f;     // Near bottom, adjust as needed
    isBulletActive_ = false; // No bullet is active initially
}

void Player::Update()
{
    float deltaTime = Time::DeltaTime(); // Frame-rate independent movement

    // Player Movement
    if (CheckHitKey(KEY_INPUT_W)) transform_.position_.y -= speed_ * deltaTime; // Move up
    if (CheckHitKey(KEY_INPUT_S)) transform_.position_.y += speed_ * deltaTime; // Move down
    if (CheckHitKey(KEY_INPUT_A)) transform_.position_.x -= speed_ * deltaTime; // Move left
    if (CheckHitKey(KEY_INPUT_D)) transform_.position_.x += speed_ * deltaTime; // Move right

    // Clamp X position
    if (transform_.position_.x < 0.0f) transform_.position_.x = 0.0f;
    if (transform_.position_.x > screenWidth - 170) transform_.position_.x = screenWidth - 170;

    // Clamp Y position
    if (transform_.position_.y < 0.0f) transform_.position_.y = 0.0f;
    if (transform_.position_.y > screenHeight - 102) transform_.position_.y = screenHeight - 102;

    // Shooting Logic
    if (CheckHitKey(KEY_INPUT_SPACE))
    {
        if (!isBulletActive_)
        {
            Bullet* bullet = Instantiate<Bullet>(this);
            bullet->SetBulletType(BulletType::Player);  // Player bullet
            bullet->Initialize();
            isBulletActive_ = true;                     // Bullet is now active
        }
    }
    else
    {
        isBulletActive_ = false; // Reset bullet flag
    }

    // Player Bullet vs. Enemy Collision
    EnemyManager* enemyManager = GetParent()->FindGameObject<EnemyManager>();
    if (enemyManager)
    {
        auto childList = enemyManager->GetChildList();
        for (GameObject* obj : *childList)
        {
            if (obj->GetObjectName() == "Enemy")
            {
                Enemy* enemy = dynamic_cast<Enemy*>(obj);
                if (enemy)
                {
                    Bullet* playerBullet = FindGameObject<Bullet>();
                    if (playerBullet && playerBullet->GetBulletType() == BulletType::Player)
                    {
                        // Use CollideCircle for Player Bullet vs. Enemy collision
                        if (enemy->CollideCircle(playerBullet->GetPosition().x, playerBullet->GetPosition().y, 12.0f)) // Bullet radius ~12
                        {
                            playerBullet->KillMe(); // Destroy bullet
                            enemy->KillMe();        // Destroy enemy
                            AddScore(50);           // Add points
                            IncrementEnemiesDefeated(); // Increment count
                            break;                 // Exit loop after collision
                        }
                    }
                }
            }
        }
    }

}

void Player::Draw()
{
    DrawGraph(static_cast<int>(transform_.position_.x), static_cast<int>(transform_.position_.y), hPlayer_, TRUE);
   

    DrawFormatString(10, 10, GetColor(255, 0, 0), "Score: %d", score_);
    DrawFormatString(10, 30, GetColor(255, 0, 0), "Enemies Defeated: %d", enemiesDefeated_);
}

void Player::Release()
{
    if (hPlayer_ != -1)
    {
        DeleteGraph(hPlayer_);
        hPlayer_ = -1;
    }
}

void Player::AddScore(int points)
{
    score_ += points; // Add points to the score
}

int Player::GetScore() const
{
    return score_;
}

void Player::IncrementEnemiesDefeated()
{
    enemiesDefeated_++; // Increment the enemy count
}

int Player::GetEnemiesDefeated() const
{
    return enemiesDefeated_;
}
bool Player::CollideCircle(float x, float y, float r)
{
    // Calculate this object's center and radius
    float myCenterX = transform_.position_.x + 32.0f; // Adjust as needed
    float myCenterY = transform_.position_.y + 32.0f; // Adjust as needed
    float myR = 85.0f; // Default radius; can be overridden by subclasses or based on dimensions

    // Calculate the squared distance between the centers
    float dx = myCenterX - x;
    float dy = myCenterY - y;
    float distanceSquared = dx * dx + dy * dy;

    // Compare squared distances for collision (avoids expensive sqrt call)
    float radiiSum = myR + r;
    return distanceSquared <= (radiiSum * radiiSum);
}