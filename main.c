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
int Create();
int Login();
int Quit();
void Logout();
void Save();
void ChangeName();
void ChangePass();
void Kanji();
void Eigo();
void Status();

struct Userstats
{
	char UserID[20];
	int ID;
	char Pass[20];
	char Name[20];
	int KanRate; //漢検段位
	int Kanlevel; //漢検ユーザーレベル
	int Kanexp; //漢検経験値
	int EngRate; //段位
	int Englevel; //ユーザーレベル
	int Engexp; //経験値
	int Days;
}Data;


int main() {

	printf("<< <   KenTei - Kun - KTK - > >>\n\n");
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

int Create() {
	int id;
	char c, Name[20], Pass[20], re_Pass[20];
	FILE *fp;

	id = 0;
	fp = fopen("UserData.txt", "r");//情報元ファイル名
	for (;;) {//何番までのIDがあるのか確認
		c = fgetc(fp);
		if (c == '\n')id++;
		else if (c == EOF)break;
	}
	fclose(fp);

	for (;;) {
		printf("ユーザー名を入力してください。\n後から変更できます。\nアカウント作成を中断する場合は「quit」と入力してください。\n");
		printf("->");
		scanf("%s", Name);
		if (!strcmp(Name, "quit")) {//中断処理
			if (!Quit())return 0;
		}
		else break;
	}
	//Linux用
	/*
	struct termios term;
	struct termios save;
	char tmp;
	for (;;) {
	for (;;) {
	tcgetattr(STDIN_FILENO, &term);
	save = term;
	term.c_lflag &= ~ICANON;
	term.c_lflag &= ~ECHO;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	tmp = fgetc(stdin);
	printf("パスワードを入力してください。\n後から変更できます。\nアカウント作成を中断する場合は「quit」と入力してください。\n");
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
	if (!strcmp(Pass, "quit")) {//中断処理
	if (!Quit())return 0;
	}
	else break;
	}
	for (;;) {
	printf("もう一度パスワードを入力してください。\nアカウント作成を中断する場合は「quit」と入力してください。\n");
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
	if (!strcmp(re_Pass, "quit")) {//中断処理
	if (!Quit())return 0;
	}
	else break;
	}

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
		for (;;) {
			printf("パスワードを入力してください。\n後から変更できます。\nアカウント作成を中断する場合は「quit」と入力してください。\n");
			printf("->");
			system("stty -echo");
			scanf("%s", Pass);
			system("stty echo");
			if (!strcmp(Pass, "quit")) {//中断処理
				if (!Quit())return 0;
			}
			else break;
		}
		for (;;) {
			printf("もう一度パスワードを入力してください。\nアカウント作成を中断する場合は「quit」と入力してください。\n");
			printf("->");
			system("stty -echo");
			scanf("%s", re_Pass);
			system("stty echo");
			if (!strcmp(re_Pass, "quit")) {//中断処理
				if (!Quit())return 0;
			}
			else break;
		}


		//パスワードの正誤判定
		if (strcmp(Pass, re_Pass) == 0) break;
		else {
			printf("同じパスワードが入力されていません。再入力してください\n");
			memset(Pass, '\0', 20);
			memset(re_Pass, '\0', 20);
		}
	}

	printf("アカウントが作成されました。\n");
	printf("ユーザーIDは%07dです。\n", id);
	printf("MENU画面に戻ります。\n\n");

	fp = fopen("UserData.txt", "a");//情報元ファイル名
	fprintf(fp, "%07d %s %s 0 1 0 0 1 0 1\n", id, Pass, Name);//各情報の初期値入力
	fclose(fp);
	Data.ID = id;
	strcpy(Data.Pass, Pass);
	strcpy(Data.Name, Name);
	Data.KanRate = 0;
	Data.Kanlevel = 1;
	Data.Kanexp = 0;
	Data.EngRate = 0;
	Data.Englevel = 1;
	Data.Engexp = 0;
	Data.Days = 1;

	return 1;
}

int Login() {
	char c, id[20];
	char pass[20];
	char r_id[20], r_pass[20];
	int i;

	for (;;) {
		printf("---------------------------------------\n");
		for (;;) {
			printf("-ID(7桁)を入力してください。\nログインを中断する場合は「quit」と入力してください。\n");
			printf("->");
			scanf("%s", id);
			if (!strcmp(id, "quit")) {//中断処理
				if (!Quit())return 0;
			}
			else break;
		}
		printf("---------------------------------------\n");

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
		for (i = 0; i <= 20; i++) {
		re_pass[i] = 0;
		}
		printf("パスワードを入力してください。\nログインを中断する場合は「quit」と入力してください。\n");
		printf("->");
		for (int j = 0; j < 19; j++) {
		tmp = fgetc(stdin);
		if (tmp < 0 || iscntrl(tmp)) {
		fprintf(stderr, "\n");
		break;
		}
		pass[j] = tmp;
		fprintf(stderr, "*");
		}
		tcsetattr(STDIN_FILENO, TCSANOW, &save);
		if (!strcmp(pass, "quit")) {//中断処理
		if (!Quit())return 0;
		}
		else break;
		}
		*/

		//windows用
		for (;;) {
			printf("パスワードを入力してください。\nログインを中断する場合は「quit」と入力してください。\n");
			printf("->");
			system("stty -echo");
			scanf("%s", pass);
			system("stty echo");
			if (!strcmp(pass, "quit")) {//中断処理
				if (!Quit())return 0;
			}
			else break;
		}


		printf("---------------------------------------\n");

		//アカウント探索
		FILE *fp;
		fp = fopen("UserData.txt", "r");//情報元ファイル名
		i = 0;
		for (;;) {
			if (i == atoi(id))break;
			c = fgetc(fp);
			if (c == '\n')i++;
			else if (c == EOF)break;
		}
		if (c == EOF) {
			printf("ログインに失敗しました。再入力して下さい。\n");
		}
		fscanf(fp, "%s %s", r_id, r_pass);
		if (strcmp(pass, r_pass) == 0) {
			printf("ログインに成功しました。\n");
			strcpy(Data.UserID, id);
			strcpy(Data.Pass, pass);
			fscanf(fp, "%s %d %d %d %d %d %d %d", Data.Name, &Data.KanRate, &Data.Kanlevel, &Data.Engexp, &Data.EngRate, &Data.Englevel, &Data.Engexp, &Data.Days);
			Data.ID = atoi(Data.UserID);

			return 1;
		}
		else {
			printf("ログインに失敗しました。再入力して下さい。\n");
		}
	}
}

