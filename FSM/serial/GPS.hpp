/*
 * GPS.cpp
 *
 *  Created on: Dec 9, 2012
 *      Author: unwin

   http://aprs.gids.nl/nmea/
   RASPBERRY PI - PREQUISITES
   	   remove references to /dev/ttyAMA0  in vi /etc/inittab /boot/cmdline.txt
   	   stty 9600 sane -echo -echok -icrnl -ixon -icanon -opost -onlcr time 3 min 0 < /dev/ttyAMA0
 */

#include <iostream>
#include <ostream>
#include <string>
#include <assert.h>

#include <boost/thread/thread.hpp>
#include <boost/asio.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>
#include <boost/circular_buffer.hpp>

#include "../SimpleThread.h"
#include "../log.h"
#include "serial.hpp"

using namespace boost::system;
using namespace boost::asio;
using namespace std;

typedef std::vector< std::string > split_vector_type;



class GPS : public SimpleThread {
	private:
		SimpleSerial *port;
		boost::circular_buffer <double> *GPGLL_utc_time;
		boost::circular_buffer <double> *GPGLL_latitude;
		boost::circular_buffer <double> *GPGLL_longitude;
		boost::circular_buffer <double> *GPGGA_latitude;
		boost::circular_buffer <double> *GPGGA_longitude;
		boost::circular_buffer <string> *GPGGA_fix_quality;
		boost::circular_buffer <double> *GPGGA_meters_above_ground;
		boost::circular_buffer <double> *GPRMC_latitude;
		boost::circular_buffer <double> *GPRMC_longitude;
		boost::circular_buffer <string> *GPRMC_validity;
		boost::circular_buffer <double> *GPRMC_ground_speed;
		boost::circular_buffer <double> *GPRMC_true_course;
		boost::circular_buffer <double> *GPGSA_HDOP;
		boost::circular_buffer <double> *GPGSA_VDOP;
		boost::circular_buffer <double> *GPGSA_PDOP;
		boost::circular_buffer <string> *GPGSA_Fix_Quality;
		boost::circular_buffer <int> *GPGSV_SV_in_view;
		boost::circular_buffer <double> *GPVTG_degrees_true;
		boost::circular_buffer <double> *GPVTG_degrees_magnetic;
		boost::circular_buffer <double> *GPVTG_speed_knots;
		boost::circular_buffer <double> *GPVTG_speed_kph;

	public:
		GPS(std::string device_port, unsigned int baud_rate) : SimpleThread()  {
			port = new SimpleSerial(device_port, baud_rate);

			init_vars();

			SetRunInterval(1000);
			StartWorker();
		};
		/**
		 * Blocks until a line is received from the serial device. A line is denoted by a final '\n' character
		 * Eventual '\n' or '\r\n' characters at the end of the string are removed.
		 * \return a string containing the received line
		 * \throws boost::system::system_error on failure
		 */


		GPS() : SimpleThread() {
			port = 0;
			init_vars();
		};

		void init_vars() {
			GPGLL_utc_time = new boost::circular_buffer<double>(10);
			GPGLL_latitude = new boost::circular_buffer<double>(10);
			GPGLL_longitude = new boost::circular_buffer<double>(10);
			GPGGA_latitude = new boost::circular_buffer<double>(10);
			GPGGA_longitude = new boost::circular_buffer<double>(10);
			GPGGA_fix_quality = new boost::circular_buffer<string>(10);
			GPGGA_meters_above_ground = new boost::circular_buffer<double>(10);
			GPRMC_latitude = new boost::circular_buffer<double>(10);
			GPRMC_longitude = new boost::circular_buffer<double>(10);
			GPRMC_validity = new boost::circular_buffer<string>(10);
			GPRMC_ground_speed = new boost::circular_buffer<double>(10);
			GPRMC_true_course = new boost::circular_buffer<double>(10);
			GPGSA_HDOP = new boost::circular_buffer<double>(10);
			GPGSA_VDOP = new boost::circular_buffer<double>(10);
			GPGSA_PDOP = new boost::circular_buffer<double>(10);
			GPGSA_Fix_Quality = new boost::circular_buffer<string>(10);
			GPGSV_SV_in_view = new boost::circular_buffer<int>(10);
			GPVTG_degrees_true = new boost::circular_buffer<double>(10);
			GPVTG_degrees_magnetic = new boost::circular_buffer<double>(10);
			GPVTG_speed_knots = new boost::circular_buffer<double>(10);
			GPVTG_speed_kph = new boost::circular_buffer<double>(10);

		}

