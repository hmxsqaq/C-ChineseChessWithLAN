#include <easyx.h>
#include <iostream>
#include <graphics.h>
#include "game.h"
#include "MapMethods.h"
#include <string>
#define GRIDWIDTH 41


Grid map[10][9];
IMAGE redChessPieceImages[9];
IMAGE blackChessPieceImages[9];
IMAGE chessBoard;
Grid* theSelectedGrid;
Grid* targetGrid;
bool turn;
IMAGE chessFrame;
SelectState state = SelectChess;
IMAGE redWin;
IMAGE blackWin;
//bool gameIsOver;
//bool red

void LoadGridImage()
{
	loadimage(&redWin, "Resources/redWin.png");
	loadimage(&blackWin, "Resources/blackWin.png");

	loadimage(&chessBoard, "Resources/chessBoard.png");
	loadimage(&chessFrame, "Resources/ChessFrame.png");

	//loadimage(redChessPieceImages+0, "Resources/RP.GIF");
	loadimage(redChessPieceImages + 1, "Resources/RedChessPiece1.GIF");
	loadimage(redChessPieceImages + 2, "Resources/RedChessPiece2.GIF");
	loadimage(redChessPieceImages + 3, "Resources/RedChessPiece3.GIF");
	loadimage(redChessPieceImages + 4, "Resources/RedChessPiece4.GIF");
	loadimage(redChessPieceImages + 5, "Resources/RedChessPiece5.GIF");
	loadimage(redChessPieceImages + 6, "Resources/RedChessPiece6.GIF");
	loadimage(redChessPieceImages + 7, "Resources/RedChessPiece7.GIF");
	loadimage(redChessPieceImages + 8, "Resources/RedChessPiece0.GIF");

	//loadimage(blackChessPieceImages + 0, "Resources/BlackChessPiece0.GIF");
	loadimage(blackChessPieceImages + 1, "Resources/BlackChessPiece1.GIF");
	loadimage(blackChessPieceImages + 2, "Resources/BlackChessPiece2.GIF");
	loadimage(blackChessPieceImages + 3, "Resources/BlackChessPiece3.GIF");
	loadimage(blackChessPieceImages + 4, "Resources/BlackChessPiece4.GIF");
	loadimage(blackChessPieceImages + 5, "Resources/BlackChessPiece5.GIF");
	loadimage(blackChessPieceImages + 6, "Resources/BlackChessPiece6.GIF");
	loadimage(blackChessPieceImages + 7, "Resources/BlackChessPiece7.GIF");
	loadimage(blackChessPieceImages + 8, "Resources/BlackChessPiece0.GIF");
}


//0-空,1-兵,2-炮,3-车,4-马,5-相,6-士,7-将
void InitMap()
{
	int intMap[10][9] =
	{
		3,4,5,6,7,6,5,4,3,
		0,0,0,0,0,0,0,0,0,
		0,2,0,0,0,0,0,2,0,
		1,0,1,0,1,0,1,0,1,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		1,0,1,0,1,0,1,0,1,
		0,2,0,0,0,0,0,2,0,
		0,0,0,0,0,0,0,0,0,
		3,4,5,6,7,6,5,4,3,
	};

	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 9; x++)
		{
			Grid newGrid;
			newGrid.Id = intMap[y][x];
			newGrid.x = x;
			newGrid.y = y;
			newGrid.IsRed = y >= 5;
			map[y][x] = newGrid;
		}
	}
}


void drawAlpha(IMAGE* picture, int  picture_x, int picture_y) //x为载入图片的X坐标，y为Y坐标
{
	// 变量初始化
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()函数，用于获取绘图设备的显存指针，EASYX自带  // NOLINT(clang-diagnostic-invalid-utf8)
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //获取picture的显存指针  // NOLINT(clang-diagnostic-invalid-utf8)
	int picture_width = picture->getwidth(); //获取picture的宽度，EASYX自带
	int picture_height = picture->getheight(); //获取picture的高度，EASYX自带
	int graphWidth = getwidth();       //获取绘图区的宽度，EASYX自带
	int graphHeight = getheight();     //获取绘图区的高度，EASYX自带
	int dstX = 0;    //在显存里像素的角标

	// 实现透明贴图 公式： Cp=αp*FP+(1-αp)*BP ， 贝叶斯定理来进行点颜色的概率计算
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //在显存里像素的角标
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA是透明度  // NOLINT(clang-diagnostic-invalid-utf8)
			int sr = ((src[srcX] & 0xff0000) >> 16); //获取RGB里的R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + picture_x) + (iy + picture_y) * graphWidth; //在显存里像素的角标
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //公式： Cp=αp*FP+(1-αp)*BP  ； αp=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //αp=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //αp=sa/255 , FP=sb , BP=db
			}
		}
	}
}

