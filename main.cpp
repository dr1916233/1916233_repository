//----------------------------------	
//	IsekaiKanchoProject
//	By ゲヱム道館門下生
//----------------------------------

#include "DxLib.h"
#include "main.h"
#include "enemy.h"
#include "keycheck.h"
#include "effect.h"
#include "stage.h"
#include "player.h"
#include "item.h"
#include "ui.h"

// 変数宣言
int SceneCounter;	// シーンカウンター用
int testCount;	

SCENE_ID scnID;			// 今のシーン
SCENE_ID scnIDpre;		// 1フレーム前のシーン

bool menuFlag;		// ゲームメニュー画面判定用
int enemyHitList[ENEMY_MAX];	// 敵にヒットしたリスト
int listIndex = 0;	// 敵キャラクターの配列インデックス保持リストのカウント用

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
	free(GetInventoryPointer());
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
	ItemSystemInit();	// アイテムの初期化
	UiSystemInit();		// UIの初期化

	return rtnFlag; 
}

// 初期化シーン
void InitScene(void)
{
	menuFlag = false;	// メニュー画面表示状態をfalseにする

		
	StageGameInit();	// ステージのゲームループ毎初期化
	EnemyGameInit();	// 敵のゲームループ毎初期化
	ItemGameInit(PlayerGameInit());	// アイテムのゲームループ毎初期化
	UiGameInit();		// UIのゲームループ毎初期化
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

	// 敵のヒットリストの初期化
	for (int enemyCnt = 0; enemyCnt < ENEMY_MAX; enemyCnt++)
	{
		enemyHitList[enemyCnt] = -1;
	}
	listIndex = 0;

	// 各オブジェクトの制御処理
	XY_F mapPosMain;	// マップ移動量保存用

	if (menuFlag)
	{
		mapPosMain = GetMapPos();
		if (keyTrgUp[KEY_MENU]) menuFlag = false;
		UiControl();	// UIの制御
	}
	else
	{
		if (keyTrgUp[KEY_MENU]) menuFlag = true;
		XY_F playerMoveDiff = PlayerControl(GetStageSize(), GetMapPos());	// プレイヤーの制御
		mapPosMain = StageControl(playerMoveDiff);		// ステージの制御
		EnemyControl({ (int)playerMoveDiff.x,(int)playerMoveDiff.y }, SceneCounter);		// 敵の制御
		ItemControl();	// アイテムの制御
	}

	// ゲーム描画
	GameDraw({ (int)mapPosMain.x,(int)mapPosMain.y });
}

