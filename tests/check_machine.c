#include "check_machine.h"

START_TEST (test_machine)
{
	// todo	
}
END_TEST

Suite * machine_suite (void)
{
	Suite *s = suite_create ("Machines");

	/* Core test case */
	TCase *tc_core = tcase_create ("Core");
	tcase_add_test (tc_core, test_machine);
	suite_add_tcase (s, tc_core);

	return s;
}