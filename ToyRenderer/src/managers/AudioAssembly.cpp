#include "AudioAssembly.h"
#include "log/Log.h"
#include "system/File.h"
#include <filesystem>
#include "vendor/soloud/soloud_wav.h"
#include "Audio/SoLoudCommonUtility.h"
#include "Audio/AudioClip.h"
namespace ToyRenderer {



	AudioClip * LoadWavAudioSource(const char* path, const char* fileName) {

		SoLoud::Wav* audioSourceWavFormat = new SoLoud::Wav();
		SoLoud::result            results = audioSourceWavFormat->load(path);
		if (results != 0) {
			ENGINE_LOG_WARN("{}: attempted to load file {} at path: {}", soLoudErrorToString(results), fileName, path);
			return nullptr;
		}
		AudioClip* toReturn = new AudioClip(audioSourceWavFormat);
		toReturn->SetName(fileName);
		return toReturn;
	}



	AudioAssembly::AudioAssembly()
	{
		std::string executablePath = std::string();
		TOYRENDERER_EXEPATH(executablePath);

		std::string filepath = executablePath + "/res/engine/audio";
		TOYRENDERER_STYLE_PATH(filepath);

		LoadAllAudiosInFolder(filepath);

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
	bool AudioAssembly::LoadAudioInPath(const std::string & path)
	{
		std::filesystem::path filePath = std::filesystem::path(path);

		if (!std::filesystem::exists(filePath)) {
			ENGINE_LOG_WARN("Attempted to load the file {}, however the file was not found.", filePath.string());
			return false;
		}


		std::string fileFormat = filePath.extension().string();
		std::string fileName   = filePath.filename().string();

		AudioClip* audioSource = nullptr;

		if (fileFormat.compare(".wav") == 0) {
			audioSource = LoadWavAudioSource(filePath.string().c_str(), fileName.c_str());
		}

		if (audioSource == nullptr) {
			ENGINE_LOG_INFO("Unsopported Audio format in the engine audio resources folder. File: {}", filePath.string().c_str());
			return false;
		}

		m_LoadedAudioSource[fileName] = audioSource;

		return true;
	}
	bool AudioAssembly::LoadAllAudiosInFolder(const std::string & path)
	{
		bool allSuccesfullyLoaded = true;

		for (const auto & entry : std::filesystem::directory_iterator(path)) {
			
			bool loaded = LoadAudioInPath(entry.path().string());
		
			allSuccesfullyLoaded = (allSuccesfullyLoaded && loaded);
		}

		return allSuccesfullyLoaded;
	}
}