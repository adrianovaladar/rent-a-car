# rent-a-car

[![Build and test](https://github.com/adrianovaladar/rent-a-car/actions/workflows/build_test.yml/badge.svg)](https://github.com/adrianovaladar/rent-a-car/actions/workflows/build_test.yml)
[![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=adrianovaladar_rent-a-car&metric=alert_status)](https://sonarcloud.io/summary/new_code?id=adrianovaladar_rent-a-car)

Welcome to the Rent-a-Car Management System! This application is designed to manage customers, vehicles, and rental contracts for a portuguese car rental service.

It was originally developed at [ISEP](https://www.isep.ipp.pt) and was fully refactored later on.

## Features
### Customer Management
- Add new customers;
- Manage existing customers by their unique codes;
- Display  customer data.
### Vehicle Management
- Add new vehicles;
- Manage vehicles by their unique codes;
- Display vehicle data;
- Display the location of the vehicles.

### Contract Management
- Create new rental contracts;
- Manage contracts by vehicle code and start date;
- Display rental contract data.

## Requirements
- Operating System: Windows or Linux.

## Installation
### Clone the repository:

```
$ git clone https://github.com/yourusername/rent-a-car.git
$ cd rent-a-car
```

### Compile the project:

```
$ cmake .
$ make
```

### Run the executable:

```
$ ./rent_a_car
```

## Usage
Once you start the application, you'll be greeted with a simple menu. Just enter the number corresponding to what you'd like to do.

Here’s what the menu looks like:

```
Rent-a-car
----------------------- MENU ----------------------

------------------ Customer Area ------------------
1 - Add customer
2 - Manage a customer
3 - Show data of all customers

------------------ Vehicle Area -------------------
11 - Add vehicle
12 - Manage a vehicle
13 - Show data of all vehicles
14 - Show location of all vehicles

------------------ Contract Area ------------------
21 - Rent vehicle
22 - Manage a contract
23 - Show data of all contracts

0 - Exit
```
## File Structure
- constants.h: Contains global constants;
- contract.h/.c: Manages contracts related to vehicle rentals:
- customer.h/.c: Manages customer information:
- vehicle.h/.c: Manages vehicle details and availability;
- input.h/.c: Handles input operations and validation;
- main.c: The entry point of the application.

## Gratitude
This project is dedicated to my dog Marley, who was with me throughout all the development of this project. She will always hold a special place in my heart and be remembered as the best dog in the world.

![IMG_0212](https://github.com/user-attachments/assets/a4a5739b-0736-4ad5-b090-cfb93217631f)

## Creator

This project was created by [**Adriano Valadar**](https://github.com/adrianovaladar).
