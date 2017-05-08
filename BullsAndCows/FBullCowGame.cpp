#include "FBullCowGame.h"
#include <algorithm>

// Constructor
FBullCowGame::FBullCowGame() { Reset(); }

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "poyankre";

	MaxTries = MAX_TRIES;
	HiddenWord = HIDDEN_WORD;
	CurrentTry = 0;
	return;
}

std::string FBullCowGame::Summarise()
{
	std::string Summary = "fElIcItYYYY :$$$! Vc lo ai solvado com ";
	Summary += std::to_string(CurrentTry);
	Summary += " tries! ";
	return Summary;
}

// Getters
int32 FBullCowGame::GetMaxTries() const { return MaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return CurrentTry; }
FString FBullCowGame::GetHiddenWord() const { return HiddenWord; }
int32 FBullCowGame::GetHiddenWordLength() const { return HiddenWord.length(); }

// Methods
bool FBullCowGame::IsGameWon(FBullCowCount BullCowCount) const
{
	return BullCowCount.Bulls == HiddenWord.length();
}

EWordStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))
		return EWordStatus::NOT_ISOGRAM;
	if (Guess.length() < HiddenWord.length())
		return EWordStatus::TOO_SHORT;
	if (Guess.length() > HiddenWord.length())
		return EWordStatus::TOO_LARGE;
	if (Guess.length() == HiddenWord.length())
		return EWordStatus::OK;
}

bool FBullCowGame::IsIsogram(FString Guess) const
{
	std::string UsedChars = "";
	for (int32 i = 0; i < Guess.length(); i++)
	{
		if (std::count(UsedChars.begin(), UsedChars.end(), Guess[i]))
			return false;
		UsedChars += Guess[i];
	}
	return true;
}

// Receives a VALID guess, increments turn number
FBullCowCount FBullCowGame::SubmitGuess(FString Guess)
{
	CurrentTry++; // increment the turn number
	FBullCowCount BullCowCount; // setup a return variable

	for (int32 i = 0; i < Guess.length(); i++) // loop through all letters in the guess
	{
		for (int32 j = 0; j < HiddenWord.length(); j++) // compare letters against the hidden word
		{
			if (Guess[i] == HiddenWord[j])// if they match then
			{
				if (i == j) // If they're in the same position
					BullCowCount.Bulls++;
				else
					BullCowCount.Cows++;
			}
		}
	}	
	return BullCowCount;
}
