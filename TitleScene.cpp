#include "TitleScene.h"
#include"Engine/SceneManager.h"
#include<assert.h>
//コンストラクタ
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"),hTitle_(-1)
{
	
}

//初期化
void TitleScene::Initialize()
{
	hTitle_=LoadGraph("Assets/Title.png");
	assert(hTitle_ > 0);
}

//更新
void TitleScene::Update()
{
	if (CheckHitKey(KEY_INPUT_RETURN) == 1)
	{
		SceneManager* sc = GetRootJob()->FindGameObject<SceneManager>();
		sc->ChangeScene(SCENE_ID::SCENE_ID_PLAY);
	}
}

//描画
void TitleScene::Draw()
{
	DrawGraph(0, 0, hTitle_, TRUE);
}

//開放
void TitleScene::Release()
{
}
