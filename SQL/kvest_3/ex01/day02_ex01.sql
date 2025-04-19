SELECT missing_date::date
FROM GENERATE_SERIES(date '2022-01-01', date '2022-01-10', INTERVAL '1 day') AS missing_date
left jOIN person_visits pv ON pv.visit_date = missing_date and (pv.person_id = 1 or pv.person_id = 2)
where pv.visit_date is NULL
ORDER BY missing_date;