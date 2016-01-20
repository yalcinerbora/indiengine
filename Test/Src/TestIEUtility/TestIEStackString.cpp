#include "gtest/gtest.h"
#include "../IETest.h"
#include "IEUtility/IEStackString.h"

// Constructors
TEST(IEStackString, Constructors)
{
	// Default Constructor
	IEStackString<> defaultString;
	EXPECT_EQ(defaultString.Length(), 0);

	// String Literal Style
	IEStackString<4> myString = "123";
	EXPECT_EQ('1', myString.Data()[0]);
	EXPECT_EQ('2', myString.Data()[1]);
	EXPECT_EQ('3', myString.Data()[2]);
	EXPECT_EQ(3, myString.Length());
	EXPECT_DEATH(IEStackString<8> deathString = "123456789", IE_TEST_ASSERT_FAIL_STRING);

	// STL String
	std::string myStringSTL = "123";
	std::string myStringSTLLong = "12345678";
	IEStackString<4> myString2(myStringSTL);	
	EXPECT_EQ('1', myString2.Data()[0]);
	EXPECT_EQ('2', myString2.Data()[1]);
	EXPECT_EQ('3', myString2.Data()[2]);
	EXPECT_EQ(3, myString2.Length());
	EXPECT_DEATH(IEStackString<7> deathString(myStringSTLLong), IE_TEST_ASSERT_FAIL_STRING);

	// const char array with size
	char charArray[] = "123";
	char charArrayLong[] = "12345678";
	IEStackString<4> myString3(charArray, 3);	
	EXPECT_EQ('1', myString3.Data()[0]);
	EXPECT_EQ('2', myString3.Data()[1]);
	EXPECT_EQ('3', myString3.Data()[2]);
	EXPECT_EQ(3, myString3.Length());
	EXPECT_DEATH(IEStackString<7> deathString(charArrayLong, 8), IE_TEST_ASSERT_FAIL_STRING);
	EXPECT_DEATH(IEStackString<7> deathString(charArrayLong, -1), IE_TEST_ASSERT_FAIL_STRING);

	// Copy Constructor
	IEStackString<4> myString4(myString);
	EXPECT_EQ('1', myString4.Data()[0]);
	EXPECT_EQ('2', myString4.Data()[1]);
	EXPECT_EQ('3', myString4.Data()[2]);
	EXPECT_EQ(3, myString4.Length());
}

