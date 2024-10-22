-- Retrieve the crime record on July 28, 2023
SELECT *
FROM crime_scene_reports
WHERE day = 28 AND month = 7 AND year = 2023;

--|  295 | 2023 | 7     | 28  | Humphrey Street | Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
-- Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery. |


-- Retrieve interviews mentioning the bakery on July 28, 2023
SELECT *
FROM interviews
WHERE day = 28 AND month = 7 AND year = 2023 AND transcript LIKE '%bakery%';


-- | 161 | Ruth    | 2023 | 7     | 28  | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
-- If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.

-- | 162 | Eugene  | 2023 | 7     | 28  | I don't know the thief's name, but it was someone I recognized.
-- Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.

-- | 163 | Raymond | 2023 | 7     | 28  | As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
-- In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
-- The thief then asked the person on the other end of the phone to purchase the flight ticket. |


-- Retrieve vehicles that exited the bakery parking lot between 10:15 and 10:35 AM
SELECT *
FROM bakery_security_logs
WHERE day = 28 AND month = 7 AND year = 2023 AND hour = 10 AND minute BETWEEN 15 AND 35 AND activity LIKE '%exit%';

+-----+------+-------+-----+------+--------+----------+---------------+
| id  | year | month | day | hour | minute | activity | license_plate |
+-----+------+-------+-----+------+--------+----------+---------------+
| 260 | 2023 | 7     | 28  | 10   | 16     | exit     | 5P2BI95       |
| 261 | 2023 | 7     | 28  | 10   | 18     | exit     | 94KL13X       |
| 262 | 2023 | 7     | 28  | 10   | 18     | exit     | 6P58WS2       |
| 263 | 2023 | 7     | 28  | 10   | 19     | exit     | 4328GD8       |
| 264 | 2023 | 7     | 28  | 10   | 20     | exit     | G412CB7       |
| 265 | 2023 | 7     | 28  | 10   | 21     | exit     | L93JTIZ       |
| 266 | 2023 | 7     | 28  | 10   | 23     | exit     | 322W7JE       |
| 267 | 2023 | 7     | 28  | 10   | 23     | exit     | 0NTHK55       |
| 268 | 2023 | 7     | 28  | 10   | 35     | exit     | 1106N58       |
+-----+------+-------+-----+------+--------+----------+---------------+


-- Retrieve ATM withdrawal transactions at Leggett Street on July 28, 2023
SELECT *
FROM atm_transactions
WHERE day = 28 AND month = 7 AND year = 2023 AND atm_location LIKE '%Leggett Street%' AND transaction_type LIKE '%withdraw%';

+-----+----------------+------+-------+-----+----------------+------------------+--------+
| id  | account_number | year | month | day |  atm_location  | transaction_type | amount |
+-----+----------------+------+-------+-----+----------------+------------------+--------+
| 246 | 28500762       | 2023 | 7     | 28  | Leggett Street | withdraw         | 48     |
| 264 | 28296815       | 2023 | 7     | 28  | Leggett Street | withdraw         | 20     |
| 266 | 76054385       | 2023 | 7     | 28  | Leggett Street | withdraw         | 60     |
| 267 | 49610011       | 2023 | 7     | 28  | Leggett Street | withdraw         | 50     |
| 269 | 16153065       | 2023 | 7     | 28  | Leggett Street | withdraw         | 80     |
| 288 | 25506511       | 2023 | 7     | 28  | Leggett Street | withdraw         | 20     |
| 313 | 81061156       | 2023 | 7     | 28  | Leggett Street | withdraw         | 30     |
| 336 | 26013199       | 2023 | 7     | 28  | Leggett Street | withdraw         | 35     |
+-----+----------------+------+-------+-----+----------------+------------------+--------+


-- Retrieve people associated with the account numbers
SELECT *
FROM bank_accounts
WHERE account_number IN (28500762, 28296815, 76054385, 49610011, 16153065, 25506511, 81061156, 26013199);