int Quit() {
	char r[20];
	int choice;
	for (;;) {
		printf("現在の作業を中止し、前のメニューへ戻りますか？\n1:はい\n2:いいえ\n->");
		scanf("%s", r);
		if (strlen(r) == 1) {
			choice = r[0] - 48;
			if (choice == 1) {
				printf("中止しました。前のメニューに戻ります。\n");
				return 0;
			}
			else if (choice == 2) {
				printf("現在の作業に戻ります。\n");
				return 1;
			}
			else printf("入力された内容が不適切です。再入力してください。\n");
		}
		else {
			printf("入力された内容が不適切です。再入力してください。\n");
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
	Data.KanRate = 0;
	Data.Kanlevel = 0;
	Data.Kanexp = 0;
	Data.EngRate = 0;
	Data.Englevel = 0;
	Data.Engexp = 0;
	Data.Days = 0;
}

void Save() {
	FILE *fp, *fi;
	char c;
	int p;

	fp = fopen("UserData.txt", "r");//情報元ファイル名
	fi = fopen("cache.txt", "w");
	for (;;) {
		c = fgetc(fp);
		if (c == EOF)break;
		fprintf(fi, "%c", c);
	}
	fclose(fp);
	fclose(fi);

	fp = fopen("UserData.txt", "w");//情報元ファイル名
	fi = fopen("cache.txt", "r");

	for (p = 0; p != atoi(Data.UserID); p++) {//複写
		for (;;) {
			c = fgetc(fi);
			fprintf(fp, "%c", c);
			if (c == '\n' || c == EOF)break;
		}
	}
	fprintf(fp, "%07d %s %s %d %d %d %d %d %d %d\n", Data.ID, Data.Pass, Data.Name, Data.KanRate, Data.Kanlevel, Data.Engexp, Data.EngRate, Data.Englevel, Data.Engexp, Data.Days);//更新
	for (;;) {//旧データの読み飛ばし
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
	fi = fopen("cache.txt", "w");//キャッシュの削除
	fclose(fi);
}

void ChangeName() {
	char Name[20], r[20];
	int i, choice;

	for (;;) {
		printf("ユーザー名を入力してください。\n中断する場合は「quit」と入力してください。\n");
		printf("->");
		scanf("%s", Name);
		if (!strcmp(Name, "quit")) {//中断処理
			if (!Quit())return;
		}
		else break;
	}

	for (;;) {
		printf("ユーザー名を「%s」から「%s」に変更しますか？\n1:はい\n2:いいえ\n->", Data.Name, Name);
		scanf("%s", r);
		if (strlen(r) == 1) {
			choice = r[0] - 48;
			if (choice == 1) {
				for (i = 0; i < 20; i++) {
					Data.Name[i] = '\0';
				}
				strcpy(Data.Name, Name);
				printf("ユーザー名の変更が完了しました。\nメニューに戻ります。\n");
				return;
			}
			else if (choice == 2) {
				printf("ユーザー名を変更せずメニューに戻ります。\n");
				return;
			}
			else printf("入力された内容が不適切です。再入力してください。\n");
		}
		else {
			printf("入力された内容が不適切です。再入力してください。\n");
		}
	}
}

void ChangePass() {
	char pass[20], Pass[20], re_Pass[20], r[20];
	int i, choice;

	for (;;) {
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
		for (i = 0; i <= 20; i++) {
		re_pass[i] = 0;
		}
		printf("現在のパスワードを入力してください。\n中断する場合は「quit」と入力してください。\n");
		printf("->");
		for (int j = 0; j < 19; j++) {
		tmp = fgetc(stdin);
		if (tmp < 0 || iscntrl(tmp)) {
		fprintf(stderr, "\n");
		break;
		}
		pass[j] = tmp;
		fprintf(stderr, "*");
		}
		tcsetattr(STDIN_FILENO, TCSANOW, &save);
		if (!strcmp(pass, "quit")) {//中断処理
		if (!Quit())return;
		}
		else break;
		}
		*/

		//windows用
		for (;;) {
			printf("現在のパスワードを入力してください。\n中断する場合は「quit」と入力してください。\n");
			printf("->");
			system("stty -echo");
			scanf("%s", pass);
			system("stty echo");
			if (!strcmp(pass, "quit")) {//中断処理
				if (!Quit())return;
			}
			else break;
		}

		//照合
		if (strcmp(pass, Data.Pass) == 0) {
			break;
		}
		else {
			printf("現在のパスワードが違います。\n再入力してください。");
		}
	}

	//Linux用
	/*
	struct termios term;
	struct termios save;
	char tmp;
	for (;;) {
	for (;;) {
	tcgetattr(STDIN_FILENO, &term);
	save = term;
	term.c_lflag &= ~ICANON;
	term.c_lflag &= ~ECHO;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	tmp = fgetc(stdin);
	printf("新しいパスワードを入力してください。\n中断する場合は「quit」と入力してください。\n");
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
	if (!strcmp(Pass, "quit")) {//中断処理
	if (!Quit())return;
	}
	else break;
	}
	for (;;) {
	printf("もう一度新しいパスワードを入力してください。\n中断する場合は「quit」と入力してください。\n");
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
	if (!strcmp(re_Pass, "quit")) {//中断処理
	if (!Quit())return;
	}
	else break;
	}

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
		for (;;) {
			printf("新しいパスワードを入力してください。\n中断する場合は「quit」と入力してください。\n");
			printf("->");
			system("stty -echo");
			scanf("%s", Pass);
			system("stty echo");
			if (!strcmp(Pass, "quit")) {//中断処理
				if (!Quit())return;
			}
			else break;
		}
		for (;;) {
			printf("もう一度新しいパスワードを入力してください。中断する場合は「quit」と入力してください。\n");
			printf("->");
			system("stty -echo");
			scanf("%s", re_Pass);
			system("stty echo");
			if (!strcmp(re_Pass, "quit")) {//中断処理
				if (!Quit())return;
			}
			else break;
		}


		//パスワードの正誤判定
		if (strcmp(Pass, re_Pass) == 0) break;
		else {
			printf("同じパスワードが入力されていません。再入力してください\n");
			memset(Pass, '\0', 20);
			memset(re_Pass, '\0', 20);
		}
	}

	for (;;) {
		printf("本当に変更しますか？\n1:はい\n2:いいえ\n->");
		scanf("%s", r);
		if (strlen(r) == 1) {
			choice = r[0] - 48;
			if (choice == 1) {
				for (i = 0; i < 20; i++) {
					Data.Pass[i] = '\0';
				}
				strcpy(Data.Pass, Pass);
				printf("パスワードの変更が完了しました。\nメニューに戻ります。\n");
				return;
			}
			else if (choice == 2) {
				printf("パスワードを変更せずメニューに戻ります。\n");
				return;
			}
			else printf("入力された内容が不適切です。再入力してください。\n");
		}
		else {
			printf("入力された内容が不適切です。再入力してください。\n");
		}
	}
}

void Kanji() {

}

void Eigo() {

}

void Status() {

}