#include<stdlib.h>
#include<stdio.h>
#include<string.h>
//Linus用
/*
#include<termios.h>
#include<unistd.h>
#include<ctype.h>
*/

#pragma warning(disable:4996)

void Menu();
void Create();
void Login();
void Logout();
void Save();
void Kanji();
void Eigo();
void Status();

struct Userstats
{
	char UserID[20];
	char Pass[20];
	char Name[20];
	int Rate; //段位
	int level; //ユーザーレベル
	int exp; //経験値
}Data;


int main() {

	printf("<< <   KenTei - Kun - KTK - >> >\n\n");
	printf("検定用学習プログラム 「KenTei-Kun」へようこそ！\n\n");

	Menu();

	return 0;
}

void Menu() {
	int Num;
	char Numc[10];

	printf("ログインしてください\n");
	Login();

	while (1) {
		printf("＊何をしますか？＊\n");
		printf(" →  1.今日は英語を勉強しようかな～\n");
		printf(" →  2.漢字の勉強やるしかねぇな\n");
		printf(" →  3.戦績でも見るか！\n");
		printf(" →  0.やっぱやめるかｗ\n→  ");
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
			printf("＊入力が間違っています＊\n＊再度入力してください＊\n\n");
			break;
		}
		if (Num == 0)break;
	}
}

void Create() {
	int i, id;
	char c, Name[20], Pass[20], re_Pass[20];
	FILE *fp;

	id = 0;
	fp = fopen("", "r");//情報元ファイル名
	for (;;) {//何番までのIDがあるのか確認
		c = fgetc(fp);
		if (c == '\n')id++;
		else if (c == EOF)break;
	}
	fclose(fp);

	printf("ユーザー名を入力してください。\n");
	printf("->");
	scanf("%s", Name);
	//Linux用
	/*
	struct termios term;
	struct termios save;
	char tmp;
	for (;;) {


	tcgetattr(STDIN_FILENO, &term);
	save = term;
	term.c_lflag &= ~ICANON;
	term.c_lflag &= ~ECHO;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	tmp = fgetc(stdin);
	printf("パスワードを入力してください。\n");
	printf("->");
	for (i = 0; i < 19; i++) {
	tmp = fgetc(stdin);
	if (tmp < 0 || iscntrl(tmp)) {
	fprintf(stderr, "\n");
	break;
	}
	Pass[i] = tmp;
	fprintf(stderr, "*");
	}

	printf("もう一度パスワードを入力してください。\n");
	printf("->");
	for (i = 0; i < sizeof(re_Pass) - 1; i++) {
	tmp = fgetc(stdin);
	if (tmp < 0 || iscntrl(tmp)) {
	fprintf(stderr, "\n");
	break;
	}
	re_Pass[i] = tmp;
	fprintf(stderr, "*");
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &save);

	//パスワードの正誤判定
	if (strcmp(Pass, re_Pass) == 0) break;
	else {
	printf("同じパスワードが入力されていません。Enterを押して再入力してください\n");
	memset(Pass, '\0', 20);
	memset(re_Pass, '\0', 20);
	}
	}
	*/

	//windws用
	for (;;) {
		printf("パスワードを入力してください。\n");
		printf("->");
		system("stty -echo");
		scanf("%s", Pass);
		system("stty echo");
		printf("もう一度パスワードを入力してください。\n");
		printf("->");
		system("stty -echo");
		scanf("%s", re_Pass);
		system("stty echo");


		//パスワードの正誤判定
		if (strcmp(Pass, re_Pass) == 0) break;
		else {
			printf("同じパスワードが入力されていません。Enterを押して再入力してください\n");
			memset(Pass, '\0', 20);
			memset(re_Pass, '\0', 20);
		}
	}

	printf("アカウントが作成されました。\n");
	printf("ユーザーIDは%07dです。\n", id);
	printf("MENU画面に戻ります。\n\n");

	fp = fopen("", "a");//情報元ファイル名
	fprintf(fp, "%07d %s %s 0 1 1\n", id, Pass, Name);
	fclose(fp);
}