		~GPS() {

		};



		void report_double(boost::circular_buffer <double> *cld, string label ) {
			std::ostringstream line_buff;
			if (cld->size() >= 1) {
				line_buff << label << ": " << std::setprecision (numeric_limits<double>::digits10 + 1) << cld->at(cld->size() - 1);

				for (int x = cld->size() - 2; x >= 0;x--) {
					line_buff << " <- " << std::setprecision (numeric_limits<double>::digits10 + 1)  << cld->at(x);
				}
				LOG << line_buff.str();
			} else {
				LOG << label << ": no data.";
			}
		}
		void report_string(boost::circular_buffer <string> *cld, string label ) {
			std::ostringstream line_buff;
			if (cld->size() >= 1) {
				line_buff << label << ": " << cld->at(cld->size() - 1);

				for (int x = cld->size() - 2; x >= 0;x--) {
					line_buff << " <- " << cld->at(x);
				}
				LOG << line_buff.str();
			} else {
				LOG << label << ": no data.";
			}
		}
		void report_int(boost::circular_buffer <int> *cld, string label ) {
			std::ostringstream line_buff;
			if (cld->size() >= 1) {
				line_buff << label << ": " << std::setprecision (numeric_limits<int>::digits10 + 1) << cld->at(cld->size() - 1);

				for (int x = cld->size() - 2; x >= 0;x--) {
					line_buff << " <- " << std::setprecision (numeric_limits<int>::digits10 + 1) << cld->at(x);
				}
				LOG << line_buff.str();
			} else {
				LOG << label << ": no data.";
			}
		}

		void report() {
			LOG << "==================== REPORTING ====================";
			report_double(GPGLL_utc_time, "GPGLL_utc_time");
			report_double(GPGLL_latitude, "GPGLL_latitude");
			report_double(GPGLL_longitude, "GPGLL_longitude");
			report_string(GPGSA_Fix_Quality, "GPGSA_Fix_Quality");
			report_string(GPGGA_fix_quality, "GPGGA_fix_quality");
			report_string(GPRMC_validity, "GPRMC_validity");
			report_double(GPGGA_latitude, "GPGGA_latitude");
			report_double(GPGGA_longitude, "GPGGA_longitude");
			report_double(GPRMC_latitude, "GPRMC_latitude");
			report_double(GPRMC_longitude, "GPRMC_longitude");
			report_double(GPRMC_ground_speed, "GPRMC_ground_speed");
			report_double(GPRMC_true_course, "GPRMC_true_course");
			report_int(GPGSV_SV_in_view, "GPGSV_SV_in_view");
			report_double(GPGGA_meters_above_ground, "GPGGA_meters_above_ground");


			report_double(GPVTG_degrees_true, "Heading Degrees From True North");
			report_double(GPVTG_degrees_magnetic, "Heading Degrees From Magnetic North");
			report_double(GPVTG_speed_knots, "Speed knots");
			report_double(GPVTG_speed_kph, "Speed KPH");

			/*
			GPRMC_validity
			GPGSA_HDOP
			GPGSA_VDOP
			GPGSA_PDOP
			GPGSA_Fix_Quality
			GPGSV_SV_in_view
			*/

			LOG << "===================================================";
		}

		const char *get_commanmd(std::string line) {
			//LOG << "get_commanmd converting line = [" << line << "] into a char *";
			std::string command = line.substr (1, 5);
			const char *result = command.c_str();
			return(result);
		}

		std::string get_commanmd_payload(std::string line) {
			// There has to be a better way to do this...
			std::string payload = line.substr(7, line.length() -7);
			return(payload);
		}

