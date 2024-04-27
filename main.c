/**
*  Responsible for orchestrating the program, 
*  getting user input, and calling functions from other files.
*  @file Main.c 
*  @author Pranav Kale pkale 
*/

#define SUCCESS 0
#define MAX_FLIGHTS 12
#define MATCHES2 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "flights.h"
#include "display.h"
#include "input.h"

// Function prototype
void loadFlightData(const char *filename, FlightDatabase *fdatab);

void displayFlightData(Flight *flight) {
    printf("Flight ID: %s\n", flight->flightID);
    printf("Departure Airport: %s\n", flight->departureAirport);
    // Add more fields as needed
}
/**
* Prints a message when program is given invalid arguments 
*/
static void usage()
{
    fprintf( stderr, "usage: main flight-file+\n" );
    exit(EXIT_FAILURE);
}

/**
    Starting point of program
    @param argv the number of arguments
    @param argc the arguments
*/
int main(int argc, char *argv[]) {

    if (argc < MATCHES2 || argc > MAX_FLIGHTS) {
        usage();
    }

    FlightDatabase *fdatab = makeDatabase();

    for (int i = 1; i < argc; i++) {
        loadFlightData(argv[i], fdatab);
    }
    
    char *command;

    while (true) {
        const char options[5][50] = {"Show Flight Table - Enter -> list \n", 
                                     "Show Flight Data - Enter -> status <flight ID>\n",
                                     "Show Airports - Enter -> list airports \n",
                                     "Book your flight - Enter -> book <flight ID> \n", 
                                     "Quit the Application - Enter -> quit \n"};  
        displayMenuOptions(options);
        printf("cmd> ");

        command = readLine(stdin);

        if (command == NULL) {
            break;
        } 
        if (strcmp(command, "list") == 0) {
            printf("%s\n", command);
            displayFlightTableHeader();
            displayFlightTableRow(fdatab);

        }
        else if (strcmp(command, "quit") == 0) { 
            printf("%s\n", command);
            free(command);
            break;
        } else {
            printf("%s\n", command);
            printf("Invalid command\n");
            free(command);
        }
        printf("\n");

        // switch () {
        //     case 1:
        //         // showFlightTable(flights, MAX_FLIGHTS);
        //         break;
        //     case 2:
        //         // showFlightData(flights, MAX_FLIGHTS);
        //         break;
        //     case 3:
        //         // showAirports(flights, MAX_FLIGHTS);
        //         break;
        //     case 4:
        //         shouldQuit = 1;
        //         break;
        //     default:
        //         break;
        // }
    }

    printf("Exiting the Flight Information App...\n");
        
    return EXIT_SUCCESS;
}

void loadFlightData(const char *filename, FlightDatabase *fdatab) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename);
        exit(EXIT_FAILURE);
    }
    Flight *newFlight = (Flight *)malloc(sizeof(Flight)); 
    if (!getData(filename, newFlight)) {
        fprintf(stderr, "Error reading flight data from %s\n", filename);
        exit(EXIT_FAILURE);
    }
    fdatab->flight[fdatab->count++] = newFlight;
    fclose(fp);
}
    // for (int i = 0; i < maxFlights; i++) {
    //     char filename[20];
    //     snprintf(filename, sizeof(filename), "flight-%d.txt", i + 1);
    //     if (getData(filename, fdatab->flight, maxFlights) != 0) {
    //         fprintf(stderr, "Error loading data from %s. Exiting...\n", filename);
    //         exit(EXIT_FAILURE);
    //     }
    // }
