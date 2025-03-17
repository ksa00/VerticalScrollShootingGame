#include "OverScene.h"
#include"Engine/SceneManager.h"
#include<assert.h>
//コンストラクタ
OverScene::OverScene(GameObject* parent)
	: GameObject(parent, "OverScene"),hOver_(-1)
{
}

//初期化
void OverScene::Initialize()
{
	hOver_ = LoadGraph("Assets/Over.png");
	assert(hOver_ > 0);
}

//更新
void OverScene::Update()
{
	if (CheckHitKey(KEY_INPUT_RETURN) == 1)
	{
		SceneManager* sc = GetRootJob()->FindGameObject<SceneManager>();
		sc->ChangeScene(SCENE_ID::SCENE_ID_PLAY);
	}
	if (CheckHitKey(KEY_INPUT_ESCAPE) == 1){
		exit(0);
	}
}

//描画
void OverScene::Draw()
{
	DrawGraph(0, 0, hOver_, TRUE);
}

//開放
void OverScene::Release()
{
}
