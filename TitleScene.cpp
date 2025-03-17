#include "TitleScene.h"
#include"Engine/SceneManager.h"
#include<assert.h>
//�R���X�g���N�^
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"),hTitle_(-1)
{
	
}

//������
void TitleScene::Initialize()
{
	hTitle_=LoadGraph("Assets/Title.png");
	assert(hTitle_ > 0);
}

//�X�V
void TitleScene::Update()
{
	if (CheckHitKey(KEY_INPUT_RETURN) == 1)
	{
		SceneManager* sc = GetRootJob()->FindGameObject<SceneManager>();
		sc->ChangeScene(SCENE_ID::SCENE_ID_PLAY);
	}
}

//�`��
void TitleScene::Draw()
{
	DrawGraph(0, 0, hTitle_, TRUE);
}

//�J��
void TitleScene::Release()
{
}
