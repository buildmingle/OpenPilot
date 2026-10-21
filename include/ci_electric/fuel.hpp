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

#include <string>

#include "check.hpp"
#include "dashboard.hpp"
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
         ci_electric::Pin injector_status_pin,
         ci_electric::Pin fuel_low_pin,
         Dashboard& dashboard);

    bool initialize();
    bool update();
    bool fuel_alert(FuelAlertType type, FuelAlertLevel level, const std::string& message);
    bool trigger_event(FuelEvent event);
    bool clear_event(FuelEvent event);
    bool check_fuel_level();
    bool check_fuel_system();

private:
    ci_electric::CiElectric& gpio_;
    ci_electric::Pin pump_status_pin_;
    ci_electric::Pin filter_status_pin_;
    ci_electric::Pin injector_status_pin_;
    ci_electric::Pin fuel_low_pin_;
    Dashboard& dashboard_;
    FuelLevel level_;
    FuelType type_;
    bool initialized_ = false;
};
