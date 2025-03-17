#pragma once
#include "Engine/GameObject.h"

//テストシーンを管理するクラス
class Stage : public GameObject
{
	int hBackGround_;
	int backgroundY_;    // Y-coordinate for the scrolling background
	float scrollSpeed_;  // Scrolling speed of the background
	float elapsedTime_;      // Elapsed time since the stage started
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Stage(GameObject* parent);
	~Stage();
	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};