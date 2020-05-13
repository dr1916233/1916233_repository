//----------------------------------
//	IsekaiKanchoProject
//	By ゲヱム道館門下生
//----------------------------------

#include "DxLib.h"
#include "main.h"
#include "keycheck.h"

// 変数宣言
bool keyTrgUp[KEY_MAX];
bool keyTrgDown[KEY_MAX];
bool keyNow[KEY_MAX];
bool keyOld[KEY_MAX];


// キー情報の初期化
void KeyInit(void)
{
	// キー情報の初期化
	for (int keyID = 0; keyID < KEY_MAX; keyID++)
	{
		keyTrgUp[keyID] = false;
		keyTrgDown[keyID] = false;
		keyNow[keyID] = false;
		keyOld[keyID] = false;
	}
}

// キーの状態をチェック
void KeyCheck(void)
{
	//　1フレーム前の状態をチェック
	for (int keyID = 0; keyID < KEY_MAX; keyID++)
	{
		keyOld[keyID] = keyNow[keyID];
		//keyTrgUp[keyID] = true;
	}

	// 今のフレームの状態を保存
	keyNow[KEY_SPACE] = (bool)CheckHitKey(KEY_INPUT_SPACE);

	// トリガー処理
	for (int keyID = 0; keyID < KEY_MAX; keyID++)
	{
		// トリガーの情報の初期化
		keyTrgDown[keyID] = false;
		keyTrgUp[keyID] = false;

		// トリガー情報の取得
		if (!keyOld[keyID] && keyNow[keyID])
		{
			keyTrgUp[keyID] = true;
		}
	}
}