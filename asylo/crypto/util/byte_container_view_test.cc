/*
 *
 * Copyright 2017 Asylo authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "asylo/crypto/util/byte_container_view.h"

#include <iterator>
#include <string>
#include <vector>

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "asylo/crypto/util/bytes.h"

namespace asylo {
namespace {

constexpr char kData1[] =
    "Mary had a little lamb, its fleece was white as snow";
constexpr size_t kSize1 = sizeof(kData1) - 1;
constexpr char kData2[] = "Mary had a big pig, and it had no fleece";

// A typed test fixture is used for tests that require a single type object.
template <typename T>
class TypedByteContainerViewTest : public ::testing::Test {
 public:
};

typedef ::testing::Types<SafeBytes<kSize1>, UnsafeBytes<kSize1>,
                         std::vector<uint8_t>, std::vector<char>, std::string,
                         std::basic_string<uint8_t, std::char_traits<uint8_t>>>
    MyTypes;
TYPED_TEST_CASE(TypedByteContainerViewTest, MyTypes);

TYPED_TEST(TypedByteContainerViewTest, DataMethod) {
  TypeParam container(kData1, kData1 + kSize1);
  ByteContainerView view(container);

  EXPECT_EQ(static_cast<const void *>(view.data()),
            static_cast<const void *>(container.data()));
}

TYPED_TEST(TypedByteContainerViewTest, SizeMethod) {
  TypeParam container(kData1, kData1 + kSize1);
  ByteContainerView view(container);

  EXPECT_EQ(view.size(), container.size());
}

// The following tests verify the various methods defined by the
// ByteContainerView object. These tests are not typed tests because the methods
// being tested behave the same irrespective of how the ByteContainerView object
// was constructed.

TEST(ByteContainerViewTest, SubscriptOperator) {
  ByteContainerView view(kData1);

  for (int i = 0; i < view.size(); i++) {
    EXPECT_EQ(static_cast<const void *>(&view[i]),
              static_cast<const void *>(&kData1[i]));
  }
}

TEST(ByteContainerViewTest, AtMethod) {
  ByteContainerView view(kData1);

  for (int i = 0; i < view.size(); i++) {
    EXPECT_EQ(static_cast<const void *>(&view.at(i)),
              static_cast<const void *>(&kData1[i]));
  }
}

TEST(ByteContainerViewTest, Iterator) {
  ByteContainerView view(kData1);
  auto it1 = view.begin();
  const char *it2 = kData1;

  while (it1 != view.end()) {
    EXPECT_EQ(static_cast<const void *>(&(*it1)),
              static_cast<const void *>(&(*it2)));
    ++it1;
    ++it2;
  }
}

TEST(ByteContainerViewTest, ConstIterator) {
  ByteContainerView view(kData1);
  auto it1 = view.cbegin();
  const char *it2 = kData1;

  while (it1 != view.cend()) {
    EXPECT_EQ(static_cast<const void *>(&(*it1)),
              static_cast<const void *>(&(*it2)));
    ++it1;
    ++it2;
  }
}

TEST(ByteContainerViewTest, ReverseIterator) {
  ByteContainerView view(kData1);
  auto it1 = view.rbegin();
  auto it2 = std::reverse_iterator<const char *>(&kData1[kSize1]);

  while (it1 != view.rend()) {
    EXPECT_EQ(static_cast<const void *>(&(*it1)),
              static_cast<const void *>(&(*it2)));
    ++it1;
    ++it2;
  }
}

TEST(ByteContainerViewTest, ConstReverseIterator) {
  ByteContainerView view(kData1);
  auto it1 = view.crbegin();
  auto it2 = std::reverse_iterator<const char *>(&kData1[kSize1]);

  while (it1 != view.crend()) {
    EXPECT_EQ(static_cast<const void *>(&(*it1)),
              static_cast<const void *>(&(*it2)));
    ++it1;
    ++it2;
  }
}

TEST(ByteContainerViewTest, EqualityOperatorPositive) {
  ByteContainerView view1(kData1);
  ByteContainerView view2(kData1);

  EXPECT_TRUE(view1 == view2);
}

TEST(ByteContainerViewTest, EqualityOperatorNegative) {
  ByteContainerView view1(kData1);
  ByteContainerView view2(kData2);

  EXPECT_FALSE(view1 == view2);
}

TEST(ByteContainerViewTest, InequalityOperatorPositive) {
  ByteContainerView view1(kData1);
  ByteContainerView view2(kData1);

  EXPECT_FALSE(view1 != view2);
}

TEST(ByteContainerViewTest, InequalityOperatorNegative) {
  ByteContainerView view1(kData1);
  ByteContainerView view2(kData2);

  EXPECT_TRUE(view1 != view2);
}

TEST(ByteContainerViewTest, SafeEqualsPositive) {
  ByteContainerView view1(kData1);
  ByteContainerView view2(kData1);

  EXPECT_TRUE(view1.SafeEquals(view2));
}

TEST(ByteContainerViewTest, SafeEqualsNegative) {
  ByteContainerView view1(kData1);
  ByteContainerView view2(kData2);

  EXPECT_FALSE(view1.SafeEquals(view2));
}

}  // namespace
}  // namespace asylo
