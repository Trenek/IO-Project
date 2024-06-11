/*
 *  CUnit - A Unit testing framework library for C.
 *  Copyright (C) 2004-2024  Jerry St.Clair, Ian Norton
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
 * Extended assertion helper wrapper functions.
 */

#ifndef CUNIT_CUASSERT_H
#define CUNIT_CUASSERT_H

#ifdef __cplusplus
extern "C" {
#endif

/** Asserts that two values are equal and prints the values in the test log if they were not
 * equal.
 */
#define CU_ASSERT_EQUAL_VALUE_TYPE(actual, expected, type, fmt) \
  do { int cu_assert_line = __LINE__;                           \
    type expected_value = expected;                             \
    type actual_value = actual;                                 \
    if (actual_value != expected_value) {                       \
        char msgbuf[255] = {0};                                 \
        snprintf(msgbuf, sizeof(msgbuf),                        \
            "CU_ASSERT_EQUAL_VALUE_TYPE("                       \
            fmt " == " fmt ")", actual_value, expected_value);  \
        CU_assertImplementation(CU_FALSE,                       \
        cu_assert_line,                                         \
        msgbuf,                                                 \
        __FILE__, CU_FUNC, CU_TRUE                              \
        );                                                      \
    }                                                           \
  } while(0)


/** Asserts that two arguments are equal using a compare function that returns 0 for equality
 * and prints the values in the test log if they were not equal.
 */
#define CU_ASSERT_EQUAL_CMP_TYPE(actual, expected, compfn, type, fmt) \
  do { int cu_assert_line = __LINE__;                                 \
    type expected_value = expected;                                   \
    type actual_value = actual;                                       \
    if (compfn(actual_value, expected_value) != 0) {                  \
        char msgbuf[255] = {0};                                       \
        snprintf(msgbuf, sizeof(msgbuf),                              \
            "CU_ASSERT_EQUAL_CMP_TYPE(" #compfn "(\""                 \
             fmt "\", \"" fmt "\"))", actual_value, expected_value);  \
        CU_assertImplementation(CU_FALSE,                             \
        cu_assert_line,                                               \
        msgbuf,                                                       \
        __FILE__, CU_FUNC, CU_TRUE                                    \
        );                                                            \
    }                                                                 \
  } while(0)


#ifdef __cplusplus // extern C
}
#endif

#endif // CUNIT_CUASSERT_H
