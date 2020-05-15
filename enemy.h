//----------------------------------
//	IsekaiKanchoProject
//	By ゲヱム道館門下生
//----------------------------------

#define ENEMY_MAX 5	// 敵の総数

// 定数
enum ENEMY_TYPE
{
	// 敵の種類
	ENEMY_TYPE_SURAIMU,	
	ENEMY_TYPE_GOBURIN,
	ENEMY_TYPE_MAX
};

//#pragma once//----------------------------------

// プロトタイプ宣言
void EnemySystemInit(void);		// 敵のシステム初期化
void EnemyGameInit(void);		// 敵のゲーム初期化
void EnemyGameDraw(void);		// 敵のゲーム描画
void EnemyControl(void);		// 敵の制御処理