#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <windows.h>
#include <pthread.h>
#include <conio.h>
/**
 * 定义基础血量
 */
#define BASE_HP 2000
/**
 * 技能个数
 */
#define SKILL_SIZE 11
/**
 * 接收用户输入的线程
 * @param th
 * @return
 */
void* demoth(void* th){
    char* in = (char*)th;
    while(1){
        char v = *in;
        if(!v){
            fflush(stdin);
            *in = getch();
        }else if(v==-1){
            break;
        }
        usleep(50*1000);
    }
    return (void*)0;
}
/***
 * 入口函数
 * @return
 */
int main() {
    // 数据
    // 角色名称
    char names [][50] = {"八神庵","草剃京","K","阿修·克里门森/艾森·古立逊","泰利·波格","坂崎獠","K9999","矢吹真吾","莉安娜","神乐千鹤"};
    //  技能名称
    char skill_names [][50] = {"空间集体屠杀","负的起源","神圣之剑、地面","神圣之剑、天空","不意打","夙刃","佰合折","狂暴之血","气功波","火焰冲拳","碎石踢"};
    // 技能最小攻击值
    int skill_min_power[]={100,120,90,130,110,170,100,88,99,60,130};
    // 技能最大攻击值
    int skill_max_power[]={260,220,140,150,140,250,200,190,260,180,260};
    // 技能组合键
    char skill_keys[][20] = {"include","stdio.h","int","main","printf","return","short","long","float","double","char"};
    // 欢迎界面文字
    char wellcomData[][1000] = {"日照大神须佐之男来到人间。",
                               "看到一个漂亮的女子在河中哭泣，被当做献给八歧大蛇的祭品，须佐之男救下了这个女子（奇稻田姬后来转世 草稚京的女友小雪）须佐之男爱上了奇稻田姬，并杀死了八歧大蛇，从它的尾部取得了神器草稚剑。",
                               "须佐之男跟奇稻田姬相爱了 后来须佐之男的后人 分为“草稚”、“八尺琼”、“八咫”三大家族，他们共同守护着三神器【八神(钩子),草稚(剑),神乐(镜子)】封印八歧大蛇",
                               "八神的祖先八尺琼苍月爱上了一个城主的女儿，那个女孩也爱上八尺琼苍月，可是草稚京的祖先草稚旭日也爱上了公主。于是城主决定让他们二人打一场 ，谁赢了就可以作他的女婿。八尺琼苍月念及草稚旭日是兄弟 不忍心下重手，结果草稚旭日太爱那位小姐了。把八尺琼苍月打成重伤，城主决定让草稚旭日当自己的女婿。八尺琼苍月对草稚旭日说从今天起我们不再是兄弟。",
                               "为了报仇八尺琼苍月决定借用一点大蛇的力量，结果被草稚旭日报告了城主，城主大怒把八尺琼苍月关了起来。在监狱中八尺琼苍月无时不刻都在想念着公主，八歧大蛇的残魂诱惑八尺琼苍月让他解开封印，它可以给他力量报仇把公主抢过来，还让八尺琼苍月看到了公主被草稚旭日虐待的景象，八尺琼苍月再也无法容忍了，解开了大蛇的封印，从此改姓为八神！",
                               "八神苍月出去后见到了病重的奄奄一息的公主，公主对他说：苍月，我爱的只有你，然后便挂掉了。草稚旭日这时对他说，她心里一直都在爱你，你不该解开封印的，让我们一起再把大蛇封印吧，八神苍月同意了草稚旭日说的 ，再次结合三神器家族的力量把大蛇封印。而草稚与八神两家族的宿怨从此结下了。",
                               "后来八神庵的父亲八神月败在了草稚京的父亲草稚柴舟的手下挂掉了。八神庵跟草稚京可以说是宿敌也可以说是彼此最了解对方的人。",
                               "再后来拳皇大赛八神被大蛇四天王中的暴风杰尼兹唤醒了大神之血，暴走了，还是草稚京一拳把他轰飞 唤醒他。最后草稚京，八神庵，神乐千鹤三神器家族一起把借用克里斯身体为传媒复活的大蛇再次封印起来。之后重伤的草稚京被N.E.S.T.S组织的人带走 利用草稚京赤炎的体质 复制了很多冒牌的草稚京，其间八神还去N.E.S.T.S组织闹了好多次",
                               "然后主角已经不再停留在草稚京和八神庵，后来越来越多的新人加入。利用草稚京 制造出来的K 来自法国的男子ASH。草稚京的女友是小雪、八神的女友是歌手谷间菊理，后来挂掉了。八神为她作了首歌《夕阳と月》",
                               };

    // 存档
    // 存档名称
    char record_names[10][50];
    // 选择角色名称
    char record_select_role_names[10][50];
    // 挑战角色名称
    char record_attack_role_names[10][50];
    // 游戏分数
    int record_score [10];
    // 游戏结果
    short record_result[10];
    // 存档时间
    char record_times[10][50];
    // 存档个数
    int record_size = 0;

    // 菜单
    // 主菜单
    char menu_home[][100] = {"\n\n\n\t\t\t+-----------------------------------------------------------------------+",
                            "\t\t\t|\t\t\t欢迎来到C语言版拳皇。请选择\t\t\t|",
                            "\t\t\t|\t\t\t1.\t开始新游戏\t\t\t\t|",
                            "\t\t\t|\t\t\t2.\t档案管理\t\t\t\t|",
                            "\t\t\t|\t\t\t3.\t退出\t\t\t\t\t|",
                            "\t\t\t|\t\t\t \t\t\t\t\t\t|",
                            "\t\t\t+-----------------------------------------------------------------------+"
                            };
    // 游戏菜单
    char menu_pay[][100] = {"\n\n\n\t\t\t+-----------------------------------------------------------------------+",
                             "\t\t\t|\t\t\t\t角色选择\t\t\t\t|",
                            "\t\t\t|\t\t\t1.\t八神庵\t\t\t\t\t|",
                            "\t\t\t|\t\t\t2.\t草剃京\t\t\t\t\t|",
                            "\t\t\t|\t\t\t3.\tK\t\t\t\t\t|",
                            "\t\t\t|\t\t\t4.\t阿修·克里门森/艾森·古立逊\t\t|",
                            "\t\t\t|\t\t\t5.\t泰利·波格\t\t\t\t|",
                            "\t\t\t|\t\t\t6.\t坂崎獠\t\t\t\t\t|",
                            "\t\t\t|\t\t\t7.\tK9999\t\t\t\t\t|",
                            "\t\t\t|\t\t\t8.\t矢吹真吾\t\t\t\t|",
                            "\t\t\t|\t\t\t9.\t莉安娜\t\t\t\t\t|",
                            "\t\t\t|\t\t\ta.\t神乐千鹤\t\t\t\t|",
                            "\t\t\t|\t\t\tb.\t返回  \t\t\t\t\t|",
                            "\t\t\t|\t\t\t \t\t\t\t\t\t|",
                            "\t\t\t+-----------------------------------------------------------------------+"
                            };
    // 存档菜单
    char menu_record[][100] = {"\n\n\n\t\t\t+-----------------------------------------------------------------------+",
                               "\t\t\t|\t\t\t\t存档管理\t\t\t\t|",
                               "\t\t\t|\t\t\t1.\t查看\t\t\t\t\t|",
                               "\t\t\t|\t\t\t2.\t删除\t\t\t\t\t|",
                               "\t\t\t|\t\t\t3.\t改名\t\t\t\t\t|",
                               "\t\t\t|\t\t\t4.\t排行\t\t\t\t\t|",
                               "\t\t\t|\t\t\t5.\t退出\t\t\t\t\t|",
                               "\t\t\t|\t\t\t\t\t\t\t\t\t|",
                               "\t\t\t+-----------------------------------------------------------------------+"
                                };

    // 随机数种子
    srand(time(0));

    // 游戏启动，展示剧情
    int i ,j ;
    for(i = 0;i<9;i++){
        char info [1000];
        strcpy(info,wellcomData[i]);
        int size = strlen(info);
        printf("\t");
        for(j=0;j<size;j++){
            printf("%c",info[j]);
            Sleep(1);
        }
        printf("\n\n");
        Sleep(500);
    }
    // 用户选择标记
    char choice;
    // 退出程序标记
    short exit_game;
    // 进入程序流程
    while(1){
        exit_game = 0;
        system("cls");
        // 展示主菜单
        for(i=0;i<7;i++){
            printf("%s\n",menu_home[i]);
        }
        // 接收用户选择
        choice = getch();
        switch(choice){
            case '1':
                    while(1){
                        // 玩家选择的角色名称
                        char pay_role_name[50];
                        // 玩家要挑战的角色名称
                        char pay_attack_name[50];
                        short to_main = 0;
                        // 用户选择的轮数
                        int round;
                        for(round=0;round<2;round++){
                            system("cls");
                            // 展示游戏菜单
                            for(i=0;i<16;i++){
                                printf("%s\n",menu_pay[i]);
                            }
                            //  接收用户选择
                            choice = getch();
                            int cindex;
                            if(choice >= 49 && choice <= 57 ){
                                cindex = choice - 49;
                            }else if('a'==choice){
                                cindex = choice - 88;
                            }else if('b'==choice){
                                to_main = 1;
                                break;
                            }else{
                                printf("没有这个选项,有效输入项为(1 - 9 或者 a 、b)...");
                            }
                            if(round == 0){
                                strcpy(pay_role_name,names[cindex]);
                                // 显示用户的选择
                                printf("你选择的角色是:%s.请继续选择想要挑战的角色。任意键继续。",pay_role_name);

                            }else{
                                strcpy(pay_attack_name,names[cindex]);
                                printf("你要挑战的角色是:%s.输入任意键开查看技能说明。\n\n\n",pay_attack_name);
                            }
                            getch();
                        }
                        // 回到主界面
                        if(to_main){
                            break;
                        }
                        system("cls");
                        printf("\n普通攻击:每次产生60-80点攻击力。大技能的攻击力更高哦。\n");
                        printf("技能\t\t 技能组合键\n\n");
                        // 提示信息
                        for(i=0;i<SKILL_SIZE;i++){
                            printf("%s\t\t%s\n",skill_names[i],skill_keys[i]);
                        }
                        printf("\n\n任意键开始游戏!");
                        getch();
                        // 玩家的分数
                        int score_pay = 0;
                        // 开始游戏
                        int role_hp,user_hp;
                        // 清屏
                        system("cls");
                        // 线程变量
                        pthread_t  th;
                        // 输入接收变量
                        char input = 0;
                        // 初始化用户和角色的血量
                        user_hp = role_hp = BASE_HP;
                        // 开启输入接收线程
                        int thCode = pthread_create(&th,NULL,demoth,(void*)&input);
                        // 玩家的组合键
                        char player_input_keys [20];
                        // 玩家输入的长度
                        int player_input_size = 0;
                        // 玩家的攻击力
                        int player_skill_power;
                        //  NPC的攻击力
                        int npc_skill_power;
                        // 攻击的计算轮回数
                        int attack_count;
                        while(user_hp  && role_hp){
                            attack_count++;
                            // 接收玩家的输入, 并且计算攻击力
                            if(input){
                                int attact_succes = 0;
                                if(input != 'k'){
                                    // 用户已有输入的长度
                                    int input_key_len = strlen(player_input_keys);
                                    if(input_key_len >= sizeof(player_input_keys)/sizeof(char)-1){
                                        // 进行一次全体数组左移操作
                                        int input_arr_len;
                                        for(input_arr_len = 0;input_arr_len < sizeof(player_input_keys)/sizeof(char)-1;input_arr_len++){
                                            player_input_keys[input_arr_len] = player_input_keys[input_arr_len+1];
                                        }
                                        player_input_keys[input_arr_len]=0;
                                        player_input_size-=1;
                                    }
                                    player_input_keys[player_input_size++] = input;
                                    player_input_keys[player_input_size] = 0;
                                    int key_index;
                                    for(key_index=0;key_index<SKILL_SIZE;key_index++){
                                        // 获取当前关键字长度
                                        int skill_key_len = strlen(skill_keys[key_index]);
                                        // 逆向读取输入内容,然后比较
                                        char nowKeyGet[20];

                                        // 用户输入没有达到标准键长度。执行下一轮标准键比较
                                        if(input_key_len < skill_key_len){
                                            continue;
                                        }
                                        // 逆向读取用户的输入
                                        int now_read_index;
                                        for(now_read_index=0;now_read_index < skill_key_len; now_read_index++){
                                            nowKeyGet[now_read_index] = player_input_keys[input_key_len-(skill_key_len - now_read_index )];
                                        }
                                        nowKeyGet[now_read_index] = 0;
                                        if(!strcmp(nowKeyGet,skill_keys[key_index])){
                                            break;
                                        }
                                    }
                                    if(key_index < SKILL_SIZE){
                                        attact_succes = 1;
                                        // 计算玩家产生的攻击力
                                        player_skill_power = rand()%(skill_max_power[key_index]-skill_min_power[key_index])+skill_min_power[key_index];
                                        printf("你发出了大招:%s\n",skill_names[key_index]);
                                        printf("产生了%d的攻击力.\n",player_skill_power);
                                        // 计算得分
                                        score_pay+= player_skill_power * 0.03;
                                    }
                                }else{
                                    attact_succes = 1;
                                    player_skill_power = rand()%20 + 60;
                                    printf("你发出了普通攻击.\n");
                                    printf("产生了%d的攻击力.\n",player_skill_power);
                                    // 计算得分
                                    score_pay+= player_skill_power * 0.03;
                                }
                                if(attact_succes){
                                    // NPC 血量计算
                                    role_hp -= player_skill_power;
                                    role_hp = role_hp < 0 ? 0:role_hp;
                                    printf("%s当前的血量为:%d\n",pay_attack_name,role_hp);
                                    printf("------------------------------------------\n\n");
                                    attact_succes = 0;
                                }
                                input = 0;
                            }

                            // 计算NPC的攻击力
                            if(!(attack_count % 10)){
                                int npc_skill_index = rand()%SKILL_SIZE;
                                if(rand()%4==3){
                                    npc_skill_power = rand()%20 + 60;
                                    printf("%s发出了普通攻击.\n",pay_attack_name);
                                }else{
                                    npc_skill_power = rand()%(skill_max_power[npc_skill_index]-skill_min_power[npc_skill_index])+skill_min_power[npc_skill_index];
                                    printf("%s发出了大招:%s\n",pay_attack_name,skill_names[npc_skill_index]);
                                }
                                printf("产生了%d的攻击力.\n",npc_skill_power);
                                // 血量计算
                                user_hp -= npc_skill_power;
                                user_hp = user_hp < 0 ? 0:user_hp;
                                printf("你当前的血量为:%d\n\n",user_hp);
                            }
                            Sleep(100);
                        }
                        // 线程退出标识位
                        input = -1;
                        // 游戏结束后中断线程
                        pthread_cancel(th);
                        printf("游戏结束!");
                        if(!user_hp){
                            printf("%s干掉你了。本轮游戏失败!\n",pay_attack_name);
                            score_pay+=5;
                        }else if(!role_hp){
                            printf("你干掉了%s.恭喜你。\n\n",pay_attack_name);
                            score_pay+=30;
                        }
                        // 记录存档
                        if(record_size==10){
                            printf("存档已满，将会覆盖最新存档...");
                            record_size--;
                        }
                        // 名称
                        char rec_name[50];
                        long long t = time(0); // 以毫秒值记录当前时间
                        sprintf(rec_name,"rec_%lld",t);
                        strcpy(record_names[record_size],rec_name);
                        // 选择角色名
                        strcpy(record_select_role_names[record_size],pay_role_name);
                        // 攻击角色名
                        strcpy(record_attack_role_names[record_size],pay_attack_name);
                        //  分数
                        record_score[record_size] = score_pay;
                        //  结果
                        record_result[record_size] = user_hp > 0 ;
                        //  记录时间
                        time_t  now;
                        struct tm* info;
                        time(&now);
                        info = localtime(&now);
                        sprintf(record_times[record_size],"%d-%d-%d %d:%d:%d",info->tm_year+1900,info->tm_mon,info->tm_mday,info->tm_hour,info->tm_min,info->tm_sec);
                        // 记录增长
                        record_size++;
                        fflush(stdin);
                        sleep(2);
                        // 判断是否继续游戏的变量
                        char continueGame = 0;
                        printf("继续游戏?(y/n)");
                        scanf("%c",&continueGame);
                        if(continueGame!='y'){
                            break;
                        }
                    }
                break;
            case '2':
                while(1){
                    // 存档管理
                    system("cls");
                    // 展示存档菜单
                    for(i=0;i<9;i++){
                        printf("%s\n",menu_record[i]);
                    }
                    // 接收用户选择
                    choice = getch();
                    int exit_record = 0;
                    switch(choice){
                        case '1': // 查看
                            system("cls");
                            if(record_size){
                                printf("编号\t名称\t\t选择角色\t\t攻击角色\t\t分数\t结果\t时间\n\n");
                                for(i=record_size-1;i>=0;i--){
                                    printf("%d\t%s\t%s\t\t%s\t\t%d\t%s\t%s\n",(record_size-i),record_names[i],record_select_role_names[i],record_attack_role_names[i],
                                           record_score[i],record_result[i]?"胜利":"失败",record_times[i]);
                                }
                            }else{
                                printf("还没有你的游戏记录呢。要不去干一盘..\n");
                            }
                            printf("任意键继续");
                            getch();
                            break;
                        case '2': // 删除
                            while(1){
                                system("cls");
                                printf("输入想要删除的记录编号:");
                                int del_record;
                                scanf("%d",&del_record);
                                if(--del_record < record_size && del_record >= 0){
                                    for(i=del_record;i<record_size-1;i++){
                                        strcpy(record_names[i],record_names[i+1]);
                                        strcpy(record_select_role_names[i],record_select_role_names[i+1]);
                                        strcpy(record_attack_role_names[i],record_attack_role_names[i+1]);
                                        record_score[i] = record_score[i+1];
                                        record_result[i] = record_result[i+1];
                                        strcpy(record_times[i],record_times[i+1]);
                                    }
                                    printf("已经删了。接着删(y/n)?");
                                }else{
                                    printf("编号没整对。重新来(y)/回去看一下(n)");
                                }
                                if('y'!=getch()){
                                    break;
                                }
                            }
                            break;
                        case '3': // 改名
                            while(1){
                                system("cls");
                                printf("输入想要修改的记录编号:");
                                int update_record;
                                scanf("%d",&update_record);
                                if(--update_record < record_size && update_record >= 0){
                                    printf("写上你想要的名字:");
                                    scanf("%s",&record_names[update_record]);
                                    printf("已经改好了。接着改(y/n)?");
                                }else{
                                    printf("编号没整对。重新来(y)/回去看一下(n)");
                                }
                                if('y'!=getch()){
                                    break;
                                }
                            }
                            break;
                        case '4': // 排行
                            system("cls");
                            // 声明序号数组
                            int record_sort_index[10],j;
                            // 初始化序号数组
                            for(i=0;i<record_size;i++){
                                record_sort_index[i]=i;
                            }
                            // 按照分数从高到低排序。移动序号数组
                            for(i=0;i<record_size-1;i++){
                                for(j=0;j<record_size-i-1;j++){
                                    if(record_score[i] < record_score[i+1]){
                                        int tmp = record_sort_index[i];
                                        record_sort_index[i] = record_sort_index[i+1];
                                        record_sort_index[i+1] = tmp;
                                    }
                                }
                            }
                            // 输出标题
                            printf("编号\t名称\t选择角色\t\t攻击角色\t\t分数\t结果\t时间\n\n");
                            // 按照序号进行输出
                            for(i=0;i<record_size;i++){
                                int index = record_sort_index[i];
                                printf("%d\t%s\t%s\t\t%s\t\t%d\t%s\t%s\n",(i+1),record_names[index],record_select_role_names[index],
                                       record_attack_role_names[index],record_score[index],record_result[index]?"胜利":"失败",
                                       record_times[index]);
                            }
                            printf("输入任意键继续!");
                            getch();
                            break;
                        case '5': // 退出
                            exit_record = 1;
                            break;
                        default:
                            printf("\n必须输入正确选项(可选项为1-5)\n");
                            break;
                    }
                    if(exit_record){
                        break;
                    }
                }
                break;
            case '3':
                exit_game = 1;
                break;
            default:
                printf("\n\n\n不要方。主菜单的选择只有1、2、3哦。\n");
                break;
        }
        if(exit_game){
            printf("游戏结束..\n");
            Sleep(2000);
            break;
        }
    }
    return 0;
}