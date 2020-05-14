//----------------------------------
//	IsekaiKanchoProject
//	By ƒQƒ‘ƒ€“¹ŠÙ–å‰º¶
//----------------------------------

#include "DxLib.h"
#include "main.h"
#include "enemy.h"

int suraimuImage[16];
int enemyImage[ENEMY_TYPE_MAX][16];

// “G‚Ì‰Šú‰»
void EnemySystemInit(void)
{
	LoadDivGraph("image/character/ƒXƒ‰ƒCƒ€finŠ®.png",16,4,4,32,32,enemyImage[ENEMY_TYPE_SURAIMU]);

	LoadDivGraph(
		"image/character/ƒXƒ‰ƒCƒ€finŠ®.png",
		ENEMY_IMAGENUM_X * ENEMY_IMAGENUM_Y,
		ENEMY_IMAGENUM_X,
		ENEMY_IMAGENUM_Y,
		ENEMY_IMAGESIZE_X,
		ENEMY_IMAGESIZE_Y,
		*enemyImage,
		true
	);
}

// “G‚ÌƒQ[ƒ€‚²‚Æ‚Ì‰Šú‰»
void EnemyGameInit(void)
{

}

// “G‚Ì•`‰æ
void EnemyGameDraw(void)
{
	DrawGraph(0, 0, suraimuImage[16], true);

	//DrawCircle(320, 240, 150, GetColor(255,255,255), false);
}

// “G‚Ì§Œäˆ—
void EnemyControl(void)
{

}