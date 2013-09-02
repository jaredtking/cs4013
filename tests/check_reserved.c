#include "check_reserved.h"

START_TEST (hello_world)
{
	// todo	
}
END_TEST

Suite * reserved_suite (void)
{
	Suite *s = suite_create ("Reserved Words");

	/* Core test case */
//	TCase *tc_core = tcase_create ("Core");
//	tcase_add_test (tc_core, test_money_create);
//	suite_add_tcase (s, tc_core);

	return s;
}