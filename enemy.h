//----------------------------------
//	IsekaiKanchoProject
//	By �Q�������ٖ剺��
//----------------------------------
#define ENEMY_IMAGENUM_X 4	// �G�l�~�[�摜��X�����̐�
#define ENEMY_IMAGENUM_Y 4	// �G�l�~�[�摜��Y�����̐�
#define ENEMY_IMAGESIZE_X	32	// �G�l�~�[�摜��X�����̃T�C�Y
#define ENEMY_IMAGESIZE_Y	32	// �G�l�~�[�摜��Y�����̃T�C�Y

// �萔
enum ENEMY_TYPE
{
	// �G�̎��
	ENEMY_TYPE_SURAIMU,	
	ENEMY_TYPE_MAX
};

//#pragma once//----------------------------------

// �v���g�^�C�v�錾
void EnemySystemInit(void);		// �G�̃V�X�e��������
void EnemyGameInit(void);		// �G�̃Q�[��������
void EnemyGameDraw(void);		// �G�̃Q�[���`��
void EnemyControl(void);		// �G�̐��䏈��