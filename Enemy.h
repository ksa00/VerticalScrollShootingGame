#pragma once
#include "Engine/GameObject.h"
#include"Bullet.h"
#include <vector>
#include <memory>


class Enemy : public GameObject
{
private:
    int hEnemy_;   // Handle for enemy sprite
    float speed_;  // Speed of the enemy
    float shootTimer_;  // Timer to control shooting intervals
    std::vector<Bullet*> bullets_;

public:
    Enemy(GameObject* parent);

    ~Enemy();

    void Initialize() override;

    void Update() override;

    void Draw() override;

    void Release() override;
    void ShootBullet(); // Function to shoot bullets
    bool CollideCircle(float x, float y, float r);
  //  Bullet* GetBullet() const { return enemyBullet_; }
   // void SetBullet(Bullet* bullet) { enemyBullet_ = bullet; } // Optional for external assignment

};
