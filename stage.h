//#pragma once
//----------------------------------
//	IsekaiKanchoProject
//	By �Q�������ٖ剺��
//----------------------------------

//#pragma once//----------------------------------

// �萔�錾
#define MAP_Y_FIELD 20
#define MAP_X_FIELD 30
#define MAP_IMAGESIZE_X	32	// �}�b�v�摜��X�����̃T�C�Y
#define MAP_IMAGESIZE_Y	32	// �}�b�v�摜��Y�����̃T�C�Y

XY GetStageSize(void);
XY GetMapPos(void);

// �v���g�^�C�v�錾	
void StageGameDraw(XY mapPos);	// �X�e�[�W�֘A�̕`��
void StageSystemInit(void);	// �X�e�[�W�֘A�̏�����
void StageGameInit(void);	// �X�e�[�W�Q�[���֘A�̏�����
XY StageControl(XY playerMoveDiff);	// �X�e�[�W�̐��䏈��