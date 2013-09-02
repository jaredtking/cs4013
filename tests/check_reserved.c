#include "check_reserved.h"

const char *testLines[] =
{
	"lexeme\ttype\tattribute",
	"lexeme\ttype\tattribute",
	"lexeme\ttype\tattribute",
	"lexeme\ttype\tattribute",
	"lexeme\ttype\tattribute",
	"lexeme\ttype\tattribute",
	"lexeme\ttype\tattribute",
	"lexeme\ttype\tattribute",
	"lexeme\ttype\tattribute",
	"lexeme\ttype\tattribute",
	NULL
};

START_TEST (test_reserved_words)
{
	ReservedWordList list = tokenize_reserved_words (testLines);
}
END_TEST

Suite * reserved_suite (void)
{
	Suite *s = suite_create ("Reserved Words");

	/* Core test case */
	TCase *tc_core = tcase_create ("Core");
	tcase_add_test (tc_core, test_reserved_words);
	suite_add_tcase (s, tc_core);

	return s;
}