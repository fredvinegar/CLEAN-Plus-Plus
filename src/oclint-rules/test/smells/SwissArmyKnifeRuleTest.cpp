#include "TestRuleOnCode.h"

#include "rules/smells/SwissArmyKnifeRule.cpp"

class SwissArmyKnifeRuleTest : public ::testing::Test {
protected:
    virtual void SetUp() override
    {
        RuleConfiguration::addConfiguration("SWISS_ARMY_KNIFE", "3");
    }

    virtual void TearDown() override
    {
        RuleConfiguration::removeAll();
    }
};

TEST_F(SwissArmyKnifeRuleTest, PropertyTest)
{
SwissArmyKnifeRule rule;
EXPECT_EQ(3, rule.priority());
EXPECT_EQ("swiss army knife", rule.name());
EXPECT_EQ("smells", rule.category());
}

TEST_F(SwissArmyKnifeRuleTest, CXXClassNoMethod)
{
testRuleOnCXXCode(new SwissArmyKnifeRule(), "class c { int i; void m() {} };");
}

TEST_F(SwissArmyKnifeRuleTest, CXXClassThreeMethods)
{
testRuleOnCXXCode(new SwissArmyKnifeRule(), "class c { int i; void m() {} void n() {} void o() {} };");
}

TEST_F(SwissArmyKnifeRuleTest, CXXClassFourMethods)
{
testRuleOnCXXCode(new SwissArmyKnifeRule(), "class c { int i; void m() {} void n() {} void o() {} void p() {} };",
0, 1, 1, 1, 66, "C++ class with 4 methods exceeds limit of 3");
}

TEST_F(SwissArmyKnifeRuleTest, CXXClassFiveMethods)
{
testRuleOnCXXCode(new SwissArmyKnifeRule(), "class c { int i; void m() {} void n() {} void o() {} void p() {} void q() {} };",
0, 1, 1, 1, 78, "C++ class with 5 methods exceeds limit of 3");
}

TEST_F(SwissArmyKnifeRuleTest, ObjCImplementationNoMethod)
{
testRuleOnObjCCode(new SwissArmyKnifeRule(), "@interface a\n@end\n@implementation a\n@end\n");
}

TEST_F(SwissArmyKnifeRuleTest, ObjCImplementationThreeMethods)
{
testRuleOnObjCCode(new SwissArmyKnifeRule(), "@interface a\n@end\n@implementation a\n-(void)m {}\n+(void)n {}\n-(void)o {}\n@end\n");
}

TEST_F(SwissArmyKnifeRuleTest, ObjCImplementationFourMethods)
{
testRuleOnObjCCode(new SwissArmyKnifeRule(), "@interface a\n@end\n@implementation a\n-(void)m {}\n+(void)n {}\n-(void)o {}\n+(void)p {}\n@end\n",
0, 3, 1, 8, 1, "Objective-C implementation with 4 methods exceeds limit of 3");
}

TEST_F(SwissArmyKnifeRuleTest, ObjCImplementationFiveMethods)
{
testRuleOnObjCCode(new SwissArmyKnifeRule(), "@interface a\n@end\n@implementation a\n-(void)m {}\n+(void)n {}\n-(void)o {}\n+(void)p {}\n-(void)q {}\n@end\n",
0, 3, 1, 9, 1, "Objective-C implementation with 5 methods exceeds limit of 3");
}

TEST_F(SwissArmyKnifeRuleTest, ObjCCategoryImplThreeMethods)
{
testRuleOnObjCCode(new SwissArmyKnifeRule(), "@interface a\n@end\n@interface a (b)\n@end\n@implementation a (b)\n-(void)m {}\n+(void)n {}\n-(void)o {}\n@end\n@implementation a\n@end\n");
}

TEST_F(SwissArmyKnifeRuleTest, ObjCCategoryImplFourMethods)
{
testRuleOnObjCCode(new SwissArmyKnifeRule(), "@interface a\n@end\n@interface a (b)\n@end\n@implementation a (b)\n-(void)m {}\n+(void)n {}\n-(void)o {}\n+(void)p {}\n@end\n@implementation a\n@end\n",
0, 5, 1, 10, 1, "Objective-C implementation with 4 methods exceeds limit of 3");
}

TEST_F(SwissArmyKnifeRuleTest, ObjCCategoryImplFiveMethods)
{
testRuleOnObjCCode(new SwissArmyKnifeRule(), "@interface a\n@end\n@interface a (b)\n@end\n@implementation a (b)\n-(void)m {}\n+(void)n {}\n-(void)o {}\n+(void)p {}\n-(void)q {}\n@end\n@implementation a\n@end\n",
0, 5, 1, 11, 1, "Objective-C implementation with 5 methods exceeds limit of 3");
}

TEST_F(SwissArmyKnifeRuleTest, ObjCImplementationFourMethodsMethodsWithOneProperty)
{
testRuleOnObjCCode(new SwissArmyKnifeRule(), "@interface a\n{\nint i;\n}\n@property int i;\n@end\n@implementation a\n@synthesize i;\n-(void)m {}\n+(void)n {}\n-(void)o {}\n+(void)p {}\n-(void)q {}\n@end\n",
0, 7, 1, 14, 1, "Objective-C implementation with 7 methods exceeds limit of 3"); // NOTE: the property is synthesized with two more methods, a getter and a setter.
}
