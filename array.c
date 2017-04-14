//
// Created by xm on 2016/12/19.
//
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define SCORE_SIZE 30

typedef struct Prop{
    char* name;
    double price;
    int stoc;
} Props;

int main(){
    Props* p = malloc(sizeof(Props));
    p->name = "你好";
    p->price = 22.0;
    printf("%s,%d",p->name,p->price);
    getch();
    return 0;
}

//int main(){
//    int scores[] = {67,33,92,86,79,100};
//    int len = sizeof(scores)/sizeof(int);
//    int i ,j;
//    /*// 冒泡排序
//    for(i=0;i<len-1;i++){
//        for(j=0;j<len-i-1;j++){
//            if(scores[j] < scores[j+1]){
//                int tmp = scores[j];
//                scores[j]=scores[j+1];
//                scores[j+1] = tmp;
//            }
//        }
//    }*/
//    // 插入排序
//    for( i=1;i<len;i++){
//        for(j=i;j>0;j--){
//            if(scores[j]<scores[j-1]){
//                int temp=scores[j];
//                scores[j]=scores[j-1];
//                scores[j-1]=temp;
//            }else{
//                break;
//            }
//        }
//    }
//
//    // 输出
//    for(i=0;i<len;i++){
//        printf("%d\t",scores[i]);
//    }
//    getch();
//    return 0;
//}


