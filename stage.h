//----------------------------------
//	IsekaiKanchoProject
//	By �Q�������ٖ剺��
//----------------------------------

//#pragma once//----------------------------------

// �萔�錾
#define MAP_X_FIELD 40			// �t�B�[���h�̉��傫��
#define MAP_Y_FIELD 30			// �t�B�[���h�̏c�傫��

#define MAP_X_DUNGEON 60		// �t�B�[���h�̉��傫��
#define MAP_Y_DUNGEON 50		// �t�B�[���h�̏c�傫��

#define MAP_IMAGESIZE_X	32		// �}�b�v�摜��X�����̃T�C�Y
#define MAP_IMAGESIZE_Y	32		// �}�b�v�摜��Y�����̃T�C�Y

enum STAGE_ID
{
	STAGE_ID_FIELD,
	STAGE_ID_DUNGEON,
	STAGE_ID_MAX
};

enum EVENT_ID
{
	EVENT_ID_NON,
	EVENT_ID_STG_JUNP,
	EVENT_ID_MAX
};

XY GetStageSize(void);
XY_F GetMapPos(void);

// �v���g�^�C�v�錾	
void StageGameDraw(XY mapPos);				// �X�e�[�W�֘A�̕`��
void StageSystemInit(void);					// �X�e�[�W�֘A�̏�����
void StageGameInit(void);					// �X�e�[�W�Q�[���֘A�̏�����
XY_F StageControl(XY_F playerMoveDiff);			// �X�e�[�W�̐��䏈��
bool IsPass(XY pos);						// �v���C���[�����̃u���b�N��ʉ߂ł��邩����
XY PosToIndex(XY pos);						// �v���C���[�̍��W���}�b�v�̃C���f�b�N�X�ɕϊ����ĕԂ�
EVENT_ID GetEvent(XY pos);
void SetMap(STAGE_ID stageID);
