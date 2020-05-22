//----------------------------------
//	IsekaiKanchoProject
//	By �Q�������ٖ剺��
//----------------------------------

//#pragma once//----------------------------------

// �萔�錾
#define PLAYER_IMAGENUM_X 4			// �v���C���[�摜��X�����̐�
#define PLAYER_IMAGENUM_Y 4			// �v���C���[�摜��Y�����̐�
#define PLAYER_IMAGESIZE_X 32		// �v���C���[�摜��X�����̃T�C�Y
#define PLAYER_IMAGESIZE_Y 32		// �v���C���[�摜��Y�����̃T�C�Y
#define PLAYER_SIZE_X 20			// �v���C���[��X�������T�C�Y
#define PLAYER_SIZE_Y 32			// �v���C���[��Y�������T�C�Y
#define PLAYER_OFFSET_X 6	// �v���C���[��X�����̗]���T�C�Y
#define PLAYER_LIFE_DEF	100			// �v���C���[�̃f�t�H���gHP
#define PLAYER_SPEED_DEF 3			// �v���C���[�̃f�t�H���g�ړ����x

// --------------------
// �\����
// --------------------



// �v���g�^�C�v�錾

void PlayerSystemInit(void);	// �v���C���[���̏�����
void PlayerGameInit(void);		// �v���C���[�̃Q�[���֌W�̏�����
void PlayerGameDraw(XY mapPos);		// �v���C���[�̃Q�[���`��
XY PlayerControl(XY chipNum, XY mapPos);	// �v���C���[�̐��䏈��
CHARACTER* GetPlayerPointer(void);
