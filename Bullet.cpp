#include "Bullet.h"
#include <assert.h>
#include "Engine/time.h"

// Constructor
Bullet::Bullet(GameObject* parent)
    : GameObject(parent, "Bullet"), hPlayerBullet_(-1), hEnemyBullet_(-1), type_(BulletType::Player), speed_(0.0f)
{
}

// Destructor
Bullet::~Bullet()
{
    Release();
}

// Initialize: Load the bullet graphics
void Bullet::Initialize()
{
    hPlayerBullet_ = LoadGraph("Assets/PlayerProjectile.png");
    assert(hPlayerBullet_ != -1 && "Failed to load player bullet image.");

    hEnemyBullet_ = LoadGraph("Assets/EnemyProjectile.png");
    assert(hEnemyBullet_ != -1 && "Failed to load enemy bullet image.");

    // Set the initial position based on parent's position (if available)
    if (GetParent())
    {
        transform_.position_ = GetParent()->GetPosition();

        // Adjust position for player or enemy bullet
        if (type_ == BulletType::Player)
        {
            transform_.position_.x += (170.0f / 2.0f) - (20.0f / 2.0f); // Center bullet relative to player
            transform_.position_.y -= 24.0f; // Offset upward for player bullet
        }
        else if (type_ == BulletType::Enemy)
        {
            transform_.position_.x += (182.0f / 2.0f) - (19.0f / 2.0f); // Center bullet relative to enemy
            transform_.position_.y += 232.0f; // Offset downward for enemy bullet
        }
    }
}

// Set bullet type and speed
void Bullet::SetBulletType(BulletType type)
{
    type_ = type;
    speed_ = (type == BulletType::Player) ? 400.0f : 300.0f; // Set speed based on type
}

BulletType Bullet::GetBulletType()
{
    return type_;
}

// Update: Move bullet and destroy if off-screen
void Bullet::Update()
{
    int screenWidth, screenHeight;
    GetScreenState(&screenWidth, &screenHeight, nullptr);

    if (type_ == BulletType::Player)
    {
        transform_.position_.y -= speed_ * Time::DeltaTime(); // Move upward
        if (transform_.position_.y < 0) KillMe();            // Destroy if off-screen
    }
    else if (type_ == BulletType::Enemy)
    {
        transform_.position_.y += speed_ * Time::DeltaTime(); // Move downward
        if (transform_.position_.y > screenHeight) KillMe();  // Destroy if off-screen
    }
}

// Draw: Render bullet
void Bullet::Draw()
{
    int sprite = (type_ == BulletType::Player) ? hPlayerBullet_ : hEnemyBullet_;
    DrawGraph(static_cast<int>(transform_.position_.x), static_cast<int>(transform_.position_.y), sprite, TRUE);
}

// Release: Clean up resources
void Bullet::Release()
{
    if (hPlayerBullet_ != -1)
    {
        DeleteGraph(hPlayerBullet_);
        hPlayerBullet_ = -1;
    }
    if (hEnemyBullet_ != -1)
    {
        DeleteGraph(hEnemyBullet_);
        hEnemyBullet_ = -1;
    }
}
