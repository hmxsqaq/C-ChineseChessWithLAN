#include "MapMethods.h"

#include <string>

#include "game.h"

int XCheck(const Grid(&map)[10][9], int x1, int x2, int y)
{
	if (x1 == x2) return -1;
	if (abs(x1 - x2) == 1) return 0;

	int amount = 0;
	if (x1 < x2)
	{
		for (int i = x1 + 1; i < x2; i++)
			if (map[y][i].Id != 0)
				amount++;
	}
	else
	{
		for (int i = x2 + 1; i < x1; i++)
			if (map[y][i].Id != 0)
				amount++;
	}
	return amount;
}

int YCheck(const Grid(&map)[10][9], int x, int y1, int y2)
{
	if (y1 == y2) return -1;
	if (abs(y1 - y2) == 1) return 0;

	int amount = 0;
	if (y1 < y2)
	{
		for (int i = y1 + 1; i < y2; i++)
			if (map[i][x].Id != 0)
				amount++;
	}
	else
	{
		for (int i = y2 + 1; i < y1; i++)
			if (map[i][x].Id != 0)
				amount++;
	}
	return amount;
}

/**
 * \brief �Ϸ��Լ���
 * \param map ��ͼ 
 * \param current ѡ�����ӵĸ���
 * \param targetX Ŀ�����x
 * \param targetY Ŀ�����y
 * \return 
 */
bool CanMoveToTarget(const Grid(& map)[10][9], const Grid& current, const int targetX, int targetY)
{
	if (current.Id == 0) return false; // ѡ��ĸ���Ϊ��
	if (targetX == current.x && targetY == current.y) return false; // Ŀ�����ѡ��ĸ���һ��

	const Grid targetGrid = map[targetY][targetX];
	if (targetGrid.Id != 0 && targetGrid.IsRed == current.IsRed) return false;

	int chessCount; // Ŀ����뵱ǰ��֮��������ӵĸ�������
	switch (current.Id)
	{
	case 1:
		// ��
		if (targetX != current.x)
			return false;

		if (current.IsRed)
			return targetY == current.y - 1;
		return targetY == current.y + 1;

	case 2:
		// ��
		if (current.x == targetX)
			chessCount = YCheck(map, targetX, current.y, targetY);
		else if (current.y == targetY)
			chessCount = XCheck(map, targetX, current.x, targetY);
		else
			return false;

		if (targetGrid.Id == 0)
		{
			if (chessCount == 0) return true;
			return false;
		}
		if (chessCount == 1) return true;
		return false;


	case 3:
		// ��
		if (current.x == targetX)
			chessCount = YCheck(map, targetX, current.y, targetY);
		else if (current.y == targetY)
			chessCount = XCheck(map, targetX, current.x, targetY);
		else 
			return false;

		if (chessCount == 0 || chessCount == 1)
			return true;
		return false;

	case 4:
		// ��
		if (abs(targetX - current.x) + abs(targetY - current.y) == 3)
		{
			// todo: ���
			return true;
		}
		return false;
		
	case 5:
		// ��
		if (abs(targetX - current.x) == 2 && abs(targetY - current.y) == 2)
		{
			// todo: ���
			return true;
		}
		return false;


	case 6:
		// ʿ
		if (current.IsRed)
		{
			if (targetY < 7 || targetX < 3 || targetX > 5)
				return false;
			return abs(targetX - current.x) == 1 && abs(targetY - current.y) == 1;
		}
		if (targetY > 2 || targetX < 3 || targetX > 5)
			return false;
		return abs(targetX - current.x) == 1 && abs(targetY - current.y) == 1;

	case 7:
		// ˧
		{
			if (current.IsRed)
			{
				if (targetY < 7 || targetX < 3 || targetX > 5)
				{
					return false;
				}
				return (abs(targetX - current.x) == 1 && abs(targetY - current.y) == 1) ||
					(abs(targetX - current.x) == 1 && targetY == current.y) ||
					(abs(targetY - current.y) == 1 && targetX == current.x);
			}
			if (targetY > 2 || targetX < 3 || targetX > 5)
			{
				return false;
			}
			return (abs(targetX - current.x) == 1 && abs(targetY - current.y) == 1) || 
				(abs(targetX - current.x) == 1 && targetY == current.y) || 
				(abs(targetY - current.y) == 1 && targetX == current.x);
		}

	case 8:
		// ������
		return (abs(targetX - current.x) == 1 && targetY == current.y) ||
			(abs(targetY - current.y) == 1 && targetX == current.x);

	default: 
		return false;
	}
}



/**
 * \brief �ƶ�����
 * \param current ѡ�����Ӹ���
 * \param target Ŀ�����
 */
void ApplyMove(Grid& current, Grid& target)
{
	target.Id = current.Id;
	target.IsRed = current.IsRed;
	current.Id = 0;
	
}



