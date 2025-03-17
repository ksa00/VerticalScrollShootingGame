#include "PlayScene.h"
#include"EnemyManager.h"
#include"Player.h"
#include"Stage.h"
#include"Bullet.h"

//コンストラクタ
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
}

//初期化
void PlayScene::Initialize()
{Instantiate<Stage>(this);
	Instantiate<Player>(this);
	Instantiate<EnemyManager>(this);
	


}

//更新
void PlayScene::Update()
{
}

//描画
void PlayScene::Draw(){
 
}

//開放
void PlayScene::Release()
{

}