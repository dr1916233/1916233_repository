//----------------------------------
//	IsekaiKanchoProject
//	By �Q�������ٖ剺��
//----------------------------------

//#pragma once//----------------------------------

// �v���g�^�C�v�錾
void SceneChange(SCENE_ID sceneID, int brightCnt, bool fade);	// �V�[���̃t�F�[�h�C��/�A�E�g����(SCENE_ID �V�[��ID, int 1�t���[�����Ƃ̉�����)
void EffectInit(void);

// extern�錾
extern SCENE_ID scnID;
extern bool FadeOutFlag;
extern bool FadeInFlag;
extern bool pauseFlag;
extern bool gameFadeOutFlag;