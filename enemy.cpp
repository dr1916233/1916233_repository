//----------------------------------
//	IsekaiKanchoProject
//	By Qนูๅบถ
//----------------------------------

#include "DxLib.h"
#include "main.h"
#include "enemy.h"

int suraimuImage[16];
int enemyImage[ENEMY_TYPE_MAX][16];

// Gฬ๚ป
void EnemySystemInit(void)
{
	LoadDivGraph("image/character/XCfinฎ.png",16,4,4,32,32,enemyImage[ENEMY_TYPE_SURAIMU]);
}

// GฬQ[ฒฦฬ๚ป
void EnemyGameInit(void)
{

}

// Gฬ`ๆ
void EnemyGameDraw(void)
{
	DrawGraph(0, 0, suraimuImage[16], true);

	//DrawCircle(320, 240, 150, GetColor(255,255,255), false);
}

// Gฬงไ
void EnemyControl(void)
{

}