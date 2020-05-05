#include "AudioAssembly.h"
#include "log/Log.h"
#include "system/File.h"
#include <filesystem>
#include "vendor/soloud/soloud_audiosource.h"
#include "vendor/soloud/soloud_wav.h"
#include "Audio/SoLoudCommonUtility.h"
#include "Audio/AudioSource.h"
namespace ToyRenderer {




	ToyRenderer::AudioSource* LoadWavAudioSource(const char* path, const char* fileName) {

		SoLoud::Wav* audioSourceWavFormat = new SoLoud::Wav();
		SoLoud::result            results = audioSourceWavFormat->load(path);
		if (results != 0) {
			ENGINE_LOG_WARN("{}: attempted to load file {} at path: {}", soLoudErrorToString(results), fileName, path);
			return nullptr;
		}

		return new AudioSource((SoLoud::AudioSource*)audioSourceWavFormat);
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

			ToyRenderer::AudioSource* audioSource = nullptr;

			if (fileFormat.compare(".wav")) audioSource = LoadWavAudioSource(entry.path().string().c_str(), fileName.c_str());
		}

	}
	AudioAssembly::~AudioAssembly()
	{
	}
	AudioSource* AudioAssembly::GetAudioSourceWitname(const char * AudioSourceTagName)
	{

		if (m_LoadedAudioSource.find(AudioSourceTagName) != m_LoadedAudioSource.end()) return m_LoadedAudioSource[AudioSourceTagName];

		ENGINE_LOG_WARN("AudioAssembly: Attempted to access the file {}, however the AudioAssembly hasnt loaded such a file. ", AudioSourceTagName);
		return nullptr;
	}
}