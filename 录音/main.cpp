#include "SoundAPI.h"

int main()
{
	HRecord r = HRecord();
	std::cout << "Init Record";
	r.InitFile("Export.sound");
	std::cout << "\nInit Record Save File";
	std::cout << "\nStart Record";
	int i = 10;
	while (i--)
	{
		r.WriteInFile(r.Record());
		std::cout << "\nRecording... " << 10 - i << "s";
	}
	r.CloseFile();
	r.~HRecord();
}