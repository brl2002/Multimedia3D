#include "Advanced2D.h"

namespace Advanced2D {

	Video::Video(HWND hwnd, std::wstring movieFile)
		: pGraph(NULL), pControl(NULL), pEvent(NULL), pVideoWindow(NULL), pPosition(NULL), bPlaying(false)
	{
        window = hwnd;

		CoInitialize(NULL);
		CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void **)&pGraph);

		pGraph->QueryInterface(IID_IMediaControl, (void **)&pControl);
		pGraph->QueryInterface(IID_IMediaEvent, (void **)&pEvent);
		pGraph->RenderFile((LPCWSTR)movieFile.c_str(), NULL);

		pGraph->QueryInterface(IID_IVideoWindow, (void**)&pVideoWindow);
		pVideoWindow->put_Owner((OAHWND)window);
		pVideoWindow->put_WindowStyle(WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS);
		RECT rect;
		GetClientRect(window, &rect);
		pVideoWindow->SetWindowPosition(rect.left, rect.top, rect.right, rect.bottom);

		// Set the owner window to receive event notices.
		pGraph->QueryInterface(IID_IMediaEventEx, (void **)&pEvent);
		pEvent->SetNotifyWindow((OAHWND)window, WM_GRAPHNOTIFY, 0);

		pGraph->QueryInterface(IID_IMediaPosition, (void**)&pPosition);
	}

	Video::~Video(void)
	{
		pVideoWindow->put_Visible(OAFALSE);
		pVideoWindow->put_Owner(NULL);
		pControl->Stop();
		wait();
		pControl->Release();
		pEvent->Release();
		pGraph->Release();
		CoUninitialize();
	}

	void Video::stop()
	{
		pControl->Stop();
	}

	void Video::pause()
	{
		pControl->Pause();
	}

	void Video::start()
	{
		pControl->Run();
		bPlaying = true;
	}

	void Video::wait()
	{
		// Wait for completion.
		long evCode;
		pEvent->WaitForCompletion(INFINITE, &evCode);
	}

	bool Video::handleGraphNotifyEvent()
	{
		long evCode, param1, param2;
		HRESULT hr;
		while (hr = pEvent->GetEvent(&evCode, &param1, &param2, 0), SUCCEEDED(hr))
		{ 
			hr = pEvent->FreeEventParams(evCode, param1, param2);
			if ((EC_COMPLETE == evCode) || (EC_USERABORT == evCode))
			{ 
				bPlaying = false;
				stop();
				return false;
			} 
		} 
		return true;
	}
}
