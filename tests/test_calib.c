/*
 * libms5803 - MS5803 pressure sensor library
 *
 * Copyright (C) 2014 by Artur Wroblewski <wrobell@pld-linux.org>
 *
 * Also contains code from
 *
 *      http://www.john.geek.nz/2013/02/update-bosch-ms5803-source-raspberry-pi/
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <check.h>

#include "../src/ms5803.c"

/* calibration coefficients from the datasheet */
#define CALIB_1 \
    calib_coeff[0] =  0; \
    calib_coeff[1] =  46546; \
    calib_coeff[2] =  42845; \
    calib_coeff[3] =  29751; \
    calib_coeff[4] =  29457; \
    calib_coeff[5] =  32745; \
    calib_coeff[6] =  29059; \
    calib_coeff[7] =  0;


#define CALIB_2 \
    calib_coeff[0] = 0; \
    calib_coeff[1] = 47226; \
    calib_coeff[2] = 41213; \
    calib_coeff[3] = 30141; \
    calib_coeff[4] = 28269; \
    calib_coeff[5] = 32976; \
    calib_coeff[6] = 28973; \
    calib_coeff[7] = 11;

#define CALIB_3 \
    calib_coeff[0] = 0; \
    calib_coeff[1] = 45432; \
    calib_coeff[2] = 39480; \
    calib_coeff[3] = 28558; \
    calib_coeff[4] = 26566; \
    calib_coeff[5] = 33269; \
    calib_coeff[6] = 28617; \
    calib_coeff[7] = 5;

#define CALIB_4 \
    calib_coeff[0] = 0; \
    calib_coeff[1] = 46702; \
    calib_coeff[2] = 40932; \
    calib_coeff[3] = 29775; \
    calib_coeff[4] = 27943; \
    calib_coeff[5] = 32284; \
    calib_coeff[6] = 29002; \
    calib_coeff[7] = 1;

#define CALIB_5 \
    calib_coeff[0] = 0; \
    calib_coeff[1] = 46205; \
    calib_coeff[2] = 41291; \
    calib_coeff[3] = 29184; \
    calib_coeff[4] = 28034; \
    calib_coeff[5] = 33225; \
    calib_coeff[6] = 28810; \
    calib_coeff[7] = 0;


/* calibration coefficients set no 1, temp +20C
 * example from the datasheet */
START_TEST(test_20C_plus_calib_1) {
    uint32_t d1, d2;
    int32_t pressure, temp;

    CALIB_1;

    d1 = 4311550;
    d2 = 8387300;

    calculate(d1, d2, &pressure, &temp);
	ck_assert_int_eq(10005, pressure);
	ck_assert_int_eq(2015, temp);
}
END_TEST


/* calibration coefficients set no 2, temp +20C */
START_TEST(test_20C_plus_calib_2) {
    uint32_t d1, d2;
    int32_t pressure, temp;

    CALIB_2;

    d1 = 4092540;
    d2 = 8467198;

    calculate(d1, d2, &pressure, &temp);
	ck_assert_int_eq(9741, pressure);
	ck_assert_int_eq(2087, temp);
}
END_TEST


/* calibration coefficients set no 2, temp below 20C */
START_TEST(test_20C_below_calib_2) {
    uint32_t d1, d2;
    int32_t pressure, temp;

    CALIB_2;

    d1 = 4094270;
    d2 = 8413580;

    calculate(d1, d2, &pressure, &temp);
	ck_assert_int_eq(9765, pressure);
	ck_assert_int_eq(1902, temp);
}
END_TEST


/* calibration coefficients set no 2, temp below 15C */
START_TEST(test_15C_below_calib_2) {
    uint32_t d1, d2;
    int32_t pressure, temp;

    CALIB_2;

    d1 = 4113716;
    d2 = 8286844;

    calculate(d1, d2, &pressure, &temp);
	ck_assert_int_eq(10163, pressure);
	ck_assert_int_eq(1456, temp);
}
END_TEST


/* calibration coefficients set no 3, temp +20C */
START_TEST(test_20C_plus_calib_3) {
    uint32_t d1, d2;
    int32_t pressure, temp;

    CALIB_3;

    d1 = 4113354;
    d2 = 8588738;

    calculate(d1, d2, &pressure, &temp);
	ck_assert_int_eq(10175, pressure);
	ck_assert_int_eq(2245, temp);
}
END_TEST


/* calibration coefficients set no 4, temp +20C */
START_TEST(test_20C_plus_calib_4) {
    uint32_t d1, d2;
    int32_t pressure, temp;

    CALIB_4;

    d1 = 4130828;
    d2 = 8333696;

    calculate(d1, d2, &pressure, &temp);
	ck_assert_int_eq(10149, pressure);
	ck_assert_int_eq(2238, temp);
}
END_TEST


/* calibration coefficients set no 5, temp +20C */
START_TEST(test_20C_plus_calib_5) {
    uint32_t d1, d2;
    int32_t pressure, temp;

    CALIB_5;

    d1 = 4206974;
    d2 = 8653124;

    calculate(d1, d2, &pressure, &temp);
	ck_assert_int_eq(10150, pressure);
	ck_assert_int_eq(2505, temp);
}
END_TEST


/* calibration coefficients set no 5, temp below 20C */
START_TEST(test_20C_below_calib_5) {
    uint32_t d1, d2;
    int32_t pressure, temp;

    CALIB_5;

    d1 = 4209022;
    d2 = 8502600;

    calculate(d1, d2, &pressure, &temp);
	ck_assert_int_eq(10151, pressure);
	ck_assert_int_eq(1989, temp);
}
END_TEST


Suite *test_suite(void) {
	Suite *s = suite_create("MS5803");

	TCase *tc = tcase_create("Calibration");

	tcase_add_test(tc, test_20C_plus_calib_1);
	tcase_add_test(tc, test_20C_plus_calib_2);
	tcase_add_test(tc, test_20C_below_calib_2);
	tcase_add_test(tc, test_15C_below_calib_2);
	tcase_add_test(tc, test_20C_plus_calib_3);
	tcase_add_test(tc, test_20C_plus_calib_4);
	tcase_add_test(tc, test_20C_plus_calib_5);
	tcase_add_test(tc, test_20C_below_calib_5);

	suite_add_tcase(s, tc);

	return s;
}

int main(void) {
	int number_failed;
	Suite *s = test_suite();
	SRunner *sr = srunner_create(s);
	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

/*
 * vim: sw=4:et:ai
 */
