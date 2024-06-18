#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // 使用boolean值
#include <time.h>   /* 時間相關函數 */

// 清理輸入緩衝區的函數
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// 隨機下棋
int randomPos(int min, int max)
{
	/* 設定亂數種子 */
    srand( time(NULL) );
    /* 指定亂數範圍 */
    /* 產生亂數 */
    int x = rand() % (max - min + 1) + min;
    return x;
}

void printTrophy() {
    printf("       ___________\n");
    printf("      '._==_==_=_.'\n");
    printf("      .-\\:      /-.\n");
    printf("     | (|:.     |) |\n");
    printf("      '-|:.     |-'\n");
    printf("        \\::.    /\n");
    printf("         '::. .'\n");
    printf("           ) (\n");
    printf("         _.' '._\n");
    printf("        `\"\"\"\"\"\"\"`\n");
}

// 印出該回合結果 
void roundResult(char checkerboard[])
{
    for (int i = 0; i < 9; i++)
    {
        printf("%c ", checkerboard[i]);
        if (i%3 == 2)
        {
            printf("\n");
        }
    }
    printf("\n");
    return;
}

// 遊戲規則介紹
void rules()
{
    getchar();
    printf("介紹遊戲規則\n");
    getchar();
    printf("遊戲棋盤如下：\n");
    printf("1 2 3\n");
    printf("4 5 6\n");
    printf("7 8 9\n");
    getchar();
    printf("輸入9宮格的位置即可劃下圈叉：\n");
    getchar();
    printf("ex: O請輸入: 5\n");
    getchar();
    printf("1 2 3\n");
    printf("4 O 6\n");
    printf("7 8 9\n");
    getchar();
    printf("ex: X請輸入: 6\n");
    getchar();
    printf("1 2 3\n");
    printf("4 O X\n");
    printf("7 8 9\n");
    
}

// 判斷勝利
bool over(char checkerboard[])
{
    // 列 
    for (int i = 0; i < 3; i++)
    {
        if (checkerboard[i*3] == checkerboard[i*3+1] && checkerboard[i*3+1] == checkerboard[i*3+2])
        {
            return true;
        }
    }
    // 行 
    for (int i = 0; i < 3; i++)
    {
        if (checkerboard[i] == checkerboard[i+3] && checkerboard[i+3] == checkerboard[i+6])
        {
            return true;
        }
    }
    // 對角線 
    if (checkerboard[0] == checkerboard[4] && checkerboard[4] == checkerboard[8])
    {
        return true;
    }
    if (checkerboard[2] == checkerboard[4] && checkerboard[4] == checkerboard[6])
    {
        return true;
    }
    return false;
}

// 判別ai是否要輸了, 符合條件傳防守步 
int aboutToLose(char checkerboard[], char aiSymbol, char playerSymbol)
{
	int defenseStep = 10; // 防守一步
	// 列
    for (int i = 0; i < 3; i++)
    {
    	// 檢查同一列的所有可能 
    	for (int j = 0; j < 3; j++)
    	{
    		// 假設尚未被下
    		if (checkerboard[i*3+(j%3)] != aiSymbol && checkerboard[i*3+(j%3)] != playerSymbol)  
    		{
    			// 並且其餘兩個已是玩家的符號 
    			if (checkerboard[i*3+(j+1)%3] == playerSymbol && checkerboard[i*3+(j+2)%3] == playerSymbol)
    			{
    				defenseStep = i*3+(j%3); // 將防守步傳回去 
				}
			}
		}
    }
    // 行 
    for (int i = 0; i < 3; i++)
    {
    	// 檢查同一行的所有可能 
    	for (int j = 0; j < 3; j++)
    	{
    		// 假設尚未被下
    		if (checkerboard[i+(j%3)*3] != aiSymbol && checkerboard[i+(j%3)*3] != playerSymbol)  
    		{
    			// 並且其餘兩個已是玩家的符號 
    			if (checkerboard[i+((j+1)%3)*3] == playerSymbol && checkerboard[i+((j+2)%3)*3] == playerSymbol)
    			{
    				defenseStep = i+(j%3)*3; // 將防守步傳回去 
				}
			}
		}
    }
    // 左上右下對角線
    for (int i = 0; i < 3; i++)
    {
    	if (checkerboard[0+(i)%3*4] != aiSymbol && checkerboard[0+(i)%3*4] != playerSymbol)
    	{
    		if (checkerboard[0+((i+1)%3)*4] == playerSymbol && checkerboard[0+((i+2)%3)*4] == playerSymbol)
    		{
    			defenseStep = 0+(i)%3*4;
			}
		}
	}
	//左下右上對角線 
    for (int i = 0; i < 3; i++)
    {
    	if (checkerboard[2+(i)%3*2] != aiSymbol && checkerboard[2+(i)%3*2] != playerSymbol)
    	{
    		if (checkerboard[2+((i+1)%3)*2] == playerSymbol && checkerboard[2+((i+2)%3)*2] == playerSymbol)
    		{
    			defenseStep =  2+(i)%3*2;
			}
		}
	}
	return defenseStep;
}

