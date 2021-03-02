-- Keep a log of any SQL queries you execute as you solve the mystery.
-- People took flight on July 28, 2020
SELECT name FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
JOIN flights ON passengers.flight_id = flights.id
WHERE year = 2020 AND month = 7 AND day = 28;


-- People took flight on July 28, 2020 from Fiftyville
SELECT name FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
JOIN flights ON passengers.flight_id = flights.id
JOIN airports ON airports.id = flights.origin_airport_id
WHERE year = 2020 AND month = 7 AND day = 28 AND city = 'Fiftyville';


-- List of people who took flight on July 28, 2020 from Fiftyville and
-- been to court before
SELECT name FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
JOIN flights ON passengers.flight_id = flights.id
JOIN airports ON airports.id = flights.origin_airport_id
WHERE year = 2020 AND month = 7 AND day = 28 AND city = 'Fiftyville'
INTERSECT
SELECT name FROM people
JOIN courthouse_security_logs ON courthouse_security_logs.license_plate = people.license_plate;


-- Now lets look at the crime scene reports on July 28, 2020 at Chamberlin Street.
SELECT description FROM crime_scene_reports
WHERE year = 2020 AND month = 7 AND day = 28 AND street = 'Chamberlin Street';

-- Now look at the three intervies took after the theft happened
SELECT name, transcript FROM interviews
WHERE year = 2020 AND month = 7 AND day = 28 AND transcript LIKE "%courthouse%";

-- As Raymond mentioned in the interview the thief was planning to get fligt the next day
-- So lets see all the fligh record for July 29, 2020
-- People took flight on July 29, 2020 from Fiftyville
SELECT name FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
JOIN flights ON passengers.flight_id = flights.id
JOIN airports ON airports.id = flights.origin_airport_id
WHERE year = 2020 AND month = 7 AND day = 29 AND city = 'Fiftyville';

-- As Eugene mention the thief withdrew some money from ATM, so lets see who
-- did ATM tranction on that day
SELECT atm_location FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
WHERE year = 2020 AND month = 7 AND day = 28;

-- Now lets see who did ATM tranction on July 28, 2020 and took flight on July 29, 2020
SELECT name FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
JOIN flights ON passengers.flight_id = flights.id
JOIN airports ON airports.id = flights.origin_airport_id
WHERE year = 2020 AND month = 7 AND day = 29 AND city = 'Fiftyville'
INTERSECT
SELECT name FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
WHERE year = 2020 AND month = 7 AND day = 28;

-- As Ruth suggested us to look at courthouse security logs as the theft left the parking
-- on that day. So lets see who exited out of court_house on that day
SELECT name FROM people
JOIN courthouse_security_logs ON courthouse_security_logs.license_plate = people.license_plate
WHERE year = 2020 AND month = 7 AND day = 28 AND activity="exit";

-- Now lets see who exited out of court_house on July 28, 2020 and did ATM tranction on
-- July 28, 2020 and took flight on July 29, 2020
SELECT name FROM people
JOIN courthouse_security_logs ON courthouse_security_logs.license_plate = people.license_plate
WHERE year = 2020 AND month = 7 AND day = 28 AND activity="exit"
INTERSECT
SELECT name FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
JOIN flights ON passengers.flight_id = flights.id
JOIN airports ON airports.id = flights.origin_airport_id
WHERE year = 2020 AND month = 7 AND day = 29 AND city = 'Fiftyville'
INTERSECT
SELECT name FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
WHERE year = 2020 AND month = 7 AND day = 28;
-- prettry cool, now we are left with only 6 persons, lets find out who is the theft among them

-- I just checked the crime scene report again and It mentioned the theft was happened at 10:15am
-- now lets narrow down more and see who exited out of court_house on July 28, 2020 within 10 min of theft
-- and did ATM tranction on July 28, 2020 and took flight on July 29, 2020
SELECT name FROM people
JOIN courthouse_security_logs ON courthouse_security_logs.license_plate = people.license_plate
WHERE year = 2020 AND month = 7 AND day = 28 AND activity="exit"
AND hour = 10 AND minute > 15 AND minute < 30
INTERSECT
SELECT name FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
JOIN flights ON passengers.flight_id = flights.id
JOIN airports ON airports.id = flights.origin_airport_id
WHERE year = 2020 AND month = 7 AND day = 29 AND city = 'Fiftyville'
INTERSECT
SELECT name FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
WHERE year = 2020 AND month = 7 AND day = 28;
-- Dope now left with only 3 persons

