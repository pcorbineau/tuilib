#include <gtest/gtest.h>
#include <tuilib/hello.h>

TEST(TOTO, TATA){
	EXPECT_EQ(tuilib::add(1,2), 3);
}
