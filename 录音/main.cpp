#include "SoundAPI.h"

int main()
{
	// ¼��
	/**HRecord r = HRecord();
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
	**/

	// ����
	/*HPlay p = HPlay();
	p.InitFile("Export.sound");
	while (p.HaveLoop())
	{
		p.Play(p.ReadFile());
		p.ReadFileEnd();
	}
	p.CloseFile();
	p.~HPlay();*/

	// ��¼�Ʊ߲���
	HRecord r;
	HPlay p;
	while (true)
	{
		p.Play((LPSTR)r.Record(10, 1024), r.recordSize());
	}
}