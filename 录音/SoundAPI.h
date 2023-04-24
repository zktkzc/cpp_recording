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
		waveForm.nSamplesPerSec = 8000; // ÿ�����
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

	// ¼��1����
	BYTE* Record()
	{
		BYTE* pBuffer1 = new BYTE[bufSize];
		wHdr1.lpData = (LPSTR)pBuffer1;
		wHdr1.dwBufferLength = bufSize;
		wHdr1.dwBytesRecorded = 0;
		wHdr1.dwFlags = 0;
		wHdr1.dwLoops = 1;

		// ��ʼ���豸
		waveInPrepareHeader(hWaveIn, &wHdr1, sizeof(WAVEHDR));
		waveInAddBuffer(hWaveIn, &wHdr1, sizeof(WAVEHDR));

		// ��ʼ¼��
		waveInStart(hWaveIn);
		Sleep(1000);
		// ����¼��
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
	HWAVEIN hWaveIn; // ��˷��豸
	WAVEFORMATEX waveForm; // ��Ƶ��ʽ
	BYTE* pBuffer1;
	WAVEHDR wHdr1;
	HANDLE wait;
	DWORD bufSize = 1024 * 1024;
	FILE* file;

};
#endif // _WIN32