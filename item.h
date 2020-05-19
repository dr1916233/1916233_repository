//----------------------------------
//	IsekaiKanchoProject
//	By ゲヱム道館門下生
//----------------------------------

//#pragma once

// 定数
#define ITEM_MAX 5	// アイテムの最大数

// アイテムの種類
enum ITEM_TYPE
{
	ITEM_TYPE_MAX
};

// アイテムの状態
enum ITEM_STATE
{
	ITEM_STATE_INVENTORY,
	ITEM_STATE_DROP,
	ITEM_STATE_MAX
};


// 構造体

// アイテム用構造体
struct ITEM
{
	ITEM_STATE state;
	ITEM_TYPE type;
};

// インベントリ用構造体
struct INVENTORY
{
	ITEM_TYPE itemType;
	int num;
};

// プロトタイプ宣言
void ItemSystemInit(void);
void ItemGameInit(void);
void ItemGameDraw(XY mapPos);
void ItemControl(void);