-- Just saw Eugene had aslo mentioned the atm location, lets apply that filter also
SELECT name FROM people
JOIN courthouse_security_logs ON courthouse_security_logs.license_plate = people.license_plate
WHERE year = 2020 AND month = 7 AND day = 28 AND activity="exit"
AND hour = 10 AND minute > 15 AND minute < 30
INTERSECT
SELECT name FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
JOIN flights ON passengers.flight_id = flights.id
JOIN airports ON airports.id = flights.origin_airport_id
WHERE year = 2020 AND month = 7 AND day = 29 AND city = 'Fiftyville'
INTERSECT
SELECT name FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location="Fifer Street";
-- Well no improvement again left with 3 person


-- As Raymond also mentiond the theft also called someone, so lets apply filter for caller
-- and the duration was less than a min. Lets use these information
SELECT name FROM people
JOIN phone_calls ON phone_calls.caller = people.phone_number
WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60;

-- Lets interset with the data we already have
SELECT name FROM people
JOIN phone_calls ON phone_calls.caller = people.phone_number
WHERE year = 2020 AND month = 7 AND day = 28 and duration < 60
INTERSECT
SELECT name FROM people
JOIN courthouse_security_logs ON courthouse_security_logs.license_plate = people.license_plate
WHERE year = 2020 AND month = 7 AND day = 28 AND activity="exit" AND hour = 10
AND minute > 15 AND minute < 30
INTERSECT
SELECT name FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
JOIN flights ON passengers.flight_id = flights.id
JOIN airports ON airports.id = flights.origin_airport_id
WHERE year = 2020 AND month = 7 AND day = 29 AND city = 'Fiftyville'
INTERSECT
SELECT name FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location="Fifer Street";
-- Cool Now the only suspect is either Ernest or Russell

-- So it is mentioned the theft took the earliest flight on July 29, 2020. So lets check that
SELECT name, hour, minute FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
JOIN flights ON passengers.flight_id = flights.id
JOIN airports ON airports.id = flights.origin_airport_id
WHERE year = 2020 AND month = 7 AND day = 29 AND city = 'Fiftyville'
ORDER BY hour, minute;
-- So From this data we came to know about the earliest flight was on 08:20am
-- Lets apply this filer also

SELECT name FROM people
JOIN phone_calls ON phone_calls.caller = people.phone_number
WHERE year = 2020 AND month = 7 AND day = 28 and duration < 60
INTERSECT
SELECT name FROM people
JOIN courthouse_security_logs ON courthouse_security_logs.license_plate = people.license_plate
WHERE year = 2020 AND month = 7 AND day = 28 AND activity="exit" AND hour = 10
 AND minute > 15 AND minute < 30
INTERSECT
SELECT name FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
JOIN flights ON passengers.flight_id = flights.id
JOIN airports ON airports.id = flights.origin_airport_id
WHERE year = 2020 AND month = 7 AND day = 29 AND hour = 8 AND minute = 20 AND city = 'Fiftyville'
INTERSECT
SELECT name FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location="Fifer Street";
-- Finally got it Ernest was the theft

-- Lets findout where did Ernest went do
-- First findout the Fligh ID of the flight which Ernest took
SELECT name, flights.id FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
JOIN flights ON passengers.flight_id = flights.id
JOIN airports ON airports.id = flights.origin_airport_id
WHERE year = 2020 AND month = 7 AND day = 29 AND hour = 8 AND minute = 20
AND city = 'Fiftyville'AND name = "Ernest";
-- Now lets find out where the flight Landed
SELECT city FROM airports
JOIN flights ON flights.destination_airport_id = airports.id
WHERE year = 2020 AND month = 7 AND day = 29 AND flights.id = 36;
-- So Ernest escaped to London

--Lets find who was helping Ernest
-- First findout the phone no. whit whome Ernest was talking to
SELECT name, receiver FROM people
JOIN phone_calls ON phone_calls.caller = people.phone_number
WHERE year = 2020 AND month = 7 AND day = 28 and duration < 60 AND name = "Ernest";
-- So the receiver's phone no is (375) 555-8161, Lets find out who was that person
SELECT name FROM people
WHERE phone_number = "(375) 555-8161";
-- Berthold was helping Ernest
-- Yoohooo, case solved