// 判別AI是否要贏了, 符合條件傳勝利步 
int aboutToWin(char checkerboard[], char aiSymbol, char playerSymbol)
{
	int finalStep = 10; // 勝利一步
	// 列
    for (int i = 0; i < 3; i++)
    {
    	// 檢查同一列的所有可能 
    	for (int j = 0; j < 3; j++)
    	{
    		// 假設尚未被下
    		if (checkerboard[i*3+(j%3)] != aiSymbol && checkerboard[i*3+(j%3)] != playerSymbol)  
    		{
    			// 並且其餘兩個已是ai的符號 
    			if (checkerboard[i*3+(j+1)%3] == aiSymbol && checkerboard[i*3+(j+2)%3] == aiSymbol)
    			{
    				finalStep = i*3+(j%3); // 將勝利的最後一步傳回去 
				}
			}
		}
    }
    // 行 
    for (int i = 0; i < 3; i++)
    {
    	// 檢查同一行的所有可能 
    	for (int j = 0; j < 3; j++)
    	{
    		// 假設尚未被下
    		if (checkerboard[i+(j%3)*3] != aiSymbol && checkerboard[i+(j%3)*3] != playerSymbol)  
    		{
    			// 並且其餘兩個已是ai的符號 
    			if (checkerboard[i+((j+1)%3)*3] == aiSymbol && checkerboard[i+((j+2)%3)*3] == aiSymbol)
    			{
    				finalStep = i+(j%3)*3; // 將勝利的最後一步傳回去 
				}
			}
		}
    }
    // 左上右下對角線
    for (int i = 0; i < 3; i++)
    {
    	if (checkerboard[0+(i)%3*4] != aiSymbol && checkerboard[0+i*4] != playerSymbol)
    	{
    		if (checkerboard[0+((i+1)%3)*4] == aiSymbol && checkerboard[0+((i+2)%3)*4] == aiSymbol)
    		{
    			finalStep = 0+(i)%3*4;
			}
		}
	}
	//左下右上對角線 
    for (int i = 0; i < 3; i++)
    {
    	if (checkerboard[0+(i)%3*4] != aiSymbol && checkerboard[0+i*4] != playerSymbol)
    	{
    		if (checkerboard[0+((i+1)%3)*4] == aiSymbol && checkerboard[0+((i+2)%3)*4] == aiSymbol)
    		{
    			finalStep =  0+(i)%3*4;
			}
		}
	}
	return finalStep;
}

// AI閃過陷阱用 
int trap(char checkerboard[], char playerSymbol)
{
	int avoidStep = 10;
	int mids[] = {1, 3, 5, 7};
	int x = randomPos(0, 3);
	if (checkerboard[0] == playerSymbol && checkerboard[8] == playerSymbol)
	{
		avoidStep = mids[x];
	}
	if (checkerboard[6] == playerSymbol && checkerboard[2] == playerSymbol)
	{
		avoidStep = mids[x];
	}
	return avoidStep;
}

