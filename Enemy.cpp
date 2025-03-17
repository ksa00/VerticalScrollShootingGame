#include "Enemy.h"
#include "Player.h"
#include <assert.h>
#include "Engine/time.h"
#include "Bullet.h"
#include "Engine/SceneManager.h"

Enemy::Enemy(GameObject* parent)
    : GameObject(parent, "Enemy"), hEnemy_(-1), speed_(100.0f), shootTimer_(0.0f)
{
}

Enemy::~Enemy()
{
    Release();
}

void Enemy::Initialize()
{
    hEnemy_ = LoadGraph("Assets/Enemy.png");
    assert(hEnemy_ != -1 && "Failed to load enemy image.");

    // Random starting position_ (X-axis)
    int screenWidth, screenHeight;
    GetScreenState(&screenWidth, &screenHeight, nullptr);

    transform_.position_.x = static_cast<float>(rand() % (screenWidth - 182)); // Random X, account for width
    transform_.position_.y = -232.0f; // Start slightly above the screen
}

void Enemy::Update()
{
    float deltaTime = Time::DeltaTime();
    shootTimer_ += deltaTime;

    // Move the enemy downward
    transform_.position_.y += speed_ * deltaTime;

    // Enemy shoots every 1.5 seconds
    if (shootTimer_ >= 1.25f)
    {
        ShootBullet();
        shootTimer_ = 0.0f; // Reset the shoot timer
    }

    // Destroy enemy if it moves off the bottom of the screen
    int screenHeight;
    GetScreenState(nullptr, &screenHeight, nullptr);
    if (transform_.position_.y > screenHeight)
    {
        for (auto* bullet : bullets_)
        {
			if (bullet)
			{
				bullet->KillMe(); // Destroy bullet
			}
		}
        KillMe(); // Mark for deletion
        return;
    }

    // Enemy Bullet vs. Player Collision

        GameObject* playerObj = GetParent()->FindObject("Player");
        if (playerObj)
        {
            Player* player = dynamic_cast<Player*>(playerObj);
            if (player)
            {
                for (auto* bullet : bullets_)
                {
                    if (bullet && player->CollideCircle(bullet->GetPosition().x, bullet->GetPosition().y, 9.5f)) // Bullet radius ~9.5
                    {
                        bullet->KillMe(); // Destroy bullet
                        player->KillMe(); // Destroy player
						if (player->IsDead())
						{
							// Game Over
							SceneManager* sc = GetRootJob()->FindGameObject<SceneManager>();
							if (sc)
							{
								sc->ChangeScene(SCENE_ID::SCENE_ID_OVER);
							}
						}
						
                    }
                }
            }
        }


    }
void Enemy::Draw()
{
    DrawGraph(static_cast<int>(transform_.position_.x), static_cast<int>(transform_.position_.y), hEnemy_, TRUE);
}

void Enemy::Release()
{
    if (hEnemy_ != -1)
    {
        DeleteGraph(hEnemy_);
        hEnemy_ = -1;
    }

    bullets_.clear();
}

void Enemy::ShootBullet()
{
    Bullet* bullet = Instantiate<Bullet>(this);
    bullet->SetBulletType(BulletType::Enemy);
    bullet->Initialize();
    bullets_.push_back(bullet); // Add to the list of active bullets
}
bool Enemy::CollideCircle(float x, float y, float r)
{
    // Enemy-specific circle properties
    float myCenterX = transform_.position_.x + (182.0f / 2.0f); // Center of enemy sprite (width: 182)
    float myCenterY = transform_.position_.y + (232.0f / 2.0f); // Center of enemy sprite (height: 232)
    float myR = 91.0f; // Enemy's radius based on sprite width

    // Compute the squared distance
    float dx = myCenterX - x;
    float dy = myCenterY - y;
    float distanceSquared = dx * dx + dy * dy;

    // Check collision
    float radiiSum = myR + r;
    return distanceSquared <= (radiiSum * radiiSum);
}
