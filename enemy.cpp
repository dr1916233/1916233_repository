//----------------------------------
//	IsekaiKanchoProject
//	By �Q�������ٖ剺��
//----------------------------------

#include "DxLib.h"
#include "main.h"
#include "enemy.h"

// �ϐ��錾
CHARACTER enemyMaster[ENEMY_TYPE_MAX];	// �G�̕ϐ�
CHARACTER enemy[ENEMY_MAX];				// �G�̑���
int enemyImage[ENEMY_TYPE_MAX][16];		// �G�̉摜�̎��

// �G�̏�����
void EnemySystemInit(void)
{
	for (int cnt = 0; cnt < ENEMY_TYPE_MAX; cnt++)
	{
		enemyMaster[cnt].size = { 0,0 };		// �G�̏����T�C�Y
		enemyMaster[cnt].offsetSize = { 0,0 };	// �G�̏����I�t�Z�b�g�T�C�Y
		enemyMaster[cnt].animCnt = 0;			// �G�̏����A�j���[�V�����J�E���g
		enemyMaster[cnt].lifeMax = 0;			// �G�̏����ő僉�C�t
		enemyMaster[cnt].life = 0;				// �G�̏������C�t
		enemyMaster[cnt].dir = DIR_DOWN;		// �G�̏�������
		enemyMaster[cnt].visible = true;		
		enemyMaster[cnt].type = CHARA_ENEMY;
	}

	//------------------------------------------------------------------------------------------
// �X���C��

	enemyMaster[ENEMY_TYPE_SLIME].size = { 32,32 };		// �X���C���̃T�C�Y
	enemyMaster[ENEMY_TYPE_SLIME].offsetSize = { 3,7 }; // �X���C���̃I�t�Z�b�g�T�C�Y
	enemyMaster[ENEMY_TYPE_SLIME].lifeMax = 2;			// �X���C���̃��C�t
	enemyMaster[ENEMY_TYPE_SLIME].moveSpeed = 1;		// �X���C���̃X�s�[�h

	LoadDivGraph("image/character/�X���C��fin��.png",
		16, 4, 4, 32, 32, enemyImage[ENEMY_TYPE_SLIME]);	// �X���C���̕`��
	//------------------------------------------------------------------------------------------
	// �S�u����

	enemyMaster[ENEMY_TYPE_GOBLIN].size = { 32,32 };	// �S�u�����̃T�C�Y
	enemyMaster[ENEMY_TYPE_GOBLIN].offsetSize = { 3,7 };// �S�u�����̃I�t�Z�b�g�T�C�Y
	enemyMaster[ENEMY_TYPE_GOBLIN].lifeMax = 2;			// �S�u�����̃��C�t
	enemyMaster[ENEMY_TYPE_GOBLIN].moveSpeed = 1;		// �S�u�����̃X�s�[�h

	LoadDivGraph("image/character/�S�u����fin��.png",
		16, 4, 4, 32, 32, enemyImage[ENEMY_TYPE_GOBLIN]);	// �S�u�����̕`��
	//------------------------------------------------------------------------------------------

}

// �G�̃Q�[�����Ƃ̏�����
void EnemyGameInit(void)
{
	for (int en = 0; en < ENEMY_MAX; en++)
	{
		int rnd = GetRand(ENEMY_TYPE_MAX - 1);
		enemy[en] = enemyMaster[rnd];

		//enemy[en].pos.x += enemy[en].size.x * en;

		// �X�N���[���̃����_���Ȉʒu�ŏo��
		enemy[en].pos.x = GetRand(SCREEN_SIZE_X - 1);
		enemy[en].pos.y = GetRand(SCREEN_SIZE_Y - 1);
	}

}

// �G�̕`��
void EnemyGameDraw(XY mapPos)
{
	enemy[ENEMY_TYPE_MAX].animCnt++;

	int picMove = (enemy[ENEMY_TYPE_MAX].visible == false) ? enemy[ENEMY_TYPE_MAX].dir * 4 + enemy[ENEMY_TYPE_MAX].animCnt / 10 % 4 :
		enemy[ENEMY_TYPE_MAX].dir * 4;

	picMove = enemy[ENEMY_TYPE_MAX].dir * 4 + enemy[ENEMY_TYPE_MAX].animCnt / 10 % 4;

	for (int en = 0; en < ENEMY_MAX; en++)
	{
		DrawGraph(
				  enemy[en].pos.x -mapPos.x,
				  enemy[en].pos.y -mapPos.y,
				  enemyImage[enemy[en].dir][picMove],
		  		  true);
	};

	//DrawCircle(320, 240, 150, GetColor(255,255,255), false);

}

// �G�̐��䏈��
void EnemyControl(void)
{
	
}

XY GetEnemyPos(int en)
{

	return { (int)enemy[en].pos.x,(int)enemy[en].pos.y };
}

XY GetEnemySize(int en)
{

	return enemy[en].size;
}

void EnemyRad(void)
{
	//17+26= 43/2= 21.5= 21
}

	