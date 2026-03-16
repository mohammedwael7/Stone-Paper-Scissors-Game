#include<iostream>
#include<cstdlib>
using namespace std;
enum enGameChoice { stone = 1, paper = 2, scissors = 3 };
enum enWinner { player1 = 1, computer = 2, draw = 3 };

struct stRoundInfo
{
	short RoundsNumber;

	enGameChoice PlayerChoice;
	enGameChoice ComputerChoice;
	enWinner RoundWinner;
	string WinnerName = "";

};

struct stGameResults
{
	short RoundsNumber;

	short PlayerWonTimes = 0;
	short ComputerWonTimes = 0;
	short DrawTimes = 0;
	enWinner GameWinner;
	string WinnerName = "";
};

int RandomNumber(int from, int to)
{
	int RandNum = rand() % (to - from + 1) + from;
	return RandNum;
}

void ResetScreen()
{
	system("cls");
	system("color 0F");
}

short ReadHowManyRounds()
{
	short RoundsNumber;
	do
	{
		cout << "How Many Rounds 1 to 10 ?\n";
		cin >> RoundsNumber;

	} while (RoundsNumber < 1 || RoundsNumber > 10);

	cout << endl;
	return RoundsNumber;
}

enGameChoice ReadPlayerChoice()
{
	short Choice;
	do
	{
		cout << "\nYour Choice : [1]:Stone, [2]:Paper, [3]Scissors ? ";
		cin >> Choice;

	} while (Choice < 1 || Choice > 3);

	return (enGameChoice)Choice;
}

enGameChoice GetComputerChoice()
{
	return (enGameChoice)RandomNumber(1, 3);
}

void GameScreenColor(string WhoWin)
{
	if (WhoWin == "Computer")
	{
		cout << "\a";
		system("color 4F");
	}
	else if (WhoWin == "Player1")
		system("color 2F");
	else
		system("color 6F");
}

enWinner  WhoWonTheRound(stRoundInfo RoundInfo)
{
	if (RoundInfo.PlayerChoice == RoundInfo.ComputerChoice)
	{
		return enWinner::draw;
	}

	switch (RoundInfo.PlayerChoice)
	{
	case enGameChoice::stone:
		if (RoundInfo.ComputerChoice == enGameChoice::paper)
		{
			return enWinner::computer;
		}
		break;

	case enGameChoice::paper:
		if (RoundInfo.ComputerChoice == enGameChoice::scissors)
		{
			return enWinner::computer;
		}
		break;

	case enGameChoice::scissors:
		if (RoundInfo.ComputerChoice == enGameChoice::stone)
		{
			return enWinner::computer;
		}
		break;
	}

	// if yoy reach here then player1 is the winner
	return enWinner::player1;
}

string GetWinnerName(enWinner Winner)
{
	string arrWinnerName[3] = { "Player1" ,"Computer" ,"Draw" };

	return arrWinnerName[Winner - 1];
}

string GetChoiceName(enGameChoice GameChoice)
{
	string arrChoiceName[3] = { "Stone", "Paper", "Scissors" };

	return arrChoiceName[GameChoice - 1];
}

enWinner  WhoWonTheGame(short PlayerWonTimes, short ComputerWonTimes)
{
	if (PlayerWonTimes > ComputerWonTimes)
		return enWinner::player1;
	else if (PlayerWonTimes < ComputerWonTimes)
		return enWinner::computer;
	else
		return enWinner::draw;
}

stGameResults FillGameResults(short RoundNumber, short PlayerWonTimes, short ComputerWonTimes, short DrawTimes)
{
	stGameResults GameResult;

	GameResult.RoundsNumber = RoundNumber;
	GameResult.PlayerWonTimes = PlayerWonTimes;
	GameResult.ComputerWonTimes = ComputerWonTimes;
	GameResult.DrawTimes = DrawTimes;
	GameResult.GameWinner = WhoWonTheGame(PlayerWonTimes, ComputerWonTimes);
	GameResult.WinnerName = GetWinnerName(GameResult.GameWinner);

	return GameResult;
}

void PrintRoundResults(stRoundInfo RoundInfo)
{
	cout << "\n__________Round [" << RoundInfo.RoundsNumber << "]__________\n\n";
	cout << "Player1  Choice: " << GetChoiceName(RoundInfo.PlayerChoice) << endl;
	cout << "Computer Choice: " << GetChoiceName(RoundInfo.ComputerChoice) << endl;
	cout << "Round Winner   : [" << RoundInfo.WinnerName << "]\n";

	cout << "___________________________________\n";

	GameScreenColor(RoundInfo.WinnerName);
}

stGameResults PlayGame(short  RoundsNumber)
{
	stRoundInfo RoundInfo;
	short PlayerWonTimes = 0, ComputerWonTimes = 0, DrawTimes = 0;

	for (int i = 1; i <= RoundsNumber; i++)
	{
		cout << "\nRound [" << i << "] begins:\n";

		RoundInfo.RoundsNumber = i;
		RoundInfo.PlayerChoice = ReadPlayerChoice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.RoundWinner = WhoWonTheRound(RoundInfo);
		RoundInfo.WinnerName = GetWinnerName(RoundInfo.RoundWinner);

		if (RoundInfo.RoundWinner == enWinner::player1)
			++PlayerWonTimes;

		else if (RoundInfo.RoundWinner == enWinner::computer)
			++ComputerWonTimes;

		else
			++DrawTimes;

		PrintRoundResults(RoundInfo);
	}

	return FillGameResults(RoundsNumber, PlayerWonTimes, ComputerWonTimes, DrawTimes);
}

void ShowGameOverScreen()
{
	cout << "\t\t____________________________________________________\n";
	cout << "\n\t\t\t\t+++ G a m e  O v e r +++\t\t\t\t\n";
	cout << "\t\t_____________________________________________________\n";
}

void ShowFinalGameResults(stGameResults GameResults)
{
	cout << "\t\t________________ [ Game Results ] ___________________\n";
	cout << "\t\tGame Rounds        : " << GameResults.RoundsNumber << endl;
	cout << "\t\tPlayer1 won times  : " << GameResults.PlayerWonTimes << endl;
	cout << "\t\tComputer won times : " << GameResults.ComputerWonTimes << endl;
	cout << "\t\tDraw times         : " << GameResults.DrawTimes << endl;
	cout << "\t\tFinal winner       : " << GameResults.WinnerName << endl;
	cout << "\t\t___________________________________\n";

	GameScreenColor(GameResults.WinnerName);
}

void Stone_Paper_Scissors_Game()
{
	char PlayAgain = 'Y';

	do
	{
		ResetScreen();
		stGameResults GameResults = PlayGame(ReadHowManyRounds());

		ShowGameOverScreen();
		ShowFinalGameResults(GameResults);

		cout << "\t\tDo you want to play again? Y/N? ";
		cin >> PlayAgain;

		cout << endl;

	} while (PlayAgain == 'y' || PlayAgain == 'Y');
}

int main()
{
	srand((unsigned)time(NULL));

	Stone_Paper_Scissors_Game();
	return 0;
}