// AI輸入
void aiInput(char checkerboard[], char aiSymbol, char difficulty, int steps)
{
	// 前置作業 
	getchar();
    char playerSymbol;
    if (aiSymbol == 'O')
    {
        playerSymbol = 'X';
    }
    else
    {
        playerSymbol = 'O';
    }
    /*
    容易難度的AI
	下棋原則：
	1. 贏得自己勝利
	2. 阻止自己敗北 
	3. 1.2.不符合就先隨機下
	*/
	if (difficulty == 'e')
	{
		// 判斷AI是否即將獲勝
    	int finalStep = aboutToWin(checkerboard, aiSymbol, playerSymbol);
    	int defenseStep = aboutToLose(checkerboard, aiSymbol, playerSymbol);
    	if (finalStep != 10)
    	{
    		printf("勝利步：%d\n", finalStep+1);
    		checkerboard[finalStep] = aiSymbol;
		}
		// 判斷AI是否即將敗北 
		else if(defenseStep != 10)
		{
			printf("防守步：%d\n", defenseStep+1);
    		checkerboard[defenseStep] = aiSymbol;
		}
		else 
		{
			bool done;
			// 重複隨機下直到可以 
    		while (!done)
			{
				int x = randomPos(0, 8);
    			// printf("x: %d",x+1);
    			if(checkerboard[x] != aiSymbol && checkerboard[x] != playerSymbol) 
				{
					checkerboard[x] = aiSymbol; // AI下棋
					done = true;
					printf("AI下在%d\n", x+1);
				}
				/* debug用 
				else
				{
					printf("，已被下過，重新找隨機數\n");
				}
				*/
			}
		}	
	}
	/*
    困難難度的AI
	下棋原則：
	1. 贏得自己勝利
	2. 阻止自己敗北
	3. 先手後手都中間為空先下，中間被下就佔角落 
	4. 玩家第二手用角落包夾中間時選擇下在平面，非角落 
	5. 1.2.3.4.不符合就先隨機下
	*/
	else
	{
		// 判斷AI是否即將獲勝
    	int finalStep = aboutToWin(checkerboard, aiSymbol, playerSymbol);
    	int defenseStep = aboutToLose(checkerboard, aiSymbol, playerSymbol);
    	int avoidStep = trap(checkerboard, playerSymbol);
    	if (finalStep != 10)
    	{
    		printf("勝利步：%d\n", finalStep+1);
    		printf("AI下在%d\n", finalStep+1);
    		checkerboard[finalStep] = aiSymbol;
		}
		// 判斷AI是否即將敗北 
		else if(defenseStep != 10)
		{
			printf("防守步：%d\n", defenseStep+1);
			printf("AI下在%d\n", defenseStep+1);
    		checkerboard[defenseStep] = aiSymbol;
		}
		// 第一步棋
		else if (steps == 0)
		{
			// 佔領中間
			if (checkerboard[4] != aiSymbol && checkerboard[4] != playerSymbol)
			{
				printf("下中間\n");
				printf("AI下在%d\n", 4);
				checkerboard[4] = aiSymbol;
			}
			else
			{
			// 佔領隨機一個角落
				printf("下角落\n");
				int corners[] = {0, 2, 6, 8};
				int x = corners[randomPos(0, 3)];
				checkerboard[x] = aiSymbol;
				printf("AI下在%d\n", x+1);
			}
		}
		// 第二步棋時被包圍 
		else if (steps == 1 && avoidStep != 10)
		{
			printf("躲陷阱\n");
			checkerboard[avoidStep] = aiSymbol;
			printf("AI下在%d\n", avoidStep+1);
		}
		else
		{
			bool done;
			// 重複隨機下直到可以 
    		while (!done)
			{
				int x = randomPos(0, 8);
    			// printf("x: %d",x+1);
    			if(checkerboard[x] != aiSymbol && checkerboard[x] != playerSymbol) 
				{
					checkerboard[x] = aiSymbol; // AI下棋
					done = true;
					printf("AI下在%d\n", x+1);
				}
				/* debug用 
				else
				{
					printf("，已被下過，重新找隨機數\n");
				}
				*/
			}
		} 
	}	
	printf("\n");  
    roundResult(checkerboard);
}

