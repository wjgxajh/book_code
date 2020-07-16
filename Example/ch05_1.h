#pragma once
#include <string>
#include<iostream>
using namespace std;
// 5-15 智力拼图问题
const int brow = 6;
const int bcol = 10;
const int flg = 0;
int ans = 0;
typedef unsigned char BYTE;
typedef struct {
	BYTE aa[5][5];
}pp;
pp var[12][8] = {};
int nvar[8] = {};

BYTE pc00[5][5] = { {1, 1, 1}, {1}, {1} };
BYTE pc01[5][5] = { {2, 2}, {2}, {2, 2} };
BYTE pc02[5][5] = { {3, 3}, {3, 3}, {3} };
BYTE pc03[5][5] = { {4, 4}, {4}, {4}, {4} };
BYTE pc04[5][5] = { {5}, {5, 5}, {0, 5}, {0, 5} };
BYTE pc05[5][5] = { {6}, {6, 6}, {6}, {6} };
BYTE pc06[5][5] = { {7, 7, 7}, {0, 7}, {0, 7} };
BYTE pc07[5][5] = { {0, 8}, {8, 8, 8}, {0, 8} };
BYTE pc08[5][5] = { {0, 9}, {9, 9}, {0, 9, 9} };
BYTE pc09[5][5] = { {10, 10,10, 10, 10} };
BYTE pc10[5][5] = { {0, 11, 11}, {11, 11}, {11} };
BYTE pc11[5][5] = { {12, 12}, {0, 12}, {0, 12, 12} };

pp* orig[] = {
	(pp*)pc00,
	(pp*)pc01,
	(pp*)pc02,
	(pp*)pc03,
	(pp*)pc04,
	(pp*)pc05,
	(pp*)pc06,
	(pp*)pc07,
	(pp*)pc08,
	(pp*)pc09,
	(pp*)pc10,
	(pp*)pc11
};
// 给定矩形状态
typedef struct {
	BYTE pos[60]; // 标记矩形中60个方格被覆盖的情况。在矩形方格(row,col)处的覆盖状态存储到pos[k]中，k值计算如下
	BYTE mark[12]; // 标记使用过的图形
}fboard;

int addr(int row, int col) {
	return (row - 1) * bcol + col - 1;
}

// 旋转
void rotp(pp* des, pp* src) {
	memset(des, 0, sizeof(pp));
	for (int x = 4, flag = 0, xp = 0; x >= 0; x--) {
		for (int y = 0; y < 5; y++) {
			des->aa[xp][y] = src->aa[y][x];
			if (src->aa[y][x])
				flag = 1;
		}
		if (flag)
			xp++;
	}
}

// 翻转
void flip(pp* des, pp* src) {
	memset(des, 0, sizeof(pp));
	for (int x = 4, flag = 0, xp = 0; x >= 0; x--) {
		for (int y = 0; y < 5; y++) {
			des->aa[y][xp] = src->aa[y][x];
			if (src->aa[y][x])
				flag = 1;
		}
		if (flag)
			xp++;
	}
}

// 初始化
void init() {
	pp tmp1, tmp2;
	for (int b = 0; b < 12; b++) {
		tmp1 = *orig[b];
		for (int d = 0; d < 5; d++) {
			for (int c = 0; c < 5; c++) {
				if (tmp1.aa[d][c])
					tmp1.aa[d][c] |= 0x10;
			}
		}
		int vc = 0;
		for (int a = 0; a < 8; a++) {
			int exist = 0;
			for (int c = 0; c < vc && !exist; c++) {
				if (memcmp(&var[b][c], &tmp1, sizeof(pp)) == 0) // 对比是否已经存在
					exist = 1;
			}
			if (!exist)
				var[b][vc++] = tmp1;
			// 旋转
			tmp2 = tmp1;
			rotp(&tmp1, &tmp2);
			// 翻转
			if (a == 3) {
				tmp2 = tmp1;
				flip(&tmp1, &tmp2);
			}
		}
		nvar[b] = vc;
	}
}

bool check(pp* tryp, fboard* ff, int px, int py) {
	for (int row = 0; row < 5; row++) {
		for (int col = 0; col < 5; col++) {
			if (tryp->aa[row][col]) {
				int r = row + py, c = col + px;
				if (r > brow || c > bcol || ff->pos[addr(r, c)])
					return 0;
			}
		}
	}
	return 1;
}

void outf(fboard* ff) {
	if (flg) {
		for (int col = 1; col <= bcol; col++) {
			for (int row = 1; row <= brow; row++) {
				int x = ff->pos[addr(row, col)] - 16;
				//cout << x << " ";
				if (x < 10)
					cout << x << " ";
				if (x == 10)
					cout << "a" << " ";
				if (x = 11)
					cout << "b" << " ";
				if (x == 12)
					cout << "c" << " ";
			}
			cout << endl;
		}
	}
	else {
		for (int row = 1; row <= brow; row++) {
			for (int col = 1; col <= bcol; col++) {
				int x = ff->pos[addr(row, col)] - 16;
				//cout << x << " ";
				if (x < 10)cout << x << " ";
				if (x == 10)cout << "a" << " ";
				if (x == 11)cout << "b" << " ";
				if (x == 12)cout << "c" << " ";
			}
			cout << endl;
		}
	}
}

void search(fboard* pre) {
	int npla = 0, frow = 0, fcol = 0;
	fboard ff = *pre;
	if (ans > 0)
		return;
	// 找到左上未被覆盖的方格
	for (int row = 1, found = 0; row <= brow && !found; row++) {
		for (int col = 1; col <= bcol && !found; col++) {
			if (pre->pos[addr(row, col)] == 0) {
				frow = row;
				fcol = col;
				found = 1;
			}
		}
	}
	// 计算已用过的图形数
	for (int pn = 0; pn < 12; pn++)
		if (pre->mark[pn])
			npla++;
	for (int pn = 0; pn < 12; pn++) {
		// 是否已用过
		if (pre->mark[pn])
			continue;
		for (int pv = 0; pv < nvar[pn]; pv++) {
			pp tryp = var[pn][pv];
			int py = frow;
			for (int px = 1; px <= bcol; px++) {
				if (px > fcol)
					break;
				if (check(&tryp, &ff, px, py)) {
					// 用该图形覆盖
					for (int row = 0; row < 5; row++) {
						for (int col = 0; col < 5; col++) {
							ff.pos[addr(row + py, col + px)] |= tryp.aa[row][col];
						}
					}
					ff.mark[pn] = 1;
					if (npla > 10) {
						++ans;
						outf(&ff);
						return;
					}
					else
						search(&ff);
					ff = *pre;
				}
			}
		}
	}
}
