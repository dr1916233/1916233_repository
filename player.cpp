//----------------------------------
//	IsekaiKanchoProject
//	By �Q�������ٖ剺��
//----------------------------------

#include "DxLib.h"
#include "main.h"
#include "player.h"
#include "keycheck.h"

// �ϐ��錾
CHARACTER player;
int playerImage[PLAYER_IMAGENUM_Y][PLAYER_IMAGENUM_X];

// �v���C���[���̏�����
void PlayerSystemInit(void)
{
	// �v���C���[�̉摜�ǂݍ���
	LoadDivGraph(
		"image/character/kancho.png",
		PLAYER_IMAGENUM_X * PLAYER_IMAGENUM_Y,
		PLAYER_IMAGENUM_X,
		PLAYER_IMAGENUM_Y,
		PLAYER_IMAGESIZE_X,
		PLAYER_IMAGESIZE_Y,
		*playerImage,
		true
	);
}

// �v���C���[�̃Q�[����������
void PlayerGameInit(void)
{
	// �v���C���[��񏉊���
	player.animCnt = 0;
	player.animCnt = 10;
	player.dir = DIR_DOWN;
	player.lifeMax = PLAYER_LIFE_DEF;
	player.life = player.lifeMax;
	player.moveSpeed = PLAYER_SPEED_DEF;
	player.pos = { 100.0f,100.0f };
	player.size = { 32,32 };
	player.type = CHARA_PLAYER;
	player.visible = true;
}

// �v���C���[���̕`��
void PlayerGameDraw(void)
{
	player.animCnt++;
	DrawGraph(player.pos.x, player.pos.y, playerImage[player.dir][player.animCnt / 10 % 4], true);
}

// �v���C���[�̐��䏈��
XY PlayerControl(void)
{
	XY playerPosRec = { (int)player.pos.x, (int)player.pos.y };
	DIR playerDirRec = player.dir;

	player.dir = DIR_MAX;

	// �L�[�����擾����
	if (keyNow[KEY_DOWN]) player.dir = DIR_DOWN;
	if (keyNow[KEY_RIGHT]) player.dir = DIR_RIGHT;
	if (keyNow[KEY_LEFT]) player.dir = DIR_LEFT;
	if (keyNow[KEY_UP]) player.dir = DIR_UP;

	// �ړ�����
	switch (player.dir)
	{
	case DIR_DOWN:
		player.pos.y += player.moveSpeed;
		break;
	case DIR_RIGHT:
		player.pos.x += player.moveSpeed;
		break;
	case DIR_LEFT:
		player.pos.x -= player.moveSpeed;
		break;
	case DIR_UP:
		player.pos.y -= player.moveSpeed;
		break;
	default:
		player.dir = playerDirRec;
		break;
	}

	return { (int)player.pos.x - playerPosRec.x ,(int)player.pos.y - playerPosRec.y };
}



