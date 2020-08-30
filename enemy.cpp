//----------------------------------		
//	IsekaiKanchoProject				
//	By �Q�������ٖ剺��
//----------------------------------

#include "DxLib.h"
#include "main.h"
#include "enemy.h"
#include "player.h"
#include "stage.h"
#include <math.h>

// �ϐ��錾
CHARACTER enemyMaster[ENEMY_TYPE_MAX];	// �G�̕ϐ�
CHARACTER enemy[ENEMY_MAX];				// �G�̑���
int enemyImage[ENEMY_TYPE_MAX][16];		// �G�̉摜�̎��

// �G�̏�����
void EnemySystemInit(void)
{
	for (int cnt = 0; cnt < ENEMY_TYPE_MAX; cnt++)
	{
		enemyMaster[cnt].offsetSize = { 0,0 };	// �G�̏����I�t�Z�b�g�T�C�Y
		enemyMaster[cnt].animCnt = 0;			// �G�̏����A�j���[�V�����J�E���g
		enemyMaster[cnt].life = enemyMaster[cnt].lifeMax;	// �G�̏������C�t
		enemyMaster[cnt].dir = DIR_DOWN;		// �G�̏�������
		enemyMaster[cnt].type = CHARA_ENEMY;
		enemyMaster[cnt].moveFlag = true;
	}

	//------------------------------------------------------------------------------------------
// �X���C��

	enemyMaster[ENEMY_TYPE_SLIME].size = { 32,32 };				// �X���C���̃T�C�Y
	enemyMaster[ENEMY_TYPE_SLIME].offsetSize = { 16,16 };		// �X���C���̃I�t�Z�b�g�T�C�Y
	enemyMaster[ENEMY_TYPE_SLIME].lifeMax = 20;					// �X���C���̃��C�t
	enemyMaster[ENEMY_TYPE_SLIME].moveSpeed = 1;				// �X���C���̃X�s�[�h
	enemyMaster[ENEMY_TYPE_SLIME].attack = 1;					// �X���C���̍U����
	enemyMaster[ENEMY_TYPE_SLIME].enemyType = ENEMY_TYPE_SLIME;	// �G�̎�ނ��X���C���ɃZ�b�g

	LoadDivGraph("image/character/�X���C��fin��.png",
		16, 4, 4, 32, 32, enemyImage[ENEMY_TYPE_SLIME]);		// �X���C���̕`��
	//------------------------------------------------------------------------------------------
	// �S�u����

	enemyMaster[ENEMY_TYPE_GOBLIN].size = { 32,32 };				// �S�u�����̃T�C�Y
	enemyMaster[ENEMY_TYPE_GOBLIN].offsetSize = { 16,18 };			// �S�u�����̃I�t�Z�b�g�T�C�Y
	enemyMaster[ENEMY_TYPE_GOBLIN].lifeMax = 20;					// �S�u�����̃��C�t
	enemyMaster[ENEMY_TYPE_GOBLIN].moveSpeed = 1;					// �S�u�����̃X�s�[�h
	enemyMaster[ENEMY_TYPE_GOBLIN].attack = 1;						// �S�u�����̍U����
	enemyMaster[ENEMY_TYPE_GOBLIN].enemyType = ENEMY_TYPE_GOBLIN;	// �G�̎�ނ��S�u�����ɃZ�b�g

	LoadDivGraph("image/character/�S�u����fin��.png",
		16, 4, 4, 32, 32, enemyImage[ENEMY_TYPE_GOBLIN]);			// �S�u�����̕`��
	//------------------------------------------------------------------------------------------
	// �I�[�N

	enemyMaster[ENEMY_TYPE_OAK].size = { 41,41 };			// �I�[�N�̃T�C�Y
	enemyMaster[ENEMY_TYPE_OAK].offsetSize = { 21,21 };		// �I�[�N�̃I�t�Z�b�g�T�C�Y
	enemyMaster[ENEMY_TYPE_OAK].lifeMax = 40;				// �I�[�N�̃��C�t
	enemyMaster[ENEMY_TYPE_OAK].moveSpeed = 1;				// �I�[�N�̃X�s�[�h
	enemyMaster[ENEMY_TYPE_OAK].attack = 3;					// �I�[�N�̍U����
	enemyMaster[ENEMY_TYPE_OAK].enemyType = ENEMY_TYPE_OAK;	// �G�̎�ނ��I�[�N�ɃZ�b�g

	LoadDivGraph("image/character/�I�[�Nfin��.png",
		16, 4, 4, 41, 41, enemyImage[ENEMY_TYPE_OAK]);		// �I�[�N�̕`��
	//------------------------------------------------------------------------------------------
	// �{�X�}���e�B�R�A

	enemyMaster[ENEMY_TYPE_BOSS].size = { 64,64 };				// �{�X�}���e�B�R�A�̃T�C�Y
	enemyMaster[ENEMY_TYPE_BOSS].offsetSize = { 32,34 };		// �{�X�}���e�B�R�A�̃I�t�Z�b�g�T�C�Y
	enemyMaster[ENEMY_TYPE_BOSS].lifeMax = 40;					// �{�X�}���e�B�R�A�̃��C�t
	enemyMaster[ENEMY_TYPE_BOSS].moveSpeed = 1;					// �{�X�}���e�B�R�A�̃X�s�[�h
	enemyMaster[ENEMY_TYPE_BOSS].attack = 10;					// �{�X�}���e�B�R�A�̍U����
	enemyMaster[ENEMY_TYPE_BOSS].enemyType = ENEMY_TYPE_BOSS;	// �G�̎�ނ��{�X�}���e�B�R�A�ɃZ�b�g

	LoadDivGraph("image/character/�{�X�}���e�B�R�A��fin.png",
		16, 4, 4, 64, 64, enemyImage[ENEMY_TYPE_BOSS]);			// �{�X�}���e�B�R�A�̕`��
	//------------------------------------------------------------------------------------------

}

