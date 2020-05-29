//----------------------------------
//	IsekaiKanchoProject
//	By �Q�������ٖ剺��
//----------------------------------

#include "DxLib.h"
#include "main.h"
#include "keycheck.h"

// �ϐ��錾
bool keyTrgUp[KEY_MAX];
bool keyTrgDown[KEY_MAX];
bool keyNow[KEY_MAX];
bool keyOld[KEY_MAX];

bool mouseTrgUp;
bool mouseTrgDown;
bool mouseNow;
bool mouseOld;

XY mousePos;


// �L�[���̏�����
void KeyInit(void)
{
	// �L�[���̏�����
	for (int keyID = 0; keyID < KEY_MAX; keyID++)
	{
		keyTrgUp[keyID] = false;
		keyTrgDown[keyID] = false;
		keyNow[keyID] = false;
		keyOld[keyID] = false;
	}

	// �}�E�X���̏�����
	mouseTrgUp = false;
	mouseTrgDown = false;
	mouseNow = false;
	mouseOld = false;
}

// �L�[�̏�Ԃ��`�F�b�N
void KeyCheck(void)
{
	//�@1�t���[���O�̏�Ԃ��`�F�b�N
	for (int keyID = 0; keyID < KEY_MAX; keyID++)
	{
		keyOld[keyID] = keyNow[keyID];
		//keyTrgUp[keyID] = true;
	}

	// ���̃t���[���̏�Ԃ�ۑ�
	keyNow[KEY_SPACE] = (bool)CheckHitKey(KEY_INPUT_SPACE);
	keyNow[KEY_DOWN] = (bool)CheckHitKey(KEY_INPUT_DOWN);
	keyNow[KEY_RIGHT] = (bool)CheckHitKey(KEY_INPUT_RIGHT);
	keyNow[KEY_LEFT] = (bool)CheckHitKey(KEY_INPUT_LEFT);
	keyNow[KEY_UP] = (bool)CheckHitKey(KEY_INPUT_UP);
	keyNow[KEY_E] = (bool)CheckHitKey(KEY_INPUT_E);
	keyNow[KEY_R] = (bool)CheckHitKey(KEY_INPUT_R);
	keyNow[KEY_MENU] = (bool)CheckHitKey(KEY_INPUT_M);
	keyNow[KEY_NORMAL_ATTACK] = (bool)CheckHitKey(KEY_INPUT_LCONTROL);
	keyNow[KEY_SPECIAL_ATTACK] = (bool)CheckHitKey(KEY_INPUT_Z);

	// �g���K�[����
	for (int keyID = 0; keyID < KEY_MAX; keyID++)
	{
		// �g���K�[�̏��̏�����
		keyTrgDown[keyID] = false;
		keyTrgUp[keyID] = false;

		// �g���K�[���̎擾
		if (!keyOld[keyID] && keyNow[keyID])
		{
			keyTrgUp[keyID] = true;
		}
	}

	// 1�t���[���O�̃}�E�X�̏��
	mouseOld = mouseNow;

	// ���̃t���[���̏�Ԃ�ۑ�
	mouseNow = (bool)GetMouseInput();

	// �g���K�[������
	mouseTrgDown = false;
	mouseTrgUp = false;

	//�@�g���K�[����
	if (!mouseOld && mouseNow)
	{
		mouseTrgUp = true;
	}

	// �}�E�X�J�[�\���̍��W���擾
	GetMousePoint(&mousePos.x, &mousePos.y);
}

// �}�E�X�̍��W�̎擾�p
XY GetMousePos(void)
{
	return mousePos;
}