//----------------------------------
//	IsekaiKanchoProject
//	By ゲヱム道館門下生
//----------------------------------

//#pragma once//----------------------------------

// 定数宣言
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
void UiGameDraw(void);
