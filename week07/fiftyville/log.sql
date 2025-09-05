-- Keep a log of any SQL queries you execute as you solve the mystery.
-- 寻找与鸭子有关的案件
SELECT * FROM crime_scene_reports
WHERE description LIKE '%duck%';
--得到结果（id =295 year =2024 month =7 day =28 street =Humphrey Street）
/*详情
这只CS50的鸭子于上午10点15分在汉弗莱街的面包店被盗。今天我们采访了当时在场的三名证人，他们的采访记录都提到了那家面包店
    （原文：Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
    Interviews were conducted today with three witnesses who were present at the time– each of their interview transcripts mentions the bakery.）
*/
--查看具体笔录(对应时间)
SELECT * FROM interviews
WHERE year = 2024 AND month = 7 AND day = 28;
/*我们收获了三个证人
1.文档ID 161:
   - 人物: Ruth
   - 内容: 盗窃案发生后的十分钟左右，我看到小偷在面包店的停车场上了一辆车开走了。如果你们有面包店停车场的监控录像，你们可能会想要查看那个时间段离开停车场车辆的情况。
   (原文： 161 | Ruth    | 2024 | 7     | 28  | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
   If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame. )
2.文档ID 162:
   - 人物: Eugene
   - 内容: 我不知道小偷的名字，但我认出了他。今天早上，在我到达艾玛的面包店之前，我路过莱格特街的自动取款机，看到小偷在那里取钱。
   (原文： 162 | Eugene  | 2024 | 7     | 28  | I don't know the thief's name, but I recognized him.
   This morning, before I arrived at Emma's bakery, I passed the ATM on Leggett Street and saw the thief withdrawing cash there.)
3.文档ID 163:
   - 人物: Raymond
   - 内容: 小偷离开面包店时，他们给某人打了个电话，通话时间不到一分钟。在电话中，我听到小偷说他们计划明天乘坐最早一班飞机离开五十维尔。小偷随后请求电话那头的人为他们购买机票。
   (原文： 163 | Raymond | 2024 | 7     | 28  | When the thief left the bakery, they made a phone call that lasted less than a minute.
    During the call, I heard the thief say they planned to take the earliest flight out of Fiftyville tomorrow.
    The thief then asked the person on the other end of the line to buy them a plane ticket.)
*/
--通过161证词，确定时间，查看监控录像
SELECT * FROM bakery_security_logs
WHERE year = 2024 AND month = 7 AND day = 28 AND hour = 10 AND (minute BETWEEN 15 AND 30);
/*收集到的原数据
+-----+------+-------+-----+------+--------+----------+---------------+
| id  | year | month | day | hour | minute | activity | license_plate |
+-----+------+-------+-----+------+--------+----------+---------------+
| 260 | 2024 | 7     | 28  | 10   | 16     | exit     | 5P2BI95       |
| 261 | 2024 | 7     | 28  | 10   | 18     | exit     | 94KL13X       |
| 262 | 2024 | 7     | 28  | 10   | 18     | exit     | 6P58WS2       |
| 263 | 2024 | 7     | 28  | 10   | 19     | exit     | 4328GD8       |
| 264 | 2024 | 7     | 28  | 10   | 20     | exit     | G412CB7       |
| 265 | 2024 | 7     | 28  | 10   | 21     | exit     | L93JTIZ       |
| 266 | 2024 | 7     | 28  | 10   | 23     | exit     | 322W7JE       |
| 267 | 2024 | 7     | 28  | 10   | 23     | exit     | 0NTHK55       |
+-----+------+-------+-----+------+--------+----------+---------------+
*/
--查询通话记录
SELECT * FROM phone_calls
WHERE year = 2024 AND month = 7 AND day = 28 AND duration < 60;
/*收集到的原数据
+-----+----------------+----------------+------+-------+-----+----------+
| id  |     caller     |    receiver    | year | month | day | duration |
+-----+----------------+----------------+------+-------+-----+----------+
| 221 | (130) 555-0289 | (996) 555-8899 | 2024 | 7     | 28  | 51       |
| 224 | (499) 555-9472 | (892) 555-8872 | 2024 | 7     | 28  | 36       |
| 233 | (367) 555-5533 | (375) 555-8161 | 2024 | 7     | 28  | 45       |
| 251 | (499) 555-9472 | (717) 555-1342 | 2024 | 7     | 28  | 50       |
| 254 | (286) 555-6063 | (676) 555-6554 | 2024 | 7     | 28  | 43       |
| 255 | (770) 555-1861 | (725) 555-3243 | 2024 | 7     | 28  | 49       |
| 261 | (031) 555-6622 | (910) 555-3251 | 2024 | 7     | 28  | 38       |
| 279 | (826) 555-1652 | (066) 555-9701 | 2024 | 7     | 28  | 55       |
| 281 | (338) 555-6650 | (704) 555-2131 | 2024 | 7     | 28  | 54       |
+-----+----------------+----------------+------+-------+-----+----------+
*/
--查询ATM取款记录
SELECT * FROM atm_transactions
WHERE year = 2024 AND month = 7 AND day = 28 AND atm_location LIKE '%Leggett%' AND transaction_type LIKE '%withdraw%';
/*查询到的原数据
+-----+----------------+------+-------+-----+----------------+------------------+--------+
| id  | account_number | year | month | day |  atm_location  | transaction_type | amount |
+-----+----------------+------+-------+-----+----------------+------------------+--------+
| 246 | 28500762       | 2024 | 7     | 28  | Leggett Street | withdraw         | 48     |
| 264 | 28296815       | 2024 | 7     | 28  | Leggett Street | withdraw         | 20     |
| 266 | 76054385       | 2024 | 7     | 28  | Leggett Street | withdraw         | 60     |
| 267 | 49610011       | 2024 | 7     | 28  | Leggett Street | withdraw         | 50     |
| 269 | 16153065       | 2024 | 7     | 28  | Leggett Street | withdraw         | 80     |
| 288 | 25506511       | 2024 | 7     | 28  | Leggett Street | withdraw         | 20     |
| 313 | 81061156       | 2024 | 7     | 28  | Leggett Street | withdraw         | 30     |
| 336 | 26013199       | 2024 | 7     | 28  | Leggett Street | withdraw         | 35     |
+-----+----------------+------+-------+-----+----------------+------------------+--------+
*/
--查询重叠ID
SELECT name FROM people
WHERE id IN (
    SELECT id FROM people
    WHERE license_plate IN (
        SELECT license_plate FROM bakery_security_logs
        WHERE year = 2024 AND month = 7 AND day = 28 AND hour = 10 AND (minute BETWEEN 15 AND 30)
    )
    AND id IN (
        SELECT id FROM people
        WHERE phone_number IN (
            SELECT caller FROM phone_calls
            WHERE year = 2024 AND month = 7 AND day = 28 AND duration < 60
        )
    )
    AND id IN (
        SELECT person_id FROM bank_accounts
        WHERE account_number IN (
            SELECT account_number FROM atm_transactions
            WHERE year = 2024 AND month = 7 AND day = 28 AND atm_location LIKE '%Leggett%' AND transaction_type LIKE '%withdraw%'
        )
    )
);
/*重叠的ID
+-------+
| name  |
+-------+
| Diana |
| Bruce |
+-------+
*/


