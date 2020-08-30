//----------------------------------		
//	IsekaiKanchoProject				
//	By ゲヱム道館門下生
//----------------------------------

#include "DxLib.h"
#include "main.h"
#include "enemy.h"
#include "player.h"
#include "stage.h"
#include <math.h>

// 変数宣言
CHARACTER enemyMaster[ENEMY_TYPE_MAX];	// 敵の変数
CHARACTER enemy[ENEMY_MAX];				// 敵の総数
int enemyImage[ENEMY_TYPE_MAX][16];		// 敵の画像の種類

// 敵の初期化
void EnemySystemInit(void)
{
	for (int cnt = 0; cnt < ENEMY_TYPE_MAX; cnt++)
	{
		enemyMaster[cnt].offsetSize = { 0,0 };	// 敵の初期オフセットサイズ
		enemyMaster[cnt].animCnt = 0;			// 敵の初期アニメーションカウント
		enemyMaster[cnt].life = enemyMaster[cnt].lifeMax;	// 敵の初期ライフ
		enemyMaster[cnt].dir = DIR_DOWN;		// 敵の初期向き
		enemyMaster[cnt].type = CHARA_ENEMY;
		enemyMaster[cnt].moveFlag = true;
	}

	//------------------------------------------------------------------------------------------
// スライム

	enemyMaster[ENEMY_TYPE_SLIME].size = { 32,32 };				// スライムのサイズ
	enemyMaster[ENEMY_TYPE_SLIME].offsetSize = { 16,16 };		// スライムのオフセットサイズ
	enemyMaster[ENEMY_TYPE_SLIME].lifeMax = 20;					// スライムのライフ
	enemyMaster[ENEMY_TYPE_SLIME].moveSpeed = 1;				// スライムのスピード
	enemyMaster[ENEMY_TYPE_SLIME].attack = 1;					// スライムの攻撃力
	enemyMaster[ENEMY_TYPE_SLIME].enemyType = ENEMY_TYPE_SLIME;	// 敵の種類をスライムにセット

	LoadDivGraph("image/character/スライムfin完.png",
		16, 4, 4, 32, 32, enemyImage[ENEMY_TYPE_SLIME]);		// スライムの描画
	//------------------------------------------------------------------------------------------
	// ゴブリン

	enemyMaster[ENEMY_TYPE_GOBLIN].size = { 32,32 };				// ゴブリンのサイズ
	enemyMaster[ENEMY_TYPE_GOBLIN].offsetSize = { 16,18 };			// ゴブリンのオフセットサイズ
	enemyMaster[ENEMY_TYPE_GOBLIN].lifeMax = 20;					// ゴブリンのライフ
	enemyMaster[ENEMY_TYPE_GOBLIN].moveSpeed = 1;					// ゴブリンのスピード
	enemyMaster[ENEMY_TYPE_GOBLIN].attack = 1;						// ゴブリンの攻撃力
	enemyMaster[ENEMY_TYPE_GOBLIN].enemyType = ENEMY_TYPE_GOBLIN;	// 敵の種類をゴブリンにセット

	LoadDivGraph("image/character/ゴブリンfin完.png",
		16, 4, 4, 32, 32, enemyImage[ENEMY_TYPE_GOBLIN]);			// ゴブリンの描画
	//------------------------------------------------------------------------------------------
	// オーク

	enemyMaster[ENEMY_TYPE_OAK].size = { 41,41 };			// オークのサイズ
	enemyMaster[ENEMY_TYPE_OAK].offsetSize = { 21,21 };		// オークのオフセットサイズ
	enemyMaster[ENEMY_TYPE_OAK].lifeMax = 40;				// オークのライフ
	enemyMaster[ENEMY_TYPE_OAK].moveSpeed = 1;				// オークのスピード
	enemyMaster[ENEMY_TYPE_OAK].attack = 3;					// オークの攻撃力
	enemyMaster[ENEMY_TYPE_OAK].enemyType = ENEMY_TYPE_OAK;	// 敵の種類をオークにセット

	LoadDivGraph("image/character/オークfin完.png",
		16, 4, 4, 41, 41, enemyImage[ENEMY_TYPE_OAK]);		// オークの描画
	//------------------------------------------------------------------------------------------
	// ボスマンティコア

	enemyMaster[ENEMY_TYPE_BOSS].size = { 64,64 };				// ボスマンティコアのサイズ
	enemyMaster[ENEMY_TYPE_BOSS].offsetSize = { 32,34 };		// ボスマンティコアのオフセットサイズ
	enemyMaster[ENEMY_TYPE_BOSS].lifeMax = 40;					// ボスマンティコアのライフ
	enemyMaster[ENEMY_TYPE_BOSS].moveSpeed = 1;					// ボスマンティコアのスピード
	enemyMaster[ENEMY_TYPE_BOSS].attack = 10;					// ボスマンティコアの攻撃力
	enemyMaster[ENEMY_TYPE_BOSS].enemyType = ENEMY_TYPE_BOSS;	// 敵の種類をボスマンティコアにセット

	LoadDivGraph("image/character/ボスマンティコア完fin.png",
		16, 4, 4, 64, 64, enemyImage[ENEMY_TYPE_BOSS]);			// ボスマンティコアの描画
	//------------------------------------------------------------------------------------------

}

