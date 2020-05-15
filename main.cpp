//----------------------------------
//	IsekaiKanchoProject
//	By ゲヱム道館門下生
//----------------------------------

#include "DxLib.h"
#include "main.h"
#include "keycheck.h"
#include "effect.h"
#include "stage.h"
#include "player.h"
#include "enemy.h"


// 変数宣言
int SceneCounter;	// シーンカウンター用
int testCount;	

SCENE_ID scnID;			// 今のシーン
SCENE_ID scnIDpre;		// 1フレーム前のシーン

// メイン関数
int WINAPI WinMain(HINSTANCE , HINSTANCE , LPSTR, int)
{
	if (!SystemInit())
	{
		return 0;
	}

	// ゲームループ
 	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClsDrawScreen();

		KeyCheck();
		SceneCounter++;

		if (scnID != scnIDpre)
		{
			scnIDpre = scnID;
			SceneCounter = 0;
		}
		
		switch (scnID)
		{
		case SCENE_INIT:
			InitScene();
			scnID = SCENE_TITLE;
			break;
		case SCENE_TITLE:
			SceneChange(scnID,10,true);
			TitleScene();
			break;
		case SCENE_GAME:
			SceneChange(scnID,10,true);
			GameScene();
			break;
		case SCENE_GAMEOVER:
			SceneChange(scnID,10,true);
			GameOverScene();
			break;
		}

		ScreenFlip();
	}

	DxLib_End();     

	return 0; 
}

// システム初期化
bool SystemInit(void)
{
	bool rtnFlag = true;

	// システム処理
	SetWindowText("異世界館長");
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);

	// DxLib初期化
	if (DxLib_Init() == -1)
	{
		return -1;
	}

	SetDrawScreen(DX_SCREEN_BACK);

	// 変数の初期化
	SceneCounter = 0;


	// 各関数のシステム初期化　

	EffectInit();		// エフェクトの初期化
	KeyInit();			// キー情報初期化
	StageSystemInit();	// ステージ関連の初期化
	PlayerSystemInit();	// プレイヤー関連の初期化
	EnemySystemInit();	// 敵関連の初期化


	return rtnFlag; 
}

// 初期化シーン
void InitScene(void)
{
	PlayerGameInit();	// プレイヤーのゲームループ毎初期化
	StageGameInit();	// ステージのゲームループ毎初期化
	EnemyGameInit();	// 敵のゲームループ毎初期化
}

// タイトルシーン
void TitleScene(void)
{
	if (keyTrgUp[KEY_SPACE] && !FadeInFlag && !FadeOutFlag)
	{
		FadeOutFlag = true;
	}

	// タイトル描画
	TitleDraw();
}

// タイトル描画
void TitleDraw(void)
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "タイトルシーンカウンター  %d", SceneCounter);
	DrawBox(100, 100, 700, 500, GetColor(0, 0, 255), true);
}

// ゲームメインシーン
void GameScene(void)
{
	// スペースが押されたらフェードアウト処理
	if (keyTrgUp[KEY_SPACE] && !FadeInFlag && !FadeOutFlag)
	{
		FadeOutFlag = true;
	}

	// 各オブジェクトの制御処理

	XY playerMoveDiff = PlayerControl(GetStageSize(), { 0,0 });	// プレイヤーの制御
	XY mapPosMain = StageControl(playerMoveDiff);		// ステージの制御
	EnemyControl();		// 敵の制御

	// ゲーム描画
	GameDraw(mapPosMain);
}

// ゲームメインシーン描画
void GameDraw(XY mapPos)
{

	// シーンカウンター描画
	DrawFormatString(0, 0, GetColor(255, 255, 255), "ゲームシーンカウンター  %d", SceneCounter);

	// ステージの描画
	if (pauseFlag)
	{
		SetDrawBright(50, 50, 50);
		StageGameDraw(mapPos);
		SetDrawBright(255, 255, 255);
	}
	else
	{
		DrawBox(100, 100, 700, 500, GetColor(255, 0, 0), true);
		// 各オブジェクト描画
		StageGameDraw(mapPos);
		EnemyGameDraw();
		PlayerGameDraw(mapPos);
	}
}

// ゲームオーバーシーン
void GameOverScene(void)
{
	if (keyTrgUp[KEY_SPACE] && !FadeInFlag && !FadeOutFlag)
	{
		FadeOutFlag = true;
	}
	GameOverDraw();
}

// ゲームオーバーシーン描画
void GameOverDraw(void)
{
	DrawFormatString(0, 0, GetColor(255,255,255), "ゲームオーバーシーンカウンター  %d", SceneCounter);
	DrawBox(100, 100, 700, 500, GetColor(0, 255, 0), true);
}