//----------------------------------
//	IsekaiKanchoProject
//	By �Q�������ٖ剺��
//----------------------------------

#define ENEMY_MAX 5	// �G�̑���

// �萔
enum ENEMY_TYPE
{
	// �G�̎��
	ENEMY_TYPE_SURAIMU,	
	ENEMY_TYPE_GOBURIN,
	ENEMY_TYPE_MAX
};

//#pragma once//----------------------------------

// �v���g�^�C�v�錾
void EnemySystemInit(void);		// �G�̃V�X�e��������
void EnemyGameInit(void);		// �G�̃Q�[��������
void EnemyGameDraw(void);		// �G�̃Q�[���`��
void EnemyControl(void);		// �G�̐��䏈��