// 敵のゲームごとの初期化
void EnemyGameInit(void)
{
	for (int cnt = 0; cnt < ENEMY_MAX; cnt++)
	{
		int rnd = GetRand(ENEMY_TYPE_MAX - 1);
		enemy[cnt] = enemyMaster[rnd];

		//enemy[en].pos.x += enemy[en].size.x * en;

		// スクリーンのランダムな位置で出現
		//enemy[cnt].pos.x = GetRand(SCREEN_SIZE_X - mapSize.x - 1);
		//enemy[cnt].pos.y = GetRand(SCREEN_SIZE_Y - mapSize.y - 1);
		enemy[cnt].pos.x = 500;
		enemy[cnt].pos.y = 500;
	}
 }

// 敵のコントロール
void EnemyControl(XY playerPos, int cnt)
{
	// 敵の移動
	for (int enemyCnt = 0; enemyCnt < ENEMY_MAX; enemyCnt++)
	{
		playerPos.x = GetPlayerPos().x;
		playerPos.y = GetPlayerPos().y;

		// 敵がプレイヤーの近くならばプレイヤーに向かって移動(〇*〇以内に入ると追跡)
		if (EnemyPlayerDiff(enemyCnt, 200 * 200))
		{
			enemy[enemyCnt].life = 10;

			if (enemy[enemyCnt].life > 0)
			{
				if (enemy[enemyCnt].pos.x < playerPos.x)
				{
					enemy[enemyCnt].pos.x += enemy[enemyCnt].moveSpeed;
					enemy[enemyCnt].dir = DIR_RIGHT;
					if ((enemy[enemyCnt].pos.x > playerPos.x)) enemy[enemyCnt].pos.x = playerPos.x;
				}

				if (enemy[enemyCnt].pos.x > playerPos.x)
				{
					enemy[enemyCnt].pos.x -= enemy[enemyCnt].moveSpeed;
					enemy[enemyCnt].dir = DIR_LEFT;
					if (enemy[enemyCnt].pos.x < playerPos.x) enemy[enemyCnt].pos.x = playerPos.x;
				}

				if (enemy[enemyCnt].pos.y < playerPos.y)
				{
					enemy[enemyCnt].pos.y += enemy[enemyCnt].moveSpeed;
					enemy[enemyCnt].dir = DIR_DOWN;
					if (enemy[enemyCnt].pos.y > playerPos.y) enemy[enemyCnt].pos.y = playerPos.y;
				}

				if (enemy[enemyCnt].pos.y > playerPos.y)
				{
					enemy[enemyCnt].pos.y -= enemy[enemyCnt].moveSpeed;
					enemy[enemyCnt].dir = DIR_UP;
					if (enemy[enemyCnt].pos.y < playerPos.y) enemy[enemyCnt].pos.y = playerPos.y;
				}
			}
		}
		// 敵のランダム移動
		else
		{
			// ランダムで敵の向きを変える
			if (GetRand(200) == 0)
			{
				enemy[enemyCnt].dir = (DIR)(GetRand(DIR_MAX - 1));
			}

			// 移動処理
			if (enemy[enemyCnt].moveFlag)
			{
				switch (enemy[enemyCnt].dir)
				{
				case DIR_DOWN:
					if (enemy[enemyCnt].pos.y > MAP_IMAGESIZE_Y + enemy[enemyCnt].size.y / 2)
					{
						enemy[enemyCnt].pos.y += enemy[enemyCnt].moveSpeed;
					}
					break;
				case DIR_UP:
					if (enemy[enemyCnt].pos.y < mapSize.y * MAP_IMAGESIZE_Y - enemy[enemyCnt].size.y / 2)
					{
						enemy[enemyCnt].pos.y -= enemy[enemyCnt].moveSpeed;
					}
					break;
				case DIR_RIGHT:
					if (enemy[enemyCnt].pos.x < mapSize.x * MAP_IMAGESIZE_X - enemy[enemyCnt].size.x / 2)
					{
						enemy[enemyCnt].pos.x += enemy[enemyCnt].moveSpeed;
					}
					break;
				case DIR_LEFT:
					if (enemy[enemyCnt].pos.x > MAP_IMAGESIZE_X + enemy[enemyCnt].size.x / 2)
					{
						enemy[enemyCnt].pos.x -= enemy[enemyCnt].moveSpeed;
					}
					break;
				default:
					break;
				}
			}
		}
		// 敵の移動モードの切り替え
		if (enemy[enemyCnt].moveFlag && GetRand(60) == 0)
		{
			enemy[enemyCnt].moveFlag = false;
		}
		else if (!enemy[enemyCnt].moveFlag && GetRand(360) == 0)
		{
			enemy[enemyCnt].moveFlag = true;
		}
	}
}

