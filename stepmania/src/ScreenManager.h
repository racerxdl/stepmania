/* ScreenManager - Manager/container for Screens. */

#ifndef ScreenManager_H
#define ScreenManager_H

#include "RageInputDevice.h"
#include "ScreenMessage.h"
#include "InputFilter.h"
#include "GameInput.h"
#include "MenuInput.h"
#include "StyleInput.h"
#include "BitmapText.h"
#include "RageSound.h"

class Screen;
struct Menu;
class ScreenSystemLayer;
class BGAnimation;


typedef Screen* (*CreateScreenFn)(const CString&);

class ScreenManager
{
public:
	// Every screen should register its class at program initialization.
	static void Register( const CString& sClassName, CreateScreenFn pfn );

	
	ScreenManager();
	~ScreenManager();

	// pass these messages along to the current state
	void Update( float fDeltaTime );
	void Draw();
	void Input( const DeviceInput& DeviceI, const InputEventType type, const GameInput &GameI, const MenuInput &MenuI, const StyleInput &StyleI );

	void PrepareScreen( const CString &sScreenName );	// creates and caches screen so that the next call to SetNewScreen for the prep'd screen will be very quick.
	void DeletePreparedScreens();
	
	void SetNewScreen( const CString &sName );
	void AddNewScreenToTop( const CString &sName, ScreenMessage messageSendOnPop );
	void Prompt( ScreenMessage SM_SendWhenDone, const CString &sText, bool bYesNo = false, bool bDefaultAnswer = false, void(*OnYes)(void*) = NULL, void(*OnNo)(void*) = NULL, void* pCallbackData = NULL );
	void TextEntry( ScreenMessage SM_SendWhenDone, CString sQuestion, CString sInitialAnswer, void(*OnOK)(CString sAnswer) = NULL, void(*OnCanel)() = NULL );
	void MiniMenu( Menu* pDef, ScreenMessage SM_SendOnOK, ScreenMessage SM_SendOnCancel = SM_None );
	void PopTopScreen( ScreenMessage SM = SM_None );
	void SystemMessage( const CString &sMessage );
	void SystemMessageNoAnimate( const CString &sMessage );

	void PostMessageToTopScreen( ScreenMessage SM, float fDelay );
	void SendMessageToTopScreen( ScreenMessage SM );

	void ReloadCreditsText();
	void RefreshCreditsMessages();
	void ThemeChanged();

	Screen *GetTopScreen();

public:
	//
	// in draw order first to last
	//
	BGAnimation			*m_pSharedBGA;	// BGA object that's persistent between screens
	void	PlaySharedBackgroundOffCommand();
private:
	vector<Screen*>		m_ScreenStack;	// bottommost to topmost
	ScreenSystemLayer	*m_SystemLayer;

	CString				m_sLastLoadedBackgroundPath;
	CString				m_sDelayedScreen;
	ScreenMessage		m_MessageSendOnPop;
	vector<Screen*>		m_vPreparedScreens;
	vector<Screen*>		m_vScreensToDelete;

	Screen* MakeNewScreen( const CString &sName );
	void SetFromNewScreen( Screen *pNewScreen, bool Stack );
	void ClearScreenStack();
	void EmptyDeleteQueue();
	void LoadDelayedScreen();

	// Keep these sounds always loaded, because they could be 
	// played at any time.  We want to eliminate SOUND->PlayOnce
public:
	void PlayStartSound();
	void PlayCoinSound();
	void PlayInvalidSound();
	void PlayScreenshotSound();
	void PlayBackSound();

private:
	RageSound	m_soundStart;
	RageSound	m_soundCoin;
	RageSound	m_soundInvalid;
	RageSound	m_soundScreenshot;
	RageSound	m_soundBack;
};


extern ScreenManager*	SCREENMAN;	// global and accessable from anywhere in our program

#endif

/*
 * (c) 2001-2003 Chris Danford, Glenn Maynard
 * All rights reserved.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, and/or sell copies of the Software, and to permit persons to
 * whom the Software is furnished to do so, provided that the above
 * copyright notice(s) and this permission notice appear in all copies of
 * the Software and that both the above copyright notice(s) and this
 * permission notice appear in supporting documentation.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF
 * THIRD PARTY RIGHTS. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR HOLDERS
 * INCLUDED IN THIS NOTICE BE LIABLE FOR ANY CLAIM, OR ANY SPECIAL INDIRECT
 * OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
 * OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */
