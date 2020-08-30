//----------------------------------
//	IsekaiKanchoProject
//	By �Q�������ٖ剺��
//----------------------------------

//#pragma once//----------------------------------

#define ENEMY_MAX 4	// �G�̑���

// �萔
enum ENEMY_TYPE
{
	// �G�̎��
	ENEMY_TYPE_SLIME,	//�X���C��
	ENEMY_TYPE_GOBLIN,	//�S�u����
	ENEMY_TYPE_OAK,		//�I�[�N
	ENEMY_TYPE_BOSS,
	ENEMY_TYPE_MAX,
};

// �v���g�^�C�v�錾
void EnemySystemInit(void);		// �G�̃V�X�e��������
void EnemyGameInit(void);		// �G�̃Q�[��������
void EnemyGameDraw(XY mapPos);	// �G�̃Q�[���`��
void EnemyControl(XY playerPos, int cnt);		// �G�̐��䏈��
void EnemyRad(void);

bool EnemyPlayerDiff(int index, int diff);
int PlayerEnemyHitCheck(int playerSize);	// �v���C���[�ƓG�̓����蔻��



// �G���ړ�������֐��Q
//int MoveEnemyY(CHARACTER* enemy, XY playerPos);
//int MoveEnemyX(CHARACTER* enemy, XY playerPos);

XY GetEnemyPos(int en);
XY GetEnemySize(int en);

void DoDamageEnemy(int index, int damage);	// �n���ꂽ�C���f�b�N�X�̓G��HP���_���[�W�����Z����
