#include "check_machine.h"

START_TEST (test_machine_ws)
{
	MachineResult res = machine_whitespace("\n\n\n\t\t\t\t\t     \t\t\n");

	ck_assert(res.err == MACHINE_ERR_NONE);
	ck_assert(res.token != NULL);
	ck_assert(res.token->type == TOKEN_WHITESPACE);
	ck_assert(res.token->attribute == 0);

	res = machine_whitespace("");

	ck_assert(res.err == MACHINE_ERR_NO_MATCH);
	ck_assert(res.token == NULL);

	res = machine_whitespace("not whitespace");

	ck_assert(res.err == MACHINE_ERR_NO_MATCH);
	ck_assert(res.token == NULL);
}
END_TEST

Suite * machine_suite (void)
{
	Suite *s = suite_create ("Machines");

	/* Core test case */
	TCase *tc_core = tcase_create ("Core");
	tcase_add_test (tc_core, test_machine_ws);
	suite_add_tcase (s, tc_core);

	return s;
}