void Login() {
	char c, id[20];
	char pass[20];
	char r_id[20], r_pass[20];
	int i;

	for (;;) {
		printf("---------------------------------------\n");
		printf("-ID(7桁)を入力してください\n");
		printf("->");
		scanf("%s", id);
		printf("---------------------------------------\n");

		//Linux用
		/*
		struct termios term;
		struct termios save;
		char tmp, re_pass[20];

		tcgetattr(STDIN_FILENO, &term);
		save = term;
		term.c_lflag &= ~ICANON;
		term.c_lflag &= ~ECHO;
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
		tmp = fgetc(stdin);
		for (i = 0; i <= 20; i++) {
		re_pass[i] = 0;
		}
		printf("パスワードを入力してください。\n");
		printf("->");
		for (int j = 0; j < 19; j++) {
		tmp = fgetc(stdin);
		if (tmp < 0 || iscntrl(tmp)) {
		fprintf(stderr, "\n");
		break;
		}
		re_pass[j] = tmp;
		fprintf(stderr, "*");
		}
		tcsetattr(STDIN_FILENO, TCSANOW, &save);
		*/

		//windows用
		printf("パスワードを入力してください。\n");
		printf("->");
		system("stty -echo");
		scanf("%s", pass);
		system("stty echo");


		printf("---------------------------------------\n");

		//アカウント探索
		FILE *fp;
		fp = fopen("", "r");//情報元ファイル名
		i = 0;
		for (;;) {
			if (i == atoi(id))break;
			c = fgetc(fp);
			if (c == '\n')i++;
			else if (c == EOF)break;
		}
		if (c == EOF) printf("ログインに失敗しました。再入力して下さい。\n");
		fscanf(fp, "%s %s", r_id, r_pass);
		if (strcmp(pass, r_pass) == 0) {
			printf("ログインに成功しました。\n");
			strcpy(Data.UserID, id);
			strcpy(Data.Pass, pass);
			fscanf(fp, "%s %d %d %d", Data.Name, &Data.Rate, &Data.level, &Data.exp);
			break;
		}
		else {
			printf("ログインに失敗しました。再入力して下さい。\n");
		}
	}
}

void Logout() {
	int i;

	Save();
	//初期化
	for (i = 0; i < 20; i++) {
		Data.UserID[i] = '\0';
		Data.Pass[i] = '\0';
		Data.Name[i] = '\0';
	}
	Data.Rate = 0;
	Data.level = 0;
	Data.exp = 0;
}

void Save() {
	FILE *fp, *fi;
	char c;
	int p;

	fp = fopen("", "r");//情報元ファイル名
	fi = fopen("cache.txt", "w");
	for (;;) {
		c = fgetc(fp);
		if (c == EOF)break;
		fprintf(fi, "%c", c);
	}
	fclose(fp);
	fclose(fi);

	fp = fopen("", "w");//情報元ファイル名
	fi = fopen("cache.txt", "r");

	for (p = 0; p != atoi(Data.UserID); p++) {//複写
		for (;;) {
			c = fgetc(fi);
			fprintf(fp, "%c", c);
			if (c == '\n' || c == EOF)break;
		}
	}
	fprintf(fp, "%s %s %s %d %d %d\n", Data.UserID, Data.Pass, Data.Name, Data.Rate, Data.level, Data.exp);//更新
	for (;;) {
		c = fgetc(fi);
		if (c == '\n' || c == EOF)break;
	}
	for (;;) {//残りすべて複写
		c = fgetc(fi);
		if (c == EOF)break;
		fprintf(fp, "%c", c);
	}
	fclose(fp);
	fclose(fi);
	fi = fopen("cache.txt", "w");
	fclose(fi);
}

void Kanji() {

}

void Eigo() {

}

void Status() {

}