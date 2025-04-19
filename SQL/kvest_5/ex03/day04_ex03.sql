SELECT generated_date as missing_date from v_generated_dates
EXCEPT
SELECT visit_date from person_visits
ORDER by 1