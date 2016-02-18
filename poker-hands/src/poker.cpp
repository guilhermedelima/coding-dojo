#include <gtest/gtest.h>
#include <vector>
#include <utility>
#include <string>
#include <iostream>

typedef std::pair< char, char > card;

std::string checkPokerRound(const std::vector< card > &blackHand, const std::vector< card > &whiteHand)
{
	char higherBlack = 0;
	char higherWhite = 0;
	std::string result;
	std::vector< char > priority;
	priority( '2', '3', '5', '6', '7', '8', '9', 'J', 'Q', 'K', 'A' );
	std::map< char, priority > priorityMap;
	priorityMap[ '2' ] = 0;
	priorityMap[ '3' ] = 1;
	priorityMap[ '4' ] = 2;
	priorityMap[ '5' ] = 3;
	priorityMap[ '6' ] = 4;
	priorityMap[ '7' ] = 5;
	priorityMap[ '8' ] = 6;
	priorityMap[ '9' ] = 7;
	priorityMap[ 'J' ] = 8;
	priorityMap[ 'Q' ] = 9;
	priorityMap[ 'K' ] = 10;
	priorityMap[ 'A' ] = 11;

	for( card c : blackHand )
	{
		higherBlack = std::max( higherBlack, c.first );
	}


	for( card c : whiteHand )
	{
		higherWhite = std::max( higherWhite, c.first );
	}

	result.append( ( higherBlack > higherWhite ) ? "Black Wins" : "White Wins" );
	result.append( " - high card: " );
	result.append( 1, std::max( higherBlack, higherWhite ) );

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

TEST( PokerTest, TestingHighCardShowWhoWins )
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
	
	std::string result = "Black Wins - high card: A";

	ASSERT_EQ( result , checkPokerRound( blackHand, whiteHand ) );
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest( &argc, argv );
	return RUN_ALL_TESTS();
}
