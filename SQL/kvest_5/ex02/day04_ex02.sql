CREATE view v_generated_dates AS
SELECT generated_date::date
FROM GENERATE_SERIES('2022-01-01'::date, '2022-01-31'::date, '1 day'::INTERVAL) as generated_date