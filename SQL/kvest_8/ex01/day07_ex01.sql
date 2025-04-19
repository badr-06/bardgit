SELECT person.name, COUNT(*) as count_of_visits
from person_visits
join person on person.id = person_visits.person_id
GROUP by person.name
order by 2 desc, 1
LIMIT 4