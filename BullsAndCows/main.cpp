/* Console executable, uses FBullCowGame. View in a MVC pattern.
For game logic see the FBullCowGame.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetGuess();
bool AskToPlayAgain();

FBullCowGame BCGame; // instantiate a new game

int main()
{
	do
	{
		PrintIntro();
		PlayGame();
	} while (AskToPlayAgain());
	return 0;
}

void PrintIntro()
{	// Game introduction
	std::cout << "Bienvenue to la Bulla et la Cowa, un jocco bastante botorudorf\n";
	// TODO ascii art
	std::cout << "Pode adivinare la isograma de " << BCGame.GetHiddenWordLength() << " letra de la ke stik pensant?\n\n";
	std::cout << "Voce disposa de " << BCGame.GetMaxTries() << " tries para conseguir el objectivo." << std::endl;
	return;
}

void PlayGame()
{	
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	int32 HiddenWordLength = BCGame.GetHiddenWord().length();
	bool bGameWon = false;

	while ((BCGame.GetCurrentTry() != MaxTries) && !bGameWon) 
	{
		FText Guess = GetGuess();
		switch (BCGame.CheckGuessValidity(Guess)) // TODO transform to SWITCH with error cases
		{
			case EWordStatus::NOT_ISOGRAM: std::cout << "Xavalado te he dive ISOGRAMA! Tu palabro no es un isograma (no se pode repeat letras)..." << std::endl; break;
			case EWordStatus::TOO_LARGE: std::cout << "Xavalada la noche es nuestra vaya palabro mas largo pedazo de kpuyo! Plix escribe un palabro de " << HiddenWordLength << " letras..." << std::endl; break;
			case EWordStatus::TOO_SHORT: std::cout << "Xavaliyo ke tas kedao corto con las letras! Plix escribe un palabro de " << HiddenWordLength << " letras..." << std::endl; break;
			case EWordStatus::OK: 
			{
				FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);
				bGameWon = BCGame.IsGameWon(BullCowCount);
				if (!bGameWon)
				{
					std::cout << "Bulla = " << BullCowCount.Bulls;
					std::cout << ". Cowa = " << BullCowCount.Cows;
					std::cout << std::endl;
				}
			}
		}
	}	
	if(bGameWon)
		std::cout << BCGame.Summarise();
	return;
}
FText GetGuess()
{	// Get a guess from the player
	std::cout << "Try " << BCGame.GetCurrentTry()+1 << ". Lo teu gueSS: ";
	FText Guess = "";
	getline(std::cin, Guess);
	return Guess;
}

bool AskToPlayAgain()
{
	FText Response = "";
	std::cout << "Vole tornare a guga? (s/n): ";
	while (getline(std::cin, Response))
	{
		if (Response[0] == 'S' || Response[0] == 's')
			return true;
		else if (Response[0] == 'N' || Response[0] == 'n')
			return false;
		else
			std::cout << "Que me dive? Vole tornare a guga? (s/n): ";
	}
}
