# Wanderlust.co - Tourism Management System

## Overview
Wanderlust.co is a C++ console-based tourism management system that allows customers to browse and book travel packages, and enables managers to add packages, approve bookings, and manage important details. The system uses MySQL for database operations and provides a simple text-based interface for users to interact with.

## Features

### Customer Features
- **User Registration**: Create a new account with name, mobile number, and password
- **User Login**: Access your account using user ID and password
- **View Packages**: Browse different types of travel packages:
  - International packages
  - National packages
  - Pilgrimage packages
  - Budget-based packages
- **Book Packages**: Select and book a package with customizable options:
  - Number of adults
  - Number of children
  - Preferred travel date
- **View Bookings**: Check the status of your booked packages

### Manager Features
- **Manager Login**: Secure access with password protection
- **Add Packages**: Create new travel packages with details:
  - Package type (International, National, Pilgrimage)
  - Destination
  - Duration (days and nights)
  - Budget per person
  - Description
- **Approve Bookings**: Review and approve pending customer bookings
- **Manage Important Details**: Add and view important contact information

## Technical Requirements

### Dependencies
- C++ compiler (supporting C++11 or later)
- MySQL Server
- MySQL Connector/C++ library

## Usage Guide

### Customer Interface
1. Select "For Customer" from the main menu
2. Choose "Login" or "Sign Up"
3. After logging in, you can:
   - View packages by type or budget
   - View your booked packages
   - Log out

### Manager Interface
1. Select "For Manager" from the main menu
2. Enter the manager password (default: "1234")
3. After logging in, you can:
   - Add new packages
   - Approve pending bookings
   - View important details
   - Add new important details
   - Log out

## Future Enhancements
- Implement better code organization with multiple files
- Add more security features
- Improve the user interface
- Add payment processing functionality
- Include search and filter options for packages

## Credits
Developed as a semester 3 OOP project.