--查询护照信息(防止使用同伙证件购买)
SELECT name, passport_number FROM people
WHERE phone_number IN (
    SELECT receiver FROM phone_calls
    WHERE caller IN (SELECT phone_number FROM people WHERE name IN ('Diana', 'Bruce'))
    AND year = 2024 AND month = 7 AND day = 28 AND duration < 60
)
OR name IN ('Diana', 'Bruce');
/*护照信息
+--------+-----------------+
|  name  | passport_number |
+--------+-----------------+
| Diana  | 3592750733      |
| Bruce  | 5773159633      |
| Philip | 3391710505      |
| Robin  | NULL            |
+--------+-----------------+
*/
--再次查询id
SELECT name FROM people
WHERE
    (phone_number IN (
        SELECT receiver FROM phone_calls
        WHERE caller IN (SELECT phone_number FROM people WHERE name IN ('Diana','Bruce'))
          AND year = 2024 AND month = 7 AND day = 28
          AND duration < 60
    ) OR name IN ('Diana', 'Bruce'))
AND passport_number IN (
    SELECT passport_number FROM passengers
    WHERE flight_id IN (
        SELECT id FROM flights
        WHERE year = 2024 AND month = 7 AND day = 29
    )
);
/*
+-------+
| name  |
+-------+
| Diana |
| Bruce |
+-------+
*/
--查询航班
SELECT * FROM flights
WHERE id IN (
    SELECT flight_id FROM passengers
    WHERE passport_number IN
        (SELECT passport_number FROM people
        WHERE name IN ('Diana', 'Bruce')
        )
AND id IN
    (SELECT id FROM flights
            WHERE year = 2024 AND month = 7 AND day = 29
    )
)
ORDER BY hour, minute
     LIMIT 1;
