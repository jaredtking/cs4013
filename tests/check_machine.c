#include "check_machine.h"

START_TEST (test_machine_ws)
{
	MachineResult res = machine_whitespace("\n\n\n\t\t\t\t\t     \t\t\n");

	ck_assert(res.err == MACHINE_ERR_NONE);
	ck_assert(res.token != NULL);
	ck_assert(res.token->type == TOKEN_WHITESPACE);
	ck_assert(res.token->attribute == TOKEN_NO_ATTRIBUTE);

	res = machine_whitespace("");

	ck_assert(res.err == MACHINE_ERR_NO_MATCH);
	ck_assert(res.token == NULL);

	res = machine_whitespace("not whitespace");

	ck_assert(res.err == MACHINE_ERR_NO_MATCH);
	ck_assert(res.token == NULL);
}
END_TEST

START_TEST (test_machine_idres)
{
	// build a reserved word list
	ReservedWord *reserved_words = tokenize_reserved_word_str ("program\t100\t0");
	ReservedWord *next = tokenize_reserved_word_str ("begin\t107\t0");
	ReservedWord *next2 = tokenize_reserved_word_str ("while\t112\t0");
	reserved_words->next = next;
	next->next = next2;

	// valid id
	MachineResult res = machine_idres("isthisanid", reserved_words);

	ck_assert(res.err == MACHINE_ERR_NONE);
	ck_assert(res.token != NULL);
	ck_assert(res.token->type == TOKEN_ID);
	ck_assert(res.token->attribute == TOKEN_NO_ATTRIBUTE);

	// invalid id
	res = machine_idres("#*(*%(&not an id", reserved_words);

	ck_assert(res.err == MACHINE_ERR_NO_MATCH);
	ck_assert(res.token == NULL);

	// check for reserved words
	// TODO
}
END_TEST

Suite * machine_suite (void)
{
	Suite *s = suite_create ("Machines");

	/* Core test case */
	TCase *tc_core = tcase_create ("Core");
	tcase_add_test (tc_core, test_machine_ws);
	tcase_add_test (tc_core, test_machine_idres);
	suite_add_tcase (s, tc_core);

	return s;
}