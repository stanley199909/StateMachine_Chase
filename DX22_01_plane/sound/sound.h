#pragma once

#include <xaudio2.h>

// サウンドファイル
typedef enum
{
	//BGM
	SOUND_LABEL_BGMTitleScene,		// BGM
	SOUND_LABEL_BGMStage1,		// BGM
	SOUND_LABEL_BGMStage2,		// BGM

	//SE
	SOUND_LABEL_SEWarning,		// SE1
	SOUND_LABEL_SEAlarm,		// SE2
	SOUND_LABEL_SEVictory,		// SE3
	SOUND_LABEL_SEDefeat,		// SE4
	SOUND_LABEL_SEDash,			// SE5
	SOUND_LABEL_SECrashed,		// SE6

	SOUND_LABEL_MAX,
} SOUND_LABEL;

class Sound {
private:
	// パラメータ構造体
	typedef struct
	{
		LPCSTR filename;	// 音声ファイルまでのパスを設定
		bool bLoop;			// trueでループ。通常BGMはture、SEはfalse。
	} PARAM;

	PARAM m_param[SOUND_LABEL_MAX] =
	{
		//BGM
		{"assets/BGM/TitleSceneBGM.wav", true},			// ゲームメインBGM（ループさせるのでtrue設定）
		{"assets/BGM/Stage1BGM.wav", true},			// ゲームメインBGM（ループさせるのでtrue設定）
		{"assets/BGM/Stage2BGM.wav", true},			// ゲームメインBGM（ループさせるのでtrue設定）

		//SE
		{"assets/SE/warning.wav", false },
		{"assets/SE/alarm.wav", true},
		{"assets/SE/victory.wav", false},
		{"assets/SE/defeat.wav", false},
		{"assets/SE/dash.wav", false},
		{"assets/SE/crashed.wav", false},


	};

	IXAudio2* m_pXAudio2 = NULL;
	IXAudio2MasteringVoice* m_pMasteringVoice = NULL;
	IXAudio2SourceVoice* m_pSourceVoice[SOUND_LABEL_MAX];
	WAVEFORMATEXTENSIBLE m_wfx[SOUND_LABEL_MAX]; // WAVフォーマット
	XAUDIO2_BUFFER m_buffer[SOUND_LABEL_MAX];
	BYTE* m_DataBuffer[SOUND_LABEL_MAX];

	HRESULT FindChunk(HANDLE, DWORD, DWORD&, DWORD&);
	HRESULT ReadChunkData(HANDLE, void*, DWORD, DWORD);

public:
	// ゲームループ開始前に呼び出すサウンドの初期化処理
	HRESULT Init(void);

	// ゲームループ終了後に呼び出すサウンドの解放処理
	void Uninit(void);

	// 引数で指定したサウンドを再生する
	void Play(SOUND_LABEL label);

	// 引数で指定したサウンドを停止する
	void Stop(SOUND_LABEL label);

	// 引数で指定したサウンドの再生を再開する
	void Resume(SOUND_LABEL label);

};