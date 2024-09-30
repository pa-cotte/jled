// Copyright (c) 2017 Jan Delgado <jdelgado[at]gmx.net>
// https://github.com/jandelgado/jled
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//
#ifndef SRC_ZEPHYR_HAL_H_
#define SRC_ZEPHYR_HAL_H_

#include <zephyr/device.h>
#include <zephyr/drivers/pwm.h>
#include <zephyr/kernel.h>

namespace jled {

class ZephyrHal {
 public:
    using PinType = struct pwm_dt_spec;

    explicit ZephyrHal(PinType pin) noexcept : pin_(pin) {
        __ASSERT(pwm_is_ready_dt(&pin), "Device %s is not ready", pin.dev->name);
    }

    void analogWrite(uint8_t val) const {
        ::pwm_set_pulse_dt(&pin_,
                           (uint32_t)((uint64_t)pin_.period * val / 255));
    }

    uint32_t millis() const { return ::k_uptime_get(); }

 private:
    PinType pin_;
};
}  // namespace jled
#endif  // SRC_ZEPHYR_HAL_H_
