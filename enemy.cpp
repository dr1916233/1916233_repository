//----------------------------------
//	IsekaiKanchoProject
//	By �Q�������ٖ剺��
//----------------------------------

#include "DxLib.h"
#include "main.h"
#include "enemy.h"

// �ϐ��錾
CHARACTER enemyMaster[ENEMY_TYPE_MAX];	// �G�̕ϐ�
CHARACTER enemy[ENEMY_MAX];
int enemyImage[ENEMY_TYPE_MAX][16];		// �G�̉摜�̎��

// �G�̏�����
void EnemySystemInit(void)
{
	//------------------------------------------------------------------------------------------
// �X���C��

	enemyMaster[ENEMY_TYPE_SLIME].lifeMax = 4;
	enemyMaster[ENEMY_TYPE_SLIME].moveSpeed = 1;
	enemyMaster[ENEMY_TYPE_SLIME].size.x = 32;
	enemyMaster[ENEMY_TYPE_SLIME].size.y = 32;
	enemyMaster[ENEMY_TYPE_SLIME].offsetSize.x = 3;
	enemyMaster[ENEMY_TYPE_SLIME].offsetSize.y = 7;

	LoadDivGraph("image/character/�X���C��fin��.png",
		16, 4, 4, 32, 32, enemyImage[ENEMY_TYPE_SLIME]);
	//------------------------------------------------------------------------------------------

	for (int cnt = 0; cnt < ENEMY_TYPE_MAX; cnt++)
	{
		enemyMaster[cnt].animCnt = 0;
		enemyMaster[cnt].lifeMax = 0;
		enemyMaster[cnt].life = 0;
		enemyMaster[cnt].dir = DIR_DOWN;
		enemyMaster[cnt].visible = true;
		enemyMaster[cnt].type = CHARA_ENEMY;
	}
}

// �G�̃Q�[�����Ƃ̏�����
void EnemyGameInit(void)
{
	for (int en = 0; en < ENEMY_MAX; en++)
	{
		int rnd = GetRand(ENEMY_TYPE_MAX - 1);
		enemy[en] = enemyMaster[rnd];

		//enemy[en].pos.x += enemy[en].size.x * en;

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
	}

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
	