TEST(IEStackString, AccessorMutator)
{
	IEStackString<> myString = "123";
	IEStackString<> myString2 = "123";
	IEStackString<> myString3 = "123";
	IEStackString<2> smallString;

	// Accessors Test (Data Is already tested with Constructors)
	EXPECT_EQ('1', myString.CharAt(0));
	EXPECT_EQ('2', myString.CharAt(1));
	EXPECT_EQ('3', myString.CharAt(2));
	EXPECT_DEATH(myString.CharAt(-1), IE_TEST_ASSERT_FAIL_STRING);
	EXPECT_DEATH(myString.CharAt(99), IE_TEST_ASSERT_FAIL_STRING);

	// Mutator Tests
	// Replace
	myString.Replace(0, 'A');
	EXPECT_EQ('A', myString.CharAt(0));
	EXPECT_DEATH(myString.Replace(-1, 'A'), IE_TEST_ASSERT_FAIL_STRING);
	EXPECT_DEATH(myString.Replace(99, 'A'), IE_TEST_ASSERT_FAIL_STRING);

	// Replace Range
	char newData[] = "ABC";
	myString2.Replace(0, newData, 3);
	EXPECT_EQ('A', myString2.CharAt(0));
	EXPECT_EQ('B', myString2.CharAt(1));
	EXPECT_EQ('C', myString2.CharAt(2));
	EXPECT_DEATH(myString.Replace(99, newData, 3), IE_TEST_ASSERT_FAIL_STRING);
	EXPECT_DEATH(myString.Replace(-1, newData, 3), IE_TEST_ASSERT_FAIL_STRING);

	myString3.Replace(1, newData, 2);
	EXPECT_EQ('1', myString3.CharAt(0));
	EXPECT_EQ('A', myString3.CharAt(1));
	EXPECT_EQ('B', myString3.CharAt(2));
	EXPECT_DEATH(myString.Replace(1, newData, 3), IE_TEST_ASSERT_FAIL_STRING);
	
	// Edit
	IEStackString<> emptyString;
	char* riskyPointer = emptyString.Edit();
	riskyPointer[0] = '9';
	riskyPointer[1] = '8';
	riskyPointer[2] = '7';
	EXPECT_NE(3, emptyString.Length());
	emptyString.LengthAfterEdit(3);
	EXPECT_EQ(3, emptyString.Length());
	EXPECT_EQ('9', emptyString.CharAt(0));
	EXPECT_EQ('8', emptyString.CharAt(1));
	EXPECT_EQ('7', emptyString.CharAt(2));
	EXPECT_DEATH(emptyString.LengthAfterEdit(-1), IE_TEST_ASSERT_FAIL_STRING);
	EXPECT_DEATH(emptyString.LengthAfterEdit(64), IE_TEST_ASSERT_FAIL_STRING);


	// = operators
	IEStackString<> copyDataSS = "!g!";
	myString3 = copyDataSS;
	EXPECT_EQ('!', myString3.Data()[0]);
	EXPECT_EQ('g', myString3.Data()[1]);
	EXPECT_EQ('!', myString3.Data()[2]);

	std::string copyDataSTL = "!g!";
	myString2 = copyDataSTL;
	EXPECT_EQ('!', myString2.Data()[0]);
	EXPECT_EQ('g', myString2.Data()[1]);
	EXPECT_EQ('!', myString2.Data()[2]);
	EXPECT_DEATH(smallString = copyDataSTL, IE_TEST_ASSERT_FAIL_STRING);

	myString = "!g!";
	EXPECT_EQ('!', myString.Data()[0]);
	EXPECT_EQ('g', myString.Data()[1]);
	EXPECT_EQ('!', myString.Data()[2]);
	EXPECT_DEATH(smallString = "!g!", IE_TEST_ASSERT_FAIL_STRING);
}

TEST(IEStackString, Operators)
{
	IEStackString<> string1 = "!g!";
	IEStackString<> string2 = "!g!";
	IEStackString<> string3 = "!A!";
	IEStackString<> string4 = "!!";

	// Equality
	EXPECT_TRUE(string1 == string2);
	EXPECT_FALSE(string1 == string3);
	EXPECT_FALSE(string1 == string4);

	// Inequality
	EXPECT_TRUE(string1 != string3);
	EXPECT_FALSE(string1 != string2);
	EXPECT_TRUE(string1 != string4);

	// Assignment
	string1 = string3;
	EXPECT_STREQ("!A!", string1.ToStlString().c_str());

	string1 = "Asd123";
	EXPECT_STREQ("Asd123", string1.ToStlString().c_str());

	std::string stlString("asd2222");
	string1 = stlString;
	EXPECT_STREQ("asd2222", string1.ToStlString().c_str());
}