// �G�̃Q�[�����Ƃ̏�����
void EnemyGameInit(void)
{
	for (int cnt = 0; cnt < ENEMY_MAX; cnt++)
	{
		int rnd = GetRand(ENEMY_TYPE_MAX - 1);
		enemy[cnt] = enemyMaster[rnd];

		//enemy[en].pos.x += enemy[en].size.x * en;

		// �X�N���[���̃����_���Ȉʒu�ŏo��
		//enemy[cnt].pos.x = GetRand(SCREEN_SIZE_X - mapSize.x - 1);
		//enemy[cnt].pos.y = GetRand(SCREEN_SIZE_Y - mapSize.y - 1);
		enemy[cnt].pos.x = 500;
		enemy[cnt].pos.y = 500;
	}
 }

// �G�̃R���g���[��
void EnemyControl(XY playerPos, int cnt)
{
	// �G�̈ړ�
	for (int enemyCnt = 0; enemyCnt < ENEMY_MAX; enemyCnt++)
	{
		playerPos.x = GetPlayerPos().x;
		playerPos.y = GetPlayerPos().y;

		// �G���v���C���[�̋߂��Ȃ�΃v���C���[�Ɍ������Ĉړ�(�Z*�Z�ȓ��ɓ���ƒǐ�)
		if (EnemyPlayerDiff(enemyCnt, 200 * 200))
		{
			enemy[enemyCnt].life = 10;

			if (enemy[enemyCnt].life > 0)
			{
				if (enemy[enemyCnt].pos.x < playerPos.x)
				{
					enemy[enemyCnt].pos.x += enemy[enemyCnt].moveSpeed;
					enemy[enemyCnt].dir = DIR_RIGHT;
					if ((enemy[enemyCnt].pos.x > playerPos.x)) enemy[enemyCnt].pos.x = playerPos.x;
				}

				if (enemy[enemyCnt].pos.x > playerPos.x)
				{
					enemy[enemyCnt].pos.x -= enemy[enemyCnt].moveSpeed;
					enemy[enemyCnt].dir = DIR_LEFT;
					if (enemy[enemyCnt].pos.x < playerPos.x) enemy[enemyCnt].pos.x = playerPos.x;
				}

				if (enemy[enemyCnt].pos.y < playerPos.y)
				{
					enemy[enemyCnt].pos.y += enemy[enemyCnt].moveSpeed;
					enemy[enemyCnt].dir = DIR_DOWN;
					if (enemy[enemyCnt].pos.y > playerPos.y) enemy[enemyCnt].pos.y = playerPos.y;
				}

				if (enemy[enemyCnt].pos.y > playerPos.y)
				{
					enemy[enemyCnt].pos.y -= enemy[enemyCnt].moveSpeed;
					enemy[enemyCnt].dir = DIR_UP;
					if (enemy[enemyCnt].pos.y < playerPos.y) enemy[enemyCnt].pos.y = playerPos.y;
				}
			}
		}
		// �G�̃����_���ړ�
		else
		{
			// �����_���œG�̌�����ς���
			if (GetRand(200) == 0)
			{
				enemy[enemyCnt].dir = (DIR)(GetRand(DIR_MAX - 1));
			}

			// �ړ�����
			if (enemy[enemyCnt].moveFlag)
			{
				switch (enemy[enemyCnt].dir)
				{
				case DIR_DOWN:
					if (enemy[enemyCnt].pos.y > MAP_IMAGESIZE_Y + enemy[enemyCnt].size.y / 2)
					{
						enemy[enemyCnt].pos.y += enemy[enemyCnt].moveSpeed;
					}
					break;
				case DIR_UP:
					if (enemy[enemyCnt].pos.y < mapSize.y * MAP_IMAGESIZE_Y - enemy[enemyCnt].size.y / 2)
					{
						enemy[enemyCnt].pos.y -= enemy[enemyCnt].moveSpeed;
					}
					break;
				case DIR_RIGHT:
					if (enemy[enemyCnt].pos.x < mapSize.x * MAP_IMAGESIZE_X - enemy[enemyCnt].size.x / 2)
					{
						enemy[enemyCnt].pos.x += enemy[enemyCnt].moveSpeed;
					}
					break;
				case DIR_LEFT:
					if (enemy[enemyCnt].pos.x > MAP_IMAGESIZE_X + enemy[enemyCnt].size.x / 2)
					{
						enemy[enemyCnt].pos.x -= enemy[enemyCnt].moveSpeed;
					}
					break;
				default:
					break;
				}
			}
		}
		// �G�̈ړ����[�h�̐؂�ւ�
		if (enemy[enemyCnt].moveFlag && GetRand(60) == 0)
		{
			enemy[enemyCnt].moveFlag = false;
		}
		else if (!enemy[enemyCnt].moveFlag && GetRand(360) == 0)
		{
			enemy[enemyCnt].moveFlag = true;
		}
	}
}