// 玩家輸入
void playerInput(char checkerboard[], char symbol, char mode)
{
    bool done;
    char number;
    if (mode == 's')
	{
		printf("玩家請輸入位置：");
	}
	else
	{
		if (symbol == 'O')
    	{
    		number = '1';
		}
		else
		{
			number = '2';
		}
    	printf("玩家%c請輸入位置：", number);
	}
    while (!done)
    {
        int pos;
        scanf(" %d", &pos); // 輸入下棋的位置
        // 檢查下的位置是否可下
        if (pos < 10 && pos > 0 && checkerboard[pos-1] != 'O' && checkerboard[pos-1] != 'X') 
        {
            checkerboard[pos-1] = symbol;
            printf("\n");
            roundResult(checkerboard);
            done = true;
        }
        else
        {
            printf("請下在正確的位置：");
            getchar(); // 處理換行符
        }
    }
    getchar();
}

// 遊戲開始
void duelGameStart(char checkerboard[])
{
	bool turn = true; // true時輪到玩家一下
	char pOneSymbol = 'O';
	char pTwoSymbol = 'X';
	for (int i = 0; i < 9; i++)
    {
        if (turn)
		{
        	playerInput(checkerboard, pOneSymbol, 'd'); // 玩家下棋
        	// 玩家一勝利 
        	if (over(checkerboard))
			{
				printf("It's over, p1 win!\n");
				printf("Congrats ^^\n");
				printTrophy();
				break;
			}
			// 最後一回合前 
            if (i < 8)
			{
				printf("輪到玩家二回合\n");
           		turn = false; // 輪到AI下
           		//printf("turn %d", turn);
			}
           
		}			
        else
		{
        	playerInput(checkerboard, pTwoSymbol, 'd'); // 玩家二 
        	// 玩家二勝利 
        	if (over(checkerboard))
			{
				printf("It's over, p2 win!");
				printf("Congrats ^^\n");
				printTrophy();
				break;
			}
			// 最後一回合前
			if (i < 8)
			{
				printf("輪到玩家一回合\n");
            	turn = true; // 輪到玩家下
           		//printf("turn %d\n", turn);
           	}
		}
		if (i == 8 && !over(checkerboard))
		{
			printf("It's over, draw!");
		}
    }
	
}

// 遊戲開始
void aiGameStart(int symbol, char checkerboard[], char difficulty)
{
    bool turn; // true時輪到玩家下
    int steps = 0; // AI下了幾步，用於在困難模式下 
    char aiSymbol; // AI的符號
    // 玩家1先攻
    if (symbol == 'O')
    {
        turn = true;
        aiSymbol = 'X';
    }
    else
    {
        aiSymbol = 'O';
    }
    for (int i = 0; i < 9; i++)
    {
        if (turn)
		{
        	playerInput(checkerboard, symbol, 's'); // 玩家下棋
        	
        	// 玩家勝利 
        	if (over(checkerboard))
			{
				printf("It's over, you win!\n");
				printf("Congrats ^^\n");
				printTrophy();
				break;
			}
			// 最後一回合前 
            if (i < 8)
			{
				printf("輪到ai回合\n");
           		turn = false; // 輪到AI下
           		//printf("turn %d", turn);
			}
           
		}			
        else
		{
        	aiInput(checkerboard, aiSymbol, difficulty, steps++); // AI下棋
        	// AI勝利 
        	if (over(checkerboard))
			{
				printf("It's over, you lose!");
				break;
			}
			// 最後一回合前
			if (i < 8)
			{
				printf("輪到玩家回合\n");
            	turn = true; // 輪到玩家下
           		//printf("turn %d\n", turn);
           	}
		}
		if (i == 8 && !over(checkerboard))
		{
			printf("It's over, draw!");
		}
    }
}

//雙人模式
void dualMode(char checkerboard[])
{
	printf("玩家一符號為O, 玩家二符號為X\n");
	getchar();
	char tutorial; 
    printf("是否略過規則(Y/N):");
    scanf(" %c", &tutorial);
    printf("\n");
    if (tutorial == 'n' || tutorial == 'N')
    {
        rules(); // 介紹規則
    }
    else if(tutorial == 'y' || tutorial == 'Y')
    {
        printf("好的，祝遊玩開心~\n");
    }
    else
    {
        printf("亂輸入就給我乖乖看教學^^\n");
        getchar();
        rules();
    }
    printf("按下enter開始遊戲...\n");
    getchar();
    getchar();
    // 開始遊戲
    duelGameStart(checkerboard);
}

