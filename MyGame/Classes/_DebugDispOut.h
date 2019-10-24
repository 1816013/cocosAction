#pragma once
#ifdef _DEBUG
#include <Windows.h>
#include <memory>
#include <tuple>
#include <chrono>	// 精度は1msぐらい

// ｽｸﾘｰﾝ設定
#define _dbgStartDrawDebug() _DebugDispOut::GetInstance().StartDrawDebug()
#define _dbgAddDrawDebug() _DebugDispOut::GetInstance().AddDrawDebug()
#define _dbgSetAlpha(alpha) _DebugDispOut::GetInstance().SetAlpha(alpha)
#define _dbgSetUp(alpha) _DebugDispOut::GetInstance().SetUp(alpha)

// DxLib関数ﾗｯﾌﾟ
#define _dbgDrawLine(fmt, ...) _DebugDispOut::GetInstance().DrawLine(fmt,  __VA_ARGS__)
#define _dbgDrawGraph(fmt, ...) _DebugDispOut::GetInstance().DrawGraph(fmt,  __VA_ARGS__)
#define _dbgDrawBox(fmt, ...) _DebugDispOut::GetInstance().DrawBox(fmt,  __VA_ARGS__)
#define _dbgDrawCircle(fmt, ...) _DebugDispOut::GetInstance().DrawCircle(fmt,  __VA_ARGS__)
#define _dbgDrawTriangle(fmt, ...) _DebugDispOut::GetInstance().DrawTriangle(fmt,  __VA_ARGS__)
#define _dbgDrawPixel(fmt, ...) _DebugDispOut::GetInstance().DrawPixel(fmt,  __VA_ARGS__)
//#define _TdbgDrawFormatString(fmt, ...) _DebugDispOut::GetInstance().DrawFormatString(fmt,  __VA_ARGS__)	
#define _dbgDrawFormatString(fmt, ...) _DebugDispOut::GetInstance().SetScreen();\
										DxLib::DrawFormatString(fmt, __VA_ARGS__);\
										_DebugDispOut::GetInstance().RevScreen();

//ｽﾛｰ機能
#define _dbgWaitMode _DebugDispOut::GetInstance().WaitMode()



										
using ChronoSysTime = std::chrono::system_clock::time_point;

class _DebugDispOut
{
public:
	static _DebugDispOut& GetInstance(void)
	{
		return (*s_Instance);
	}
	// DxLibﾗｯﾌﾟ用関数※DxLibのﾘﾌｧﾚﾝｽからとっているのでわからなかったらそれを見ること
	int DrawLine(int x1, int y1, int x2, int y2, unsigned int Color);	// 線
	int DrawGraph(int x, int y, int GrHandle, int TransFlag);	// 画像
	int DrawBox(int x1, int y1, int x2, int y2,unsigned int Color, int FillFlag);	// 箱(正方形)
	int DrawCircle(int x, int y, int r, unsigned int Color, int FillFlag);			// 円
	int DrawTriangle(int x1, int y1, int x2, int y2,int x3, int y3, unsigned int Color, int FillFlag);	// 三角
	int DrawPixel(int x, int y, unsigned int Color);	// 点
	int DrawString(int x, int y, char *String, unsigned int Color);	// 文字
	int DrawFormatString(int x, int y, unsigned int Color, const char *FormatString, ...);	// 文字(%d などを使う可変)

	void WaitMode(void);		// ｽﾛｰ機能
	
	// ｽｸﾘｰﾝ設定
	bool StartDrawDebug(void);	// ﾃﾞﾊﾞｯｸﾞｽｸﾘｰﾝの初期化
	bool AddDrawDebug(void);	// ﾃﾞﾊﾞｯｸﾞｽｸﾘｰﾝの情報をdrawQueに追加
	bool SetAlpha(int alpha);	// 透明度の設定
	bool SetUp(int alpha);		// ﾃﾞﾊﾞｯｸﾞｽｸﾘｰﾝの作成

	void SetScreen(void);		// 今のｽｸﾘｰﾝを記録してﾃﾞﾊﾞｯｸﾞｽｸﾘｰﾝに変更
	void RevScreen(void);		// 記録していたｽｸﾘｰﾝに移動※記録していなかったら呼び出すと不定値が入っていて危険



private:
	struct _DebugDispOutDeleter		// ﾃﾞﾘｰﾀｰ
	{
		void operator()(_DebugDispOut* _debugContOut) const
		{
			delete _debugContOut;
		}
	};
	_DebugDispOut();
	~_DebugDispOut();

	FILE* _debugFp = nullptr;
	//static _DebugConOut *s_Instance;
	static std::unique_ptr<_DebugDispOut, _DebugDispOutDeleter> s_Instance;

	// ﾃﾞﾊﾞｯｸﾞｽｸﾘｰﾝ
	int _alpha;			// 透明度
	int _dbgScreen;		// ﾃﾞﾊﾞｯｸﾞ用の表示をするｽｸﾘｰﾝ
	bool _dbgFlag;		// true: ﾃﾞﾊﾞｯｸﾞ系の表示　false:非表示
	int ghBefor;		// 前のｽｸﾘｰﾝ

	// ｽﾛｰ処理系
	ChronoSysTime _startTime;	// 計測はじめold情報
	ChronoSysTime _endTime;		// 計測終わりnew情報
	double _waitTime;			// 待機時間
};
#else
// Releseのときは空読みする
#define _dbgStartDrawDebug()
#define _dbgAddDrawDebug() 
#define _dbgSetAlpha(alpha) 
#define _dbgSetUp(alpha)
#define _dbgDrawLine(fmt, ...)
#define _dbgDrawGraph(fmt, ...)
#define _dbgDrawBox(fmt, ...)
#define _dbgDrawCircle(fmt, ...)
#define _dbgDrawTriangle(fmt, ...)
#define _dbgDrawPixel(fmt, ...)
//#define _dbgDrawFormatString(fmt, ...)
#define _dbgDrawFormatString(fmt, ...)
#endif	// _DEBUG

