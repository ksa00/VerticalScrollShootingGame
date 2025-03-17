#pragma once
#include "Engine/GameObject.h"
enum class BulletType
{
	Player, // Player bullet
	Enemy   // Enemy bullet
};
//�e�X�g�V�[�����Ǘ�����N���X
class Bullet : public GameObject
{
	int hPlayerBullet_;
	int hEnemyBullet_;
	BulletType type_;    // Type of bullet
	float speed_;        // Speed of the bullet
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Bullet(GameObject* parent);
	~Bullet();
	//������
	void Initialize() override;

	void SetBulletType(BulletType type); // New: Set bullet type
	BulletType GetBulletType( ); // New: Get bullet type
	void SetSpeed(float speed);         // New: Set speed

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};