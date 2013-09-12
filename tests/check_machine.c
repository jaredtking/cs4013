#include "check_machine.h"

// TODO need to verify f values

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

START_TEST (test_machine_idres)
{
	// build a reserved word list
	ReservedWord *reserved_words = tokenize_reserved_word_str ("program\t1000\t0");
	ReservedWord *next = tokenize_reserved_word_str ("begin\t1007\t0");
	ReservedWord *next2 = tokenize_reserved_word_str ("while\t1012\t0");
	reserved_words->next = next;
	next->next = next2;

	// valid id
	MachineResult res = machine_idres("isthisanid", reserved_words);

	ck_assert(res.err == MACHINE_ERR_NONE);
	ck_assert(res.token != NULL);
	ck_assert(res.token->type == TOKEN_ID);
	ck_assert(res.token->attribute == 0);

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

	ck_assert(res.err == MACHINE_ERR_NONE);
	ck_assert(res.token != NULL);
	ck_assert(res.token->type == TOKEN_WHILE);
	ck_assert(res.token->attribute == 0);
}
END_TEST

START_TEST (test_machine_int)
{
	MachineResult res = machine_int("1234567890");

	ck_assert(res.err == MACHINE_ERR_NONE);
	ck_assert(res.token != NULL);
	ck_assert(res.token->type == TOKEN_NUM);
	ck_assert(res.token->attribute == ATTRIBUTE_INT);

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
	MachineResult res = machine_real("12.34567");

	ck_assert(res.err == MACHINE_ERR_NONE);
	ck_assert(res.token != NULL);
	ck_assert(res.token->type == TOKEN_NUM);
	ck_assert(res.token->attribute == ATTRIBUTE_REAL);

	res = machine_real("12345.");

	ck_assert(res.err == MACHINE_ERR_NONE);
	ck_assert(res.token != NULL);
	ck_assert(res.token->type == TOKEN_NUM);
	ck_assert(res.token->attribute == ATTRIBUTE_REAL);

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
	MachineResult res = machine_longreal("12345.01E+1");

	ck_assert(res.err == MACHINE_ERR_NONE);
	ck_assert(res.token != NULL);
	ck_assert(res.token->type == TOKEN_NUM);
	ck_assert(res.token->attribute == ATTRIBUTE_LONGREAL);

	res = machine_longreal("12.34567E-22");

	ck_assert(res.err == MACHINE_ERR_NONE);
	ck_assert(res.token != NULL);
	ck_assert(res.token->type == TOKEN_NUM);
	ck_assert(res.token->attribute == ATTRIBUTE_LONGREAL);

	res = machine_longreal("12.E13");

	ck_assert(res.err == MACHINE_ERR_NONE);
	ck_assert(res.token != NULL);
	ck_assert(res.token->type == TOKEN_NUM);
	ck_assert(res.token->attribute == ATTRIBUTE_LONGREAL);

	res = machine_longreal("123408");

	ck_assert(res.err == MACHINE_ERR_NO_MATCH);
	ck_assert(res.token == NULL);

	res = machine_longreal("1234.08");

	ck_assert(res.err == MACHINE_ERR_NO_MATCH);
	ck_assert(res.token == NULL);

	res = machine_longreal("123456.803E+2");

	ck_assert(res.err == MACHINE_ERR_REAL_XX_TOO_LONG);
	ck_assert(res.token == NULL);

	res = machine_longreal("12.345678E+1");

	ck_assert(res.err == MACHINE_ERR_REAL_YY_TOO_LONG);
	ck_assert(res.token == NULL);	

	res = machine_longreal("12345.803E-123");

	ck_assert(res.err == MACHINE_ERR_REAL_ZZ_TOO_LONG);
	ck_assert(res.token == NULL);
}
END_TEST

START_TEST (test_machine_relop)
{
	MachineResult res = machine_relop(">");

	ck_assert(res.err == MACHINE_ERR_NONE);
	ck_assert(res.token != NULL);
	ck_assert(res.token->type == TOKEN_RELOP);
	ck_assert(res.token->attribute == '>');

	res = machine_relop(">=");

	ck_assert(res.err == MACHINE_ERR_NONE);
	ck_assert(res.token != NULL);
	ck_assert(res.token->type == TOKEN_RELOP);
	ck_assert(res.token->attribute == ATTRIBUTE_GE);

	res = machine_relop("<");

	ck_assert(res.err == MACHINE_ERR_NONE);
	ck_assert(res.token != NULL);
	ck_assert(res.token->type == TOKEN_RELOP);
	ck_assert(res.token->attribute == '<');

	res = machine_relop("<=");

	ck_assert(res.err == MACHINE_ERR_NONE);
	ck_assert(res.token != NULL);
	ck_assert(res.token->type == TOKEN_RELOP);
	ck_assert(res.token->attribute == ATTRIBUTE_LE);

	res = machine_relop("<>");

	ck_assert(res.err == MACHINE_ERR_NONE);
	ck_assert(res.token != NULL);
	ck_assert(res.token->type == TOKEN_RELOP);
	ck_assert(res.token->attribute == ATTRIBUTE_NE);

	res = machine_relop("=");

	ck_assert(res.err == MACHINE_ERR_NONE);
	ck_assert(res.token != NULL);
	ck_assert(res.token->type == TOKEN_RELOP);
	ck_assert(res.token->attribute == '=');

	res = machine_relop("notarelop");

	ck_assert(res.err == MACHINE_ERR_NO_MATCH);
	ck_assert(res.token == NULL);
}
END_TEST

