#pragma once
#include "Engine/GameObject.h"

class EnemyManager : public GameObject
{
private:
    float spawnTimer_;   // Timer to control spawn intervals
    int maxEnemies_;     // Maximum number of enemies to spawn at a time

public:
    EnemyManager(GameObject* parent);

    ~EnemyManager();

    void Initialize() override;

    void Update() override;

    void SpawnEnemy(); // Function to spawn a single enemy
};
