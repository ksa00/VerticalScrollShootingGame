#include "PlayScene.h"
#include"EnemyManager.h"
#include"Player.h"
#include"Stage.h"
#include"Bullet.h"

//�R���X�g���N�^
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
}

//������
void PlayScene::Initialize()
{Instantiate<Stage>(this);
	Instantiate<Player>(this);
	Instantiate<EnemyManager>(this);
	


}

//�X�V
void PlayScene::Update()
{
}

//�`��
void PlayScene::Draw(){
 
}

//�J��
void PlayScene::Release()
{

}