//----------------------------------
//	IsekaiKanchoProject
//	By ƒQƒ‘ƒ€“¹ŠÙ–å‰º¶
//----------------------------------

#include "DxLib.h"
#include "main.h"
#include "enemy.h"

// •Ï”éŒ¾
CHARACTER enemyMaster[ENEMY_TYPE_MAX];		// “G‚Ì•Ï”
CHARACTER enemy[ENEMY_MAX];
int enemyImage[ENEMY_TYPE_MAX][16];

// “G‚Ì‰Šú‰»
void EnemySystemInit(void)
{

}

// “G‚ÌƒQ[ƒ€‚²‚Æ‚Ì‰Šú‰»
void EnemyGameInit(void)
{
	//------------------------------------------------------------------------------------------
// ƒXƒ‰ƒCƒ€

	enemyMaster[ENEMY_TYPE_SURAIMU].type = CHARA_ENEMY;
	enemyMaster[ENEMY_TYPE_SURAIMU].lifeMax = 4;
	enemyMaster[ENEMY_TYPE_SURAIMU].moveSpeed = 1;
	enemyMaster[ENEMY_TYPE_SURAIMU].size.x = 32;
	enemyMaster[ENEMY_TYPE_SURAIMU].size.y = 32;
	LoadDivGraph("image/character/ƒXƒ‰ƒCƒ€finŠ®.png",
		16, 4, 4, 32, 32, enemyImage[ENEMY_TYPE_SURAIMU]);
	

	//------------------------------------------------------------------------------------------

	for (int cnt = 0; cnt < ENEMY_TYPE_MAX; cnt++)
	{
		enemyMaster[cnt].animCnt = 0;
		enemyMaster[cnt].lifeMax = 0;
		enemyMaster[cnt].life = 0;
		enemyMaster[cnt].pos = { 0,0 };
		enemyMaster[cnt].size.x = 0;
		enemyMaster[cnt].size.y = 0;
		enemyMaster[cnt].type = CHARA_ENEMY;
		enemyMaster[cnt].dir = DIR_DOWN;
		enemyMaster[cnt].visible = true;
	}

}

// “G‚Ì•`‰æ
void EnemyGameDraw(void)
{
	enemy[ENEMY_MAX].animCnt++;
	DrawGraph(enemy[ENEMY_MAX].pos.x, enemy[ENEMY_MAX].pos.y, enemyImage[enemy[ENEMY_MAX].dir][enemy[ENEMY_MAX].animCnt / 10 % 4], true);

	//DrawCircle(320, 240, 150, GetColor(255,255,255), false);

}

// “G‚Ì§Œäˆ—
void EnemyControl(void)
{
	
}