//----------------------------------
//	IsekaiKanchoProject
//	By �Q�������ٖ剺��
//----------------------------------

#define ENEMY_MAX 4	// �G�̑���


// �萔
enum ENEMY_TYPE
{
	// �G�̎��
	ENEMY_TYPE_SLIME,	//�X���C��
	ENEMY_TYPE_GOBLIN,	//�S�u����
	ENEMY_TYPE_MAX
};

//#pragma once//----------------------------------

// �v���g�^�C�v�錾
void EnemySystemInit(void);		// �G�̃V�X�e��������
void EnemyGameInit(void);		// �G�̃Q�[��������
void EnemyGameDraw(XY mapPos);	// �G�̃Q�[���`��
void EnemyControl(void);		// �G�̐��䏈��
void EnemyRad(void);

XY GetEnemyPos(int en);
XY GetEnemySize(int en);