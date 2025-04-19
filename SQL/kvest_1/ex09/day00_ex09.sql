SELECT (
  	SELECT name from person where person.id = pv.person_id
  ) as person_name,
  (
    SELECT name FROM pizzeria where pizzeria.id = pv.pizzeria_id
  ) as pizzeria_name
from (
    SELECT * from person_visits where visit_date BETWEEN date '2022-01-07' and date '2022-01-09'
    ) as pv
ORDER by 1, 2 DESC