TEST(IEStackString, Append)
{
	// Append A Char
	IEStackString<3> string;
	string.Append('2');
	EXPECT_EQ('2', string.CharAt(0));
	EXPECT_EQ(1, string.Length());
	string.Append('3');
	EXPECT_EQ('3', string.CharAt(1));
	EXPECT_EQ(2, string.Length());
	EXPECT_DEATH(string.Append('2'), IE_TEST_ASSERT_FAIL_STRING);

	// Append A String
	IEStackString<6> string2;
	IEStackString<6> string3 = "12";
	IEStackString<6> string4 = "9";

	string2.Append(string3);
	EXPECT_EQ('1', string2.CharAt(0));
	EXPECT_EQ('2', string2.CharAt(1));
	EXPECT_EQ(2, string2.Length());
	string2.Append(string3);
	EXPECT_EQ('1', string2.CharAt(0));
	EXPECT_EQ('2', string2.CharAt(1));
	EXPECT_EQ('1', string2.CharAt(2));
	EXPECT_EQ('2', string2.CharAt(3));
	EXPECT_EQ(4, string2.Length());
	string2.Append(string4);
	EXPECT_EQ('1', string2.CharAt(0));
	EXPECT_EQ('2', string2.CharAt(1));
	EXPECT_EQ('1', string2.CharAt(2));
	EXPECT_EQ('2', string2.CharAt(3));
	EXPECT_EQ('9', string2.CharAt(4));
	EXPECT_EQ(5, string2.Length());
	EXPECT_DEATH(string2.Append(string3), IE_TEST_ASSERT_FAIL_STRING);
	
	// Append A STL String
	IEStackString<6> string5;
	std::string string6 = "12";
	std::string string7 = "9";

	string5.Append(string6);
	EXPECT_EQ('1', string5.CharAt(0));
	EXPECT_EQ('2', string5.CharAt(1));
	EXPECT_EQ(2, string5.Length());
	string5.Append(string6);
	EXPECT_EQ('1', string5.CharAt(0));
	EXPECT_EQ('2', string5.CharAt(1));
	EXPECT_EQ('1', string5.CharAt(2));
	EXPECT_EQ('2', string5.CharAt(3));
	EXPECT_EQ(4, string5.Length());
	string5.Append(string7);
	EXPECT_EQ('1', string5.CharAt(0));
	EXPECT_EQ('2', string5.CharAt(1));
	EXPECT_EQ('1', string5.CharAt(2));
	EXPECT_EQ('2', string5.CharAt(3));
	EXPECT_EQ('9', string5.CharAt(4));
	EXPECT_EQ(5, string5.Length());
	EXPECT_DEATH(string5.Append(string6), IE_TEST_ASSERT_FAIL_STRING);
	
	// Append A  C String sizeless
	IEStackString<6> string8;

	string8.Append("12");
	EXPECT_EQ('1', string8.CharAt(0));
	EXPECT_EQ('2', string8.CharAt(1));
	EXPECT_EQ(2, string8.Length());
	string8.Append("12");
	EXPECT_EQ('1', string8.CharAt(0));
	EXPECT_EQ('2', string8.CharAt(1));
	EXPECT_EQ('1', string8.CharAt(2));
	EXPECT_EQ('2', string8.CharAt(3));
	EXPECT_EQ(4, string8.Length());
	string8.Append("9");
	EXPECT_EQ('1', string8.CharAt(0));
	EXPECT_EQ('2', string8.CharAt(1));
	EXPECT_EQ('1', string8.CharAt(2));
	EXPECT_EQ('2', string8.CharAt(3));
	EXPECT_EQ('9', string8.CharAt(4));
	EXPECT_EQ(5, string8.Length());
	EXPECT_DEATH(string8.Append("12"), IE_TEST_ASSERT_FAIL_STRING);
	
	// Append A  C String With Size
	IEStackString<6> string9;

	string9.Append("12", 2);
	EXPECT_EQ('1', string9.CharAt(0));
	EXPECT_EQ('2', string9.CharAt(1));
	EXPECT_EQ(2, string9.Length());
	string9.Append("12", 2);
	EXPECT_EQ('1', string9.CharAt(0));
	EXPECT_EQ('2', string9.CharAt(1));
	EXPECT_EQ('1', string9.CharAt(2));
	EXPECT_EQ('2', string9.CharAt(3));
	EXPECT_EQ(4, string9.Length());
	string9.Append("9", 1);
	EXPECT_EQ('1', string9.CharAt(0));
	EXPECT_EQ('2', string9.CharAt(1));
	EXPECT_EQ('1', string9.CharAt(2));
	EXPECT_EQ('2', string9.CharAt(3));
	EXPECT_EQ('9', string9.CharAt(4));
	EXPECT_EQ(5, string9.Length());
	EXPECT_DEATH(string9.Append("12", 2), IE_TEST_ASSERT_FAIL_STRING);
	EXPECT_DEATH(string9.Append("12", -1), IE_TEST_ASSERT_FAIL_STRING);
}

