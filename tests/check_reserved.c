#include "check_reserved.h"

START_TEST (reserved_words)
{
	char lines[10][72] = {
		{"lexeme\ttype\tattribute"},
		{"lexeme\ttype\tattribute"},
		{"lexeme\ttype\tattribute"},
		{"lexeme\ttype\tattribute"},
		{"lexeme\ttype\tattribute"},
		{"lexeme\ttype\tattribute"},
		{"lexeme\ttype\tattribute"},
		{"lexeme\ttype\tattribute"},
		{"lexeme\ttype\tattribute"},
		{"lexeme\ttype\tattribute"},
		{"lexeme\ttype\tattribute"}
	};
}
END_TEST

Suite * reserved_suite (void)
{
	Suite *s = suite_create ("Reserved Words");

	/* Core test case */
	TCase *tc_core = tcase_create ("Core");
	tcase_add_test (tc_core, reserved_words);
	suite_add_tcase (s, tc_core);

	return s;
}