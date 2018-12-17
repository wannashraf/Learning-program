#include<stdlib.h>
#include<stdio.h>
#include<string.h>

void Menu();
void Login();
void Logout();
void Kanji();
void Eigo();
void Status();

struct Userstats
{
	int Rate; //段位
	int level; //ユーザーレベル
	int exp; //経験値
}Data;

int UserID; //ログイン時に入れるやつ


int main(){

	printf(<<<   KenTei-Kun  -KTK-   >>>\n\n");
	printf("検定用学習プログラム 「KenTei-Kun」へようこそ！\n\n");

	MENU();

	return 0;
}

void Menu(){
	int Num;			
	char Numc[10],Log[20];
	bool check;

	check = false;
	printf("ログインしてください\nアカウントがなければ「Create」と、ある場合は「Login」と入力してください。\n\n");
	while (1)
	{
		scanf(" → %s", Log);
		if (strcmp(Log, "Create") == 0) {
			check = true;
			Create();
		}
		else if (strcmp(Log, "Login") == 0) {
			check = true;
			Login();
		}
		else {
			printf("\n入力が間違っています\n「Login」または「Create」と入力してください\n");
		}
		if (check)break;
	}

	while(1){
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

void Login() {

}

void Logout() {

}

void Kanji() {

}

void Eigo() {

}

void Status() {
	printf("-----ここではあなたの今までのデータが記録されています-----\n\n");
	
}