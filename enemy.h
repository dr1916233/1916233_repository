//----------------------------------
//	IsekaiKanchoProject
//	By ゲヱム道館門下生
//----------------------------------

#define ENEMY_MAX 3	// 敵の総数


// 定数
enum ENEMY_TYPE
{
	// 敵の種類
	ENEMY_TYPE_SURAIMU,	
	ENEMY_TYPE_MAX
};

//#pragma once//----------------------------------

// プロトタイプ宣言
void EnemySystemInit(void);		// 敵のシステム初期化
void EnemyGameInit(void);		// 敵のゲーム初期化
void EnemyGameDraw(XY mapPos);		// 敵のゲーム描画
void EnemyControl(void);		// 敵の制御処理


XY GetEnemyPos(int en);
XY GetEnemySize(int en);