#pragma once
#include "Engine/GameObject.h"
enum class BulletType
{
	Player, // Player bullet
	Enemy   // Enemy bullet
};
//テストシーンを管理するクラス
class Bullet : public GameObject
{
	int hPlayerBullet_;
	int hEnemyBullet_;
	BulletType type_;    // Type of bullet
	float speed_;        // Speed of the bullet
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Bullet(GameObject* parent);
	~Bullet();
	//初期化
	void Initialize() override;

	void SetBulletType(BulletType type); // New: Set bullet type
	BulletType GetBulletType( ); // New: Get bullet type
	void SetSpeed(float speed);         // New: Set speed

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};