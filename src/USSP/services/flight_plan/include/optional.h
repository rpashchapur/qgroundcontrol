// AirMap Platform SDK
// Copyright © 2018 AirMap, Inc. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//   http://www.apache.org/licenses/LICENSE-2.0
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an AS IS BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#ifndef USSP_OPTIONAL_H_
#define USSP_OPTIONAL_H_

#include <include/visibility.h>

#include <iostream>
#include <type_traits>

namespace ussp {

/// Optional manages an optional contained value of type T.
template <typename T>
class USSP_EXPORT Optional {
 public:
  /// Optional initializes a new instance with no contained value.
  Optional() : has_value{false} {
  }

  /// Optional initializes a new instance with 'other'.
  Optional(const Optional& other) : has_value{other.has_value} {
    if (has_value)
      new (&storage.value) T(other.storage.value);
  }

  /// Optional initializes a new instance with 'other'.
  Optional(Optional<T>&& other) : has_value{other.has_value} {
    if (has_value)
      new (&storage.value) T(other.storage.value);
  }

  /// Optional initializes a new instance with 'value'.
  Optional(const T& value) : has_value{true} {
    new (&storage.value) T(value);
  }

  /// Optional initializes a new instance with 'value'.
  Optional(T&& value) : has_value{true} {
    new (&storage.value) T(value);
  }

  /// ~Optional cleans up the instance and calls the destructor
  /// of the contained value if one is set.
  ~Optional() {
    reset();
  }

  /// @cond
  Optional& operator=(const Optional& rhs) {
    if (rhs.has_value)
      set(rhs.storage.value);
    else
      reset();

    return *this;
  }

  Optional& operator=(const T& rhs) {
    set(rhs);
    return *this;
  }

  Optional& operator=(Optional&& rhs) {
    if (rhs.has_value)
      set(rhs.storage.value);
    else
      reset();

    return *this;
  }

  bool operator==(const Optional& rhs) const {
    if (has_value != rhs.has_value)
      return false;

    return has_value && (storage.value == rhs.storage.value);
  }
  /// @endcond

  /// operator bool returns true if this instance contains a value.
  explicit operator bool() const {
    return has_value;
  }

  /// get returns an immutable reference to the contained value.
  /// If no value is contained in this instance, the result of the call is undefined.
  const T& get() const {
    return storage.value;
  }

  /// get returns an immutable reference to the contained value.
  /// If no value is contained in this instance, the result of the call is undefined.
  T& get() {
    return storage.value;
  }

  /// set adjusts the contained value to 'value'.
  void set(const T& value) {
    reset();

    has_value = true;
    new (&storage.value) T(value);
  }

  /// reset frees up any contained value if one is set.
  /// After this call has completed, no value is contained in this Optional instance.
  void reset() {
    if (has_value)
      (&storage.value)->~T();
    has_value = false;
  }

 private:
  bool has_value;
  union USSP_EXPORT Storage {
    Storage() {
    }
    ~Storage() {
    }
    T value;
  } storage;
};

/// operator<< inserts value into out.
template <typename T>
USSP_EXPORT inline std::ostream& operator<<(std::ostream& out, const Optional<T>& value) {
  if (value)
    out << value.get();
  else
    out << "not set";
  return out;
}

/// @cond
template <typename T>
using Required = Optional<T>;
/// @endcond

}  // namespace ussp

#endif  // USSP_OPTIONAL_H_
