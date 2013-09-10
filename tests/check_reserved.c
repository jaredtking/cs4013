#include "check_reserved.h"

START_TEST (test_reserved_words)
{
	ReservedWord *word = tokenize_reserved_word_str ("program\t100\t0");

	ck_assert(strcmp(word->name, "program") == 0);
	ck_assert(word->type == TOKEN_PROGRAM);
	ck_assert(word->attribute == TOKEN_NO_ATTRIBUTE);

	word = tokenize_reserved_word_str ("and\t118\t100");

	ck_assert(strcmp(word->name, "and") == 0);
	ck_assert(word->type == TOKEN_AND);
	ck_assert(word->attribute == TOKEN_PROGRAM);
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