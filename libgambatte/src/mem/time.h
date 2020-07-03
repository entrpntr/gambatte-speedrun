//
//   Copyright (C) 2007 by sinamas <sinamas at users.sourceforge.net>
//
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License version 2 as
//   published by the Free Software Foundation.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License version 2 for more details.
//
//   You should have received a copy of the GNU General Public License
//   version 2 along with this program; if not, write to the
//   Free Software Foundation, Inc.,
//   51 Franklin St, Fifth Floor, Boston, MA  02110-1301, USA.
//

#ifndef TIME_H
#define TIME_H

#include <ctime>

#ifdef _MSC_VER
#include "../../msvc/src/time/gettimeofday.h"
#else
#include <sys/time.h>
#endif

namespace gambatte {

struct SaveState;

class Time {
public:
	static timeval now() {
		timeval t;
		gettimeofday(&t, 0);
		return t;
	}

	Time();
	void saveState(SaveState &state, unsigned long cycleCounter);
	void loadState(SaveState const &state);

	std::time_t get(unsigned long cycleCounter);
	void set(std::time_t seconds, unsigned long cycleCounter);
	void reset(std::time_t seconds, unsigned long cycleCounter);
	void resetCc(unsigned long oldCc, unsigned long newCc);
	void speedChange(unsigned long cycleCounter);

	timeval baseTime(unsigned long cycleCounter);
	void setBaseTime(timeval baseTime, unsigned long cycleCounter);
	void setTimeMode(bool useCycles, unsigned long cycleCounter);

	unsigned timeNow(unsigned long cycleCounter) const;

private:
	std::time_t seconds_;
	timeval lastTime_;
	unsigned long lastCycles_;
	bool useCycles_;
	bool ds_;

	void update(unsigned long cycleCounter);
	void cyclesFromTime(unsigned long cycleCounter);
	void timeFromCycles(unsigned long cycleCounter);
};

}

#endif
