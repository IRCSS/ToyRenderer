#include "AudioAssembly.h"
#include "log/Log.h"
#include "system/File.h"
#include <filesystem>
#include "vendor/soloud/soloud_wav.h"
#include "Audio/SoLoudCommonUtility.h"
#include "Audio/AudioClip .h"
namespace ToyRenderer {


	AudioClip * LoadWavAudioSource(const char* path, const char* fileName) {

		SoLoud::Wav* audioSourceWavFormat = new SoLoud::Wav();
		SoLoud::result            results = audioSourceWavFormat->load(path);
		if (results != 0) {
			ENGINE_LOG_WARN("{}: attempted to load file {} at path: {}", soLoudErrorToString(results), fileName, path);
			return nullptr;
		}

		return new AudioClip((SoLoud::AudioSource*)audioSourceWavFormat);
	}



	AudioAssembly::AudioAssembly()
	{
		std::string executablePath = std::string();
		TOYRENDERER_EXEPATH(executablePath);

		std::string filepath = executablePath + "/res/audio";
		TOYRENDERER_STYLE_PATH(filepath);

		for (const auto & entry : std::filesystem::directory_iterator(filepath)) {
			std::string fileFormat = entry.path().extension().string();
			std::string fileName   = entry.path().filename().string();

			AudioClip* audioSource = nullptr;

			if (fileFormat.compare(".wav") == 0) {
				audioSource = LoadWavAudioSource(entry.path().string().c_str(), fileName.c_str());
			}

			if (audioSource == nullptr) {
				ENGINE_LOG_INFO("Unsopported Audio format in the engine audio resources folder. File: {}", entry.path().string().c_str());
				continue;
			}

			m_LoadedAudioSource[fileName] = audioSource;
				
		}

	}
	AudioAssembly::~AudioAssembly()
	{
		// Iterate over an unordered_map using range based for loop
		for (std::pair<std::string, AudioClip*> element : m_LoadedAudioSource)
		{
			delete element.second;
		}
		m_LoadedAudioSource.clear();
	}

	AudioClip* AudioAssembly::GetAudioClipWitname(const char * AudioSourceTagName)
	{

		if (m_LoadedAudioSource.find(AudioSourceTagName) != m_LoadedAudioSource.end()) return m_LoadedAudioSource[AudioSourceTagName];

		ENGINE_LOG_WARN("AudioAssembly: Attempted to access the file {}, however the AudioAssembly hasnt loaded such a file. ", AudioSourceTagName);
		return nullptr;
	}
}