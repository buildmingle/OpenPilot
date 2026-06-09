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

// Car ignition?

#pragma once

namespace car_electric {

enum class PowerState {
	OFF,
	SHORTAGE,
	ON,
	STARTING_ENGINE
};

class Ignition {
public:
	bool init();				// Initializing.
	bool off();					// No power detected.
	bool shortage();			// To little power to run.
	bool pwr_on();				// Key is twisted at position two.
	bool start_engine();		// Should only be valid when you have a key that requires
								// twisting, modern cars use a button, so this will be changed
								// depending on the model.
	PowerState state() const;

private:
	// Default state is OFF
	PowerState current_state = PowerState::OFF;
	void set_state(PowerState new_state);
};

}