#pragma once
#include <string>

using FString = std::string;
using int32 = int;

// All values initialized to zero
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

class FBullCowGame {
public:
	FBullCowGame(); // constructor
	void Reset(); // Reset word. TODO make a more rich return value
	std::string Summarise(); // Returns a string with a summary of the game

	// Getters
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	FString GetHiddenWord() const;
	int32 GetHiddenWordLength() const;

	// Public methods
	bool IsGameWon(FBullCowCount) const;
	bool IsGuessValid(FString) const;
	// counts bulls and cows ad increases turn number assuming valid guess
	FBullCowCount SubmitGuess(FString);

private:
	// Attributes
	int32 CurrentTry;
	int32 MaxTries;
	FString HiddenWord;

	// Private methods
	bool IsIsogram(FString) const;
};