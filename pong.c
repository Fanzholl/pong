#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int painting(int ball[], int firstPlayer[], int secondPlayer[], int scoreFirst, int scoreSecond);
void stepScan(char *step);
void stepCalculation(char step, int firstPlayer[], int secondPlayer[]);
void ballMovement(int ball[], int firstPlayer[], int secondPlayer[], int *scoreFirst, int *scoreSecond);
void score(int *scoreFirst, int *scoreSecond, int side);

int main(void)
{
	srand(time(NULL)); // Инициализация генератора случайных чисел.

	char step = 'h';
	int scoreFirst = 0, scoreSecond = 0;
	int ball[4] = {39, 12, (rand() % 2) ? 1 : -1, (rand() % 2) ? 1 : -1} /* Инициализация мяча: {x, y, скорость по x, скорость по y} */, firstPlayer[2] = {0, 12} /* Инициализация первой каретки (игрока): {x, y}*/, secondPlayer[2] = {79, 12}; /* Инициализация второй каретки (игрока): {x, y}*/

	do
	{
		painting(ball, firstPlayer, secondPlayer, scoreFirst, scoreSecond);		  // Отрисовываем поле (Логика не зависит от него. Это - лишь видимая игроку часть игры).
		stepScan(&step);														  // Получаем ввод хода от игрока и записываем его в память по адресу переменной step.
		stepCalculation(step, firstPlayer, secondPlayer);						  // Вычисляем новые координаты положения кареток, после внесённых изменений.
		ballMovement(ball, firstPlayer, secondPlayer, &scoreFirst, &scoreSecond); // Проводив все необходимые вычисления для движения мяча и его отражения от поверхностей на игровом пространстве.
	} while (1);

	return 0;
}

// Функция отрисовки игрового процесса (Алгоритм вывода данных в терминал).
int painting(int ball[], int firstPlayer[], int secondPlayer[], int scoreFirst, int scoreSecond)
{

	printf("Player 1: %d ", scoreFirst); // Вывод счёта первого игрока.
    for (int i = 0; i < 57; i++) printf(" "); // Пробелы для выравнивания счёта.
    printf("Player 2: %d\n", scoreSecond); // Вывод счёта второго игрока.

	for (int lines = 0; lines < 25; lines++)
	{
		for (int symbols = 0; symbols < 80; symbols++)
		{

			if (symbols == firstPlayer[0] && // Отрисовка каретки первого игрока (Элемента игрового поля, управляемого первым игроком).
				(lines == firstPlayer[1] || lines == firstPlayer[1] - 1 || lines == firstPlayer[1] + 1))
			{
				printf("|");
			}
			else if (symbols == secondPlayer[0] && // Отрисовка каретки второго игрока (Элемента игрового поля, управляемого вторым игроком).
					 (lines == secondPlayer[1] || lines == secondPlayer[1] - 1 || lines == secondPlayer[1] + 1))
			{
				printf("|");
			}
			else if (lines == 0 || lines == 24)
			{ // Отрисовка краёв игрового поля.
				printf("#");
			}
			else if (lines == ball[1] && symbols == ball[0])
			{ // Отрисовка мячика.
				printf("@");
			}
			else if (symbols == 39)
			{ // Отрисовка центра поля.
				printf("|");
			}
			else
			{
				printf(" "); // Заполнение игрового поля.
			}
		}

		printf("\n");
	}

	return 0;
}

// Функция считывания хода/ов игрока/ов.
void stepScan(char *step)
{
	scanf(" %c", step);
}

// Функция вычисления координат каретки, после получения и обработки данных от пользователя через консоль терминала.
void stepCalculation(char step, int firstPlayer[], int secondPlayer[])
{
	printf("%c\n", step);
	switch (step)
	{
	case 'a':
		if (firstPlayer[1] > 2)
			firstPlayer[1]--; // Проверка выхода за границы и декрементация каретки первого игрока.
		break;
	case 'z':
		if (firstPlayer[1] < 22)
			firstPlayer[1]++; // Проверка выхода за границы и инкрементация каретки первого игрока.
		break;
	case 'k':
		if (secondPlayer[1] > 2)
			secondPlayer[1]--; // Проверка выхода за границы и декрементация каретки второго игрока.
		break;
	case 'm':
		if (secondPlayer[1] < 22)
			secondPlayer[1]++; // Проверка выхода за границы и инкрементация каретки второго игрока.
		break;
	default:
		break;
	}
}

// Функция движения мяча.
void ballMovement(int ball[], int firstPlayer[], int secondPlayer[], int *scoreFirst, int *scoreSecond)
{
	// Обновление позиции мяча.
	ball[0] += ball[2];
	ball[1] += ball[3];

	// Проверка столкновений с верхней и нижней стенками.
	if (ball[1] <= 1 || ball[1] >= 23)
	{
		ball[3] = -ball[3]; // Меняем направление движения по вертикали.
	}

	// Проверка столкновений с левыми и правыми стенками.
	if (ball[0] <= 0)
	{
		*scoreSecond += 1;				 // Увеличиваем счёт второго игрока.
		ball[0] = 39;					 // Сбрасываем позицию мяча в центр.
		ball[1] = 12;					 // Сбрасываем позицию мяча в центр.
		ball[2] = (rand() % 2) ? 1 : -1; // Случайное начальное направление по x.
		ball[3] = (rand() % 2) ? 1 : -1; // Случайное начальное направление по y.
	}
	else if (ball[0] >= 79)
	{
		*scoreFirst += 1;				 // Увеличиваем счёт первого игрока.
		ball[0] = 39;					 // Сбрасываем позицию мяча в центр.
		ball[1] = 12;					 // Сбрасываем позицию мяча в центр.
		ball[2] = (rand() % 2) ? 1 : -1; // Случайное начальное направление по x.
		ball[3] = (rand() % 2) ? 1 : -1; // Случайное начальное направление по y.
	}

	// Проверка столкновений с каретками.
	if (ball[0] == firstPlayer[0] + 1 && (ball[1] == firstPlayer[1] || ball[1] == firstPlayer[1] - 1 || ball[1] == firstPlayer[1] + 1))
	{
		ball[2] = -ball[2]; // Отражаем мяч от каретки первого игрока.
	}
	else if (ball[0] == secondPlayer[0] - 1 && (ball[1] == secondPlayer[1] || ball[1] == secondPlayer[1] - 1 || ball[1] == secondPlayer[1] + 1))
	{
		ball[2] = -ball[2]; // Отражаем мяч от каретки второго игрока.
	}
}

// Функция обновления счёта
void score(int *scoreFirst, int *scoreSecond, int side)
{
	if (side == 0)
	{
		(*scoreSecond)++; // Инкрементируем счёт второго игрока при забитие гола.
	}
	else if (side == 1)
	{
		(*scoreFirst)++; // Инкрементируем счёт первого игрока при забитие гола.
	}
}