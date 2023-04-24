#pragma once
#if _WIN32
#include <Windows.h>
#include <iostream>

#pragma comment (lib, "winmm.lib")

class HRecord
{
public:
	HRecord()
	{
		waveForm.wFormatTag = WAVE_FORMAT_PCM;
		waveForm.nSamplesPerSec = 8000; // 每秒采样
		waveForm.wBitsPerSample = 16;
		waveForm.nChannels = 1;
		waveForm.nAvgBytesPerSec = 16000;
		waveForm.nBlockAlign = 2;
		waveForm.cbSize = 0;

		wait = CreateEvent(NULL, 0, 0, NULL);

		waveInOpen(
			&hWaveIn,
			WAVE_MAPPER,
			&waveForm,
			(DWORD_PTR)wait,
			0L,
			CALLBACK_EVENT
		);

	}

	~HRecord()
	{
		waveInClose(hWaveIn);
	}

	void Resize(size_t newSize)
	{
		bufSize = newSize;
	}

	// 录制1秒钟
	BYTE* Record()
	{
		BYTE* pBuffer1 = new BYTE[bufSize];
		wHdr1.lpData = (LPSTR)pBuffer1;
		wHdr1.dwBufferLength = bufSize;
		wHdr1.dwBytesRecorded = 0;
		wHdr1.dwFlags = 0;
		wHdr1.dwLoops = 1;

		// 初始化设备
		waveInPrepareHeader(hWaveIn, &wHdr1, sizeof(WAVEHDR));
		waveInAddBuffer(hWaveIn, &wHdr1, sizeof(WAVEHDR));

		// 开始录制
		waveInStart(hWaveIn);
		Sleep(1000);
		// 结束录制
		waveInReset(hWaveIn);

		return pBuffer1;
	}

	size_t recordSize()
	{
		return wHdr1.dwBytesRecorded;
	}

	void InitFile(const char* Path)
	{
		fopen_s(&file, Path, "wb");
	}

	void WriteInFile(BYTE* record)
	{
		fwrite(record, 1, wHdr1.dwBytesRecorded, file);
		delete record;
	}

	int CloseFile()
	{
		waveInClose(hWaveIn);
		return fclose(file);
	}

private:
	HWAVEIN hWaveIn; // 麦克风设备
	WAVEFORMATEX waveForm; // 音频格式
	BYTE* pBuffer1;
	WAVEHDR wHdr1;
	HANDLE wait;
	DWORD bufSize = 1024 * 1024;
	FILE* file;

};
#endif // _WIN32