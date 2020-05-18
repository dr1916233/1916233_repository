//----------------------------------
//	IsekaiKanchoProject
//	By ゲヱム道館門下生
//----------------------------------

#include "DxLib.h"
#include "main.h"
#include "enemy.h"

// 変数宣言
CHARACTER enemyMaster[ENEMY_TYPE_MAX];	// 敵の変数
CHARACTER enemy[ENEMY_MAX];				// 敵の総数
int enemyImage[ENEMY_TYPE_MAX][16];		// 敵の画像の種類

// 敵の初期化
void EnemySystemInit(void)
{
	for (int cnt = 0; cnt < ENEMY_TYPE_MAX; cnt++)
	{
		enemyMaster[cnt].size = { 0,0 };		// 敵の初期サイズ
		enemyMaster[cnt].offsetSize = { 0,0 };	// 敵の初期オフセットサイズ
		enemyMaster[cnt].animCnt = 0;			// 敵の初期アニメーションカウント
		enemyMaster[cnt].lifeMax = 0;			// 敵の初期最大ライフ
		enemyMaster[cnt].life = 0;				// 敵の初期ライフ
		enemyMaster[cnt].dir = DIR_DOWN;		// 敵の初期向き
		enemyMaster[cnt].visible = true;		
		enemyMaster[cnt].type = CHARA_ENEMY;
	}

	//------------------------------------------------------------------------------------------
// スライム

	enemyMaster[ENEMY_TYPE_SLIME].size = { 32,32 };		// スライムのサイズ
	enemyMaster[ENEMY_TYPE_SLIME].offsetSize = { 3,7 }; // スライムのオフセットサイズ
	enemyMaster[ENEMY_TYPE_SLIME].lifeMax = 2;			// スライムのライフ
	enemyMaster[ENEMY_TYPE_SLIME].moveSpeed = 1;		// スライムのスピード

	LoadDivGraph("image/character/スライムfin完.png",
		16, 4, 4, 32, 32, enemyImage[ENEMY_TYPE_SLIME]);	// スライムの描画
	//------------------------------------------------------------------------------------------
	// ゴブリン

	enemyMaster[ENEMY_TYPE_GOBLIN].size = { 32,32 };	// ゴブリンのサイズ
	enemyMaster[ENEMY_TYPE_GOBLIN].offsetSize = { 3,7 };// ゴブリンのオフセットサイズ
	enemyMaster[ENEMY_TYPE_GOBLIN].lifeMax = 2;			// ゴブリンのライフ
	enemyMaster[ENEMY_TYPE_GOBLIN].moveSpeed = 1;		// ゴブリンのスピード

	LoadDivGraph("image/character/ゴブリンfin完.png",
		16, 4, 4, 32, 32, enemyImage[ENEMY_TYPE_GOBLIN]);	// ゴブリンの描画
	//------------------------------------------------------------------------------------------

}

// 敵のゲームごとの初期化
void EnemyGameInit(void)
{
	for (int en = 0; en < ENEMY_MAX; en++)
	{
		int rnd = GetRand(ENEMY_TYPE_MAX - 1);
		enemy[en] = enemyMaster[rnd];

		//enemy[en].pos.x += enemy[en].size.x * en;

		// スクリーンのランダムな位置で出現
		enemy[en].pos.x = GetRand(SCREEN_SIZE_X - 1);
		enemy[en].pos.y = GetRand(SCREEN_SIZE_Y - 1);
	}

}

// 敵の描画
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

// 敵の制御処理
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

	