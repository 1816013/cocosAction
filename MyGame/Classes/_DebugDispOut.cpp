#ifdef _DEBUG
#include <Windows.h>
#include <DxLib.h>

#include "_DebugDispOut.h"
#include <Scene/SceneMng.h>


std::unique_ptr<_DebugDispOut, _DebugDispOut::_DebugDispOutDeleter> _DebugDispOut::s_Instance(new _DebugDispOut);


int _DebugDispOut::DrawLine(int x1, int y1, int x2, int y2, unsigned int Color)
{
	SetScreen();
	int rtnFlag = DxLib::DrawLine(x1 + lpSceneMng.gameScreenPos.x, 
								  y1 + lpSceneMng.gameScreenPos.y, 
								  x2 + +lpSceneMng.gameScreenPos.x, 
								  y2 + lpSceneMng.gameScreenPos.y,
								  Color);
	RevScreen();
	return rtnFlag;
}

int _DebugDispOut::DrawGraph(int x, int y, int GrHandle, int TransFlag)
{
	SetScreen();
	int rtnFlag = DxLib::DrawGraph(x, y, GrHandle, TransFlag);
	RevScreen();
	return rtnFlag;
}

int _DebugDispOut::DrawBox(int x1, int y1, int x2, int y2, unsigned int Color, int FillFlag)
{
	SetScreen();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
	int rtnFlag = DxLib::DrawBox(x1 + lpSceneMng.gameScreenPos.x, 
								 y1 + lpSceneMng.gameScreenPos.y,
								 x2 + lpSceneMng.gameScreenPos.x,
								 y2 + lpSceneMng.gameScreenPos.y, 
								 Color, FillFlag);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	RevScreen();
	return rtnFlag;
}
int _DebugDispOut::DrawCircle(int x, int y, int r, unsigned int Color, int FillFlag)
{
	SetScreen();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
	int rtnFlag = DxLib::DrawCircle(x + lpSceneMng.gameScreenPos.x,
									y + lpSceneMng.gameScreenPos.y,
									r, Color, FillFlag);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	RevScreen();
	return rtnFlag;
}

int _DebugDispOut::DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, unsigned int Color, int FillFlag)
{
	SetScreen();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
	int rtnFlag = DxLib::DrawTriangle(x1 + lpSceneMng.gameScreenPos.x,
									y1 + lpSceneMng.gameScreenPos.y,
									x2 + +lpSceneMng.gameScreenPos.x,
									y2 + lpSceneMng.gameScreenPos.y, 
									x3 + lpSceneMng.gameScreenPos.x,
									y3 + lpSceneMng.gameScreenPos.y,
									Color, FillFlag);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	RevScreen();
	return rtnFlag;
}

int _DebugDispOut::DrawPixel(int x, int y, unsigned int Color)
{
	SetScreen();
	int rtnFlag = DxLib::DrawPixel(x + lpSceneMng.gameScreenPos.x, y + lpSceneMng.gameScreenPos.y,Color);
	RevScreen();
	return rtnFlag;
}

int _DebugDispOut::DrawString(int x, int y, char * String, unsigned int Color)
{
	SetScreen();
	int rtnFlag = DxLib::DrawString(x, y, String, Color);
	RevScreen();
	return rtnFlag;
}

int _DebugDispOut::DrawFormatString(int x, int y, unsigned int Color,const char* FormatString, ...)
{
	/*SetScreen();
	va_list list;
	va_start(list, FormatString);
	int rtnFlag;
	rtnFlag = DxLib::DrawFormatString(x, y, Color, FormatString, va_arg(list, int), va_arg(list, int));
	va_end(list);
	RevScreen();
	return rtnFlag;*/
	return 0;
}

void _DebugDispOut::WaitMode(void)
{
	if (CheckHitKey(KEY_INPUT_ADD))
	{
		if (CheckHitKey(KEY_INPUT_MULTIPLY))
		{
			_waitTime += 100;
		}
		else
		{
			_waitTime++;
		}
	}

	if (CheckHitKey(KEY_INPUT_SUBTRACT))
	{
		if (CheckHitKey(KEY_INPUT_DIVIDE))
		{
			_waitTime -= 100;
		}
		else
		{
			_waitTime--;
		}
		if (_waitTime < 0.0)
		{
			_waitTime = 0.0;
		}
		
	}
	if (CheckHitKey(KEY_INPUT_END))
	{
		_waitTime = 0.0;
	}
	_startTime = std::chrono::system_clock::now();
	do 
	{
		_endTime = std::chrono::system_clock::now();
		if (ProcessMessage() != 0 || CheckHitKey(KEY_INPUT_ESCAPE) != 0)
		{
			break;
		}
	} while ( std::chrono::duration_cast<std::chrono::milliseconds >(_endTime - _startTime).count() < _waitTime);
}


bool _DebugDispOut::StartDrawDebug(void)
{
	SetScreen();
	ClsDrawScreen();
	RevScreen();
	return true;
}

bool _DebugDispOut::AddDrawDebug(void)
{
	if (CheckHitKey(KEY_INPUT_PGUP))
	{
		_dbgFlag = true;
	}
	if (CheckHitKey(KEY_INPUT_PGDN))
	{
		_dbgFlag = false;
	}
	if (_dbgFlag)
	{
		lpSceneMng.addDrawQue({_dbgScreen, 0, 0});
	}
	WaitMode();
	return _dbgFlag;
}

bool _DebugDispOut::SetAlpha(int alpha)
{
	if (alpha >= 0 && alpha <= 255)
	{
		_alpha = alpha;
	}
	else
	{
		alpha = 0;
	}
	return true;
}

bool _DebugDispOut::SetUp(int alpha)
{
	if (_dbgScreen == -1)
	{
		_dbgScreen = MakeScreen(lpSceneMng.screenSize.x, lpSceneMng.screenSize.y, true);
	}
	SetAlpha(alpha);
	return true;
}

_DebugDispOut::_DebugDispOut()
{
	_dbgScreen = -1;
	_dbgFlag = true;
	_waitTime = 0;
}


_DebugDispOut::~_DebugDispOut()
{
}

void _DebugDispOut::SetScreen(void)
{
	ghBefor = GetDrawScreen();
	SetDrawScreen(_dbgScreen);
}

void _DebugDispOut::RevScreen(void)
{
	SetDrawScreen(ghBefor);
}

#endif	// _DEBUG
