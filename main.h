//----------------------------------
//	IsekaiKanchoProject
//	By ゲヱム道館門下生
//----------------------------------

//#pragma once//----------------------------------

// 定数宣言
#define SCREEN_SIZE_X	800		// ゲームスクリーンのXサイズ
#define SCREEN_SIZE_Y	600		// ゲームスクリーンのYサイズ

// シーン遷移用
enum SCENE_ID {
	SCENE_INIT,		// 初期化用
	SCENE_TITLE,	// タイトル
	SCENE_GAME,		// ゲームメイン
	SCENE_GAMEOVER,	// ゲームオーバー
	SCENE_MAX,
};

// プロトタイプ宣言
bool SystemInit(void);	// システム初期化
void InitScene(void);	// 初期化シーン
void TitleScene(void);	// タイトルシーン
void TitleDraw(void);	// タイトル描画
void GameScene(void);	// ゲームシーン
void GameDraw(void);	// ゲーム描画
void GameOverScene(void);	// ゲームオーバーシーン
void GameOverDraw(void);	// ゲームオーバー描画