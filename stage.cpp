//----------------------------------
//	IsekaiKanchoProject
//	By ゲヱム道館門下生
//----------------------------------

#include "DxLib.h"
#include "main.h"
#include "stage.h"

// マップ画像用
int FieldMap[3][256];
int DungeonMap[6][256];
int mapID;

int map[MAP_Y_FIELD][MAP_X_FIELD];
XY mapPos;
STAGE_ID stgID;

// フィールドマップ
// 草
int grass[MAP_Y_FIELD][MAP_X_FIELD] = {
	{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 30, 31,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 30, 31,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 30, 31,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 36, 37,  0,  0,  0,  0, 20, 15, 15, 15, 21,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 36, 14, 14, 14, 37,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{ 20, 15, 15, 15, 21,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{ 36, 14, 14,150, 31,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{  0,  0,  0, 30, 31,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{  0,  0,  0, 30 ,31,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{  0,  0,  0, 30, 31,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{  0,  0,  0, 30,166, 15, 15, 15, 21,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{  0,  0,  0,151, 14, 14, 14, 14, 37,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{  0, 46, 46, 46, 46, 46,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 20, 15, 15, 21,  0,  0,  0, 20, 15, 21,  0,  0},
	{  0, 46, 46, 46, 46, 46,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 30,167,167,166, 15, 15, 15,183,167, 31,  0,  0},
	{  0,  0,  0, 46, 46, 46, 46, 46,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 30,167,167,167,167,167,167,167,167, 31,  0,  0},
	{  0,  0,  0, 46, 46, 46, 46, 46,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 30,167,167,167,167,167,167,167,167, 31,  0,  0},
	{  0,  0,  0, 46, 46, 46, 46, 46,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 30,167,167,167,167,167,167,167,167, 31,  0,  0},
	{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 36, 14, 14, 14, 14, 14, 14, 14, 14, 37,  0,  0},
	{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 20, 15, 15, 15, 15, 15, 15, 15, 21,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 30,167,167,167,167,167,167,167, 31,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 30,167,167,167,167,167,167,167, 31,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 30,167,167,167,167,167,167,167, 31,  0,  0,  0,  0, 20, 15, 15, 15, 21,  0,  0,  0,  0,  0,  0,  0,  0},
	{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 36, 14, 14, 14, 14, 14, 14, 14, 37,  0,  0,  0,  0, 36, 14, 14, 14, 37,  0,  0,  0,  0,  0,  0,  0,  0},
	{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
};

// オブジェ用
int Field[MAP_Y_FIELD][MAP_X_FIELD] = {
	{448,449,450,451,452,453,454,455,  0, 13, 12,  0, 11,512,513,513,513,513,514,  0,  0,512,513,513,513,513,513,513,513,513,514,  0, 52, 53, 54, 55, 52, 53, 54, 55},
	{456,457,458,459,460,461,462,463,  0,  0,  0, 28, 29,512,513,513,513,513,514,235,236,512,513,513,513,513,229,230,231,513,514,  0, 68, 69, 70, 71, 68, 69, 70, 71},
	{464,465,466,467,468,469,470,471,  0,  0,  0,  0,  0,520,521,521,521,521,522,251,252,520,521,521,521,521,199,246,215,521,522,  0, 84, 85, 86, 87, 84, 85, 86, 87},
	{472,473,474,475,476,477,478,479,  0,  0, 14, 14, 14,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 24, 14,  0, 14, 25,  0,  0,100,101,102,103,100,101,102,103},
	{480,481,482,483,484,485,486,487,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{  0,  0,  0,  0,  0,278,279,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{  0,  0,  0,  0,  0,294,295,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{189,190,191,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{205,206,207,  0,  0,  0,  0,310,  0,  0,  0,  0,  0,  0,  0,  0,310,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{221,222,223,  0,  0,  0,  0,310,  0,189,190,191,  0,  0,  0,  0,310,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,509,509,509,509,  0,  0,  0,509,509,509,  0,  0},
	{  0,144,  0,  0,  0,  0,  0,  0,  0,205,206,207,  0,  0,  0,  0,  0, 32, 33, 34, 35,  0,  0,  0,  0,  0,  0,498,513,513,513,513,211,211,211,513,198,513,496,  0},
	{  0,  0,  0,  0,  0,  0,  0,  0,  0,221,222,223,  0,  0,  0,  0,  0, 48, 49, 50, 51,  0,310,  0,  0,  0,  0,498,521,521,521,521,227,227,227,521,214,521,496,  0},
	{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 64, 65, 66, 67,  0,  0,  0,  0,  0,  0,498,128,  0,  5,  0,243,243,243,447, 14,447,496,  0},
	{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 80, 81, 82, 83,  0,  0,  0,  0,  0,  0,498,  0,129,  0,  0,  0,  0,  0,447,447,447,496,  0},
	{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 96, 97, 98, 99,  0,  0,  0,  0,  0,  0,498,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,496,  0},
	{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,310,  0,  0,  0,  0,  0,498,  0,  0,  0,  0,  0,131,130,  0,  0,  0,496,  0},
	{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,498,  0,145,  0,  0,  0,  0,131,  0,  0,  0,496,  0},
	{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,498,  0,  0,  0,131,  0,  0,  0,  0,  0,  0,496,  0},
	{203,204,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,489,489,489,489,489,489,489,489,489,489,  0,  0},
	{219,220,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,318,  0,  0,  0,  0,  0,  0,  0,318,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{  0,  0,448,449,454,455,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{  0,  0,456,457,458,463,  0,  0,378,379,  0,  0,  0,  0,  0,  0,  0,106,107,108,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,189,190,191,  0,  0,  0,  0},
	{  0,  0,464,465,466,471,  0,  0,394,395,  0,  0,  0,  0,318,  0,  0,  0,  0,  0,  0,  0,318,  0,  0,  0,  0,  0,106,107,108,  0,  0,205,206,207,  0,  0,  0,  0},
	{  0,  0,472,473,474,479,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,144,  0,  0,  0,  0,  0,  0,253,221,222,223,  0,  0,  0,  0},
	{  0,  0,480,481,482,487,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,509,509,509,509,509,509,509,509,509,  0,253,  0,  0,  0,  0},
	{448,449,454,455,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,498,537,537,537,537,537,537,537,537,537,496,  0,  0,  0,  0,  0},
	{456,457,458,463,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,498,563,563,564,563,563,563,563,562,563,496,  0,  0,  0,  0,  0},
	{464,465,466,471,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,498,563,562,563,560,561,562,563,563,564,496,  0,237,  0,  0,  0},
	{472,473,474,479,  0,  0,  0,  0,  0,  0,  0,  0,113,113,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,498,562,564,563,568,569,562,563,562,563,496,  0,  0,  0,  0,  0},
	{480,481,482,487,  0,  0,  0,  0,  0,  0,  0,  0,113,113,114,114,  0,  0,  0,  0,  0,  0,  0,  0,498,564,563,562,563,563,562,563,564,562,496,  0,  0,  0,  0,  0},
};


int dungeon1[MAP_Y_DUNGEON][MAP_X_DUNGEON] = {
	{12,12,12,12,12,12,12,12,12,12,12,12,15,17,17,17,17,17,17,17,17,17,17,17,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
	{15,17,17,17,17,17,17,17,17,17,14,12,10,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
	{10,12,12,12,12,12,12,12,12,12, 8,12,10,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
	{10,12,12,12,12,12,12,12,12,12, 8,12,10,12, 0, 1, 2,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
	{10,12,12,12,12,12,12,12,12,12,16,17,18,12, 8, 9,10,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
	{10,12,12,12,12,12,12,12,12,12,12,12,12,12,16,17,18,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
	{10,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
	{10,12,12,12,12,12,12,12,12,12, 0, 1, 2,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
	{10,12,12,12,12,12,12,12,12,12, 8,12,10,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
	{10,12,12,12,12,12,12,12,12,12, 8,12, 7, 1, 1, 1, 1, 2,12,12, 0, 1,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
	{ 7, 1, 1, 1, 1, 1, 1, 1, 1, 1, 6,12,12,12,12,12,12,10,12,12, 8,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
	{12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,10,12,12, 8,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
	{12,12,12,12,12,12,12,12,15,17,17,17,17,17,17,17,17,18,12,12,16,17,17,17,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
	{12,12,12,12,12,12,12,12,10,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
	{12,12,12,12,12,12,12,12,10,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
	{12,12,12,12,12,12,12,12,10,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
	{12,12,12,12,12,12,12,12,10,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
	{12,12,12,12,12,12,12,12,10,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
	{12,12,12,12,12,12,12,12,10,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
	{12,12,12,12,12,12,12,12,10,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
	{12,12,12,12,12,12,12,12,10,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
	{12,12,12,12,12,12,12,12,10,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
	{12,12,12,12,12,12,12,12,10,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
	{12,12,12,12,12,12,12,12,10,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
	{12,12,12,12,12,12,12,12,10,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
	{12,12,12,12,12,12,12,12,10,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
	{12,12,12,12,12,12,12,12,10,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
	{12,12,12,12,12,12,12,12, 7, 1,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
	{12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
	{12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
	{12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
	{12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
	{12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
	{12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
	{12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
	{12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
	{12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
	{12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
	{12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
	{12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
	{12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
	{12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
	{12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
	{12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
	{12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
	{12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
	{12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
	{12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
	{12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
	{12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
};

// ステージ関連の初期化
void StageSystemInit(void)
{
	// ステージの描画読み込み
	// 地上のマップ
	LoadDivGraph("image/stage/field_grass.png",  192, 16, 12, MAP_IMAGESIZE_X, MAP_IMAGESIZE_Y, FieldMap[0]);
	LoadDivGraph("image/stage/field_forest.png", 128,  8, 16, MAP_IMAGESIZE_X, MAP_IMAGESIZE_Y, FieldMap[1]);
	LoadDivGraph("image/stage/field_obj.png",    256, 16, 16, MAP_IMAGESIZE_X, MAP_IMAGESIZE_Y, FieldMap[2]);
	// ダンジョンのマップ
	LoadDivGraph("image/stage/cave_dig_bg.png", 128, 8, 16, MAP_IMAGESIZE_X, MAP_IMAGESIZE_Y, DungeonMap[0]);
	LoadDivGraph("image/stage/cave_dig_obj.png", 128, 8, 16, MAP_IMAGESIZE_X, MAP_IMAGESIZE_Y, DungeonMap[1]);
	LoadDivGraph("image/stage/cave_ground.png", 128, 8, 16, MAP_IMAGESIZE_X, MAP_IMAGESIZE_Y, DungeonMap[2]);
	LoadDivGraph("image/stage/cave_rock_bg.png", 128, 8, 16, MAP_IMAGESIZE_X, MAP_IMAGESIZE_Y, DungeonMap[3]);
	LoadDivGraph("image/stage/cave_rock_obj.png", 128, 8, 16, MAP_IMAGESIZE_X, MAP_IMAGESIZE_Y, DungeonMap[4]);
	LoadDivGraph("image/stage/cave_stream.png", 128, 8, 16, MAP_IMAGESIZE_X, MAP_IMAGESIZE_Y, DungeonMap[5]);

}

// ステージのゲーム毎の初期化
void StageGameInit(void)
{
	mapPos = { 0,0 };
}

XY GetStageSize(void)
{
	if (dungeon1)
	{
		return { MAP_X_DUNGEON,MAP_Y_DUNGEON };
	}
	else
	{
		return { MAP_X_FIELD,MAP_Y_FIELD };
	}
}

// ステージ関連の描画
void StageGameDraw(XY mapPos)
{
	// フィールド用
	//for (int y = 0; y < MAP_Y_FIELD; y++)
	//{
	//	for (int x = 0; x < MAP_X_FIELD; x++)
	//	{
	//		// 草用
	//		DrawGraph(x * MAP_IMAGESIZE_X - mapPos.x, y * MAP_IMAGESIZE_Y - mapPos.y, FieldMap[0][grass[y][x]], true);
	//		// オブジェ用
	//		if (Field[y][x] >= 448)
	//		{
	//			DrawGraph(x * MAP_IMAGESIZE_X - mapPos.x, y * MAP_IMAGESIZE_Y - mapPos.y, FieldMap[1][Field[y][x] - 448], true);

	//		}
	//		else if (Field[y][x] >= 256)
	//		{
	//			DrawGraph(x * MAP_IMAGESIZE_X - mapPos.x, y * MAP_IMAGESIZE_Y - mapPos.y, FieldMap[0][Field[y][x] - 256], true);
	//		}
	//		else
	//		{
	//			DrawGraph(x * MAP_IMAGESIZE_X - mapPos.x, y * MAP_IMAGESIZE_Y - mapPos.y, FieldMap[2][Field[y][x]], true);
	//		}
	//	}
	//}
	for (int y = 0; y < MAP_Y_DUNGEON; y++)
	{
		for (int x = 0; x < MAP_X_DUNGEON; x++)
		{
			DrawGraph(x * MAP_IMAGESIZE_X - mapPos.x, y * MAP_IMAGESIZE_Y - mapPos.y, DungeonMap[0][dungeon1[y][x]], true);
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
	// 木材
	case 106:
//	case 107:
//	case 108:
//	// 石
//	case 128:
//	case 235:
//	case 236:
//	case 237:
//	case 251:
//	case 252:
//	case 253:
//	case 318:
//	// 小物
//	case  11:
//	case  12:
//	case  13:
//	case  28:
//	case  29:
//	case 113:
//	case 114:
//	// 塀
//	case 14:
//	// ツボ系
//	case   8:
//	case   9:
//	case  10:
//	case  24:
//	case  25:
//	case  26:
//	// 土凹
//	case 262:
//	// 土凹集団
//	case 278:
//	case 279:
//	case 280:
//	case 281:
//	// 木株
//	case 144:
//	case 145:
//	// 木
//	case  32:
//	case  33:
//	case  34:
//	case  35:
//	case  48:
//	case  49:
//	case  50:
//	case  51:
//	case  64:
//	case  65:
//	case  66:
//	case  67:
//	case  80:
//	case  81:
//	case  82:
//	case  83:
//	case  96:
//	case  97:
//	case  98:
//	case  99:
//	case  52:
//	case  53:
//	case  54:
//	case  55:
//	case  68:
//	case  69:
//	case  70:
//	case  71:
//	case  84:
//	case  85:
//	case  86:
//	case  87:
//	case 100:
//	case 101:
//	case 102:
//	case 103:
//	case 189:
//	case 190:
//	case 191:
//	case 205:
//	case 206:
//	case 207:
//	case 221:
//	case 222:
//	case 223:
//	case 448:
//	case 449:
//	case 450:
//	case 451:
//	case 452:
//	case 453:
//	case 454:
//	case 455:
//	case 456:
//	case 457:
//	case 458:
//	case 459:
//	case 460:
//	case 461:
//	case 462:
//	case 463:
//	case 464:
//	case 465:
//	case 466:
//	case 467:
//	case 468:
//	case 469:
//	case 470:
//	case 471:
//	case 472:
//	case 473:
//	case 474:
//	case 475:
//	case 476:
//	case 477:
//	case 478:
//	case 479:
//	case 480:
//	case 481:
//	case 482:
//	case 483:
//	case 484:
//	case 485:
//	case 486:
//	case 487:
//	// 崖
//	case 489:
//	case 496:
//	case 498:
//	case 509:
//	case 512:
//	case 513:
//	case 514:
//	case 520:
//	case 521:
//	case 522:
//	case 537:
//// ダンジョン穴
//	case 199:
//	case 215:
//	case 229:
//	case 231:
		return false;
	default:
		break;
	}

	return true;
}

EVENT_ID GetEvent(XY pos)
{
	XY Index;

	Index = PosToIndex(pos);

	switch (Field[Index.y][Index.x])
	{
	case 246:
		return EVENT_ID_STG_JUNP;
	default:
		break;
	}
	return EVENT_ID_NON;
}

void SetMap(STAGE_ID stageID)
{
	switch (stageID)
	{
	case STAGE_ID_FIELD:
		for (int y = 0; y < MAP_Y_FIELD; y++)
		{
			for (int x = 0; x < MAP_X_FIELD; x++)
			{
				map[y][x] = grass[y][x];
			}
		}
	case STAGE_ID_DUNGEON:
		for (int y = 0; y < MAP_Y_DUNGEON; y++)
		{
			for (int x = 0; x < MAP_X_DUNGEON; x++)
			{
				map[y][x] = dungeon1[y][x];
			}
		}
	default:
		break;
	}
	// ステージ管理用IDを変更
	stgID = stageID;
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