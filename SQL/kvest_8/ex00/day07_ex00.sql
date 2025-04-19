SELECT person_id, COUNT(*) as count_of_visits
from person_visits
GROUP by person_id
order by 2 desc, 1