#pragma once
void middlse(int& tomiddle, int secondparm) {
	tomiddle += secondparm;
	tomiddle -= (tomiddle % 2);
	tomiddle /= 2;
}
class dataversion {
public:
	int x{ 0 };
	int y{ 0 };
	int time{ 0 };
};
std::vector<dataversion> datasstore;
enum class workstate { movemouse, gettingdata, nulls };
workstate workstateof{ workstate::movemouse };
workstate prevworkstateof{ workstate::nulls };
bool stopsss{ false };
int collectdata(HWND* datas, bool* stop) {
	int returncode = 0;
	while (!*stop) {
		POINT p;
		dataversion old;
		if (GetCursorPos(&p))
		{
			//cursor position now in p.x and p.y
			if (ScreenToClient(*datas, &p))
			{
				//p.x and p.y are now relative to hwnd's client area
				if ((int)p.x != old.x || (int)p.y != old.y) {
					dataversion toadd;
					toadd.time = (int)time(NULL);
					toadd.x = p.x;
					toadd.y = p.y;
					middlse(returncode, toadd.x * toadd.y * toadd.time);
					datasstore.push_back(toadd);
					old = toadd;
				}
			}
		}
	}
	return returncode;
}
std::future<int> fut;
