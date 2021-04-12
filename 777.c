#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int card[52],play[13],com1[13],com2[13],com3[13],number,startcolor,start,who,b=13,com1_round=13,com2_round=13,com3_round=13,spade[13],heart[13],diamond[13],club[13],Frist_card;
int blackspace[2]={7,7} , redheart[2]={20,20} , blackdiamond[2]={33,33} , redclub[2]={46,46};
//spade 黑桃 heart紅心 diamond方塊 club梅花

int main(){
    rule();
    shuffle();
    back_zeor();
    Bubble_sort(play,13);
    //Bubble_sort(com1,13);   
    //Bubble_sort(com2,13);   
    //Bubble_sort(com3,13);   
    whostart();
    startgame();
    printf("start : %d | startcolor : %d | number : %d | who : %d | FristCard : %d\n",start,startcolor,number,who,Frist_card);
    //output_arr(card,52);
    printf("play : ");
    output_arr(play,13);
    printf("com1 : ");    
    output_arr(com1,13);
    printf("com2 : ");
    output_arr(com2,13);
    printf("com3 : ");
    output_arr(com3,13);
    return 0;
}

void back_zeor(){
    for (int i = 0; i < 13; i++){
        spade[i]=0;
        heart[i]=0;
        diamond[i]=0;
        club[i]=0;
    }
}
//決定 什麼花色開始 start:切牌 startsolor:哪個花色的7先開始 0黑桃 1紅心 2黑梅 3紅方 number : 開始發牌位子1:play 2:com1 3:com2 0:com3 ok 
void rule(){
    srand(time(NULL));
    start = (rand()%52+1);
    startcolor = (start / 13); 
    if (start==13 || start ==26 ||start ==39 ||start ==52){   
        startcolor--;
    }
    number = start%13;
    if(number==0){
        number=13;
    }
    number = number%4;
}
//洗牌 分成4人分 ok
void shuffle(){
    srand(time(NULL));
    for (int i = 0; i < 52; i++){
        card[i]=(rand() % 52)+1 ;
        for (int a = 0; a < i; a++){
            if (card[i]==card[a]){
                i--;
            }
        }
        switch ((number+i)%4){
        case 1:
            play[i/4]=card[i];
            break;
        case 2:
            com1[i/4]=card[i];
            break;
        case 3:
            com2[i/4]=card[i];
            break;
        case 0:
            com3[i/4]=card[i];
            break;
        } 
    }
}
//把牌排序 ok 電腦就不排序了增加遊戲的出牌性ㄅ
void Bubble_sort(int a[],int n){
    int i,j,tmp;
    for ( int i = n-1; i > 0; i--){
        for (int j = 0; j < i; j++){
            if (a[j]>a[j+1]){
                tmp = a[j];
                a[j] = a[j+1];
                a[j+1] = tmp;
            }
        }
    }
}
//誰先開始 who 1玩家 2com1 3com2 4com3 ok
void whostart(){
    Frist_card = (startcolor*13)+7;
    //printf("FristCard : %d\n",Frist_card);
    for (int i = 0; i < 13; i++){
        if(Frist_card == play[i]){
            who = 1;
        }
        if(Frist_card == com1[i]){
            who = 2;
        }
        if(Frist_card == com2[i]){
            who = 3;
        }
        if(Frist_card == com3[i]){
            who = 4;
        }
    }
    printf("Frist_card : %d | who:%d\n",Frist_card,who);
}
//開始遊戲!!!!!!!!!!!!!!!!!!!!!!!!!
void startgame(){
    int frist_card_no,check_card,tmp;
    for (int i = 0; i < 52; i++){
        printf("round : %d\n",i);
        switch (who){
        case 1:
            if (i==0){
                judgment(Frist_card);
                frist_card_no = seach_frist_number(play);
                clean_up_card(play,frist_card_no,b);
                b--;
            }
            else{
                input();
                //printf("b number : %d\n",b);
                b--;
            }
           break;
        case 2:
            if (i==0){
                judgment(Frist_card);
                frist_card_no = seach_frist_number(com1);
                clean_up_card(com1,frist_card_no,com1_round);
                com1_round--;
            }
            else{
                output_arr(com1,com1_round);
                com_card(com1,com1_round);
                printf("com1_R number : %d\n",com1_round);
                check_card = check(com1,com1_round);
                if(check_card == 1){
                    com_input(com1,com1_round);
                }
                else if(check_card == 0){
                    printf("I NEED CLOSE CARD");
                }
                /*
                tmp = com_input(com1,com1_round);
                if (tmp == 100){
                    clean_up_card(com1,1,com1_round);
                }
                else{
                    clean_up_card(com1,tmp+1,com1_round);
                }
                */
                 com1_round--;
                
            }
            break;
        case 3:
            if (i==0){
                judgment(Frist_card);
                frist_card_no = seach_frist_number(com2);
                clean_up_card(com2,frist_card_no,com2_round);
                com2_round--;
            }
            else{
                output_arr(com2,com2_round);
                com_card(com2,com2_round);
                printf("com2_R number : %d\n",com2_round);
                check_card = check(com2,com2_round);
                if(check_card == 1){
                    com_input(com2,com2_round);
                }
                else if(check_card == 0){
                    printf("I NEED CLOSE CARD");
                }
                //check_card = check(com2,com2_round);
                /*
                tmp = com_input(com2,com2_round);
                if (tmp == 100){
                    clean_up_card(com2,1,com2_round);
                }
                else{
                    clean_up_card(com2,tmp+1,com2_round);
                }
                */
                 com2_round--;
                //printf("com2 : ");
            }
            break;
        case 4:
            printf("com3 : ");
            output_arr(com3,com3_round);
            if (i==0){
                judgment(Frist_card);
                frist_card_no = seach_frist_number(com3);
                clean_up_card(com3,frist_card_no,com3_round);
                com3_round--;
            }
            else{
                output_arr(com3,com3_round);
                com_card(com3,com3_round);
                printf("com3_R number : %d\n",com3_round);
                check_card = check(com3,com3_round);
                if(check_card == 1){
                    com_input(com3,com3_round);
                }
                else if(check_card == 0){
                    printf("I NEED CLOSE CARD\n");
                }
                //check_card = check(com3,com3_round);
                /*
                tmp = com_input(com3,com3_round);
                if (tmp == 0){
                    clean_up_card(com3,1,com3_round);
                }
                else{
                    clean_up_card(com3,tmp+1,com3_round);
                } */
                com3_round--;
            }
            break;
        }
        if (who == 4){
            who=1;
        }
        else{
            who++;
        }
        printf("Round : %d | space_up : %d down : %d | heart_up : %d down : %d | Diamond_up : %d down : %d | club_up : %d down : %d\n",i+1,blackspace[0],blackspace[1],redheart[0],redheart[1],blackdiamond[0],blackdiamond[1],redclub[0],redclub[1]);
        printf("-----------------------------------------------------------------------------\n");
        printf("| Spcae : ");
        output_arr(spade,13);
        printf("| Heart : ");
        output_arr(heart,13);
        printf("| Dimamond : ");
        output_arr(diamond,13);
        printf("| Club : ");
        output_arr(club,13);
    }
}
//com出牌 ok  一次只能出一張拉 幹 !!!!!!!!!!!!!!!!!!!!!!!!!! 
int com_input(int arr[],int a){
    int tmp,com_input_count=0,nocard=10;
    do
    {
        tmp = judgment(arr[com_input_count]);
        com_input_count++;
    } while (tmp == 0);
    clean_up_card(arr,com_input_count,a);
}
//玩家出牌  ok
void input(){ 
    int input,tmp_play,check_card;
    check_card = check(play,b);
    if (check_card == 1){
        do{
            for (int i = 0; i < b; i++){
                printf("No.%d : %d |",i+1,play[i]);
            }
            fflush(stdin);
            printf("\n Please Input Card Number : No.");
            scanf("%d",&input);
            tmp_play = judgment(play[input-1]);
        } while (input>b || input< 1 || tmp_play == 0);
        clean_up_card(play,input,b);
    }
    else if(check_card == 0){
        do{
            for (int i = 0; i < b; i++){
            printf("No.%d : %d |",i+1,play[i]);
            }
            fflush(stdin);
            printf("\n Please Input You Want to Close Card number : No.");
            scanf("%d",&input);
        } while (input>b || input < 1);
        clean_up_card(play,input,b);   
    }
}
//判斷+出牌了 blackspace[2]={7.7} redheart[2]={20.20} blackdiamond[2]={33.33} redclub[2]={46.46} 去看那些牌可以出 可以出迴傳1 不能回傳0  ok
int judgment(int j_a){ 
    int tmp;
    printf("intoJudgment_number:| %d |\n",j_a);
    if ((j_a == blackspace[0] || j_a == blackspace[1])&& j_a<14 ){
        spade[j_a-1] = j_a;
        if (j_a==blackspace[0]){
            blackspace[0]--;
            if (blackspace[0]==0){
                blackspace[0]=0;
            }
        }
        if (j_a==blackspace[1]){
            blackspace[1]++;
            if (blackspace[1]==14){
                blackspace[1]=0;
            }
        }
        return 1;
    }
    else if((j_a == redheart[0] || j_a == redheart[1])&&(j_a > 13 && j_a < 27)){  
        //redheart
        tmp = (j_a%13);
        if (tmp==0){
            tmp=13;
        }
        tmp--;
        heart[tmp] = j_a;
        if (j_a==redheart[0]){
            redheart[0]--;
            if (redheart[0]==13){
                redheart[0]=0;
            }
        }
        if (j_a==redheart[1]){
            redheart[1]++;
            if (redheart[1]==27){
                redheart[1]=0;
            }
        }
        return 1;
    }
    else if((j_a == blackdiamond[0] || j_a == blackdiamond[1]) && (j_a > 26 && j_a < 40)){
        //redclub
        tmp=(j_a%26);
        if (tmp==0){
            tmp=13;
        }
        tmp--;
        diamond[tmp] = j_a;
        if (j_a==blackdiamond[0]){
            blackdiamond[0]--;
            if (blackdiamond[0]==26){
                blackdiamond[0]=0;
            }
        }
        if (j_a==blackdiamond[1]){
            blackdiamond[1]++;
            if (blackdiamond[1]==40){
                blackdiamond[1]=0;
            }
        }
        return 1;
    }
    else if((j_a == redclub[0] || j_a == redclub[1]) && (j_a > 39 && j_a<53)){
        //redclub
        tmp=(j_a%39);
        if (tmp==0){
            tmp=13;
        }
        tmp--;
        club[tmp] = j_a;
        if (j_a==redclub[0]){
            redclub[0]--;
            if (redclub[0]==39){
                redclub[0]=0;
            }
        }
        if (j_a==redclub[1]){
            redclub[1]++;
            if (redclub[1]==53){
                redclub[1]=0;
            }
            
        }
        return 1;
    }
    return 0;
}
//第一張只能出7.20.33.46 尋找第一章牌是在第幾張卡ok
int seach_frist_number(int arr[]){
    for (int i = 0; i < 13; i++){
        if (arr[i] == Frist_card){
            return i+1;   
        }
    }
} 
//換成遞補ok   !!!!!!!!!!!!!!!!! 我要有它是哪張牌 已及他的陣列 為0 後面清
void clean_up_card(int arr[] , int no , int round){
    round = round - 1;
    arr[no-1] = 0;
    for (int i = no-1; i < round; i++){
        arr[i] = arr[i+1];
        if (arr[i]==0){
            break;
        }
    }
    arr[round] = 0;
}
//檢查手中的牌是不是可以出ok
int check(int arr[],int b){
    for (int  i = 0; i < b; i++)
    {
        if(arr[i] == blackspace[0] || arr[i] == blackspace[1] || arr[i] == redheart[0] || arr[i] == redheart[1] ||arr[i] == blackdiamond[0]||arr[i] == blackdiamond[1]||arr[i] == redclub[0]||arr[i] == redclub[1]){
            return 1;
        }
    }
    return 0;
    
}
//列印 ok
void output_arr(int arr[] , int n){
    for (int i = 0; i < n; i++)
    {   /*
        if (arr[i]==0){
            printf(" ");
        }else if (arr[i]<=13){
            printf("| Spade %d |",arr[i]);
        }else if(arr[i]<=26){
            printf("| heart %d |",arr[i]-13);
        }else if(arr[i]<=39){
            printf("| diamond %d |",arr[i]-26);
        }else if(arr[i]<=52){
            printf("| club %d |",arr[i]-39);
        }*/
        
        printf("| %d |",arr[i]);
    }
    printf("\n");        
}



