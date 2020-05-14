//----------------------------------
//	IsekaiKanchoProject
//	By �Q�������ٖ剺��
//----------------------------------

#include "DxLib.h"
#include "main.h"
#include "enemy.h"

int suraimuImage[16];
int enemyImage[ENEMY_TYPE_MAX][16];

// �G�̏�����
void EnemySystemInit(void)
{
	LoadDivGraph("image/character/�X���C��fin��.png",16,4,4,32,32,enemyImage[ENEMY_TYPE_SURAIMU]);

	LoadDivGraph(
		"image/character/�X���C��fin��.png",
		ENEMY_IMAGENUM_X * ENEMY_IMAGENUM_Y,
		ENEMY_IMAGENUM_X,
		ENEMY_IMAGENUM_Y,
		ENEMY_IMAGESIZE_X,
		ENEMY_IMAGESIZE_Y,
		*enemyImage,
		true
	);
}

// �G�̃Q�[�����Ƃ̏�����
void EnemyGameInit(void)
{

}

// �G�̕`��
void EnemyGameDraw(void)
{
	DrawGraph(0, 0, suraimuImage[16], true);

	//DrawCircle(320, 240, 150, GetColor(255,255,255), false);
}

// �G�̐��䏈��
void EnemyControl(void)
{

}