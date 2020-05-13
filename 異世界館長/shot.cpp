//o‰Æ—Ç‘¾
//----------------------------------

#include <math.h>
#include "DxLib.h"
#include "main.h"
#include "keycheck.h"
#include "shot.h"
#include "enemy.h"


// •Ï”éŒ¾
CHARACTER shot[SHOT_MAX];
CHARACTER enemyShot[ENEMY_MAX];
int shotImage[2];

// ’eŠÖ˜A‚ÌƒVƒXƒeƒ€‰Šú‰»
void ShotSysInit(void)
{
	LoadDivGraph("bmp/shot.bmp", 2, 2, 1, 12, 12, shotImage);
}

// ’eŠÖ˜A‚ÌƒQ[ƒ€‰Šú‰»
void ShotGameInit(void)
{
	// ƒvƒŒƒCƒ„[‚Ì’e‚ğ‰Šú‰»
	for (int cnt = 0; cnt < SHOT_MAX; cnt++)
	{
		shot[cnt].lifeMax = SHOT_LIFE_MAX;
		shot[cnt].moveDir = DIR_DOWN;
		shot[cnt].moveSpeed = SHOT_SPEED_DEF;
		shot[cnt].pos.x = 100;
		shot[cnt].pos.y = 100;
		shot[cnt].animCnt = 0;
		shot[cnt].size.x = 12;
		shot[cnt].size.y = 12;
		shot[cnt].offsetSize.x = shot[cnt].size.x / 2;
		shot[cnt].offsetSize.y = shot[cnt].size.y / 2;
	}

	// “G‚Ì’e‚ğ‰Šú‰»
	for (int cnt = 0; cnt < SHOT_MAX; cnt++)
	{
		enemyShot[cnt].lifeMax = SHOT_LIFE_MAX;
		enemyShot[cnt].moveDir = DIR_DOWN;
		enemyShot[cnt].moveSpeed = SHOT_SPEED_DEF;
		enemyShot[cnt].pos.x = 110;
		enemyShot[cnt].pos.y = 110;
		enemyShot[cnt].animCnt = 0;
		enemyShot[cnt].size.x = 12;
		enemyShot[cnt].size.y = 12;
		enemyShot[cnt].offsetSize.x = enemyShot[cnt].size.x / 2;
		enemyShot[cnt].offsetSize.y = enemyShot[cnt].size.y / 2;
	}
}

// ’e‚ÌƒRƒ“ƒgƒ[ƒ‹
void ShotControl(void)
{
	// ’e‚ÌˆÚ“®ˆ—
	for (int sCnt = 0; sCnt < SHOT_MAX; sCnt++)
	{
		switch (shot[sCnt].moveDir)
		{
		case DIR_UP:
			shot[sCnt].pos.y -= shot[sCnt].moveSpeed;
			shot[sCnt].life--;
			break;
		case DIR_DOWN:
			shot[sCnt].pos.y += shot[sCnt].moveSpeed;
			shot[sCnt].life--;
			break;
		case DIR_LEFT:
			shot[sCnt].pos.x -= shot[sCnt].moveSpeed;
			shot[sCnt].life--;
			break;
		case DIR_RIGHT:
			shot[sCnt].pos.x += shot[sCnt].moveSpeed;
			shot[sCnt].life--;
			break;
		}
		AddCharOrder(
			CHARACTER_SHOT,
			sCnt,
			shot[sCnt].pos.y + shot[sCnt].size.y / 2
		);
	}

	// “G‚Ì’e‚ÌˆÚ“®ˆ—
	for (int sCnt = 0; sCnt < SHOT_MAX; sCnt++)
	{
		switch (enemyShot[sCnt].moveDir)
		{
		case DIR_UP:
			enemyShot[sCnt].pos.y -= enemyShot[sCnt].moveSpeed;
			enemyShot[sCnt].life--;
			break;
		case DIR_DOWN:
			enemyShot[sCnt].pos.y += enemyShot[sCnt].moveSpeed;
			enemyShot[sCnt].life--;
			break;
		case DIR_LEFT:
			enemyShot[sCnt].pos.x -= enemyShot[sCnt].moveSpeed;
			enemyShot[sCnt].life--;
			break;
		case DIR_RIGHT:
			enemyShot[sCnt].pos.x += enemyShot[sCnt].moveSpeed;
			enemyShot[sCnt].life--;
			break;
		}
		AddCharOrder(
			CHARACTER_ENEMY_SHOT,
			sCnt,
			enemyShot[sCnt].pos.y + enemyShot[sCnt].size.y / 2
		);
	}
}

// ’e‚Ì•`‰æ
void ShotGameDraw(XY map, int index, CHARACTER_TYPE type)
{
	switch (type)
	{
	case CHARACTER_SHOT:
		if (shot[index].life > 0)
		{
			shot[index].animCnt++;
			DrawGraph(
				shot[index].pos.x - map.x - shot[index].offsetSize.x,
				shot[index].pos.y - map.y - shot[index].offsetSize.y,
				shotImage[shot[index].animCnt / 5 % 2],
				true
			);
		}
		break;
	case CHARACTER_ENEMY_SHOT:
		if (enemyShot[index].life > 0)
		{
			enemyShot[index].animCnt++;
			DrawGraph(
				enemyShot[index].pos.x - map.x - enemyShot[index].offsetSize.x,
				enemyShot[index].pos.y - map.y - enemyShot[index].offsetSize.y,
				shotImage[enemyShot[index].animCnt / 5 % 2],
				true
			);
		}
		break;
	default:
		break;
	}
}

// ’e‚Ì¶¬ˆ—
void CreateShot(XY pPos, DIR pDir)
{
	for (int sCnt = 0; sCnt < SHOT_MAX; sCnt++)
	{
		if (shot[sCnt].life <= 0)
		{
			shot[sCnt].pos.x = pPos.x;
			shot[sCnt].pos.y = pPos.y;
			shot[sCnt].moveDir = pDir;
			shot[sCnt].life = shot[sCnt].lifeMax;
			break;
		}
	}
}

// “G‚Ì’e‚Ì¶¬ˆ—
void CreateEnemyShot(XY ePos, DIR eDir)
{
	for (int sCnt = 0; sCnt < ENEMY_SHOT_MAX; sCnt++)
	{
		if (enemyShot[sCnt].life <= 0)
		{
			enemyShot[sCnt].pos.x = ePos.x;
			enemyShot[sCnt].pos.y = ePos.y;
			enemyShot[sCnt].moveDir = eDir;
			enemyShot[sCnt].life = enemyShot[sCnt].lifeMax;
			break;
		}
	}
}


