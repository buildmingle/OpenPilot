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

#include "../../include/ci_electric/fuel.hpp"

Fuel::Fuel(ci_electric::CiElectric& gpio,
           ci_electric::Pin pump_status_pin,
           ci_electric::Pin filter_status_pin,
           ci_electric::Pin injector_status_pin,
           ci_electric::Pin fuel_low_pin,
           Dashboard& dashboard)
    : gpio_(gpio),
      pump_status_pin_(pump_status_pin),
      filter_status_pin_(filter_status_pin),
      injector_status_pin_(injector_status_pin),
      fuel_low_pin_(fuel_low_pin),
      dashboard_(dashboard) {}

bool Fuel::initialize() {
    level_ = FuelLevel::CALIBRATING;
    type_ = FuelType::GASOLINE;
    initialized_ = false;

    if (pump_status_pin_.id() == filter_status_pin_.id() ||
        pump_status_pin_.id() == injector_status_pin_.id() ||
        pump_status_pin_.id() == fuel_low_pin_.id() ||
        filter_status_pin_.id() == injector_status_pin_.id() ||
        filter_status_pin_.id() == fuel_low_pin_.id() ||
        injector_status_pin_.id() == fuel_low_pin_.id()) {
        return false;
    }

    if (!gpio_.init() ||
        !gpio_.pin_mode(pump_status_pin_, ci_electric::PinMode::INPUT) ||
        !gpio_.pin_mode(filter_status_pin_, ci_electric::PinMode::INPUT) ||
        !gpio_.pin_mode(injector_status_pin_, ci_electric::PinMode::INPUT) ||
        !gpio_.pin_mode(fuel_low_pin_, ci_electric::PinMode::INPUT)) {
        return false;
    }

    initialized_ = true;
    return true;
}

bool Fuel::update() {
    if (type_ != FuelType::GASOLINE) {
        return true;
    }
    return check_fuel_level() && check_fuel_system();
}

bool Fuel::fuel_alert(FuelAlertType type, FuelAlertLevel level, const std::string& message) {
    DashboardAlertType dashboard_type;
    switch (type) {
        case FuelAlertType::LOW_FUEL:
            dashboard_type = DashboardAlertType::SENSOR;
            break;
        case FuelAlertType::FUEL_LEAK:
        case FuelAlertType::FUEL_SYSTEM_FAILURE:
            dashboard_type = DashboardAlertType::SYSTEM;
            break;
        default:
            return false;
    }

    DashboardAlertLevel dashboard_level;
    switch (level) {
        case FuelAlertLevel::INFO:
            dashboard_level = DashboardAlertLevel::INFO;
            break;
        case FuelAlertLevel::WARNING:
            dashboard_level = DashboardAlertLevel::WARNING;
            break;
        case FuelAlertLevel::CRITICAL:
            dashboard_level = DashboardAlertLevel::CRITICAL;
            break;
        default:
            return false;
    }

    const bool alert_sent =
        dashboard_.dashboard_alert(dashboard_type, dashboard_level, message);
    const bool light_set = dashboard_.set_light(DashboardLights::FUEL, true);
    return alert_sent && light_set;
}

bool Fuel::trigger_event(FuelEvent event) {
    (void)event;
    return true;
}

bool Fuel::clear_event(FuelEvent event) {
    (void)event;
    return true;
}

bool Fuel::check_fuel_level() {
    if (!initialized_) {
        return false;
    }

    const bool fuel_is_low =
        gpio_.digital_read(fuel_low_pin_) == ci_electric::PowerStatus::HIGH;
    if (fuel_is_low) {
        level_ = FuelLevel::LOW;
        fuel_alert(FuelAlertType::LOW_FUEL, FuelAlertLevel::WARNING,
                   "Fuel level is low.");
        return false;
    }

    return dashboard_.clear_light(DashboardLights::FUEL);
}

bool Fuel::check_fuel_system() {
    if (!initialized_) {
        return false;
    }

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