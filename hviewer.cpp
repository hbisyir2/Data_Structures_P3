// implement your main entry point and any supporting code for the hviewer applicaiton here

#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <chrono>
#include <ctime>

int main(int argc, char *argv[])
{
	// Variable declarations
	char* filename;
	LinkedList<std::string> dates, names, locs;
	LinkedList<int> placeHolder;
	std::size_t i = 0, j = 0, displayCount = 0, found1, found2;
	std::string readDate, readName, readLoc;
	std::string userIn1, userIn2Str; 
	int userIn2;
	char todayPtr[5]; 
	char yesPtr[5];
	char monPtr[5];
	char yearPtr[5];
	std::string thisWeek[7];
	std::string today = "20161103";
	std::string yesterday = "20161102";
	std::string thisMonth = "201611";
	std::string year;
	auto now = std::chrono::system_clock::now();

	//gather time information
	// Loop too gather all the days of this week
	for (i = 0; i < 7; i++) {
		auto as_time_t_week = std::chrono::system_clock::to_time_t(now - std::chrono::hours(i * 24));
		auto as_tm_week = std::localtime(&as_time_t_week);
		sprintf(todayPtr, "%d", as_tm_week->tm_mday);
		sprintf(monPtr, "%d", as_tm_week->tm_mon + 1);
		sprintf(yearPtr, "%d", as_tm_week->tm_year + 1900);

		year = yearPtr;
		thisMonth = monPtr;

		thisWeek[i] = todayPtr;
		thisWeek[i] = (thisWeek[i].length() == 1) ? "0" + thisWeek[i] : thisWeek[i];
		thisWeek[i] = year + thisMonth + thisWeek[i];

	}

	// Gather data from yesterday
	auto as_time_yes = std::chrono::system_clock::to_time_t(now - std::chrono::hours(24));
	auto as_tm_yes = std::localtime(&as_time_yes);
	sprintf(yesPtr, "%d", as_tm_yes->tm_mday);
	sprintf(yearPtr, "%d", as_tm_yes->tm_year + 1900);
	sprintf(monPtr, "%d", as_tm_yes->tm_mon + 1);
	thisMonth = monPtr;
	year = yearPtr;
	yesterday = yesPtr;
	yesterday = (yesterday.length() == 1) ? "0" + yesterday : yesterday;
	yesterday = year + thisMonth + yesterday;

	// Gather data for today and this month
	auto as_time = std::chrono::system_clock::to_time_t(now);
	auto as_tm = std::localtime(&as_time);
	sprintf(todayPtr, "%d", as_tm->tm_mday);
	today = todayPtr;
	sprintf(monPtr, "%d", as_tm->tm_mon + 1);
	thisMonth = monPtr;
	sprintf(yearPtr, "%d", as_tm->tm_year + 1900);
	year = yearPtr;
	
	//get time strings in the right format
	today = (today.length() == 1) ? "0" + today : today;
	today = year + thisMonth + today;
	thisMonth = year + thisMonth;

	// Gather filename
	if (argc > 1) filename = argv[1];
	else filename = "history.csv";

	// Open file
	std::ifstream fileopen(filename);

	// Read information and store into linked lists
	while (std::getline(fileopen, readDate, ',')) {
		getline(fileopen, readName, ',');
		getline(fileopen, readLoc);
		// Stores data in reverse chronological order
		for (i = 0; i <= dates.getLength(); i++) {
			if (i == dates.getLength()) {
				dates.insert(i, readDate);
				names.insert(i, readName);
				locs.insert(i, readLoc);
				break;
			}
			else if (readDate > dates.getEntry(i)) {
				dates.insert(i, readDate);
				names.insert(i, readName);
				locs.insert(i, readLoc);
				break;
			}
		}
	}

	// Display welcome message
	std::cout << "Browser history program\nPlease insert command: ";

	// Main processing loop
	while (std::cin >> userIn1) {
		j = 0;
		i = 0;
		displayCount = 0;
		if (userIn1 == "s") {
			placeHolder.clear();
			std::cin >> userIn2;
			if (userIn2 == 0) {
				for (i = 0; i < dates.getLength(); i++) {
					std::cout << names.getEntry(i) << ", " << locs.getEntry(i) << std::endl;
					placeHolder.insert(displayCount, i);
					displayCount++;
				}
				if (displayCount == 0) {
					std::cout << "No entries" << std::endl;
				}
			}
			else if (userIn2 == 1) {
				for (i = 0; i < dates.getLength(); i++) {
					if (dates.getEntry(i).substr(0, 8) == today) {
						std::cout << names.getEntry(i) << ", " << locs.getEntry(i) << std::endl;
						placeHolder.insert(displayCount, i);
						displayCount++;
					}
				}
				if (displayCount == 0) {
					std::cout << "No entries" << std::endl;
				}
			}
			else if (userIn2 == 2) {
				for (i = 0; i < dates.getLength(); i++) {
					if (dates.getEntry(i).substr(0, 8) == yesterday) {
						std::cout << names.getEntry(i) << ", " << locs.getEntry(i) << std::endl;
						placeHolder.insert(displayCount, i);
						displayCount++;
					}
				}
				if (displayCount == 0) {
					std::cout << "No entries" << std::endl;
				}
			}
			else if (userIn2 == 3) {
				for (i = 0; i < dates.getLength(); i++) {
					for (j = 0; j < 6; j++) {
						if (thisWeek[j] == dates.getEntry(i).substr(0, 8)) {
							std::cout << names.getEntry(i) << ", " << locs.getEntry(i) << std::endl;
							placeHolder.insert(displayCount, i);
							displayCount++;
						}
					}
				}
				if (displayCount == 0) {
					std::cout << "No entries" << std::endl;
				}
			}
			else if (userIn2 == 4) {
				for (i = 0; i < dates.getLength(); i++) {
					if (dates.getEntry(i).substr(0, 6) == thisMonth) {
						std::cout << names.getEntry(i) << ", " << locs.getEntry(i) << std::endl;
						placeHolder.insert(displayCount, i);
						displayCount++;
					}
				}
				if (displayCount == 0) {
					std::cout << "No entries" << std::endl;
				}
			}
		}
		else if (userIn1 == "f") {
			placeHolder.clear();
			found1 = 0;
			found2 = 0;
			std::cin >> userIn2Str;
			for (i = 0; i < dates.getLength(); i++) {
				found1 = names.getEntry(i).find(userIn2Str);
				found2 = locs.getEntry(i).find(userIn2Str);
				if (found1 != std::string::npos) {
					std::cout << names.getEntry(i) << ", " << locs.getEntry(i) << std::endl;
					placeHolder.insert(displayCount, i);
					displayCount++;
				}
				else if (found2 != std::string::npos) {
					std::cout << names.getEntry(i) << ", " << locs.getEntry(i) << std::endl;
					placeHolder.insert(displayCount, i);
					displayCount++;
				}
			}
			if (displayCount == 0) std::cout << "No entries" << std::endl;
		}
		else if (userIn1 == "r") {
			j = 0;
			if (placeHolder.isEmpty()) std::cout << "Can not remove at this time.\nPlease display more history" << std::endl;
			std::cin >> userIn2;
			if (userIn2 > placeHolder.getLength() + 1 || userIn2 < 0) {
				std::cout << "Invalid entry" << std::endl;
			}
			else if (userIn2 == 0) {
				for (i = 0; i < placeHolder.getLength(); i++) {
					dates.remove(placeHolder.getEntry(i)-j);
					names.remove(placeHolder.getEntry(i)-j);
					locs.remove(placeHolder.getEntry(i)-j);
					j++;
				}
				std::cout << "Removed all displayed entries" << std::endl;
			}
			else {
				dates.remove(placeHolder.getEntry(userIn2-1));
				names.remove(placeHolder.getEntry(userIn2-1));
				locs.remove(placeHolder.getEntry(userIn2-1));
				std::cout << "Removed desired entry" << std::endl;
			}
			placeHolder.clear();
		}
		else if (userIn1 == "w") {
			std::ofstream fileWrite;
			fileWrite.open(filename, std::ofstream::out | std::ofstream::trunc);
			for (i = 0; i < dates.getLength(); i++) {
				fileWrite << dates.getEntry(i) << "," << names.getEntry(i) << "," << locs.getEntry(i) << "\n";
			}
			fileWrite.close();
			std::cout << "Updated histroy file" << std::endl;
		}
		else {
			std::cout << "Unknown Command" << std::endl;
		}
		std::cout << "Please enter command: ";
	} // end while
  return 0;
}