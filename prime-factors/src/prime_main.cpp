#include <gtest/gtest.h>
#include <vector>
#include <utility>
#include <cmath>
#include <cstring>

#define MAX 1000000

typedef std::pair< int, int > factor;

bool sieve[ MAX+1 ];
std::vector< int > primeList;

void genPrimes()
{
	if( !primeList.empty() )
		return;

	memset( sieve, false, sizeof( sieve ) );

	int i = 2;

	sieve[ 0 ] = true;
	sieve[ 1 ] = true;

	while( i <= MAX )
	{
		primeList.push_back( i );

		for( int j=i*2; j<=MAX; j+=i )
		{
			sieve[ j ] = true;
		}

		i++;

		while( i <= MAX && sieve[i] )
			i++;
	}
}

std::vector< factor > primeFactors( int N )
{
	std::vector< factor > factors;

	genPrimes();

	for( int prime : primeList )
	{
		int count;
		for( count = 0; N % prime == 0;  ++count)
			N /= prime;

		if( count )
			factors.push_back( factor( prime, count ) );

		if( N <= 1 )
			break;
	}

	return factors;
}

TEST( PrimeFactorsTest, usingNumberWithOnlyOneFactorReturnsOneFactor )
{
	int N = 2;
	std::vector< factor > primes;

	primes.push_back( factor( 2, 1 ) );

	ASSERT_EQ( primes, primeFactors( N ) );
}

TEST( PrimeFactorsTest, usingNumberWIthTwoFactorsReturnTwoFactors )
{
	int N = 6;
	std::vector< factor > primes;
	primes.push_back( factor( 2, 1 ) );
	primes.push_back( factor( 3, 1 ) );

	ASSERT_EQ( primes, primeFactors( N ) );
}

TEST( PrimeFactorsTest, using17ReturnOnly17 )
{
	int N = 17;
	std::vector< factor > factorList;
	factorList.push_back( factor(17, 1) );

	ASSERT_EQ( factorList, primeFactors( N ) );
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest( &argc, argv );
	return RUN_ALL_TESTS();
}
