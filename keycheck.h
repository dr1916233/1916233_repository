//----------------------------------
//	IsekaiKanchoProject
//	By ゲヱム道館門下生
//----------------------------------

//#pragma once//----------------------------------

// プロトタイプ宣言
void KeyInit(void);		// キー情報の初期化
void KeyCheck(void);	// キーの状態を取得
XY GetMousePos(void);	// マウスの座標取得用

// キー制御用
enum KEY_ID {
	KEY_SPACE,
	KEY_DOWN,
	KEY_RIGHT,
	KEY_LEFT,
	KEY_UP,
	KEY_E,
	KEY_R,
	KEY_MENU,
	KEY_NORMAL_ATTACK,
	KEY_SPECIAL_ATTACK,
	KEY_MAX
};

// exturn宣言
extern bool keyTrgUp[KEY_MAX];
extern bool keyTrgDown[KEY_MAX];
extern bool keyNow[KEY_MAX];
extern bool keyOld[KEY_MAX];

extern bool mouseTrgUp;
extern bool mouseNow;
extern XY mousePos;