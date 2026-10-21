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

#include "../../include/ci_electric/dashboard.hpp"
#include "../../include/ci_electric/check.hpp"
#include "../../include/ci_electric/pin.hpp"

bool Dashboard::initialize() {
    // Initialize dashboard components
    // Startup simply shows animation or
    // boot.
    status_ = DashboardStatus::STARTUP;
    return true;
}

// The initial update; after initialize.
bool Dashboard::update() {
    status_ = DashboardStatus::OK;
    return true;
}