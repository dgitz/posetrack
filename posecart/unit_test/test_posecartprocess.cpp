#include <gtest/gtest.h>
#include "../PoseCartProcess/PoseCartProcess.h"
TEST(Test1,Test1a)
{
    PoseCartProcess process;
    process.update();
}
int main(int argc,char ** argv)
{
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