// 單人模式
void singleMode(char checkerboard[])
{
    printf("接下來會有電腦玩家陪您遊玩\n");
    getchar();
    char difficulty;
    bool done;
    // 難度選擇
    printf("請選擇容易或困難的難易度(E/H):");
    while (!done)
    {
        scanf(" %c", &difficulty);
        if (difficulty == 'e' || difficulty == 'E')
        {
            printf("\n");
            printf("容易模式\n");
            difficulty = 'e';
            done = true;
        }
        else if(difficulty == 'h' || difficulty == 'H')
        {
            printf("\n");
            printf("困難模式\n");
            difficulty = 'h';
            done = true;
        }
        else
        {
            printf("請輸入有效的選擇\n");
            getchar(); // 處理換行符
        }
    }
    done = false;
    // 先攻順序
    char symbol;
    printf("規則為O先下\n");
    printf("請選擇符號(O/X):");
    while (!done)
    {
        scanf(" %c", &symbol);
        if (symbol == 'o' || symbol == 'O')
        {
            printf("\n");
            printf("選擇O\n");
            symbol = 'O';
            done = true;
        }
        else if(symbol == 'x' || symbol == 'X')
        {
            printf("\n");
            printf("選擇X\n");
            symbol = 'X';
            done = true;
        }
        else
        {
            printf("請輸入有效的選擇\n");
            getchar(); // 處理換行符
        }
    }
    char tutorial; 
    printf("是否略過規則(Y/N):");
    scanf(" %c", &tutorial);
    printf("\n");
    if (tutorial == 'n' || tutorial == 'N')
    {
        rules(); // 介紹規則
    }
    else if(tutorial == 'y' || tutorial == 'Y')
    {
        printf("好的，祝遊玩開心~\n");
    }
    else
    {
        printf("亂輸入就給我乖乖看教學^^\n");
        getchar();
        rules();
    }
    
    printf("按下enter開始遊戲...\n");
    getchar();
    getchar();
    // 開始遊戲
    aiGameStart(symbol, checkerboard, difficulty);
}

// 模式選擇
void modeSelect()
{
	getchar();
    char mode;
    bool done;
    printf("選擇單人或雙人模式(S/D)：");
    while (!done)
    {
        scanf(" %c", &mode);
        if (mode == 's' || mode == 'S')
        {
            printf("\n");
            printf("選擇了單人模式\n");
            mode = 's';
            done = true;
        }
        else if(mode == 'd' || mode == 'D')
        {
            printf("\n");
            printf("選擇了雙人模式\n");
            mode = 'd';
            done = true;
        }
        else
        {
            printf("\n");
            printf("請輸入有效的選擇\n");
            getchar(); // 處理換行符
        }
    }
    // 宣告3x3 OOXX棋盤
    char checkerboard[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    if (mode == 's')
    {
        singleMode(checkerboard);
    }
    else if (mode == 'd')
    {
        dualMode(checkerboard);
    }
}
 
int main()
{
    printf("歡迎遊玩圈圈叉叉遊戲！");
    // 等待使用者按下 Enter
    int times = 0;
    // 程式繼續執行
    while (1)
    {
    	modeSelect();
    	times++;
    	if (times > 10)
    	{
    		printf("謝謝支持^^\n");
    		getchar();
		}		
		else if (times > 20)
		{
			printf("哇...圈圈叉叉這麼好玩嗎");
			getchar();
		}
    	clearInputBuffer();
    	if (times > 0)
		{
			char again;
    		printf("再玩一次？(Y/N):\n");
    		scanf("%c", &again);
    		if (again == 'y' || again == 'Y')
    		{
    			// do nothing
			}
			else
			{
				printf("See you next time ^^\n");
				break;
			}
		}
	}
    return 0;
}