START_TEST (test_machine_catchall)
{
	MachineResult res = machine_catchall("+");

	ck_assert(res.err == MACHINE_ERR_NONE);
	ck_assert(res.token != NULL);
	ck_assert(res.token->type == TOKEN_ADDOP);
	ck_assert(res.token->attribute == '+');

	res = machine_catchall("-");

	ck_assert(res.err == MACHINE_ERR_NONE);
	ck_assert(res.token != NULL);
	ck_assert(res.token->type == TOKEN_ADDOP);
	ck_assert(res.token->attribute == '-');

	res = machine_catchall("*");

	ck_assert(res.err == MACHINE_ERR_NONE);
	ck_assert(res.token != NULL);
	ck_assert(res.token->type == TOKEN_MULOP);
	ck_assert(res.token->attribute == '*');

	res = machine_catchall("/");

	ck_assert(res.err == MACHINE_ERR_NONE);
	ck_assert(res.token != NULL);
	ck_assert(res.token->type == TOKEN_MULOP);
	ck_assert(res.token->attribute == '/');

	res = machine_catchall(",");

	ck_assert(res.err == MACHINE_ERR_NONE);
	ck_assert(res.token != NULL);
	ck_assert(res.token->type == TOKEN_COMMA);
	ck_assert(res.token->attribute == 0);

	res = machine_catchall(".");

	ck_assert(res.err == MACHINE_ERR_NONE);
	ck_assert(res.token != NULL);
	ck_assert(res.token->type == TOKEN_PERIOD);
	ck_assert(res.token->attribute == 0);

	res = machine_catchall(";");

	ck_assert(res.err == MACHINE_ERR_NONE);
	ck_assert(res.token != NULL);
	ck_assert(res.token->type == TOKEN_SEMICOLON);
	ck_assert(res.token->attribute == 0);

	res = machine_catchall("(");

	ck_assert(res.err == MACHINE_ERR_NONE);
	ck_assert(res.token != NULL);
	ck_assert(res.token->type == TOKEN_LPAREN);
	ck_assert(res.token->attribute == 0);

	res = machine_catchall(")");

	ck_assert(res.err == MACHINE_ERR_NONE);
	ck_assert(res.token != NULL);
	ck_assert(res.token->type == TOKEN_RPAREN);
	ck_assert(res.token->attribute == 0);

	res = machine_catchall("[");

	ck_assert(res.err == MACHINE_ERR_NONE);
	ck_assert(res.token != NULL);
	ck_assert(res.token->type == TOKEN_LBRACKET);
	ck_assert(res.token->attribute == 0);

	res = machine_catchall("]");

	ck_assert(res.err == MACHINE_ERR_NONE);
	ck_assert(res.token != NULL);
	ck_assert(res.token->type == TOKEN_RBRACKET);
	ck_assert(res.token->attribute == 0);

	res = machine_catchall(":");

	ck_assert(res.err == MACHINE_ERR_NONE);
	ck_assert(res.token != NULL);
	ck_assert(res.token->type == TOKEN_COLON);
	ck_assert(res.token->attribute == 0);

	res = machine_catchall(":=");

	ck_assert(res.err == MACHINE_ERR_NONE);
	ck_assert(res.token != NULL);
	ck_assert(res.token->type == TOKEN_ASSIGNOP);
	ck_assert(res.token->attribute == 0);

	res = machine_catchall("thisdoesnotwork");

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
	tcase_add_test (tc_core, test_machine_idres);
	tcase_add_test (tc_core, test_machine_int);
	tcase_add_test (tc_core, test_machine_real);
	tcase_add_test (tc_core, test_machine_longreal);
	tcase_add_test (tc_core, test_machine_relop);
	tcase_add_test (tc_core, test_machine_catchall);

	suite_add_tcase (s, tc_core);

	return s;
}