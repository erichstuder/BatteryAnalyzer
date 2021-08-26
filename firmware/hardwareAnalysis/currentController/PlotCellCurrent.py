"""
Battery Analyzer
Copyright (C) 2019 Erich Studer

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as published
by the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
"""

import sys

sys.path.append('../../IT_Client')
from helpers.TelegramHandler import TelegramHandler
from helpers.TelegramPlotter import TelegramPlotter

print("Starting up, may take a few seconds ...")

myFile = sys.argv[1]
telegramHandler = TelegramHandler(myFile)
plotter = TelegramPlotter('myPlot')


while True:
	telegram = telegramHandler.getLastValue('Ki')
	if telegram is not None:
		print('Ki ' + str(telegram['value']))

	current = telegramHandler.getLastValues('current', 10e6)
	pwm = telegramHandler.getLastValues('pwm', 10e6)
	plotter.plot(current)
	plotter.plot(pwm)
	plotter.update()