/*原数据
+----+-------------------+------------------------+------+-------+-----+------+--------+
| id | origin_airport_id | destination_airport_id | year | month | day | hour | minute |
+----+-------------------+------------------------+------+-------+-----+------+--------+
| 36 | 8                 | 4                      | 2024 | 7     | 29  | 8    | 20     |
+----+-------------------+------------------------+------+-------+-----+------+--------+
*/
--查询是谁最早的航班 id = 36
SELECT name FROM people
WHERE passport_number IN(
    SELECT passport_number FROM passengers
    WHERE flight_id = 36
    AND passport_number IN(
        SELECT passport_number FROM people
        WHERE name IN ('Diana', 'Bruce')
    )
);
/*确认小偷
+-------+
| Bruce |
+-------+
*/
--确认同伙
SELECT name FROM people
WHERE phone_number IN (
    SELECT receiver FROM phone_calls
    WHERE caller IN (SELECT phone_number FROM people WHERE name IN ('Bruce'))
    AND year = 2024 AND month = 7 AND day = 28 AND duration < 60
);
/*
+-------+
| name  |
+-------+
| Robin |
+-------+
*/
--找到逃跑到的城市
SELECT city FROM airports
WHERE id = 4;
/*
+---------------+
|     city      |
+---------------+
| New York City |
+---------------+
*/
--整合一下
-- 综合查询：找出小偷、同伙及逃跑城市
SELECT
    thief.name AS thief,
    accomplice.name AS accomplice,
    destination.city AS escaped_to_city
FROM
    people AS thief
JOIN
    phone_calls ON thief.phone_number = phone_calls.caller
JOIN
    people AS accomplice ON phone_calls.receiver = accomplice.phone_number
JOIN
    passengers ON thief.passport_number = passengers.passport_number
JOIN
    flights ON passengers.flight_id = flights.id
JOIN
    airports AS destination ON flights.destination_airport_id = destination.id
WHERE
    -- 案发时间面包店停车场监控条件
    thief.license_plate IN (
        SELECT license_plate FROM bakery_security_logs
        WHERE year = 2024 AND month = 7 AND day = 28
        AND hour = 10 AND minute BETWEEN 15 AND 25
        AND activity = 'exit'
    )
    -- ATM取款条件
    AND thief.id IN (
        SELECT person_id FROM bank_accounts
        WHERE account_number IN (
            SELECT account_number FROM atm_transactions
            WHERE year = 2024 AND month = 7 AND day = 28
            AND atm_location = 'Leggett Street'
            AND transaction_type = 'withdraw'
        )
    )
    -- 通话记录条件
    AND phone_calls.year = 2024
    AND phone_calls.month = 7
    AND phone_calls.day = 28
    AND phone_calls.duration < 60
    -- 最早航班条件
    AND flights.id = (
        SELECT id FROM flights
        WHERE year = 2024 AND month = 7 AND day = 29
        ORDER BY hour, minute
        LIMIT 1
    )
LIMIT 1;
