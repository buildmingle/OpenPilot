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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include "check.hpp"
#include "power.hpp"

enum class FuelType {
    GASOLINE,
    DIESEL,
    ELECTRIC,
    HYBRID
};

enum class FuelLevel {
    EMPTY,
    LOW,
    HALF,
    FULL,
    CALIBRATING
};

enum class FuelAlertLevel {
    INFO,
    WARNING,
    CRITICAL
};

enum class FuelAlertType {
    LOW_FUEL,
    FUEL_LEAK,
    FUEL_SYSTEM_FAILURE
};

enum class FuelEvent {
    FUEL_PUMP_FAILURE,
    FUEL_FILTER_CLOGGED,
    FUEL_INJECTOR_FAILURE
};


class Fuel {
public:
    Fuel(ci_electric::CiElectric& gpio,
         ci_electric::Pin pump_status_pin,
         ci_electric::Pin filter_status_pin,
         ci_electric::Pin injector_status_pin)
        : gpio_(gpio),
          pump_status_pin_(pump_status_pin),
          filter_status_pin_(filter_status_pin),
          injector_status_pin_(injector_status_pin) {}

    bool initialize() {
        level_ = FuelLevel::CALIBRATING;
        type_ = FuelType::GASOLINE;
        initialized_ = false;

        if (pump_status_pin_.id() == filter_status_pin_.id() ||
            pump_status_pin_.id() == injector_status_pin_.id() ||
            filter_status_pin_.id() == injector_status_pin_.id()) {
            return false;
        }

        if (!gpio_.init() ||
            !gpio_.pin_mode(pump_status_pin_, ci_electric::PinMode::INPUT) ||
            !gpio_.pin_mode(filter_status_pin_, ci_electric::PinMode::INPUT) ||
            !gpio_.pin_mode(injector_status_pin_, ci_electric::PinMode::INPUT)) {
            return false;
        }

        initialized_ = true;
        return true;
    }

    bool update() {
        // Update fuel status based on checks and sensor data
        if (type_ == FuelType::GASOLINE) {
            return check_fuel_level() && check_fuel_system();
        }
        return true;
    }

    bool fuel_alert(FuelAlertType type, FuelAlertLevel level, const std::string& message) {
        // Handle fuel alerts based on type and level
        return true;
    }

    bool trigger_event(FuelEvent event) {
        // Trigger a fuel event
        return true;
    }

    bool clear_event(FuelEvent event) {
        // Clear a fuel event
        return true;
    }

    bool check_fuel_level() {
        // Check fuel level and return true if it's above a certain threshold
        return true;
    }

    bool check_fuel_system() {
        if (!initialized_) {
            return false;
        }

        // Each status input is HIGH when its component is functioning properly.
        const bool pump_ok =
            gpio_.digital_read(pump_status_pin_) == ci_electric::PowerStatus::HIGH;
        const bool filter_ok =
            gpio_.digital_read(filter_status_pin_) == ci_electric::PowerStatus::HIGH;
        const bool injector_ok =
            gpio_.digital_read(injector_status_pin_) == ci_electric::PowerStatus::HIGH;

        if (!pump_ok) {
            trigger_event(FuelEvent::FUEL_PUMP_FAILURE);
        }
        if (!filter_ok) {
            trigger_event(FuelEvent::FUEL_FILTER_CLOGGED);
        }
        if (!injector_ok) {
            trigger_event(FuelEvent::FUEL_INJECTOR_FAILURE);
        }

        return pump_ok && filter_ok && injector_ok;
    }

private:
    ci_electric::CiElectric& gpio_;
    ci_electric::Pin pump_status_pin_;
    ci_electric::Pin filter_status_pin_;
    ci_electric::Pin injector_status_pin_;
    FuelLevel level_;
    FuelType type_;
    bool initialized_ = false;
};
