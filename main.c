#include<stdio.h>
#include<stdlib.h>
#include <time.h>

#define DEALER_CARD (i + 20)

typedef struct{
    int number;
    int point;
    int isAce;
    char mark;
}ST_TRUMP;

static int s_playerisAce = 0;
static int s_dealerisAce = 0;

void shaffl(ST_TRUMP *card);
void result_printf(int result);

void main(){
    ST_TRUMP card[52];

    int player_max, dealer_max, dealer_upCard, dealerWait = 1;
    int i = 2, addCard, judge = 1, result;

//乱数の種を設定
    srand((unsigned int) time(NULL));

//カードをシャッフル
    shaffl(card);

//初期カードをセット
    player_max    =  card[1].point;
    player_max    += card[2].point;
    s_playerisAce += card[1].isAce;
    s_playerisAce += card[2].isAce;

    dealer_max    =  card[20].point;
    dealer_max    += card[21].point;
    dealer_upCard = card[21].point;
    s_dealerisAce += card[20].isAce;
    s_dealerisAce += card[21].isAce;

    printf("プレイヤーにカードが配られます。\n");

    printf("1枚目：%cの%d\n",card[1].mark,card[1].number);
    printf("2枚目：%cの%d\n",card[2].mark,card[2].number);

    printf("プレイヤー合計：%d点\n",player_max);
    printf("\nディーラーのアップカード：%cの%d\n",card[21].mark,card[21].number);
//Blackjackであれば56行目のdo文を抜ける
    if(player_max == 21){
        judge = 0;
    }
    
    do {
        i++;
		printf("\nさらにカードを引きますか？ [Yes:1 No:0]\n");
//カードを引くか選択
        scanf("%d",&addCard);
        if(addCard != 0) {
//プレイヤーのカードをセット
            player_max += card[i].point;
            s_playerisAce += card[i].isAce;
//21点以上の時、1を引いていれば得点から10を引く
            if(player_max > 21 && s_playerisAce > 0) {
                player_max = player_max - 10;
//1を引いた回数をデクリメント
                s_playerisAce--;
            }

            printf("%d枚目：%cの%d\n",i,card[i].mark,card[i].number);
            printf("プレイヤーの合計：%d点\n",player_max);
//dealerWaitが0の時ディーラーはカードを引かない
            if(dealerWait){
//ディーラーのカードをセット
                dealer_max += card[DEALER_CARD].point;
                dealer_upCard += card[DEALER_CARD].point;
//21点以上の時、1を引いていれば得点から10を引く
                if(dealer_upCard > 21 && s_dealerisAce > 0) {
                     dealer_max    = dealer_max - 10;
                     dealer_upCard = dealer_upCard - 10;
                     s_playerisAce--;
                }
                printf("\nディーラー追加カード：%cの%d\n",card[DEALER_CARD].mark,card[DEALER_CARD].number);
                printf("ディーラーのアップカードの合計：%d点\n",dealer_upCard);
//ディーラーのアップカードの合計が16を超えたらそれ以上カードを引かない。
//dealerWaitを0にリセット
                if((dealer_upCard > 16 && player_max <= 20 && dealer_upCard <= 21)){
                    printf("\nディーラーのアップカードの合計が17以上になりました。\n");
                    printf("ディーラーはこれ以上カードを引きません。\n");
                    dealerWait = 0;
                }
            }
//プレイヤーの点数が21を超えたらdo文を抜ける
            if(player_max >= 21){
                judge = 0;
            }
        }else{
            judge = 0;
        }
    }while(judge);

    printf("\nディーラーのホールカード：%cの%d\n",card[20].mark,card[20].number);
    printf("\nプレイヤーの合計：%d点”\n",player_max);
    printf("ディーラーの合計：%d点\n",dealer_max);

//ゲーム結果
    if(player_max == 21 && dealer_max == !21){
        result = 0;
    }else if(player_max > 21 || dealer_max <= 21 && player_max < dealer_max){
        result = 1;
    }else if(player_max <= 21 && dealer_max < player_max || dealer_max > 21){
        result = 2;
    }else{
        result = 3;
    }
   
    result_printf(result);
    return;
}

void shaffl(ST_TRUMP *card){
    int flag;
    int data[52];
    int i,j;
//要素数52の配列を用意し、rand関数を用いてシャッフル
    for( i=0; i<52; i++){
        data[i] = i;
    }
    for(i=0;i<52;i++){
        int j = rand()% 52;
        int temp = data[i];
        data[i] = data[j];
        data[j] = temp;
    }
    for(i=0;i<52;i++){
//isAceをリセット
        card[i].isAce = 0;
//マークを設定
    switch(data[i] % 4){
    case 0:
        card[i].mark = 'S'; break ;
    case 1:
        card[i].mark = 'H'; break ;
    case 2:
        card[i].mark = 'D'; break ;
    case 3:
        card[i].mark = 'C'; break ;
    }
//カードのナンバーを設定    
        card[i].number = (data[i] % 13) + 1;
//カードの得点を設定
        if (card[i].number == 1){
            card[i].isAce = 1;
            card[i].point = 11;
        }else if(card[i].number > 10){
            card[i].point = 10;
        }else{
          card[i].point = card[i].number;
        }
    }
}
//結果を表示する関数
void result_printf(int result){
        putchar('\n');
    switch(result){
        case 0:
        printf("BlackJack!貴方の勝ちです！"); break;
        case 1:
        printf("貴方の負けです！");break;
        case 2:
        printf("貴方の勝ちです！"); break;
        case 3:
        printf("引き分けです！"); break;
    }
    return;
}

