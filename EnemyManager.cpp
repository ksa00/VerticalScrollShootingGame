#include "EnemyManager.h"
#include "Enemy.h"
#include "Engine/time.h"
#include <cstdlib> // For rand()

EnemyManager::EnemyManager(GameObject* parent)
    : GameObject(parent, "EnemyManager"), spawnTimer_(0.0f), maxEnemies_(1)
{
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::Initialize()
{
   // Instantiate<Enemy>(this);
    spawnTimer_ = 0.0f;
    maxEnemies_ = 1; // Start with 1 enemy
   // SpawnEnemy();
}

void EnemyManager::Update()
{
    static float elapsedTime = 0.0f; // Track total elapsed time
    float deltaTime = Time::DeltaTime();
    spawnTimer_ += deltaTime;
    elapsedTime += deltaTime; // Increment elapsed time
    // Increase spawn rate over time
    if (static_cast<int>(elapsedTime) % 30 == 0) // Every 30 seconds
    {
        maxEnemies_ = 1 + (elapsedTime / 30); // Increase max enemies
    }

    // Spawn new enemies
    if (spawnTimer_ >= 2.0f) // Spawn an enemy every 2 seconds
    {
        // Dereference the child list to check current enemies
        auto childList = GetChildList(); // Assuming GetChildList() returns a pointer
        int currentEnemies = 0;

        for (auto it = childList->begin(); it != childList->end(); ++it)
        {
            if ((*it)->GetObjectName() == "Enemy" && !(*it)->IsDead())
            {
                currentEnemies++;
            }
        }

        if (currentEnemies < maxEnemies_) // Only spawn if below max limit
        {
            SpawnEnemy();
        }

        spawnTimer_ = 0.0f; // Reset timer
    }
}

void EnemyManager::SpawnEnemy()
{
    // Create and initialize a new enemy
    Enemy* enemy = new Enemy(this);
	Instantiate<Enemy>(this);
	
}
