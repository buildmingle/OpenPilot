/*
 * Open-source auto-pilot software for robotics and vehicles.
 * Control with precision, build with confidence.
 *
 * Copyright (C) 2026 WeVuild, Be
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

#include "../../include/ci_electric/power.hpp"
#include "../../include/autopilot/system.hpp"
#include "../../include/car_electric/car_ignition.hpp"

namespace ci_electric {


bool CiElectric::init() {
    current_system_state = autopilot::SystemState::OFF;
    current_power_state  = PowerState::OFF;
    // TODO: initialize GPIO subsystem
    return true;
}


bool CiElectric::pin_mode(Pin& pin, PinMode mode) {
    pin.mode_ = mode;
    configure_hardware_pin(pin.id(), mode);
    return true;
}


bool CiElectric::digital_write(const Pin& pin, PowerStatus value) {
    if (pin.mode() != PinMode::OUTPUT) {
        return false;
    }

    write_hardware_pin(pin.id(), value);
    return true;
}


PowerStatus CiElectric::digital_read(const Pin& pin) const {
    if (pin.mode() != PinMode::INPUT) {
        // In real systems you might assert or throw
        throw PowerStatus::LOW;
        // return PowerStatus::LOW;
    }

    return read_hardware_pin(pin.id());
}

// HARDWARE ABSTRACTION (MOCK) FOR NOW

void CiElectric::configure_hardware_pin(int pin_id, PinMode mode) {
    // TODO: Replace with real hardware register configuration
    (void)pin_id;
    (void)mode;
}

void CiElectric::write_hardware_pin(int pin_id, PowerStatus value) const {
    // TODO: Replace with real hardware write
    (void)pin_id;
    (void)value;
}

PowerStatus CiElectric::read_hardware_pin(int pin_id) const {
    // TODO: Replace with real hardware read
    (void)pin_id;

    return PowerStatus::LOW; // default mock value
}

} // namespace ci_electric