+----------------+-----------+---------------+
| account_number | person_id | creation_year |
+----------------+-----------+---------------+
| 49610011       | 686048    | 2010          |
| 26013199       | 514354    | 2012          |
| 16153065       | 458378    | 2012          |
| 28296815       | 395717    | 2014          |
| 25506511       | 396669    | 2014          |
| 28500762       | 467400    | 2014          |
| 76054385       | 449774    | 2015          |
| 81061156       | 438727    | 2018          |
+----------------+-----------+---------------+


-- Retrieve flight details on July 29, 2023
SELECT *
FROM flights
WHERE year = 2023 AND month = 7 AND day = 29;

+----+-------------------+------------------------+------+-------+-----+------+--------+
| id | origin_airport_id | destination_airport_id | year | month | day | hour | minute |
+----+-------------------+------------------------+------+-------+-----+------+--------+
| 18 | 8                 | 6                      | 2023 | 7     | 29  | 16   | 0      |
| 23 | 8                 | 11                     | 2023 | 7     | 29  | 12   | 15     |
| 36 | 8                 | 4                      | 2023 | 7     | 29  | 8    | 20     |
| 43 | 8                 | 1                      | 2023 | 7     | 29  | 9    | 30     |
| 53 | 8                 | 9                      | 2023 | 7     | 29  | 15   | 20     |
+----+-------------------+------------------------+------+-------+-----+------+--------+


-- Retrieve the destination city for flights on July 29, 2023 (Airport where the thief went)
SELECT *
FROM airports
WHERE id = 4;

+----+--------------+-------------------+---------------+
| id | abbreviation |     full_name     |     city      |
+----+--------------+-------------------+---------------+
| 4  | LGA          | LaGuardia Airport | New York City | !!!!!!!!!
+----+--------------+-------------------+---------------+


-- Retrieve details of the person with person_id = 686048
SELECT *
FROM people
WHERE id = 686048;

+--------+-------+----------------+-----------------+---------------+
|   id   | name  |  phone_number  | passport_number | license_plate |
+--------+-------+----------------+-----------------+---------------+
| 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       |   !!!!!!!!
+--------+-------+----------------+-----------------+---------------+


-- Retrieve short phone calls made or received on July 28, 2023
SELECT *
FROM phone_calls
WHERE day = 28 AND month = 7 AND year = 2023 AND duration < 60 AND (caller IN ('(130) 555-0289', '(499) 555-9472', '(367) 555-5533') OR receiver IN ('(130) 555-0289', '(499) 555-9472', '(367) 555-5533'));

+-----+----------------+----------------+------+-------+-----+----------+
| id  |     caller     |    receiver    | year | month | day | duration |
+-----+----------------+----------------+------+-------+-----+----------+
| 221 | (130) 555-0289 | (996) 555-8899 | 2023 | 7     | 28  | 51       |
| 224 | (499) 555-9472 | (892) 555-8872 | 2023 | 7     | 28  | 36       |
| 233 | (367) 555-5533 | (375) 555-8161 | 2023 | 7     | 28  | 45       |   !!!!!!!!
| 251 | (499) 555-9472 | (717) 555-1342 | 2023 | 7     | 28  | 50       |
+-----+----------------+----------------+------+-------+-----+----------+


-- Retrieve people who received the short phone calls
SELECT *
FROM people
WHERE phone_number IN ('(996) 555-8899', '(892) 555-8872', '(717) 555-1342', '(375) 555-8161');

+--------+---------+----------------+-----------------+---------------+
|   id   |  name   |  phone_number  | passport_number | license_plate |
+--------+---------+----------------+-----------------+---------------+
| 251693 | Larry   | (892) 555-8872 | 2312901747      | O268ZZ0       |
| 567218 | Jack    | (996) 555-8899 | 9029462229      | 52R0Y8U       |
| 626361 | Melissa | (717) 555-1342 | 7834357192      | NULL          |
| 864400 | Robin   | (375) 555-8161 | NULL            | 4V16VO0       |
+--------+---------+----------------+-----------------+---------------+

Bruce ((367) 555-5533) Calls Robin ((375) 555-8161)