// ゲームメインシーン描画
void GameDraw(XY mapPos)
{

	// シーンカウンター描画
	DrawFormatString(0, 0, GetColor(255, 255, 255), "ゲームシーンカウンター  %d", SceneCounter);

	// ステージの描画
	if (menuFlag)
	{
		SetDrawBright(50, 50, 50);
		StageGameDraw(mapPos);
		EnemyGameDraw(mapPos);
		PlayerGameDraw(mapPos);
		ItemGameDraw(mapPos);
		SetDrawBright(255, 255, 255);
	}
	else
	{
		DrawBox(100, 100, 700, 500, GetColor(255, 0, 0), true);
		// 各オブジェクト描画
		StageGameDraw(mapPos);
		EnemyGameDraw(mapPos);
		PlayerGameDraw(mapPos);
		ItemGameDraw(mapPos);
	}

	// オフセットエリア描画
	DrawBox(0, 0, 800, 60, GetColor(15, 15, 15), true);

	// UI描画
	UiGameDraw(menuFlag);
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

// 矩形の当たり判定(接触：0、非接触：-1、ダメージがある場合：1以上の整数)
int RectHitCheckMain(CHARATYPE type, XY pos1,  XY size1)
{
	// 判定先のキャラクタータイプの状態保持用変数
	XY pos2 = {0,0};
	XY size2 = {0,0};
	// 判定後のオブジェクトの攻撃力取得用変数
	int attack = -1;
	
	// 判定を取りたいオブジェクト情報を取得
	switch (type)
	{
	case CHARA_PLAYER:
		// pos1 = GetPlayerPos();
		// size2 = GetPlayerSize();
		//if ((pos1.x + size1.x > pos2.x) &&
		//	(pos1.x < pos2.x + size2.x) &&
		//	(pos1.y + size1.y > pos2.y) &&
		//	(pos1.y < pos2.y + size2.y))
		//{
		//	attack = -1;
		//}
		break;
	case CHARA_ENEMY:
		for (int en = 0; en < ENEMY_MAX; en++)
		{
			pos2 = GetEnemyPos(en);
			size2 = GetEnemySize(en);
	/*		if ((pos1.x + size1.x >= pos2.x) &&
				(pos1.y <= pos2.x + size2.x) &&
				(pos1.x <= pos2.x + size2.x) &&
				(pos1.y >= pos2.y - size2.y))
			{
				attack = 0;
			}*/
			if ((pos1.x + size1.x >= pos2.x) &&
				(pos1.y <= pos2.x + size2.x) &&
				(pos1.x <= pos2.x + size2.x) &&
				(pos1.y >= pos2.y - size2.y))
			{
				attack = 0;
			}
		}
		break;
	case CHARA_MAGIC:
		// pos1 = GetMagicPos();
		// size2 = GetMagicSize();
		//if ((pos1.x + size1.x > pos2.x) &&
		//	(pos1.x < pos2.x + size2.x) &&
		//	(pos1.y + size1.y > pos2.y) &&
		//	(pos1.y < pos2.y + size2.y))
		//{
		//	attack = -1;
		//}
		break;
	default:
		break;
	}
	
	return attack;
}

// 円と円の当たり判定
bool CircleHitCheckMain(CHARATYPE type, XY pos1, XY size1,int rad)
{
	// 返り値用変数
	bool rtnFlag = false;

	// 判定を取るオブジェクトの情報用変数
	XY pos2 = { 0,0 };
	XY size2 = { 0,0 };

	// 座標を画像の中心にする
	pos1.x += size1.x / 2;
	pos1.y += size1.y / 2;

	switch (type)
	{
	case CHARA_PLAYER:
		break;
	case CHARA_ENEMY:
		for (int en = 0; en < ENEMY_MAX; en++)
		{
			pos2 = GetEnemyPos(en);
			size2 = GetEnemySize(en);
	// 画像の真ん中を座標の中心にする
			pos2.x = pos2.x + size2.x / 2;
			pos2.y = pos2.y + size2.y / 2;
			size2.x = (size2.x + size2.y) / 2; // 画像の縦サイズと横サイズの半分の平均を半径として判定を取る
			if ((pos2.x - pos1.x) * (pos2.x - pos1.x) + (pos2.y - pos1.y) * (pos2.y - pos1.y) <= 22*22 + rad*rad)
			{
				rtnFlag = true;
				enemyHitList[listIndex] = en;
				listIndex++;
			}
		}
		break;
	case CHARA_MAGIC:
		break;
	default:
		break;
	}

	return rtnFlag;
}

// アイテムとプレイヤーの当たり判定
void ItemHitCheckMain(XY pPos, XY pSize)
{
	for (int itemCnt = 0; itemCnt < ITEM_MAX; itemCnt++)
	{
		// アイテムの座標を取得
		XY itemPos = GetItemPos(itemCnt);

		if ((pPos.x + pSize.x > itemPos.x) &&
			(itemPos.x + ITEM_SIZE_X > pPos.x) &&
			(pPos.y + pSize.x > itemPos.y) &&
			(itemPos.y + ITEM_SIZE_Y > pPos.y))
		{
			if (keyTrgUp[KEY_E])
			{
				if (AddInventoryList(itemCnt))
				{
					DeleteItem(itemCnt);
					return;
				}
			}
		}
	}
}

// 引数で渡されたキャラクターのHPをダメージ分減算する
void DoDamageMain(CHARATYPE charaType, int damage)
{
	switch (charaType)
	{
	case CHARA_PLAYER:
		break;
	case CHARA_ENEMY:
		for (int enemyCnt = 0; enemyCnt <= listIndex; enemyCnt++)
		{
			DoDamageEnemy(enemyHitList[enemyCnt], damage);
		}
		break;
	default:
		break;
	}
}

// プレイヤーから移動予定座標の座標を貰って移動できるかを調べる
bool IsPassMain(XY playerPos)
{
	if (IsPass(playerPos)) return true;
	else return false;
}

// インベントリーの描画を促し、描画したインベントリの数を返す
int InventoryItemDrawMain(void)
{
	return InventoryItemDraw();
}

// マウスの座標取得用
XY GetMousePosMain(void)
{
	return GetMousePos();
}

// アイテム使用用
bool UseItemMain(int index)
{
	return UseItem(GetPlayerPointer(), index);
}

// プレイヤーの情報を取得
CHARACTER GetPlayerMain(void)
{
	return GetPlayer();
}

// プレイヤーのポインタを取得
CHARACTER* GetPlayerPointerMain(void)
{
	return GetPlayerPointer();
}

void UpdateInvenyoryListMain(int max)
{
	UpdateInventoryList(max);
}

void DeleteInventoryListMain(int index)
{
	DeleteInventoryList(index);
}

void GetEventMain(XY pos)
{
	GetEvent(pos);
	if (GetEvent(pos) == EVENT_ID_STG_JUNP)
	{
		SetMap(STAGE_ID_DUNGEON);
	}
}