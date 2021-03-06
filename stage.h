//----------------------------------
//	IsekaiKanchoProject
//	By ゲヱム道館門下生
//----------------------------------

//#pragma once//----------------------------------

// 定数宣言
#define MAP_X_FIELD 40			// フィールドの横大きさ
#define MAP_Y_FIELD 30			// フィールドの縦大きさ

#define MAP_X_DUNGEON 60		// ダンジョン1の横大きさ
#define MAP_Y_DUNGEON 50		// ダンジョン1の縦大きさ

#define MAP_X_DUNGEON2 30		// ダンジョン2の横大きさ
#define MAP_Y_DUNGEON2 60		// ダンジョン2の縦大きさ

#define MAP_X_DUNGEON3 50		// ダンジョン3の横大きさ
#define MAP_Y_DUNGEON3 50		// ダンジョン3の縦大きさ

#define MAP_X_DUNGEON4 60		// ダンジョン4の横大きさ
#define MAP_Y_DUNGEON4 40		// ダンジョン4の縦大きさ

#define MAP_X_DUNGEON5 30		// ダンジョン5の横大きさ
#define MAP_Y_DUNGEON5 30		// ダンジョン5の縦大きさ

#define MAP_X_MAX 100			// マップの最大の横大きさ
#define MAP_Y_MAX 100			// マップの最大の縦大きさ

#define MAP_IMAGESIZE_X	32		// マップ画像のX方向のサイズ
#define MAP_IMAGESIZE_Y	32		// マップ画像のY方向のサイズ

enum STAGE_ID
{
	STAGE_ID_FIELD,
	STAGE_ID_DUNGEON,
	STAGE_ID_DUNGEON2,
	STAGE_ID_DUNGEON3,
	STAGE_ID_DUNGEON4,
	STAGE_ID_DUNGEON5,
	STAGE_ID_MAX
};

enum EVENT_ID
{
	EVENT_ID_NON,
	EVENT_ID_STG_JUMP,
	EVENT_ID_STG_DONW,
	EVENT_ID_GAMEOVER,
	EVENT_ID_MAX
};

XY GetStageSize(void);
XY_F GetMapPos(void);

// プロトタイプ宣言	
void StageGameDraw(XY mapPos);				// ステージ関連の描画
void StageSystemInit(void);					// ステージ関連の初期化
void StageGameInit(void);					// ステージゲーム関連の初期化
XY_F StageControl(XY_F playerMoveDiff);			// ステージの制御処理
bool IsPass(XY pos);						// プレイヤーが次のブロックを通過できるか判定
XY PosToIndex(XY pos);						// プレイヤーの座標をマップのインデックスに変換して返す
EVENT_ID GetEvent(XY pos);
void SetMap(STAGE_ID stageID);

extern STAGE_ID stgID;			// ステージのID
extern XY_F mapPos;
extern XY mapSize;
