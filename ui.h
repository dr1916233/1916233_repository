//----------------------------------
//	IsekaiKanchoProject
//	By ゲヱム道館門下生
//----------------------------------

//#pragma once//----------------------------------

// 定数宣言
#define ITEMBOX_MAX 36
#define ITEMBOX_SIZE_X 38
#define ITEMBOX_SIZE_Y 38

enum MENU_TYPE
{
	MENU_TYPE_CRAFT,
	MENU_TYPE_STATUS,
	MENU_TYPE_INVENTORY,
	MENU_TYPE_MAX
};

// プロトタイプ宣言
void UiSystemInit(void);
void UiGameInit(void);
void UiControl(void);
void UiGameDraw(bool menuFlag);
