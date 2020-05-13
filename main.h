//----------------------------------
//	IsekaiKanchoProject
//	By �Q�������ٖ剺��
//----------------------------------

//#pragma once//----------------------------------

// �萔�錾
#define SCREEN_SIZE_X	800		// �Q�[���X�N���[����X�T�C�Y
#define SCREEN_SIZE_Y	600		// �Q�[���X�N���[����Y�T�C�Y

// �V�[���J�ڗp
enum SCENE_ID {
	SCENE_INIT,		// �������p
	SCENE_TITLE,	// �^�C�g��
	SCENE_GAME,		// �Q�[�����C��
	SCENE_GAMEOVER,	// �Q�[���I�[�o�[
	SCENE_MAX,
};

// �v���g�^�C�v�錾
bool SystemInit(void);	// �V�X�e��������
void InitScene(void);	// �������V�[��
void TitleScene(void);	// �^�C�g���V�[��
void TitleDraw(void);	// �^�C�g���`��
void GameScene(void);	// �Q�[���V�[��
void GameDraw(void);	// �Q�[���`��
void GameOverScene(void);	// �Q�[���I�[�o�[�V�[��
void GameOverDraw(void);	// �Q�[���I�[�o�[�`��