//怎麼找出最低的蓋排限度 先不求最好
void seach_close_card(int arr[],int n){
    int tmp;
    for (int i = 0; i <n ; i++){
        tmp = arr[i]%13;
        if (tmp == 0){
            tmp = 13;
        }
    }
}
/*
//判斷電腦卡別
void com_card(int arr[],int a){
    int black_S_D=0 , black_S_U=0,red_H_U=0,red_H_D=0,black_D_D=0,black_D_U=0,red_C_U=0,red_C_D=0;
    for (int i = 0; i < a; i++)
    {
        if (arr[i]<blackspace[0]){
            black_S_D++;
        }
        else if (arr[i]>blackspace[1] && arr[i]<14)
        {
            black_S_U++;
        }
        else if (arr[i]<redheart[0])
        {
            red_H_D++;
        }
        else if (arr[i]>redheart[1] && arr[i]<27)
        {
            red_H_U++;
        }
        else if (arr[i]<blackdiamond[0])
        {
            black_D_D++;
        }
        else if (arr[i]>blackdiamond[1] && arr[i]<40)
        {
            black_D_U++;
        }
        else if (arr[i]<redclub[0])
        {
            red_C_D++;
        }
        else if (arr[i]>redclub[1] && arr[i]<53)
        {
            red_C_U++;
        }        
    }
    printf("SD : %d | SU : %d | HD : %d | HU : %d | DD : %d | DU :%d | CD : %d | CU : %d \n",black_S_D,black_S_U,red_H_D,red_H_U,black_D_D,black_D_U,red_C_D,red_C_U);

}*/


//選單 看要不要在謝其他遊戲
//遊戲目前是可以跑了 但電腦的蓋牌機制要在修改一下 不燃到後面都在蓋牌 遊戲沒辦法繼續下去
//顯示的部分修改一下 不要麼亂 用一下cls
//紀錄誰蓋了什麼牌


// 寫完後 再去是寫一個用指標 動態陣列 的版本 
//cls會影像到我的質 待解