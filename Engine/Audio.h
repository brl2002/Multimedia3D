#include "Advanced2D.h"

#ifndef _AUDIO_H
#define _AUDIO_H 1

namespace Advanced2D {


	class Sample
	{
	private:
		std::string name;
	
	public:
		#ifndef _NOAUDIO
		FMOD_SOUND	*sample;
		FMOD_CHANNEL *channel;
		#endif
		
	public:
		Sample(void);
		~Sample(void);
		std::string getName() { return name; }
		void setName(std::string value) { name = value; }
	};
	
	class Audio
	{
	private:
		#ifndef _NOAUDIO
		FMOD_SYSTEM *system;
		#endif
		typedef std::vector<Sample*> Samples;
		typedef std::vector<Sample*>::iterator Iterator;
		Samples samples;
	
	public:
		Audio();
		~Audio();
		#ifndef _NOAUDIO
		FMOD_SYSTEM* getSystem() { return system; }
		#endif
		
		bool Init();
		void Update(); //must be called once per frame
		bool Load(std::string filename, std::string name);
		Sample* Load(std::string filename);
		bool Play(std::string name);
		bool Play(Sample *sample);
		void Stop(std::string name);
		void StopAll();
		void StopAllExcept(std::string name);
		
		bool IsPlaying(std::string name);
		bool SampleExists(std::string name);
		Sample *FindSample(std::string name);
		
	};



};

#endif
