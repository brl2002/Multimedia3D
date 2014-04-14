#include "Advanced2D.h"

#ifndef _VIDEO_H
#define _VIDEO_H 1

namespace Advanced2D {

	class Video
	{
	private:
		HWND window; 
		IGraphBuilder *pGraph;
		IMediaControl *pControl;
		IMediaEventEx *pEvent;
		IVideoWindow  *pVideoWindow;
		IMediaPosition *pPosition;
		bool bPlaying;

	public:
		Video(HWND hwnd, std::wstring movieFile);
		~Video(void);
	
		void stop();
		void pause();
		void start();
		void wait();
		bool handleGraphNotifyEvent();
	};

};

#endif
