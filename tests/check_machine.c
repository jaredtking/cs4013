#include "check_machine.h"

// TODO need to verify f values

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

	// too long id
	res = machine_idres("thisidiswaytooooolong", reserved_words);

	ck_assert(res.err == MACHINE_ERR_ID_TOO_LONG);
	ck_assert(res.token == NULL);

	// invalid id
	res = machine_idres("#*(*%(&not an id", reserved_words);

	ck_assert(res.err == MACHINE_ERR_NO_MATCH);
	ck_assert(res.token == NULL);

	// check for reserved words
	res = machine_idres("while", reserved_words);

	// TODO this is incomplete
	ck_assert(res.err == MACHINE_ERR_NONE);
	ck_assert(res.token != NULL);
	ck_assert(res.token->type == TOKEN_RESERVED_WORD);
	ck_assert(res.token->attribute == TOKEN_NO_ATTRIBUTE);
}
END_TEST

START_TEST (test_machine_int)
{
	MachineResult res = machine_int("19274");

	ck_assert(res.err == MACHINE_ERR_NONE);
	ck_assert(res.token != NULL);
	ck_assert(res.token->type == TOKEN_NUM);
	ck_assert(res.token->attribute == TOKEN_ATTRIBUTE_INT);

	res = machine_int("notanint");

	ck_assert(res.err == MACHINE_ERR_NO_MATCH);
	ck_assert(res.token == NULL);

	res = machine_int("12345678901");

	ck_assert(res.err == MACHINE_ERR_INT_TOO_LONG);
	ck_assert(res.token == NULL);
}
END_TEST

START_TEST (test_machine_real)
{
	MachineResult res = machine_real("12.34");

	ck_assert(res.err == MACHINE_ERR_NONE);
	ck_assert(res.token != NULL);
	ck_assert(res.token->type == TOKEN_NUM);
	ck_assert(res.token->attribute == TOKEN_ATTRIBUTE_REAL);

	res = machine_real("123408");

	ck_assert(res.err == MACHINE_ERR_NO_MATCH);
	ck_assert(res.token == NULL);

	res = machine_real("123456.803");

	ck_assert(res.err == MACHINE_ERR_REAL_XX_TOO_LONG);
	ck_assert(res.token == NULL);

	res = machine_real("12.345678");

	ck_assert(res.err == MACHINE_ERR_REAL_YY_TOO_LONG);
	ck_assert(res.token == NULL);	
}
END_TEST

START_TEST (test_machine_longreal)
{
	MachineResult res = machine_longreal("12.34E+1");

	ck_assert(res.err == MACHINE_ERR_NONE);
	ck_assert(res.token != NULL);
	ck_assert(res.token->type == TOKEN_NUM);
	ck_assert(res.token->attribute == TOKEN_ATTRIBUTE_LONGREAL);

	res = machine_longreal("12.34E-22");

	ck_assert(res.err == MACHINE_ERR_NONE);
	ck_assert(res.token != NULL);
	ck_assert(res.token->type == TOKEN_NUM);
	ck_assert(res.token->attribute == TOKEN_ATTRIBUTE_LONGREAL);

	res = machine_longreal("12.34E13");

	ck_assert(res.err == MACHINE_ERR_NONE);
	ck_assert(res.token != NULL);
	ck_assert(res.token->type == TOKEN_NUM);
	ck_assert(res.token->attribute == TOKEN_ATTRIBUTE_LONGREAL);

	res = machine_longreal("123408");

	ck_assert(res.err == MACHINE_ERR_NO_MATCH);
	ck_assert(res.token == NULL);

	res = machine_longreal("123456.803E2");

	ck_assert(res.err == MACHINE_ERR_REAL_XX_TOO_LONG);
	ck_assert(res.token == NULL);

	res = machine_longreal("12.345678E1");

	ck_assert(res.err == MACHINE_ERR_REAL_YY_TOO_LONG);
	ck_assert(res.token == NULL);	

	res = machine_longreal("123456.803E123");

	ck_assert(res.err == MACHINE_ERR_REAL_ZZ_TOO_LONG);
	ck_assert(res.token == NULL);
}
END_TEST

Suite * machine_suite (void)
{
	Suite *s = suite_create ("Machines");

	/* Core test case */
	TCase *tc_core = tcase_create ("Core");

	tcase_add_test (tc_core, test_machine_ws);
	tcase_add_test (tc_core, test_machine_idres);
	tcase_add_test (tc_core, test_machine_int);
	tcase_add_test (tc_core, test_machine_real);
	tcase_add_test (tc_core, test_machine_longreal);

	suite_add_tcase (s, tc_core);

	return s;
}