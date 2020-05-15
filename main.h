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

enum CHARATYPE
{
	CHARA_PLAYER,
	CHARA_ENEMY,
	CHARA_MAGIC,
	CHARATYPE_MAX
};

// --------------------
// �\����
// --------------------

// 2�����x�N�g���p
struct XY
{
	int x;
	int y;
};

// 2����float�p
struct XY_F
{
	float x;
	float y;
};

struct CHARACTER
{
	XY_F pos;
	DIR dir;
	CHARATYPE type;
	XY size;
	int lifeMax;
	int life;
	int animCnt;
	float moveSpeed;
	bool visible;
	int level;
	int attack;
};

// �v���g�^�C�v�錾
bool SystemInit(void);	// �V�X�e��������
void InitScene(void);	// �������V�[��
void TitleScene(void);	// �^�C�g���V�[��
void TitleDraw(void);	// �^�C�g���`��
void GameScene(void);	// �Q�[���V�[��
void GameDraw(XY mapPos);	// �Q�[���`��
void GameOverScene(void);	// �Q�[���I�[�o�[�V�[��
void GameOverDraw(void);	// �Q�[���I�[�o�[�`��