//----------------------------------
//	IsekaiKanchoProject
//	By ゲヱム道館門下生
//----------------------------------

#include "DxLib.h"
#include "main.h"
#include "stage.h"

// マップ画像

int FieldMap[2][192];

XY map[MAP_Y_FIELD][MAP_X_FIELD];
XY mapPos;

// フィールドマップ
int Field[MAP_Y_FIELD][MAP_X_FIELD] = {
	{192,193,198,199,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{200,201,202,207,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{208,209,210,215,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{216,217,218,223,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{224,225,226,231,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
};


// ステージ関連の初期化
void StageSystemInit(void)
{

	// ステージの描画読み込み
	// 地上のマップ
	//LoadDivGraph("image/stage/field_forest.png", 128, 8, 16, MAP_IMAGESIZE_X, MAP_IMAGESIZE_Y, FieldMap1);
	//LoadDivGraph("image/stage/field_grass.png", 192, 16, 12, MAP_IMAGESIZE_X, MAP_IMAGESIZE_Y, FieldMap2);

	LoadDivGraph("image/stage/field_grass.png", 192, 16, 12, MAP_IMAGESIZE_X, MAP_IMAGESIZE_Y, FieldMap[0]);
	LoadDivGraph("image/stage/field_forest.png", 128, 8, 16, MAP_IMAGESIZE_X, MAP_IMAGESIZE_Y, FieldMap[1]);
}

// ステージのゲーム毎の初期化
void StageGameInit(void)
{
	mapPos = { 0,0 };
}

XY GetStageSize(void)
{
	return { MAP_X_FIELD,MAP_Y_FIELD };
}

// ステージ関連の描画
void StageGameDraw(XY mapPos)
{
	// フィールド用
	for (int y = 0; y <= MAP_Y_FIELD; y++)
	{
		for (int x = 0; x <= MAP_X_FIELD; x++)
		{
			if (Field[y][x] > 192)
			{
				DrawGraph(x * MAP_IMAGESIZE_X - mapPos.x, y * MAP_IMAGESIZE_Y - mapPos.y, FieldMap[1][Field[y][x] - 192], true);

			}
			else
			{
				DrawGraph(x * MAP_IMAGESIZE_X - mapPos.x, y * MAP_IMAGESIZE_Y - mapPos.y, FieldMap[0][Field[y][x]], true);
			}
		}
	}
}

// プレイヤーが次のブロックを通過できるか判定
bool IsPass(XY pos)
{
	XY Index;

	Index = PosToIndex(pos);

	switch (Field[Index.y][Index.x])
	{
	case 199:
		return false;
	default:
		break;
	}

	return true;
}

// プレイヤーの座標をマップインデックスにして返す
XY PosToIndex(XY pos)
{
	XY rtnIndex;

	rtnIndex.x = pos.x / MAP_IMAGESIZE_X;
	rtnIndex.y = pos.y / MAP_IMAGESIZE_Y;

	return rtnIndex;
}

XY StageControl(XY playerMoveDiff)
{
	mapPos.x += playerMoveDiff.x;
	mapPos.y += playerMoveDiff.y;

	return mapPos;
}

XY GetMapPos(void)
{
	return mapPos;
}