// 敵の描画
void EnemyGameDraw(XY mapPos)
{
	//　アニメーション用カウント
		for (int en = 0; en < ENEMY_MAX; en++)
		{
			enemy[en].animCnt++;
				//DrawGraph(
				//	enemy[en].pos.x - mapPos.x,
				//	enemy[en].pos.y - mapPos.y + SCREEN_OFFSET_Y,
				//	enemyImage[enemy[en].enemyType][enemy[en].dir * 4 + enemy[en].animCnt / 10 % 4],
				//	true);

				// 描画処理
				DrawGraph(
					(enemy[en].pos.x - mapPos.x - enemy[en].offsetSize.x),
					(enemy[en].pos.y - mapPos.y - enemy[en].offsetSize.y),
					enemyImage[enemy[en].enemyType][enemy[en].dir * 4 + enemy[en].animCnt / 10 % 4],
					true
				);

				//DrawCircle(enemy[en].pos.x, enemy[en].pos.y, 3, GetColor(255, 0, 255), true);

				DrawBox(
			enemy[en].pos.x - enemy[en].offsetSize.x - mapPos.x,
			enemy[en].pos.y - enemy[en].offsetSize.y - mapPos.y,
			enemy[en].pos.x + enemy[en].offsetSize.x - mapPos.x,
			enemy[en].pos.y + enemy[en].offsetSize.y - mapPos.y,
			GetColor(255, 255, 255),
			false
		);
				//DrawCircle(enemy[en].pos.x - enemy[en].offsetSize.x - mapPos.x + 20,
				//	enemy[en].pos.y - enemy[en].offsetSize.y - mapPos.y,
				//	200, GetColor(255, 255, 255), false);
		}
}


