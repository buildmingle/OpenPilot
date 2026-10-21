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
    bool initialize() {
        level_ = FuelLevel::CALIBRATING;
        type_ = FuelType::GASOLINE;
        return true;
    }

    bool update() {
        // Update fuel status based on checks and sensor data
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
        // Check fuel system components and return true if they are functioning properly
        // TODO: Do this before anything else.
        return true;
    }

private:
    FuelLevel level_;
    FuelType type_;
};