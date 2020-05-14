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
	SCENE_MAX
};

// �����p
enum DIR
{
	DIR_DOWN,		// ��
	DIR_RIGHT,		// �E
	DIR_LEFT,		// ��
	DIR_UP,			// ��
	DIR_MAX
};

// --------------------
// �\����
// --------------------

// 2�����x�N�g���p
struct Pos
{
	int x;
	int y;
};

// 2����float�p
struct Pos_F
{
	float x;
	float y;
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