#include "OverScene.h"
#include"Engine/SceneManager.h"
#include<assert.h>
//�R���X�g���N�^
OverScene::OverScene(GameObject* parent)
	: GameObject(parent, "OverScene"),hOver_(-1)
{
}

//������
void OverScene::Initialize()
{
	hOver_ = LoadGraph("Assets/Over.png");
	assert(hOver_ > 0);
}

//�X�V
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

//�`��
void OverScene::Draw()
{
	DrawGraph(0, 0, hOver_, TRUE);
}

//�J��
void OverScene::Release()
{
}
