#include <stdio.h>

int painting(int ball[], int firstPlayer[], int secondPlayer[]);
void stepScan(char *step);
void stepCalculation(char step, int firstPlayer[], int secondPlayer[]);

int main(void) {
	char step = 'h';
	//int score_first = 0, score_second = 0;
	int ball[2] = {39, 12}, firstPlayer[2] = {0, 12}, secondPlayer[2] = {79, 12};
	
	do {
		painting(ball, firstPlayer, secondPlayer); // Отрисовываем поле (Логика не зависит от него. Это - лишь видимая игроку часть игры).
		stepScan(&step); // Получаем ввод хода от игрока и записываем его в память по адресу переменной step.
		stepCalculation(step, firstPlayer, secondPlayer); // Вычисляем новые координаты положения кареток, после внесённых изменений.
	} while(1);

	return 0;
}



// Функция отрисовки игрового процесса (Алгоритм вывода данных в терминал).
int painting(int ball[], int firstPlayer[], int secondPlayer[]) {
	
	for (int lines = 0; lines < 25; lines++) {
		for (int symbols  = 0; symbols < 80; symbols++) {
			
			if (symbols == firstPlayer[0] && // Отрисовка каретки (Элемента игрового поля, управляемого игроком).
                (lines == firstPlayer[1] || lines == firstPlayer[1] - 1 || lines == firstPlayer[1] + 1)) {
                printf("|");
			} else if (symbols == secondPlayer[0] && 
                (lines == secondPlayer[1] || lines == secondPlayer[1] - 1 || lines == secondPlayer[1] + 1)) {
                printf("|");
            } else if (lines == 0 || lines == 24) { // Отрисовка краёв игрового поля.
				printf("#");
			} else if (lines == ball[1] && symbols == ball[0]) { // Отрисовка мячика.
			    printf("@");
			} else if (symbols == 39 && lines != ball[1]) { // Отрисовка центра поля.
				printf("|");
			} else {
				printf(" "); // Заполнение игрового поля.
			}

		}

		printf("\n");

	}

	return 0;
}


// Функция считывания хода/ов игрока/ов.
void stepScan(char *step) {
    scanf(" %c", step);
}

// Функция вычисления координат каретки, после получения и обработки данных от пользователя через консоль терминала.
void stepCalculation(char step, int firstPlayer[], int secondPlayer[]) {
	printf("%c\n", step);
	switch (step) {
		case 'a':
            if (firstPlayer[1] > 2) firstPlayer[1]--; // Проверка выхода за границы и декрементация каретки первого игрока.
            break;
        case 'z':
            if (firstPlayer[1] < 22) firstPlayer[1]++; // Проверка выхода за границы и инкрементация каретки первого игрока.
            break;
        case 'k':
            if (secondPlayer[1] > 2) secondPlayer[1]--; // Проверка выхода за границы и декрементация каретки второго игрока.
            break;
        case 'm':
            if (secondPlayer[1] < 22) secondPlayer[1]++; // Проверка выхода за границы и инкрементация каретки второго игрока.
            break;
        default:
            break;
	}
}