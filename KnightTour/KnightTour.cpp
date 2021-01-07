#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <assert.h>
using namespace std;
#define		BD_WIDTH		6
#define		BD_HEIGHT		6
#define		BD_SIZE			(BD_WIDTH*BD_HEIGHT)
#define		ARY_WIDTH		(BD_WIDTH+4)
#define		ARY_HEIGHT		(BD_HEIGHT+4)
#define		ARY_SIZE		(ARY_WIDTH*ARY_HEIGHT)
#define		WALL			0xff
typedef unsigned char uchar;
typedef const int cint;
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
inline int xyToIX(cint ARY_WD, int x, int y) {
	//assert(x >= 0 && y >= 0);
	return (x+2) + (y+2) * ARY_WD;
}
void print(vector<uchar>& bd, cint WD, cint HT) {
	for (int y = 0; y < HT; ++y) {
		for (int x = 0; x < WD; ++x) {
			auto t = to_string((int)bd[xyToIX(WD+4, x, y)]);
			if( t.size() < 2 ) t = ' ' + t;
			cout << t << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}
void printAll(vector<uchar>& bd, cint WD, cint HT) {
	cint ARY_WD = WD + 4;
	cint ARY_HT = HT + 4;
	int ix = 0;
	for (int y = 0; y < ARY_HT; ++y) {
		for (int x = 0; x < ARY_WD; ++x) {
			auto t = to_string((int)bd[ix++]);
			if (t.size() < 3) t = string(3 - t.size(), ' ') + t;
			cout << t << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}
void KnightTour(vector<uchar>& bd, cint ARY_WD, cint BD_SZ, int n, int x, int y) {
#if	0
	if( x < 0 || y < 0 ) {
		printAll();
		assert(x >= 0 && y >= 0);
	}
#endif
	bd[xyToIX(ARY_WD, x, y)] = n;
#if	0
	cout << n << ":\n";
	cint WD = ARY_WD - 4;
	cint HT = bd.size() / ARY_WD - 4;
	//print(bd, WD, HT);
	printAll(bd, WD, HT);
#endif
	if( x == 1 && y == 2 ) {
		if( n == BD_SZ ) {	//	found!
			++g_count;
			if (g_count % 100 == 0) cout << ".";
			//cout << g_count << ":\n";
			//print();
		} else if( n != 2 ) {
			bd[xyToIX(ARY_WD, x, y)] = 0;
			return;
		}
	}
	if( bd[xyToIX(ARY_WD, x-1, y-2)] == 0 )
		KnightTour(bd, ARY_WD, BD_SZ, n+1, x-1, y-2);
	if( bd[xyToIX(ARY_WD, x+1, y-2)] == 0 )
		KnightTour(bd, ARY_WD, BD_SZ, n+1, x+1, y-2);
	if( bd[xyToIX(ARY_WD, x-2, y-1)] == 0 )
		KnightTour(bd, ARY_WD, BD_SZ, n+1, x-2, y-1);
	if( bd[xyToIX(ARY_WD, x+2, y-1)] == 0 )
		KnightTour(bd, ARY_WD, BD_SZ, n+1, x+2, y-1);
	if( bd[xyToIX(ARY_WD, x-2, y+1)] == 0 )
		KnightTour(bd, ARY_WD, BD_SZ, n+1, x-2, y+1);
	if( bd[xyToIX(ARY_WD, x+2, y+1)] == 0 )
		KnightTour(bd, ARY_WD, BD_SZ, n+1, x+2, y+1);
	if( bd[xyToIX(ARY_WD, x-1, y+2)] == 0 )
		KnightTour(bd, ARY_WD, BD_SZ, n+1, x-1, y+2);
	if( bd[xyToIX(ARY_WD, x+1, y+2)] == 0 )
		KnightTour(bd, ARY_WD, BD_SZ, n+1, x+1, y+2);
	bd[xyToIX(ARY_WD, x, y)] = 0;
}
int countNightToor(cint WD, cint HT) {
	cint BD_SZ = WD * HT;
	cint ARY_WD = WD + 4;
	cint ARY_HT = HT + 4;
	cint ARY_SZ = ARY_WD * ARY_HT;
	vector<uchar> bd(ARY_SZ, WALL);
	for (int y = 0; y < HT; ++y) {
		for (int x = 0; x < WD; ++x) {
			bd[xyToIX(ARY_WD, x, y)] = 0;
		}
	}
	g_count = 0;
	bd[xyToIX(ARY_WD, 0, 0)] = 1;		//	左上隅から開始
	KnightTour(bd, ARY_WD, BD_SZ, 2, 2, 1);		//	最初は (2, 1) に移動
	return g_count;
}
int main()
{
	cout << countNightToor(10, 3) << "\n";
	cout << countNightToor(6, 5) << "\n";
	cout << countNightToor(6, 6) << "\n";
#if	0
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
#endif
    std::cout << "\nOK!\n";
}

