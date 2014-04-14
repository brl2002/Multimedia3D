#include "fmod.hpp"
#include "common.h"

#ifndef _AUDIO_H
#define _AUDIO_H 1

namespace Advanced2D {

    class Sample
    {
    private:
        std::string name;
    
    public:
		FMOD::Sound    *sound;
		FMOD::Channel *channel;
        
    public:
        Sample(void);
        ~Sample(void);
        std::string getName() { return name; }
        void setName(std::string value) { name = value; }
    };
    
    class Audio
    {
    private:
		FMOD::System *system;
        typedef std::vector<Sample*> Samples;
        typedef std::vector<Sample*>::iterator Iterator;
        Samples samples;
    
    public:
        Audio();
        ~Audio();
		FMOD::System* getSystem() { return system; }
        
        bool Init();
        void Update(); //must be called once per frame
        bool Load(std::string filename, std::string name);
        Sample* Load(std::string filename);
        bool Play(std::string name);
        bool Play(Sample *sample);
        void Stop(std::string name);
		void Stop(Sample *sample);
        void StopAll();
        void StopAllExcept(std::string name);
        
		void Release();

        bool IsPlaying(std::string name);
        bool SampleExists(std::string name);
        Sample *FindSample(std::string name);
        
    };

};

#endif