TEST(IEStackString, SubstringTrim)
{
	// SubString
	IEStackString<> string = "1234567890";
	IEStackString<> subString = string.SubString(0, string.Length());
	EXPECT_EQ('1',subString.CharAt(0));
	EXPECT_EQ('2', subString.CharAt(1));
	EXPECT_EQ('3', subString.CharAt(2));
	EXPECT_EQ('4', subString.CharAt(3));
	EXPECT_EQ('5', subString.CharAt(4));
	EXPECT_EQ('6', subString.CharAt(5));
	EXPECT_EQ('7', subString.CharAt(6));
	EXPECT_EQ('8', subString.CharAt(7));
	EXPECT_EQ('9', subString.CharAt(8));
	EXPECT_EQ('0', subString.CharAt(9));
	EXPECT_EQ(10, subString.Length());

	subString = string.SubString(1, 2);
	EXPECT_EQ('2', subString.CharAt(0));
	EXPECT_EQ(1, subString.Length());

	subString = string.SubString(2, 5);
	EXPECT_EQ('3', subString.CharAt(0));
	EXPECT_EQ('4', subString.CharAt(1));
	EXPECT_EQ('5', subString.CharAt(2));
	EXPECT_EQ(3, subString.Length());
	
	EXPECT_DEATH(string.SubString(2, 2), IE_TEST_ASSERT_FAIL_STRING);
	EXPECT_DEATH(string.SubString(3, 2), IE_TEST_ASSERT_FAIL_STRING);
	EXPECT_DEATH(string.SubString(-1, 2), IE_TEST_ASSERT_FAIL_STRING);
	EXPECT_DEATH(string.SubString(3, 22), IE_TEST_ASSERT_FAIL_STRING);

	// Trim
	IEStackString<> trimString = string;

	trimString.Trim(0, trimString.Length());
	EXPECT_EQ('1', trimString.CharAt(0));
	EXPECT_EQ('2', trimString.CharAt(1));
	EXPECT_EQ('3', trimString.CharAt(2));
	EXPECT_EQ('4', trimString.CharAt(3));
	EXPECT_EQ('5', trimString.CharAt(4));
	EXPECT_EQ('6', trimString.CharAt(5));
	EXPECT_EQ('7', trimString.CharAt(6));
	EXPECT_EQ('8', trimString.CharAt(7));
	EXPECT_EQ('9', trimString.CharAt(8));
	EXPECT_EQ('0', trimString.CharAt(9));
	EXPECT_EQ(10, trimString.Length());

	trimString = string;
	trimString.Trim(1, 2);
	EXPECT_EQ('2', trimString.CharAt(0));
	EXPECT_EQ(1, trimString.Length());

	trimString = string;
	trimString.Trim(2, 5);
	EXPECT_EQ('3', trimString.CharAt(0));
	EXPECT_EQ('4', trimString.CharAt(1));
	EXPECT_EQ('5', trimString.CharAt(2));
	EXPECT_EQ(3, trimString.Length());
	
	EXPECT_DEATH(trimString.Trim(2, 2), IE_TEST_ASSERT_FAIL_STRING);
	EXPECT_DEATH(trimString.Trim(3, 2), IE_TEST_ASSERT_FAIL_STRING);
	EXPECT_DEATH(trimString.Trim(-1, 2), IE_TEST_ASSERT_FAIL_STRING);
	EXPECT_DEATH(trimString.Trim(3, 22), IE_TEST_ASSERT_FAIL_STRING);
}

