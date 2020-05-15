//----------------------------------
//	IsekaiKanchoProject
//	By ゲヱム道館門下生
//----------------------------------

#include "DxLib.h"
#include "main.h"
#include "enemy.h"

// 変数宣言
CHARACTER enemyMaster[ENEMY_TYPE_MAX];	// 敵の変数
CHARACTER enemy[ENEMY_MAX];
int enemyImage[ENEMY_TYPE_MAX][16];		// 敵の画像の種類

// 敵の初期化
void EnemySystemInit(void)
{
	//------------------------------------------------------------------------------------------
// スライム

	//enemyMaster[ENEMY_TYPE_SURAIMU].type = CHARA_ENEMY;
	//enemyMaster[ENEMY_TYPE_SURAIMU].lifeMax = 4;
	//enemyMaster[ENEMY_TYPE_SURAIMU].moveSpeed = 1;
	//enemyMaster[ENEMY_TYPE_SURAIMU].size.x = 32;
	//enemyMaster[ENEMY_TYPE_SURAIMU].size.y = 32;
	LoadDivGraph("image/character/スライムfin完.png",
		16, 4, 4, 32, 32, enemyImage[ENEMY_TYPE_SURAIMU]);
	//------------------------------------------------------------------------------------------

	for (int cnt = 0; cnt < ENEMY_TYPE_MAX; cnt++)
	{
		enemyMaster[cnt].animCnt = 0;
		enemyMaster[cnt].lifeMax = 0;
		enemyMaster[cnt].life = 0;
		enemyMaster[cnt].dir = DIR_DOWN;
		enemyMaster[cnt].visible = true;
	}
}

// 敵のゲームごとの初期化
void EnemyGameInit(void)
{
	for (int en = 0; en < ENEMY_MAX; en++)
	{
		int rnd = GetRand(ENEMY_TYPE_MAX - 1);
		enemy[en] = enemyMaster[rnd];

		enemy[en].pos.x += enemy[en].size.x * en;
		//enemy[cnt].pos.x = GetRand(SCREEN_SIZE_X - 1);
		//enemy[cnt].pos.y = GetRand(SCREEN_SIZE_Y - 1);
	}

}

// 敵の描画
void EnemyGameDraw(void)
{
	enemy[ENEMY_TYPE_MAX].animCnt++;

	int picMove = (enemy[ENEMY_TYPE_MAX].visible == false) ? enemy[ENEMY_TYPE_MAX].dir * 4 + enemy[ENEMY_TYPE_MAX].animCnt / 10 % 4 :
		enemy[ENEMY_TYPE_MAX].dir * 4;

	picMove = enemy[ENEMY_TYPE_MAX].dir * 4 + enemy[ENEMY_TYPE_MAX].animCnt / 10 % 4;

	for (int en = 0; en < ENEMY_MAX; en++)
	{
		DrawGraph(enemy[en].pos.x,
				  enemy[en].pos.y,
				  enemyImage[enemy[en].dir][picMove],
		  		  true);
	}

	//DrawCircle(320, 240, 150, GetColor(255,255,255), false);

}

// 敵の制御処理
void EnemyControl(void)
{
	
}
	