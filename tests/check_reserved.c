#include "check_reserved.h"

START_TEST (test_reserved_words)
{
	ReservedWord *word = tokenize_reserved_word_str ("program\t1000\t0");

	ck_assert(strcmp(word->name, "program") == 0);
	ck_assert(word->token != NULL);
	ck_assert(word->token->type == TOKEN_PROGRAM);
	ck_assert(word->token->attribute == 0);

	word = tokenize_reserved_word_str ("and\t1018\t100");

	ck_assert(strcmp(word->name, "and") == 0);
	ck_assert(word->token != NULL);
	ck_assert(word->token->type == TOKEN_AND);
	ck_assert(word->token->attribute == 100);
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