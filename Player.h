#pragma once
#include "Engine/GameObject.h"

//�e�X�g�V�[�����Ǘ�����N���X
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
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Player(GameObject* parent);
	~Player();
	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
	void AddScore(int points);        // Add points to the player's score
	int GetScore() const;             // Get the current score
	void IncrementEnemiesDefeated();   // Increment defeated enemy count
	int GetEnemiesDefeated() const;    // Get the number of enemies defeated
	bool CollideCircle(float x, float y, float r) ;
};