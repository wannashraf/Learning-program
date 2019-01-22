#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>

void LogMenu();
void Menu();
int Login();
int Create();
void NextDay(int, int, int);
void Logout();
void Kanji();
void Eigo();
void Status();
void ExpUp(int, int, int);
float MaxExp(int);

struct Userstats
{
	char UserID[20];
	char Pass[20];
	char Name[20];
	int EngRate; //段位
	int KanRate; //段位
	int EngLevel; //ユーザーレベル
	int KanLevel;
	int EngExp; //経験値
	int KanExp;
	int Days;
	int ContDay;
}Data;


int main() {

	printf("<<<   KenTei-Kun  -KTK-   >>>\n\n");
	printf("検定用学習プログラム 「KenTei-Kun」へようこそ！\n\n");

	LogMenu();

	return 0;
}

void LogMenu() {
	char Log[20];
	bool check;

	check = false;
	printf("ログインしてください\nアカウントがなければ「Create」と、ある場合は「Login」と入力してください。\n → ");
	while (1)
	{
		scanf("%s", Log);
		if (strcmp(Log, "Create") == 0) {
			check = Create();
		}
		else if (strcmp(Log, "Login") == 0) {
			check = Login();
		}
		else {
			printf("\n入力が間違っています\n「Login」または「Create」と入力してください\n → ");
		}
		if (check)break;
	}
	Menu();
}

void Menu() {
	time_t timer;
	int Num;
	int y, m, d;
	char Numc[10];
	FILE *fi, *fo;
	struct tm *local;
	int year, month, day;

	/* 現在時刻を取得 */
	timer = time(NULL);

	local = localtime(&timer); /* 地方時に変換 */
	year = local->tm_year + 1900;
	month = local->tm_mon + 1;
	day = local->tm_mday;

	fi = fopen("Login.txt", "r");
	fo = fopen("Login.txt", "a");

	for (int i = 0; i <= atoi(Data.UserID); i++) {
		if (fscanf(fi, "%d/%d/%d\n", &y, &m, &d) == EOF) {
			fprintf(fo, "%d/%d/%d\n", year, month, day);
			Data.Days = 0;
		}
	}

	if (year == y && month == m && day == d) {
	}
	else {
		Data.Days++;
	}

	fclose(fi);
	fclose(fo);

	NextDay(y, m, d);

	printf("ようこそ %s さん！\n", Data.Name);
	printf("通算 %d 日のログイン！\n", Data.Days);
	printf("今日は %d 日連続です\n\n", Data.ContDay);

	while (1) {
		Num = -1;
		printf("＊何をしますか？＊\n");
		printf(" →  1.今日は英語を勉強しようかな～\n");
		printf(" →  2.漢字の勉強やるしかねぇな\n");
		printf(" →  3.戦績でも見るか！\n");
		printf(" →  0.やっぱやめるかｗ\n　→　");
		scanf("%s", Numc);
		if (strlen(Numc) == 1) Num = Numc[0] - 48;
		switch (Num)
		{
		case 1:
			Kanji();
			break;
		case 2:
			Eigo();
			break;
		case 3:
			Status();
			break;
		case 0:
			printf("＊ログアウトします＊\n＊お疲れさまでした＊\n\n");
			Logout();
			break;
		default:
			printf("＊入力が間違っています＊\n＊再度入力してください＊\n　→　\n");
			break;
		}
		if (Num == 0)break;
	}
}

int Login() {
	strcpy(Data.Name, "瀬川侑");
	Data.UserID[0] = '1';
	Data.ContDay = 2;
	Data.Days = 10;
	Data.KanLevel = 6;
	Data.EngLevel = 4;
	return 1;
}

int Create() {
	return 1;
}

void Logout() {

}

void Kanji() {
	ExpUp(5, 6, 1);
}

void Eigo() {
	ExpUp(30, 4, 0);
}

void NextDay(int ly, int lm, int ld) {
	time_t timer;
	struct tm *local;
	int year, month, day;
	int uru;

	/* 現在時刻を取得 */
	timer = time(NULL);

	local = localtime(&timer); /* 地方時に変換 */
	year = local->tm_year + 1900;
	month = local->tm_mon + 1;
	day = local->tm_mday;

	switch (lm) {
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
		if (ld == 31) {
			ld = 1;
			lm++;
		}
		else ld++;
		break;

	case 12:
		if (ld == 31) {
			ld = 1;
			lm = 1;
			ly++;
		}
		else ld++;
		break;

	case 2:
		if (ly % 4 == 0) {
			uru = 1;
			if (ly % 100 == 0) {
				uru = 0;
				if (ly % 400 == 0) {
					uru = 1;
				}
			}
		}
		else uru = 0;

		if (ld == 29) {
			ld = 1;
			lm++;
		}
		if (ld == 28 && uru == 0) {
			ld = 1;
			lm++;
		}
		else {
			ld++;
		}
		break;

	case 4:
	case 6:
	case 9:
	case 11:
		if (ld == 30) {
			ld = 1;
			lm++;
		}
		else ld++;
		break;
	}

	if (year == ly && month == lm && day == ld) {
		Data.ContDay++;
	}
	else Data.ContDay = 1;
}

void ExpUp(int Ans, int dif, int kind) {
	int MaxEng, MaxKan;
	float amp;
	if (kind) {
		amp = MaxExp(Data.KanLevel);
		MaxKan = amp / 1;

		Data.KanExp += Ans * dif;
		while (MaxKan <= Data.KanExp) {
			Data.KanLevel++;
			Data.KanExp -= MaxKan;
			amp *= 1.1;
			MaxKan = amp / 1;
		}
	}
	else {
		amp = MaxExp(Data.EngLevel);
		MaxEng = amp / 1;

		Data.EngExp += Ans * dif;
		while (MaxEng <= Data.EngExp) {
			Data.EngLevel++;
			Data.EngExp -= MaxEng;
			amp *= 1.1;
			MaxEng = amp / 1;
		}
	}
}

float MaxExp(int Level) {
	float a = 10;

	for (int i = 1; i < Level; i++) {
		a *= 1.1;
	}
	return a;
}

void Status() {
	int Exp1, Exp2;
	Exp1 = MaxExp(Data.KanLevel) / 1;
	Exp2 = MaxExp(Data.EngLevel) / 1;
	printf("-----ここではあなたの今までのデータが記録されています-----\n\n");
	printf("漢字レベル %d exp %d/%d\n", Data.KanLevel, Data.KanExp, Exp1);
	printf("英語レベル %d exp %d/%d\n", Data.EngLevel, Data.EngExp, Exp2);

}