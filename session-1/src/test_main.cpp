#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <algorithm>

std::vector<std::string> anagram( const std::string& word)
{
	std::vector<std::string> anagrams;
	std::string str(word);

	sort( str.begin(), str.end() );

	do {
		anagrams.push_back(str);
	} while (next_permutation(str.begin(), str.end()));

	sort( anagrams.begin(), anagrams.end() );

	return anagrams;
}

TEST(AnagramTest, OnlyOneLetterReturnsLetter)
{
	std::vector<std::string> v;
	std::string word("A");

	v.push_back(word);
	ASSERT_EQ(v, anagram( word ));
}

TEST( AnagramTest, ThreeLettersWithRepetition )
{
	std::vector< std::string > v;

	v.push_back( "AAB" );
	v.push_back( "ABA" );
	v.push_back( "BAA" );

	ASSERT_EQ( v, anagram( "AAB" ) );
}

TEST(AnagramTest, TwoLettersReturnTwoAnagrams)
{
	std::vector< std::string > v;
	std::string word("AB");

	v.push_back( "AB" );
	v.push_back( "BA" );
	ASSERT_EQ( v, anagram( word ) );
}

TEST(AnagramTest, TestCodingDojoWebSite)
{
	std::vector< std::string > v;

	v.push_back( "biro" );
	v.push_back( "bior" );
	v.push_back( "brio" );
	v.push_back( "broi" );
	v.push_back( "boir" );
	v.push_back( "bori" );
	v.push_back( "ibro" );
	v.push_back( "ibor" );
	v.push_back( "irbo" );
	v.push_back( "irob" );
	v.push_back( "iobr" );
	v.push_back( "iorb" );
	v.push_back( "rbio" );
	v.push_back( "rboi" );
	v.push_back( "ribo" );
	v.push_back( "riob" );
	v.push_back( "roib" );
	v.push_back( "robi" );
	v.push_back( "obir" );
	v.push_back( "obri" );
	v.push_back( "oibr" );
	v.push_back( "oirb" );
	v.push_back( "orbi" );
	v.push_back( "orib" );

	sort( v.begin(), v.end() );

	//ASSERT_EQ( v.size(), anagram( "biro" ).size() );
	ASSERT_EQ( v, anagram( "biro" ) );
	
}

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest( &argc, argv );
	return RUN_ALL_TESTS();
}
