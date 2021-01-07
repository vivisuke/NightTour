#include <iostream>
#include <string>
#include <chrono>
using namespace std;
#define		BD_WIDTH		6
#define		BD_HEIGHT		6
#define		BD_SIZE			(BD_WIDTH*BD_HEIGHT)
#define		ARY_WIDTH		(BD_WIDTH+4)
#define		ARY_HEIGHT		(BD_HEIGHT+4)
#define		ARY_SIZE		(ARY_WIDTH*ARY_HEIGHT)
#define		WALL			0xff
typedef unsigned char uchar;
int g_count = 0;
uchar g_bd[ARY_SIZE];
inline int xyToIX(int x, int y) { return (x+2) + (y+2) * ARY_WIDTH; }
void print() {
	for (int y = 0; y < BD_HEIGHT; ++y) {
		for (int x = 0; x < BD_WIDTH; ++x) {
			auto t = to_string((int)g_bd[xyToIX(x, y)]);
			if( t.size() < 2 ) t = ' ' + t;
			cout << t << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}
void KnightTour(int n, int x, int y) {
	g_bd[xyToIX(x, y)] = n;
	//cout << n << ":\n";
	//print();
#if	1
	//if( n == 1 ) {
	//	KnightTour(n+1, x+2, y+1);		//	最初は (2, 1) に移動
	//	return;
	//}
	if( x == 1 && y == 2 ) {
		if( n == BD_SIZE ) {	//	found!
			++g_count;
			if (g_count % 100 == 0) cout << ".";
			//cout << g_count << ":\n";
			//print();
		} else if( n != 2 ) {
			g_bd[xyToIX(x, y)] = 0;
			return;
		}
	}
#else
	if( (x == 2 && y == 1) || (x == 1 && y == 2) ) {	//	巡回解
		if( n == BD_SIZE ) {	//	found!
			++g_count;
			cout << g_count << ":\n";
			print();
		} else if( n != 2 ) {
			g_bd[xyToIX(x, y)] = 0;
			return;
		}
	}
#endif
	if( g_bd[xyToIX(x-1, y-2)] == 0 )
		KnightTour(n+1, x-1, y-2);
	if( g_bd[xyToIX(x+1, y-2)] == 0 )
		KnightTour(n+1, x+1, y-2);
	if( g_bd[xyToIX(x-2, y-1)] == 0 )
		KnightTour(n+1, x-2, y-1);
	if( g_bd[xyToIX(x+2, y-1)] == 0 )
		KnightTour(n+1, x+2, y-1);
	if( g_bd[xyToIX(x-2, y+1)] == 0 )
		KnightTour(n+1, x-2, y+1);
	if( g_bd[xyToIX(x+2, y+1)] == 0 )
		KnightTour(n+1, x+2, y+1);
	if( g_bd[xyToIX(x-1, y+2)] == 0 )
		KnightTour(n+1, x-1, y+2);
	if( g_bd[xyToIX(x+1, y+2)] == 0 )
		KnightTour(n+1, x+1, y+2);
	g_bd[xyToIX(x, y)] = 0;
}
int main()
{
	auto start = std::chrono::system_clock::now();      // 計測スタート時刻を保存
	for(auto& x: g_bd) x = WALL;
	for (int y = 0; y < BD_HEIGHT; ++y) {
		for (int x = 0; x < BD_WIDTH; ++x) {
			g_bd[xyToIX(x, y)] = 0;
		}
	}
	g_bd[xyToIX(0, 0)] = 1;		//	左上隅から開始
	KnightTour(2, 2, 1);		//	最初は (2, 1) に移動
	auto end = std::chrono::system_clock::now();       // 計測終了時刻を保存
	auto dur = end - start;        // 要した時間を計算
	auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
	cout << "\ncount = " << g_count << "\n";
	cout << msec << "msec\n";
    std::cout << "\nOK!\n";
}