		void process_line(std::string line) {
			const char *command = get_commanmd(line);
			string cmd = string(command);
			std::string payload = get_commanmd_payload(line);
			if ((command[0] == 'G') || (command[1] == 'P')) {
				switch (command[2]) {
					case 'B' :  if (cmd == "GPBOD")
									// $GPBOD - Bearing, origin to destination
									parse_GPBOD(payload);
								else if (cmd == "GPBWC")
									// $GPBWC - Bearing and distance to waypoint, great circle
									parse_GPBWC(payload);
								else
									CRITICAL << "Unrecognized command " << command;
								break;
					case 'G' :	switch (command[3]) {
									case 'G' : if ('A' == command[4])
													// $GPGGA - Global Positioning System Fix Data
													parse_GPGGA(payload);
											   break;
									case 'L' : if ('L' == command[4])
													// $GPGLL - Geographic position, latitude / longitude
													parse_GPGLL(payload);
											   break;
									case 'S' : if ('A' == command[4]) {
													// $GPGSA - GPS DOP and active satellites
													parse_GPGSA(payload);
											   } else if  ('V' == command[4]) {
												   	// $GPGSV - GPS Satellites in view
												   	parse_GPGSV(payload);
											   } else {
												    CRITICAL << "Unrecognized command " << command;
											   }
											   break;
									default:   CRITICAL << "Unrecognized command " << command;
											   break;
								}
								break;
					case 'H' :  if (('D' == command[3]) && ('T' == command[4]))
									// *  $GPHDT - Heading, True
									parse_GPGSV(payload);
								else {
									CRITICAL << "Unrecognized command " << command;
								}
								break;
					case 'R' :	switch (command[3]) {
									case '0':  if ('0' == command[4])
													// $GPR00 - List of waypoints in currently active route
													parse_GPR00(payload);
													break;
									case 'M':  if ('A' == command[4]) {
													// $GPRMA - Recommended minimum specific Loran-C data
													parse_GPGSA(payload);
											   } else if  ('B' == command[4]) {
													// $GPRMB - Recommended minimum navigation info
													parse_GPGSV(payload);
											   } else if  ('C' == command[4]) {
													// $GPRMC - Recommended minimum specific GPS/Transit data
													parse_GPRMC(payload);
											   } else {
												   CRITICAL << "Unrecognized command " << command;
											   }
											   break;
									case 'T':  if ('E' == command[4]) {
													// $GPRTE - Routes
													parse_GPRTE(payload);
											   } else {
												   CRITICAL << "Unrecognized command " << command;
											   }
											   break;
								}
								break;
					case 'T' :  if (cmd == "GPTRF")
									// $GPTRF - Transit Fix Data
									parse_GPTRF(payload);
								else
									CRITICAL << "Unrecognized command " << command;
								break;
					case 'S' :  if (cmd == "GPSTN")
									// $GPSTN - Multiple Data ID
									parse_GPSTN(payload);
								else
									CRITICAL << "Unrecognized command " << command;
								break;
					case 'V' :  if (cmd == "GPVBW")
									// *$GPVBW - Dual Ground / Water Speed
									parse_GPVBW(payload);
								else if (cmd == "GPVTG")
									// $GPVTG - Track made good and ground speed
									parse_GPVTG(payload);
								else
									CRITICAL << "V - Unrecognized command " << command;
								break;
					case 'W' :  if (cmd == "GPWPL")
									// $GPWPL - Waypoint location
									parse_GPWPL(payload);
								else
									CRITICAL << "Unrecognized command " << command;
								break;
					case 'X' :  if (cmd == "GPXTE")
									// $GPXTE - Cross-track error, Measured
									parse_GPXTE(payload);
								else
									CRITICAL << "Unrecognized command " << command;
								break;
					case 'Z' :  if (cmd == "GPZDA")
									// $GPZDA - Date & Time
									parse_GPZDA(payload);
								else
									CRITICAL << "Unrecognized command " << command;
								break;
				}
			} else {
				CRITICAL << "Unrecognized command " << command;
			}
		}

		void parse_GPBOD(std::string payload) {
			CRITICAL << "NOT IMPLEMENTED parse_GPBOD - " << payload;
		}

		void parse_GPBWC(std::string payload) {

			CRITICAL << "NOT IMPLEMENTED parse_GPBWC - " << payload;
		}

		void parse_GPZDA(std::string payload) {
			CRITICAL << "NOT IMPLEMENTED parse_GPZDA - " << payload;
		}

		void parse_GPXTE(std::string payload) {
			CRITICAL << "NOT IMPLEMENTED parse_GPXTE - " << payload;
		}

		void parse_GPWPL(std::string payload) {
			CRITICAL << "NOT IMPLEMENTED parse_GPWPL - " << payload;
		}

