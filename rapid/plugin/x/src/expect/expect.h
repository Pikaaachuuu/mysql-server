/*
 * Copyright (c) 2017, Oracle and/or its affiliates. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; version 2 of the
 * License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301  USA
 */

#ifndef X_SRC_EXPECT_EXPECT_H_
#define X_SRC_EXPECT_EXPECT_H_

#include <deque>
#include <utility>
#include <string>
#include <memory>

#include "expect/expect_condition.h"
#include "ngs_common/protocol_protobuf.h"


namespace xpl {

class Expectation {
 public:
  using Expect_condition_ptr = std::unique_ptr<Expect_condition>;

 public:
  Expectation() : m_fail_on_error(false) {}
  Expectation(const Expectation &other);

  /*
    Make a copy of "other" element while calling assignment operator.
    This way we do not need temporary variable while swapping.
  */
  Expectation &operator =(Expectation other);

  // whether an error occurred previously in a no_error block
  void set_failed(const ngs::Error_code &error) { m_error = error; }
  bool failed() const { return m_error; }
  bool fail_on_error() const { return m_fail_on_error; }
  ngs::Error_code error() const;

  ngs::Error_code check_conditions();

  void unset(const uint32_t key, const std::string &value);
  ngs::Error_code set(const uint32_t key, const std::string &value);

  void add_condition(Expect_condition_ptr condition);

 private:
  static void swap(Expectation &one, Expectation &other);

  std::deque<Expect_condition_ptr> m_conditions;
  ngs::Error_code m_error;
  bool m_fail_on_error;
};

}  // namespace xpl


#endif  // X_SRC_EXPECT_EXPECT_H_