TEST(IEStackString, EmptyLengthClear)
{
	IEStackString<> empty;
	IEStackString<> notEmpty = "21311";

	// Empty
	EXPECT_TRUE(empty.IsEmpty());
	EXPECT_FALSE(notEmpty.IsEmpty());

	// Length
	EXPECT_EQ(5, notEmpty.Length());

	// Max Length
	EXPECT_EQ(IE_STACK_STRING_DEFAULT_LENGTH, empty.MaxLength());

	// Clear
	notEmpty.Clear();
	EXPECT_TRUE(notEmpty.IsEmpty());
}

TEST(IEStackString, ConcatIndexOf)
{
	// Concat
	IEStackString<7> string1 = "123";
	IEStackString<7> string2 = "568";
	IEStackString<7> result = string1.Concatenate<7>(string2);
	IEStackString<7> death;

	EXPECT_EQ('1', result.CharAt(0));
	EXPECT_EQ('2', result.CharAt(1));
	EXPECT_EQ('3', result.CharAt(2));
	EXPECT_EQ('5', result.CharAt(3));
	EXPECT_EQ('6', result.CharAt(4));
	EXPECT_EQ('8', result.CharAt(5));
	EXPECT_EQ(6, result.Length());
	EXPECT_DEATH(death = result.Concatenate<7>(string1), IE_TEST_ASSERT_FAIL_STRING);
	
	// First Index Of
	IEStackString<> findString = "kas takas as pas lapas";
	// Char
	EXPECT_EQ(1, findString.FirstIndexOf('a'));
	EXPECT_EQ(0, findString.FirstIndexOf('k'));
	EXPECT_EQ(-1, findString.FirstIndexOf('1'));

	// C String
	EXPECT_EQ(1, findString.FirstIndexOf("as", 2));
	EXPECT_EQ(13, findString.FirstIndexOf("pas", 3));
	EXPECT_EQ(4, findString.FirstIndexOf("takas", 5));
	EXPECT_EQ(-1, findString.FirstIndexOf("stuff", 5));
	EXPECT_DEATH(findString.FirstIndexOf("stuff", -1), IE_TEST_ASSERT_FAIL_STRING);

	// Stack String
	IEStackString<> as("as");
	IEStackString<> pas("pas");
	IEStackString<> takas("takas");
	IEStackString<> stuff("stuff");
	EXPECT_EQ(1, findString.FirstIndexOf(as));
	EXPECT_EQ(13, findString.FirstIndexOf(pas));
	EXPECT_EQ(4, findString.FirstIndexOf(takas));
	EXPECT_EQ(-1, findString.FirstIndexOf(stuff));
	EXPECT_EQ(0, findString.FirstIndexOf(findString));

	// Last Index Of
	// Char
	//IEStackString<> findString = "kas takas as pas lapas"
	EXPECT_EQ(20, findString.LastIndexOf('a'));
	EXPECT_EQ(6, findString.LastIndexOf('k'));
	EXPECT_EQ(-1, findString.LastIndexOf('1'));

	// C String
	EXPECT_EQ(20, findString.LastIndexOf("as", 2));
	EXPECT_EQ(19, findString.LastIndexOf("pas", 3));
	EXPECT_EQ(4, findString.LastIndexOf("takas", 5));
	EXPECT_EQ(-1, findString.LastIndexOf("stuff", 5));
	EXPECT_DEATH(findString.LastIndexOf("stuff", -1), IE_TEST_ASSERT_FAIL_STRING);

	// Stack String
	EXPECT_EQ(20, findString.LastIndexOf(as));
	EXPECT_EQ(19, findString.LastIndexOf(pas));
	EXPECT_EQ(4, findString.LastIndexOf(takas));
	EXPECT_EQ(-1, findString.LastIndexOf(stuff));
	EXPECT_EQ(0, findString.LastIndexOf(findString));
}