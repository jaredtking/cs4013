#include <stdlib.h>
#include <check.h>

START_TEST (hello_world)
{
	// todo	
}
END_TEST

Suite * machine_suite (void)
{
	Suite *s = suite_create ("Machines");

	/* Core test case */
//	TCase *tc_core = tcase_create ("Core");
//	tcase_add_test (tc_core, test_money_create);
//	suite_add_tcase (s, tc_core);

	return s;
}

int main (void)
{
	int number_failed;
	Suite *s = machine_suite ();
	SRunner *sr = srunner_create (s);
	srunner_run_all (sr, CK_NORMAL);
	number_failed = srunner_ntests_failed (sr);
	srunner_free (sr);
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}