// �G�̕`��
void EnemyGameDraw(XY mapPos)
{
	//�@�A�j���[�V�����p�J�E���g
		for (int en = 0; en < ENEMY_MAX; en++)
		{
			enemy[en].animCnt++;
				//DrawGraph(
				//	enemy[en].pos.x - mapPos.x,
				//	enemy[en].pos.y - mapPos.y + SCREEN_OFFSET_Y,
				//	enemyImage[enemy[en].enemyType][enemy[en].dir * 4 + enemy[en].animCnt / 10 % 4],
				//	true);

				// �`�揈��
				DrawGraph(
					(enemy[en].pos.x - mapPos.x - enemy[en].offsetSize.x),
					(enemy[en].pos.y - mapPos.y - enemy[en].offsetSize.y),
					enemyImage[enemy[en].enemyType][enemy[en].dir * 4 + enemy[en].animCnt / 10 % 4],
					true
				);

				//DrawCircle(enemy[en].pos.x, enemy[en].pos.y, 3, GetColor(255, 0, 255), true);

				DrawBox(
			enemy[en].pos.x - enemy[en].offsetSize.x - mapPos.x,
			enemy[en].pos.y - enemy[en].offsetSize.y - mapPos.y,
			enemy[en].pos.x + enemy[en].offsetSize.x - mapPos.x,
			enemy[en].pos.y + enemy[en].offsetSize.y - mapPos.y,
			GetColor(255, 255, 255),
			false
		);
				//DrawCircle(enemy[en].pos.x - enemy[en].offsetSize.x - mapPos.x + 20,
				//	enemy[en].pos.y - enemy[en].offsetSize.y - mapPos.y,
				//	200, GetColor(255, 255, 255), false);
		}
}


