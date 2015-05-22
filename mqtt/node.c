/**
 * Copyright (C) 2015 NIPE-SYSTEMS
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <stdio.h>
// #include <string.h>
#include "node-protocol.h"

/**
 * Prints a single byte as decimal and binary byte. Also the character is
 * printed.
 * @param byte The byte to print.
 */
void print_byte(char byte)
{
	printf("%3i '%c' %i%i%i%i%i%i%i%i\n", byte, byte, (byte&(1<<7))?(1):(0), (byte&(1<<6))?(1):(0), (byte&(1<<5))?(1):(0), (byte&(1<<4))?(1):(0), (byte&(1<<3))?(1):(0), (byte&(1<<2))?(1):(0), (byte&(1<<1))?(1):(0), (byte&(1<<0))?(1):(0));
}

/**
 * main without command line arguments.
 * @return Returns zero (success) all the time.
 */
int main(void)
{
	char buffer[32];
	unsigned int offset = 0;
	unsigned int i = 0;
	
	// initialize buffer
	for(i = 0; i < 32; i++)
	{
		buffer[i] = 0;
	}
	
	// testing offset
	offset = 10;
	
	// append data to buffer
	mqtt_string_encode(buffer, &offset, "Hello World!", 12);
	mqtt_control_packet_fixed_header(buffer, &offset, PUBLISH, 0, 0, 0);
	mqtt_control_packet_fixed_header(buffer, &offset, PUBLISH, 1, 0, 0);
	mqtt_control_packet_fixed_header(buffer, &offset, PUBLISH, 1, 2, 0);
	mqtt_control_packet_fixed_header(buffer, &offset, PUBLISH, 1, 1, 1);
	mqtt_control_packet_fixed_header(buffer, &offset, CONNECT, 1, 1, 1);
	
	// output buffer
	for(i = 0; i < 32; i++)
	{
		print_byte(buffer[i]);
	}
	
	return 0;
}