		void parse_GPVTG(std::string payload) {
			// Track Made Good and Ground Speed.
			//LOG << "parse_GPVTG - " << payload;
			split_vector_type string_tokens;
			boost::split( string_tokens, payload, boost::is_any_of(",") );
			if (string_tokens[0].length() > 0) {
				double degrees_true = boost::lexical_cast<double>(string_tokens[0]);
				assert(string_tokens[1] == "T");
				GPVTG_degrees_true->push_back(degrees_true);
				//LOG << "Heading Degrees from True North: " << degrees_true;
			} else
				GPVTG_degrees_true->push_back(0);
			if (string_tokens[2].length() > 0) {
				double degrees_magnetic = boost::lexical_cast<double>(string_tokens[2]);
				assert(string_tokens[3] == "M");
				GPVTG_degrees_magnetic->push_back(degrees_magnetic);
				//LOG << "Heading Degrees from Magnetic North: " << degrees_magnetic;
			} else
				GPVTG_degrees_magnetic->push_back(0);
			if (string_tokens[4].length() > 0) {
				double speed_knots = boost::lexical_cast<double>(string_tokens[4]);
				assert(string_tokens[5] == "N");
				GPVTG_speed_knots->push_back(speed_knots);
				//LOG << "Speed, Knots: " << speed_knots;
			} else
				GPVTG_speed_knots->push_back(0);
			if (string_tokens[6].length() > 0) {
				double speed_kph = boost::lexical_cast<double>(string_tokens[6]);
				assert(string_tokens[7] == "K");
				GPVTG_speed_kph->push_back(speed_kph);
				//LOG << "Speed, KPH: " << speed_kph;
			} else
				GPVTG_speed_kph->push_back(0);

		}

		void parse_GPVBW(std::string payload) {
			CRITICAL << "NOT IMPLEMENTED parse_GPVBW - " << payload;
		}

		void parse_GPSTN(std::string payload) {
			CRITICAL << "NOT IMPLEMENTED parse_GPSTN - " << payload;
		}

		void parse_GPTRF(std::string payload) {
			CRITICAL << "NOT IMPLEMENTED parse_GPRTE - " << payload;
		}

		void parse_GPGLL(std::string payload) {
			split_vector_type string_tokens;
			boost::split( string_tokens, payload, boost::is_any_of(",") );
			//LOG << "parse_GPGLL - " << payload;

			double lat = boost::lexical_cast<double>(string_tokens[0]);
			if (string_tokens[1] == "S")
				lat *= -1;
			GPGLL_latitude->push_back(lat);
			double lon = boost::lexical_cast<double>(string_tokens[2]);
			if (string_tokens[3] == "W")
				lon *= -1;
			GPGLL_longitude->push_back(lon);
			double utc_time = boost::lexical_cast<double>(string_tokens[4]);
			GPGLL_utc_time->push_back(utc_time);
		}

		void parse_GPR00(std::string payload) {
			CRITICAL << "NOT IMPLEMENTED parse_GPR00 - " << payload;
		}

		void parse_GPRTE(std::string payload) {
			CRITICAL << "NOT IMPLEMENTED parse_GPRTE - " << payload;
		}

		void parse_GPGGA(std::string payload) {
			//// LOG << "parse_GPGGA - " << payload;
			split_vector_type string_tokens;
			boost::split( string_tokens, payload, boost::is_any_of(",") );

			//// LOG << "-" << "UTC of position = " << string_tokens[0];

			double lat = boost::lexical_cast<double>(string_tokens[1]);
			if (string_tokens[2] == "S")
				lat *= -1;
			GPGGA_latitude->push_back(lat);
			//LOG << "+" << "Latitude: " << std::setprecision (numeric_limits<double>::digits10 + 1) << lat;

			double lon = boost::lexical_cast<double>(string_tokens[3]);
			if (string_tokens[4] == "W")
				lon *= -1;
			GPGGA_longitude->push_back(lon);
			//LOG << "+" << "Longitude: " << std::setprecision (numeric_limits<double>::digits10 + 1) << lon;

			std::string fix_quality[4] = {"Invalid", "GPS fix", "DGPS fix" };
			string sat_fix_quality = fix_quality[boost::lexical_cast<int>(string_tokens[5])];
			GPGGA_fix_quality->push_back(sat_fix_quality);
			//LOG << "+" << "FIX QUALITY: " << sat_fix_quality << ".";

			double meters_above_ground = boost::lexical_cast<double>(string_tokens[8]);
			GPGGA_meters_above_ground->push_back(meters_above_ground);
			//LOG << "+" << "Meters above ground: " << meters_above_ground;
			//// LOG << "-" << "time since last DGPS update is " << string_tokens[12];
			//// LOG << "-" << "number of satellites in view: " << string_tokens[6];
		}

