SELECT id
from person_visits
where visit_date BETWEEN date '2022-01-06' and date '2022-01-09'
ORDER by id DESC