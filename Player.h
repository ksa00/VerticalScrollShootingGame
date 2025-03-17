#pragma once
#include "Engine/GameObject.h"

//テストシーンを管理するクラス
class Player : public GameObject
{
	int hPlayer_;
	float speed_;      // Movement speed of the player
	int screenWidth, screenHeight;
	bool isBulletActive_;  // Tracks if a bullet is currently active
	int score_; // Player's score
	int enemiesDefeated_; // New: Count of defeated enemies
	//std::list<Bullet*> playerBullets;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Player(GameObject* parent);
	~Player();
	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
	void AddScore(int points);        // Add points to the player's score
	int GetScore() const;             // Get the current score
	void IncrementEnemiesDefeated();   // Increment defeated enemy count
	int GetEnemiesDefeated() const;    // Get the number of enemies defeated
	bool CollideCircle(float x, float y, float r) ;
};