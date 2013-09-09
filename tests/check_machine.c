#include "check_machine.h"

START_TEST (test_machine_ws)
{
	MachineResult *res = machine_ws("\n\n\n\t\t\t\t\t     \t\t\n");

	chk_assert(res->token != NULL);
	chk_assert(res->token->type == NOTFOUND);
	chk_assert(res->token->attribute == 0);
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