void PrintMap()
{
	putimage(0, 0, &chessBoard);
	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 9; x++)
		{
			//putimage(x * 10, y * 10, map[y][x].isRed ? &redChessPieceImages[map[y][x].Id] : &blackChessPieceImages[map[y][x].Id]);
			drawAlpha(map[y][x].IsRed ? &redChessPieceImages[map[y][x].Id] : &blackChessPieceImages[map[y][x].Id], x * GRIDWIDTH, y * GRIDWIDTH);
		}
	}
	if (theSelectedGrid != nullptr)
		drawAlpha(&chessFrame, theSelectedGrid->x * GRIDWIDTH, theSelectedGrid->y * GRIDWIDTH);

}

void InitGame()
{
	InitMap();
	initgraph(377, 417);
	putimage(0, 0, &chessBoard);
	PrintMap();
}

void WinOrLoseCheck(int id, bool isRed);

std::string SelectChessPiece()
{
	MOUSEMSG m = GetMouseMsg();
	while (true)
	{
		switch (state)
		{
		case SelectChess:
			while (true)
			{
				std::cout << "走出个虎虎生风" << std::endl;
				while (!m.mkLButton || theSelectedGrid == nullptr || theSelectedGrid->Id == 0)
				{
					m = GetMouseMsg();
					theSelectedGrid = &map[m.y / GRIDWIDTH][m.x / GRIDWIDTH];
				}
				if (theSelectedGrid->Id != 0)
				{
					PrintMap();
					state = PutChess;
					break;
				}
			}
			break;
		case PutChess:
			while (true)
			{
				std::cout << "走出个恍如隔世" << std::endl;
				m = GetMouseMsg();
				if (m.mkLButton)
				{
					targetGrid = &map[m.y / GRIDWIDTH][m.x / GRIDWIDTH];
					if (theSelectedGrid != nullptr && CanMoveToTarget(map, *theSelectedGrid, targetGrid->x, targetGrid->y))
					{
						int id = targetGrid->Id;
						bool isRed = targetGrid->IsRed;
						ApplyMove(*theSelectedGrid, *targetGrid);
						Grid* selectGrid = theSelectedGrid;
						theSelectedGrid = nullptr;
						PrintMap();
						WinOrLoseCheck(id, isRed);
						return OutputInformation(*selectGrid, *targetGrid);
					}
					theSelectedGrid = nullptr;
					PrintMap();
					state = SelectChess;
					break;
				}
				else if (m.mkRButton)
				{
					theSelectedGrid = nullptr;
					PrintMap();
					state = SelectChess;
					break;
				}
			}
			break;
		}
	}

}

void InputInformationAndMoveChess(std::string information)
{
	int currentX = (int)information[0] - '0';
	int currentY = (int)information[1] - '0';
	int targetX = (int)information[2] - '0';
	int targetY = (int)information[3] - '0';

	std::cout << currentX << currentY << targetX << targetY << std::endl;
	int id = map[targetY][targetX].Id;
	bool isRed = map[targetY][targetX].IsRed;
	ApplyMove(map[currentY][currentX], map[targetY][targetX]);
	theSelectedGrid = nullptr;
	PrintMap();
	WinOrLoseCheck(id, isRed);
}

std::string OutputInformation(Grid& current, Grid& target)
{
	std::cout << std::to_string(current.x) + std::to_string(current.y) + std::to_string(target.x) + std::to_string(target.y) << std::endl;
	return std::to_string(current.x) + std::to_string(current.y) + std::to_string(target.x) + std::to_string(target.y);
}

void WinOrLoseCheck(int id, bool isRed)
{
	if (id == 7)
	{
		if (isRed)
		{
			putimage(0, 0, &blackWin);
		}
		else
		{
			putimage(0, 0, &redWin);
		}
	}
}
