#include "check_reserved.h"

START_TEST (test_reserved_words)
{
	ReservedWord *word = tokenize_reserved_word_str ("program\t100\t0");

	ck_assert_msg(strcmp(word->name, "program") == 0, "Was expecting name program, but found %s", word->name);
	ck_assert_msg(word->type == 100, "Was expecting type 100, but found %d", word->type);
	ck_assert_msg(word->attribute == 0, "Was expecting attribute 0, but found %d", word->attribute);

	word = tokenize_reserved_word_str ("and\t1001\t48");

	ck_assert_msg(strcmp(word->name, "and") == 0, "Was expecting name program, but found %s", word->name);
	ck_assert_msg(word->type == 1001, "Was expecting type 1001, but found %d", word->type);
	ck_assert_msg(word->attribute == 48, "Was expecting attribute 48, but found %d", word->attribute);
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