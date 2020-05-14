//----------------------------------
//	IsekaiKanchoProject
//	By ゲヱム道館門下生
//----------------------------------

#include "DxLib.h"
#include "main.h"
#include "enemy.h"

int suraimuImage[16];
int enemyImage[ENEMY_TYPE_MAX][16];

// 敵の初期化
void EnemySystemInit(void)
{
	LoadDivGraph("image/character/スライムfin完.png",16,4,4,32,32,enemyImage[ENEMY_TYPE_SURAIMU]);

	LoadDivGraph(
		"image/character/スライムfin完.png",
		ENEMY_IMAGENUM_X * ENEMY_IMAGENUM_Y,
		ENEMY_IMAGENUM_X,
		ENEMY_IMAGENUM_Y,
		ENEMY_IMAGESIZE_X,
		ENEMY_IMAGESIZE_Y,
		*enemyImage,
		true
	);
}

// 敵のゲームごとの初期化
void EnemyGameInit(void)
{

}

// 敵の描画
void EnemyGameDraw(void)
{
	DrawGraph(0, 0, suraimuImage[16], true);

	//DrawCircle(320, 240, 150, GetColor(255,255,255), false);
}

// 敵の制御処理
void EnemyControl(void)
{

}