int main_(){
    // 声明分数数组
    int scorearr[SCORE_SIZE] ; // = {652,706,704}
    char provinces[SCORE_SIZE][50] ;
    // 将数组中的数据用0填充
    memset(scorearr,0, sizeof(scorearr));
    memset(provinces,0,sizeof(provinces));
    // 添加分数, 数据初始化
    scorearr[0] = 652; // 湖北
    scorearr[1] = 706; // 河北
    scorearr[2] = 704; // 贵州
    // {"湖北","河北","贵州"}
//    provinces[0] = "湖北";
//    provinces[1] = "河北";
//    provinces[2] = "贵州";
    strcpy(provinces[0],"湖北");
    strcpy(provinces[1],"河北");
    strcpy(provinces[2],"贵州");
    // 菜单
    char  menu[][200]={
            " 请输入你的选择\n",
            "1. 查看所有分数\n",
            "2. 添加状元分数\n",
            "3. 指定编号状元分数添加\n",
            "4. 查询指定省份状元分数\n",
            "5. 修改指定省份/编号状元分数\n",
            "6. 删除指定省份/编号状元分数\n",
            "7. 状元榜（个数、总分、平均分）\n",
            "8. 退出\n"
    };
    // 是否退出程序
    int exit_app = 0;
    while(!exit_app){
        system("cls");
        // 展示菜单信息
        int i;
        for(i=0;i<9;i++){
            printf("%s",menu[i]);
        }
        // 接收用户的键盘输入
        int choice = getch();
        system("cls");
        switch(choice){
            case '1': // 查看所有分数
                printf("序号\t省份\t分数\n");
                int r_index;
                for(r_index=0;r_index<SCORE_SIZE;r_index++){
                    if(scorearr[r_index] > 0){
                        printf("%d\t%s\t%d\n",r_index+1,provinces[r_index],scorearr[r_index]);
                    }
                }
                printf("任意键退出");
                getch();
                break;
            case '2': // 添加状元分数，在第一个
                while(1){
                    // 腾空第一个位置
                    for(i = SCORE_SIZE-1;i>1;i--){
                        scorearr[i] = scorearr[i-1];
                        //provinces[i] = provinces[i-1];
                        strcpy(provinces[i],provinces[i-1]);
                    }
                    printf("输入分数:");
                    scanf("%d",&scorearr[0]); // 接收分数
                    printf("输入省份名称:");
                    scanf("%s",&provinces[0]);
                    printf("继续添加?(y/n):");
                    if('y'!=getch()){
                        break;
                    }
                }
                break;
            case '3': // 指定编号添加状元分数
                while(1){
                    printf("输入添加位置:");
                    int index;
                    scanf("%d",&index);
                    index--;
                    if(index > SCORE_SIZE -1 || index < 0){
                        printf("序号不存在. 请重新输入。任意键继续.");
                        getch();
                        system("cls");
                    }
                    // 腾空第一个位置
                    for(i = SCORE_SIZE-1;i>=index;i--){
                        scorearr[i] = scorearr[i-1];
                        // provinces[i] = provinces[i-1];
                        strcpy(provinces[i],provinces[i-1]);
                    }
                    printf("输入分数:");
                    scanf("%d",&scorearr[index]); // 接收分数
                    printf("输入省份名称:");
                    scanf("%s",&provinces[index]);
                    printf("继续添加?(y/n):");
                    if('y'!=getch()){
                        break;
                    }
                }
                break;
            case '4': // 查询指定编号、省份状元分数
                while(1){
                    printf("请输入编号.(省份查询输入0)");
                    int read_index;
                    scanf("%d",&read_index);
                    char province_name[50];
                    if(!read_index){
                        printf("请输入省份名称:");
                        scanf("%s",&province_name);
                        for(i=0;i<SCORE_SIZE;i++){
                            if(!strcmp(provinces[i],province_name)){
                                read_index=i;
                                break;
                            }
                        }
                        if(i == SCORE_SIZE){
                            printf("找不到输入省份,任意键继续");
                            getch();
                            system("cls");
                        }
                    }else{
                        read_index--;
                        if(read_index > SCORE_SIZE -1 || read_index < 0){
                            printf("序号不存在. 请重新输入。任意键继续.");
                            getch();
                            system("cls");
                        }
                    }
                    printf("序号\t省份\t分数\n");
                    printf("%d\t%s\t%d\n",read_index+1,provinces[read_index],scorearr[read_index]);
                    printf("继续查找?(y/n):");
                    if('y'!=getch()){
                        break;
                    }
                }
                break;
            case '5': // 修改指定编号、省份状元分数
                while(1){
                    printf("请输入编号.(省份查询输入0)");
                    int read_index;
                    scanf("%d",&read_index);
                    char province_name[50];
                    if(!read_index){
                        printf("请输入省份名称:");
                        scanf("%s",&province_name);
                        for(i=0;i<SCORE_SIZE;i++){
                            if(!strcmp(provinces[i],province_name)){
                                read_index=i;
                                break;
                            }
                        }
                        if(i == SCORE_SIZE){
                            printf("找不到输入省份,任意键继续");
                            getch();
                            system("cls");
                        }
                    }else{
                        read_index--;
                        if(read_index > SCORE_SIZE -1 || read_index < 0){
                            printf("序号不存在. 请重新输入。任意键继续.");
                            getch();
                            system("cls");
                        }
                    }
                    printf("输入分数:");
                    scanf("%d",&scorearr[read_index]); // 接收分数

                    printf("修改成功，继续修改?(y/n):");
                    if('y'!=getch()){
                        break;
                    }
                }
                break;
            case '6': // 删除指定编号、省份状元分数
                while(1){
                    printf("请输入编号.(省份查询输入0)");
                    int del_index;
                    scanf("%d",&del_index);
                    char province_name[50];
                    if(!del_index){
                        printf("请输入省份名称:");
                        scanf("%s",&province_name);
                        for(i=0;i<SCORE_SIZE;i++){
                            if(!strcmp(provinces[i],province_name)){
                                del_index=i;
                                break;
                            }
                        }
                        if(i == SCORE_SIZE){
                            printf("找不到输入省份,任意键继续");
                            getch();
                            system("cls");
                        }
                    }else{
                        del_index--;
                        if(del_index > SCORE_SIZE -1 || del_index < 0){
                            printf("序号不存在. 请重新输入。任意键继续.");
                            getch();
                            system("cls");
                        }
                    }
                    // 清空数据
                    memset(provinces[del_index],0,sizeof(provinces[del_index]));
                    scorearr[del_index] = 0;
                    printf("继续删除?(y/n):");
                    if('y'!=getch()){
                        break;
                    }
                }
                break;
            case '7': // 状元榜（个数、总分、平均分）
                printf("\n");
                int arr_len = 0; // 榜单人数
                double sum_score = 0; // 总分
                double avg_score = 0; // 平均分
                for(i=0;i<SCORE_SIZE;i++){
                    if(scorearr[i]>0){
                        arr_len++;
                        sum_score+=scorearr[i];
                    }
                }
                avg_score = sum_score/arr_len;
                printf("榜单人数\t总分\t平均分\n");
                printf("%d\t\t%.0lf\t%.2lf\n",arr_len,sum_score,avg_score);
                printf("任意键继续:");
                getch();
                break;
            case '8':
                exit_app=1;
                break;
            default:
                printf("选项无效，任意键继续\n");
                getch();
                break;
        }
    }
    return 0;
}