		void parse_GPGSA(std::string payload) {
			//LOG << "parse_GPGSA - " << payload;
			split_vector_type string_tokens;
			boost::split( string_tokens, payload, boost::is_any_of(",*") );

			std::string fix_mode[4] = {"", "Fix not available", "2D", "3D" };
			string fix_quality = fix_mode[boost::lexical_cast<int>(string_tokens[1])];
			GPGSA_Fix_Quality->push_back(fix_quality);
			//LOG << "+FIX QUALITY: " << fix_quality << ".";
			//for (int x = 2;x < 14;x++)
			//	if (!string_tokens[x].empty())
			//		LOG << "-USING SAT: " << string_tokens[x];

			// http://en.wikipedia.org/wiki/Dilution_of_precision_(GPS)
			double hdop = boost::lexical_cast<double>(string_tokens[15]);
			GPGSA_HDOP->push_back(hdop);
			//LOG << "+Horizontal Dilution of Precision: " << hdop;

			double vdop = boost::lexical_cast<double>(string_tokens[16]);
			GPGSA_VDOP->push_back(vdop);
			//LOG << "+Vertical Dilution of Precision: " << vdop;

			double pdop = boost::lexical_cast<double>(string_tokens[14]);
			GPGSA_PDOP->push_back(pdop);
			//LOG << "+Positional (3d) Dilution of Precision: " << pdop;
		}

		void parse_GPRMC(std::string payload) {
			//// LOG << "parse_GPRMC - " << payload;

			split_vector_type string_tokens;
			boost::split( string_tokens, payload, boost::is_any_of(",*") );

			// HHMMSS - Time of fix 22:54:46 UTC
			//// LOG << "-" << "UTC Time Stamp: " << string_tokens[0];

			if (string_tokens[1] == "A")
				GPRMC_validity->push_back("Valid");
			else
				GPRMC_validity->push_back("Invalid");

			//LOG << "+" << "validity: " << GPRMC_validity->at(0);

			double lat = boost::lexical_cast<double>(string_tokens[2]);
			if (string_tokens[3] == "S")
				lat *= -1;
			GPRMC_latitude->push_back(lat);
			//LOG << "+" << "Latitude: " << std::setprecision (numeric_limits<double>::digits10 + 1) << lat;

			double lon = boost::lexical_cast<double>(string_tokens[4]);
			if (string_tokens[5] == "W")
				lon *= -1;
			GPRMC_longitude->push_back(lon);
			//LOG << "+" << "Longitude: " << std::setprecision (numeric_limits<double>::digits10 + 1) << lon;

			double ground_speed = boost::lexical_cast<double>(string_tokens[6]);
			GPRMC_ground_speed->push_back(ground_speed);
			//LOG << "+" << "Ground Speed: " << ground_speed;

			if ("" != string_tokens[7]) {
				double true_course = boost::lexical_cast<double>(string_tokens[7]);
				GPRMC_true_course->push_back(true_course);
				//// LOG << "-" << "True course: " << true_course;
			}

			// DD MM YY
			//// LOG << "-" << "Date of fix: " << string_tokens[8];



			// Magnetic declination is the angle between compass north (the direction the north end of
			// a compass needle points) and true north. The declination is positive when the magnetic
			// north is east of true north. The term magnetic variation is a synonym, and is more often
			// used in navigation.
			//LOG << "-" << "Magnetic variation: " << string_tokens[9] << string_tokens[10];
		}

		void parse_GPGSV(std::string payload) {
			//// LOG << "parse_GPGSV - " << payload;
			split_vector_type string_tokens;
			boost::split( string_tokens, payload, boost::is_any_of(",*") );

			int id = 0;
			//// LOG << "-" << "Total number of messages of this type in this cycle: " << string_tokens[id++];
			//// LOG << "-" << "Message number: " << string_tokens[id++];

			// SVNs are "space vehicle numbers", the serial numbers assigned to each GPS satellite, and
			// PRNs are the "pseudo-random noise" sequences, or Gold codes, that each satellite transmits
			// to differentiate itself from other satellites in the active constellation.
			// SV = Space Vehicle

			int sv_in_view = boost::lexical_cast<int>(string_tokens[2]);
			GPGSV_SV_in_view->push_back(sv_in_view);
			//LOG << "+" << "Total number of SVs in view: " << sv_in_view;

			//// LOG << "-" << "SV PRN number: " << string_tokens[id++];
			//// LOG << "-" << "Elevation in degrees, 90 maximum: " << string_tokens[id++];
			//// LOG << "-" << "Azimuth, degrees from true north, 000 to 359: " << string_tokens[id++];
			//// LOG << "-" << "SNR, 00-99 dB (null when not tracking): " << string_tokens[id++];
		}


		void DoWork() {
			 //LOG << "GPS::DoWork ";
			 string line = port->readLine();
			 process_line(line);
		}
};