//　敵を移動させる関数群 X移動
//int MoveEnemyX(CHARACTER *enemy, XY playerPos)
//{
//	int speed = (*enemy).moveSpeed;
//	int diff = playerPos.x - (*enemy).pos.x;
//
//	XY_F enemyPosCopy = (*enemy).pos;
//	XY enemyPosTop;
//	XY enemyPosUnder;
//
//	if (diff > 0)
//	{
//		// 右
//		speed = (diff < speed) ? diff : speed;
//
//		enemyPosCopy.x += speed;
//		enemyPosCopy.x += (*enemy).size.x;
//
//		enemyPosTop = { (int)enemyPosCopy.x ,  (int)enemyPosCopy.y };
//		enemyPosUnder = { (int)enemyPosCopy.x ,  (int)enemyPosCopy.y };
//
//		enemyPosUnder.y += (int)enemyPosCopy.y + (*enemy).size.y;
//
//
//		if (IsPassMain(enemyPosTop) && IsPassMain(enemyPosUnder))
//		{
//			(*enemy).pos.x += speed;
//			(*enemy).dir = DIR_RIGHT;
//		}
//	}
//	else
//	{
//		// 左
//		speed = (-diff < speed) ? -diff : speed;
//
//		enemyPosCopy.x -= speed;
//
//		enemyPosTop = { (int)enemyPosCopy.x ,  (int)enemyPosCopy.y };
//		enemyPosUnder = { (int)enemyPosCopy.x ,  (int)enemyPosCopy.y };
//
//		enemyPosUnder.y += (int)enemyPosCopy.y + (*enemy).size.y;
//
//		if (IsPassMain(enemyPosTop) && IsPassMain(enemyPosUnder))
//		{
//			(*enemy).pos.x -= speed;
//			(*enemy).dir = DIR_LEFT;
//		}
//	}
//
//	return speed;
//}
//
//// 敵を移動させる関数群 Y移動
//int MoveEnemyY(CHARACTER *enemy, XY playerPos)
//{
//	int speed = (*enemy).moveSpeed;
//	int diff = playerPos.y - (*enemy).pos.y;
//
//	XY_F enemyPosCopy = (*enemy).pos;
//	XY enemyPosRIght;
//	XY enemyPosLeft;
//
//	if (diff >= 0)
//	{
//		// 下
//		speed = (diff < speed) ? diff : speed;
//
//		enemyPosCopy.x += speed;
//		enemyPosCopy.x += (*enemy).size.x;
//
//		enemyPosRIght = { (int)enemyPosCopy.x ,  (int)enemyPosCopy.y };
//		enemyPosLeft = { (int)enemyPosCopy.x ,  (int)enemyPosCopy.y };
//
//		enemyPosLeft.y += (int)enemyPosCopy.y + (*enemy).size.y;
//
//
//		if (IsPassMain(enemyPosRIght) && IsPassMain(enemyPosLeft))
//		{
//			(*enemy).pos.y += speed;
//			(*enemy).dir = DIR_DOWN;
//		}
//	}
//	else
//	{
//		// 上
//		speed = (-diff < speed) ? -diff : speed;
//		enemyPosRIght = { (int)enemyPosCopy.x ,  (int)enemyPosCopy.y };
//		enemyPosLeft = { (int)enemyPosCopy.x ,  (int)enemyPosCopy.y };
//
//		enemyPosLeft.y += (int)enemyPosCopy.y + (*enemy).size.y;
//
//		if (IsPassMain(enemyPosRIght) && IsPassMain(enemyPosLeft))
//		{
//			(*enemy).pos.y -= speed;
//			(*enemy).dir = DIR_UP;
//		}
//	}
//	return speed;
//}


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

// 敵とのプレイヤーの距離判定
bool EnemyPlayerDiff(int index, int diff)
{
	// 受け取った距離diff以下か判定する
	if (
		(GetPlayerPos().x - enemy[index].pos.x) * (GetPlayerPos().x - enemy[index].pos.x) +
		(GetPlayerPos().y - enemy[index].pos.y) * (GetPlayerPos().y - enemy[index].pos.y) <= diff
		)
	{
		//　diff以下
		return true;
	}
	//　diff以上
	return false;
}

// プレイヤーと敵の当たり判定
int PlayerEnemyHitCheck(int playerSize)
{
	for (int eCnt = 0; eCnt < ENEMY_MAX; eCnt++)
	{
		if (enemy[eCnt].life > 0)
		{
			int rad = (enemy[eCnt].offsetSize.x + playerSize) * (enemy[eCnt].offsetSize.x + playerSize);

			if (
				(GetPlayerPos().x - enemy[eCnt].pos.x) * (GetPlayerPos().x - enemy[eCnt].pos.x) +
				(GetPlayerPos().y - enemy[eCnt].pos.y) * (GetPlayerPos().y - enemy[eCnt].pos.y) <= rad
				)
			{
				// 敵に当たったら当たった敵の攻撃力を返す
				//return enemy[eCnt].attack;
			}
		}
	}
	return 0;
}

// 引数で渡された配列添字の敵キャラにダメージを与える
void DoDamageEnemy(int index,int damage)
{
	enemy[index].life -= damage;
	if (enemy[index].life <= 0) enemy[index].visible = false;
}

