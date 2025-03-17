#pragma once
#include "Engine/GameObject.h"

//�e�X�g�V�[�����Ǘ�����N���X
class Stage : public GameObject
{
	int hBackGround_;
	int backgroundY_;    // Y-coordinate for the scrolling background
	float scrollSpeed_;  // Scrolling speed of the background
	float elapsedTime_;      // Elapsed time since the stage started
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Stage(GameObject* parent);
	~Stage();
	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};