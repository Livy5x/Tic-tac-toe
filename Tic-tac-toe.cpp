#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // �ϥ�boolean��
#include <time.h>   /* �ɶ�������� */

// �M�z��J�w�İϪ����
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// �H���U��
int randomPos(int min, int max)
{
	/* �]�w�üƺؤl */
    srand( time(NULL) );
    /* ���w�üƽd�� */
    /* ���Ͷü� */
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

// �L�X�Ӧ^�X���G 
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

// �C���W�h����
void rules()
{
    getchar();
    printf("���йC���W�h\n");
    getchar();
    printf("�C���ѽL�p�U�G\n");
    printf("1 2 3\n");
    printf("4 5 6\n");
    printf("7 8 9\n");
    getchar();
    printf("��J9�c�檺��m�Y�i���U��e�G\n");
    getchar();
    printf("ex: O�п�J: 5\n");
    getchar();
    printf("1 2 3\n");
    printf("4 O 6\n");
    printf("7 8 9\n");
    getchar();
    printf("ex: X�п�J: 6\n");
    getchar();
    printf("1 2 3\n");
    printf("4 O X\n");
    printf("7 8 9\n");
    
}

// �P�_�ӧQ
bool over(char checkerboard[])
{
    // �C 
    for (int i = 0; i < 3; i++)
    {
        if (checkerboard[i*3] == checkerboard[i*3+1] && checkerboard[i*3+1] == checkerboard[i*3+2])
        {
            return true;
        }
    }
    // �� 
    for (int i = 0; i < 3; i++)
    {
        if (checkerboard[i] == checkerboard[i+3] && checkerboard[i+3] == checkerboard[i+6])
        {
            return true;
        }
    }
    // �﨤�u 
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

// �P�Oai�O�_�n��F, �ŦX����Ǩ��u�B 
int aboutToLose(char checkerboard[], char aiSymbol, char playerSymbol)
{
	int defenseStep = 10; // ���u�@�B
	// �C
    for (int i = 0; i < 3; i++)
    {
    	// �ˬd�P�@�C���Ҧ��i�� 
    	for (int j = 0; j < 3; j++)
    	{
    		// ���]�|���Q�U
    		if (checkerboard[i*3+(j%3)] != aiSymbol && checkerboard[i*3+(j%3)] != playerSymbol)  
    		{
    			// �åB��l��Ӥw�O���a���Ÿ� 
    			if (checkerboard[i*3+(j+1)%3] == playerSymbol && checkerboard[i*3+(j+2)%3] == playerSymbol)
    			{
    				defenseStep = i*3+(j%3); // �N���u�B�Ǧ^�h 
				}
			}
		}
    }
    // �� 
    for (int i = 0; i < 3; i++)
    {
    	// �ˬd�P�@�檺�Ҧ��i�� 
    	for (int j = 0; j < 3; j++)
    	{
    		// ���]�|���Q�U
    		if (checkerboard[i+(j%3)*3] != aiSymbol && checkerboard[i+(j%3)*3] != playerSymbol)  
    		{
    			// �åB��l��Ӥw�O���a���Ÿ� 
    			if (checkerboard[i+((j+1)%3)*3] == playerSymbol && checkerboard[i+((j+2)%3)*3] == playerSymbol)
    			{
    				defenseStep = i+(j%3)*3; // �N���u�B�Ǧ^�h 
				}
			}
		}
    }
    // ���W�k�U�﨤�u
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
	//���U�k�W�﨤�u 
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

// �P�OAI�O�_�nĹ�F, �ŦX����ǳӧQ�B 
int aboutToWin(char checkerboard[], char aiSymbol, char playerSymbol)
{
	int finalStep = 10; // �ӧQ�@�B
	// �C
    for (int i = 0; i < 3; i++)
    {
    	// �ˬd�P�@�C���Ҧ��i�� 
    	for (int j = 0; j < 3; j++)
    	{
    		// ���]�|���Q�U
    		if (checkerboard[i*3+(j%3)] != aiSymbol && checkerboard[i*3+(j%3)] != playerSymbol)  
    		{
    			// �åB��l��Ӥw�Oai���Ÿ� 
    			if (checkerboard[i*3+(j+1)%3] == aiSymbol && checkerboard[i*3+(j+2)%3] == aiSymbol)
    			{
    				finalStep = i*3+(j%3); // �N�ӧQ���̫�@�B�Ǧ^�h 
				}
			}
		}
    }
    // �� 
    for (int i = 0; i < 3; i++)
    {
    	// �ˬd�P�@�檺�Ҧ��i�� 
    	for (int j = 0; j < 3; j++)
    	{
    		// ���]�|���Q�U
    		if (checkerboard[i+(j%3)*3] != aiSymbol && checkerboard[i+(j%3)*3] != playerSymbol)  
    		{
    			// �åB��l��Ӥw�Oai���Ÿ� 
    			if (checkerboard[i+((j+1)%3)*3] == aiSymbol && checkerboard[i+((j+2)%3)*3] == aiSymbol)
    			{
    				finalStep = i+(j%3)*3; // �N�ӧQ���̫�@�B�Ǧ^�h 
				}
			}
		}
    }
    // ���W�k�U�﨤�u
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
	//���U�k�W�﨤�u 
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

// AI�{�L������ 
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

// AI��J
void aiInput(char checkerboard[], char aiSymbol, char difficulty, int steps)
{
	// �e�m�@�~ 
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
    �e�����ת�AI
	�U�ѭ�h�G
	1. Ĺ�o�ۤv�ӧQ
	2. ����ۤv�ѥ_ 
	3. 1.2.���ŦX�N���H���U
	*/
	if (difficulty == 'e')
	{
		// �P�_AI�O�_�Y�N���
    	int finalStep = aboutToWin(checkerboard, aiSymbol, playerSymbol);
    	int defenseStep = aboutToLose(checkerboard, aiSymbol, playerSymbol);
    	if (finalStep != 10)
    	{
    		printf("�ӧQ�B�G%d\n", finalStep+1);
    		checkerboard[finalStep] = aiSymbol;
		}
		// �P�_AI�O�_�Y�N�ѥ_ 
		else if(defenseStep != 10)
		{
			printf("���u�B�G%d\n", defenseStep+1);
    		checkerboard[defenseStep] = aiSymbol;
		}
		else 
		{
			bool done;
			// �����H���U����i�H 
    		while (!done)
			{
				int x = randomPos(0, 8);
    			// printf("x: %d",x+1);
    			if(checkerboard[x] != aiSymbol && checkerboard[x] != playerSymbol) 
				{
					checkerboard[x] = aiSymbol; // AI�U��
					done = true;
					printf("AI�U�b%d\n", x+1);
				}
				/* debug�� 
				else
				{
					printf("�A�w�Q�U�L�A���s���H����\n");
				}
				*/
			}
		}	
	}
	/*
    �x�����ת�AI
	�U�ѭ�h�G
	1. Ĺ�o�ۤv�ӧQ
	2. ����ۤv�ѥ_
	3. �����ⳣ�������ť��U�A�����Q�U�N������ 
	4. ���a�ĤG��Ψ����]�������ɿ�ܤU�b�����A�D���� 
	5. 1.2.3.4.���ŦX�N���H���U
	*/
	else
	{
		// �P�_AI�O�_�Y�N���
    	int finalStep = aboutToWin(checkerboard, aiSymbol, playerSymbol);
    	int defenseStep = aboutToLose(checkerboard, aiSymbol, playerSymbol);
    	int avoidStep = trap(checkerboard, playerSymbol);
    	if (finalStep != 10)
    	{
    		printf("�ӧQ�B�G%d\n", finalStep+1);
    		printf("AI�U�b%d\n", finalStep+1);
    		checkerboard[finalStep] = aiSymbol;
		}
		// �P�_AI�O�_�Y�N�ѥ_ 
		else if(defenseStep != 10)
		{
			printf("���u�B�G%d\n", defenseStep+1);
			printf("AI�U�b%d\n", defenseStep+1);
    		checkerboard[defenseStep] = aiSymbol;
		}
		// �Ĥ@�B��
		else if (steps == 0)
		{
			// ���⤤��
			if (checkerboard[4] != aiSymbol && checkerboard[4] != playerSymbol)
			{
				printf("�U����\n");
				printf("AI�U�b%d\n", 4);
				checkerboard[4] = aiSymbol;
			}
			else
			{
			// �����H���@�Ө���
				printf("�U����\n");
				int corners[] = {0, 2, 6, 8};
				int x = corners[randomPos(0, 3)];
				checkerboard[x] = aiSymbol;
				printf("AI�U�b%d\n", x+1);
			}
		}
		// �ĤG�B�ѮɳQ�]�� 
		else if (steps == 1 && avoidStep != 10)
		{
			printf("������\n");
			checkerboard[avoidStep] = aiSymbol;
			printf("AI�U�b%d\n", avoidStep+1);
		}
		else
		{
			bool done;
			// �����H���U����i�H 
    		while (!done)
			{
				int x = randomPos(0, 8);
    			// printf("x: %d",x+1);
    			if(checkerboard[x] != aiSymbol && checkerboard[x] != playerSymbol) 
				{
					checkerboard[x] = aiSymbol; // AI�U��
					done = true;
					printf("AI�U�b%d\n", x+1);
				}
				/* debug�� 
				else
				{
					printf("�A�w�Q�U�L�A���s���H����\n");
				}
				*/
			}
		} 
	}	
	printf("\n");  
    roundResult(checkerboard);
}

// ���a��J
void playerInput(char checkerboard[], char symbol, char mode)
{
    bool done;
    char number;
    if (mode == 's')
	{
		printf("���a�п�J��m�G");
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
    	printf("���a%c�п�J��m�G", number);
	}
    while (!done)
    {
        int pos;
        scanf(" %d", &pos); // ��J�U�Ѫ���m
        // �ˬd�U����m�O�_�i�U
        if (pos < 10 && pos > 0 && checkerboard[pos-1] != 'O' && checkerboard[pos-1] != 'X') 
        {
            checkerboard[pos-1] = symbol;
            printf("\n");
            roundResult(checkerboard);
            done = true;
        }
        else
        {
            printf("�ФU�b���T����m�G");
            getchar(); // �B�z�����
        }
    }
    getchar();
}

// �C���}�l
void duelGameStart(char checkerboard[])
{
	bool turn = true; // true�ɽ��쪱�a�@�U
	char pOneSymbol = 'O';
	char pTwoSymbol = 'X';
	for (int i = 0; i < 9; i++)
    {
        if (turn)
		{
        	playerInput(checkerboard, pOneSymbol, 'd'); // ���a�U��
        	// ���a�@�ӧQ 
        	if (over(checkerboard))
			{
				printf("It's over, p1 win!\n");
				printf("Congrats ^^\n");
				printTrophy();
				break;
			}
			// �̫�@�^�X�e 
            if (i < 8)
			{
				printf("���쪱�a�G�^�X\n");
           		turn = false; // ����AI�U
           		//printf("turn %d", turn);
			}
           
		}			
        else
		{
        	playerInput(checkerboard, pTwoSymbol, 'd'); // ���a�G 
        	// ���a�G�ӧQ 
        	if (over(checkerboard))
			{
				printf("It's over, p2 win!");
				printf("Congrats ^^\n");
				printTrophy();
				break;
			}
			// �̫�@�^�X�e
			if (i < 8)
			{
				printf("���쪱�a�@�^�X\n");
            	turn = true; // ���쪱�a�U
           		//printf("turn %d\n", turn);
           	}
		}
		if (i == 8 && !over(checkerboard))
		{
			printf("It's over, draw!");
		}
    }
	
}

// �C���}�l
void aiGameStart(int symbol, char checkerboard[], char difficulty)
{
    bool turn; // true�ɽ��쪱�a�U
    int steps = 0; // AI�U�F�X�B�A�Ω�b�x���Ҧ��U 
    char aiSymbol; // AI���Ÿ�
    // ���a1����
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
        	playerInput(checkerboard, symbol, 's'); // ���a�U��
        	
        	// ���a�ӧQ 
        	if (over(checkerboard))
			{
				printf("It's over, you win!\n");
				printf("Congrats ^^\n");
				printTrophy();
				break;
			}
			// �̫�@�^�X�e 
            if (i < 8)
			{
				printf("����ai�^�X\n");
           		turn = false; // ����AI�U
           		//printf("turn %d", turn);
			}
           
		}			
        else
		{
        	aiInput(checkerboard, aiSymbol, difficulty, steps++); // AI�U��
        	// AI�ӧQ 
        	if (over(checkerboard))
			{
				printf("It's over, you lose!");
				break;
			}
			// �̫�@�^�X�e
			if (i < 8)
			{
				printf("���쪱�a�^�X\n");
            	turn = true; // ���쪱�a�U
           		//printf("turn %d\n", turn);
           	}
		}
		if (i == 8 && !over(checkerboard))
		{
			printf("It's over, draw!");
		}
    }
}

//���H�Ҧ�
void dualMode(char checkerboard[])
{
	printf("���a�@�Ÿ���O, ���a�G�Ÿ���X\n");
	getchar();
	char tutorial; 
    printf("�O�_���L�W�h(Y/N):");
    scanf(" %c", &tutorial);
    printf("\n");
    if (tutorial == 'n' || tutorial == 'N')
    {
        rules(); // ���гW�h
    }
    else if(tutorial == 'y' || tutorial == 'Y')
    {
        printf("�n���A���C���}��~\n");
    }
    else
    {
        printf("�ÿ�J�N���ڨĨĬݱо�^^\n");
        getchar();
        rules();
    }
    printf("���Uenter�}�l�C��...\n");
    getchar();
    getchar();
    // �}�l�C��
    duelGameStart(checkerboard);
}

// ��H�Ҧ�
void singleMode(char checkerboard[])
{
    printf("���U�ӷ|���q�����a���z�C��\n");
    getchar();
    char difficulty;
    bool done;
    // ���׿��
    printf("�п�ܮe���Χx����������(E/H):");
    while (!done)
    {
        scanf(" %c", &difficulty);
        if (difficulty == 'e' || difficulty == 'E')
        {
            printf("\n");
            printf("�e���Ҧ�\n");
            difficulty = 'e';
            done = true;
        }
        else if(difficulty == 'h' || difficulty == 'H')
        {
            printf("\n");
            printf("�x���Ҧ�\n");
            difficulty = 'h';
            done = true;
        }
        else
        {
            printf("�п�J���Ī����\n");
            getchar(); // �B�z�����
        }
    }
    done = false;
    // ���𶶧�
    char symbol;
    printf("�W�h��O���U\n");
    printf("�п�ܲŸ�(O/X):");
    while (!done)
    {
        scanf(" %c", &symbol);
        if (symbol == 'o' || symbol == 'O')
        {
            printf("\n");
            printf("���O\n");
            symbol = 'O';
            done = true;
        }
        else if(symbol == 'x' || symbol == 'X')
        {
            printf("\n");
            printf("���X\n");
            symbol = 'X';
            done = true;
        }
        else
        {
            printf("�п�J���Ī����\n");
            getchar(); // �B�z�����
        }
    }
    char tutorial; 
    printf("�O�_���L�W�h(Y/N):");
    scanf(" %c", &tutorial);
    printf("\n");
    if (tutorial == 'n' || tutorial == 'N')
    {
        rules(); // ���гW�h
    }
    else if(tutorial == 'y' || tutorial == 'Y')
    {
        printf("�n���A���C���}��~\n");
    }
    else
    {
        printf("�ÿ�J�N���ڨĨĬݱо�^^\n");
        getchar();
        rules();
    }
    
    printf("���Uenter�}�l�C��...\n");
    getchar();
    getchar();
    // �}�l�C��
    aiGameStart(symbol, checkerboard, difficulty);
}

// �Ҧ����
void modeSelect()
{
	getchar();
    char mode;
    bool done;
    printf("��ܳ�H�����H�Ҧ�(S/D)�G");
    while (!done)
    {
        scanf(" %c", &mode);
        if (mode == 's' || mode == 'S')
        {
            printf("\n");
            printf("��ܤF��H�Ҧ�\n");
            mode = 's';
            done = true;
        }
        else if(mode == 'd' || mode == 'D')
        {
            printf("\n");
            printf("��ܤF���H�Ҧ�\n");
            mode = 'd';
            done = true;
        }
        else
        {
            printf("\n");
            printf("�п�J���Ī����\n");
            getchar(); // �B�z�����
        }
    }
    // �ŧi3x3 OOXX�ѽL
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
    printf("�w��C�����e�e�C���I");
    // ���ݨϥΪ̫��U Enter
    int times = 0;
    // �{���~�����
    while (1)
    {
    	modeSelect();
    	times++;
    	if (times > 10)
    	{
    		printf("���¤��^^\n");
    		getchar();
		}		
		else if (times > 20)
		{
			printf("�z...���e�e�o��n����");
			getchar();
		}
    	clearInputBuffer();
    	if (times > 0)
		{
			char again;
    		printf("�A���@���H(Y/N):\n");
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
