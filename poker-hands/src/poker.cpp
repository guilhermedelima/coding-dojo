#include <gtest/gtest.h>

#include <vector>
#include <map>
#include <utility>
#include <string>
#include <iostream>

typedef std::pair< char, char > card;


const static std::string names[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace" };
static int priorityMap[128];
const static std::string gameNames[] = {" - high card: ", " - pair"};

void initializeDeck()
{
	priorityMap[ (int)'2' ] = 0;
	priorityMap[ (int)'3' ] = 1;
	priorityMap[ (int)'4' ] = 2;
	priorityMap[ (int)'5' ] = 3;
	priorityMap[ (int)'6' ] = 4;
	priorityMap[ (int)'7' ] = 5;
	priorityMap[ (int)'8' ] = 6;
	priorityMap[ (int)'9' ] = 7;
	priorityMap[ (int)'T' ] = 8;
	priorityMap[ (int)'J' ] = 9;
	priorityMap[ (int)'Q' ] = 10;
	priorityMap[ (int)'K' ] = 11;
	priorityMap[ (int)'A' ] = 12;
}

bool CheckPair(const std::vector< card > &blackHand)
{
	int count = 0;

	for (unsigned int i = 0; i < blackHand.size(); ++i)
		for( unsigned int j = i + 1; j < blackHand.size(); ++j)
			count += blackHand[i].first == blackHand[j].first;

	return count;
}

int GetGame(const std::vector< card > &blackHand)
{
	int game = 1;

	if (CheckPair(blackHand))
		return game;

	--game;

	return game;
}

std::string checkPokerRound(const std::vector< card > &blackHand, const std::vector< card > &whiteHand)
{
	int higherBlack = 0;
	int higherWhite = 0;
	std::string result;

	int blackGame = GetGame(blackHand);
	int whiteGame = GetGame(whiteHand);

	if (blackGame > whiteGame)
	{
		result += "Black Wins";
		result += gameNames[blackGame];
	}
	else if (whiteGame > blackGame)
	{
		result += "White Wins";
		result += gameNames[whiteGame];
	}
	else
	{
		/*
		 * CONTINUE:
		 * Sort both hands and compares from last to first
		 * which one is bigger.
		 *
		 * We were trying to create a lambda function because
		 * of the vocal cards.
		 */
		auto cmp = []() {}
		std::sort( blackHand.begin(), blackHand.end());
		std::sort( whiteHand.begin(), whiteHand.end());

		for (int i = blackHand.size() - 1; i >= 0; ++i)
			if (blackHand[i].first > whiteHand[i].first)
			{
				result.append( "Black Wins" );
				result.append( " - high card: " );
				result.append( names[ std::max( higherBlack, higherWhite ) ] );
			}

	}

	return result;
}

TEST( PokerTest, TestingHigherCardOnlyNumbersShowBlackWins )
{
	std::vector< card > blackHand;
	std::vector< card > whiteHand;
	
	blackHand.push_back( card( '2', 'H' ) );
	blackHand.push_back( card( '3', 'S' ) );
	blackHand.push_back( card( '4', 'H' ) );
	blackHand.push_back( card( '6', 'H' ) );
	blackHand.push_back( card( '9', 'S' ) );
		
	whiteHand.push_back( card( '2', 'S' ) );
	whiteHand.push_back( card( '4', 'H' ) );
	whiteHand.push_back( card( '8', 'S' ) );
	whiteHand.push_back( card( '3', 'S' ) );
	whiteHand.push_back( card( '5', 'H' ) );
	
	std::string result = "Black Wins - high card: 9";

	ASSERT_EQ( result , checkPokerRound( blackHand, whiteHand ) );
}

TEST( PokerTest, TestingHigherCardAceWinsShowCardName )
{
	std::vector< card > blackHand;
	std::vector< card > whiteHand;
	
	blackHand.push_back( card( '2', 'H' ) );
	blackHand.push_back( card( '3', 'S' ) );
	blackHand.push_back( card( '4', 'H' ) );
	blackHand.push_back( card( '6', 'H' ) );
	blackHand.push_back( card( 'A', 'S' ) );
		
	whiteHand.push_back( card( '2', 'S' ) );
	whiteHand.push_back( card( '4', 'H' ) );
	whiteHand.push_back( card( '8', 'S' ) );
	whiteHand.push_back( card( '3', 'S' ) );
	whiteHand.push_back( card( 'Q', 'H' ) );
	
	std::string result = "Black Wins - high card: Ace";

	ASSERT_EQ( result , checkPokerRound( blackHand, whiteHand ) );
}

TEST( PokerTest, TestingBlackHasAPairAndWins )
{
	std::vector< card > blackHand;
	std::vector< card > whiteHand;
	
	blackHand.push_back( card( '2', 'H' ) );
	blackHand.push_back( card( '2', 'S' ) );
	blackHand.push_back( card( '3', 'S' ) );
	blackHand.push_back( card( '4', 'H' ) );
	blackHand.push_back( card( '6', 'H' ) );
		
	whiteHand.push_back( card( '2', 'S' ) );
	whiteHand.push_back( card( '4', 'H' ) );
	whiteHand.push_back( card( '8', 'S' ) );
	whiteHand.push_back( card( '3', 'S' ) );
	whiteHand.push_back( card( 'Q', 'H' ) );

	std::string result = "Black Wins - pair";

	ASSERT_EQ( result , checkPokerRound( blackHand, whiteHand ) );
}

TEST( PokerTest, TestingWhiteWinsWithTheSecondHighCard )
{
	std::vector< card > blackHand;
	std::vector< card > whiteHand;
	
	blackHand.push_back( card( '2', 'H' ) );
	blackHand.push_back( card( 'Q', 'S' ) );
	blackHand.push_back( card( '6', 'H' ) );
	blackHand.push_back( card( '3', 'S' ) );
	blackHand.push_back( card( '4', 'H' ) );
		
	whiteHand.push_back( card( 'Q', 'S' ) );
	whiteHand.push_back( card( '4', 'H' ) );
	whiteHand.push_back( card( '8', 'S' ) );
	whiteHand.push_back( card( '3', 'S' ) );
	whiteHand.push_back( card( '2', 'H' ) );

	std::string result = "White Wins - high card: 8";
	ASSERT_EQ( result, checkPokerRound( blackHand, whiteHand ) );
}

int main(int argc, char* argv[])
{
	initializeDeck();
	::testing::InitGoogleTest( &argc, argv );
	return RUN_ALL_TESTS();
}