//�@�G���ړ�������֐��Q X�ړ�
//int MoveEnemyX(CHARACTER *enemy, XY playerPos)
//{
//	int speed = (*enemy).moveSpeed;
//	int diff = playerPos.x - (*enemy).pos.x;
//
//	XY_F enemyPosCopy = (*enemy).pos;
//	XY enemyPosTop;
//	XY enemyPosUnder;
//
//	if (diff > 0)
//	{
//		// �E
//		speed = (diff < speed) ? diff : speed;
//
//		enemyPosCopy.x += speed;
//		enemyPosCopy.x += (*enemy).size.x;
//
//		enemyPosTop = { (int)enemyPosCopy.x ,  (int)enemyPosCopy.y };
//		enemyPosUnder = { (int)enemyPosCopy.x ,  (int)enemyPosCopy.y };
//
//		enemyPosUnder.y += (int)enemyPosCopy.y + (*enemy).size.y;
//
//
//		if (IsPassMain(enemyPosTop) && IsPassMain(enemyPosUnder))
//		{
//			(*enemy).pos.x += speed;
//			(*enemy).dir = DIR_RIGHT;
//		}
//	}
//	else
//	{
//		// ��
//		speed = (-diff < speed) ? -diff : speed;
//
//		enemyPosCopy.x -= speed;
//
//		enemyPosTop = { (int)enemyPosCopy.x ,  (int)enemyPosCopy.y };
//		enemyPosUnder = { (int)enemyPosCopy.x ,  (int)enemyPosCopy.y };
//
//		enemyPosUnder.y += (int)enemyPosCopy.y + (*enemy).size.y;
//
//		if (IsPassMain(enemyPosTop) && IsPassMain(enemyPosUnder))
//		{
//			(*enemy).pos.x -= speed;
//			(*enemy).dir = DIR_LEFT;
//		}
//	}
//
//	return speed;
//}
//
//// �G���ړ�������֐��Q Y�ړ�
//int MoveEnemyY(CHARACTER *enemy, XY playerPos)
//{
//	int speed = (*enemy).moveSpeed;
//	int diff = playerPos.y - (*enemy).pos.y;
//
//	XY_F enemyPosCopy = (*enemy).pos;
//	XY enemyPosRIght;
//	XY enemyPosLeft;
//
//	if (diff >= 0)
//	{
//		// ��
//		speed = (diff < speed) ? diff : speed;
//
//		enemyPosCopy.x += speed;
//		enemyPosCopy.x += (*enemy).size.x;
//
//		enemyPosRIght = { (int)enemyPosCopy.x ,  (int)enemyPosCopy.y };
//		enemyPosLeft = { (int)enemyPosCopy.x ,  (int)enemyPosCopy.y };
//
//		enemyPosLeft.y += (int)enemyPosCopy.y + (*enemy).size.y;
//
//
//		if (IsPassMain(enemyPosRIght) && IsPassMain(enemyPosLeft))
//		{
//			(*enemy).pos.y += speed;
//			(*enemy).dir = DIR_DOWN;
//		}
//	}
//	else
//	{
//		// ��
//		speed = (-diff < speed) ? -diff : speed;
//		enemyPosRIght = { (int)enemyPosCopy.x ,  (int)enemyPosCopy.y };
//		enemyPosLeft = { (int)enemyPosCopy.x ,  (int)enemyPosCopy.y };
//
//		enemyPosLeft.y += (int)enemyPosCopy.y + (*enemy).size.y;
//
//		if (IsPassMain(enemyPosRIght) && IsPassMain(enemyPosLeft))
//		{
//			(*enemy).pos.y -= speed;
//			(*enemy).dir = DIR_UP;
//		}
//	}
//	return speed;
//}


XY GetEnemyPos(int en)
{
	return { (int)enemy[en].pos.x,(int)enemy[en].pos.y };
}

XY GetEnemySize(int en)
{
	return enemy[en].size;
}

void EnemyRad(void)
{
	//17+26= 43/2= 21.5= 21
}

// �G�Ƃ̃v���C���[�̋�������
bool EnemyPlayerDiff(int index, int diff)
{
	// �󂯎��������diff�ȉ������肷��
	if (
		(GetPlayerPos().x - enemy[index].pos.x) * (GetPlayerPos().x - enemy[index].pos.x) +
		(GetPlayerPos().y - enemy[index].pos.y) * (GetPlayerPos().y - enemy[index].pos.y) <= diff
		)
	{
		//�@diff�ȉ�
		return true;
	}
	//�@diff�ȏ�
	return false;
}

// �v���C���[�ƓG�̓����蔻��
int PlayerEnemyHitCheck(int playerSize)
{
	for (int eCnt = 0; eCnt < ENEMY_MAX; eCnt++)
	{
		if (enemy[eCnt].life > 0)
		{
			int rad = (enemy[eCnt].offsetSize.x + playerSize) * (enemy[eCnt].offsetSize.x + playerSize);

			if (
				(GetPlayerPos().x - enemy[eCnt].pos.x) * (GetPlayerPos().x - enemy[eCnt].pos.x) +
				(GetPlayerPos().y - enemy[eCnt].pos.y) * (GetPlayerPos().y - enemy[eCnt].pos.y) <= rad
				)
			{
				// �G�ɓ��������瓖�������G�̍U���͂�Ԃ�
				//return enemy[eCnt].attack;
			}
		}
	}
	return 0;
}

// �����œn���ꂽ�z��Y���̓G�L�����Ƀ_���[�W��^����
void DoDamageEnemy(int index,int damage)
{
	enemy[index].life -= damage;
	if (enemy[index].life <= 0) enemy[index].visible = false;
}

